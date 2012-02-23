/*!
    \class Widget
    \brief Ui for the application.
    \internal
*/

#include "widget.h"
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

#include <QSqlQuery>
#include <qscatterseries.h>
#include <qchartview.h>
#include <qchartaxis.h>
#include <qbarcategory.h>
#include <qbarset.h>
#include <QListWidget>
#include <QPrinter>
#include <QPrintDialog>
#include <QRadioButton>

QTCOMMERCIALCHART_USE_NAMESPACE

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setGeometry(100, 100, 1000, 600);

    // right panel layout
    barChartRadioButton = new QRadioButton(tr("Bar chart"));
    barChartRadioButton->setChecked(true);
    scatterChartRadioButton = new QRadioButton(tr("Scatter chart"));
    scatterChartRadioButton->setChecked(false);
    countrieslist = new QListWidget;
    countrieslist->setSelectionMode(QAbstractItemView::MultiSelection);

    yearslist = new QListWidget;
    yearslist->setSelectionMode(QAbstractItemView::ExtendedSelection);
    for (int i = 1990; i < 2011; i++)
        yearslist->addItem(QString("%1").arg(i));

    QPushButton* refreshButton = new QPushButton(tr("Refresh"));
    connect(refreshButton, SIGNAL(clicked()), this, SLOT(refreshChart()));

    QPushButton* printButton = new QPushButton(tr("Print chart"));
    connect(printButton, SIGNAL(clicked()), this, SLOT(printChart()));

    QVBoxLayout* rightPanelLayout = new QVBoxLayout;
    rightPanelLayout->addWidget(barChartRadioButton);
    rightPanelLayout->addWidget(scatterChartRadioButton);
    rightPanelLayout->addWidget(countrieslist);
    rightPanelLayout->addWidget(yearslist);
    rightPanelLayout->addWidget(refreshButton);
    rightPanelLayout->addWidget(printButton);
    rightPanelLayout->setStretch(0, 1);
    rightPanelLayout->setStretch(1, 0);

    // main layout
    chartArea = new QChartView(this);
    chartArea->setChartTitle("GDP by country");
    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addWidget(chartArea, 0, 0);
    mainLayout->addLayout(rightPanelLayout, 0, 1);
    mainLayout->setColumnStretch(0,1);
    setLayout(mainLayout);

    // connect to the database
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("gdpData");
    if(!db.open())
    {
        qDebug() << "could not open database. SQLite db file missing (?)";
        return;
    }

    // get the list of all countires and regions.
    QSqlQuery query;
    query.exec("SELECT DISTINCT country FROM gdp2");

    // add the countries to the country filter
    while (query.next()) {
        countrieslist->addItem(query.value(0).toString());
    }

    // hide axis X labels
    QChartAxis* axis = chartArea->axisX();
//    axis->setLabelsVisible(false);
    //    newAxis.setLabelsOrientation(QChartAxis::LabelsOrientationSlide);

}

Widget::~Widget()
{
    //
    db.close();
}

