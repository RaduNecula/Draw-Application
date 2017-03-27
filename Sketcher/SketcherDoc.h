
// SketcherDoc.h : interface of the CSketcherDoc class
//


#pragma once
#include "ElementColor.h"
#include "ElementType.h"
#include <list>
#include <memory>
#include "Element.h"
#include "PenStyle.h"

using SketchIterator = std::list<std::shared_ptr<CElement>>::const_iterator;


class CSketcherDoc : public CDocument
{
protected: // create from serialization only
	CSketcherDoc();
	DECLARE_DYNCREATE(CSketcherDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CSketcherDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnColorBlack();
	afx_msg void OnColorRed();
	afx_msg void OnColorGreen();
	afx_msg void OnColorBlue();
	afx_msg void OnUpdateColorBlack(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorRed(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorGreen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateColorBlue(CCmdUI *pCmdUI);
protected:
	// Current element type
	ElementType m_Element{ ElementType::LINE };
	ElementColor m_Color{ ElementColor::BLACK };
	PenStyle m_PenStyle{ PenStyle::SOLID };
	int m_PenWidth{};
	std::list<std::shared_ptr<CElement>> m_Sketch;
	CSize m_DocSize{ 3000,3000 };



public:
	ElementType GetElementType() const;
		
	ElementColor GetElementColor() const;

	CSize GetDocSize()const
	{
		return m_DocSize;
	}

	PenStyle GetPenStyle() const;

	int GetPenWidth() const
	{
		return m_PenWidth;
	}

	afx_msg void OnElementLine();
	afx_msg void OnElementRectangle();
	afx_msg void OnElementCircle();
	afx_msg void OnElementCurve();
	afx_msg void OnElementEllipse();
	afx_msg void OnUpdateElementLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateElementRectangle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateElementCircle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateElementCurve(CCmdUI *pCmdUI);
	afx_msg void OnUpdateElementEllipse(CCmdUI *pCmdUI);
	afx_msg void OnElementEllipse2();
	afx_msg void OnUpdateElementEllipse2(CCmdUI *pCmdUI);

public:
	void AddElement(std::shared_ptr<CElement>& pElement)
	{
		m_Sketch.push_back(pElement);
		UpdateAllViews(nullptr, 0, pElement.get());
		SetModifiedFlag();
	}

	void DeleteElement(std::shared_ptr<CElement>& pElement)
	{
		m_Sketch.remove(pElement);
		UpdateAllViews(nullptr, 0, pElement.get());
		SetModifiedFlag();
	}

	SketchIterator begin() const
	{
		return std::begin(m_Sketch);
	}

	SketchIterator end() const
	{
		return std::end(m_Sketch);
	}

	
	afx_msg void OnPenstyleSolid();
	afx_msg void OnUpdatePenstyleSolid(CCmdUI *pCmdUI);
	afx_msg void OnPenstyleDashed();
	afx_msg void OnUpdatePenstyleDashed(CCmdUI *pCmdUI);
	afx_msg void OnPenstyleDotted();
	afx_msg void OnUpdatePenstyleDotted(CCmdUI *pCmdUI);
	afx_msg void OnPenstyleDashDotted();
	afx_msg void OnUpdatePenstyleDashDotted(CCmdUI *pCmdUI);
	afx_msg void OnPenstyleDashDotDot();
	afx_msg void OnUpdatePenstyleDashDot(CCmdUI *pCmdUI);
	
	std::shared_ptr<CElement> FindElement(const CPoint& point) const;
	void SendToBack(std::shared_ptr<CElement>& pElement);
	afx_msg void OnPenWidth();
	afx_msg void OnElementText();
	afx_msg void OnUpdateElementText(CCmdUI *pCmdUI);
	CRect GetDocExtent() const;
};
