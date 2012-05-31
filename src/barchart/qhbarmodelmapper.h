#ifndef QHBARMODELMAPPER_H
#define QHBARMODELMAPPER_H

#include <QBarModelMapper>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QTCOMMERCIALCHART_EXPORT QHBarModelMapper : public QBarModelMapper
{
    Q_OBJECT
    Q_PROPERTY(int firstBarSetRow READ firstBarSetRow WRITE setFirstBarSetRow)
    Q_PROPERTY(int lastBarSetRow READ lastBarSetRow WRITE setLastBarSetRow)
    Q_PROPERTY(int categoriesRow READ categoriesRow WRITE setCategoriesRow)

public:
    explicit QHBarModelMapper(QObject *parent = 0);

    int firstBarSetRow() const;
    void setFirstBarSetRow(int firstBarSetRow);

    int lastBarSetRow() const;
    void setLastBarSetRow(int lastBarSetRow);

    int categoriesRow() const;
    void setCategoriesRow(int categoriesRow);

};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // QHBARMODELMAPPER_H
