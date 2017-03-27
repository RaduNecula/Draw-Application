#pragma once
#include "Element.h"
class CLine :
	public CElement
{
	DECLARE_SERIAL(CLine)
public:
	virtual ~CLine();
	virtual void Draw(CDC* pDC, std::shared_ptr<CElement> pElement=nullptr) override;
	CLine(const CPoint& start, const CPoint& end, COLORREF aColor, PenStyle penStyle, int penWidth);
	virtual void Move(const CSize& aSize) override; // Function to move an element
	virtual void Serialize(CArchive& ar) override;

protected:
	CLine();
	CPoint m_EndPoint;

};

