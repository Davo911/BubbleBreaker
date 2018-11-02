
// MFCSpritesDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "MFCSprites.h"
#include "MFCSpritesDlg.h"
#include "afxdialogex.h"
#include "Bubble.h"
#include <iostream>
#include <fstream>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCSpritesDlg-Dialogfeld



CMFCSpritesDlg::CMFCSpritesDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCSpritesDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCSpritesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCSpritesDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CMFCSpritesDlg-Meldungshandler

BOOL CMFCSpritesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Symbol für dieses Dialogfeld festlegen.  Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden
	srand((unsigned)time(NULL));
	SetTimer(2, 25, NULL);

	if (bkg.Load("feld.bmp", CSize(1100, 1100),NULL) == false) {
		AfxMessageBox(L"Bkg Bild nicht gefunden!");
		return FALSE;
	}
	m_buf.Load("feld.bmp");
	bkg.SetZ(0);
	if (opt.Load("OPTIONSBKG.bmp", CSize(600, 375), 1) == false) {
		AfxMessageBox(L"OPT Bild nicht gefunden!");
		return FALSE;
	}
	opt.SetZ(50);
	opt.SetPosition(900, 300);

	if (about.Load("ABOUT.bmp", CSize(468,475), 1) == false) {
		AfxMessageBox(L"about Bild nicht gefunden!");
		return FALSE;
	}
	about.SetZ(50);
	about.SetPosition(-568, 300);

	//Buttons
	if (b_init.Load("init.bmp", CSize(247,100), 1) == false) {
		AfxMessageBox(L"Init Bild nicht gefunden!");
		return FALSE;
	}
	b_init.SetZ(5);
	b_init.SetPosition(300, 0);
	b_init.SetSpriteNumber(0, 0);

	if (b_opt.Load("OPTIONS.bmp", CSize(247, 100), 1) == false) {
		AfxMessageBox(L"Options Bild nicht gefunden!");
		return FALSE;
	}
	b_opt.SetZ(6);
	b_opt.SetPosition(550, 0);
	b_opt.SetSpriteNumber(0, 0);

	if (b_exit.Load("EXIT.bmp", CSize(247, 100), 1) == false) {
		AfxMessageBox(L"Exit Bild nicht gefunden!");
		return FALSE;
	}
	b_exit.SetZ(7);
	b_exit.SetPosition(550, 100);
	b_exit.SetSpriteNumber(0, 0);

	if (b_save.Load("SAVE.bmp", CSize(247, 100), 1) == false) {
		AfxMessageBox(L"save Bild nicht gefunden!");
		return FALSE;
	}
	b_save.SetZ(7);
	b_save.SetPosition(300, 100);
	b_save.SetSpriteNumber(0, 0);

	if (b_info.Load("INFO.bmp", CSize(51, 52), 1) == false) {
		AfxMessageBox(L"info Bild nicht gefunden!");
		return FALSE;
	}
	b_info.SetZ(60);
	b_info.SetPosition(900, 900);
	b_info.SetSpriteNumber(0, 1);


	if (b_switch[0].Load("SWITCH.bmp", CSize(109, 42), 1) == false) {
		AfxMessageBox(L"switch Bild nicht gefunden!");
		return FALSE;
	}
	b_switch[0].SetZ(55);
	b_switch[0].SetPosition(900, 900);
	b_switch[0].SetSpriteNumber(0, 1);
	b_switch[1] = b_switch[2] = b_switch[3] = b_switch[0];

	if (digit[0].Load("DIGITS.bmp", CSize(73, 121), 1) == false) {
		AfxMessageBox(L"Digits nicht gefunden!");
		return FALSE;
	}
	digit[0].SetZ(15);
	digit[0].SetSpriteNumber(0, 0);
	digit[3] = digit[2] = digit[1] = digit[0];


	for (int i = 0; i < 4; i++) {
		digit[i].SetPosition(i*73+1, 80);
	}



	if (logo.Load("me112x260.bmp", CSize(112,260), 1) == false) {
		AfxMessageBox(L"Logo Bild nicht gefunden!");
		return FALSE;
	}
	logo.SetZ(100);
	logo.SetPosition(100,0);
	SetTimer(1, 70, NULL);

