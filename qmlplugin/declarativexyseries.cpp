//#include "DeclarativeXySeries.h"
#include "declarativexyseries.h"
#include "qxyseries.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

DeclarativeXySeries::DeclarativeXySeries()
{
}

DeclarativeXySeries::~DeclarativeXySeries()
{
}

void DeclarativeXySeries::classBegin()
{
}

void DeclarativeXySeries::componentComplete()
{
    seriesComplete();
}

QDeclarativeListProperty<DeclarativeXyPoint> DeclarativeXySeries::points()
{
    return QDeclarativeListProperty<DeclarativeXyPoint>(seriesObject(), 0, &DeclarativeXySeries::appendPoints);
}

void DeclarativeXySeries::appendPoints(QDeclarativeListProperty<DeclarativeXyPoint> *list,
                                          DeclarativeXyPoint *element)
{
    QXYSeries *series = qobject_cast<QXYSeries *>(list->object);
    if (series)
        series->add(QPointF(element->x(), element->y()));
}

QTCOMMERCIALCHART_END_NAMESPACE
