/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
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

#ifndef QPIELEGENDMARKER_H
#define QPIELEGENDMARKER_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QLegendMarker>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

QT_CHARTS_BEGIN_NAMESPACE

class QPieLegendMarkerPrivate;

class QT_CHARTS_EXPORT QPieLegendMarker : public QLegendMarker
{
    Q_OBJECT

public:
    explicit QPieLegendMarker(QPieSeries *series, QPieSlice *slice, QLegend *legend, QObject *parent = 0);
    virtual ~QPieLegendMarker();

    virtual LegendMarkerType type() { return LegendMarkerTypePie; }

    // Related series and slice
    virtual QPieSeries* series();
    QPieSlice* slice();

protected:
    QPieLegendMarker(QPieLegendMarkerPrivate &d, QObject *parent = 0);

private:
    Q_DECLARE_PRIVATE(QPieLegendMarker)
    Q_DISABLE_COPY(QPieLegendMarker)

};

QT_CHARTS_END_NAMESPACE
#endif // QPIELEGENDMARKER_H