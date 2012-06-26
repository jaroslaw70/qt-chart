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
#include "qchart_p.h"
#include "qabstractaxis.h"
#include "chartdataset_p.h"
#include "charttheme_p.h"
#include "chartanimator_p.h"
#include "chartanimation_p.h"
#include "qabstractseries_p.h"
#include "qareaseries.h"
#include "chartaxis_p.h"
#include "chartaxisx_p.h"
#include "chartaxisy_p.h"
#include "areachartitem_p.h"
#include "chartbackground_p.h"
#include "chartlayout_p.h"
#include <QTimer>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

ChartPresenter::ChartPresenter(QChart* chart,ChartDataSet* dataset):QObject(chart),
m_chart(chart),
m_animator(0),
m_dataset(dataset),
m_chartTheme(0),
m_options(QChart::NoAnimation),
m_state(ShowState),
m_layout(new ChartLayout(this)),
m_backgroundItem(0),
m_titleItem(0)
{

}

ChartPresenter::~ChartPresenter()
{
    delete m_chartTheme;
}

void ChartPresenter::setGeometry(const QRectF& rect)
{

    Q_ASSERT(rect.isValid());

    if(m_rect!=rect) {
           m_rect=rect;
           emit geometryChanged(m_rect);
    }
}

void ChartPresenter::handleAxisAdded(QAbstractAxis* axis,Domain* domain)
{
    ChartAxis* item;

    if(axis == m_dataset->axisX()){
        item = new ChartAxisX(axis,this);
    }else{
        item = new ChartAxisY(axis,this);
    }

    if(m_options.testFlag(QChart::GridAxisAnimations)){
        item->setAnimator(m_animator);
        item->setAnimation(new AxisAnimation(item));
    }

    if(axis==m_dataset->axisX()){
        m_chartTheme->decorate(axis,true);
        QObject::connect(domain,SIGNAL(rangeXChanged(qreal,qreal,int)),item,SLOT(handleRangeChanged(qreal,qreal,int)));
        //initialize
        item->handleRangeChanged(domain->minX(),domain->maxX(),domain->tickXCount());

    }
    else{
        m_chartTheme->decorate(axis,false);
        QObject::connect(domain,SIGNAL(rangeYChanged(qreal,qreal,int)),item,SLOT(handleRangeChanged(qreal,qreal,int)));
        //initialize
        item->handleRangeChanged(domain->minY(),domain->maxY(),domain->tickYCount());
    }

    QObject::connect(this,SIGNAL(geometryChanged(QRectF)),item,SLOT(handleGeometryChanged(QRectF)));
    //initialize
    if(m_rect.isValid()) item->handleGeometryChanged(m_rect);
    m_axisItems.insert(axis, item);
}

void ChartPresenter::handleAxisRemoved(QAbstractAxis* axis)
{
    ChartAxis* item = m_axisItems.take(axis);
    Q_ASSERT(item);
    if(m_animator) m_animator->removeAnimation(item);
    delete item;
}


void ChartPresenter::handleSeriesAdded(QAbstractSeries* series,Domain* domain)
{
    Chart *item = series->d_ptr->createGraphics(this);
    Q_ASSERT(item);
    QObject::connect(this,SIGNAL(geometryChanged(QRectF)),item,SLOT(handleGeometryChanged(QRectF)));
    QObject::connect(domain,SIGNAL(domainChanged(qreal,qreal,qreal,qreal)),item,SLOT(handleDomainChanged(qreal,qreal,qreal,qreal)));
    //initialize
    item->handleDomainChanged(domain->minX(),domain->maxX(),domain->minY(),domain->maxY());
    if(m_rect.isValid()) item->handleGeometryChanged(m_rect);
    m_chartItems.insert(series,item);
}

