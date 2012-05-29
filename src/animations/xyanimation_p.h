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

#ifndef XYANIMATION_P_H
#define XYANIMATION_P_H

#include "chartanimation_p.h"
#include <QPointF>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class XYChart;

class XYAnimation : public ChartAnimation
{
protected:
    enum Animation { AddPointAnimation, RemovePointAnimation, ReplacePointAnimation, NewAnimation };
public:
    XYAnimation(XYChart *item);
    ~XYAnimation();
    void setup(const QVector<QPointF> &oldPoints, const QVector<QPointF> &newPoints,int index = -1);
    Animation animationType() const { return m_type; };

protected:
    QVariant interpolated(const QVariant &start, const QVariant &end, qreal progress ) const;
    void updateCurrentValue (const QVariant &value );
    void updateState(QAbstractAnimation::State newState, QAbstractAnimation::State oldState);
protected:
    Animation m_type;
    bool m_dirty;
    int m_index;
private:
    XYChart *m_item;
    QVector<QPointF> m_oldPoints;
    QVector<QPointF> m_newPoints;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
