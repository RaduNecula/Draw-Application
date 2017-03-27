#include "stdafx.h"
#include "Ellipse.h"
#include <algorithm>


IMPLEMENT_SERIAL(CEllipse, CElement, VERSION_NUMBER)

CEllipse::CEllipse()
{
}

CEllipse::CEllipse(const CPoint& start, const CPoint& end, COLORREF color, PenStyle penStyle, int penWidth) :
	CElement(start, color, penStyle, penWidth)
{
	m_StartPoint = CPoint((std::min)(start.x, end.x), (std::min)(start.y, end.y));
	m_BottomRight = CPoint((std::max)(start.x, end.x), (std::max)(start.y, end.y));
	m_EnclosingRect = CRect(m_StartPoint.x, m_StartPoint.y,
							m_BottomRight.x, m_BottomRight.y);
	int width{ penWidth == 0 ? 1 : penWidth };
	m_EnclosingRect.InflateRect(width, width);
}
	
void CEllipse::Draw(CDC* pDC, std::shared_ptr<CElement> pElement)
{
	CPen aPen;
	CreatePen(aPen, pElement);
	CPen* pOldPen{ pDC->SelectObject(&aPen) };
	CBrush* pOldBrush{ dynamic_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH)) };
	pDC->Ellipse(m_StartPoint.x, m_StartPoint.y, m_BottomRight.x, m_BottomRight.y);
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);

}



CEllipse::~CEllipse()
{
}


void CEllipse::Move(const CSize& aSize)
{
	m_StartPoint += aSize; // Move the start point
	m_BottomRight += aSize; // Move the bottom right point
	m_EnclosingRect += aSize; // Move the enclosing rectangle
}


void CEllipse::Serialize(CArchive& ar)
{
	CElement::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << m_BottomRight;
	}
	else
	{
		ar >> m_BottomRight;
	}
}