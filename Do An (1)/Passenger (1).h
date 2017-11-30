#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#ifndef _PASSENGER_H
#define _PASSENGER_H

#include "DateTime.h"
#include "Display.h"

//nPassenger begin 0 

struct Passenger
{
	int  sex = 1; //1 male, 2 female
	unsigned int id = 0;
	char firstName[20], lastName[20];
	bool isBooked = false;
};
typedef struct Passenger PASSENGER;

struct NodePassenger
{
	PASSENGER data;
	struct NodePassenger* pLeft, *pRight;
};
typedef struct NodePassenger NODE_PASSENGER;
typedef NODE_PASSENGER* TREE_PASSENGER;

void InitTreePassenger(TREE_PASSENGER &t)
{
	nPassenger = -1;
	t = NULL;
}
bool IsEmpty(TREE_PASSENGER t)
{
	return t == NULL;
}
bool CheckIdIsExisted(TREE_PASSENGER t, unsigned int x)
{
	if (t != NULL)
	{
		if (t->data.id == x)
			return true;
		if (t->data.id > x)
			CheckIdIsExisted(t->pLeft, x);
		else
			CheckIdIsExisted(t->pRight, x);
	}
	return false;
}
NODE_PASSENGER* FindPassenger(TREE_PASSENGER t, unsigned int idPassenger)
{
	if (t != NULL)
	{
		NODE_PASSENGER* p = t;
		while (p != NULL)
		{
			if (p->data.id == idPassenger)
				return p;
			else if (p->data.id > idPassenger)
				p = p->pLeft;
			else
				p = p->pRight;
		}
	}
	return NULL;
}

void InsertPassengerToTree(TREE_PASSENGER &t, PASSENGER x)
{
	//tree empty, x is root of tree
	if (t == NULL)
	{
		NODE_PASSENGER* p = new NODE_PASSENGER;
		p->data = x;
		p->pLeft = p->pRight = NULL;
		t = p;
		arrPassengerId[++nPassenger] = x.id;
	}
	else
	{
		if (x.id < t->data.id)
			InsertPassengerToTree(t->pLeft, x);
		else if (x.id > t->data.id)
			InsertPassengerToTree(t->pRight, x);
	}
}

void FindReplace(NODE_PASSENGER* &p, NODE_PASSENGER* &q)
{
	////way 1:
	//if (q->pLeft != NULL)
	//{
	//	findReplace(p, q->pLeft);
	//}
	//else //at tail, at the end
	//{
	//	p->data = q->data;
	//	p = q;
	//	q = q->pRight;
	//}

	//way 2:
	if (q->pRight != NULL)
	{
		FindReplace(p, q->pRight);
	}
	else
	{
		p->data = q->data;
		p = q;
		q = q->pLeft;
	}
}

bool IsDeletedPassenger(TREE_PASSENGER &t, PASSENGER x)
{
	if (t == NULL)
		return false;
	else
	{
		if (x.id > t->data.id)
			IsDeletedPassenger(t->pRight, x);
		else if (x.id < t->data.id)
			IsDeletedPassenger(t->pLeft, x);
		else // x.id = t->data.id
		{
			NODE_PASSENGER *temp = t;
			if (t->pLeft == NULL)     //1.
				t = t->pRight;
			else if (t->pRight == NULL)
				t = t->pLeft;
			//5. 1-> delete node have 0 or 1 child
			else // node have 2 child
			{
				//way 2: rightest of left
				FindReplace(temp, t->pLeft);
			}
			delete temp;
			return true;

		}
	}
}




void QuickSort(int left, int right, unsigned int a[]) {
	int key = a[(left + right) / 2];
	int i = left, j = right;
	do {
		while (a[i] < key) i++;
		while (a[j] > key) j--;
		if (i <= j) {
			if (i < j) swap(a[i], a[j]);
			i++;	j--;
		}
	} while (i <= j);
	if (left < j) QuickSort(left, j, a);
	if (right > i) QuickSort(i, right, a);
}

void OutputPassenger(PASSENGER p, int locate)
{
	DeleteOldData(sizeof(keyDisplayPassenger) / sizeof(string), locate);
	Gotoxy(xKeyDisplay[0] + 1, Y_DISPLAY + 3 + locate); cout << p.id;
	Gotoxy(xKeyDisplay[1] + 1, Y_DISPLAY + 3 + locate); cout << p.firstName;
	Gotoxy(xKeyDisplay[2] + 1, Y_DISPLAY + 3 + locate); cout << p.lastName;
	Gotoxy(xKeyDisplay[3] + 1, Y_DISPLAY + 3 + locate);
	if (p.sex == 1)cout << "Nam";
	else cout << "Nu";
}

