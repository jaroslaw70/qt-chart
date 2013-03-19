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

#include "chartbarcategoryaxisx_p.h"
#include "chartpresenter_p.h"
#include "qbarcategoryaxis_p.h"
#include "chartlayout_p.h"
#include <QFontMetrics>
#include <QDebug>
#include <qmath.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartBarCategoryAxisX::ChartBarCategoryAxisX(QBarCategoryAxis *axis, QGraphicsItem* item)
    : HorizontalAxis(axis, item, true),
      m_categoriesAxis(axis)
{
    QObject::connect(m_categoriesAxis,SIGNAL(categoriesChanged()),this, SLOT(handleCategoriesChanged()));
    handleCategoriesChanged();
}

ChartBarCategoryAxisX::~ChartBarCategoryAxisX()
{
}

QVector<qreal> ChartBarCategoryAxisX::calculateLayout() const
{
    QVector<qreal> points;
    const QRectF& gridRect = gridGeometry();
    qreal range = max() - min();
    const qreal delta = gridRect.width() / range;

    if (delta < 2)
        return points;

    qreal adjustedMin = min() + 0.5;
    qreal offset = (ceil(adjustedMin) - adjustedMin) * delta;

    int count = qFloor(range);
    if (count < 1)
        return points;

    points.resize(count + 2);

    for (int i = 0; i < count + 2; ++i)
        points[i] = offset + (i * delta) + gridRect.left();

    return points;
}

QStringList ChartBarCategoryAxisX::createCategoryLabels(const QVector<qreal>& layout) const
{
    QStringList result ;
    const QRectF &gridRect = gridGeometry();
    qreal d = (max() - min()) / gridRect.width();

    for (int i = 0; i < layout.count() - 1; ++i) {
        qreal x = qFloor((((layout[i] + layout[i + 1]) / 2 - gridRect.left()) * d + min() + 0.5));
        if ((x < m_categoriesAxis->categories().count()) && (x >= 0)) {
            result << m_categoriesAxis->categories().at(x);
        } else {
            // No label for x coordinate
            result << "";
        }
    }
    result << "";
    return result;
}


void ChartBarCategoryAxisX::updateGeometry()
{
    const QVector<qreal>& layout = ChartAxis::layout();
    if (layout.isEmpty())
        return;
    setLabels(createCategoryLabels(layout));
    HorizontalAxis::updateGeometry();
}

void ChartBarCategoryAxisX::handleCategoriesChanged()
{
    QGraphicsLayoutItem::updateGeometry();
    if(presenter()) presenter()->layout()->invalidate();
}

QSizeF ChartBarCategoryAxisX::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(constraint)

    QFontMetrics fn(font());
    QSizeF sh;
    QSizeF base = HorizontalAxis::sizeHint(which, constraint);
    QStringList ticksList = m_categoriesAxis->categories();

    qreal width = 0; // Width is irrelevant for X axes with interval labels
    qreal height = 0;

    switch (which) {
        case Qt::MinimumSize: {
            QRectF boundingRect = labelBoundingRect(fn, "...");
            height = boundingRect.height() + labelPadding();
            height += base.height();
            sh = QSizeF(width, height);
            break;
        }
        case Qt::PreferredSize:{
            int labelHeight = 0;
            foreach (const QString& s, ticksList) {
                QRect rect = labelBoundingRect(fn, s);
                labelHeight = qMax(rect.height(), labelHeight);
            }
            height = labelHeight + labelPadding();
            height += base.height();
            sh = QSizeF(width, height);
            break;
        }
        default:
          break;
    }
    return sh;
}

#include "moc_chartbarcategoryaxisx_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
