#ifndef STACKEDBARCHARTSERIES_H
#define STACKEDBARCHARTSERIES_H

#include <QList>
#include <QAbstractItemModel>
#include "qbarchartseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QBarCategory;
class QBarSet;
class BarChartModel;

//class QTCOMMERCIALCHART_EXPORT QStackedBarChartSeries : public QChartSeries
class QTCOMMERCIALCHART_EXPORT QStackedBarChartSeries : public QBarChartSeries
{
    Q_OBJECT
public:
    QStackedBarChartSeries(QBarCategory *category, QObject* parent=0);

    // from QChartSeries
    virtual QChartSeriesType type() const { return QChartSeries::SeriesTypeStackedBar; }
/*
    // Set handling
    void addBarSet(QBarSet *set);       // Takes ownership
    void removeBarSet(QBarSet *set);    // Releases ownership, doesn't delete set
    int countSets();
    QBarSet* nextSet(bool first=false);     // Returns first set, if called with true

    QList<QString> legend();  // Returns legend of series (ie. names of all sets in series)

    // Disabled by default. Call these to change behavior.
    void enableFloatingValues(bool enabled=true);
    void enableHoverNames(bool enabled=true);

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
    BarChartModel* mModel;
*/
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // STACKEDBARCHARTSERIES_H
