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
#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets/QWidget>
#include <QtCharts/QPieSeries>

QT_BEGIN_NAMESPACE
class QTimer;
QT_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void updateRotation();
    void explodeSlice(bool exploded);

private:
    QList<QPieSeries *> m_donuts;
    QTimer *updateTimer;
};

#endif // WIDGET_H
