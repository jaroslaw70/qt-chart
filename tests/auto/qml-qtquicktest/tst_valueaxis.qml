/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.0
import QtTest 1.0
import QtCommercial.Chart 1.3

Rectangle {
    width: 400
    height: 300

    TestCase {
        id: tc1
        name: "tst_qml-qtquicktest ValueAxis"
        when: windowShown

        // test functions are run in alphabetical order, the name has 'a' so that it
        // will be the first function to execute.
        function test_a_properties() {
            // Default properties
            verify(axisX.min < 0, "AxisX min");
            verify(axisX.max > 0, "AxisX max");
            verify(axisY.min < 0, "AxisY min");
            verify(axisY.max > 0, "AxisY max");
            verify(axisX.tickCount == 5, "AxisX tick count");
            verify(axisY.tickCount == 5, "AxisY tick count");
            verify(axisX.labelFormat == "", "label format");

            // Modify properties
            axisX.tickCount = 3;
            verify(axisX.tickCount == 3, "set tick count");
        }

        function test_functions() {
            // Set the axis ranges to not "nice" ones...
            var min = 0.032456456;
            var max = 10.67845634;
            axisX.min = min;
            axisX.max = max;
            axisY.min = min;
            axisY.max = max;

            // ...And then apply nice numbers and verify the range was changed
            axisX.applyNiceNumbers();
            axisY.applyNiceNumbers();
            verify(axisX.min != min);
            verify(axisX.max != max);
            verify(axisY.min != min);
            verify(axisY.max != max);
        }

        function test_signals() {
            minChangedSpy.clear();
            maxChangedSpy.clear();
            axisX.min = 2;
            compare(minChangedSpy.count, 1, "onMinChanged");
            compare(maxChangedSpy.count, 0, "onMaxChanged");

            axisX.max = 8;
            compare(minChangedSpy.count, 1, "onMinChanged");
            compare(maxChangedSpy.count, 1, "onMaxChanged");

            // restore original values
            axisX.min = 0;
            axisX.max = 10;
            compare(minChangedSpy.count, 2, "onMinChanged");
            compare(maxChangedSpy.count, 2, "onMaxChanged");
        }
    }

    ChartView {
        id: chartView
        anchors.fill: parent

        LineSeries {
            id: lineSeries1
            axisX: ValueAxis {
                id: axisX
            }
            axisY: ValueAxis {
                id: axisY
            }
            XYPoint { x: -1; y: -1 }
            XYPoint { x: 0; y: 0 }
            XYPoint { x: 5; y: 5 }
        }

        SignalSpy {
            id: minChangedSpy
            target: axisX
            signalName: "minChanged"
        }
        SignalSpy {
            id: maxChangedSpy
            target: axisX
            signalName: "maxChanged"
        }
    }
}
