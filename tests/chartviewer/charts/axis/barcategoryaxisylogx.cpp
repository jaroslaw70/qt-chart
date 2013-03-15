/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

#include "charts.h"
#include "qchart.h"
#include "qhorizontalbarseries.h"
#include "qbarset.h"
#include "qlogvalueaxis.h"
#include "qbarcategoryaxis.h"

class BarCategoryAxisYLogX: public Chart
{
public:
    QString name() { return "AxisY"; }
    QString category()  { return QObject::tr("Axis"); }
    QString subCategory() { return "BarCategoryAxis"; }

    QChart *createChart(const DataTable &table)
    {
        QChart *chart = new QChart();
        chart->setTitle(" LogValue X , BarCateogry Y");

        QString name("Series ");
        QHorizontalBarSeries *series = new QHorizontalBarSeries(chart);
        QLogValueAxis *logvalueaxis = new QLogValueAxis();
        logvalueaxis->setBase(2);
        QBarCategoryAxis *barcategory = new QBarCategoryAxis();
        for (int i(0); i < table.count(); i++) {
            QBarSet *set = new QBarSet("Bar set " + QString::number(i));
            foreach (Data data, table[i])
                *set << data.first.y();
            series->append(set);
        }
        chart->addSeries(series);

        int count = series->barSets().first()->count();


        for (int i = 0; i < count; i++) {
            barcategory->append("BarSet " + QString::number(i));
        }

        chart->setAxisX(logvalueaxis, series);
        chart->setAxisY(barcategory, series);

        return chart;
    }
};

class BarCategoryAxisYLogXTitle: public BarCategoryAxisYLogX
{
    QString name() { return "AxisX Title"; }
    QChart *createChart(const DataTable &table)
    {
        QChart *chart = BarCategoryAxisYLogX::createChart(table);
        chart->axisX()->setTitleText("Axis X");
        chart->axisY()->setTitleText("Axis Y");
        chart->setTitle(" LogValue X , BarCateogry Y, title");
        return chart;
    }
};

DECLARE_CHART(BarCategoryAxisYLogX);
DECLARE_CHART(BarCategoryAxisYLogXTitle);