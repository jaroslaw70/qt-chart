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

#include "chartdataset_p.h"
#include "qchartaxis.h"
//series
#include "qlineseries.h"
#include "qareaseries.h"
#include "qbarseries.h"
#include "qstackedbarseries.h"
#include "qpercentbarseries.h"
#include "qpieseries.h"
#include "qscatterseries.h"
#include "qsplineseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartDataSet::ChartDataSet(QObject *parent):QObject(parent),
    m_axisX(new QChartAxis(this)),
    m_axisY(new QChartAxis(this)),
    m_domainIndex(0),
    m_axisXInitialized(false)
{
}

ChartDataSet::~ChartDataSet()
{
}

void ChartDataSet::addSeries(QSeries* series, QChartAxis *axisY)
{
    if(axisY==0) axisY = m_axisY;

    QChartAxis* axis = m_seriesAxisMap.value(series);

    if(axis) {
        qWarning() << "Can not add series. Series already on the chart";
        return;
    }

    if(!series->parent()){
       series->setParent(this); // take ownership
    };

    if(!axisY->parent()){
       axisY->setParent(this); // take ownership
    }

    Domain* domain = m_axisDomainMap.value(axisY);

    if(!domain) {
        domain = new Domain(axisY);
        QObject::connect(axisY,SIGNAL(changed(qreal,qreal,int,bool)),domain,SLOT(handleAxisYChanged(qreal,qreal,int,bool)));
        QObject::connect(axisX(),SIGNAL(changed(qreal,qreal,int,bool)),domain,SLOT(handleAxisXChanged(qreal,qreal,int,bool)));
        QObject::connect(domain,SIGNAL(rangeYChanged(qreal,qreal,int)),axisY,SLOT(handleAxisRangeChanged(qreal,qreal,int)));
        QObject::connect(domain,SIGNAL(rangeXChanged(qreal,qreal,int)),axisX(),SLOT(handleAxisRangeChanged(qreal,qreal,int)));
        //initialize
        m_axisDomainMap.insert(axisY,domain);
        emit axisAdded(axisY,domain);
    }

    if(!m_axisXInitialized){
       emit axisAdded(axisX(),domain);
       m_axisXInitialized=true;
    }

    calculateDomain(series,domain);

    m_seriesAxisMap.insert(series,axisY);

    QMapIterator<int, QSeries*> i(m_indexSeriesMap);

    int key=0;
    while (i.hasNext()) {
        i.next();
        if(i.key()!=key) {
            break;
        }
        key++;
    }

    m_indexSeriesMap.insert(key,series);

    emit seriesAdded(series,domain);

}

void ChartDataSet::removeSeries(QSeries* series)
{

    QChartAxis* axis = m_seriesAxisMap.value(series);

    if(!axis){
        qWarning()<<"Can not remove series. Series not found on the chart.";
        return;
    }
    emit seriesRemoved(series);
    m_seriesAxisMap.remove(series);
    int key = seriesIndex(series);
    Q_ASSERT(key!=-1);

    m_indexSeriesMap.remove(key);

    if(series->parent()==this){
        delete series;
        series=0;
    }

    QList<QChartAxis*> axes =  m_seriesAxisMap.values();

    int i = axes.indexOf(axis);

    if(i==-1){
        Domain* domain = m_axisDomainMap.take(axis);
        emit axisRemoved(axis);
        if(axis!=axisY()){
            if(axis->parent()==this){
                delete axis;
                axis=0;
            }
        }
        delete domain;
    }

    if(m_seriesAxisMap.values().size()==0)
    {
        m_axisXInitialized=false;
        emit axisRemoved(axisX());
    }
}

void ChartDataSet::removeAllSeries()
{

    QList<QSeries*> series =  m_seriesAxisMap.keys();

    foreach(QSeries* s , series) {
        removeSeries(s);
    }

    Q_ASSERT(m_seriesAxisMap.count()==0);
    Q_ASSERT(m_axisDomainMap.count()==0);

}

