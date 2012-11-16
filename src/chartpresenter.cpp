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
#include "chartpresenter_p.h"
#include "qchart.h"
#include "chartitem_p.h"
#include "qchart_p.h"
#include "qabstractaxis.h"
#include "qabstractaxis_p.h"
#include "chartdataset_p.h"
#include "chartanimation_p.h"
#include "qabstractseries_p.h"
#include "qareaseries.h"
#include "chartaxis_p.h"
#include "chartbackground_p.h"
#include "chartlayout_p.h"
#include "charttitle_p.h"
#include <QTimer>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartPresenter::ChartPresenter(QChart *chart)
    : QObject(chart),
      m_chart(chart),
      m_options(QChart::NoAnimation),
      m_state(ShowState),
      m_layout(new ChartLayout(this)),
      m_background(0),
      m_title(0)
{

}

ChartPresenter::~ChartPresenter()
{

}

void ChartPresenter::setGeometry(const QRectF rect)
{
	if(m_rect != rect) {
		m_rect=rect;
		foreach (ChartItem *chart, m_chartItems){
			chart->domain()->setSize(rect.size());
			chart->setPos(rect.topLeft());
		}
	}
}

QRectF ChartPresenter::geometry() const
{
	return m_rect;
}

void ChartPresenter::handleAxisAdded(QAbstractAxis *axis)
{
    qDebug()<<__FUNCTION__;
    axis->d_ptr->initializeGraphics(rootItem());
    axis->d_ptr->initializeAnimations(m_options);
    ChartAxis *item = axis->d_ptr->axisItem();
    item->setPresenter(this);
    item->setThemeManager(m_chart->d_ptr->m_themeManager);
    m_axisItems<<item;
    m_axes<<axis;
    m_layout->invalidate();
}

void ChartPresenter::handleAxisRemoved(QAbstractAxis *axis)
{
    qDebug()<<__FUNCTION__;
    ChartAxis *item  = axis->d_ptr->m_item.take();
    item->hide();
    item->disconnect();
    item->deleteLater();
    m_axisItems.removeAll(item);
    m_axes.removeAll(axis);
    m_layout->invalidate();
}


void ChartPresenter::handleSeriesAdded(QAbstractSeries *series)
{
    qDebug()<<__FUNCTION__;
    series->d_ptr->initializeGraphics(rootItem());
    series->d_ptr->initializeAnimations(m_options);
    ChartItem *chart = series->d_ptr->chartItem();
    chart->setPresenter(this);
    chart->setThemeManager(m_chart->d_ptr->m_themeManager);
    chart->domain()->setSize(m_rect.size());
    chart->setPos(m_rect.topLeft());
    chart->handleDomainUpdated(); //this could be moved to intializeGraphics when animator is refactored
    m_chartItems<<chart;
    m_series<<series;
    m_layout->invalidate();
}

void ChartPresenter::handleSeriesRemoved(QAbstractSeries *series)
{
    qDebug()<<__FUNCTION__;
    ChartItem *chart  = series->d_ptr->m_item.take();
    chart->hide();
    chart->disconnect();
    chart->deleteLater();
    m_chartItems.removeAll(chart);
    m_series.removeAll(series);
    m_layout->invalidate();
}

void ChartPresenter::setAnimationOptions(QChart::AnimationOptions options)
{
    if (m_options != options) {
        m_options = options;

        foreach(QAbstractSeries* series, m_series){
            series->d_ptr->initializeAnimations(m_options);
        }
        foreach(QAbstractAxis* axis, m_axes){
            axis->d_ptr->initializeAnimations(m_options);
        }
    }
}

void ChartPresenter::setState(State state,QPointF point)
{
	m_state=state;
	m_statePoint=point;
}

QChart::AnimationOptions ChartPresenter::animationOptions() const
{
    return m_options;
}

void ChartPresenter::createBackgroundItem()
{
    if (!m_background) {
        m_background = new ChartBackground(rootItem());
        m_background->setPen(Qt::NoPen);
        m_background->setZValue(ChartPresenter::BackgroundZValue);
    }
}

void ChartPresenter::createTitleItem()
{
    if (!m_title) {
        m_title = new ChartTitle(rootItem());
        m_title->setZValue(ChartPresenter::BackgroundZValue);
    }
}


void ChartPresenter::handleAnimationFinished()
{
    m_animations.removeAll(qobject_cast<ChartAnimation *>(sender()));
    if (m_animations.empty())
        emit animationsFinished();
}

void ChartPresenter::startAnimation(ChartAnimation *animation)
{
    if (animation->state() != QAbstractAnimation::Stopped) animation->stop();
    QObject::connect(animation, SIGNAL(finished()), this, SLOT(handleAnimationFinished()), Qt::UniqueConnection);
    if (!m_animations.isEmpty())
        m_animations.append(animation);
    QTimer::singleShot(0, animation, SLOT(start()));
}

void ChartPresenter::setBackgroundBrush(const QBrush &brush)
{
    createBackgroundItem();
    m_background->setBrush(brush);
    m_layout->invalidate();
}

QBrush ChartPresenter::backgroundBrush() const
{
    if (!m_background)
        return QBrush();
    return m_background->brush();
}

void ChartPresenter::setBackgroundPen(const QPen &pen)
{
    createBackgroundItem();
    m_background->setPen(pen);
    m_layout->invalidate();
}

QPen ChartPresenter::backgroundPen() const
{
    if (!m_background)
        return QPen();
    return m_background->pen();
}

void ChartPresenter::setTitle(const QString &title)
{
    createTitleItem();
    m_title->setText(title);
    m_layout->invalidate();
}

QString ChartPresenter::title() const
{
    if (!m_title)
        return QString();
    return m_title->text();
}

void ChartPresenter::setTitleFont(const QFont &font)
{
    createTitleItem();
    m_title->setFont(font);
    m_layout->invalidate();
}

QFont ChartPresenter::titleFont() const
{
    if (!m_title)
        return QFont();
    return m_title->font();
}

void ChartPresenter::setTitleBrush(const QBrush &brush)
{
    createTitleItem();
    m_title->setBrush(brush);
    m_layout->invalidate();
}

QBrush ChartPresenter::titleBrush() const
{
    if (!m_title)
        return QBrush();
    return m_title->brush();
}

void ChartPresenter::setBackgroundVisible(bool visible)
{
    createBackgroundItem();
    m_background->setVisible(visible);
}


bool ChartPresenter::isBackgroundVisible() const
{
    if (!m_background)
        return false;
    return m_background->isVisible();
}

void ChartPresenter::setBackgroundDropShadowEnabled(bool enabled)
{
    createBackgroundItem();
    m_background->setDropShadowEnabled(enabled);
}

bool ChartPresenter::isBackgroundDropShadowEnabled() const
{
    if (!m_background)
        return false;
    return m_background->isDropShadowEnabled();
}


ChartLayout *ChartPresenter::layout()
{
    return m_layout;
}

QLegend *ChartPresenter::legend()
{
    return m_chart->legend();
}

void ChartPresenter::setVisible(bool visible)
{
    m_chart->setVisible(visible);
}

ChartBackground *ChartPresenter::backgroundElement()
{
    return m_background;
}

QList<ChartAxis *>  ChartPresenter::axisItems() const
{
    return m_axisItems;
}

QList<ChartItem *> ChartPresenter::chartItems() const
{
    return m_chartItems;
}

ChartTitle *ChartPresenter::titleElement()
{
    return m_title;
}

#include "moc_chartpresenter_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
