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

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Enterprise Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QABSTRACTSERIES_P_H
#define QABSTRACTSERIES_P_H

#include "qabstractseries.h"
#include "qchart.h"
#include "abstractdomain_p.h"

class QGraphicsItem;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartPresenter;
class ChartElement;
class LegendMarker;
class QLegend;
class ChartDataSet;
class QAbstractAxis;
class QLegendMarker;
class ChartTheme;
class ChartAnimation;
class ChartItem;
class BoxPlotChartItem;

class QAbstractSeriesPrivate : public QObject
{
    Q_OBJECT
public:
    QAbstractSeriesPrivate(QAbstractSeries *q);
    ~QAbstractSeriesPrivate();

    virtual void initializeDomain() = 0;
    virtual void initializeAxes() = 0;
    virtual void initializeTheme(int index, ChartTheme* theme, bool forced = false) = 0;
    virtual void initializeGraphics(QGraphicsItem* parent) = 0;
    virtual void initializeAnimations(QChart::AnimationOptions options) = 0;

    virtual QList<QLegendMarker*> createLegendMarkers(QLegend* legend) = 0;

    virtual QAbstractAxis::AxisType defaultAxisType(Qt::Orientation) const = 0;
    virtual QAbstractAxis* createDefaultAxis(Qt::Orientation) const = 0;

    ChartItem* chartItem() { return m_item.data(); }

    virtual void setDomain(AbstractDomain* domain);
    AbstractDomain* domain() { return m_domain.data(); }

    QChart* chart() { return m_chart; }

Q_SIGNALS:
    void countChanged();

protected:
    QAbstractSeries *q_ptr;
    QChart *m_chart;
    QScopedPointer<ChartItem> m_item;
    QList<QAbstractAxis*> m_axes;
private:
    QScopedPointer<AbstractDomain> m_domain;
    QString m_name;
    bool m_visible;
    qreal m_opacity;

    friend class QAbstractSeries;
    friend class ChartDataSet;
    friend class ChartPresenter;
    friend class QLegendPrivate;
    friend class BoxPlotChartItem;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