int indexOutPassenger = -1;
void OutputListPassenger(TREE_PASSENGER t)
{
	if (t != NULL)
	{
		OutputListPassenger(t->pLeft);
		OutputPassenger(t->data, ++indexOutPassenger);
		OutputListPassenger(t->pRight);
	}
}


void OutputListPassengerPerPage(TREE_PASSENGER t, int indexBegin)
{
	for (int i = 0; i + indexBegin <= nPassenger && i < QUANTITY_PER_PAGE; i++)
	{
		NODE_PASSENGER* p = FindPassenger(t, arrPassengerId[i + indexBegin]);
		OutputPassenger(p->data, i * 2);
	}
	Gotoxy(X_PAGE, Y_PAGE);
	cout << "Trang " << pageNowPassenger << "/" << totalPagePassenger;
}


void SetDefaultChosenPassenger(PASSENGER p, int ordinal)
{
	SetBGColor(GREEN);
	OutputPassenger(p, ordinal % QUANTITY_PER_PAGE);
	SetBGColor(PURPLE);
}
void   EffectiveMenuPassenger(int index, PASSENGER newPassenger, PASSENGER oldPassenger)
{
	int current = index;

	SetBGColor(GREEN);
	OutputPassenger(newPassenger, (current % QUANTITY_PER_PAGE) * 2);
	SetBGColor(PURPLE);
	OutputPassenger(oldPassenger, (currposPrecPassenger % QUANTITY_PER_PAGE) * 2);
	currposPrecPassenger = current;
}

void ChangePagePassenger(TREE_PASSENGER t)
{
	currposPassenger = (pageNowPassenger - 1) * QUANTITY_PER_PAGE;
	currposPrecPassenger = (pageNowPassenger - 1) * QUANTITY_PER_PAGE;
	system("cls");
	Display(keyDisplayPassenger, sizeof(keyDisplayPassenger) / sizeof(string));
	DeleteNote(sizeof(keyDisplayPassenger) / sizeof(string));

	

}
NODE_PASSENGER* ChoosePassenger(TREE_PASSENGER &t)
{
	if (t == NULL) return NULL;
	ShowCur(false);
	int key;
	int keyboard_read = 0;
	int PASS = 1;
	QuickSort(0, nPassenger, arrPassengerId);
	Display(keyDisplayPassenger, sizeof(keyDisplayPassenger) / sizeof(string));
	pageNowPassenger = 1;
	currposPassenger = (pageNowPassenger - 1) * QUANTITY_PER_PAGE;
	currposPrecPassenger = (pageNowPassenger - 1) * QUANTITY_PER_PAGE;
	NODE_PASSENGER* newPassenger = FindPassenger(t, arrPassengerId[0]);
	OutputListPassengerPerPage(t, 0);
	SetDefaultChosenPassenger(newPassenger->data, currposPassenger);
	NODE_PASSENGER* oldPassenger = NULL;
	Gotoxy(X_PAGE, Y_PAGE);
	cout << "trang " << pageNowPassenger << "/" << totalPagePassenger;

	while (PASS)
	{
		keyboard_read = _getch();
		if (keyboard_read == 0)
			keyboard_read = _getch();

		switch (keyboard_read)
		{


		case KEY_UP:
			if (currposPassenger % QUANTITY_PER_PAGE > 0)
			{
				currposPassenger = currposPassenger - 1;
				oldPassenger = newPassenger;
				newPassenger = FindPassenger(t, arrPassengerId[currposPassenger]);
				EffectiveMenuPassenger(currposPassenger, newPassenger->data, oldPassenger->data);
			}
			break;
		case KEY_DOWN:
			if (currposPassenger % QUANTITY_PER_PAGE < QUANTITY_PER_PAGE - 1 && currposPassenger < nPassenger)
			{
				currposPassenger = currposPassenger + 1;
				oldPassenger = newPassenger;
				newPassenger = FindPassenger(t, arrPassengerId[currposPassenger]);
				EffectiveMenuPassenger(currposPassenger, newPassenger->data, oldPassenger->data);
			}
			break;


		case PAGE_DOWN:
			if (pageNowPassenger < totalPagePassenger)
			{

				pageNowPassenger++;
				ChangePagePassenger(t);

				newPassenger = FindPassenger(t, arrPassengerId[currposPassenger]);
				oldPassenger = newPassenger;


				OutputListPassengerPerPage(t, (pageNowPassenger - 1) * QUANTITY_PER_PAGE);
				SetDefaultChosenPassenger(newPassenger->data, currposPassenger);


			}
			break;
		case PAGE_UP:
			if (pageNowPassenger > 1)
			{

				pageNowPassenger--;
				ChangePagePassenger(t);

				newPassenger = FindPassenger(t, arrPassengerId[currposPassenger]);
				oldPassenger = newPassenger;


				OutputListPassengerPerPage(t, (pageNowPassenger - 1) * QUANTITY_PER_PAGE);
				SetDefaultChosenPassenger(newPassenger->data, currposPassenger);

			}
			break;


		case ENTER:  //enter
			PASS = 0;
			ShowCur(true);
			return newPassenger;
			break;
		case ESC:
			ShowCur(true);
			return NULL;
			break;
		}
	}
}




