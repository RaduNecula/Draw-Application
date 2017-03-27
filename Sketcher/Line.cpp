#include "stdafx.h"
#include "Line.h"
#include "PenStyle.h"

IMPLEMENT_SERIAL(CLine, CElement, VERSION_NUMBER)
CLine::CLine()
{
}

CLine::CLine(const CPoint& start, const CPoint& end, COLORREF aColor, PenStyle penStyle, int penWidth) :
	CElement(start, aColor, penStyle, penWidth), m_EndPoint{ end } 
{
	//Define the enclosing rectangle
	m_EnclosingRect = CRect(start, end);
	m_EnclosingRect.NormalizeRect();
	int width{ penWidth = 0 ? 1 : penWidth };
	m_EnclosingRect.InflateRect(width, width);
}
	

CLine::~CLine()
{
}

void CLine::Draw(CDC* pDC, std::shared_ptr<CElement> pElement)
{
	//Create a pen for this object and initialize it
	CPen aPen;
	CreatePen(aPen, pElement);
	CPen* pOldPen{ pDC->SelectObject(&aPen) };

	//Now draw the line
	pDC->MoveTo(m_StartPoint);
	pDC->LineTo(m_EndPoint);

	pDC->SelectObject(pOldPen); //Restore the old pen
}

void CLine::Move(const CSize& aSize)
{
	m_StartPoint += aSize; // Move the start point
	m_EndPoint += aSize; // and the end point
	m_EnclosingRect += aSize; // Move the enclosing rectangle
}

void CLine::Serialize(CArchive& ar)
{
	CElement::Serialize(ar);

	if (ar.IsStoring())
	{//Writing to the file
		ar << m_EndPoint;
	}
	else
	{//reading from file
		ar >> m_EndPoint;
	}
}