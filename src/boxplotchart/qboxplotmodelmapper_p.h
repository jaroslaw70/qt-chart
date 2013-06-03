/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

#ifndef QBOXPLOTMODELMAPPER_P_H
#define QBOXPLOTMODELMAPPER_P_H

#include <QObject>
#include "qboxplotmodelmapper.h"

class QModelIndex;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QBoxSet;

class QBoxPlotModelMapperPrivate : public QObject
{
    Q_OBJECT
public:
    explicit QBoxPlotModelMapperPrivate(QBoxPlotModelMapper *q);

public Q_SLOTS:
    // for the model
    void modelUpdated(QModelIndex topLeft, QModelIndex bottomRight);
    void modelHeaderDataUpdated(Qt::Orientation orientation, int first, int last);
    void modelRowsAdded(QModelIndex parent, int start, int end);
    void modelRowsRemoved(QModelIndex parent, int start, int end);
    void modelColumnsAdded(QModelIndex parent, int start, int end);
    void modelColumnsRemoved(QModelIndex parent, int start, int end);
    void handleModelDestroyed();

    // for the series
    void boxSetsAdded(QList<QBoxSet *> sets);
    void boxSetsRemoved(QList<QBoxSet *> sets);
    void valuesAdded(int index, int count);
    void valuesRemoved(int index, int count);
    void boxValueChanged(int index);
    void handleSeriesDestroyed();

    void initializeBoxFromModel();

private:
    QBoxSet *boxSet(QModelIndex index);
    QModelIndex boxModelIndex(int boxSection, int posInBox);
    void insertData(int start, int end);
    void removeData(int start, int end);
    void blockModelSignals(bool block = true);
    void blockSeriesSignals(bool block = true);

private:
    QBoxPlotSeries *m_series;
    QList<QBoxSet *> m_boxSets;
    QAbstractItemModel *m_model;
    int m_first;
    int m_count;
    Qt::Orientation m_orientation;
    int m_firstBoxSetSection;
    int m_lastBoxSetSection;
    bool m_seriesSignalsBlock;
    bool m_modelSignalsBlock;

private:
    QBoxPlotModelMapper *q_ptr;
    Q_DECLARE_PUBLIC(QBoxPlotModelMapper)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QBOXPLOTMODELMAPPER_P_H
