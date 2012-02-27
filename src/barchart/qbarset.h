#ifndef QBARSET_H
#define QBARSET_H

#include <qchartglobal.h>
#include <QPen>
#include <QBrush>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QBarSet : public QObject
{
    Q_OBJECT
public:
    QBarSet(QString name, QObject *parent = 0);

    void setName(QString name);
    QString name();
    QBarSet& operator << (const qreal &value);  // appends new value to set

    int count();                                // count of values in set
    qreal valueAt(int index);                   // for modifying individual values
    void setValue(int index, qreal value);      // setter for individual value

    void setPen(QPen pen);
    QPen pen();

    void setBrush(QBrush brush);
    QBrush brush();

Q_SIGNALS:
    void clicked();                         // Clicked and hover signals exposed to user
    void hoverEnter(QPoint pos);
    void hoverLeave();

    // TODO: Expose this to user or not?
    // TODO: TO PIMPL --->
    void toggleFloatingValues();
    void showToolTip(QPoint pos, QString tip);  // Private signal
    // <--- TO PIMPL

public Q_SLOTS:
    // These are for internal communication
    // TODO: TO PIMPL --->
    void barClicked();
    void barHoverEntered(QPoint pos);
    void barHoverLeaved();
    // <--- TO PIMPL

private:

    QString mName;
    QList<qreal> mValues;
    QPen mPen;
    QBrush mBrush;

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QBARSET_H
