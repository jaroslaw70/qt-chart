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

#include "barchartitem_p.h"
#include "bar_p.h"
#include "qbarset.h"
#include "qbarset_p.h"
#include "qbarseries.h"
#include "qbarseries_p.h"
#include "qchart.h"
#include "chartpresenter_p.h"
#include "chartanimator_p.h"
#include "chartdataset_p.h"
#include <QPainter>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarChartItem::BarChartItem(QAbstractBarSeries *series, ChartPresenter *presenter) :
    ChartItem(presenter),
    m_series(series)
{
    setFlag(ItemClipsChildrenToShape);
    connect(series->d_func(), SIGNAL(updatedBars()), this, SLOT(handleLayoutChanged()));
    connect(series->d_func(), SIGNAL(labelsVisibleChanged(bool)), this, SLOT(handleLabelsVisibleChanged(bool)));
    connect(series->d_func(), SIGNAL(restructuredBars()), this, SLOT(handleDataStructureChanged()));
    connect(series, SIGNAL(visibleChanged()), this, SLOT(handleVisibleChanged()));
    setZValue(ChartPresenter::BarSeriesZValue);
    handleDataStructureChanged();
}

BarChartItem::~BarChartItem()
{
}

void BarChartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF BarChartItem::boundingRect() const
{
    return m_rect;
}

QVector<QRectF> BarChartItem::calculateLayout()
{
    QVector<QRectF> layout;

    // Use temporary qreals for accuracy
    qreal categoryCount = m_series->d_func()->categoryCount();
    qreal setCount = m_series->count();
    bool barsVisible = m_series->isVisible();

    // Domain:
    qreal width = geometry().width();
    qreal height = geometry().height();
    qreal rangeY = m_domainMaxY - m_domainMinY;
    qreal rangeX = m_domainMaxX - m_domainMinX;
    qreal scaleY = (height / rangeY);
    qreal scaleX = (width / rangeX);
    qreal barWidth = scaleX * m_series->d_func()->barWidth();

    int itemIndex(0);
    for (int category = 0; category < categoryCount; category++) {
        qreal yPos = height + scaleY * m_domainMinY + geometry().topLeft().y();
        for (int set = 0; set < setCount; set++) {
            QBarSetPrivate* barSet = m_series->d_func()->barsetAt(set)->d_ptr.data();
            qreal xPos = (barSet->m_values.at(category).x() - m_domainMinX) * scaleX + m_rect.left() - barWidth/2;
            qreal barHeight = barSet->m_values.at(category).y() * scaleY;

            Bar* bar = m_bars.at(itemIndex);
            QRectF rect(xPos, yPos - barHeight, barWidth, barHeight);

            layout.append(rect);
            bar->setPen(barSet->m_pen);
            bar->setBrush(barSet->m_brush);
            bar->setVisible(barsVisible);

            QGraphicsSimpleTextItem* label = m_labels.at(itemIndex);

            if (!qFuzzyIsNull(barSet->m_values.at(category).y())) {
                label->setText(QString::number(barSet->m_values.at(category).y()));
            } else {
                label->setText(QString(""));
            }

            label->setPos(xPos + (rect.width()/2 - label->boundingRect().width()/2)
                          ,yPos - barHeight/2 - label->boundingRect().height()/2);
            label->setFont(barSet->m_labelFont);
            label->setBrush(barSet->m_labelBrush);

            itemIndex++;
        }
    }

    return layout;
}

void BarChartItem::applyLayout(const QVector<QRectF> &layout)
{
    if (animator()) {
        animator()->updateLayout(this, m_layout, layout);
    } else {
        setLayout(layout);
        update();
    }
}

void BarChartItem::setLayout(const QVector<QRectF> &layout)
{
    if (layout.count() != m_bars.count())
        return;

    m_layout = layout;    

    for (int i=0; i < m_bars.count(); i++) {
        m_bars.at(i)->setRect(layout.at(i));
    }
}
//handlers

void BarChartItem::handleDomainChanged(qreal minX, qreal maxX, qreal minY, qreal maxY)
{
    m_domainMinX = minX;
    m_domainMaxX = maxX;
    m_domainMinY = minY;
    m_domainMaxY = maxY;
    handleLayoutChanged();
}

void BarChartItem::handleGeometryChanged(const QRectF &rect)
{
    prepareGeometryChange();
    m_rect = rect;
    handleLayoutChanged();
}

void BarChartItem::handleLayoutChanged()
{
    if ((m_rect.width() <= 0) || (m_rect.height() <= 0)) {
        // rect size zero.
        return;
    }
    QVector<QRectF> layout = calculateLayout();
    applyLayout(layout);
}



void BarChartItem::handleLabelsVisibleChanged(bool visible)
{
    foreach (QGraphicsSimpleTextItem* label, m_labels) {
        label->setVisible(visible);
    }
    update();
}

void BarChartItem::handleDataStructureChanged()
{
    foreach(QGraphicsItem *item, childItems()) {
        delete item;
    }

    m_bars.clear();
    m_labels.clear();
    m_layout.clear();

    bool labelsVisible = m_series->isLabelsVisible();

    // Create new graphic items for bars
    for (int c = 0; c < m_series->d_func()->categoryCount(); c++) {
        for (int s = 0; s < m_series->count(); s++) {
            QBarSet *set = m_series->d_func()->barsetAt(s);

            // Bars
            Bar *bar = new Bar(set,c,this);
            m_bars.append(bar);
            connect(bar, SIGNAL(clicked(int, QBarSet*)), m_series, SIGNAL(clicked(int, QBarSet*)));
            connect(bar, SIGNAL(hovered(bool, QBarSet*)), m_series, SIGNAL(hovered(bool, QBarSet*)));
            connect(bar, SIGNAL(clicked(int, QBarSet*)), set, SIGNAL(clicked(int)));
            connect(bar, SIGNAL(hovered(bool, QBarSet*)), set, SIGNAL(hovered(bool)));
            m_layout.append(QRectF(0, 0, 0, 0));

            // Labels
            QGraphicsSimpleTextItem *label = new QGraphicsSimpleTextItem(this);
            label->setVisible(labelsVisible);
            m_labels.append(label);
        }
    }

    // TODO: Is this the right place to call it?
    presenter()->chartTheme()->decorate(m_series, presenter()->dataSet()->seriesIndex(m_series));
    handleLayoutChanged();
}

void BarChartItem::handleVisibleChanged()
{
    bool visible = m_series->isVisible();
    handleLabelsVisibleChanged(visible);
    foreach(QGraphicsItem *item, childItems()) {
        item->setVisible(visible);
    }
}

#include "moc_barchartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
