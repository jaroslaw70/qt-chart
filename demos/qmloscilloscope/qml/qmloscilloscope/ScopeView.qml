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

import QtQuick 1.0
import QtCommercial.Chart 1.1

//![1]
ChartView {
    id: chartView
    animationOptions: ChartView.NoAnimation
    theme: ChartView.ChartThemeDark

    ValueAxis {
        id: axisY1
        min: -1
        max: 4
    }

    ValueAxis {
        id: axisY2
        min: -10
        max: 5
    }

    ValueAxis {
        id: axisX
        min: 0
        max: 1000
    }

    LineSeries {
        id: lineSeries1
        name: "signal 1"
        axisX: axisX
        axisY: axisY1
    }
    LineSeries {
        id: lineSeries2
        name: "signal 2"
        axisX: axisX
        axisY: axisY2
    }
// ...
//![1]

    //![2]
    Timer {
        id: refreshTimer
        interval: 1 / 60 * 1000 // 60 Hz
        running: true
        repeat: true
        onTriggered: {
            dataSource.update(chartView.series(0));
            dataSource.update(chartView.series(1));
        }
    }
    //![2]

    //![3]
    function changeSeriesType(type) {
        chartView.removeAllSeries();

        // Create two new series of the correct type. Axis x is the same for both of the series,
        // but the series have their own y-axes to make it possible to control the y-offset
        // of the "signal sources".
        if (type == "line") {
            scopeView.createSeries(ChartView.SeriesTypeLine, "signal 1", createAxis(0, 1000), createAxis(-1, 4));
            scopeView.createSeries(ChartView.SeriesTypeLine, "signal 2", chartView.axisX(), createAxis(-10, 5));
        } else if (type == "spline") {
            scopeView.createSeries(ChartView.SeriesTypeSpline, "signal 1", createAxis(0, 1000), createAxis(-1, 4));
            scopeView.createSeries(ChartView.SeriesTypeSpline, "signal 2", chartView.axisX(), createAxis(-10, 5));
        } else {
            var series1 = scopeView.createSeries(ChartView.SeriesTypeScatter, "signal 1", createAxis(0, 1000), createAxis(-1, 4));
            series1.markerSize = 3;
            series1.borderColor = "transparent";
            var series2 = scopeView.createSeries(ChartView.SeriesTypeScatter, "signal 2", chartView.axisX(), createAxis(-10, 5));
            series2.markerSize = 3;
            series2.borderColor = "transparent";
        }
    }

    function createAxis(min, max) {
        // The following creates a ValueAxis object that can be then set as a x or y axis for a series
        return Qt.createQmlObject("import QtQuick 1.1; import QtCommercial.Chart 1.1; ValueAxis { min: "
                                  + min + "; max: " + max + " }", chartView);
    }
    //![3]

    function setAnimations(enabled) {
        if (enabled)
            scopeView.animationOptions = ChartView.SeriesAnimations;
        else
            scopeView.animationOptions = ChartView.NoAnimation;
    }

    function changeRefreshRate(rate) {
        refreshTimer.interval = 1 / Number(rate) * 1000;
    }
}
