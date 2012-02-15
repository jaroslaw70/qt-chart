#include "axisitem_p.h"
#include "qchartaxis.h"
#include <QPainter>
#include <QDebug>

static int label_padding = 5;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

AxisItem::AxisItem(AxisType type,QGraphicsItem* parent) :
ChartItem(parent),
m_ticks(4),
m_type(type),
m_labelsAngle(0),
m_shadesEnabled(true),
m_grid(parent),
m_shades(parent),
m_labels(parent)
{
    //initial initialization
    m_shades.setZValue(0);
    m_grid.setZValue(2);
    createItems();
}

AxisItem::~AxisItem()
{
}

QRectF AxisItem::boundingRect() const
{
    return m_rect;
}

void AxisItem::createItems()
{
    for (int i = 0; i <= m_ticks; ++i) {
           m_grid.addToGroup(new QGraphicsLineItem(this));
           m_labels.addToGroup(new QGraphicsSimpleTextItem(this));
           if(i%2) m_shades.addToGroup(new QGraphicsRectItem(this));
       }
}

void AxisItem::clear()
{
    foreach(QGraphicsItem* item , m_shades.childItems()) {
        delete item;
    }

    foreach(QGraphicsItem* item , m_grid.childItems()) {
        delete item;
    }

    foreach(QGraphicsItem* item , m_labels.childItems()) {
        delete item;
    }

}

void AxisItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

void AxisItem::updateDomain()
{

    QList<QGraphicsItem *> lines = m_grid.childItems();
    QList<QGraphicsItem *> labels = m_labels.childItems();
    QList<QGraphicsItem *> shades = m_shades.childItems();

    switch (m_type)
      {
          case X_AXIS:
          {
              const qreal deltaX = m_rect.width() / m_ticks;

              m_axis.setLine(m_rect.left(), m_rect.bottom(), m_rect.right(), m_rect.bottom());

              for (int i = 0; i <= m_ticks; ++i) {

                  int x = i * deltaX + m_rect.left();

                  qreal label = m_domain.m_minX + (i * m_domain.spanX()/ m_ticks);

                  QGraphicsLineItem *lineItem =  static_cast<QGraphicsLineItem*>(lines.at(i));
                  lineItem->setLine(x, m_rect.top(), x, m_rect.bottom());

                  QGraphicsSimpleTextItem *labelItem = static_cast<QGraphicsSimpleTextItem*>(labels.at(i));
                  labelItem->setText(QString::number(label));
                  QPointF center = labelItem->boundingRect().center();
                  labelItem->setTransformOriginPoint(center.x(), center.y());
                  labelItem->setPos(x - center.x(), m_rect.bottom() + label_padding);

                  if(i%2){
                      QGraphicsRectItem *rectItem =  static_cast<QGraphicsRectItem*>(shades.at(i/2));
                      rectItem->setRect(x,m_rect.top(),deltaX,m_rect.height());
                      rectItem->setOpacity( 0.5 );
                  }
              }
          }
          break;

          case Y_AXIS:
          {
              const qreal deltaY = m_rect.height()/ m_ticks;

              m_axis.setLine(m_rect.left() , m_rect.top(), m_rect.left(), m_rect.bottom());

              for (int i = 0; i <= m_ticks; ++i) {

                  int y = i * -deltaY + m_rect.bottom();

                  qreal label = m_domain.m_minY + (i * m_domain.spanY()/ m_ticks);

                  QGraphicsLineItem *lineItem =  static_cast<QGraphicsLineItem*>(lines.at(i));
                  lineItem->setLine(m_rect.left() , y, m_rect.right(), y);

                  QGraphicsSimpleTextItem *labelItem = static_cast<QGraphicsSimpleTextItem*>(labels.at(i));
                  labelItem->setText(QString::number(label));
                  QPointF center = labelItem->boundingRect().center();
                  labelItem->setTransformOriginPoint(center.x(), center.y());
                  labelItem->setPos(m_rect.left() -  labelItem->boundingRect().width() - label_padding , y-center.y());


                  if(i%2){
                      QGraphicsRectItem *rectItem =  static_cast<QGraphicsRectItem*>(shades.at(i/2));
                      rectItem->setRect(m_rect.left(),y,m_rect.width(),deltaY);

                  }
              }
          }
          break;
          default:
          qDebug()<<"Unknown axis type";
          break;
      }
}

