/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#include <QtCharts/QAreaLegendMarker>
#include <private/qarealegendmarker_p.h>
#include <private/qareaseries_p.h>
#include <QtCharts/QAreaSeries>

QT_CHARTS_BEGIN_NAMESPACE

/*!
    \class QAreaLegendMarker
    \inmodule Qt Charts
    \brief QLegendMarker subclass for area series.

    QAreaLegendMarker is related to QAreaSeries. One QAreaSeries results in one marker.

    \sa QLegend, QAreaSeries
*/

/*!
  \fn virtual LegendMarkerType QAreaLegendMarker::type()
  Returns QLegendMarker::LegendMarkerTypeArea
*/

/*!
  \internal
*/
QAreaLegendMarker::QAreaLegendMarker(QAreaSeries *series, QLegend *legend, QObject *parent) :
    QLegendMarker(*new QAreaLegendMarkerPrivate(this,series,legend), parent)
{
    d_ptr->updated();
}

/*!
  Destructor
*/
QAreaLegendMarker::~QAreaLegendMarker()
{
}

/*!
    \internal
*/
QAreaLegendMarker::QAreaLegendMarker(QAreaLegendMarkerPrivate &d, QObject *parent) :
    QLegendMarker(d, parent)
{
}

/*!
  Returns related series of marker
*/
QAreaSeries* QAreaLegendMarker::series()
{
    Q_D(QAreaLegendMarker);
    return d->m_series;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QAreaLegendMarkerPrivate::QAreaLegendMarkerPrivate(QAreaLegendMarker *q, QAreaSeries *series, QLegend *legend) :
    QLegendMarkerPrivate(q,legend),
    q_ptr(q),
    m_series(series)
{
    QObject::connect(m_series->d_func(),SIGNAL(updated()), this, SLOT(updated()));
    QObject::connect(m_series, SIGNAL(nameChanged()), this, SLOT(updated()));
}

QAreaLegendMarkerPrivate::~QAreaLegendMarkerPrivate()
{
}

QAreaSeries* QAreaLegendMarkerPrivate::series()
{
    return m_series;
}

QObject* QAreaLegendMarkerPrivate::relatedObject()
{
    return m_series;
}

void QAreaLegendMarkerPrivate::updated()
{
    bool labelChanged = false;
    bool brushChanged = false;

    if (!m_customBrush && (m_item->brush() != m_series->brush())) {
        m_item->setBrush(m_series->brush());
        brushChanged = true;
    }
    if (!m_customLabel && (m_item->label() != m_series->name())) {
        m_item->setLabel(m_series->name());
        labelChanged = true;
    }
    invalidateLegend();

    if (labelChanged)
        emit q_ptr->labelChanged();
    if (brushChanged)
        emit q_ptr->brushChanged();
}

#include "moc_qarealegendmarker.cpp"
#include "moc_qarealegendmarker_p.cpp"

QT_CHARTS_END_NAMESPACE
