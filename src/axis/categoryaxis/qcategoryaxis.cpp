/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

#include "qcategoryaxis.h"
#include "qcategoryaxis_p.h"
#include "chartcategoryaxisx_p.h"
#include "chartcategoryaxisy_p.h"
#include "polarchartcategoryaxisangular_p.h"
#include "polarchartcategoryaxisradial_p.h"
#include "qchart.h"
#include <qmath.h>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE
/*!
    \class QCategoryAxis
    \brief The QCategoryAxis class allows putting a named ranges on the axis.
    \mainclass

    This class can be used when the underlying data needs to be given extra meaning.
    Unlike with the QBarCategoryAxis the QCategoryAxis allows the categories ranges widths to be specified freely.

    Example code on how to use QCategoryAxis:
    \table
        \row
            \o  \br
                \br
                \code
                QChartView *chartView = new QChartView;
                QLineSeries *series = new QLineSeries;
                // ...
                chartView->chart()->addSeries(series);

                QCategoryAxis *axisY = new QCategoryAxis;
                axisY->setMin(0);
                axisY->setMax(52);
                axisY->setStartValue(15);
                axisY->append("First", 20);
                axisY->append("Second", 37);
                axisY->append("Third", 52);
                chartView->chart()->setAxisY(axisY, series);
                \endcode
            \o \br
               \inlineimage api_category_axis.png
    \endtable
*/
/*!
    \qmlclass CategoryAxis QCategoryAxis
    \inherits AbstractAxis
    \brief CategoryAxis allows putting a named ranges on the axis.

    For example:
    \table
        \row
            \o  \br
                \br
                \br
                \snippet ../demos/qmlaxes/qml/qmlaxes/View3.qml 1
            \o \inlineimage demos_qmlaxes3.png
    \endtable
*/

/*!
  \property QCategoryAxis::startValue
  Defines the low end of the first category on the axis.
*/
/*!
  \qmlproperty int CategoryAxis::startValue
  Defines the low end of the first category on the axis.
*/

/*!
  \property QCategoryAxis::count
  The count of categories.
*/
/*!
  \qmlproperty int CategoryAxis::count
  The count of categories.
*/

/*!
  \property QCategoryAxis::categoriesLabels
  The category labels as a string list.
*/
/*!
  \qmlproperty StringList CategoryAxis::categoriesLabels
  The category labels as a list of strings.
*/

/*!
  \fn void QCategoryAxis::categoriesChanged()
  Axis emits signal when the categories of the axis have changed.
*/


/*!
    Constructs an axis object which is a child of \a parent.
*/
QCategoryAxis::QCategoryAxis(QObject *parent):
    QValueAxis(*new QCategoryAxisPrivate(this), parent)
{
}

/*!
    Destroys the object
*/
QCategoryAxis::~QCategoryAxis()
{
    Q_D(QCategoryAxis);
    if (d->m_chart)
        d->m_chart->removeAxis(this);
}

/*!
    \internal
*/
QCategoryAxis::QCategoryAxis(QCategoryAxisPrivate &d, QObject *parent): QValueAxis(d, parent)
{

}

/*!
    \qmlmethod CategoryAxis::append(string label, real endValue)
    Appends new category to the axis with an \a label. Category label has to be unique.
    Parameter \a endValue specifies the high end limit of the category.
    It has to be greater than the high end limit of the previous category.
    Otherwise the method returns without adding a new category.
*/
/*!
    Appends new category to the axis with an \a categoryLabel.
    Category label has to be unique.
    Parameter \a categoryEndValue specifies the high end limit of the category.
    It has to be greater than the high end limit of the previous category.
    Otherwise the method returns without adding a new category.
*/
void QCategoryAxis::append(const QString &categoryLabel, qreal categoryEndValue)
{
    Q_D(QCategoryAxis);

    if (!d->m_categories.contains(categoryLabel)) {
        if (d->m_categories.isEmpty()) {
            Range range(d->m_categoryMinimum, categoryEndValue);
            d->m_categoriesMap.insert(categoryLabel, range);
            d->m_categories.append(categoryLabel);
            emit categoriesChanged();
        } else if (categoryEndValue > endValue(d->m_categories.last())) {
            Range previousRange = d->m_categoriesMap.value(d->m_categories.last());
            d->m_categoriesMap.insert(categoryLabel, Range(previousRange.second, categoryEndValue));
            d->m_categories.append(categoryLabel);
            emit categoriesChanged();
        }
    }
}

/*!
    Sets \a min to be the low end limit of the first category on the axis.
    If there is already some categories added to the axis then passed value must be lower than the high end value of the already defined first category range.
    Otherwise nothing is done.
*/
void QCategoryAxis::setStartValue(qreal min)
{
    Q_D(QCategoryAxis);
    if (d->m_categories.isEmpty()) {
        d->m_categoryMinimum = min;
        emit categoriesChanged();
    } else {
        Range range = d->m_categoriesMap.value(d->m_categories.first());
        if (min < range.second) {
            d->m_categoriesMap.insert(d->m_categories.first(), Range(min, range.second));
            emit categoriesChanged();
        }
    }
}