void ChartPresenter::handleSeriesRemoved(QAbstractSeries* series)
{
    Chart* item = m_chartItems.take(series);
    Q_ASSERT(item);
    if(m_animator) {
        //small hack to handle area animations
        if(series->type() == QAbstractSeries::SeriesTypeArea){
            QAreaSeries* areaSeries = static_cast<QAreaSeries*>(series);
            AreaChartItem* area = static_cast<AreaChartItem*>(item);
            m_animator->removeAnimation(area->upperLineItem());
            if(areaSeries->lowerSeries())  m_animator->removeAnimation(area->lowerLineItem());
        }else
            m_animator->removeAnimation(item);
    }
    delete item;
}

void ChartPresenter::setTheme(QChart::ChartTheme theme,bool force)
{
    if(m_chartTheme && m_chartTheme->id() == theme) return;
    delete m_chartTheme;
    m_chartTheme = ChartTheme::createTheme(theme);
    m_chartTheme->setForced(force);
    m_chartTheme->decorate(m_chart);
    m_chartTheme->decorate(m_chart->legend());
    resetAllElements();

    // We do not want "force" to stay on.
    // Bar/pie are calling decorate when adding/removing slices/bars which means
    // that to preserve users colors "force" must not be on.
    m_chartTheme->setForced(false);
}

QChart::ChartTheme ChartPresenter::theme()
{
    return m_chartTheme->id();
}

void ChartPresenter::setAnimationOptions(QChart::AnimationOptions options)
{
    if(m_options!=options) {

        m_options=options;

        if(m_options!=QChart::NoAnimation && !m_animator) {
            m_animator= new ChartAnimator(this);
        }
        resetAllElements();
    }

}

void ChartPresenter::resetAllElements()
{
    QList<QAbstractAxis*> axisList = m_axisItems.uniqueKeys();
    QList<QAbstractSeries *> seriesList = m_chartItems.uniqueKeys();

    foreach(QAbstractAxis *axis, axisList) {
        handleAxisRemoved(axis);
        handleAxisAdded(axis,m_dataset->domain(axis));
    }
    foreach(QAbstractSeries *series, seriesList) {
        handleSeriesRemoved(series);
        handleSeriesAdded(series,m_dataset->domain(series));
//        m_dataset->removeSeries(series);
//        m_dataset->addSeries(series);
    }
}

void ChartPresenter::zoomIn(qreal factor)
{
    QRectF rect = geometry();
    rect.setWidth(rect.width()/factor);
    rect.setHeight(rect.height()/factor);
    rect.moveCenter(geometry().center());
    zoomIn(rect);
}

void ChartPresenter::zoomIn(const QRectF& rect)
{
    QRectF r = rect.normalized();
    r.translate(-geometry().topLeft());
    if (!r.isValid())
        return;

    m_state = ZoomInState;
    m_statePoint = QPointF(r.center().x()/geometry().width(),r.center().y()/geometry().height());
    m_dataset->zoomInDomain(r,geometry().size());
    m_state = ShowState;
}

void ChartPresenter::zoomOut(qreal factor)
{
    m_state = ZoomOutState;

    QRectF chartRect;
    chartRect.setSize(geometry().size());

    QRectF rect;
    rect.setSize(chartRect.size()/factor);
    rect.moveCenter(chartRect.center());
    if (!rect.isValid())
        return;
    m_statePoint = QPointF(rect.center().x()/geometry().width(),rect.center().y()/geometry().height());
    m_dataset->zoomOutDomain(rect, chartRect.size());
    m_state = ShowState;
}

void ChartPresenter::scroll(qreal dx,qreal dy)
{
    if(dx<0) m_state=ScrollLeftState;
    if(dx>0) m_state=ScrollRightState;
    if(dy<0) m_state=ScrollUpState;
    if(dy>0) m_state=ScrollDownState;

    m_dataset->scrollDomain(dx,dy,geometry().size());
    m_state = ShowState;
}

QChart::AnimationOptions ChartPresenter::animationOptions() const
{
    return m_options;
}

void ChartPresenter::createBackgroundItem()
{
    if (!m_backgroundItem) {
        m_backgroundItem = new ChartBackground(rootItem());
        m_backgroundItem->setPen(Qt::NoPen);
        m_backgroundItem->setZValue(ChartPresenter::BackgroundZValue);
    }
}