//Bubbles
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 12; j++) {
			feld[j][i].set_img(i,j, rand() % 4, liste);






		}
	}
	for (int i = 0; i < 4; i++) {
		liste.Insert(&b_switch[i]);
		liste.Insert(&digit[i]);
	}
	liste.Insert(&logo);
	liste.Insert(&b_save);
	liste.Insert(&bkg);
	liste.Insert(&opt);
	liste.Insert(&about);
	liste.Insert(&b_info);
	liste.Insert(&b_init);
	liste.Insert(&b_exit);
	liste.Insert(&b_opt);
	liste.SetWorkspace(&m_buf);

	SetWindowPos(	NULL, 0, 0,					//Fenster Einstellungen
					bkg.DibWidth()+16,			//X
					bkg.DibHeight()+38,			//Y
					SWP_NOZORDER | SWP_NOMOVE);	//
					

	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen.  Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.

void CMFCSpritesDlg::OnPaint()
{
	CPaintDC dc(this); // Gerätekontext zum Zeichnen
	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Symbol in Clientrechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		liste.RedrawAll(&dc, 0, 0);
		CDialogEx::OnPaint();
	}

}

// Die System ruft diese Funktion auf, um den Cursor abzufragen, der angezeigt wird, während der Benutzer
//  das minimierte Fenster mit der Maus zieht.
HCURSOR CMFCSpritesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCSpritesDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	CSprite * hit = liste.HitTest(point);

	int popped = 0;		//pro klick zerplatzt

	//markiere gleichfarbige
	if (opt_f == 1) {
		for (int y = 0; y < 12; y++) {
			for (int x = 0; x < 16; x++) {
				if (((feld[y][x].bubble_img.HitTest(point, 0)) == 1)) {
					int c = feld[y][x].GetFarbe();
					feld[y][x].Search(x, y, c, feld);
					y = x = 16;

					//lösche markierte
					for (y = 0; y < 12; y++) {
						for (x = 0; x < 16; x++) {
							if ((feld[y][x].GetDelMark() == 1)) {					// lösche markierte
								liste.Remove(&feld[y][x].bubble_img);				// Bubble Sprite aus liste
								liste.Update(&dc, 0, 0);
								feld[y][x].bubble_img.SetPosition(1000, 1000);		// ausßerhalb den displays positionieren
								feld[y][x].bubble_img.SetSpriteNumber(0, 5);
								feld[y][x].SetDelMark(0);							// Markierung entfernen
								feld[y][x].SetDelStatus(1);							// als gelöscht setzen
								feld[y][x].SetFarbe(5);
								popped++;											// anzahl gelöschter bubbles hochzählen

							}
						}
					}



					//Punkterechner
					punkte += (popped * (popped - 1));
					s_punkte.Format(L"Punkte : %d", punkte);
					digit[0].SetSpriteNumber(punkte/1000 % 10,0);
					digit[1].SetSpriteNumber(punkte/100 % 10,0);
					digit[2].SetSpriteNumber(punkte/10 % 10,0);
					digit[3].SetSpriteNumber(punkte % 10,0);
				}
			}
		}



		// nachrücker feld[y][x]   Center
		// lücke feld[y+1][x]		Down



				//Nachrücken
		if (popped >= 1) {
			for (int y = 10; y >= 0; y--) {
				for (int x = 15; x >= 0; x--) {
					if ((feld[y][x].GetDelStatus() == 0) && (feld[y + 1][x].GetDelStatus() == 1)) {
						int YPos = 0, Anim = 1;
						liste.Remove(&feld[y + 1][x].bubble_img);
						if (BAnim == 1) {
							while (Anim == 1) {
								feld[y][x].bubble_img.SetPosition((feld[y][x].bubble_img.GetXPos()), (feld[y][x].bubble_img.GetYPos() + 5));
								YPos += 5;
								liste.Update(&dc, 0, 0);
								Sleep(1);
								if (YPos == 50) { Anim = 0; }
							}
						}
						else if (BAnim == 0) { feld[y][x].bubble_img.SetPosition((feld[y][x].bubble_img.GetXPos()), (feld[y][x].bubble_img.GetYPos() + 50)); }
						feld[y + 1][x].bubble_img.SetSpriteNumber((0), (feld[y][x].GetFarbe()));
						feld[y + 1][x].bubble_img.SetPosition((feld[y][x].bubble_img.GetXPos()), (feld[y][x].bubble_img.GetYPos()));
						liste.Insert(&feld[y + 1][x].bubble_img);
						feld[y + 1][x].SetFarbe(feld[y][x].GetFarbe());
						feld[y][x].bubble_img.SetPosition(1000, 1000);
						feld[y][x].SetDelStatus(1);
						feld[y + 1][x].SetDelStatus(0);
						feld[y][x].SetFarbe(5);
						x = 15; y = 10;
					}
				}
			}
		}





		//feld[y][x+1] --> rechts
		//feld[y][x-1] --> links										//SORRY für diese verschachtelung :)
		int k = 1;
		while (k == 1) {
			for (int i = 15; i > 0; i--) {							//suche in letzter zeile nach lücke
				if ((feld[11][i].GetDelStatus() == 1)) {			//^
					for (int j = 11; j > 0; j--) {					//schau ob spalte wirklich leer
						if (feld[j][i].GetDelStatus() == 0) {/*wenn in spalte noch etwas ist ignore*/ }
						else {										//wenn komplett leer rücke von links rein
							for (int x = i, y = 11; y >= 0; y--) {
								if ((feld[y][x - 1].GetDelStatus() == 0) && ((feld[y][x].GetDelStatus() == 1))) {
									//um 90 grad gedrehter nachrück algo
									liste.Remove(&feld[y][x].bubble_img);
									feld[y][x - 1].bubble_img.SetPosition((feld[y][x - 1].bubble_img.GetXPos() + 50), (feld[y][x - 1].bubble_img.GetYPos()));
									feld[y][x].bubble_img.SetSpriteNumber((0), (feld[y][x - 1].GetFarbe()));
									feld[y][x].bubble_img.SetPosition((feld[y][x - 1].bubble_img.GetXPos()), (feld[y][x - 1].bubble_img.GetYPos()));
									liste.Insert(&feld[y][x].bubble_img);
									feld[y][x].SetFarbe(feld[y][x - 1].GetFarbe());
									feld[y][x - 1].bubble_img.SetPosition(1000, 1000);
									feld[y][x - 1].SetDelStatus(1);
									feld[y][x].SetDelStatus(0);
									feld[y][x - 1].SetFarbe(5);
									liste.Update(&dc, 0, 0);
									Sleep(1);
									i = 15;
								}
							}
						}
					}
				}k = 0;
			}
		}
	}


	//BUTTONS
		for (int y = 0; y < 12; y++) {
			for (int x = 0; x < 16; x++) {
				if ((b_init.HitTest(point, 0)) == 1) {
					b_init.SetSpriteNumber(0, 0);
					liste.Update(&dc, 0, 0);
					liste.Remove(&feld[y][x].bubble_img);
					feld[y][x].set_img(x, y, rand() % 4, liste);
					feld[y][x].SetDelMark(0);
					feld[y][x].SetDelStatus(0);
					SetWindowText(L"Bubble Breaker");
					punkte = 0;
				}
			}
		}


			if ((b_opt.HitTest(point, 0)) == 1) {
				
				if (opt.GetXPos() >= 800) {
					AnimEngine(1);
				}
				else { 
					AnimEngine(2);
				}
			}
			if ((b_exit.HitTest(point, 0)) == 1) {
				b_exit.SetSpriteNumber(0, 0);
				liste.Update(&dc, 0, 0);
				Sleep(3);
				exit(0);
			}
			if ((b_save.HitTest(point, 0)) == 1) {
				b_save.SetSpriteNumber(0, 0);
				AfxMessageBox(L"Spielstand gespeichert!");
				time(&datum);
				fstream highscore;
				highscore.open("Highscore.txt",std::ios::app);
				if (highscore.fail()) {
					AfxMessageBox(L"Konnte Highscore-Table nicht laden!");
				}
				highscore <<endl<< "Score : " << punkte << "	|	" << asctime(localtime(&datum)) << endl;
				if (highscore.is_open()) { highscore.close(); }
			}
		
			if ((b_info.HitTest(point, 0)) == 1) {
				about.SetPosition(-568, 900);
				AnimEngine(3);
			}
			if ((about.HitTest(point, 0)) == 1) {
				AnimEngine(4);
			}



	//Option Switches
	for (int i = 0; i < 4; i++) {
		if (b_switch[i].HitTest(point, 0) == 1) {
			if (swx[i] == 0) {
				b_switch[i].SetSpriteNumber(0, 1);
				swx[i] = 1;
				if (swx[0] == 1) { SetTimer(1, 60, NULL); }
				if (swx[1] == 1) { DnD = 1; }
				if (swx[2] == 1) { BAnim = 1; }
			}
			else { b_switch[i].SetSpriteNumber(0, 0); swx[i] = 0; 
			if (swx[0] == 0) { KillTimer(1); }
			if (swx[1] == 0) { DnD = 0; }
			if (swx[2] == 0) { BAnim = 0; }
			}
		}
	}
				liste.Update(&dc, 0, 0);
				CDialogEx::OnLButtonUp(nFlags, point);
	}

