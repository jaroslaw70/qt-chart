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

#ifndef DECLARATIVEPOLARCHART_H
#define DECLARATIVEPOLARCHART_H

#include <QtCore/QtGlobal>
#include "shared_defines.h"

#ifdef CHARTS_FOR_QUICK2
#include <QtQuick/QQuickItem>
#else
#include <QtDeclarative/QDeclarativeItem>
#endif

#include "declarativechart.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class DeclarativePolarChart : public DeclarativeChart
{
    Q_OBJECT
public:
    DeclarativePolarChart(QDECLARATIVE_ITEM *parent = 0);
    ~DeclarativePolarChart();
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // DECLARATIVEPOLARCHART_H
