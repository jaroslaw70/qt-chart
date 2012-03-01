#include "splinewidget.h"
#include "qchartview.h"
#include "qsplineseries.h"
#include "qlineseries.h"
#include <QGridLayout>

QTCOMMERCIALCHART_USE_NAMESPACE

SplineWidget::SplineWidget(QWidget *parent)
    : QWidget(parent)
{
    //create QSplineSeries
    QSplineSeries* series = new QSplineSeries(this);
    series->add(QPointF(150, 100));
    series->add(QPointF(200, 180));
    series->add(QPointF(240, 130));
    series->add(QPointF(270, 120));
    series->add(QPointF(310, 120));
    series->add(QPointF(420, 160));
    series->add(QPointF(535, 250));

    series->calculateControlPoints();

//    QLineSeries* lineSeries = new QLineSeries;
//    for (int i = 0; i < series->count() - 1; i++)
//    {
//        lineSeries->add(series->at(i).x(), series->at(i).y());
//        lineSeries->add(series->controlPoint(2*i).x(), series->controlPoint(2*i).y());
//        lineSeries->add(series->controlPoint(2*i + 1).x(), series->controlPoint(2*i + 1).y());
//    }

//    QLineChartSeries* lineSeries2 = new QLineChartSeries;
//    lineSeries2->add(10, 50);
//    lineSeries2->add(30, 15);
//    lineSeries2->add(60, 40);
//    lineSeries2->add(90, 70);
//    lineSeries2->add(100, 20);

    //create chart view
    QChartView* chart = new QChartView;
    chart->setMinimumSize(800,600);
//    chart->setGeometry(50, 50, 400, 300);
    chart->addSeries(series);

    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addWidget(chart);
    setLayout(mainLayout);
}

SplineWidget::~SplineWidget()
{
    
}