void CMFCSpritesDlg::AnimEngine(int ereignis) {
		switch (m_tabelle[ereignis][m_zustand].aktion) {
		case -1: return;	//ignore event
		case 0: break;		//do nothing but change m_zustans
		case 1: 
			b_opt.SetSpriteNumber(0, 0);
			if (opt.GetXPos() != 100) {
			opt.SetPosition(opt.GetXPos() - 50, opt.GetYPos());
			b_switch[0].SetPosition(opt.GetXPos() + 400, opt.GetYPos() + 95);
			b_switch[1].SetPosition(opt.GetXPos() + 400, opt.GetYPos() + 180);
			b_switch[2].SetPosition(opt.GetXPos() + 400, opt.GetYPos() + 275);
			b_info.SetPosition(opt.GetXPos() + 50, opt.GetYPos() + 30);

			if (about.GetXPos() > 0) {
				about.SetPosition(about.GetXPos() - 70, about.GetYPos());
			}
			

  }
			opt_f = 0;
			break;
		case 2:
			b_opt.SetSpriteNumber(0, 0);

			if (opt.GetXPos() != 900) { 
			opt.SetPosition(opt.GetXPos() + 50, opt.GetYPos());
			b_switch[0].SetPosition(opt.GetXPos() + 400, opt.GetYPos() + 95);
			b_switch[1].SetPosition(opt.GetXPos() + 400, opt.GetYPos() + 180);
			b_switch[2].SetPosition(opt.GetXPos() + 400, opt.GetYPos() + 275);
			b_info.SetPosition(opt.GetXPos() + 50, opt.GetYPos() + 30);
  }
			if (about.GetYPos() < 800) {
				about.SetPosition(about.GetXPos(), about.GetYPos() + 40);
			}
			opt_f = 1;
			break;
		case 3:
			b_info.SetSpriteNumber(0, 1);
			if ((about.GetXPos() <= 150)) {
			opt.SetPosition(opt.GetXPos() + 50, opt.GetYPos());
			b_switch[0].SetPosition(opt.GetXPos() + 400, opt.GetYPos() + 95);
			b_switch[1].SetPosition(opt.GetXPos() + 400, opt.GetYPos() + 180);
			b_switch[2].SetPosition(opt.GetXPos() + 400, opt.GetYPos() + 275);
			b_info.SetPosition(opt.GetXPos() + 50, opt.GetYPos() + 30);
			about.SetPosition(about.GetXPos() + 50, 300);
  }
			break;
		case 4:

			
			break;
		}
		m_zustand = m_tabelle[ereignis][m_zustand].naechster_zustand;
	}

