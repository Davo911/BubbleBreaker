
// MFCSprites.h: Hauptheaderdatei für die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "'stdafx.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"		// Hauptsymbole


// CMFCSpritesApp:
// Siehe MFCSprites.cpp für die Implementierung dieser Klasse
//

class CMFCSpritesApp : public CWinApp
{
public:
	CMFCSpritesApp();

// Überschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CMFCSpritesApp theApp;