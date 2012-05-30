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

#include "qbarseries.h"
#include "qbarseries_p.h"
#include "qbarset.h"
#include "qbarset_p.h"
#include "domain_p.h"
#include "legendmarker_p.h"
#include "chartdataset_p.h"
#include "charttheme_p.h"
#include "chartanimator_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QBarSeries
    \brief part of QtCommercial chart API.
    \mainclass

    QBarSeries represents a series of data shown as bars. The purpose of this class is to draw bars to
    the position defined by data. Single bar is defined by QPointF, where x value is the x-coordinate of the bar
    and y-value is the height of the bar. The category names are ignored with this series and x-axis
    shows the x-values.

    See the \l {BarChart Example} {bar chart example} to learn how to create a simple bar chart.
    \image examples_barchart.png

    \sa QBarSet, QStackedBarSeries, QPercentBarSeries
*/

/*!
    \fn void QBarSeries::clicked(QBarSet *barset, QString category)

    The signal is emitted if the user clicks with a mouse on top of QBarSet \a barset of category \a category
    contained by the series.
*/

/*!
    \fn void QBarSeries::hovered(QBarSet* barset, bool status)

    The signal is emitted if mouse is hovered on top of series.
    Parameter \a barset is the pointer of barset, where hover happened.
    Parameter \a status is true, if mouse entered on top of series, false if mouse left from top of series.
*/

/*!
    Constructs empty QBarSeries.
    QBarSeries is QObject which is a child of a \a parent.
*/
QBarSeries::QBarSeries(QObject *parent) :
    QAbstractSeries(*new QBarSeriesPrivate(this),parent)
{
}

/*!
    Destructs barseries and owned barsets.
*/
QBarSeries::~QBarSeries()
{
    Q_D(QBarSeries);
    if(d->m_dataset){
        d->m_dataset->removeSeries(this);
    }
}

/*!
    \internal
*/
QBarSeries::QBarSeries(QBarSeriesPrivate &d, QObject *parent) :
    QAbstractSeries(d,parent)
{
}

/*!
    Returns the type of series. Derived classes override this.
*/
QAbstractSeries::SeriesType QBarSeries::type() const
{
    return QAbstractSeries::SeriesTypeBar;
}

/*!
    Sets the \a categories, which are used to to group the data.
*/
void QBarSeries::setCategories(QBarCategories categories)
{
    Q_D(QBarSeries);
    d->setCategories(categories);
    emit d->categoriesUpdated();
}

void QBarSeries::setBarMargin(qreal margin)
{
    Q_D(QBarSeries);
    d->setBarMargin(margin);
}

qreal QBarSeries::barMargin() const
{
    Q_D(const QBarSeries);
    return d->barMargin();
}

/*!
    Adds a set of bars to series. Takes ownership of \a set. If the set is null or is already in series, it won't be appended.
    Returns true, if appending succeeded.

*/
bool QBarSeries::append(QBarSet *set)
{
    Q_D(QBarSeries);
    return d->append(set);
}

/*!
    Removes a set of bars from series. Releases ownership of \a set. Doesn't delete \a set.
    Returns true, if set was removed.
*/
bool QBarSeries::remove(QBarSet *set)
{
    Q_D(QBarSeries);
    return d->remove(set);
}

/*!
    Adds a list of barsets to series. Takes ownership of \a sets.
    Returns true, if all sets were appended succesfully. If any of the sets is null or is already appended to series,
    nothing is appended and function returns false. If any of the sets is in list more than once, nothing is appended
    and function returns false.
*/
bool QBarSeries::append(QList<QBarSet* > sets)
{
    Q_D(QBarSeries);
    return d->append(sets);
}

/*!
    Removes a list of barsets from series. Releases ownership of \a sets. Doesn't delete \a sets.
*/
bool QBarSeries::remove(QList<QBarSet* > sets)
{
    Q_D(QBarSeries);
    return d->remove(sets);
}

void QBarSeries::clear()
{
    Q_D(QBarSeries);
    d->m_barSets.clear();
    d->m_categories.clear();
}

/*!
    Returns number of sets in series.
*/
int QBarSeries::barsetCount() const
{
    Q_D(const QBarSeries);
    return d->m_barSets.count();
}

/*!
    Returns number of categories in series
*/
int QBarSeries::categoryCount() const
{
    Q_D(const QBarSeries);
    return d->categoryCount();
}

/*!
    Returns a list of sets in series. Keeps ownership of sets.
 */
QList<QBarSet*> QBarSeries::barSets() const
{
    Q_D(const QBarSeries);
    return d->m_barSets;
}

/*!
    Returns the bar categories of the series.
*/
QBarCategories QBarSeries::categories() const
{
    Q_D(const QBarSeries);
    return d->categories();
}

void QBarSeries::setVisible(bool visible)
{
    Q_D(QBarSeries);
    d->setVisible(visible);
}

