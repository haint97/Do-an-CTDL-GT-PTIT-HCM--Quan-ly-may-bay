#ifndef _AIRPLANE_H
#define _AIRPLANE_H
#include "Flight.h"

struct Airplane
{
	char id[30];
	int nChair;
	int nFlight = 0;
	LIST_FLIGHT listFlight;
};
typedef struct Airplane AIRPLANE;
typedef AIRPLANE* PTR_AIRPLANE;

struct ListAirplane
{
	int n = -1; //also index
	PTR_AIRPLANE *listAirplane = new PTR_AIRPLANE[MAX_AIRPLANE];
};
typedef struct ListAirplane LIST_AIRPLANE;
typedef LIST_AIRPLANE* PTR_LIST_AIRPLANE;

PTR_AIRPLANE FindAirplane(PTR_LIST_AIRPLANE l, char id[])
{
	if (l->n < 0) return NULL;
	for (int i = 0; i <= l->n; i++)
		if (_stricmp(l->listAirplane[i]->id, id) == 0) return l->listAirplane[i];
	return NULL;
}

int FindIndexAirplane(PTR_LIST_AIRPLANE l, char id[])
{
	if (l->n < 0) return -1;
	for (int i = 0; i <= l->n; i++)
		if (_strcmpi(l->listAirplane[i]->id, id) == 0) return i;
	return -1;
}

void OutputAirplane(PTR_AIRPLANE al, int ordinal)
{
	DeleteOldData(sizeof(keyDisplayAirplane) / sizeof(string), ordinal);
	Gotoxy(xKeyDisplay[0] + 1, Y_DISPLAY + 3 + ordinal); cout << al->id;
	Gotoxy(xKeyDisplay[1] + 1, Y_DISPLAY + 3 + ordinal); cout << al->nChair;
}

//check when input
bool DataAirplaneIsEmpty(PTR_AIRPLANE al)
{
	if (strlen(al->id) == 0) return true;
	if ((int)log10(al->nChair) + 1 == 0 || al->nChair == 0) return true;
	return false;
}

void SwapAirplane(PTR_AIRPLANE &a, PTR_AIRPLANE &b)
{
	PTR_AIRPLANE temp = a;
	a = b;
	b = temp;
}
void OutputListAirplane(PTR_LIST_AIRPLANE l)
{
	if (l == NULL) return;
	for (int i = 0; i <= l->n; i++)
		OutputAirplane(l->listAirplane[i], i);
}
void OutputListAirplanePerPage(PTR_LIST_AIRPLANE l, int indexBegin)
{
	if (l == NULL) return;
	for (int i = 0; i + indexBegin <= l->n && i < QUANTITY_PER_PAGE; i++)
		OutputAirplane(l->listAirplane[i+ indexBegin], i*2);
	Gotoxy(X_PAGE, Y_PAGE);
	cout << "Trang " << pageNowAirplane << "/" << totalPageAirplane;
}
bool DeleteAirplaneIsSucceed(PTR_LIST_AIRPLANE &l, char *id)
{
	int index = FindIndexAirplane(l, id);
	if (index == -1) return false; //esc no choose
	if (l->listAirplane[index]->listFlight.pHead != NULL) return false;
	for (int i = index; i < l->n; i++)
		l->listAirplane[i] = l->listAirplane[i + 1];
	l->n--;
	return true;
}