void ChartPresenter::createTitleItem()
{
    if (!m_titleItem) {
        m_titleItem = new QGraphicsSimpleTextItem(rootItem());
        m_titleItem->setZValue(ChartPresenter::BackgroundZValue);
    }
}


void ChartPresenter::handleAnimationFinished()
{
   m_animations.removeAll(qobject_cast<ChartAnimation*>(sender()));
   if(m_animations.empty()) emit animationsFinished();
}

void ChartPresenter::startAnimation(ChartAnimation* animation)
{
    if (animation->state() != QAbstractAnimation::Stopped) animation->stop();
    QObject::connect(animation, SIGNAL(finished()),this,SLOT(handleAnimationFinished()),Qt::UniqueConnection);
    if(!m_animations.isEmpty()){
        m_animations.append(animation);
    }
    QTimer::singleShot(0, animation, SLOT(start()));
}

QGraphicsRectItem* ChartPresenter::backgroundItem()
{
    return m_backgroundItem;
}

void ChartPresenter::setBackgroundBrush(const QBrush& brush)
{
    createBackgroundItem();
    m_backgroundItem->setBrush(brush);
    m_layout->invalidate();
}

QBrush ChartPresenter::backgroundBrush() const
{
    if (!m_backgroundItem) return QBrush();
    return m_backgroundItem->brush();
}

void ChartPresenter::setBackgroundPen(const QPen& pen)
{
    createBackgroundItem();
    m_backgroundItem->setPen(pen);
    m_layout->invalidate();
}

QPen ChartPresenter::backgroundPen() const
{
    if (!m_backgroundItem) return QPen();
    return m_backgroundItem->pen();
}

QGraphicsItem* ChartPresenter::titleItem()
{
    return m_titleItem;
}

void ChartPresenter::setTitle(const QString& title)
{
    createTitleItem();
    m_titleItem->setText(title);
    m_layout->invalidate();
}

QString ChartPresenter::title() const
{
    if (!m_titleItem) return QString();
    return m_titleItem->text();
}

void ChartPresenter::setTitleFont(const QFont& font)
{
    createTitleItem();
    m_titleItem->setFont(font);
    m_layout->invalidate();
}

QFont ChartPresenter::titleFont() const
{
    if (!m_titleItem)  return QFont();
    return m_titleItem->font();
}

void ChartPresenter::setTitleBrush(const QBrush &brush)
{
    createTitleItem();
    m_titleItem->setBrush(brush);
    m_layout->invalidate();
}

QBrush ChartPresenter::titleBrush() const
{
    if (!m_titleItem) return QBrush();
    return m_titleItem->brush();
}

void ChartPresenter::setBackgroundVisible(bool visible)
{
    createBackgroundItem();
    m_backgroundItem->setVisible(visible);
}


bool ChartPresenter::isBackgroundVisible() const
{
    if (!m_backgroundItem) return false;
    return m_backgroundItem->isVisible();
}

void ChartPresenter::setBackgroundDropShadowEnabled(bool enabled)
{
    createBackgroundItem();
    m_backgroundItem->setDropShadowEnabled(enabled);
}

bool ChartPresenter::isBackgroundDropShadowEnabled() const
{
    if (!m_backgroundItem) return false;
    return m_backgroundItem->isDropShadowEnabled();
}


QGraphicsLayout* ChartPresenter::layout()
{
    return m_layout;
}

void ChartPresenter::setMarginsMinimum(const QRectF& margins)
{
    Q_UNUSED(margins);
  //  m_layout->setMarginsMinimum(margins);
}

QRectF ChartPresenter::margins() const
{
    return QRectF();//m_layout->margins();
}

QLegend* ChartPresenter::legend()
{
    return m_chart->legend();
}

QList<ChartAxis*>  ChartPresenter::axisItems() const
{
    return m_axisItems.values();
}

void ChartPresenter::setVisible(bool visible)
{
    m_chart->setVisible(visible);
}

#include "moc_chartpresenter_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
