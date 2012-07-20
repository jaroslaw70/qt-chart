/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
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

#include "tst_qabstractaxis.h"

Q_DECLARE_METATYPE(QPen)
Q_DECLARE_METATYPE(Qt::Orientation)

void tst_QAbstractAxis::initTestCase()
{
}

void tst_QAbstractAxis::cleanupTestCase()
{
}

void tst_QAbstractAxis::init(QAbstractAxis* axis, QAbstractSeries* series)
{
    m_axis = axis;
    m_series = series;
    m_view = new QChartView(new QChart());
    m_chart = m_view->chart();
}

void tst_QAbstractAxis::cleanup()
{
    delete m_view;
    m_view = 0;
    m_chart = 0;
    m_axis = 0;
}

void tst_QAbstractAxis::qabstractaxis()
{
    QCOMPARE(m_axis->axisPen(), QPen());
    //TODO QCOMPARE(m_axis->axisPenColor(), QColor());
    QCOMPARE(m_axis->gridLinePen(), QPen());
    QCOMPARE(m_axis->isArrowVisible(), true);
    QCOMPARE(m_axis->isGridLineVisible(), true);
    QCOMPARE(m_axis->isVisible(), false);
    QCOMPARE(m_axis->labelsAngle(), 0);
    QCOMPARE(m_axis->labelsBrush(), QBrush());
    //TODO QCOMPARE(m_axis->labelsColor(), QColor());
    QCOMPARE(m_axis->labelsFont(), QFont());
    QCOMPARE(m_axis->labelsPen(), QPen());
    QCOMPARE(m_axis->labelsVisible(), true);
    QCOMPARE(m_axis->orientation(), Qt::Orientation(0));
    m_axis->setArrowVisible(false);
    m_axis->setAxisPen(QPen());
    m_axis->setAxisPenColor(QColor());
    m_axis->setGridLinePen(QPen());
    m_axis->setGridLineVisible(false);
    m_axis->setLabelsAngle(-1);
    m_axis->setLabelsBrush(QBrush());
    m_axis->setLabelsColor(QColor());
    m_axis->setLabelsFont(QFont());
    m_axis->setLabelsPen(QPen());
    m_axis->setLabelsVisible(false);
    m_axis->setMax(QVariant());
    m_axis->setMin(QVariant());
    m_axis->setRange(QVariant(), QVariant());
    m_axis->setShadesBorderColor(QColor());
    m_axis->setShadesBrush(QBrush());
    m_axis->setShadesColor(QColor());
    m_axis->setShadesPen(QPen());
    m_axis->setShadesVisible(false);
    m_axis->setVisible(false);
    //TODO QCOMPARE(m_axis->shadesBorderColor(), QColor());
    //TODO QCOMPARE(m_axis->shadesBrush(), QBrush());
    //TODO QCOMPARE(m_axis->shadesColor(), QColor());
    QCOMPARE(m_axis->shadesPen(), QPen());
    QCOMPARE(m_axis->shadesVisible(), false);
    m_axis->show();
    m_axis->hide();
}

void tst_QAbstractAxis::axisPen_data()
{
    QTest::addColumn<QPen>("axisPen");
    QTest::newRow("null") << QPen();
    QTest::newRow("blue") << QPen(Qt::blue);
    QTest::newRow("black") << QPen(Qt::black);
    QTest::newRow("red") << QPen(Qt::red);
}

