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

//  W A R N I N G
//  -------------
//
// This file is not part of the Qt Enterprise Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef QPIESLICE_P_H
#define QPIESLICE_P_H

#include <QtCore/QObject>
#include <QtCharts/QPieSlice>
#include <private/pieslicedata_p.h>

QT_CHARTS_BEGIN_NAMESPACE
class QPieSeries;

class QPieSlicePrivate : public QObject
{
    Q_OBJECT

public:
    QPieSlicePrivate(QPieSlice *parent);
    ~QPieSlicePrivate();

    static QPieSlicePrivate *fromSlice(QPieSlice *slice);

    void setPen(const QPen &pen, bool themed);
    void setBrush(const QBrush &brush, bool themed);
    void setLabelBrush(const QBrush &brush, bool themed);
    void setLabelFont(const QFont &font, bool themed);

    void setPercentage(qreal percentage);
    void setStartAngle(qreal angle);
    void setAngleSpan(qreal span);

Q_SIGNALS:
    void labelPositionChanged();
    void explodedChanged();
    void labelArmLengthFactorChanged();
    void explodeDistanceFactorChanged();

private:
    friend class QPieSeries;
    friend class QPieSeriesPrivate;
    friend class ChartThemeManager;
    friend class PieChartItem;

    QPieSlice * const q_ptr;
    Q_DECLARE_PUBLIC(QPieSlice)

    PieSliceData m_data;
    QPieSeries *m_series;
};

QT_CHARTS_END_NAMESPACE

#endif // QPIESLICE_P_H