void InputPassenger(TREE_PASSENGER &t, PASSENGER &pa, bool isEdited = false)
{
	ShowCur(true);
	int ordinal = 0;
	bool isMoveUp = false;
	bool isSave = false;

	unsigned int id = 0;
	string firstName, lastName;
	int sex = 0;
	bool idIsExist = false;
	Gotoxy(X_NOTIFY, Y_NOTIFY + 1);
	cout << "1: Nam 2: Nu";
	if (isEdited)
	{
		id = pa.id;
		firstName = pa.firstName;
		lastName = pa.lastName;
		sex = pa.sex;

		Gotoxy(X_ADD + 10, 0 * 3 + Y_ADD);
		cout << id;
		Gotoxy(X_ADD + 10, 1 * 3 + Y_ADD);
		cout << firstName;
		Gotoxy(X_ADD + 10, 2 * 3 + Y_ADD);
		cout << lastName;
		Gotoxy(X_ADD + 10, 3 * 3 + Y_ADD);
		cout << sex;
	}
	while (true)
	{
		switch (ordinal)
		{
		case 0:
		{
			if (isEdited) break;
			CheckMoveAndValidateIdentityCard(id, isMoveUp, ordinal, isSave, 10);

			if (FindPassenger(t, id) == NULL)
			{
				idIsExist = false;
				break;
			}
			idIsExist = true;
			break;
		}

		case 1:
			CheckMoveAndValidateName(firstName, isMoveUp, ordinal, isSave, 10);
			break;
		case 2:
			CheckMoveAndValidateName(lastName, isMoveUp, ordinal, isSave, 10);
			break;
		case 3:
			CheckMoveAndValidateNumber(sex, isMoveUp, ordinal, isSave, 10, 2);
			break;
		}

		if (isMoveUp)
		{
			if (ordinal == 0)
				isMoveUp = false;
			ordinal--;

		}
		else
		{
			if (ordinal == 4)
				isMoveUp = true;
			ordinal++;
		}
		if (isSave)
		{
			Gotoxy(X_NOTIFY, Y_NOTIFY);
			cout << setw(50) << setfill(' ') << " ";
			if (firstName.empty() || lastName.empty() || sex == 0 || int((log10(id) + 1)) != 9)
			{
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << "Cac truong du lieu khong dc de trong";
			}
			else if (idIsExist)
			{
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << "ID khong duoc trung";
			}
			else
			{
				pa.id = id;
				strcpy(pa.firstName, firstName.c_str());
				strcpy(pa.lastName, lastName.c_str());
				pa.sex = sex;

				StandardName(pa.firstName);
				StandardName(pa.lastName);
				if (isEdited)
				{
					NodePassenger* p = FindPassenger(t, id);
					p->data = pa;
					int index = 0;
					while (index <= nPassenger && arrPassengerId[index] != pa.id) index++;

				}
				else
				{
					InsertPassengerToTree(t, pa);

				}
				DeleteMenuAdd();
				Gotoxy(X_NOTIFY, Y_NOTIFY + 1);
				cout << "                    ";
				return;
			}
			isSave = false;
		}
		else
			isSave = false;
	}
	ShowCur(false);

}


