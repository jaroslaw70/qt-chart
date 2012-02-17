#ifndef DOMAIN_H_
#define DOMAIN_H_
#include "qchartglobal.h"
#include <QRect>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class Domain {
public:
	Domain();
	virtual ~Domain();

	qreal spanX() const;
	qreal spanY() const;

	friend bool operator== (const Domain &domain1, const Domain &domain2);
	friend bool operator!= (const Domain &domain1, const Domain &domain2);

	Domain subDomain(const QRectF& rect, qreal maxWidth, qreal maxHeight) const;

public:
	qreal m_minX;
	qreal m_maxX;
	qreal m_minY;
	qreal m_maxY;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif
