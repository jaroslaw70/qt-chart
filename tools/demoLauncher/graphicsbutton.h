/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Enterprise Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Enterprise licenses may use this file in
** accordance with the Qt Enterprise License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef GRAPHICSBUTTON_H
#define GRAPHICSBUTTON_H

#include <QWidget>
#include <QDir>

class QProcess;

class GraphicsButton : public QWidget
{
    Q_OBJECT
public:
    explicit GraphicsButton(const QString &path, QDir appFolder, const QString &app, QWidget *parent = 0);
    ~GraphicsButton();

protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    QPixmap m_pixmap;
    QString m_path;
    QDir m_appFolder;
    QString m_app;
    QProcess *m_demoApp;
};

#endif // GRAPHICSBUTTON_H
