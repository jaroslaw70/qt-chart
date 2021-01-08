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

#include <private/chartbarcategoryaxisy_p.h>
#include <private/chartpresenter_p.h>
#include <private/qbarcategoryaxis_p.h>
#include <private/abstractchartlayout_p.h>
#include <QtCore/QtMath>
#include <QtCore/QDebug>

QT_CHARTS_BEGIN_NAMESPACE

ChartBarCategoryAxisY::ChartBarCategoryAxisY(QBarCategoryAxis *axis, QGraphicsItem* item)
    : VerticalAxis(axis, item, true),
      m_categoriesAxis(axis)
{
    QObject::connect( m_categoriesAxis,SIGNAL(categoriesChanged()),this, SLOT(handleCategoriesChanged()));
    handleCategoriesChanged();
}

ChartBarCategoryAxisY::~ChartBarCategoryAxisY()
{
}

QVector<qreal> ChartBarCategoryAxisY::calculateLayout() const
{
    QVector<qreal> points;
    const QRectF& gridRect = gridGeometry();
    qreal range = max() - min();
    const qreal delta = gridRect.height() / range;

    if (delta < 2)
        return points;

    qreal adjustedMin = min() + 0.5;
    qreal offset = (qRound(adjustedMin) - adjustedMin) * delta;

    int count = qFloor(range);
    if (count < 1)
        return points;

    points.resize(count + 2);

    for (int i = 0; i < count + 2; ++i)
        points[i] =  gridRect.bottom() - (qreal(i) * delta) - offset;

    return points;
}

QStringList ChartBarCategoryAxisY::createCategoryLabels(const QVector<qreal>& layout) const
{
    QStringList result;
    const QRectF &gridRect = gridGeometry();
    qreal d = (max() - min()) / gridRect.height();

    for (int i = 0; i < layout.count() - 1; ++i) {
        int x = qFloor(((gridRect.height() - (layout[i + 1] + layout[i]) / 2 + gridRect.top()) * d + min() + 0.5));
        if ((x < m_categoriesAxis->categories().count()) && (x >= 0)) {
            result << m_categoriesAxis->categories().at(x);
        } else {
            // No label for x coordinate
            result << QString();
        }
    }
    result << QString();
    return result;
}

void ChartBarCategoryAxisY::updateGeometry()
{
    const QVector<qreal>& layout = ChartAxisElement::layout();
    if (layout.isEmpty())
        return;
    setLabels(createCategoryLabels(layout));
    VerticalAxis::updateGeometry();
}

void ChartBarCategoryAxisY::handleCategoriesChanged()
{
    QGraphicsLayoutItem::updateGeometry();
    if(presenter()) presenter()->layout()->invalidate();
}

QSizeF ChartBarCategoryAxisY::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(constraint)

    QSizeF sh;
    QSizeF base = VerticalAxis::sizeHint(which, constraint);
    QStringList ticksList = m_categoriesAxis->categories();
    qreal width = 0;
    qreal height = 0; // Height is irrelevant for Y axes with interval labels

    switch (which) {
        case Qt::MinimumSize: {
            QRectF boundingRect = ChartPresenter::textBoundingRect(axis()->labelsFont(),
                                                                   QStringLiteral("..."),
                                                                   axis()->labelsAngle());
            width = boundingRect.width() + labelPadding() + base.width() + 1.0;
            if (base.width() > 0.0)
                width += labelPadding();
            sh = QSizeF(width, height);
            break;
        }
        case Qt::PreferredSize:{
            qreal labelWidth = 0.0;
            foreach (const QString& s, ticksList) {
                QRectF rect = ChartPresenter::textBoundingRect(axis()->labelsFont(), s, axis()->labelsAngle());
                labelWidth = qMax(rect.width(), labelWidth);
            }
            width = labelWidth + labelPadding() + base.width() + 1.0;
            if (base.width() > 0.0)
                width += labelPadding();
            sh = QSizeF(width, height);
            break;
        }
        default:
          break;
      }
      return sh;
}

QT_CHARTS_END_NAMESPACE

#include "moc_chartbarcategoryaxisy_p.cpp"
