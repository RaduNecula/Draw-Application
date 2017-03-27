#pragma once
#include "Element.h"
#include <vector>
class CCurve :
	public CElement
{
	DECLARE_SERIAL(CCurve)
public:
	CCurve(const CPoint first, const CPoint& second, COLORREF color, PenStyle penStyle, int penWidth);
	virtual ~CCurve();
	virtual void Draw(CDC* pDC, std::shared_ptr<CElement> pElement=nullptr) override;
	void AddSegment(const CPoint& point);
	virtual void Move(const CSize& aSize) override; // Function to move an element
	virtual void Serialize(CArchive& ar) override;
protected:
	CCurve();
	std::vector<CPoint> m_Points;

};