void InputAirplane(PTR_LIST_AIRPLANE &l, PTR_AIRPLANE al, bool isEdited = false)
{
	ShowCur(true);
	int ordinal = 0;
	bool isMoveUp = false;
	bool isSave = false;
	string id;
	int nChair = 0;
	bool idIsExist = false;
	if (isEdited)
	{
		id = al->id;
		nChair = al->nChair;
		//binding data
		Gotoxy(X_ADD + 6, 0 * 3 + Y_ADD);
		cout << id;
		Gotoxy(X_ADD + 6, 1 * 3 + Y_ADD);
		cout << nChair;
	}

	while (true)
	{
		switch (ordinal)
		{
		case 0:
			CheckMoveAndValidateID(id, isMoveUp, ordinal, isSave, 6);
			if (isEdited && _stricmp(al->id, id.c_str()) == 0)
			{
				idIsExist = false;
				break;  // no change ID
			}
			else if (FindAirplane(l, (char *)id.c_str()) == NULL)
			{
				idIsExist = false;
				break;
			}
			else idIsExist = true;
			break;
		case 1:
			CheckMoveAndValidateNumber(nChair, isMoveUp, ordinal, isSave, 6, MAX_TICKET);
			break;
		}//switch 

		if (isMoveUp)
		{
			if (ordinal == 0)isMoveUp = false;
			ordinal--;
		}
		else
		{
			if (ordinal == 1)isMoveUp = true;
			ordinal++;
		}
		if (isSave)
		{
			Gotoxy(X_NOTIFY, Y_NOTIFY);
			cout << setw(50) << setfill(' ') << " ";

			if (idIsExist)
			{
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << "Ma so khong duoc trung";
				
			}
			else
			{
				PTR_AIRPLANE temp = new AIRPLANE;
				strcpy(temp->id, id.c_str());
				temp->nChair = nChair;
				if (DataAirplaneIsEmpty(temp))
				{
					Gotoxy(X_NOTIFY, Y_NOTIFY);
					cout << "Cac truong du lieu khong dc de trong";
				}
				else
				{
					strcpy(al->id, id.c_str());
					al->nChair = nChair;
					if (isEdited)
					{
						int index = FindIndexAirplane(l, al->id);
						l->listAirplane[index] = al;						
					}
					else
					{
						InitListFlight(al->listFlight);
						l->listAirplane[++l->n] = new AIRPLANE;
						l->listAirplane[l->n] = al;
					}
					DeleteMenuAdd();
					totalPageAirplane = l->n / QUANTITY_PER_PAGE + 1;
					return;
				}
			}
			isSave = false;
		}
		else
			isSave = false;
	}
	ShowCur(false);
}
void SetDefaultChosenAirplane(PTR_LIST_AIRPLANE l, int ordinal)
{
	SetBGColor(GREEN);
	OutputAirplane(l->listAirplane[ordinal], (ordinal % QUANTITY_PER_PAGE)*2);
	SetBGColor(PURPLE);
}
void   EffectiveMenuAirplane(int ordinal, PTR_LIST_AIRPLANE l)
{
	int current = ordinal;
	SetDefaultChosenAirplane(l, current);
	OutputAirplane(l->listAirplane[currposPrecAirplane], (currposPrecAirplane % QUANTITY_PER_PAGE) * 2);
	currposPrecAirplane = current;
}
void ChangePageAirplane(PTR_LIST_AIRPLANE l)
{
	system("cls");
	Display(keyDisplayAirplane, sizeof(keyDisplayAirplane) / sizeof(string));
	DeleteNote(sizeof(keyDisplayAirplane) / sizeof(string));
	currposAirplane = (pageNowAirplane - 1) * QUANTITY_PER_PAGE;
	currposPrecAirplane = (pageNowAirplane - 1) * QUANTITY_PER_PAGE;
	Gotoxy(X_PAGE, Y_PAGE);
	cout << "Trang " << pageNowAirplane << "/" << totalPageAirplane;
}
int ChooseAirplane(PTR_LIST_AIRPLANE l)
{
	ShowCur(false);
	int key;
	int keyboard_read = 0;
	pageNowAirplane = 1;
	currposAirplane = 0;
	currposPrecAirplane = 0;
	OutputListAirplanePerPage(l,0);
	SetDefaultChosenAirplane(l, currposAirplane);
	
	while (true)
	{
		
		while (_kbhit())
		{
			keyboard_read = _getch();
			if (keyboard_read == 0)
				keyboard_read = _getch();
			switch (keyboard_read)
			{
			case KEY_UP:
				if (currposAirplane % QUANTITY_PER_PAGE > 0)
				{
					currposAirplane = currposAirplane - 1;
					EffectiveMenuAirplane(currposAirplane, l);
				}
				break;
			case KEY_DOWN:
				if (currposAirplane % QUANTITY_PER_PAGE < QUANTITY_PER_PAGE - 1 && currposAirplane < l->n)
				{
					currposAirplane = currposAirplane + 1;
					EffectiveMenuAirplane(currposAirplane, l);
				}
				break;
			case PAGE_DOWN:
				if (pageNowAirplane < totalPageAirplane)
				{

					pageNowAirplane++;
					ChangePageAirplane(l);
					OutputListAirplanePerPage(l, (pageNowAirplane - 1) * QUANTITY_PER_PAGE);
					SetDefaultChosenAirplane(l, currposAirplane);

				}
				break;
			case PAGE_UP:
				if (pageNowAirplane > 1)
				{

					pageNowAirplane--;
					ChangePageAirplane(l);
					OutputListAirplanePerPage(l, (pageNowAirplane - 1) * QUANTITY_PER_PAGE);
					SetDefaultChosenAirplane(l, currposAirplane);

				}
				break;
			case ESC:
				ShowCur(false);
				return -1;
				break; // no choose
			case ENTER:
				ShowCur(false);
				return currposAirplane;
				break;
			}
		}
		
	}
}

