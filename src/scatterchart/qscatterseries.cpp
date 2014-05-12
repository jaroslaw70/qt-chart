/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qscatterseries.h"
#include "qscatterseries_p.h"
#include "scatterchartitem_p.h"
#include "chartdataset_p.h"
#include "charttheme_p.h"
#include "scatteranimation_p.h"
#include "qchart_p.h"

/*!
    \class QScatterSeries
    \inmodule Qt Charts
    \brief The QScatterSeries class is used for making scatter charts.

    \mainclass

    The scatter data is displayed as a collection of points on the chart. Each point determines the position on the horizontal axis
    and the vertical axis.

    \image examples_scatterchart.png

    Creating basic scatter chart is simple:
    \code
    QScatterSeries* series = new QScatterSeries();
    series->append(0, 6);
    series->append(2, 4);
    ...
    chart->addSeries(series);
    \endcode
*/
#ifdef QDOC_QT5
/*!
    \qmltype ScatterSeries
    \instantiates QScatterSeries
    \inqmlmodule QtCommercial.Chart

    \include doc/src/scatterseries.qdocinc
*/
#else
/*!
    \qmlclass ScatterSeries QScatterSeries

    \include ../doc/src/scatterseries.qdocinc
*/
#endif

/*!
    \enum QScatterSeries::MarkerShape

    This enum describes the shape used when rendering marker items.

    \value MarkerShapeCircle
    \value MarkerShapeRectangle
*/

/*!
    \property QScatterSeries::brush
    Brush used to draw the series.
*/

/*!
    \property QScatterSeries::color
    Fill (brush) color of the series. This is a convenience property for modifying the color of brush.
    \sa QScatterSeries::brush()
*/

/*!
    \property QScatterSeries::borderColor
    Line (pen) color of the series. This is a convenience property for modifying the color of pen.
    \sa QScatterSeries::pen()
*/
/*!
    \qmlproperty color ScatterSeries::borderColor
    Border (pen) color of the series.
*/

/*!
    \qmlproperty real ScatterSeries::borderWidth
    The width of the border line. By default the width is 2.0.
*/

/*!
    \property QScatterSeries::markerShape
    Defines the shape of the marker used to draw the points in the series. The default shape is MarkerShapeCircle.
*/
/*!
    \qmlproperty MarkerShape ScatterSeries::markerShape
    Defines the shape of the marker used to draw the points in the series. One of ScatterSeries
    ScatterSeries.MarkerShapeCircle or ScatterSeries.MarkerShapeRectangle.
    The default shape is ScatterSeries.MarkerShapeCircle.
*/

/*!
    \property QScatterSeries::markerSize
    Defines the size of the marker used to draw the points in the series. The default size is 15.0.
*/
/*!
    \qmlproperty real ScatterSeries::markerSize
    Defines the size of the marker used to draw the points in the series. The default size is 15.0.
*/

/*!
    \qmlproperty QString ScatterSeries::brushFilename
    The name of the file used as a brush for the series.
*/

/*!
    \fn void QScatterSeries::colorChanged(QColor color)
    Signal is emitted when the fill (brush) color has changed to \a color.
*/

/*!
    \fn void QScatterSeries::borderColorChanged(QColor color)
    Signal is emitted when the line (pen) color has changed to \a color.
*/
/*!
    \qmlsignal ScatterSeries::borderColorChanged(color color)
    Signal is emitted when the line (pen) color has changed to \a color.
*/

/*!
    \fn QAbstractSeries::SeriesType QScatterSeries::type() const
    Returns QAbstractSeries::SeriesTypeScatter.
    \sa QAbstractSeries, SeriesType
*/

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    Constructs a series object which is a child of \a parent.
*/
QScatterSeries::QScatterSeries(QObject *parent)
    : QXYSeries(*new QScatterSeriesPrivate(this), parent)
{
}

/*!
    Destroys the object. Note that adding series to QChart transfers the ownership to the chart.
*/
QScatterSeries::~QScatterSeries()
{
    Q_D(QScatterSeries);
    if (d->m_chart)
        d->m_chart->removeSeries(this);
}

QAbstractSeries::SeriesType QScatterSeries::type() const
{
    return QAbstractSeries::SeriesTypeScatter;
}