void tst_QAbstractAxis::axisPen()
{
    QFETCH(QPen, axisPen);

    QSignalSpy spy0(m_axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(m_axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(m_axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(m_axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(m_axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(m_axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(m_axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(m_axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(m_axis, SIGNAL(visibleChanged(bool)));

    m_axis->setAxisPen(axisPen);
    QCOMPARE(m_axis->axisPen(), axisPen);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);

    m_chart->setAxisX(m_axis, m_series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    //TODO QCOMPARE(m_axis->axisPen(), axisPen);
}

void tst_QAbstractAxis::axisPenColor_data()
{
}

void tst_QAbstractAxis::axisPenColor()
{
    QSKIP("Test is not implemented. This is depreciated function", SkipAll);
}

void tst_QAbstractAxis::gridLinePen_data()
{

    QTest::addColumn<QPen>("gridLinePen");
    QTest::newRow("null") << QPen();
    QTest::newRow("blue") << QPen(Qt::blue);
    QTest::newRow("black") << QPen(Qt::black);
    QTest::newRow("red") << QPen(Qt::red);

}

void tst_QAbstractAxis::gridLinePen()
{
    QFETCH(QPen, gridLinePen);

    QSignalSpy spy0(m_axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(m_axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(m_axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(m_axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(m_axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(m_axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(m_axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(m_axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(m_axis, SIGNAL(visibleChanged(bool)));

    m_axis->setGridLinePen(gridLinePen);
    QCOMPARE(m_axis->gridLinePen(), gridLinePen);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);

    m_chart->setAxisX(m_axis, m_series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    //TODO QCOMPARE(m_axis->gridLinePen(), gridLinePen);
}

void tst_QAbstractAxis::arrowVisible_data()
{
    QTest::addColumn<bool>("arrowVisible");
    QTest::newRow("true") << true;
    QTest::newRow("false") << false;
}

void tst_QAbstractAxis::arrowVisible()
{
    QFETCH(bool, arrowVisible);

    m_axis->setArrowVisible(!arrowVisible);

    QSignalSpy spy0(m_axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(m_axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(m_axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(m_axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(m_axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(m_axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(m_axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(m_axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(m_axis, SIGNAL(visibleChanged(bool)));

    m_axis->setArrowVisible(arrowVisible);
    QCOMPARE(m_axis->isArrowVisible(), arrowVisible);

    QCOMPARE(spy0.count(), 1);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);

    m_chart->setAxisX(m_axis, m_series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    QCOMPARE(m_axis->isArrowVisible(), arrowVisible);
}

void tst_QAbstractAxis::gridLineVisible_data()
{
    QTest::addColumn<bool>("gridLineVisible");
    QTest::newRow("true") << true;
    QTest::newRow("false") << false;
}

void tst_QAbstractAxis::gridLineVisible()
{
    QFETCH(bool, gridLineVisible);

    m_axis->setGridLineVisible(!gridLineVisible);

    QSignalSpy spy0(m_axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(m_axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(m_axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(m_axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(m_axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(m_axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(m_axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(m_axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(m_axis, SIGNAL(visibleChanged(bool)));

    m_axis->setGridLineVisible(gridLineVisible);
    QCOMPARE(m_axis->isGridLineVisible(), gridLineVisible);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 1);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);

    m_chart->setAxisX(m_axis, m_series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    QCOMPARE(m_axis->isGridLineVisible(), gridLineVisible);

}

void tst_QAbstractAxis::visible_data()
{
    QTest::addColumn<bool>("visible");
    QTest::newRow("true") << true;
    QTest::newRow("false") << false;
}

void tst_QAbstractAxis::visible()
{
    QFETCH(bool, visible);

    m_axis->setVisible(!visible);

    QSignalSpy spy0(m_axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(m_axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(m_axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(m_axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(m_axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(m_axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(m_axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(m_axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(m_axis, SIGNAL(visibleChanged(bool)));

    m_axis->setVisible(visible);
    QCOMPARE(m_axis->isVisible(), visible);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 1);

    m_chart->setAxisX(m_axis, m_series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    QCOMPARE(m_axis->isVisible(), true);
}

void tst_QAbstractAxis::labelsAngle_data()
{
    QTest::addColumn<int>("labelsAngle");
    QTest::newRow("0") << 0;
    QTest::newRow("45") << 45;
    QTest::newRow("90") << 90;
}

void tst_QAbstractAxis::labelsAngle()
{
    QFETCH(int, labelsAngle);

    QSignalSpy spy0(m_axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(m_axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(m_axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(m_axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(m_axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(m_axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(m_axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(m_axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(m_axis, SIGNAL(visibleChanged(bool)));

    m_axis->setLabelsAngle(labelsAngle);
    QCOMPARE(m_axis->labelsAngle(), labelsAngle);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);

    m_chart->setAxisX(m_axis, m_series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    QCOMPARE(m_axis->labelsAngle(), labelsAngle);
}

void tst_QAbstractAxis::labelsBrush_data()
{
    QTest::addColumn<QBrush>("labelsBrush");
    QTest::newRow("null") << QBrush();
    QTest::newRow("blue") << QBrush(Qt::blue);
    QTest::newRow("black") << QBrush(Qt::black);

}

void tst_QAbstractAxis::labelsBrush()
{

    QFETCH(QBrush, labelsBrush);

    QSignalSpy spy0(m_axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(m_axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(m_axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(m_axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(m_axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(m_axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(m_axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(m_axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(m_axis, SIGNAL(visibleChanged(bool)));

    m_axis->setLabelsBrush(labelsBrush);
    QCOMPARE(m_axis->labelsBrush(), labelsBrush);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    //TODO QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);

    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    QCOMPARE(m_axis->labelsBrush(), labelsBrush);

}

void tst_QAbstractAxis::labelsColor_data()
{

}

void tst_QAbstractAxis::labelsColor()
{
    QSKIP("Test is not implemented. This is depreciated function", SkipAll);
}

void tst_QAbstractAxis::labelsFont_data()
{
    QTest::addColumn<QFont>("labelsFont");
    QTest::newRow("null") << QFont();
    QTest::newRow("serif") << QFont("SansSerif");
}

void tst_QAbstractAxis::labelsFont()
{

    QFETCH(QFont, labelsFont);

    QSignalSpy spy0(m_axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(m_axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(m_axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(m_axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(m_axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(m_axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(m_axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(m_axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(m_axis, SIGNAL(visibleChanged(bool)));

    m_axis->setLabelsFont(labelsFont);
    QCOMPARE(m_axis->labelsFont(), labelsFont);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);

    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    QCOMPARE(m_axis->labelsFont(), labelsFont);

}

void tst_QAbstractAxis::labelsPen_data()
{
    QTest::addColumn<QPen>("labelsPen");
    QTest::newRow("null") << QPen();
    QTest::newRow("blue") << QPen(Qt::blue);
    QTest::newRow("black") << QPen(Qt::black);
    QTest::newRow("red") << QPen(Qt::red);
}

void tst_QAbstractAxis::labelsPen()
{
    QFETCH(QPen, labelsPen);

    QSignalSpy spy0(m_axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(m_axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(m_axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(m_axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(m_axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(m_axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(m_axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(m_axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(m_axis, SIGNAL(visibleChanged(bool)));

    m_axis->setLabelsPen(labelsPen);
    QCOMPARE(m_axis->labelsPen(), labelsPen);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);

    m_chart->setAxisX(m_axis, m_series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    //TODO QCOMPARE(m_axis->labelsPen(), labelsPen);
}

void tst_QAbstractAxis::labelsVisible_data()
{
    QTest::addColumn<bool>("labelsVisible");
    QTest::newRow("true") << true;
    QTest::newRow("false") << false;
}

void tst_QAbstractAxis::labelsVisible()
{
    QFETCH(bool, labelsVisible);

    m_axis->setLabelsVisible(!labelsVisible);

    QSignalSpy spy0(m_axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(m_axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(m_axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(m_axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(m_axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(m_axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(m_axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(m_axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(m_axis, SIGNAL(visibleChanged(bool)));

    m_axis->setLabelsVisible(labelsVisible);
    QCOMPARE(m_axis->labelsVisible(), labelsVisible);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 1);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);

    m_chart->setAxisX(m_axis, m_series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    QCOMPARE(m_axis->labelsVisible(), labelsVisible);
}

void tst_QAbstractAxis::orientation_data()
{
    QTest::addColumn<Qt::Orientation>("orientation");
    QTest::newRow("Vertical") << Qt::Vertical;
    QTest::newRow("Horizontal") << Qt::Horizontal;
}

void tst_QAbstractAxis::orientation()
{
    QFETCH(Qt::Orientation, orientation);

    QSignalSpy spy0(m_axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(m_axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(m_axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(m_axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(m_axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(m_axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(m_axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(m_axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(m_axis, SIGNAL(visibleChanged(bool)));

    if(orientation==Qt::Vertical){
        m_chart->setAxisY(m_axis,m_series);
    }else{
        m_chart->setAxisX(m_axis,m_series);
    }
    QCOMPARE(m_axis->orientation(), orientation);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 1);

    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    QCOMPARE(m_axis->orientation(), orientation);
}

void tst_QAbstractAxis::setMax_data()
{
    //just check if it does not crash
    QTest::addColumn<QVariant>("max");
    QTest::newRow("something") << QVariant("something");
    QTest::newRow("1.0") << QVariant(1.0);
}

void tst_QAbstractAxis::setMax()
{
    QFETCH(QVariant, max);
    m_axis->setMax(max);
}

void tst_QAbstractAxis::setMin_data()
{
    //just check if it does not crash
    QTest::addColumn<QVariant>("min");
    QTest::newRow("something") << QVariant("something");
    QTest::newRow("1.0") << QVariant(1.0);
}

// public void setMin(QVariant const& min)
void tst_QAbstractAxis::setMin()
{
    QFETCH(QVariant, min);
    m_axis->setMin(min);
}

void tst_QAbstractAxis::setRange_data()
{
    //just check if it does not crash
    QTest::addColumn<QVariant>("min");
    QTest::addColumn<QVariant>("max");
    QTest::newRow("something") << QVariant("something0") << QVariant("something1");
    QTest::newRow("-1 1") << QVariant(-1.0) << QVariant(1.0);
}

// public void setRange(QVariant const& min, QVariant const& max)
void tst_QAbstractAxis::setRange()
{

    QFETCH(QVariant, min);
    QFETCH(QVariant, max);
    m_axis->setRange(min,max);
}

void tst_QAbstractAxis::shadesBorderColor_data()
{

}

void tst_QAbstractAxis::shadesBorderColor()
{
    QSKIP("Test is not implemented. This is depreciated function", SkipAll);
}

void tst_QAbstractAxis::shadesBrush_data()
{
    QTest::addColumn<QBrush>("shadesBrush");
    QTest::newRow("null") << QBrush();
    QTest::newRow("blue") << QBrush(Qt::blue);
    QTest::newRow("black") << QBrush(Qt::black);
}

void tst_QAbstractAxis::shadesBrush()
{
    QFETCH(QBrush, shadesBrush);

    QSignalSpy spy0(m_axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(m_axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(m_axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(m_axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(m_axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(m_axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(m_axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(m_axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(m_axis, SIGNAL(visibleChanged(bool)));

    m_axis->setShadesBrush(shadesBrush);
    QCOMPARE(m_axis->shadesBrush(), shadesBrush);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    //TODO QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);

    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    QCOMPARE(m_axis->shadesBrush(), shadesBrush);
}

void tst_QAbstractAxis::shadesColor_data()
{
}

// public QColor shadesColor() const
void tst_QAbstractAxis::shadesColor()
{
    QSKIP("Test is not implemented. This is depreciated function", SkipAll);
}

void tst_QAbstractAxis::shadesPen_data()
{
    QTest::addColumn<QPen>("shadesPen");
    QTest::newRow("null") << QPen();
    QTest::newRow("blue") << QPen(Qt::blue);
    QTest::newRow("black") << QPen(Qt::black);
    QTest::newRow("red") << QPen(Qt::red);
}

void tst_QAbstractAxis::shadesPen()
{
    QFETCH(QPen, shadesPen);

    QSignalSpy spy0(m_axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(m_axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(m_axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(m_axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(m_axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(m_axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(m_axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(m_axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(m_axis, SIGNAL(visibleChanged(bool)));

    m_axis->setShadesPen(shadesPen);
    QCOMPARE(m_axis->shadesPen(), shadesPen);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 0);

    m_chart->setAxisX(m_axis, m_series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    QCOMPARE(m_axis->shadesPen(), shadesPen);
}

void tst_QAbstractAxis::shadesVisible_data()
{
    QTest::addColumn<bool>("shadesVisible");
    QTest::newRow("true") << true;
    QTest::newRow("false") << false;
}

void tst_QAbstractAxis::shadesVisible()
{
    QFETCH(bool, shadesVisible);

    m_axis->setShadesVisible(!shadesVisible);

    QSignalSpy spy0(m_axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(m_axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(m_axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(m_axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(m_axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(m_axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(m_axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(m_axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(m_axis, SIGNAL(visibleChanged(bool)));

    m_axis->setShadesVisible(shadesVisible);
    QCOMPARE(m_axis->shadesVisible(), shadesVisible);

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 1);
    QCOMPARE(spy8.count(), 0);

    m_chart->setAxisX(m_axis, m_series);
    m_view->show();
    QTest::qWaitForWindowShown(m_view);
    QCOMPARE(m_axis->shadesVisible(), shadesVisible);
}

void tst_QAbstractAxis::show_data()
{

}

void tst_QAbstractAxis::show()
{
    m_axis->hide();
    QCOMPARE(m_axis->isVisible(), false);

    QSignalSpy spy0(m_axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(m_axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(m_axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(m_axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(m_axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(m_axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(m_axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(m_axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(m_axis, SIGNAL(visibleChanged(bool)));

    m_axis->show();

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 1);
    QCOMPARE(m_axis->isVisible(), true);
}

void tst_QAbstractAxis::hide_data()
{

}

void tst_QAbstractAxis::hide()
{
    m_axis->show();
    QCOMPARE(m_axis->isVisible(),true);

    QSignalSpy spy0(m_axis, SIGNAL(arrowVisibleChanged(bool)));
    QSignalSpy spy1(m_axis, SIGNAL(colorChanged(QColor)));
    QSignalSpy spy2(m_axis, SIGNAL(gridVisibleChanged(bool)));
    QSignalSpy spy3(m_axis, SIGNAL(labelsColorChanged(QColor)));
    QSignalSpy spy4(m_axis, SIGNAL(labelsVisibleChanged(bool)));
    QSignalSpy spy5(m_axis, SIGNAL(shadesBorderColorChanged(QColor)));
    QSignalSpy spy6(m_axis, SIGNAL(shadesColorChanged(QColor)));
    QSignalSpy spy7(m_axis, SIGNAL(shadesVisibleChanged(bool)));
    QSignalSpy spy8(m_axis, SIGNAL(visibleChanged(bool)));

    m_axis->hide();

    QCOMPARE(spy0.count(), 0);
    QCOMPARE(spy1.count(), 0);
    QCOMPARE(spy2.count(), 0);
    QCOMPARE(spy3.count(), 0);
    QCOMPARE(spy4.count(), 0);
    QCOMPARE(spy5.count(), 0);
    QCOMPARE(spy6.count(), 0);
    QCOMPARE(spy7.count(), 0);
    QCOMPARE(spy8.count(), 1);
    QCOMPARE(m_axis->isVisible(),false);
}












