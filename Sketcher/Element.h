#pragma once

#include "PenStyle.h"
#include <memory>


// CElement command target

static const COLORREF SELECT_COLOR{ RGB(255,0,180) };
static const UINT VERSION_NUMBER{ 1001 }; // Version number for serialization

class CElement : public CObject
{
	DECLARE_SERIAL(CElement)
protected:
	CPoint m_StartPoint;
	int m_PenWidth;
	COLORREF m_Color;
	CRect m_EnclosingRect;
	PenStyle m_PenStyle;

public:
	virtual ~CElement();
	virtual void Draw(CDC* pDC, std::shared_ptr<CElement> pElement=nullptr) {}//Virtual draw operation
	virtual void Move(const CSize& aSize){} //Move an element
	//Get the element enclosing rectangle
	const CRect& GetEnclosingRect()const { return m_EnclosingRect; }
	virtual void Serialize(CArchive& ar) override; // Serialize object

protected:
	CElement();
	CElement(const CPoint& start, COLORREF color, PenStyle penStyle = PenStyle::SOLID, int penWidth = 1);
	
	void CreatePen(CPen& aPen, std::shared_ptr<CElement> pElement)
	{
		if (!aPen.CreatePen(static_cast<int>(m_PenStyle), m_PenWidth, 
			this==pElement.get() ? SELECT_COLOR : m_Color))
		{
			//Pen creation failed
			AfxMessageBox(_T("Pen creation failed"), MB_OK);
			AfxAbort();
		}
	}

};


