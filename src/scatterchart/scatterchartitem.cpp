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

#include "scatterchartitem_p.h"
#include "qscatterseries.h"
#include "qscatterseries_p.h"
#include "chartpresenter_p.h"
#include "abstractdomain_p.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ScatterChartItem::ScatterChartItem(QScatterSeries *series, QGraphicsItem* item)
    : XYChart(series,item),
      m_series(series),
      m_items(this),
      m_visible(true),
      m_shape(QScatterSeries::MarkerShapeRectangle),
      m_size(15)
{
    QObject::connect(m_series->d_func(), SIGNAL(updated()), this, SLOT(handleUpdated()));
    QObject::connect(m_series, SIGNAL(visibleChanged()), this, SLOT(handleUpdated()));
    QObject::connect(m_series, SIGNAL(opacityChanged()), this, SLOT(handleUpdated()));

    setZValue(ChartPresenter::ScatterSeriesZValue);
    setFlags(QGraphicsItem::ItemClipsChildrenToShape);

    handleUpdated();

    m_items.setHandlesChildEvents(false);
}

QRectF ScatterChartItem::boundingRect() const
{
    return m_rect;
}

void ScatterChartItem::createPoints(int count)
{
    for (int i = 0; i < count; ++i) {

        QGraphicsItem *item = 0;

        switch (m_shape) {
        case QScatterSeries::MarkerShapeCircle: {
            item = new CircleMarker(0, 0, m_size, m_size, this);
            const QRectF &rect = item->boundingRect();
            item->setPos(-rect.width() / 2, -rect.height() / 2);
            break;
        }
        case QScatterSeries::MarkerShapeRectangle:
            item = new RectangleMarker(0, 0, m_size, m_size, this);
            item->setPos(-m_size / 2, -m_size / 2);
            break;
        default:
            qWarning() << "Unsupported marker type";
            break;
        }
        m_items.addToGroup(item);
    }
}

void ScatterChartItem::deletePoints(int count)
{
    QList<QGraphicsItem *> items = m_items.childItems();

    for (int i = 0; i < count; ++i) {
        QGraphicsItem *item = items.takeLast();
        m_markerMap.remove(item);
        delete(item);
    }
}

void ScatterChartItem::markerSelected(QGraphicsItem *marker)
{
    emit XYChart::clicked(domain()->calculateDomainPoint(m_markerMap[marker]));
}

void ScatterChartItem::markerHovered(QGraphicsItem *marker, bool state)
{
    emit XYChart::hovered(domain()->calculateDomainPoint(m_markerMap[marker]), state);
}

void ScatterChartItem::updateGeometry()
{

    const QVector<QPointF>& points = geometryPoints();

    if (points.size() == 0) {
        deletePoints(m_items.childItems().count());
        return;
    }

    int diff = m_items.childItems().size() - points.size();

    if (diff > 0)
        deletePoints(diff);
    else if (diff < 0)
        createPoints(-diff);

    if (diff != 0)
        handleUpdated();

    QList<QGraphicsItem *> items = m_items.childItems();

    QRectF clipRect(QPointF(0,0),domain()->size());

    for (int i = 0; i < points.size(); i++) {
        QGraphicsItem *item = items.at(i);
        const QPointF &point = points.at(i);
        const QRectF &rect = item->boundingRect();
        m_markerMap[item] = point;
        item->setPos(point.x() - rect.width() / 2, point.y() - rect.height() / 2);
        if (!m_visible || !clipRect.contains(point))
            item->setVisible(false);
        else
            item->setVisible(true);
    }

    prepareGeometryChange();
    m_rect = clipRect;
}

void ScatterChartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(widget)
}

void ScatterChartItem::setPen(const QPen &pen)
{
    foreach (QGraphicsItem *item , m_items.childItems())
        static_cast<QAbstractGraphicsShapeItem*>(item)->setPen(pen);
}

void ScatterChartItem::setBrush(const QBrush &brush)
{
    foreach (QGraphicsItem *item , m_items.childItems())
        static_cast<QAbstractGraphicsShapeItem*>(item)->setBrush(brush);
}

void ScatterChartItem::handleUpdated()
{
    int count = m_items.childItems().count();

    if (count == 0)
        return;

    bool recreate = m_visible != m_series->isVisible()
                    || m_size != m_series->markerSize()
                    || m_shape != m_series->markerShape();

    m_visible = m_series->isVisible();
    m_size = m_series->markerSize();
    m_shape = m_series->markerShape();
    setOpacity(m_series->opacity());

    if (recreate) {        
        deletePoints(count);
        createPoints(count);

        // Updating geometry is now safe, because it won't call handleUpdated unless it creates/deletes points
        updateGeometry();
    }

    setPen(m_series->pen());
    setBrush(m_series->brush());
    update();
}

#include "moc_scatterchartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
