/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "linechartitem_p.h"
#include "qlineseries.h"
#include "qlineseries_p.h"
#include "chartpresenter_p.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

const qreal mouseEventMinWidth(12);

LineChartItem::LineChartItem(QLineSeries* series,ChartPresenter *presenter):
    XYChart(series, presenter),
    QGraphicsItem(presenter ? presenter->rootItem() : 0),
    m_series(series),
    m_pointsVisible(false)
{
    setZValue(ChartPresenter::LineChartZValue);
    QObject::connect(series->d_func(),SIGNAL(updated()),this,SLOT(handleUpdated()));
    QObject::connect(series, SIGNAL(visibleChanged()), this, SLOT(handleUpdated()));
    handleUpdated();
}

QRectF LineChartItem::boundingRect() const
{
	return m_rect;
}

QPainterPath LineChartItem::shape() const
{
    return m_path;
}

void LineChartItem::updateGeometry()
{
    m_points = geometryPoints();

    if(m_points.size()==0)
    {
        prepareGeometryChange();
        m_path = QPainterPath();
        m_rect = QRect();
        return;
    }

    QPainterPath linePath(m_points.at(0));

    if(m_pointsVisible) {

        int size = m_linePen.width();
        linePath.addEllipse(m_points.at(0),size,size);
        for(int i=1; i< m_points.size();i++) {
            linePath.lineTo(m_points.at(i));
            linePath.addEllipse(m_points.at(i),size,size);
        }

    } else {

        for(int i=1; i< m_points.size();i++) {
            linePath.lineTo(m_points.at(i));
        }
    }

    m_linePath=linePath;
    QPainterPathStroker stroker;
    stroker.setWidth(m_linePen.width()*1.42);
    stroker.setJoinStyle(m_linePen.joinStyle());
    stroker.setCapStyle(m_linePen.capStyle());
    stroker.setMiterLimit(m_linePen.miterLimit());

    prepareGeometryChange();

    m_path = stroker.createStroke(linePath);
    m_rect = m_path.boundingRect();

    setPos(origin());
}

void LineChartItem::handleUpdated()
{
    setVisible(m_series->isVisible());
    m_pointsVisible = m_series->pointsVisible();
    m_linePen = m_series->pen();
    update();
}

void LineChartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setPen(m_linePen);

    painter->setBrush(m_linePen.color());
    painter->setClipRect(clipRect());

    if (m_pointsVisible) {
        painter->drawPath(m_linePath);
    }
    else {
        for (int i(1); i < m_points.size();i++)
        painter->drawLine(m_points.at(i-1), m_points.at(i));
    }
}

void LineChartItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit XYChart::clicked(calculateDomainPoint(event->pos()));
    QGraphicsItem::mousePressEvent(event);
}

#include "moc_linechartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
