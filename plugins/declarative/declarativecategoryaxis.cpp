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

#include "declarativecategoryaxis.h"
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

#ifdef QDOC_QT5
/*!
    \qmltype CategoryRange
    \inqmlmodule QtCommercial.Chart

    \include /doc/src/categoryrange.qdocinc
*/
#else
/*!
    \qmlclass CategoryRange

    \include ../doc/src/categoryrange.qdocinc
*/
#endif

DeclarativeCategoryRange::DeclarativeCategoryRange(QObject *parent) :
    QObject(parent),
    m_endValue(0),
    m_label(QString())
{
}

DeclarativeCategoryAxis::DeclarativeCategoryAxis(QObject *parent) :
    QCategoryAxis(parent)
{
}

void DeclarativeCategoryAxis::classBegin()
{
}

void DeclarativeCategoryAxis::componentComplete()
{
    QList<QPair<QString, qreal> > ranges;
    foreach (QObject *child, children()) {
        if (qobject_cast<DeclarativeCategoryRange *>(child)) {
            DeclarativeCategoryRange *range = qobject_cast<DeclarativeCategoryRange *>(child);
            ranges.append(QPair<QString, qreal>(range->label(), range->endValue()));
        }
    }

    // Sort and append the range objects according to end value
    qSort(ranges.begin(), ranges.end(), endValueLessThan);
    for (int i(0); i < ranges.count(); i++)
        append(ranges.at(i).first, ranges.at(i).second);
}

bool DeclarativeCategoryAxis::endValueLessThan(const QPair<QString, qreal> &value1, const QPair<QString, qreal> &value2)
{
    return value1.second < value2.second;
}

QDECLARATIVE_LIST_PROPERTY<QObject> DeclarativeCategoryAxis::axisChildren()
{
    return QDECLARATIVE_LIST_PROPERTY<QObject>(this, 0, &DeclarativeCategoryAxis::appendAxisChildren LIST_PROPERTY_PARAM_DEFAULTS);
}

void DeclarativeCategoryAxis::append(const QString &label, qreal categoryEndValue)
{
    QCategoryAxis::append(label, categoryEndValue);
}

void DeclarativeCategoryAxis::remove(const QString &label)
{
    QCategoryAxis::remove(label);
}

void DeclarativeCategoryAxis::replace(const QString &oldLabel, const QString &newLabel)
{
    QCategoryAxis::replaceLabel(oldLabel, newLabel);
}

void DeclarativeCategoryAxis::appendAxisChildren(QDECLARATIVE_LIST_PROPERTY<QObject> *list, QObject *element)
{
    // Empty implementation; the children are parsed in componentComplete instead
    Q_UNUSED(list)
    Q_UNUSED(element)
}

#include "moc_declarativecategoryaxis.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
