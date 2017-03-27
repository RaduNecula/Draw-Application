// Element.cpp : implementation file
//

#include "stdafx.h"
#include "Sketcher.h"
#include "Element.h"

IMPLEMENT_SERIAL(CElement, CObject, VERSION_NUMBER)


// CElement

CElement::CElement()
{
}

CElement::CElement(const CPoint& start, COLORREF color, PenStyle penStyle, int penWidth): 
	m_StartPoint{ start }, m_Color{ color }, m_PenStyle{ penStyle }, m_PenWidth {
	penWidth
} {}

CElement::~CElement()
{
}


void CElement::Serialize(CArchive& ar)
{
	CObject::Serialize(ar); // Call the base class function
	if (ar.IsStoring())
	{ // Writing to the file
		
		ar << m_StartPoint // Element position
			<< m_PenWidth // The pen width
			<< m_Color // The element color
			<< m_EnclosingRect // The enclosing rectangle
			<< static_cast<int>(m_PenStyle);
	}
	else
	{ // Reading from the file
		int penStyle{};
		ar >> m_StartPoint // Element position
			>> m_PenWidth // The pen width
			>> m_Color // The element color
			>> m_EnclosingRect // The enclosing rectangle
			>> penStyle;
		m_PenStyle = static_cast<PenStyle>(penStyle);
	}
}