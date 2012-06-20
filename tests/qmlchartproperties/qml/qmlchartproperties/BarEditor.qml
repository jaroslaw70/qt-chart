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

Flow {
    id: flow
    spacing: 5
    flow: Flow.TopToBottom
    property variant series

    Button {
        text: "visible"
        onClicked: series.visible = !series.visible;
    }
    Button {
        text: "labels visible"
        onClicked: series.labelsVisible = !series.labelsVisible;
    }
    Button {
        text: "bar width +"
        onClicked: series.barWidth += 0.1;
    }
    Button {
        text: "bar width -"
        onClicked: series.barWidth -= 0.1;
    }
    Button {
        text: "append set"
        onClicked: {
            var count = series.count;
            series.append("set" + count, [0, 0.1 * count, 0.2 * count, 0.3 * count, 0.4 * count, 0.5 * count, 0.6 * count]);
        }
    }
    Button {
        text: "insert set"
        onClicked: {
            var count = series.count;
            series.insert(count - 1, "set" + count, [0, 0.1 * count, 0.2 * count, 0.3 * count, 0.4 * count, 0.5 * count, 0.6 * count]);
        }
    }
    Button {
        text: "remove set"
        onClicked: series.remove(series.at(series.count - 1));
    }
    Button {
        text: "clear sets"
        onClicked: series.clear();
    }
    Button {
        text: "set 1 color"
        onClicked: series.at(0).color = main.nextColor();
    }
    Button {
        text: "set 1 border color"
        onClicked: series.at(0).borderColor = main.nextColor();
    }
    Button {
        text: "set 1 label color"
        onClicked: series.at(0).labelColor = main.nextColor();
    }
    Button {
        text: "set 1 font size +"
        onClicked: series.at(0).labelFont.pixelSize += 1;
    }
    Button {
        text: "set 1 font size -"
        onClicked: series.at(0).labelFont.pixelSize -= 1;
    }
}
