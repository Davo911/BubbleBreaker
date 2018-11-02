#include "stdafx.h"
#include "Bubble.h"


CBubble::CBubble(void)
{

}



void CBubble::set_img(int x,int y, int n_farb, CSpriteList &liste) {

	farbe = n_farb;
	if (bubble_img.Load("bubble2.bmp", CSize(50, 50)) == false) {
		AfxMessageBox(L"Bild nicht gefunden!");
	}
	bubble_img.SetZ(3);
	bubble_img.SetSpriteNumber(0,farbe);
	bubble_img.SetPosition(50 * x, 50 * y+200);

	liste.Insert(&bubble_img);
}

void CBubble::Search(int x, int y, int c_farbe,CBubble feld[12][16]) {
	

		if ((c_farbe == farbe) && (del_mark == 0)) {						//check ob selber farbe und unmarkiert
			if ((feld[y + 1][x].GetFarbe() == c_farbe) && ((y + 1) <= 11) ||//check Feldgrenzen
				(feld[y - 1][x].GetFarbe() == c_farbe) && ((y - 1) >= 0)  ||
				(feld[y][x + 1].GetFarbe() == c_farbe) && ((x + 1) <= 15) ||
				(feld[y][x - 1].GetFarbe() == c_farbe) && ((x - 1) >= 0)){

				del_mark = 1;
				

			if ((y + 1) <= 11) {
				feld[y + 1][x].Search(x, y + 1, c_farbe, feld);		//check darunter
			}
			if ((y - 1) >= 0) {
				feld[y - 1][x].Search(x, y - 1, c_farbe, feld);		//check darüber
			}
			if ((x + 1) <= 15) {
				feld[y][x + 1].Search(x + 1, y, c_farbe, feld);		//check rechts
			}
			if ((x - 1) >= 0) {
				feld[y][x - 1].Search(x - 1, y, c_farbe, feld);		//check links
			}
		}
	}
}






int CBubble::GetFarbe() {
	return farbe;
}
void CBubble::SetFarbe(int f) //5 - transparent,gelöscht
{
	if ((f<=5)&&(f>=0))
		farbe = f;
}
int CBubble::GetDelMark() {
	return del_mark;
}
void CBubble::SetDelMark(int s){
	if (s == 0 || 1)
	del_mark = s;
}

int CBubble::GetDelStatus() {
	return del_status;
}
void CBubble::SetDelStatus(int d) {
	if (d == 0 || 1)
	del_status = d;
}

CBubble::~CBubble()
{
}

