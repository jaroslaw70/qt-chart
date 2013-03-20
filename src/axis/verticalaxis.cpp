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

#include "verticalaxis_p.h"
#include "qabstractaxis.h"
#include <QFontMetrics>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

VerticalAxis::VerticalAxis(QAbstractAxis *axis, QGraphicsItem* item, bool intervalAxis)
    : ChartAxis(axis, item, intervalAxis)
{

}

VerticalAxis::~VerticalAxis()
{

}

void VerticalAxis::updateGeometry()
{
    const QVector<qreal> &layout = ChartAxis::layout();

    if (layout.isEmpty())
        return;

    QStringList labelList = labels();

    QList<QGraphicsItem *> lines = lineItems();
    QList<QGraphicsItem *> labels = labelItems();
    QList<QGraphicsItem *> shades = shadeItems();
    QList<QGraphicsItem *> axis = arrowItems();
    QGraphicsSimpleTextItem* title = titleItem();

    Q_ASSERT(labels.size() == labelList.size());
    Q_ASSERT(layout.size() == labelList.size());

    const QRectF &axisRect = axisGeometry();
    const QRectF &gridRect = gridGeometry();

    qreal height = axisRect.bottom();


    //arrow
    QGraphicsLineItem *arrowItem = static_cast<QGraphicsLineItem*>(axis.at(0));

    //arrow position
    if (alignment()==Qt::AlignLeft)
        arrowItem->setLine( axisRect.right() , gridRect.top(), axisRect.right(), gridRect.bottom());
    else if(alignment()==Qt::AlignRight)
        arrowItem->setLine( axisRect.left() , gridRect.top(), axisRect.left(), gridRect.bottom());

    QFontMetrics fn(font());

    //title
    int titlePad = 0;
    QRectF titleBoundingRect;
    if (!titleText().isEmpty() && titleItem()->isVisible()) {
        QFontMetrics fn(title->font());
        int size(0);
        size = gridRect.height();
        QString titleText = this->titleText();

        if (fn.boundingRect(titleText).width() > size) {
            QString string = titleText + "...";
            while (fn.boundingRect(string).width() > size && string.length() > 3)
            string.remove(string.length() - 4, 1);
            title->setText(string);
        }
        else {
            title->setText(titleText);
        }

        titlePad = titlePadding();
        titleBoundingRect = title->boundingRect();

        QPointF center = gridRect.center() - titleBoundingRect.center();
        if (alignment() == Qt::AlignLeft) {
            title->setPos(axisRect.left() - titleBoundingRect.width() / 2 + titleBoundingRect.height() / 2 + titlePad, center.y());
        }
        else if (alignment() == Qt::AlignRight) {
            title->setPos(axisRect.right() - titleBoundingRect.width() / 2 - titleBoundingRect.height() / 2 - titlePad, center.y());
        }
        title->setTransformOriginPoint(titleBoundingRect.center());
        title->setRotation(270);
    }

    for (int i = 0; i < layout.size(); ++i) {

        //items
        QGraphicsLineItem *gridItem = static_cast<QGraphicsLineItem *>(lines.at(i));
        QGraphicsLineItem *tickItem = static_cast<QGraphicsLineItem *>(axis.at(i + 1));
        QGraphicsSimpleTextItem *labelItem = static_cast<QGraphicsSimpleTextItem *>(labels.at(i));

        //grid line
        gridItem->setLine(gridRect.left() , layout[i], gridRect.right(), layout[i]);

        //label text wrapping
        QString text = labelList.at(i);
        QRectF boundingRect = labelBoundingRect(fn, text);

        qreal size = axisRect.right() - axisRect.left() - labelPadding() - titleBoundingRect.height() - (titlePad * 2);
        if (boundingRect.width() > size) {
            QString label = text + "...";
            while (boundingRect.width() > size && label.length() > 3) {
                label.remove(label.length() - 4, 1);
                boundingRect = labelBoundingRect(fn, label);
            }
            labelItem->setText(label);
        } else {
            labelItem->setText(text);
        }

        //label transformation origin point
        const QRectF &rect = labelItem->boundingRect();

        QPointF center = rect.center();
        labelItem->setTransformOriginPoint(center.x(), center.y());
        int widthDiff = rect.width() - boundingRect.width();

        //ticks and label position
        if (alignment() == Qt::AlignLeft) {
            labelItem->setPos(axisRect.right() - rect.width() + (widthDiff / 2) - labelPadding(), layout[i] - center.y());
            tickItem->setLine(axisRect.right() - labelPadding(), layout[i], axisRect.right(), layout[i]);
        } else if (alignment() == Qt::AlignRight) {
            labelItem->setPos(axisRect.left() + labelPadding() - (widthDiff / 2), layout[i] - center.y());
            tickItem->setLine(axisRect.left(), layout[i], axisRect.left() + labelPadding(), layout[i]);
        }

        //label in beetwen
        if(intervalAxis()&& i+1!=layout.size()) {
            const qreal delta = (layout[i+1] - layout[i])/2;
            labelItem->setPos(labelItem->pos().x() , layout[i] + delta - center.y());
        }

        //label overlap detection - compensate one pixel for rounding errors
        if (labelItem->pos().y() + boundingRect.height() > height ||
            (labelItem->pos().y() + (boundingRect.height() / 2.0) - 1.0) > axisRect.bottom() ||
            labelItem->pos().y() + (boundingRect.height() / 2.0) < (axisRect.top() - 1.0)) {
            labelItem->setVisible(false);
        }
        else {
            labelItem->setVisible(true);
            height=labelItem->pos().y();
        }

        //shades
        if ((i + 1) % 2 && i > 1) {
            QGraphicsRectItem *rectItem = static_cast<QGraphicsRectItem *>(shades.at(i / 2 - 1));
            rectItem->setRect(gridRect.left(), layout[i], gridRect.width(), layout[i - 1] - layout[i]);
        }

        // check if the grid line and the axis tick should be shown
        qreal y = gridItem->line().p1().y();
        if ((y < gridRect.top() || y > gridRect.bottom()))
        {
            gridItem->setVisible(false);
            tickItem->setVisible(false);
        }else{
            gridItem->setVisible(true);
            tickItem->setVisible(true);
        }

    }
    //begin/end grid line in case labels between
    if (intervalAxis()) {
        QGraphicsLineItem *gridLine;
        gridLine = static_cast<QGraphicsLineItem *>(lines.at(layout.size()));
        gridLine->setLine(gridRect.left(), gridRect.top(), gridRect.right(), gridRect.top());
        gridLine->setVisible(true);
        gridLine = static_cast<QGraphicsLineItem*>(lines.at(layout.size()+1));
        gridLine->setLine(gridRect.left(), gridRect.bottom(), gridRect.right(), gridRect.bottom());
        gridLine->setVisible(true);
    }
}

QSizeF VerticalAxis::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{

    Q_UNUSED(constraint);
    QFontMetrics fn(titleFont());
    QSizeF sh(0,0);

    if (titleText().isEmpty() || !titleItem()->isVisible())
        return sh;

    switch (which) {
    case Qt::MinimumSize:
            sh = QSizeF(fn.height() + (titlePadding() * 2), fn.boundingRect("...").width());
        break;
    case Qt::MaximumSize:
    case Qt::PreferredSize:
            sh = QSizeF(fn.height() + (titlePadding() * 2), fn.boundingRect(axis()->titleText()).width());
        break;
    default:
        break;
    }

    return sh;
}

QTCOMMERCIALCHART_END_NAMESPACE
