#include <limits.h>
#include <QDebug>
#include "qpercentbarchartseries.h"
#include "qbarset.h"
#include "qbarcategory.h"
#include "barchartmodel_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

QPercentBarChartSeries::QPercentBarChartSeries(QBarCategory *category, QObject *parent)
    : QChartSeries(parent)
    ,mModel(new BarChartModel(category, this))
{
}

void QPercentBarChartSeries::addBarSet(QBarSet *set)
{
    mModel->addBarSet(set);
}

void QPercentBarChartSeries::removeBarSet(QBarSet *set)
{
    mModel->removeBarSet(set);
}

int QPercentBarChartSeries::countSets()
{
    return mModel->countSets();
}

QBarSet* QPercentBarChartSeries::nextSet(bool getFirst)
{
    return mModel->nextSet(getFirst);
}

int QPercentBarChartSeries::countCategories()
{
    return mModel->countCategories();
}

qreal QPercentBarChartSeries::min()
{
    return mModel->min();
}

qreal QPercentBarChartSeries::max()
{
    return mModel->max();
}

qreal QPercentBarChartSeries::valueAt(int set, int category)
{
    return mModel->valueAt(set,category);
}

qreal QPercentBarChartSeries::maxCategorySum()
{
    return mModel->maxCategorySum();
}

BarChartModel& QPercentBarChartSeries::model()
{
    return *mModel;
}


#include "moc_qpercentbarchartseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE

