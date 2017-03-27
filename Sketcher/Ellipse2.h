#pragma once
#include "Element.h"
class CEllipse2 :
	public CElement
{
	DECLARE_SERIAL(CEllipse2)

public:
	CEllipse2(const CPoint& start, const CPoint& end, COLORREF color, PenStyle penStyle, int penWidth);
	virtual ~CEllipse2();
	void virtual Draw(CDC* pDC, std::shared_ptr<CElement> pElement=nullptr) override;
	virtual void Move(const CSize& aSize) override; // Function to move an element
	virtual void Serialize(CArchive& ar) override;
protected:
	CEllipse2();
	CPoint m_BottomRight;
};

