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

#include "charts.h"
#include "qchart.h"
#include "qlineseries.h"

class FontChart: public Chart
{
public:
    FontChart(int fontSize):m_fontSize(fontSize){};
    QString name() { return QObject::tr("Font") + " " + QString::number(m_fontSize); }
    QString category()  { return QObject::tr("Font"); }
    QString subCategory() { return QString::null; }

    QChart* createChart(const DataTable& table) {

           QChart* chart = new QChart();
           chart->setTitle("Font size " + QString::number(m_fontSize));

           QString name("Series ");
           int nameIndex = 0;
           foreach (DataList list, table) {
               QLineSeries *series = new QLineSeries(chart);
               foreach (Data data, list)
                   series->append(data.first);
               series->setName(name + QString::number(nameIndex));
               nameIndex++;
               chart->addSeries(series);
           }

           chart->createDefaultAxes();
           QFont font;
           font.setPixelSize(m_fontSize);
           chart->setTitleFont(font);
           chart->axisX()->setLabelsFont(font);
           chart->axisY()->setLabelsFont(font);

           return chart;
    }

private:
    int m_fontSize;

};

class FontChart5:public FontChart{
public:
    FontChart5():FontChart(5){};
};

class FontChart8:public FontChart{
public:
    FontChart8():FontChart(8){};
};

class FontChart10:public FontChart{
public:
    FontChart10():FontChart(10){};
};

class FontChart12:public FontChart{
public:
    FontChart12():FontChart(12){};
};

class FontChart15:public FontChart{
public:
    FontChart15():FontChart(15){};
};

class FontChart18:public FontChart{
public:
    FontChart18():FontChart(18){};
};

class FontChart20:public FontChart{
public:
    FontChart20():FontChart(20){};
};

class FontChart24:public FontChart{
public:
    FontChart24():FontChart(24){};
};

class FontChart28:public FontChart{
public:
    FontChart28():FontChart(28){};
};

DECLARE_CHART(FontChart5);
DECLARE_CHART(FontChart8);
DECLARE_CHART(FontChart10);
DECLARE_CHART(FontChart12);
DECLARE_CHART(FontChart15);
DECLARE_CHART(FontChart18);
DECLARE_CHART(FontChart20);
DECLARE_CHART(FontChart24);
DECLARE_CHART(FontChart28);
