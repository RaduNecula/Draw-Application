
// ChildFrm.h : interface of the CChildFrame class
//

#pragma once
#include "afxext.h"

class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// Attributes
public:

// Operations
public:

// Overrides
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	// Status bar object
	CStatusBar m_StatusBar;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
