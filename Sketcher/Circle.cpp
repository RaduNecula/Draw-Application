#include "stdafx.h"
#include "Circle.h"
#include <cmath>


IMPLEMENT_SERIAL(CCircle, CElement, VERSION_NUMBER)

CCircle::CCircle()
{
}

CCircle::CCircle(const CPoint& start, const CPoint& end, COLORREF color, PenStyle penStyle, int penWidth) :
	CElement(start, color, penStyle, penWidth)
{
	long radius = static_cast<long>(sqrt((double)((pow((end.x - start.x), 2) 
		+ pow((end.y - start.y), 2)))));

	if (radius < 1L)
		radius = 1L;

	m_StartPoint = CPoint(start.x - radius, start.y - radius);
	m_BottomRight = CPoint(start.x + radius, start.y + radius);

	m_EnclosingRect = CRect{ m_StartPoint.x, m_StartPoint.y, 
										m_BottomRight.x, m_BottomRight.y };

	int width{ penWidth == 0 ? 1 : penWidth };

	m_EnclosingRect.InflateRect(width, width);
}

void CCircle::Draw(CDC* pDC, std::shared_ptr<CElement> pElement)
{
	CPen aPen;
	CreatePen(aPen, pElement);

	CPen* pOldPen{ pDC->SelectObject(&aPen) };
	CBrush* pOldBrush{ dynamic_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH)) };

	pDC->Ellipse(CRect(m_StartPoint.x, m_StartPoint.y, 
		m_BottomRight.x, m_BottomRight.y));

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}


CCircle::~CCircle()
{
}


void CCircle::Move(const CSize& aSize)
{
	m_StartPoint += aSize; // Move the start point
	m_BottomRight += aSize; // Move the bottom right point
	m_EnclosingRect += aSize; // Move the enclosing rectangle
}

void CCircle::Serialize(CArchive& ar)
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