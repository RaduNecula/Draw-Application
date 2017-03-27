#pragma once
#include "Element.h"
class CRectangle :
	public CElement
{
	DECLARE_SERIAL(CRectangle)

public:
	
	virtual ~CRectangle();
	virtual void Draw(CDC* pDC, std::shared_ptr<CElement> pElement=nullptr) override;
	CRectangle(const CPoint& start, const CPoint& end, COLORREF color, PenStyle penStyle, int penWidth);
	virtual void Move(const CSize& aSize) override; // Function to move an element
	virtual void Serialize(CArchive& ar) override;
protected:
	CRectangle();
	CPoint m_BottomRight;
};