/*!
    Sets \a pen used for drawing points' border on the chart. If the pen is not defined, the
    pen from chart theme is used.
    \sa QChart::setTheme()
*/
void QScatterSeries::setPen(const QPen &pen)
{
    Q_D(QXYSeries);
    if (d->m_pen != pen) {
        bool emitColorChanged = d->m_pen.color() != pen.color();
        d->m_pen = pen;
        emit d->updated();
        if (emitColorChanged)
            emit borderColorChanged(pen.color());
    }
}

/*!
    Sets \a brush used for drawing points on the chart. If the brush is not defined, brush
    from chart theme setting is used.
    \sa QChart::setTheme()
*/
void QScatterSeries::setBrush(const QBrush &brush)
{
    Q_D(QScatterSeries);
    if (d->m_brush != brush) {
        bool emitColorChanged = d->m_brush.color() != brush.color();
        d->m_brush = brush;
        emit d->updated();
        if (emitColorChanged)
            emit colorChanged(brush.color());
    }
}

QBrush QScatterSeries::brush() const
{
    Q_D(const QScatterSeries);
    if (d->m_brush == QChartPrivate::defaultBrush())
        return QBrush();
    else
        return d->m_brush;
}

void QScatterSeries::setColor(const QColor &color)
{
    QBrush b = brush();
    if (b == QChartPrivate::defaultBrush())
        b = QBrush();
    if (b == QBrush())
        b.setStyle(Qt::SolidPattern);
    b.setColor(color);
    setBrush(b);
}

QColor QScatterSeries::color() const
{
    return brush().color();
}

void QScatterSeries::setBorderColor(const QColor &color)
{
    QPen p = pen();
    if (p == QChartPrivate::defaultPen())
        p = QPen();
    p.setColor(color);
    setPen(p);
}

QColor QScatterSeries::borderColor() const
{
    return pen().color();
}

QScatterSeries::MarkerShape QScatterSeries::markerShape() const
{
    Q_D(const QScatterSeries);
    return d->m_shape;
}

void QScatterSeries::setMarkerShape(MarkerShape shape)
{
    Q_D(QScatterSeries);
    if (d->m_shape != shape) {
        d->m_shape = shape;
        emit d->updated();
    }
}

qreal QScatterSeries::markerSize() const
{
    Q_D(const QScatterSeries);
    return d->m_size;
}

void QScatterSeries::setMarkerSize(qreal size)
{
    Q_D(QScatterSeries);

    if (!qFuzzyCompare(d->m_size, size)) {
        d->m_size = size;
        emit d->updated();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QScatterSeriesPrivate::QScatterSeriesPrivate(QScatterSeries *q)
    : QXYSeriesPrivate(q),
      m_shape(QScatterSeries::MarkerShapeCircle),
      m_size(15.0)
{
}

void QScatterSeriesPrivate::initializeGraphics(QGraphicsItem* parent)
{
    Q_Q(QScatterSeries);
    ScatterChartItem *scatter = new ScatterChartItem(q,parent);
    m_item.reset(scatter);
    QAbstractSeriesPrivate::initializeGraphics(parent);
}

void QScatterSeriesPrivate::initializeTheme(int index, ChartTheme* theme, bool forced)
{
    Q_Q(QScatterSeries);
    const QList<QColor> colors = theme->seriesColors();
    const QList<QGradient> gradients = theme->seriesGradients();

    if (forced || QChartPrivate::defaultPen() == m_pen) {
        QPen pen;
        pen.setColor(ChartThemeManager::colorAt(gradients.at(index % gradients.size()), 0.0));
        pen.setWidthF(2);
        q->setPen(pen);
    }

    if (forced || QChartPrivate::defaultBrush() == m_brush) {
        QBrush brush(colors.at(index % colors.size()));
        q->setBrush(brush);
    }
}

void QScatterSeriesPrivate::initializeAnimations(QChart::AnimationOptions options)
{
    ScatterChartItem *item = static_cast<ScatterChartItem *>(m_item.data());
    Q_ASSERT(item);

    if (item->animation())
        item->animation()->stopAndDestroyLater();

    if (options.testFlag(QChart::SeriesAnimations))
        item->setAnimation(new ScatterAnimation(item));
    else
        item->setAnimation(0);

    QAbstractSeriesPrivate::initializeAnimations(options);
}

#include "moc_qscatterseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
