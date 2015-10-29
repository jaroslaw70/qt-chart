/******************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Charts module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/

import QtQuick 2.0
import QtCharts 2.0

Item {
    anchors.fill: parent

    //![1]
    PolarChartView {
        title: "Numerical Data for Dummies"
        anchors.fill: parent
        legend.visible: false
        antialiasing: true

        LineSeries {
            axisRadial: CategoryAxis {
                min: 0
                max: 30
                CategoryRange {
                    label: "critical"
                    endValue: 2
                }
                CategoryRange {
                    label: "low"
                    endValue: 7
                }
                CategoryRange {
                    label: "normal"
                    endValue: 12
                }
                CategoryRange {
                    label: "high"
                    endValue: 18
                }
                CategoryRange {
                    label: "extremely high"
                    endValue: 30
                }
            }

            axisAngular: ValueAxis {
                tickCount: 13
            }

            XYPoint { x: 0; y: 4.3 }
            XYPoint { x: 1; y: 4.1 }
            XYPoint { x: 2; y: 4.7 }
            XYPoint { x: 3; y: 3.9 }
            XYPoint { x: 4; y: 5.2 }
            XYPoint { x: 5; y: 5.3 }
            XYPoint { x: 6; y: 6.1 }
            XYPoint { x: 7; y: 7.7 }
            XYPoint { x: 8; y: 12.9 }
            XYPoint { x: 9; y: 19.2 }
        }
    }
    //![1]
}
