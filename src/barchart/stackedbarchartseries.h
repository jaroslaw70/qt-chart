#ifndef STACKEDBARCHARTSERIES_H
#define STACKEDBARCHARTSERIES_H

#include <QList>
#include <QAbstractItemModel>
#include "qchartseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class StackedBarGroup;
class QBarCategory;
class QBarSet;
class BarChartModel;

class QTCOMMERCIALCHART_EXPORT StackedBarChartSeries : public QChartSeries
{
    Q_OBJECT
public:
    StackedBarChartSeries(QBarCategory *category, QObject* parent=0);

    // from QChartSeries
    virtual QChartSeriesType type() const { return QChartSeries::SeriesTypeStackedBar; }

    void addBarSet(QBarSet *set);       // Takes ownership
    void removeBarSet(QBarSet *set);    // Also deletes the set, if set is owned.
    int countSets();
    QBarSet* nextSet(bool first=false);     // Returns first set, if called with true

    //TODO:
    //QList<QString> legend();  // Returns legend of series (ie. names of all sets in series)

    // TODO: Functions below this are not part of api and will be moved
    // to private implementation, when we start using it (not part of api)
    int countCategories();
    qreal min();
    qreal max();
    qreal valueAt(int set, int category);
    qreal maxCategorySum();

    BarChartModel& model();

signals:
    void changed(int index);

public Q_SLOTS:

private:

    StackedBarGroup* mStackedBarGroup;
    BarChartModel* mModel;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // STACKEDBARCHARTSERIES_H
