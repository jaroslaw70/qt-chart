/****************************************************************************
**
** Copyright (C) 2013 Digia Plc
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

#ifndef QSTACKEDBARSERIES_H
#define QSTACKEDBARSERIES_H

#include <QStringList>
#include <qabstractbarseries.h>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QStackedBarSeriesPrivate;

class QTCOMMERCIALCHART_EXPORT QStackedBarSeries : public QAbstractBarSeries
{
    Q_OBJECT
public:
    explicit QStackedBarSeries(QObject *parent = 0);
    ~QStackedBarSeries();
    QAbstractSeries::SeriesType type() const;

private:
    Q_DECLARE_PRIVATE(QStackedBarSeries)
    Q_DISABLE_COPY(QStackedBarSeries)
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QSTACKEDBARSERIES_H
