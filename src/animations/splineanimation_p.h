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

#ifndef SPLINEANIMATION_P_H
#define SPLINEANIMATION_P_H
#include "xyanimation_p.h"
#include <QPointF>

typedef  QPair<QVector<QPointF >, QVector<QPointF > >  SplineVector;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class SplineChartItem;

class SplineAnimation : public XYAnimation
{
public:
    SplineAnimation(SplineChartItem *item);
    ~SplineAnimation();
    void setup(QVector<QPointF> &oldPoints, QVector<QPointF> &newPoints, QVector<QPointF> &oldContorlPoints, QVector<QPointF> &newControlPoints, int index = -1);

protected:
    QVariant interpolated(const QVariant &start, const QVariant &end, qreal progress) const;
    void updateCurrentValue(const QVariant &value);
    void updateState(QAbstractAnimation::State newState, QAbstractAnimation::State oldState);

private:
    SplineVector m_oldSpline;
    SplineVector m_newSpline;
    SplineChartItem *m_item;
    bool m_valid;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
