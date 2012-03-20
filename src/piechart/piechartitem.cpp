#include "piechartitem_p.h"
#include "pieslice_p.h"
#include "qpieslice.h"
#include "qpiesliceprivate_p.h"
#include "qpieseries.h"
#include "chartpresenter_p.h"
#include "chartdataset_p.h"
#include "chartanimator_p.h"
#include <QDebug>
#include <QPainter>
#include <QTimer>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

PieChartItem::PieChartItem(QPieSeries *series, ChartPresenter *presenter, QGraphicsItem *parent)
    :ChartItem(parent),
    m_series(series),
    m_presenter(presenter)
{
    Q_ASSERT(series);
    connect(series, SIGNAL(added(QList<QPieSlice*>)), this, SLOT(handleSlicesAdded(QList<QPieSlice*>)));
    connect(series, SIGNAL(removed(QList<QPieSlice*>)), this, SLOT(handleSlicesRemoved(QList<QPieSlice*>)));
    connect(series, SIGNAL(piePositionChanged()), this, SLOT(handlePieLayoutChanged()));
    connect(series, SIGNAL(pieSizeChanged()), this, SLOT(handlePieLayoutChanged()));

    QTimer::singleShot(0, this, SLOT(initialize()));

    // Note: the following does not affect as long as the item does not have anything to paint
    setZValue(ChartPresenter::PieSeriesZValue);
}

PieChartItem::~PieChartItem()
{
    // slices deleted automatically through QGraphicsItem
}

void PieChartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    Q_UNUSED(painter)
    // TODO: paint shadows for all components
    // - get paths from items & merge & offset and draw with shadow color?
    //painter->setBrush(QBrush(Qt::red));
    //painter->drawRect(m_debugRect);
}

void PieChartItem::initialize()
{
    handleSlicesAdded(m_series->slices());
}

void PieChartItem::handleSlicesAdded(QList<QPieSlice*> slices)
{
    bool isEmpty = m_slices.isEmpty();

    m_presenter->theme()->decorate(m_series, m_presenter->dataSet()->seriesIndex(m_series));

    foreach (QPieSlice *s, slices) {
        PieSlice* slice = new PieSlice(this);
        m_slices.insert(s, slice);
        connect(s, SIGNAL(changed()), this, SLOT(handleSliceChanged()));
        connect(slice, SIGNAL(clicked()), s, SIGNAL(clicked()));
        connect(slice, SIGNAL(hoverEnter()), s, SIGNAL(hoverEnter()));
        connect(slice, SIGNAL(hoverLeave()), s, SIGNAL(hoverLeave()));

        PieSliceData data = sliceData(s);

        if (m_animator)
            m_animator->addAnimation(this, s, data, isEmpty);
        else
            setLayout(s, data);
    }
}

void PieChartItem::handleSlicesRemoved(QList<QPieSlice*> slices)
{
    m_presenter->theme()->decorate(m_series, m_presenter->dataSet()->seriesIndex(m_series));

    foreach (QPieSlice *s, slices) {
        if (m_animator)
            m_animator->removeAnimation(this, s);
        else
            destroySlice(s);
    }
}

void PieChartItem::handlePieLayoutChanged()
{
    PieLayout layout = calculateLayout();
    applyLayout(layout);
    update();
}

void PieChartItem::handleSliceChanged()
{
    QPieSlice* slice = qobject_cast<QPieSlice *>(sender());
    Q_ASSERT(m_slices.contains(slice));
    PieSliceData data = sliceData(slice);
    updateLayout(slice, data);
    update();
}

void PieChartItem::handleDomainChanged(qreal, qreal, qreal, qreal)
{
    // TODO
}

void PieChartItem::handleGeometryChanged(const QRectF& rect)
{
    prepareGeometryChange();
    m_rect = rect;
    handlePieLayoutChanged();
}

void PieChartItem::calculatePieLayout()
{
    // find pie center coordinates
    m_pieCenter.setX(m_rect.left() + (m_rect.width() * m_series->pieHorizontalPosition()));
    m_pieCenter.setY(m_rect.top() + (m_rect.height() * m_series->pieVerticalPosition()));

    // find maximum radius for pie
    m_pieRadius = m_rect.height() / 2;
    if (m_rect.width() < m_rect.height())
        m_pieRadius = m_rect.width() / 2;

    // apply size factor
    m_pieRadius *= m_series->pieSize();
}

PieSliceData PieChartItem::sliceData(QPieSlice *slice)
{
    PieSliceData sliceData = slice->d_ptr->m_data;
    sliceData.m_center = PieSlice::sliceCenter(m_pieCenter, m_pieRadius, slice);
    sliceData.m_radius = m_pieRadius;
    sliceData.m_angleSpan = slice->endAngle() - slice->startAngle();
    return sliceData;
}

PieLayout PieChartItem::calculateLayout()
{
    calculatePieLayout();
    PieLayout layout;
    foreach (QPieSlice* s, m_series->slices()) {
        if (m_slices.contains(s)) // calculate layout only for those slices that are already visible
            layout.insert(s, sliceData(s));
    }
    return layout;
}

void PieChartItem::applyLayout(const PieLayout &layout)
{
    if (m_animator)
        m_animator->updateLayout(this, layout);
    else
        setLayout(layout);
}

void PieChartItem::updateLayout(QPieSlice *slice, const PieSliceData &sliceData)
{
    if (m_animator)
        m_animator->updateLayout(this, slice, sliceData);
    else
        setLayout(slice, sliceData);
}

void PieChartItem::setLayout(const PieLayout &layout)
{
    foreach (QPieSlice *slice, layout.keys()) {
        PieSlice *s = m_slices.value(slice);
        Q_ASSERT(s);
        s->setSliceData(layout.value(slice));
        s->updateGeometry();
        s->update();
    }
}

void PieChartItem::setLayout(QPieSlice *slice, const PieSliceData &sliceData)
{
    // find slice
    PieSlice *s = m_slices.value(slice);
    Q_ASSERT(s);
    s->setSliceData(sliceData);
    s->updateGeometry();
    s->update();
}

void PieChartItem::destroySlice(QPieSlice *slice)
{
    delete m_slices.take(slice);
}

#include "moc_piechartitem_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
