/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
****************************************************************************/

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef LOGXLOGYPOLARDOMAIN_H
#define LOGXLOGYPOLARDOMAIN_H
#include <private/polardomain_p.h>
#include <QtCharts/private/qchartglobal_p.h>
#include <QtCore/QRectF>
#include <QtCore/QSizeF>

QT_CHARTS_BEGIN_NAMESPACE

class Q_CHARTS_PRIVATE_EXPORT LogXLogYPolarDomain: public PolarDomain
{
    Q_OBJECT
public:
    explicit LogXLogYPolarDomain(QObject *object = 0);
    virtual ~LogXLogYPolarDomain();

    DomainType type() { return AbstractDomain::LogXLogYPolarDomain; }

    void setRange(qreal minX, qreal maxX, qreal minY, qreal maxY);

    friend bool Q_AUTOTEST_EXPORT operator== (const LogXLogYPolarDomain &domain1, const LogXLogYPolarDomain &domain2);
    friend bool Q_AUTOTEST_EXPORT operator!= (const LogXLogYPolarDomain &domain1, const LogXLogYPolarDomain &domain2);
    friend QDebug Q_AUTOTEST_EXPORT operator<<(QDebug dbg, const LogXLogYPolarDomain &domain);

    void zoomIn(const QRectF &rect);
    void zoomOut(const QRectF &rect);
    void move(qreal dx, qreal dy);

    QPointF calculateDomainPoint(const QPointF &point) const;

    bool attachAxis(QAbstractAxis *axis);
    bool detachAxis(QAbstractAxis *axis);

public Q_SLOTS:
    void handleVerticalAxisBaseChanged(qreal baseY);
    void handleHorizontalAxisBaseChanged(qreal baseX);

protected:
    qreal toAngularCoordinate(qreal value, bool &ok) const;
    qreal toRadialCoordinate(qreal value, bool &ok) const;

private:
    qreal m_logLeftX;
    qreal m_logRightX;
    qreal m_logBaseX;
    qreal m_logInnerY;
    qreal m_logOuterY;
    qreal m_logBaseY;
};

QT_CHARTS_END_NAMESPACE

#endif // LOGXLOGYPOLARDOMAIN_H
