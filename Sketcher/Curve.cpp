#include "stdafx.h"
#include "Curve.h"
#include <algorithm>


IMPLEMENT_SERIAL(CCurve, CElement, VERSION_NUMBER)

CCurve::CCurve()
{
}

CCurve::CCurve(const CPoint first, const CPoint& second, COLORREF color, PenStyle penStyle, int penWidth): 
	CElement( first, color, penStyle, penWidth )
{
	//Store the second point in the vector
	m_Points.push_back(second);
	m_EnclosingRect = CRect((std::min)(first.x, second.x), (std::min)(first.y, second.y),
						(std::max)(first.x, second.x), (std::max)(first.y, second.y));
	int width{ penWidth == 0 ? 1 : penWidth };
	m_EnclosingRect.InflateRect(width, width);
}

void CCurve::Draw(CDC* pDC, std::shared_ptr<CElement> pElement)
{
	CPen aPen;
	CreatePen(aPen, pElement);

	CPen* pOldPen{ pDC->SelectObject(&aPen) };

	pDC->MoveTo(m_StartPoint);
	for (const auto& point : m_Points)
		pDC->LineTo(point);
	pDC->SelectObject(pOldPen);
}

void CCurve::AddSegment(const CPoint& point)
{
	m_Points.push_back(point);

	int width{ m_PenWidth == 0 ? 1 : m_PenWidth };

	m_EnclosingRect.DeflateRect(width, width);
	m_EnclosingRect = CRect{ (std::min)(m_EnclosingRect.left, point.x),
		(std::min)(m_EnclosingRect.top, point.y),
		(std::max)(m_EnclosingRect.right, point.x),
		(std::max)(m_EnclosingRect.bottom, point.y) };
	m_EnclosingRect.InflateRect(width, width);
}

CCurve::~CCurve()
{
}


void CCurve::Move(const CSize& aSize)
{
	m_EnclosingRect += aSize; // Move the rectangle
	m_StartPoint += aSize; // Move the start point
						   // Now move all the other points
	for (auto& p : m_Points)
		p += aSize;
}

void CCurve::Serialize(CArchive& ar)
{
	CElement::Serialize(ar);

	if (ar.IsStoring())
	{
		size_t NrElem = m_Points.size();
		ar << NrElem;
		for (const auto& p : m_Points)
			ar << p;
	}
	else
	{
		size_t NrElem{};
		ar >> NrElem;
		CPoint point;
		for (size_t i{}; i < NrElem; i++)
		{
			ar >> point;
			m_Points.push_back(point);
		}
	}
}