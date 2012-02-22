#include "qchart.h"
#include "qchartaxis.h"
#include "chartpresenter_p.h"
#include "chartdataset_p.h"
#include <QGraphicsScene>
#include <QGraphicsSceneResizeEvent>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \enum QChart::ChartTheme

    This enum describes the theme used by the chart.

    \value ChartThemeDefault
    \value ChartThemeVanilla
    \value ChartThemeIcy
    \value ChartThemeGrayscale
    \value ChartThemeScientific
*/

/*!
    \class QChart
    \brief QtCommercial chart API.

    QChart is a QGraphicsWidget that you can show in a QGraphicsScene. It manages the graphical
    representation of different types of QChartSeries and other chart related objects like
    QChartAxis and QChartLegend. If you simply want to show a chart in a layout, you can use the
    convenience class QChartView instead of QChart.
    \sa QChartView
*/

/*!
    Constructs a chart object which is a child of parent.
*/
QChart::QChart(QGraphicsItem *parent, Qt::WindowFlags wFlags) : QGraphicsWidget(parent,wFlags),
    m_backgroundItem(0),
    m_titleItem(0),
    m_dataset(new ChartDataSet(this)),
    m_presenter(new ChartPresenter(this,m_dataset))
{
}

/*!
    Destroys the object and it's children, like QChartSeries and QChartAxis object added to it.
*/
QChart::~QChart()
{
}

/*!
    Adds the \a series and optional y axis onto the chart and takes the ownership of the objects.
    If auto scaling is enabled, re-scales the axes the series is bound to (both the x axis and
    the y axis).
*/
void QChart::addSeries(QChartSeries* series, QChartAxis* axisY)
{
    m_dataset->addSeries(series, axisY);
}

/*!
    Removes the QChartSeries specified in a perameter from the QChartView.
    It releses its ownership of the specified QChartSeries object.
    It does not delete the pointed QChartSeries data object
    \sa removeSeries(), removeAllSeries()
*/
void QChart::removeSeries(QChartSeries* series)
{
    m_dataset->removeSeries(series);
}

/*!
    Removes all the QChartSeries that have been added to the QChartView
    It also deletes the pointed QChartSeries data objects
    \sa addSeries(), removeSeries()
*/
void QChart::removeAllSeries()
{
    m_dataset->removeAllSeries();
}

void QChart::setChartBackgroundBrush(const QBrush& brush)
{
    createChartBackgroundItem();
    m_backgroundItem->setBrush(brush);
    m_backgroundItem->update();
}

void QChart::setChartBackgroundPen(const QPen& pen)
{
    createChartBackgroundItem();
    m_backgroundItem->setPen(pen);
    m_backgroundItem->update();
}

/*!
    Sets the chart \a title. The description text that is rendered above the chart.
*/
void QChart::setChartTitle(const QString& title)
{
    createChartTitleItem();
    m_titleItem->setPlainText(title);
}

/*!
    Sets the \a font that is used for rendering the description text that is rendered above the chart.
*/
void QChart::setChartTitleFont(const QFont& font)
{
    createChartTitleItem();
    m_titleItem->setFont(font);
}

void QChart::createChartBackgroundItem()
{
    if(!m_backgroundItem) {
        m_backgroundItem = new QGraphicsRectItem(this);
        m_backgroundItem->setPen(Qt::NoPen);
        m_backgroundItem->setZValue(ChartPresenter::BackgroundZValue);
    }
}

void QChart::createChartTitleItem()
{
    if(!m_titleItem) {
        m_titleItem = new QGraphicsTextItem(this);
        m_titleItem->setZValue(ChartPresenter::BackgroundZValue);
    }
}

/*!
    Returns the chart margin, which is the distance between the widget edge and the part of the chart where the actual data can be displayed.
    \sa setMargin()
*/
int QChart::margin() const
{
    return m_presenter->margin();
}

/*!
    Sets the chart \a margin, which is the distance between the widget edge and the part of the chart where the actual data can be displayed.
    \sa margin()
*/
void QChart::setMargin(int margin)
{
    m_presenter->setMargin(margin);
}

/*!
    Sets the \a theme used by the chart for rendering data graphical representation
    \sa ChartTheme, chartTheme()
*/
void QChart::setChartTheme(QChart::ChartTheme theme)
{
    m_presenter->setChartTheme(theme);
}

/*!
    Returns the theme enum used by the chart.
    \sa ChartTheme, setChartTheme()
*/
QChart::ChartTheme QChart::chartTheme() const
{
    return m_presenter->chartTheme();
}

void QChart::zoomIn()
{
    if (!m_dataset->nextDomain()) {
        QRectF rect = m_presenter->geometry();
        rect.setWidth(rect.width()/2);
        rect.setHeight(rect.height()/2);
        rect.moveCenter(m_presenter->geometry().center());
        zoomIn(rect);
    }
}

void QChart::zoomIn(const QRectF& rect)
{
    if(!rect.isValid()) return;
       QRectF r = rect.normalized();
       int margin = m_presenter->margin();
       r.translate(-margin, -margin);
       m_dataset->addDomain(r,m_presenter->geometry());
}

void QChart::zoomOut()
{
    m_dataset->previousDomain();
}

void QChart::zoomReset()
{
    m_dataset->clearDomains();
}

/*!
    Returns the pointer to the x axis object of the chart
*/
QChartAxis* QChart::axisX() const
{
    return m_dataset->axisX();
}

/*!
    Returns the pointer to the y axis object of the chart
*/
QChartAxis* QChart::axisY() const
{
    return m_dataset->axisY();
}

void QChart::resizeEvent(QGraphicsSceneResizeEvent *event)
{

    m_rect = QRectF(QPoint(0,0),event->newSize());
    QRectF rect = m_rect.adjusted(margin(),margin(), -margin(), -margin());

    // recalculate title position
    if (m_titleItem) {
        QPointF center = m_rect.center() -m_titleItem->boundingRect().center();
        m_titleItem->setPos(center.x(),m_rect.top()/2 + margin()/2);
    }

    //recalculate background gradient
    if (m_backgroundItem) {
        m_backgroundItem->setRect(rect);
    }

    QGraphicsWidget::resizeEvent(event);
    update();
}

#include "moc_qchart.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
