#include <limits.h>
#include <QDebug>
#include "barchartseriesbase.h"
#include "bargroup.h"
#include "barchartmodel_p.h"
#include "qbarset.h"
#include "qbarcategory.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

BarChartSeriesBase::BarChartSeriesBase(QBarCategory &category, QObject *parent)
    : QChartSeries(parent)
    ,mModel(new BarChartModel(category, this))
{
    mLabels.append(category.items());
}

void BarChartSeriesBase::addBarSet(QBarSet &set)
{
    mModel->addBarSet(set);
}

void BarChartSeriesBase::removeBarSet(QBarSet &set)
{
    mModel->removeBarSet(set);
}

qreal BarChartSeriesBase::min()
{
    return mModel->min();
}

qreal BarChartSeriesBase::max()
{
    return mModel->max();
}

int BarChartSeriesBase::countColumns()
{
    return mModel->countCategories();
}

qreal BarChartSeriesBase::valueAt(int series, int item)
{
//    qDebug() << "BarChartSeriesBase::valueAt" << series << item;
    return mModel->valueAt(series,item);
}

qreal BarChartSeriesBase::maxColumnSum()
{
//    qDebug() << "BarChartSeriesBase::maxColumnSum" << mModel->maxColumnSum();
    return mModel->maxCategorySum();
}

BarChartModel& BarChartSeriesBase::model()
{
    return *mModel;
}

QString BarChartSeriesBase::label(int item)
{
    if ((item>=0) && (item < mLabels.count()))  {
        return mLabels.at(item);
    }

    return QString("");
}

#include "moc_barchartseriesbase.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
