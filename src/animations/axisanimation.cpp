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

#include "axisanimation_p.h"
#include "chartaxiselement_p.h"
#include "qabstractaxis_p.h"

Q_DECLARE_METATYPE(QVector<qreal>)

QTCOMMERCIALCHART_BEGIN_NAMESPACE


AxisAnimation::AxisAnimation(ChartAxisElement *axis)
    : ChartAnimation(axis),
      m_axis(axis),
      m_type(DefaultAnimation)
{
    setDuration(ChartAnimationDuration);
    setEasingCurve(QEasingCurve::OutQuart);
}

AxisAnimation::~AxisAnimation()
{
}

void AxisAnimation::setAnimationType(Animation type)
{
    if (state() != QAbstractAnimation::Stopped)
        stop();
    m_type = type;
}

void AxisAnimation::setAnimationPoint(const QPointF &point)
{
    if (state() != QAbstractAnimation::Stopped)
        stop();
    m_point = point;
}

void AxisAnimation::setValues(QVector<qreal> &oldLayout, QVector<qreal> &newLayout)
{
    if (state() != QAbstractAnimation::Stopped) stop();

    switch (m_type) {
    case ZoomOutAnimation: {
        QRectF rect = m_axis->gridGeometry();
        oldLayout.resize(newLayout.count());

        for (int i = 0, j = oldLayout.count() - 1; i < (oldLayout.count() + 1) / 2; ++i, --j) {
            oldLayout[i] = m_axis->axis()->orientation() == Qt::Horizontal ? rect.left() : rect.bottom();
            oldLayout[j] = m_axis->axis()->orientation() == Qt::Horizontal ? rect.right() : rect.top();
        }
    }
    break;
    case ZoomInAnimation: {
        int index = qMin(oldLayout.count() * (m_axis->axis()->orientation() == Qt::Horizontal ? m_point.x() : (1 - m_point.y())), newLayout.count() - (qreal)1.0);
        oldLayout.resize(newLayout.count());

        for (int i = 0; i < oldLayout.count(); i++)
            oldLayout[i] = oldLayout[index];
    }
    break;
    case MoveForwardAnimation: {
        oldLayout.resize(newLayout.count());

        for (int i = 0, j = i + 1; i < oldLayout.count() - 1; ++i, ++j)
            oldLayout[i] = oldLayout[j];
    }
    break;
    case MoveBackwordAnimation: {
        oldLayout.resize(newLayout.count());

        for (int i = oldLayout.count() - 1, j = i - 1; i > 0; --i, --j)
            oldLayout[i] = oldLayout[j];
    }
    break;
    default: {
        oldLayout.resize(newLayout.count());
        QRectF rect = m_axis->gridGeometry();
        for (int i = 0, j = oldLayout.count() - 1; i < oldLayout.count(); ++i, --j)
            oldLayout[i] = m_axis->axis()->orientation() == Qt::Horizontal ? rect.left() : rect.top();
    }
    break;
    }

    QVariantAnimation::KeyValues value;
    setKeyValues(value); //workaround for wrong interpolation call
    setKeyValueAt(0.0, qVariantFromValue(oldLayout));
    setKeyValueAt(1.0, qVariantFromValue(newLayout));
}

QVariant AxisAnimation::interpolated(const QVariant &start, const QVariant &end, qreal progress) const
{
    QVector<qreal> startVector = qvariant_cast<QVector<qreal> >(start);
    QVector<qreal> endVecotr = qvariant_cast<QVector<qreal> >(end);
    QVector<qreal> result;

    Q_ASSERT(startVector.count() == endVecotr.count()) ;

    for (int i = 0; i < startVector.count(); i++) {
        qreal value = startVector[i] + ((endVecotr[i] - startVector[i]) * progress); //qBound(0.0, progress, 1.0));
        result << value;
    }
    return qVariantFromValue(result);
}


void AxisAnimation::updateCurrentValue(const QVariant &value)
{
    if (state() != QAbstractAnimation::Stopped) { //workaround
        QVector<qreal> vector = qvariant_cast<QVector<qreal> >(value);
//        Q_ASSERT(vector.count() != 0);
        m_axis->setLayout(vector);
        m_axis->updateGeometry();
    }

}

QTCOMMERCIALCHART_END_NAMESPACE
