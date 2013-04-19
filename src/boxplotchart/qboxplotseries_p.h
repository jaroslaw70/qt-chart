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

//  W A R N I N G
//  -------------
//
// This file is not part of the QtCommercial Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QBOXPLOTSERIES_P_H
#define QBOXPLOTSERIES_P_H

#include "qboxplotseries.h"
#include "qabstractbarseries_p.h"
#include "abstractdomain_p.h"
#include "qbarset.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QBoxPlotSeriesPrivate : public QAbstractSeriesPrivate
{
    Q_OBJECT

public:
    QBoxPlotSeriesPrivate(QBoxPlotSeries *q);
    ~QBoxPlotSeriesPrivate();

    void initializeGraphics(QGraphicsItem* parent);
    void initializeDomain();
    void initializeAxes();
    void initializeAnimations(QChart::AnimationOptions options);
    void initializeTheme(int index, ChartTheme* theme, bool forced = false);

    QList<QLegendMarker*> createLegendMarkers(QLegend *legend);

    virtual QAbstractAxis::AxisType defaultAxisType(Qt::Orientation orientation) const;
    QAbstractAxis* createDefaultAxis(Qt::Orientation orientation) const;

    bool append(QBoxSet *set);
    bool remove(QBoxSet *set);
    bool append(QList<QBoxSet *> sets);
    bool remove(QList<QBoxSet *> sets);
    bool insert(int index, QBoxSet *set);
    QBoxSet *boxsetAt(int index);

    qreal max();
    qreal bottom();

private:
    void populateCategories(QBarCategoryAxis *axis);

Q_SIGNALS:
    void updated();
    void clicked(int index, QBoxSet *barset);
    void updatedBoxes();
    void updatedLayout();
    void restructuredBoxes();

private slots:
    void handleSeriesChange(QAbstractSeries *series);
    void handleSeriesRemove(QAbstractSeries *series);

protected:
    QList<QBoxSet *> m_boxSets;
    QPen m_pen;
    QBrush m_brush;
    int m_index;

private:
    Q_DECLARE_PUBLIC(QBoxPlotSeries)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
