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

#ifndef POLARCHARTDATETIMEAXISANGULAR_P_H
#define POLARCHARTDATETIMEAXISANGULAR_P_H

#include "polarchartaxisangular_p.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QDateTimeAxis;

class PolarChartDateTimeAxisAngular : public PolarChartAxisAngular
{
    Q_OBJECT
public:
    PolarChartDateTimeAxisAngular(QDateTimeAxis *axis, QGraphicsItem *item);
    ~PolarChartDateTimeAxisAngular();

    virtual QVector<qreal> calculateLayout() const;
    virtual void createAxisLabels(const QVector<qreal> &layout);

private Q_SLOTS:
    void handleTickCountChanged(int tick);
    void handleFormatChanged(const QString &format);
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // POLARCHARTDATETIMEAXISANGULAR_P_H
