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

#ifndef CHART_H
#define CHART_H

#include "qchartglobal.h"
#include <QObject>
#include <QRect>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartAnimator;
class ChartPresenter;
class ChartAnimation;
class Domain;

class Chart: public QObject
{
    Q_OBJECT
public:
    explicit Chart(ChartPresenter *presenter);

public Q_SLOTS:
    virtual void handleGeometryChanged(const QRectF& rect);
    virtual void handleDomainChanged(qreal minX,qreal maxX,qreal minY,qreal maxY);

    void setAnimator(ChartAnimator* animator);
    ChartAnimator* animator() const;
    void setPresenter(ChartPresenter *presenter);
    ChartPresenter* presenter() const;
    void setDomain(Domain *domain);
    Domain* domain() const;
    virtual ChartAnimation* animation() const { return 0; };

private:
    ChartAnimator* m_animator;
    ChartPresenter* m_presenter;
    Domain* m_domain;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
