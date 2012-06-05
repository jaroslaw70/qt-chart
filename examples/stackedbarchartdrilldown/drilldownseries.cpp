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

#include "drilldownseries.h"

QTCOMMERCIALCHART_USE_NAMESPACE

DrilldownBarSeries::DrilldownBarSeries(QStringList categories, QObject *parent)
    : QStackedBarSeries(parent)
{
    m_categories = categories;
}

void DrilldownBarSeries::mapDrilldownSeries(int index, DrilldownBarSeries* drilldownSeries)
{
    m_DrilldownSeries[index] = drilldownSeries;
}

DrilldownBarSeries* DrilldownBarSeries::drilldownSeries(int index)
{
    return m_DrilldownSeries[index];
}

QStringList DrilldownBarSeries::categories()
{
    return m_categories;
}

#include "moc_drilldownseries.cpp"