/*!
    Returns the low end limit of the category specified by an \a categoryLabel
*/
qreal QCategoryAxis::startValue(const QString &categoryLabel) const
{
    Q_D(const QCategoryAxis);
    if (categoryLabel.isEmpty())
        return d->m_categoryMinimum;
    return d->m_categoriesMap.value(categoryLabel).first;
}

/*!
    Returns the high end limit of the interval specified by an \a categoryLabel
*/
qreal QCategoryAxis::endValue(const QString &categoryLabel) const
{
    Q_D(const QCategoryAxis);
    return d->m_categoriesMap.value(categoryLabel).second;
}

/*!
    \qmlmethod CategoryAxis::remove(string label)
    Removes a category specified by the \a label from the axis
*/
/*!
    Removes an interval specified by the \a categoryLabel from the axis
*/
void QCategoryAxis::remove(const QString &categoryLabel)
{
    Q_D(QCategoryAxis);
    int labelIndex = d->m_categories.indexOf(categoryLabel);

    // check if such label exists
    if (labelIndex != -1) {
        d->m_categories.removeAt(labelIndex);
        d->m_categoriesMap.remove(categoryLabel);

        // the range of the interval that follows (if exists) needs to be updated
        if (labelIndex < d->m_categories.count()) {
            QString label = d->m_categories.at(labelIndex);
            Range range = d->m_categoriesMap.value(label);

            // set the range
            if (labelIndex == 0) {
                range.first = d->m_categoryMinimum;
                d->m_categoriesMap.insert(label, range);
            } else {
                range.first = d->m_categoriesMap.value(d->m_categories.at(labelIndex - 1)).second;
                d->m_categoriesMap.insert(label, range);
            }
        }
        emit categoriesChanged();
    }
}

/*!
  \qmlmethod CategoryAxis::replace(string oldLabel, string newLabel)
  Replaces \a oldLabel of an existing category with a \a newLabel.
  If the old label does not exist the method returns without making any changes.
*/
/*!
  Replaces \a oldLabel of an existing category with a \a newLabel
  If the old label does not exist the method returns without making any changes.
 */
void QCategoryAxis::replaceLabel(const QString &oldLabel, const QString &newLabel)
{
    Q_D(QCategoryAxis);
    int labelIndex = d->m_categories.indexOf(oldLabel);

    // check if such label exists
    if (labelIndex != -1) {
        d->m_categories.replace(labelIndex, newLabel);
        Range range = d->m_categoriesMap.value(oldLabel);
        d->m_categoriesMap.remove(oldLabel);
        d->m_categoriesMap.insert(newLabel, range);
        emit categoriesChanged();
    }
}

/*!
  Returns the list of the intervals labels
 */
QStringList QCategoryAxis::categoriesLabels()
{
    Q_D(QCategoryAxis);
    return d->m_categories;
}

/*!
  Returns number of intervals.
 */
int QCategoryAxis::count() const
{
    Q_D(const QCategoryAxis);
    return d->m_categories.count();
}

/*!
  Returns the type of the axis
*/
QAbstractAxis::AxisType QCategoryAxis::type() const
{
    return QAbstractAxis::AxisTypeCategory;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QCategoryAxisPrivate::QCategoryAxisPrivate(QCategoryAxis *q)
    : QValueAxisPrivate(q),
      m_categoryMinimum(0)
{

}

QCategoryAxisPrivate::~QCategoryAxisPrivate()
{

}

int QCategoryAxisPrivate::ticksCount() const
{
    return m_categories.count() + 1;
}

void QCategoryAxisPrivate::initializeGraphics(QGraphicsItem *parent)
{
    Q_Q(QCategoryAxis);
    ChartAxisElement *axis(0);
    if (m_chart->chartType() == QChart::ChartTypeCartesian) {
        if (orientation() == Qt::Vertical)
            axis = new ChartCategoryAxisY(q,parent);
        else if (orientation() == Qt::Horizontal)
            axis = new ChartCategoryAxisX(q,parent);
    }

    if (m_chart->chartType() == QChart::ChartTypePolar) {
        if (orientation() == Qt::Vertical)
            axis = new PolarChartCategoryAxisRadial(q, parent);
        if (orientation() == Qt::Horizontal)
            axis = new PolarChartCategoryAxisAngular(q, parent);
    }

    m_item.reset(axis);
    QAbstractAxisPrivate::initializeGraphics(parent);
}

#include "moc_qcategoryaxis.cpp"
#include "moc_qcategoryaxis_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
