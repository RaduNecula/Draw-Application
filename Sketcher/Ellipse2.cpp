#include "stdafx.h"
#include "Ellipse2.h"
#include <algorithm>


IMPLEMENT_SERIAL(CEllipse2, CElement, VERSION_NUMBER)

CEllipse2::CEllipse2()
{
}

CEllipse2::CEllipse2(const CPoint& start, const CPoint& end, COLORREF color, PenStyle penStyle, int penWidth) :
	CElement(start, color, penStyle, penWidth)
{
	if (start.x < end.x)
	{
		if (start.y < end.y)
		{
			m_StartPoint = CPoint((start.x - (end.x - start.x)), start.y-(end.y-start.y) );
			m_BottomRight = CPoint(end.x,end.y);
		}

		if (start.y > end.y)
		{
			m_StartPoint = CPoint(start.x - (end.x - start.x), end.y);
			m_BottomRight = CPoint(end.x, start.y + (start.y - end.y));
		}
		if (start.y == end.y)
		{
			m_StartPoint = CPoint((start.x - (end.x - start.x), (end.y - 1)));
			m_BottomRight = CPoint((end.x), (end.y + 1));
		}	
	}
	if (start.x > end.x)
	{
		if(start.y<end.y)
		{
			m_StartPoint = CPoint(end.x, (start.y-(end.y-start.y)));
			m_BottomRight = CPoint((start.x + (start.x - end.x)), end.y);
		}
		if (start.y>end.y)
		{	
			m_StartPoint = CPoint(end.x, end.y);
			m_BottomRight = CPoint(start.x + (start.x - end.x), start.y + (start.y - end.y));
		}
		if(start.y==end.y)
		{
			m_StartPoint = CPoint(end.x, start.y - 1);
			m_BottomRight = CPoint(start.x + (start.x - end.x), start.y + 1);
		}
	}
	if (start.x == end.x)
	{
		if (start.y<end.y)
		{
			m_StartPoint = CPoint(start.x - 1, start.y - (end.y - start.y));
			m_BottomRight = CPoint(start.x + 1, end.y);
		}
		if (start.y>end.y)
		{
			m_StartPoint = CPoint(start.x - 1, end.y);
			m_BottomRight = CPoint(start.x + 1, start.y + start.y - end.y);
		}
		if (start.y == end.y)
		{
			m_StartPoint = CPoint(start.x - 1, start.y - 1);
			m_BottomRight = CPoint(end.x + 1, end.y + 1);
		}
	}

	m_EnclosingRect = CRect(m_StartPoint.x, m_StartPoint.y, m_BottomRight.x, m_BottomRight.y);
	int width{ penWidth == 0 ? 1 : penWidth };
	m_EnclosingRect.InflateRect(width, width);
}


void CEllipse2::Draw(CDC* pDC, std::shared_ptr<CElement> pElement)
{
	CPen aPen;
	CreatePen(aPen, pElement);
	CPen* pOldPen{ pDC->SelectObject(&aPen) };
	CBrush* pOldBrush{ dynamic_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH)) };
	pDC->Ellipse(m_StartPoint.x, m_StartPoint.y, m_BottomRight.x, m_BottomRight.y);
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}


CEllipse2::~CEllipse2()
{
}

void CEllipse2::Move(const CSize& aSize)
{
	m_StartPoint += aSize; // Move the start point
	m_BottomRight += aSize; // Move the bottom right point
	m_EnclosingRect += aSize; // Move the enclosing rectangle
}

void CEllipse2::Serialize(CArchive& ar)
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