void SortByNumberFlight(PTR_LIST_AIRPLANE &l)
{
	for (int i = 0; i < l->n; i++)
		for (int j = i + 1; j <= l->n; j++)
			if (l->listAirplane[i]->listFlight.n < l->listAirplane[j]->listFlight.n)
				SwapAirplane(l->listAirplane[i], l->listAirplane[j]);
}
int DisplayAndChooseIndexAirplane(PTR_LIST_AIRPLANE l, string title)
{
	if (l == NULL) return -1;
	if (l->n<0) return -1;
	system("cls");
	Gotoxy(X_TITLE, Y_TITLE); cout << title;
	Display(keyDisplayAirplane, sizeof(keyDisplayAirplane) / sizeof(string));
	DeleteNote(sizeof(keyDisplayAirplane) / sizeof(string));
	int indexAirplanee = ChooseAirplane(l);
	return indexAirplanee;
}

void ChangePageManageAirplane(PTR_LIST_AIRPLANE l)
{
	system("cls");
	Gotoxy(X_TITLE, Y_TITLE); cout << "QUAN LY CAC MAY BAY";
	OutputListAirplanePerPage(l, (pageNowAirplane - 1) * QUANTITY_PER_PAGE);
	Display(keyDisplayAirplane, sizeof(keyDisplayAirplane) / sizeof(string));
}
void MenuManageAirplane(PTR_LIST_AIRPLANE &l)
{
backMenu:
	system("cls");
	pageNowAirplane = 1;
	OutputListAirplanePerPage(l, 0);
	Display(keyDisplayAirplane, sizeof(keyDisplayAirplane) / sizeof(string));
	int key;
	Gotoxy(X_TITLE, Y_TITLE); cout << "QUAN LY CAC MAY BAY";
	Gotoxy(X_PAGE, Y_PAGE);
	while (true)
	{
		
		while (_kbhit())
		{		
			
			key = _getch();
			if (key == 0 || key == 224)
			{
				key = _getch();
				if (key == KEY_F2)
				{
					PTR_AIRPLANE al = new AIRPLANE;
					DisplayEdit(keyDisplayAirplane, sizeof(keyDisplayAirplane) / sizeof(string), 35);
					InputAirplane(l, al);
					totalPageAirplane = l->n / QUANTITY_PER_PAGE + 1;
					pageNowAirplane = 1;
					OutputListAirplanePerPage(l, (pageNowAirplane - 1) * QUANTITY_PER_PAGE);
					Gotoxy(X_NOTIFY, Y_NOTIFY);
					cout << "Them thanh cong";
				}
				else if (key == KEY_F3) //f3
				{
					int k = ChooseAirplane(l);
					if (k == -1) goto backMenu;
					Gotoxy(X_NOTIFY, Y_NOTIFY);
					cout << "Ban co chac chan xoa? Enter dong y";
					key = _getch();
					Gotoxy(X_NOTIFY, Y_NOTIFY);
					cout << setw(50) << setfill(' ') << " ";
					if (key == ENTER)
					{
						bool isDeleted = DeleteAirplaneIsSucceed(l, l->listAirplane[k]->id);
						if (!isDeleted)
						{
							Gotoxy(X_NOTIFY, Y_NOTIFY);
							cout << "Xoa that bai. Trong chuyen bay con du lieu."<<endl;
							Gotoxy(X_NOTIFY, Y_NOTIFY+1);
							cout << "Nhap phim bat ky de tiep tuc ";
							_getch();
							goto backMenu;
						}
						else
						{
							system("cls");
							Display(keyDisplayAirplane, sizeof(keyDisplayAirplane) / sizeof(string));
							if ((l->n + 1) % QUANTITY_PER_PAGE == 0) pageNowAirplane--;
							totalPageAirplane = l->n / QUANTITY_PER_PAGE + 1;
							OutputListAirplanePerPage(l, (pageNowAirplane - 1) * QUANTITY_PER_PAGE);
						}
					}
					else
						goto backMenu;
				}
				else if (key == KEY_F4)
				{
					int k = ChooseAirplane(l);
					if (k == -1) goto backMenu;;
					Gotoxy(X_ADD, 40);
					DisplayEdit(keyDisplayAirplane, sizeof(keyDisplayAirplane) / sizeof(string), 35);
					InputAirplane(l, l->listAirplane[k], true);
					OutputListAirplanePerPage(l, (pageNowAirplane - 1) * QUANTITY_PER_PAGE);
					Gotoxy(X_NOTIFY, Y_NOTIFY);
					cout << "Sua thanh cong";
				}
				else if (key == PAGE_DOWN && pageNowAirplane < totalPageAirplane)
				{
					
					pageNowAirplane++;
					ChangePageManageAirplane(l);
				}
				else if (key == PAGE_UP && pageNowAirplane > 1)
				{
					
					pageNowAirplane--;
					ChangePageManageAirplane(l);
					
				}
			}
			else if (key == ESC)
				return;
		}
	}
}

#endif