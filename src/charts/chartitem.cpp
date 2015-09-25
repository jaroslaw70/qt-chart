/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd
** All rights reserved.
** For any questions to The Qt Company, please use contact form at http://qt.io
**
** This file is part of the Qt Charts module.
**
** Licensees holding valid commercial license for Qt may use this file in
** accordance with the Qt License Agreement provided with the Software
** or, alternatively, in accordance with the terms contained in a written
** agreement between you and The Qt Company.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.io
**
****************************************************************************/

#include <private/chartitem_p.h>
#include <private/qabstractseries_p.h>
#include <private/abstractdomain_p.h>
#include <QtGui/QPainter>

QT_CHARTS_BEGIN_NAMESPACE

ChartItem::ChartItem(QAbstractSeriesPrivate *series,QGraphicsItem* item):
      ChartElement(item),
      m_validData(true),
      m_series(series)
{

}

AbstractDomain* ChartItem::domain() const
{
    return m_series->domain();
}

void ChartItem::handleDomainUpdated()
{
    qWarning() <<  __FUNCTION__<< "Slot not implemented";
}

void ChartItem::reversePainter(QPainter *painter, const QRectF &clipRect)
{
    if (m_series->reverseXAxis()) {
        painter->translate(clipRect.width(), 0);
        painter->scale(-1, 1);
    }

    if (m_series->reverseYAxis()) {
        painter->translate(0, clipRect.height());
        painter->scale(1, -1);
    }
}

#include "moc_chartitem_p.cpp"

QT_CHARTS_END_NAMESPACE