bool QBarSeries::isVisible() const
{
    Q_D(const QBarSeries);
    return d->isVisible();
}

/*!
    Sets the visibility of labels in series to \a visible
*/
void QBarSeries::setLabelsVisible(bool visible)
{
    Q_D(QBarSeries);
    if (d->m_labelsVisible != visible) {
        d->m_labelsVisible = visible;
        emit d->updatedBars();
    }
}

bool QBarSeries::isLabelsVisible() const
{
    Q_D(const QBarSeries);
    return d->m_labelsVisible;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QBarSeriesPrivate::QBarSeriesPrivate(QBarSeries *q) :
    QAbstractSeriesPrivate(q),
    m_barMargin(0.5),  // Default value is 50% of category width
    m_labelsVisible(false),
    m_visible(true)
{
}

void QBarSeriesPrivate::setCategories(QBarCategories categories)
{
    m_categories = categories;
}

void QBarSeriesPrivate::insertCategory(int index, const QString category)
{
    m_categories.insert(index, category);
    emit categoriesUpdated();
}

void QBarSeriesPrivate::removeCategory(int index)
{
    m_categories.removeAt(index);
    emit categoriesUpdated();
}

int QBarSeriesPrivate::categoryCount() const
{
    if (m_categories.count() > 0) {
        return m_categories.count();
    }

    // No categories defined. return count of longest set.
    int count = 0;
    for (int i=0; i<m_barSets.count(); i++) {
        if (m_barSets.at(i)->count() > count) {
            count = m_barSets.at(i)->count();
        }
    }

    return count;
}

QBarCategories QBarSeriesPrivate::categories() const
{
    if (m_categories.count() > 0) {
        return m_categories;
    }

    // No categories defined. retun list of indices.
    QBarCategories categories;

    int count = categoryCount();
    for (int i = 0; i < count; i++) {
        categories.append(QString::number(i));
    }
    return categories;
}

void QBarSeriesPrivate::setBarMargin(qreal margin)
{
    if (margin > 1.0) {
        margin = 1.0;
    } else if (margin < 0.0) {
        margin = 0.0;
    }

    m_barMargin = margin;
    emit updatedBars();
}

qreal QBarSeriesPrivate::barMargin() const
{
    return m_barMargin;
}

QBarSet* QBarSeriesPrivate::barsetAt(int index)
{
    return m_barSets.at(index);
}

void QBarSeriesPrivate::setVisible(bool visible)
{
    if (m_visible != visible) {
        m_visible = visible;
        emit updatedBars();
    }
}

bool QBarSeriesPrivate::isVisible() const
{
    return m_visible;
}

QString QBarSeriesPrivate::categoryName(int category)
{
    if ((category >= 0) && (category < m_categories.count())) {
        return m_categories.at(category);
    }

    return QString::number(category);
}

qreal QBarSeriesPrivate::min()
{
    if (m_barSets.count() <= 0) {
        return 0;
    }
    qreal min = INT_MAX;

    for (int i = 0; i < m_barSets.count(); i++) {
        int categoryCount = m_barSets.at(i)->count();
        for (int j = 0; j < categoryCount; j++) {
            qreal temp = m_barSets.at(i)->at(j).y();
            if (temp < min)
                min = temp;
        }
    }
    return min;
}

qreal QBarSeriesPrivate::max()
{
    if (m_barSets.count() <= 0) {
        return 0;
    }
    qreal max = INT_MIN;

    for (int i = 0; i < m_barSets.count(); i++) {
        int categoryCount = m_barSets.at(i)->count();
        for (int j = 0; j < categoryCount; j++) {
            qreal temp = m_barSets.at(i)->at(j).y();
            if (temp > max)
                max = temp;
        }
    }

    return max;
}

qreal QBarSeriesPrivate::valueAt(int set, int category)
{
    if ((set < 0) || (set >= m_barSets.count())) {
        // No set, no value.
        return 0;
    } else if ((category < 0) || (category >= m_barSets.at(set)->count())) {
        // No category, no value.
        return 0;
    }

    return m_barSets.at(set)->at(category).y();
}

qreal QBarSeriesPrivate::percentageAt(int set, int category)
{
    if ((set < 0) || (set >= m_barSets.count())) {
        // No set, no value.
        return 0;
    } else if ((category < 0) || (category >= m_barSets.at(set)->count())) {
        // No category, no value.
        return 0;
    }

    qreal value = m_barSets.at(set)->at(category).y();
    qreal sum = categorySum(category);
    if ( qFuzzyIsNull(sum) ) {
        return 0;
    }

    return value / sum;
}

qreal QBarSeriesPrivate::categorySum(int category)
{
    qreal sum(0);
    int count = m_barSets.count(); // Count sets
    for (int set = 0; set < count; set++) {
        if (category < m_barSets.at(set)->count())
            sum += m_barSets.at(set)->at(category).y();
    }
    return sum;
}

qreal QBarSeriesPrivate::absoluteCategorySum(int category)
{
    qreal sum(0);
    int count = m_barSets.count(); // Count sets
    for (int set = 0; set < count; set++) {
        if (category < m_barSets.at(set)->count())
            sum += qAbs(m_barSets.at(set)->at(category).y());
    }
    return sum;
}

qreal QBarSeriesPrivate::maxCategorySum()
{
    qreal max = INT_MIN;
    int count = categoryCount();
    for (int i = 0; i < count; i++) {
        qreal sum = categorySum(i);
        if (sum > max)
            max = sum;
    }
    return max;
}

void QBarSeriesPrivate::barsetChanged()
{
    emit updatedBars();
}

void QBarSeriesPrivate::scaleDomain(Domain& domain)
{
    qreal minX(domain.minX());
    qreal minY(domain.minY());
    qreal maxX(domain.maxX());
    qreal maxY(domain.maxY());
    int tickXCount(domain.tickXCount());
    int tickYCount(domain.tickYCount());

    qreal x = categoryCount();
    qreal y = max();
    minX = qMin(minX, x) - 0.5;
    minY = qMin(minY, y);
    maxX = qMax(maxX, x) - 0.5;
    maxY = qMax(maxY, y);
    tickXCount = x+1;

    domain.setRange(minX,maxX,minY,maxY,tickXCount,tickYCount);
}

Chart* QBarSeriesPrivate::createGraphics(ChartPresenter* presenter)
{
    Q_Q(QBarSeries);

    BarChartItem* bar = new BarChartItem(q,presenter);
    if(presenter->animationOptions().testFlag(QChart::SeriesAnimations)) {
        presenter->animator()->addAnimation(bar);
    }
    presenter->chartTheme()->decorate(q, presenter->dataSet()->seriesIndex(q));
    return bar;

}

QList<LegendMarker*> QBarSeriesPrivate::createLegendMarker(QLegend* legend)
{
    Q_Q(QBarSeries);
    QList<LegendMarker*> markers;
    foreach(QBarSet* set, q->barSets()) {
        BarLegendMarker* marker = new BarLegendMarker(q,set,legend);
        markers << marker;
    }

    return markers;
}

bool QBarSeriesPrivate::append(QBarSet *set)
{
    Q_Q(QBarSeries);
    if ((m_barSets.contains(set)) || (set == 0)) {
        // Fail if set is already in list or set is null.
        return false;
    }
    m_barSets.append(set);
    QObject::connect(set->d_ptr.data(), SIGNAL(updatedBars()), this, SLOT(barsetChanged()));
    if (m_dataset) {
        m_dataset->updateSeries(q);   // this notifies legend
    }
    emit restructuredBars();      // this notifies barchartitem
    return true;
}

bool QBarSeriesPrivate::remove(QBarSet *set)
{
    Q_Q(QBarSeries);
    if (!m_barSets.contains(set)) {
        // Fail if set is not in list
        return false;
    }
    m_barSets.removeOne(set);
    QObject::disconnect(set->d_ptr.data(), SIGNAL(updatedBars()), this, SLOT(barsetChanged()));
    if (m_dataset) {
        m_dataset->updateSeries(q);   // this notifies legend
    }
    emit restructuredBars();        // this notifies barchartitem
    return true;
}

bool QBarSeriesPrivate::append(QList<QBarSet* > sets)
{
    Q_Q(QBarSeries);
    foreach (QBarSet* set, sets) {
        if ((set == 0) || (m_barSets.contains(set))) {
            // Fail if any of the sets is null or is already appended.
            return false;
        }
        if (sets.count(set) != 1) {
            // Also fail if same set is more than once in given list.
            return false;
        }
    }

    foreach (QBarSet* set, sets) {
        m_barSets.append(set);
        QObject::connect(set->d_ptr.data(), SIGNAL(updatedBars()), this, SLOT(barsetChanged()));
    }
    if (m_dataset) {
        m_dataset->updateSeries(q);   // this notifies legend
    }
    emit restructuredBars();        // this notifies barchartitem
    return true;
}

bool QBarSeriesPrivate::remove(QList<QBarSet* > sets)
{
    Q_Q(QBarSeries);
    bool setsRemoved = false;
    foreach (QBarSet* set, sets) {
        if (m_barSets.contains(set)) {
            m_barSets.removeOne(set);
            QObject::disconnect(set->d_ptr.data(), SIGNAL(updatedBars()), this, SLOT(barsetChanged()));
            setsRemoved = true;
        }
    }

    if (setsRemoved) {
        if (m_dataset) {
            m_dataset->updateSeries(q);   // this notifies legend
        }
        emit restructuredBars();        // this notifies barchartitem
    }
    return setsRemoved;
}

#include "moc_qbarseries.cpp"
#include "moc_qbarseries_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
