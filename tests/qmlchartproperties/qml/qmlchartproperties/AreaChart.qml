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
import QtCommercial.Chart 1.0

ChartView {
    title: "area series"
    anchors.fill: parent

    property variant series: areaSeries

    AreaSeries {
        id: areaSeries
        name: "area 1"
        axisX: CategoriesAxis {
            id: categoriesAxis
            categories: ["2000", "2001", "2002", "2003", "2004", "2005", "2006", "2007",
                "2008", "2009", "2010", "2011" ]
        }
        upperSeries: LineSeries {
            XYPoint { x: 0; y: 1 }
            XYPoint { x: 1; y: 1 }
            XYPoint { x: 2; y: 3 }
            XYPoint { x: 3; y: 3 }
            XYPoint { x: 4; y: 2 }
            XYPoint { x: 5; y: 0 }
            XYPoint { x: 6; y: 2 }
            XYPoint { x: 7; y: 1 }
            XYPoint { x: 8; y: 2 }
            XYPoint { x: 9; y: 1 }
            XYPoint { x: 10; y: 3 }
            XYPoint { x: 11; y: 3 }
        }
        lowerSeries: LineSeries {
            XYPoint { x: 0; y: 0 }
            XYPoint { x: 1; y: 0 }
            XYPoint { x: 2; y: 0 }
            XYPoint { x: 3; y: 0 }
            XYPoint { x: 4; y: 0 }
            XYPoint { x: 5; y: 0 }
            XYPoint { x: 6; y: 0 }
            XYPoint { x: 7; y: 0 }
            XYPoint { x: 8; y: 0 }
            XYPoint { x: 9; y: 0 }
            XYPoint { x: 10; y: 0 }
            XYPoint { x: 11; y: 0 }
        }

        onNameChanged:              console.log("areaSeries.onNameChanged: " + name);
        onVisibleChanged:           console.log("areaSeries.onVisibleChanged: " + visible);
        onClicked:                  console.log(name + ".onClicked: " + point.x + ", " + point.y);
        onSelected:                 console.log("areaSeries.onSelected");
        onColorChanged:             console.log("areaSeries.onColorChanged: " + color);
        onBorderColorChanged:       console.log("areaSeries.onBorderColorChanged: " + borderColor);
//        onCountChanged:             console.log("areaSeries.onCountChanged: " + count);
    }
}
