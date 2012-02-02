#ifndef STACKEDBARGROUP_H
#define STACKEDBARGROUP_H

#include "charttheme_p.h"
#include "chartitem_p.h"
#include "barlabel_p.h"
#include "bar_p.h"
#include "stackedbarchartseries.h"
#include <QGraphicsItem>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

// TODO: derive this from ChartObjectInterface, when setSize is back in ChartItem
class StackedBarGroup : public ChartItem, public ChartThemeObserver
{
public:
    StackedBarGroup(StackedBarChartSeries& series, QGraphicsItem *parent = 0);

    // Bar chart spesific
    void setSeparatorsVisible(bool visible = true);

public: // From ChartItem
    void setSize(const QSizeF &size);
    void setPlotDomain(const PlotDomain& data);

    // From ChartThemeObserver
    void themeChanged(ChartTheme *theme);

public: // Layout "api"
    void setPos(qreal x, qreal y);
    void setBarWidth( int w );          // Default width for each bar

    int addColor( QColor color );
    void resetColors();

    // From QGraphicsItem
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

private:

    void dataChanged();     // data of series has changed -> need to recalculate bar sizes
    void layoutChanged();   // layout has changed -> need to recalculate bar sizes

private:

    // Data
    StackedBarChartSeries& mSeries;
    int mMin;                                   // Min and max values of data. (updated when data is changed, used when drawing)
    int mMax;

    int mHeight;        // Layout spesific
    int mWidth;
    int mBarDefaultWidth;

    bool mLayoutSet;    // True, if component has been laid out.
    bool mLayoutDirty;

    QList<QColor> mColors;  // List of colors for series for now

    ChartTheme* mTheme;
    bool mSeparatorsVisible;
    QList<qreal> mSeparatorPositions;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // STACKEDBARGROUP_H
