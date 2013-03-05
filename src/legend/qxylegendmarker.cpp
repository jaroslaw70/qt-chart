/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

#include "qxylegendmarker.h"
#include "qxylegendmarker_p.h"
#include "qxyseries_p.h"
#include <QXYSeries>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QXYLegendMarker
    \brief QXYLegendMarker object
    \mainclass

    QXYLegendMarker is related to QXYSeries derived classes. Each marker is related to one series.

    \sa QLegend QXYSeries QSplineSeries QScatterSeries QLineSeries
*/

/*!
  \fn virtual LegendMarkerType QXYLegendMarker::type()
  Returns QLegendMarker::LegendMarkerTypeXY
*/

/*!
  \internal
*/
QXYLegendMarker::QXYLegendMarker(QXYSeries *series, QLegend *legend, QObject *parent) :
    QLegendMarker(*new QXYLegendMarkerPrivate(this,series,legend), parent)
{
    d_ptr->updated();
}

/*!
  Destructor
*/
QXYLegendMarker::~QXYLegendMarker()
{
}

/*!
    \internal
*/
QXYLegendMarker::QXYLegendMarker(QXYLegendMarkerPrivate &d, QObject *parent) :
    QLegendMarker(d, parent)
{
}

/*!
  Returns the related series
*/
QXYSeries* QXYLegendMarker::series()
{
    Q_D(QXYLegendMarker);
    return d->m_series;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QXYLegendMarkerPrivate::QXYLegendMarkerPrivate(QXYLegendMarker *q, QXYSeries *series, QLegend *legend) :
    QLegendMarkerPrivate(q,legend),
    q_ptr(q),
    m_series(series)
{
    QObject::connect(m_series, SIGNAL(nameChanged()), this, SLOT(updated()));
    QObject::connect(m_series->d_func(), SIGNAL(updated()), this, SLOT(updated()));
}

QXYLegendMarkerPrivate::~QXYLegendMarkerPrivate()
{
}

QAbstractSeries* QXYLegendMarkerPrivate::series()
{
    return m_series;
}

QObject* QXYLegendMarkerPrivate::relatedObject()
{
    return m_series;
}

void QXYLegendMarkerPrivate::updated()
{
    bool labelChanged = false;
    bool brushChanged = false;

    if (!m_customLabel && (m_item->label() != m_series->name())) {
        m_item->setLabel(m_series->name());
        labelChanged = true;
    }

    if (m_series->type()== QAbstractSeries::SeriesTypeScatter)  {
        if (!m_customBrush && (m_item->brush() != m_series->brush())) {
            m_item->setBrush(m_series->brush());
            brushChanged = true;
        }
    } else {
        if (!m_customBrush && (m_item->brush().color() != m_series->pen().color())) {
            m_item->setBrush(QBrush(m_series->pen().color()));
            brushChanged = true;
        }
    }
    invalidateLegend();

    if (labelChanged)
        emit q_ptr->labelChanged();
    if (brushChanged)
        emit q_ptr->brushChanged();
}

#include "moc_qxylegendmarker.cpp"
#include "moc_qxylegendmarker_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

