#pragma once
#include "Element.h"
class CEllipse :
	public CElement
{
	DECLARE_SERIAL(CEllipse)

public:
	CEllipse(const CPoint& start, const CPoint& end, COLORREF color, PenStyle penStyle, int penWidth);
	virtual ~CEllipse();
	void virtual Draw(CDC* pDC, std::shared_ptr<CElement> pElement=nullptr) override;
	virtual void Move(const CSize& aSize) override; // Function to move an element
	virtual void Serialize(CArchive& ar) override;
protected:
	CEllipse();
	CPoint m_BottomRight;
};

