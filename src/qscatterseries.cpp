#include "qscatterseries.h"
#include "qscatterseries_p.h"
#include "qchart.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QScatterSeriesPrivate::QScatterSeriesPrivate() :
    m_data(QList<QPointF>())
{
}

QScatterSeries::QScatterSeries(QObject *parent) :
    QChartSeries(parent),
    d(new QScatterSeriesPrivate())
{
}

QScatterSeries::~QScatterSeries()
{
    delete d;
}

// TODO: change to list of QPointFs?
//bool QScatterSeries::setData(QList<qreal> xlist, QList<qreal> ylist)
void QScatterSeries::setData(QList<QPointF> data)
{
    d->m_data = data;
    emit changed();
}

void QScatterSeries::addData(QPointF data)
{
    d->m_data.append(data);
    emit changed();
}

QList<QPointF> QScatterSeries::data()
{
    return d->m_data;
}

void QScatterSeries::setMarkerPen(QPen pen)
{
    d->m_markerPen = pen;
}

QPen QScatterSeries::markerPen()
{
    return d->m_markerPen;
}

#include "moc_qscatterseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