/*!
    refreshes the chart
*/
void Widget::refreshChart()
{
    chartArea->removeAllSeries();

    // selected countries items list is not sorted. copy the values to QStringlist and sort them.
    QStringList selectedCountriesStrings;
    QList<QListWidgetItem*> selectedCountriesItems = countrieslist->selectedItems();
    for (int i = 0; i < selectedCountriesItems.size(); i++)
        selectedCountriesStrings.append(selectedCountriesItems[i]->text());
    selectedCountriesStrings.sort();

    QSqlQuery query;
    // selected years items list is not sorted. copy the values to QList<Integer> and sort them.
    QList<int> selectedYearsInts;
    QList<QListWidgetItem*> selectedYearsItems = yearslist->selectedItems();
    for (int i = 0; i < selectedYearsItems.size(); i++)
        selectedYearsInts.append(selectedYearsItems[i]->text().toInt());
    qSort(selectedYearsInts.begin(), selectedYearsInts.end(), qGreater<int>());

    if (barChartRadioButton->isChecked())
    {
        // use the sorted selected coutries list to initialize BarCategory
        QBarCategory* category = new QBarCategory;
        for (int i = 0; i < selectedCountriesStrings.size(); i++)
            *category << selectedCountriesStrings[i];
        series0 = new QBarChartSeries(category);

        // prepare the selected counries SQL query
        QString countriesQuery = "country IN (";
        for (int i = 0; i < selectedCountriesStrings.size(); i++)
        {
            countriesQuery.append("'" + selectedCountriesStrings[i] + "'");
            if ( i < selectedCountriesStrings.size() - 1)
                countriesQuery.append(",");
            else
                countriesQuery.append(")");
        }

        // perform a query for each selected year
        for (int i = 0; i < selectedYearsInts.size(); i++)
        {
            query.exec("SELECT country,gdpvalue FROM gdp2 where year=" + QString("%1").arg(selectedYearsInts[i]) + " AND " + countriesQuery);
            QBarSet* barSet = new QBarSet(QString("GDP_%1").arg(selectedYearsInts[i]));
            //        while (query.next()) {
            //            qDebug() << query.value(0).toString() << " : " << query.value(1).toString();
            //        }
            query.first();

            // the data for some of the coutries for some years might be missing.
            // QBarChart needs bars to have same size
            for (int k = 0; k < selectedCountriesStrings.size(); k++)
            {
                if (selectedCountriesStrings[k] == query.value(0).toString())
                {
                    *barSet << query.value(1).toReal();
                    qDebug() << query.value(0).toString() << query.value(1).toReal() << " : " << QString("%1").arg(selectedYearsInts[i]);
                    query.next();
                }
                else
                {
                    // data missing, put 0
                    *barSet << 0.0f;
                    qDebug() << "Putting 0 for Bosnia" << " : " << QString("%1").arg(selectedYearsInts[i]);
                }
            }
            series0->addBarSet(barSet);
        }
        // add the serie to the chart
        chartArea->addSeries(series0);

    }
    else if (scatterChartRadioButton->isChecked())
    {
        QString yearsQuery = "year IN (";
        for (int i = 0; i < selectedYearsInts.size(); i++)
        {
            yearsQuery.append("'" + QString("%1").arg(selectedYearsInts[i]) + "'");
            if ( i < selectedYearsInts.size() - 1)
                yearsQuery.append(",");
            else
                yearsQuery.append(")");
        }

        // perform a query for each selected year
        for (int i = 0; i < selectedCountriesStrings.size(); i++)
        {
            query.exec("SELECT year,gdpvalue FROM gdp2 where country='" + selectedCountriesStrings[i] + "' AND " + yearsQuery);
            query.first();

            QScatterSeries* series = new QScatterSeries;
            // the data for some of the coutries for some years might be missing.
            for (int k = 0; k < selectedYearsInts.size(); k++)
            {
                if (selectedYearsInts[k] == query.value(0).toInt())
                {
                    *series << QPointF(query.value(0).toInt() , query.value(1).toReal());
                    qDebug() << query.value(0).toString() << query.value(1).toReal() << " : " << QString("%1").arg(selectedYearsInts[k]);
                    query.next();
                }
                else
                {
                    // data missing, put 0
                    *series << QPointF(selectedYearsInts[k] , 0.0f);
                    qDebug() << "Putting 0 for Bosnia" << " : " << QString("%1").arg(selectedYearsInts[i]) << " " << query.value(0).toInt();
                }
            }
//            chartArea->axisX()->setRange(selectedYearsInts[selectedYearsInts.size() - 1] + 1, selectedYearsInts[0] - 1);
            chartArea->addSeries(series);
        }
        chartArea->axisX()->setRange(selectedYearsInts[selectedYearsInts.size() - 1] + 1, selectedYearsInts[0] - 1);
    }
}

void Widget::printChart()
{
    QPrinter printer;
    //    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOrientation(QPrinter::Landscape);
    printer.setOutputFileName("print.pdf");

    QPainter painter;
    painter.begin(&printer);
    chartArea->render(&painter);
}
