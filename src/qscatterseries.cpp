#include "qscatterseries.h"
#include "qscatterseries_p.h"
#include "qchart.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

//#define QSeriesData QList<qreal>

QScatterSeriesPrivate::QScatterSeriesPrivate(QList<qreal> x, QList<qreal> y, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    m_x(x),
    m_y(y),
    m_scalex(100), // TODO: let the use define the scale (or autoscaled)
    m_scaley(100)
{
    resize(parent->boundingRect());
}

void QScatterSeriesPrivate::resize(QRectF rect)
{
    m_scenex.clear();
    m_sceney.clear();

    foreach(qreal x, m_x)
        m_scenex.append(rect.left() + x * (rect.width() / m_scalex));

    foreach(qreal y, m_y)
        m_sceney.append(rect.bottom() - y * (rect.height() / m_scaley));
}

// TODO:
//void QScatterSeriesPrivate::setAxisScale(qreal xscale, qreal yscale)

QRectF QScatterSeriesPrivate::boundingRect() const
{
    return QRectF(0, 0, 55, 100);
}

void QScatterSeriesPrivate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen = painter->pen();
    QBrush brush = pen.brush();
    // TODO: The opacity should be user definable...
    brush.setColor(QColor(255, 82, 0, 100));
    pen.setBrush(brush);
    pen.setWidth(4);
    painter->setPen(pen);

    // TODO: m_scenex and m_sceny are left empty during construction -> we would need a resize
    // event right after construction or maybe given a size during initialization
    for (int i(0); i < m_scenex.count() && i < m_sceney.count(); i++) {
        if (scene()->width() > m_scenex.at(i) && scene()->height() > m_sceney.at(i))
            //painter->drawArc(m_scenex.at(i), m_sceney.at(i), 2, 2, 0, 5760);
            painter->drawPoint(m_scenex.at(i), m_sceney.at(i));
    }
}

QScatterSeries::QScatterSeries(QList<qreal> x, QList<qreal> y, QObject *parent) :
    QChartSeries(parent),
    d(new QScatterSeriesPrivate(x, y, qobject_cast<QGraphicsItem *> (parent)))
{
}

void QScatterSeries::chartSizeChanged(QRectF rect)
{
    // Recalculate scatter data point locations on the scene
//    d->transform().reset();
//    d->transform().translate();
    d->resize(rect);
}

// TODO:
//void QScatterSeries::chartScaleChanged(qreal xscale, qreal yscale)
//{
//    d->rescale(xscale, yscale);
//}

QScatterSeries::~QScatterSeries()
{
    delete d;
}

#include "moc_qscatterseries.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
