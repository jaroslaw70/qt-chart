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

#ifndef CHARTAXISELEMENT_H
#define CHARTAXISELEMENT_H

#include "qchartglobal.h"
#include "chartelement_p.h"
#include "axisanimation_p.h"
#include <QGraphicsItem>
#include <QGraphicsLayoutItem>
#include <QFont>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class ChartPresenter;
class QAbstractAxis;

class ChartAxisElement : public ChartElement, public QGraphicsLayoutItem
{
    Q_OBJECT

    using QGraphicsLayoutItem::setGeometry;
public:
    ChartAxisElement(QAbstractAxis *axis, QGraphicsItem *item, bool intervalAxis = false);
    ~ChartAxisElement();

    virtual QRectF gridGeometry() const = 0;
    virtual void setGeometry(const QRectF &axis, const QRectF &grid) = 0;
    virtual bool isEmpty() = 0;

    void setAnimation(AxisAnimation *animation) { m_animation = animation; }
    AxisAnimation *animation() const { return m_animation; }

    QAbstractAxis *axis() const { return m_axis; }
    void setLayout(QVector<qreal> &layout) { m_layout = layout; }
    QVector<qreal> &layout() { return m_layout; } // Modifiable reference
    inline qreal labelPadding() const { return qreal(1.0); }
    inline qreal titlePadding() const { return qreal(1.0); }
    void setLabels(const QStringList &labels) { m_labelsList = labels; }
    QStringList labels() const { return m_labelsList; }

    qreal min() const;
    qreal max() const;

    QRectF axisGeometry() const { return m_axisRect; }
    void setAxisGeometry(const QRectF &axisGeometry) { m_axisRect = axisGeometry; }

    void axisSelected();

    //this flag indicates that axis is used to show intervals it means labels are in between ticks
    bool intervalAxis() const { return m_intervalAxis; }

    static QStringList createValueLabels(qreal max, qreal min, int ticks, const QString &format);
    static QStringList createLogValueLabels(qreal min, qreal max, qreal base, int ticks, const QString &format);
    static QStringList createDateTimeLabels(qreal max, qreal min, int ticks, const QString &format);

    // from QGraphicsLayoutItem
    QRectF boundingRect() const
    {
        return QRectF();
    }

    // from QGraphicsLayoutItem
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*)
    {
    }

protected:
    virtual QVector<qreal> calculateLayout() const = 0;
    virtual void updateLayout(QVector<qreal> &layout) = 0;

    QList<QGraphicsItem *> gridItems() { return m_grid->childItems(); }
    QList<QGraphicsItem *> labelItems() { return m_labels->childItems(); }
    QList<QGraphicsItem *> shadeItems() { return m_shades->childItems(); }
    QList<QGraphicsItem *> arrowItems() { return m_arrow->childItems(); }
    QGraphicsTextItem *titleItem() const { return m_title.data(); }
    QGraphicsItemGroup *gridGroup() { return m_grid.data(); }
    QGraphicsItemGroup *labelGroup() { return m_labels.data(); }
    QGraphicsItemGroup *shadeGroup() { return m_shades.data(); }
    QGraphicsItemGroup *arrowGroup() { return m_arrow.data(); }

public Q_SLOTS:
    void handleVisibleChanged(bool visible);
    void handleArrowVisibleChanged(bool visible);
    void handleGridVisibleChanged(bool visible);
    void handleLabelsVisibleChanged(bool visible);
    void handleShadesVisibleChanged(bool visible);
    void handleLabelsAngleChanged(int angle);
    virtual void handleShadesBrushChanged(const QBrush &brush) = 0;
    virtual void handleShadesPenChanged(const QPen &pen) = 0;
    virtual void handleArrowPenChanged(const QPen &pen) = 0;
    virtual void handleGridPenChanged(const QPen &pen) = 0;
    void handleLabelsPenChanged(const QPen &pen);
    void handleLabelsBrushChanged(const QBrush &brush);
    void handleLabelsFontChanged(const QFont &font);
    void handleTitlePenChanged(const QPen &pen);
    void handleTitleBrushChanged(const QBrush &brush);
    void handleTitleFontChanged(const QFont &font);
    void handleTitleTextChanged(const QString &title);
    void handleTitleVisibleChanged(bool visible);
    void handleRangeChanged(qreal min, qreal max);

Q_SIGNALS:
    void clicked();

private:
    void connectSlots();

    QAbstractAxis *m_axis;
    AxisAnimation *m_animation;
    QVector<qreal> m_layout;
    QStringList m_labelsList;
    QRectF m_axisRect;
    QScopedPointer<QGraphicsItemGroup> m_grid;
    QScopedPointer<QGraphicsItemGroup> m_arrow;
    QScopedPointer<QGraphicsItemGroup> m_shades;
    QScopedPointer<QGraphicsItemGroup> m_labels;
    QScopedPointer<QGraphicsTextItem> m_title;
    bool m_intervalAxis;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif /* CHARTAXISELEMENT_H */