void CMFCSpritesDlg::OnLButtonDown(UINT nFlags, CPoint point)
{	CClientDC dc(this);
	CSprite * hit = liste.HitTest(point);


			if ((b_init.HitTest(point, 0)) == 1) {
				b_init.SetSpriteNumber(0, 1);
			}
			if ((b_opt.HitTest(point, 0)) == 1) {
				b_opt.SetSpriteNumber(0, 1);
			}
			if ((b_exit.HitTest(point, 0)) == 1) {
				b_exit.SetSpriteNumber(0, 1);
			}
			if ((b_save.HitTest(point, 0)) == 1) {
				b_save.SetSpriteNumber(0, 1);
			}
			if ((b_info.HitTest(point, 0)) == 1) {
				b_info.SetSpriteNumber(0, 0);
			}



	liste.Update(&dc, 0, 0);
	CDialogEx::OnLButtonDown(nFlags, point);
}



void CMFCSpritesDlg::OnTimer(UINT_PTR nIDEvent)
{
	CClientDC dc(this);

	//Logo Spin
	static int i = 0;
	if (nIDEvent == 1) {
		logo.SetSpriteNumber(i % 20, 0);
		i++;
	}
	//OPT IN
if ((nIDEvent == 2)) {
	AnimEngine(0);
	}
	//OPT OUT
	else if ((nIDEvent == 3)) {
		
	}
	//ABOUT DIALOG
	if (nIDEvent == 4) { 
		
	}
	//ABOUT OUT
	if (nIDEvent == 5) {

	}

	liste.Update(&dc, 0, 0);
	CDialogEx::OnTimer(nIDEvent);
}




void CMFCSpritesDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this); 
	CSprite * hit = liste.HitTest(point);

	//Logo move
	if ((logo.HitTest(point, 1)) && (nFlags & MK_LBUTTON) && DnD == 1) {
		logo.SetPosition(point.x-50, point.y-40);
	}


	CDialogEx::OnMouseMove(nFlags, point);
}