//to be removed with PIMPL
void ChartDataSet::calculateDomain(QSeries* series,Domain* domain)
{
    qreal minX(domain->minX());
    qreal minY(domain->minY());
    qreal maxX(domain->maxX());
    qreal maxY(domain->maxY());
    int tickXCount(domain->tickXCount());
    int tickYCount(domain->tickYCount());


    switch(series->type())
    {
        case QSeries::SeriesTypeLine:
        case QSeries::SeriesTypeSpline:
        case QSeries::SeriesTypeScatter:
        {

            QXYSeries* xySeries = static_cast<QXYSeries*>(series);

            for (int i = 0; i < xySeries->count(); i++)
            {
                qreal x = xySeries->x(i);
                qreal y = xySeries->y(i);
                minX = qMin(minX, x);
                minY = qMin(minY, y);
                maxX = qMax(maxX, x);
                maxY = qMax(maxY, y);
            }
            break;
        }
        case QSeries::SeriesTypeArea: {

            QAreaSeries* areaSeries = static_cast<QAreaSeries*>(series);
            QLineSeries* upperSeries = areaSeries->upperSeries();
            QLineSeries* lowerSeries = areaSeries->lowerSeries();

            for (int i = 0; i < upperSeries->count(); i++)
            {
                qreal x = upperSeries->x(i);
                qreal y = upperSeries->y(i);
                minX = qMin(minX, x);
                minY = qMin(minY, y);
                maxX = qMax(maxX, x);
                maxY = qMax(maxY, y);
            }
            if(lowerSeries) {
                for (int i = 0; i < lowerSeries->count(); i++)
                {
                    qreal x = lowerSeries->x(i);
                    qreal y = lowerSeries->y(i);
                    minX = qMin(minX, x);
                    minY = qMin(minY, y);
                    maxX = qMax(maxX, x);
                    maxY = qMax(maxY, y);
                }}
            break;
        }
        case QSeries::SeriesTypeBar: {

            QBarSeries* barSeries = static_cast<QBarSeries*>(series);
            qreal x = barSeries->categoryCount();
            qreal y = barSeries->max();
            minX = qMin(minX, x);
            minY = qMin(minY, y);
            maxX = qMax(maxX, x);
            maxY = qMax(maxY, y);
            tickXCount = x+1;
            setupCategories(barSeries);
            break;
        }
        case QSeries::SeriesTypeStackedBar: {

            QStackedBarSeries* stackedBarSeries = static_cast<QStackedBarSeries*>(series);
            qreal x = stackedBarSeries->categoryCount();
            qreal y = stackedBarSeries->maxCategorySum();
            minX = qMin(minX, x);
            minY = qMin(minY, y);
            maxX = qMax(maxX, x);
            maxY = qMax(maxY, y);
            tickXCount = x+1;
            setupCategories(stackedBarSeries);
            break;
        }
        case QSeries::SeriesTypePercentBar: {

            QPercentBarSeries* percentBarSeries = static_cast<QPercentBarSeries*>(series);
            qreal x = percentBarSeries->categoryCount();
            minX = qMin(minX, x);
            maxX = qMax(maxX, x);
            minY = 0;
            maxY = 100;
            tickXCount = x+1;
            setupCategories(percentBarSeries);
            break;
        }

        case QSeries::SeriesTypePie: {
            //QPieSeries *pieSeries = static_cast<QPieSeries *>(series);
            // TODO: domain stuff
            break;
        }


        default: {
            qDebug()<<__FUNCTION__<<"type" << series->type()<<"not supported";
            return;
        }

    }

    domain->setRangeX(minX,maxX,tickXCount);
    domain->setRangeY(minY,maxY,tickYCount);
}


void ChartDataSet::setupCategories(QBarSeries* series)
{
   QChartAxisCategories* categories = axisX()->categories();
   categories->clear();
   categories->insert(series->categories());
}

void ChartDataSet::zoomInDomain(const QRectF& rect, const QSizeF& size)
{
    QMapIterator<QChartAxis*, Domain*> i(m_axisDomainMap);
    while (i.hasNext()) {
        i.next();
        i.value()->zoomIn(rect,size);
    }
}

void ChartDataSet::zoomOutDomain(const QRectF& rect, const QSizeF& size)
{
    QMapIterator<QChartAxis*, Domain*> i(m_axisDomainMap);
    while (i.hasNext()) {
        i.next();
        i.value()->zoomOut(rect,size);
    }
}

int ChartDataSet::seriesCount(QSeries::QSeriesType type)
{
    int count=0;
    QMapIterator<QSeries*, QChartAxis*> i(m_seriesAxisMap);
    while (i.hasNext()) {
           i.next();
           if(i.key()->type()==type) count++;
    }
    return count;
}

int ChartDataSet::seriesIndex(QSeries *series)
{
    QMapIterator<int, QSeries*> i(m_indexSeriesMap);
    while (i.hasNext()) {
        i.next();
        if (i.value() == series)
            return i.key();
    }
    return -1;
}

QChartAxis* ChartDataSet::axisY(QSeries* series) const
{
    if(series == 0) return m_axisY;
    return m_seriesAxisMap.value(series);
}

Domain* ChartDataSet::domain(QSeries* series) const
{
	QChartAxis* axis = m_seriesAxisMap.value(series);
	if(axis){
		return m_axisDomainMap.value(axis);
	}else
		return 0;
}

Domain* ChartDataSet::domain(QChartAxis* axis) const
{
    if(!axis || axis==axisX()) {
        return  m_axisDomainMap.value(axisY());
    }
    else {
        return m_axisDomainMap.value(axis);
    }
}

void ChartDataSet::scrollDomain(int dx,int dy,const QSizeF& size)
{
	 QMapIterator<QChartAxis*, Domain*> i( m_axisDomainMap);
	 	while (i.hasNext()) {
	        i.next();
	        i.value()->move(dx,dy,size);
	    }
}

#include "moc_chartdataset_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
