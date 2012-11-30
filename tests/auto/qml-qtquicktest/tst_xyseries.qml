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
import QtQuickTest 1.0
import QtCommercial.Chart 1.2

Rectangle {
    width: 400
    height: 300

    TestCase {
        id: tc1
        name: "tst_qml-qtquicktest XY Series"
        when: windowShown

        function test_properties() {
            verify(lineSeries.color != undefined);
            compare(lineSeries.pointsVisible, false);
            compare(lineSeries.capStyle, Qt.SquareCap);
            compare(lineSeries.style, Qt.SolidLine);
            compare(lineSeries.width, 2.0);

            verify(splineSeries.color != undefined);
            compare(splineSeries.pointsVisible, false);
            compare(splineSeries.capStyle, Qt.SquareCap);
            compare(splineSeries.style, Qt.SolidLine);
            compare(splineSeries.width, 2.0);

            verify(scatterSeries.color != undefined);
            verify(scatterSeries.borderColor != undefined);
            compare(scatterSeries.borderWidth, 2.0);
            compare(scatterSeries.markerShape, ScatterSeries.MarkerShapeCircle);
            compare(scatterSeries.markerSize, 15.0);

            verify(areaSeries.color != undefined);
            verify(areaSeries.borderColor != undefined);
            compare(areaSeries.borderWidth, 2.0);
        }

        function test_axes() {
            // Axis initialization
            compare(chartView.axes.length, 2);
            verify(chartView.axes[0] == lineSeries.axisX || chartView.axes[1] == lineSeries.axisX);
            verify(chartView.axes[0] == lineSeries.axisY || chartView.axes[1] == lineSeries.axisY);
            compare(lineSeries.axisX, splineSeries.axisX);
            compare(lineSeries.axisY, splineSeries.axisY);
            compare(lineSeries.axisX, areaSeries.axisX);
            compare(lineSeries.axisY, areaSeries.axisY);

            // Set illegal axes
            lineSeries.axisX = lineSeries.axisY;
            compare(lineSeries.axisX, splineSeries.axisX);
            lineSeries.axisXTop = lineSeries.axisX;
            compare(lineSeries.axisX, splineSeries.axisX);
            lineSeries.axisY = lineSeries.axisX;
            compare(lineSeries.axisY, splineSeries.axisY);
            lineSeries.axisYRight = lineSeries.axisY;
            compare(lineSeries.axisY, splineSeries.axisY);
        }

        function test_append() {
            lineSeriesPointAddedSpy.clear();
            splineSeriesPointAddedSpy.clear();
            scatterSeriesPointAddedSpy.clear();
            var count = append();
            compare(lineSeries.count, count);
            compare(splineSeries.count, count);
            compare(scatterSeries.count, count);
            tryCompare(lineSeriesPointAddedSpy.count, count);
            tryCompare(splineSeriesPointAddedSpy.count, count);
            tryCompare(scatterSeriesPointAddedSpy.count, count);
            clear();
            compare(lineSeries.count, 0);
            compare(splineSeries.count, 0);
            compare(scatterSeries.count, 0);
        }

        function test_replace() {
            var count = append();
            for (var i = 0; i < count; i++) {
                lineSeries.replace(lineSeries.at(i).x, lineSeries.at(i).y, i, Math.random());
                splineSeries.replace(splineSeries.at(i).x, splineSeries.at(i).y, i, Math.random());
                scatterSeries.replace(scatterSeries.at(i).x, scatterSeries.at(i).y, i, Math.random());
            }
            compare(lineSeries.count, count);
            compare(splineSeries.count, count);
            compare(scatterSeries.count, count);
            tryCompare(lineSeriesPointReplacedSpy.count, count);
            tryCompare(splineSeriesPointReplacedSpy.count, count);
            tryCompare(scatterSeriesPointReplacedSpy.count, count);
            clear();
        }

        function test_insert() {
            var count = append();
            lineSeriesPointAddedSpy.clear();
            splineSeriesPointAddedSpy.clear();
            scatterSeriesPointAddedSpy.clear();
            for (var i = 0; i < count; i++) {
                lineSeries.insert(i * 2, i, Math.random());
                splineSeries.insert(i * 2, i, Math.random());
                scatterSeries.insert(i * 2, i, Math.random());
            }
            compare(lineSeries.count, count * 2);
            compare(splineSeries.count, count * 2);
            compare(scatterSeries.count, count * 2);
            tryCompare(lineSeriesPointAddedSpy.count, count);
            tryCompare(splineSeriesPointAddedSpy.count, count);
            tryCompare(scatterSeriesPointAddedSpy.count, count);
            clear();
        }

        function test_remove() {
            lineSeriesPointRemovedSpy.clear();
            splineSeriesPointRemovedSpy.clear();
            scatterSeriesPointRemovedSpy.clear();
            var count = append();
            for (var i = 0; i < count; i++) {
                lineSeries.remove(lineSeries.at(0).x, lineSeries.at(0).y);
                splineSeries.remove(splineSeries.at(0).x, splineSeries.at(0).y);
                scatterSeries.remove(scatterSeries.at(0).x, scatterSeries.at(0).y);
            }
            compare(lineSeries.count, 0);
            compare(splineSeries.count, 0);
            compare(scatterSeries.count, 0);
            tryCompare(lineSeriesPointRemovedSpy.count, count);
            tryCompare(splineSeriesPointRemovedSpy.count, count);
            tryCompare(scatterSeriesPointRemovedSpy.count, count);
        }

        // Not a test function, called from test functions
        function append() {
            var count = 100;
            chartView.axisX().min = 0;
            chartView.axisX().max = 100;
            chartView.axisY().min = 0;
            chartView.axisY().max = 1;

            for (var i = 0; i < count; i++) {
                lineSeries.append(i, Math.random());
                splineSeries.append(i, Math.random());
                scatterSeries.append(i, Math.random());
            }

            return count;
        }

        // Not a test function, called from test functions
        function clear() {
            lineSeries.clear();
            splineSeries.clear();
            scatterSeries.clear();
        }
    }

    ChartView {
        id: chartView
        anchors.fill: parent

        LineSeries {
            id: lineSeries
            name: "line"

            SignalSpy {
                id: lineSeriesPointAddedSpy
                target: lineSeries
                signalName: "pointAdded"
            }

            SignalSpy {
                id: lineSeriesPointReplacedSpy
                target: lineSeries
                signalName: "pointReplaced"
            }

            SignalSpy {
                id: lineSeriesPointsReplacedSpy
                target: lineSeries
                signalName: "pointsReplaced"
            }

            SignalSpy {
                id: lineSeriesPointRemovedSpy
                target: lineSeries
                signalName: "pointRemoved"
            }
        }

        AreaSeries {
            id: areaSeries
            name: "area"
            upperSeries: lineSeries
        }

        SplineSeries {
            id: splineSeries
            name: "spline"

            SignalSpy {
                id: splineSeriesPointAddedSpy
                target: splineSeries
                signalName: "pointAdded"
            }

            SignalSpy {
                id: splineSeriesPointReplacedSpy
                target: splineSeries
                signalName: "pointReplaced"
            }

            SignalSpy {
                id: splineSeriesPointsReplacedSpy
                target: splineSeries
                signalName: "pointsReplaced"
            }

            SignalSpy {
                id: splineSeriesPointRemovedSpy
                target: splineSeries
                signalName: "pointRemoved"
            }
        }

        ScatterSeries {
            id: scatterSeries
            name: "scatter"

            SignalSpy {
                id: scatterSeriesPointAddedSpy
                target: scatterSeries
                signalName: "pointAdded"
            }

            SignalSpy {
                id: scatterSeriesPointReplacedSpy
                target: scatterSeries
                signalName: "pointReplaced"
            }

            SignalSpy {
                id: scatterSeriesPointsReplacedSpy
                target: scatterSeries
                signalName: "pointsReplaced"
            }

            SignalSpy {
                id: scatterSeriesPointRemovedSpy
                target: scatterSeries
                signalName: "pointRemoved"
            }
        }
    }
}
