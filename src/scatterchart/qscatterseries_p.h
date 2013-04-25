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

#ifndef QSCATTERSERIES_P_H
#define QSCATTERSERIES_P_H

#include "qxyseries_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QScatterSeriesPrivate: public QXYSeriesPrivate
{
public:
    QScatterSeriesPrivate(QScatterSeries *q);
    void initializeGraphics(QGraphicsItem* parent);
    void initializeTheme(int index, ChartTheme* theme, bool forced = false);
    void initializeAnimations(QtCommercialChart::QChart::AnimationOptions options);

private:
    QScatterSeries::MarkerShape m_shape;
    qreal m_size;
    Q_DECLARE_PUBLIC(QScatterSeries)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