void AxisItem::handleAxisChanged(const QChartAxis& axis)
{
    if(axis.isAxisVisible()) {
        setAxisOpacity(100);
    }
    else {
        setAxisOpacity(0);
    }

    if(axis.isGridVisible()) {
        setGridOpacity(100);
    }
    else {
        setGridOpacity(0);
    }

    if(axis.isLabelsVisible())
    {
        setLabelsOpacity(100);
    }
    else {
        setLabelsOpacity(0);
    }

    if(axis.isShadesVisible()) {
        setShadesOpacity(axis.shadesOpacity());
    }
    else {
        setShadesOpacity(0);
    }

    switch(axis.labelsOrientation())
    {
        case QChartAxis::LabelsOrientationHorizontal:
            setLabelsAngle(0);
            break;
        case QChartAxis::LabelsOrientationVertical:
            setLabelsAngle(90);
            break;
        case QChartAxis::LabelsOrientationSlide:
            setLabelsAngle(-45);
            break;
        default:
            break;
    }

    setAxisPen(axis.axisPen());
    setLabelsPen(axis.labelsPen());
    setLabelsBrush(axis.labelsBrush());
    setLabelsFont(axis.labelFont());
    setGridPen(axis.gridPen());
    setShadesPen(axis.shadesPen());
    setShadesBrush(axis.shadesBrush());

}

void AxisItem::handleDomainChanged(const Domain& domain)
{
    m_domain = domain;
    updateDomain();
    update();
}

void AxisItem::handleGeometryChanged(const QRectF& rect)
{
    m_rect = rect;
    updateDomain();
    update();
}

void AxisItem::setAxisOpacity(qreal opacity)
{
    m_axis.setOpacity(opacity);
}

qreal AxisItem::axisOpacity() const
{
    return m_axis.opacity();
}

void AxisItem::setGridOpacity(qreal opacity)
{
    m_grid.setOpacity(opacity);
}


qreal AxisItem::gridOpacity() const
{
    return m_grid.opacity();
}

void AxisItem::setLabelsOpacity(qreal opacity)
{
    m_labels.setOpacity(opacity);
}

qreal AxisItem::labelsOpacity() const
{
    return m_labels.opacity();
}

void AxisItem::setShadesOpacity(qreal opacity)
{
    m_shades.setOpacity(opacity);
}

qreal AxisItem::shadesOpacity() const
{
    return m_shades.opacity();
}

void AxisItem::setLabelsAngle(int angle)
{
    foreach(QGraphicsItem* item , m_labels.childItems()) {
          QPointF center = item->boundingRect().center();
          item->setRotation(angle);
    }

    m_labelsAngle=angle;
}

void AxisItem::setLabelsPen(const QPen& pen)
{
    foreach(QGraphicsItem* item , m_labels.childItems()) {
        static_cast<QGraphicsSimpleTextItem*>(item)->setPen(pen);
    }
}

void AxisItem::setLabelsBrush(const QBrush& brush)
{
    foreach(QGraphicsItem* item , m_labels.childItems()) {
        static_cast<QGraphicsSimpleTextItem*>(item)->setBrush(brush);
    }
}

void AxisItem::setLabelsFont(const QFont& font)
{
    foreach(QGraphicsItem* item , m_labels.childItems()) {
        static_cast<QGraphicsSimpleTextItem*>(item)->setFont(font);
    }
}

void AxisItem::setShadesBrush(const QBrush& brush)
{
    foreach(QGraphicsItem* item , m_shades.childItems()) {
        static_cast<QGraphicsRectItem*>(item)->setBrush(brush);
    }
}

void AxisItem::setShadesPen(const QPen& pen)
{
    foreach(QGraphicsItem* item , m_shades.childItems()) {
        static_cast<QGraphicsRectItem*>(item)->setPen(pen);
    }
}

void AxisItem::setAxisPen(const QPen& pen)
{
    m_axis.setPen(pen);
}

void AxisItem::setGridPen(const QPen& pen)
{
    foreach(QGraphicsItem* item , m_grid.childItems()) {
        static_cast<QGraphicsLineItem*>(item)->setPen(pen);
    }
}

void AxisItem::setTicks(int count)
{
    if(count!=m_ticks){
    clear();
    m_ticks=count;
    createItems();
    }
}

//TODO "nice numbers algorithm"
#include "moc_axisitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
