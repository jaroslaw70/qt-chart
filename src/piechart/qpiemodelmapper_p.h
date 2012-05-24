#ifndef QPIEMODELMAPPER_P_H
#define QPIEMODELMAPPER_P_H

#include "qpiemodelmapper.h"
#include <QObject>

class QModelIndex;
class QAbstractItemModel;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QPieModelMapper;
class QPieSeries;
class QPieSlice;

class QPieModelMapperPrivate : public QObject
{
    Q_OBJECT

public:
    QPieModelMapperPrivate(QPieModelMapper *q);

public Q_SLOTS:
    // for the model
    void modelUpdated(QModelIndex topLeft, QModelIndex bottomRight);
    void modelRowsAdded(QModelIndex parent, int start, int end);
    void modelRowsRemoved(QModelIndex parent, int start, int end);
    void modelColumnsAdded(QModelIndex parent, int start, int end);
    void modelColumnsRemoved(QModelIndex parent, int start, int end);

    // for the series
    void slicesAdded(QList<QPieSlice*> slices);
    void slicesRemoved(QList<QPieSlice*> slices);
    void sliceLabelChanged();
    void sliceValueChanged();

    void initializePieFromModel();

private:
    QPieSlice* pieSlice(QModelIndex index) const;
    QModelIndex valueModelIndex(int slicePos);
    QModelIndex labelModelIndex(int slicePos);
    void insertData(int start, int end);
    void removeData(int start, int end);

    void blockModelSignals(bool block = true);
    void blockSeriesSignals(bool block = true);

private:
    bool m_seriesSignalsBlock;
    bool m_modelSignalsBlock;
    QPieSeries *m_series;
    QList<QPieSlice*> m_slices;
    QAbstractItemModel *m_model;
    int m_first;
    int m_count;
    Qt::Orientation m_orientation;
    int m_valuesIndex;
    int m_labelsIndex;

private:

    QPieModelMapper *q_ptr;
    Q_DECLARE_PUBLIC(QPieModelMapper)
    friend class QPieSeriesPrivate;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QPIEMODELMAPPER_P_H
