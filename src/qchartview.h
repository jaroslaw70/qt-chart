#ifndef QCHARTWIDGET_H
#define QCHARTWIDGET_H

#include "qchartglobal.h"
#include "qchartseries.h"
#include "qchart.h"
#include <QGraphicsView>

class QGraphicsScene;
class QRubberBand;

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QChart;

class QTCOMMERCIALCHART_EXPORT QChartView : public QGraphicsView
{
public:
    enum  RubberBandPolicy { NoRubberBand, VerticalRubberBand, HorizonalRubberBand, RectangleRubberBand };

    explicit QChartView(QWidget *parent = 0);
    ~QChartView();

    //implement from QWidget
    void resizeEvent(QResizeEvent *event);

    void addSeries(QChartSeries* series); // takes ownership

    // Convenience function
    QChartSeries* createSeries(QChartSeries::QChartSeriesType type);

    int margin() const;

    void setChartTitle(const QString& title);
    void setChartTitleFont(const QFont& font);
    void setChartBackgroundBrush(const QBrush& brush);
    void setChartBackgroundPen(const QPen& pen);

    void zoomInToRect(const QRect& rectangle);
    void zoomIn();
    void zoomOut();

    void setRubberBandPolicy(const RubberBandPolicy );
    RubberBandPolicy rubberBandPolicy() const;

    void setChartTheme(QChart::ChartTheme theme);
    QChart::ChartTheme chartTheme() const;

    void setDefaultAxisX(const QChartAxis& axis);
    void setDefaultAxisY(const QChartAxis& axis);
    QChartAxis defaultAxisX() const;
    QChartAxis defaultAxisY() const;
    QChartAxis axisY(int id) const;
    int addAxisY(const QChartAxis& axis);
    void removeAxisY(int id);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);


private:
    QGraphicsScene *m_scene;
    QChart* m_chart;
    QPoint m_rubberBandOrigin;
    QRubberBand* m_rubberBand;
    bool m_verticalRubberBand;
    bool m_horizonalRubberBand;
    Q_DISABLE_COPY(QChartView)


};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QCHARTWIDGET_H
