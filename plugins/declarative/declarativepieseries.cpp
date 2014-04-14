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

#include "declarativepieseries.h"
#include "qpieslice.h"
#include "qvpiemodelmapper.h"
#include "qhpiemodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativePieSlice::DeclarativePieSlice(QObject *parent)
    : QPieSlice(parent)
{
    connect(this, SIGNAL(brushChanged()), this, SLOT(handleBrushChanged()));
}

QString DeclarativePieSlice::brushFilename() const
{
    return m_brushFilename;
}

void DeclarativePieSlice::setBrushFilename(const QString &brushFilename)
{
    QImage brushImage(brushFilename);
    if (QPieSlice::brush().textureImage() != brushImage) {
        QBrush brush = QPieSlice::brush();
        brush.setTextureImage(brushImage);
        QPieSlice::setBrush(brush);
        m_brushFilename = brushFilename;
        m_brushImage = brushImage;
        emit brushFilenameChanged(brushFilename);
    }
}

void DeclarativePieSlice::handleBrushChanged()
{
    // If the texture image of the brush has changed along the brush
    // the brush file name needs to be cleared.
    if (!m_brushFilename.isEmpty() && QPieSlice::brush().textureImage() != m_brushImage) {
        m_brushFilename.clear();
        emit brushFilenameChanged(QString(""));
    }
}

// Declarative pie series =========================================================================
DeclarativePieSeries::DeclarativePieSeries(QDECLARATIVE_ITEM *parent) :
    QPieSeries(parent)
{
    connect(this, SIGNAL(added(QList<QPieSlice*>)), this, SLOT(handleAdded(QList<QPieSlice*>)));
    connect(this, SIGNAL(removed(QList<QPieSlice*>)), this, SLOT(handleRemoved(QList<QPieSlice*>)));
}

void DeclarativePieSeries::classBegin()
{
}

void DeclarativePieSeries::componentComplete()
{
    foreach (QObject *child, children()) {
        if (qobject_cast<QPieSlice *>(child)) {
            QPieSeries::append(qobject_cast<QPieSlice *>(child));
        } else if (qobject_cast<QVPieModelMapper *>(child)) {
            QVPieModelMapper *mapper = qobject_cast<QVPieModelMapper *>(child);
            mapper->setSeries(this);
        } else if (qobject_cast<QHPieModelMapper *>(child)) {
            QHPieModelMapper *mapper = qobject_cast<QHPieModelMapper *>(child);
            mapper->setSeries(this);
        }
    }
}

QDECLARATIVE_LIST_PROPERTY<QObject> DeclarativePieSeries::seriesChildren()
{
    return QDECLARATIVE_LIST_PROPERTY<QObject>(this, 0, &DeclarativePieSeries::appendSeriesChildren LIST_PROPERTY_PARAM_DEFAULTS);
}

void DeclarativePieSeries::appendSeriesChildren(QDECLARATIVE_LIST_PROPERTY<QObject> * list, QObject *element)
{
    // Empty implementation; the children are parsed in componentComplete instead
    Q_UNUSED(list);
    Q_UNUSED(element);
}

QPieSlice *DeclarativePieSeries::at(int index)
{
    QList<QPieSlice *> sliceList = slices();
    if (index >= 0 && index < sliceList.count())
        return sliceList[index];

    return 0;
}

QPieSlice *DeclarativePieSeries::find(QString label)
{
    foreach (QPieSlice *slice, slices()) {
        if (slice->label() == label)
            return slice;
    }
    return 0;
}

DeclarativePieSlice *DeclarativePieSeries::append(QString label, qreal value)
{
    DeclarativePieSlice *slice = new DeclarativePieSlice(this);
    slice->setLabel(label);
    slice->setValue(value);
    if (QPieSeries::append(slice))
        return slice;
    delete slice;
    return 0;
}

bool DeclarativePieSeries::remove(QPieSlice *slice)
{
    return QPieSeries::remove(slice);
}

void DeclarativePieSeries::clear()
{
    QPieSeries::clear();
}

void DeclarativePieSeries::handleAdded(QList<QPieSlice *> slices)
{
    foreach (QPieSlice *slice, slices)
        emit sliceAdded(slice);
}

void DeclarativePieSeries::handleRemoved(QList<QPieSlice *> slices)
{
    foreach (QPieSlice *slice, slices)
        emit sliceRemoved(slice);
}

#include "moc_declarativepieseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
