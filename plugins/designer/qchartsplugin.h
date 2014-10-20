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

#ifndef QCHARTSPLUGIN_H
#define QCHARTSPLUGIN_H

#include <QtDesigner/QDesignerCustomWidgetInterface>

class QChartsPlugin: public QObject, public QDesignerCustomWidgetInterface
{
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidgetInterface")

    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    QChartsPlugin(QObject *parent = 0);
    ~QChartsPlugin();

    QString name() const;
    QString includeFile() const;
    QString group() const;
    QIcon icon() const;
    QString toolTip() const;
    QString whatsThis() const;
    bool isContainer() const;
    QWidget *createWidget(QWidget *parent);
    QString domXml() const;
};

#endif /* QCHARTSPLUGIN_H */
