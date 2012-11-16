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

#include "xychart_p.h"
#include "qxyseries.h"
#include "qxyseries_p.h"
#include "chartpresenter_p.h"
#include "domain_p.h"
#include "qxymodelmapper.h"
#include <QPainter>
#include <QAbstractItemModel>


QTCOMMERCIALCHART_BEGIN_NAMESPACE

//TODO: optimize : remove points which are not visible

XYChart::XYChart(QXYSeries *series,QGraphicsItem* item):
      ChartItem(series->d_func(),item),
      m_series(series),
      m_animation(0),
      m_dirty(true)
{
    QObject::connect(series, SIGNAL(pointReplaced(int)), this, SLOT(handlePointReplaced(int)));
    QObject::connect(series, SIGNAL(pointsReplaced()), this, SLOT(handlePointsReplaced()));
    QObject::connect(series, SIGNAL(pointAdded(int)), this, SLOT(handlePointAdded(int)));
    QObject::connect(series, SIGNAL(pointRemoved(int)), this, SLOT(handlePointRemoved(int)));
    QObject::connect(this, SIGNAL(clicked(QPointF)), series, SIGNAL(clicked(QPointF)));
    QObject::connect(this, SIGNAL(hovered(QPointF,bool)), series, SIGNAL(hovered(QPointF,bool)));
}

void XYChart::setGeometryPoints(const QVector<QPointF>& points)
{
    m_points = points;
}

void XYChart::setAnimation(XYAnimation *animation)
{
    m_animation = animation;
}

void XYChart::setDirty(bool dirty)
{
    m_dirty = dirty;
}

void XYChart::updateChart(QVector<QPointF> &oldPoints, QVector<QPointF> &newPoints, int index)
{

    if (m_animation) {
        m_animation->setup(oldPoints, newPoints, index);
        m_points = newPoints;
        setDirty(false);
        presenter()->startAnimation(m_animation);
    } else {
        m_points = newPoints;
        updateGeometry();
    }
}

//handlers

void XYChart::handlePointAdded(int index)
{
    Q_ASSERT(index < m_series->count());
    Q_ASSERT(index >= 0);

    QVector<QPointF> points;

    if (m_dirty) {
        points = domain()->calculateGeometryPoints(m_series->points());
    } else {
        points = m_points;
        QPointF point = domain()->calculateGeometryPoint(m_series->points()[index]);
        points.insert(index, point);
    }

    updateChart(m_points, points, index);
}

void XYChart::handlePointRemoved(int index)
{
    Q_ASSERT(index <= m_series->count());
    Q_ASSERT(index >= 0);

    QVector<QPointF> points;

    if (m_dirty) {
        points = domain()->calculateGeometryPoints(m_series->points());
    } else {
        points = m_points;
        points.remove(index);
    }

    updateChart(m_points, points, index);
}

void XYChart::handlePointReplaced(int index)
{
    Q_ASSERT(index < m_series->count());
    Q_ASSERT(index >= 0);

    QVector<QPointF> points;

    if (m_dirty) {
        points = domain()->calculateGeometryPoints(m_series->points());
    } else {
        QPointF point = domain()->calculateGeometryPoint(m_series->points()[index]);
        points = m_points;
        points.replace(index, point);
    }

    updateChart(m_points, points, index);
}

void XYChart::handlePointsReplaced()
{
    // All the points were replaced -> recalculate
    QVector<QPointF> points =  domain()->calculateGeometryPoints(m_series->points());
    updateChart(m_points, points, -1);
}

void XYChart::handleDomainUpdated()
{
    if (isEmpty()) return;
    QVector<QPointF> points =  domain()->calculateGeometryPoints(m_series->points());
    updateChart(m_points, points);
}

bool XYChart::isEmpty()
{
    return domain()->isEmpty() || m_series->points().isEmpty();
}

#include "moc_xychart_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
