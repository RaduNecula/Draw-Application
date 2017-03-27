#pragma once
#include "Element.h"

class CCircle :
	public CElement
{
	DECLARE_SERIAL(CCircle)
public:
	CCircle(const CPoint& start, const CPoint& end, COLORREF color, PenStyle penStyle, int penWidth);
	virtual ~CCircle();
	virtual void Draw(CDC* pDC, std::shared_ptr<CElement> pElement=nullptr) override;
	virtual void Move(const CSize& aSize) override; // Function to move an element
	virtual void Serialize(CArchive& ar) override;
protected:
	CCircle();
	CPoint m_BottomRight;
};

