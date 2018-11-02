
// MFCSpritesDlg.h: Headerdatei
//

#pragma once

#include "spritelib.h"
#include "Bubble.h"


// CMFCSpritesDlg-Dialogfeld
class CMFCSpritesDlg : public CDialogEx
{
// Konstruktion
public:
	CMFCSpritesDlg(CWnd* pParent = NULL);	// Standardkonstruktor

// Dialogfelddaten
	enum { IDD = IDD_MFCSPRITES_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


// Implementierung
protected:
	HICON m_hIcon;
	CBubble feld[12][16];
	CDIB m_buf;
	CSprite bkg;
	CSprite opt;
	CSprite about;
	CSprite b_init;
	CSprite b_opt;
	CSprite b_exit;
	CSprite logo;
	CSprite b_info;
	CSprite b_save;
	CSprite b_switch[4];
	CSprite digit[4];
	int swx[3] = { 1,1,1 };
	int punkte = 0;
	CString s_punkte;
	//int digits[4];
	int mark_count = 0;
	int opt_f = 1;
	int DnD = 1;
	int BAnim = 1;
	time_t datum;
	int m_zustand = 0;
	struct {
		int naechster_zustand;
		int aktion;
	}m_tabelle[5][3] = {
	{ {0,2}, {1,1}, {2,3} },
	{ {1,0}, {-1,-1} , {-1, -1} },
	{ {-1,-1}, {0,0}, {-1,-1} },
	{ {-1,-1}, {2,0}, {-1,-1} },
	{ {-1,-1}, {-1,-1}, {0,2} }
	};



	CSpriteList liste;
	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	void AnimEngine(int ereignis);

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

