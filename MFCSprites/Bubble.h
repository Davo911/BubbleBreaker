#pragma once
#include "spritelib.h"
class CBubble :
	public CSprite
{
public:
	CBubble();
	void set_img(int x,int y, int n_farb, CSpriteList &liste);
	int CBubble::GetFarbe();
	void CBubble::SetFarbe(int f);
	int CBubble::GetDelMark();
	void CBubble::SetDelMark(int s);
	int CBubble::GetDelStatus();
	void CBubble::SetDelStatus(int d);
	void CBubble::Search(int x, int y, int c_farbe, CBubble feld[12][16]);
	~CBubble();

	CSprite bubble_img;

protected:

	int farbe;
	int del_mark = 0;		//lösch markierung
	int del_status = 0;		// gelöscht status


};

