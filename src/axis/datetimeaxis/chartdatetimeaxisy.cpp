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

#include "chartdatetimeaxisy_p.h"
#include "chartpresenter_p.h"
#include "qdatetimeaxis.h"
#include <QGraphicsLayout>
#include <QFontMetrics>
#include <QDateTime>
#include <qmath.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartDateTimeAxisY::ChartDateTimeAxisY(QDateTimeAxis *axis,ChartPresenter *presenter) : VerticalAxis(axis,presenter),
m_tickCount(0),m_axis(axis)
{
}

ChartDateTimeAxisY::~ChartDateTimeAxisY()
{
}

QVector<qreal> ChartDateTimeAxisY::calculateLayout() const
{
    Q_ASSERT(m_tickCount>=2);

    QVector<qreal> points;
    points.resize(m_tickCount);
    const QRectF& gridRect = gridGeometry();
    const qreal deltaY = gridRect.height()/(m_tickCount-1);
    for (int i = 0; i < m_tickCount; ++i) {
        int y = i * -deltaY + gridRect.bottom();
        points[i] = y;
    }

    return points;
}

void ChartDateTimeAxisY::updateGeometry()
{
    const QVector<qreal> &layout = ChartAxis::layout();
    if(layout.isEmpty()) return;
    setLabels(createDateTimeLabels(m_axis->format(),layout.size()));
    VerticalAxis::updateGeometry();
}

void ChartDateTimeAxisY::handleAxisUpdated()
{
    m_tickCount = m_axis->tickCount();
    ChartAxis::handleAxisUpdated();
}

QSizeF ChartDateTimeAxisY::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    Q_UNUSED(constraint)

    QFontMetrics fn(font());
    QSizeF sh;

      switch (which) {
        case Qt::MinimumSize:
            sh = QSizeF(fn.boundingRect("...").width(),fn.height());
            break;
        case Qt::PreferredSize:{

            const QVector<qreal>& layout = ChartAxis::layout();
            if(layout.isEmpty()) break;
            QStringList ticksList;


            qreal width=0;
            qreal height=0;

            for (int i = 0; i < ticksList.size(); ++i)
            {
                QRectF rect = fn.boundingRect(ticksList.at(i));
                width+=rect.width();
                height+=qMax(rect.height()+labelPadding(),height);
            }
            sh = QSizeF(width,height);
            break;
        }
        default:
          break;
      }

      return sh;
}

QTCOMMERCIALCHART_END_NAMESPACE
