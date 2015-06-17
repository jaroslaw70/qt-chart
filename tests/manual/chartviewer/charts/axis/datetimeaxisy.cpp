/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#include "charts.h"
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QDateTimeAxis>

class DateTimeAxisY: public Chart
{
public:
    QString name() { return "AxisY"; }
    QString category()  { return QObject::tr("Axis"); }
    QString subCategory() { return "DateTimeAxis"; }

    QChart *createChart(const DataTable &table)
    {
        QChart *chart = new QChart();
        chart->setTitle("Value X , DateTime Y");
        QValueAxis *valueaxis = new QValueAxis();
        QDateTimeAxis *datetimeaxis = new QDateTimeAxis();
        datetimeaxis->setTickCount(10);
        datetimeaxis->setFormat("yyyy");

        qreal day = 1000l * 60l * 60l * 24l;

        QString name("Series ");
        int nameIndex = 0;
        foreach (DataList list, table) {
            QLineSeries *series = new QLineSeries(chart);
            foreach (Data data, list) {
                QPointF point = data.first;
                series->append(point.x(), day * 365l * 30l + point.y() * day * 365l);
            }
            series->setName(name + QString::number(nameIndex));
            nameIndex++;
            chart->addSeries(series);
            chart->setAxisY(datetimeaxis, series);
            chart->setAxisX(valueaxis, series);
        }

        return chart;
    }
};

class DateTimeAxisYTitle: public DateTimeAxisY
{
public:
    QString name() { return "AxisY Title"; }

    QChart *createChart(const DataTable &table)
    {
        QChart *chart = DateTimeAxisY::createChart(table);
        chart->axisX()->setTitleText("Axis X");
        chart->axisY()->setTitleText("Axis Y");
        chart->setTitle("Value X , DateTime Y, Title");
        return chart;
    }
};

DECLARE_CHART(DateTimeAxisY);
DECLARE_CHART(DateTimeAxisYTitle);