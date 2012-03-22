#include "areachartitem_p.h"
#include "qareaseries.h"
#include "qlineseries.h"
#include "chartpresenter_p.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>


QTCOMMERCIALCHART_BEGIN_NAMESPACE

//TODO: optimize : remove points which are not visible

AreaChartItem::AreaChartItem(QAreaSeries* areaSeries,ChartPresenter *presenter):ChartItem(presenter),
m_series(areaSeries),
m_upper(0),
m_lower(0),
m_pointsVisible(false)
{
    setZValue(ChartPresenter::LineChartZValue);
    m_upper = new AreaBoundItem(this,m_series->upperSeries(),presenter);
    if(m_series->lowerSeries()){
    m_lower = new AreaBoundItem(this,m_series->lowerSeries(),presenter);
    }

    QObject::connect(areaSeries,SIGNAL(updated()),this,SLOT(handleUpdated()));
    QObject::connect(this,SIGNAL(clicked(const QPointF&)),areaSeries,SIGNAL(clicked(const QPointF&)));

    handleUpdated();
}

AreaChartItem::~AreaChartItem()
{
    delete m_upper;
    delete m_lower;
};

QRectF AreaChartItem::boundingRect() const
{
    return m_rect;
}

QPainterPath AreaChartItem::shape() const
{
    return m_path;
}

void AreaChartItem::updatePath()
{
    QPainterPath path;

    path.connectPath(m_upper->shape());
    if(m_lower){
    path.connectPath(m_lower->shape().toReversed());
    }
    else{
        QPointF first = path.pointAtPercent(0);
        QPointF last =  path.pointAtPercent(1);
        path.lineTo(last.x(),m_clipRect.bottom());
        path.lineTo(first.x(),m_clipRect.bottom());
    }
    path.closeSubpath();
    prepareGeometryChange();
    m_path=path;
    m_rect=path.boundingRect();
    update();
}

void AreaChartItem::handleUpdated()
{
    m_pointsVisible = m_series->pointsVisible();
    m_linePen = m_series->pen();
    m_brush = m_series->brush();
    m_pointPen = m_series->pen();
    m_pointPen.setWidthF(2*m_pointPen.width());

    update();
}

void AreaChartItem::handleDomainChanged(qreal minX, qreal maxX, qreal minY, qreal maxY)
{
    m_upper->handleDomainChanged(minX,maxX,minY,maxY);
    if(m_lower)
    m_lower->handleDomainChanged(minX,maxX,minY,maxY);
}

void AreaChartItem::handleGeometryChanged(const QRectF& rect)
{
    m_clipRect=rect.translated(-rect.topLeft());
    setPos(rect.topLeft());
    m_upper->handleGeometryChanged(rect);
    if(m_lower)
    m_lower->handleGeometryChanged(rect);
}
//painter

void AreaChartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->save();
    QPen pen;
    pen.setCosmetic(false);
    pen.setWidth(4);
    pen.setColor(qRgb(200,0,250));
    painter->setPen(pen);
    //painter->setBrush(m_brush);
    painter->setClipRect(m_clipRect);
    painter->drawPath(m_path);
    if(m_pointsVisible){
           painter->setPen(m_pointPen);
           painter->drawPoints(m_upper->points());
           if(m_lower)  painter->drawPoints(m_lower->points());
    }
    painter->restore();
}

void AreaChartItem::mousePressEvent( QGraphicsSceneMouseEvent * event )
{
    emit clicked(m_upper->calculateDomainPoint(event->pos()));
}

#include "moc_areachartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
