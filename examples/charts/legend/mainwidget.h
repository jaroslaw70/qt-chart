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

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGraphicsWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGraphicsGridLayout>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtCharts/QBarSeries>

QT_CHARTS_USE_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);
    void createSeries();
    void showLegendSpinbox();
    void hideLegendSpinbox();

public Q_SLOTS:
    void toggleAttached();
    void addBarset();
    void removeBarset();

    void setLegendAlignment();

    void toggleBold();
    void toggleItalic();
    void fontSizeChanged();

    void updateLegendLayout();

private:
    QChart *m_chart;
    QBarSeries *m_series;

    QChartView *m_chartView;
    QGridLayout *m_mainLayout;
    QGridLayout *m_buttonLayout;
    QGridLayout *m_fontLayout;

    QDoubleSpinBox *m_fontSize;

    // For detached layout
    QGroupBox *m_legendSettings;
    QDoubleSpinBox *m_legendPosX;
    QDoubleSpinBox *m_legendPosY;
    QDoubleSpinBox *m_legendWidth;
    QDoubleSpinBox *m_legendHeight;
};

#endif // MAINWIDGET_H
