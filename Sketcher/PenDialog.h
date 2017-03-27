#pragma once


// CPenDialog dialog

class CPenDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPenDialog)

public:
	CPenDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPenDialog();

	int m_PenWidth;  //Record the current pen width

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PENWIDTH_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPenwidth0();
	afx_msg void OnPenwidth1();
	afx_msg void OnPenwidth2();
	afx_msg void OnPenwidht3();
	afx_msg void OnPenwidth4();
	afx_msg void OnPenwidth5();
};
