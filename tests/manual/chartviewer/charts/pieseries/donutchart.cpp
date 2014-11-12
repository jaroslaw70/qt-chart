/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#include "charts.h"
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>

class DonutChart: public Chart
{
public:
    QString name() { return QObject::tr("DonutChart"); }
    QString category()  { return QObject::tr("PieSeries"); }
    QString subCategory() { return QString::null; }

    QChart *createChart(const DataTable &table)
    {
        QChart *chart = new QChart();
        chart->setTitle("Donut chart");
        for (int i = 0, j = table.count(); i < table.count(); i++, j--) {
            QPieSeries *series = new QPieSeries(chart);
            foreach (Data data, table[i]) {
                QPieSlice *slice = series->append(data.second, data.first.y());
                if (data == table[i].first())
                    slice->setLabelVisible();
            }
            series->setPieSize(j / (qreal) table.count());
            if (j > 1)
                series->setHoleSize((j - 1) / (qreal) table.count() + 0.1);
            series->setHorizontalPosition(0.5);
            series->setVerticalPosition(0.5);
            chart->addSeries(series);
        }
        return chart;
    }
};

DECLARE_CHART(DonutChart)