void MenuManagePassenger(TREE_PASSENGER &t)
{
backMenu:
	totalPagePassenger = nPassenger / QUANTITY_PER_PAGE + 1;
	pageNowPassenger = 1;
	indexOutPassenger = -1;
	QuickSort(0, nPassenger, arrPassengerId);
	//OutputListPassenger(t);

	Display(keyDisplayPassenger, sizeof(keyDisplayPassenger) / sizeof(string));
	OutputListPassengerPerPage(t, 0);
	int key;
	while (true)
	{
		while (_kbhit())
		{
			Gotoxy(X_TITLE, Y_TITLE); cout << " QUAN LY HANH KHACH ";
			Gotoxy(X_PAGE, Y_PAGE);
			cout << "trang " << pageNowPassenger << "/" << totalPagePassenger;
			key = _getch();
			if (key == 0 || key == 224)
			{
				key = _getch();
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << setw(35) << setfill(' ') << " ";
				if (key == KEY_F2) //f2
				{
					PASSENGER pa;
					DisplayEdit(keyDisplayPassenger, sizeof(keyDisplayPassenger) / sizeof(string), 35);
					InputPassenger(t, pa);
					Gotoxy(X_NOTIFY, Y_NOTIFY);
					cout << "Them thanh cong";
					totalPagePassenger = nPassenger / QUANTITY_PER_PAGE + 1;
					pageNowPassenger = 1;
					OutputListPassengerPerPage(t, (pageNowPassenger - 1) * QUANTITY_PER_PAGE);
				}
				else if (key == KEY_F3) //f3
				{
					system("cls");
					NODE_PASSENGER* k = ChoosePassenger(t);
					if (k == NULL) goto backMenu;

					if (k->data.isBooked)
					{
						Gotoxy(X_NOTIFY, Y_NOTIFY);
						cout << "Nguoi nay dang giu ve. K xoa duoc";
						key = _getch();
						DeleteNotify();
						goto backMenu;
					}

					Gotoxy(X_NOTIFY, Y_NOTIFY);
					cout << "Ban co chac chan xoa? Enter dong y";
					key = _getch();
					if (key == ENTER)
					{
						system("cls");
						Display(keyDisplayPassenger, sizeof(keyDisplayPassenger) / sizeof(string));
						for (int i = 0; i <= nPassenger; i++)
						{
							if (arrPassengerId[i] == k->data.id)
							{
								for (int j = i; j < nPassenger; j++)
									arrPassengerId[j] = arrPassengerId[j + 1];
								nPassenger--;
								break;
							}
						}
						if (IsDeletedPassenger(t, k->data))
						{
							OutputListPassengerPerPage(t, (pageNowPassenger - 1) * QUANTITY_PER_PAGE);
							Gotoxy(X_NOTIFY, Y_NOTIFY);
							cout << "Xoa thanh cong";
						}
						/*IsDeletedPassenger(t, k->data);
						indexOutPassenger = -1;
						OutputListPassengerPerPage(t, (pageNowPassenger - 1) * QUANTITY_PER_PAGE);*/
					}
					else
						goto backMenu;


				}
				else if (key == KEY_F4) //f4
				{
					NODE_PASSENGER* k = ChoosePassenger(t);
					if (k == NULL) goto backMenu;
					DisplayEdit(keyDisplayPassenger, sizeof(keyDisplayPassenger) / sizeof(string), 35);
					InputPassenger(t, k->data, true);
					OutputListPassengerPerPage(t, (pageNowPassenger - 1) * QUANTITY_PER_PAGE);

				}
				else if (key == PAGE_DOWN && pageNowPassenger < totalPagePassenger)
				{
					system("cls");
					pageNowPassenger++;
					OutputListPassengerPerPage(t, (pageNowPassenger - 1) * QUANTITY_PER_PAGE);
					Display(keyDisplayPassenger, sizeof(keyDisplayPassenger) / sizeof(string));
				}
				else if (key == PAGE_UP && pageNowPassenger > 1)
				{
					system("cls");
					pageNowPassenger--;
					OutputListPassengerPerPage(t, (pageNowPassenger - 1) * QUANTITY_PER_PAGE);
					Display(keyDisplayPassenger, sizeof(keyDisplayPassenger) / sizeof(string));
				}
			}
			else if (key == ESC)
				return;
		}
	}
}
#endif
#endif