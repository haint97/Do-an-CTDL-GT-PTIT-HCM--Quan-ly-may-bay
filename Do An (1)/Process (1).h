#ifndef _PROCESS_H
#define _PROCESS_H
#include "Airplane.h"
#include <fstream>

//-------------------DATABASE--------------------------------
void LoadAirplane(PTR_LIST_AIRPLANE &pListAirplane)
{
	int SizeFlight = sizeof(FLIGHT) - sizeof(TICKET*);
	int SizeAirplane = sizeof(AIRPLANE) - sizeof(LIST_FLIGHT);
	fstream fileData("data.txt", ios::in | ios::binary);
	while (!fileData.eof())
	{
		pListAirplane->listAirplane[++pListAirplane->n] = new AIRPLANE;
		fileData.read(reinterpret_cast<char*>(pListAirplane->listAirplane[pListAirplane->n]), SizeAirplane);
		InitListFlight(pListAirplane->listAirplane[pListAirplane->n]->listFlight);
		int nFlight = pListAirplane->listAirplane[pListAirplane->n]->nFlight;
		FLIGHT p;
		for (int j = 0; j < nFlight; ++j)
		{
			fileData.read(reinterpret_cast<char*>(&p), SizeFlight);
			int nTicket = p.nTicket;
			p.listTicket = new TICKET[MAX_TICKET];
			for (int i = 0; i < nTicket; i++)
				fileData.read(reinterpret_cast<char*>(&p.listTicket[i]), sizeof(TICKET));

			AddTailListFlight(pListAirplane->listAirplane[pListAirplane->n]->listFlight, p);
		}
	}
	delete pListAirplane->listAirplane[pListAirplane->n];
	--pListAirplane->n;
	fileData.close();
}
void SaveAirplane(PTR_LIST_AIRPLANE pListAirplane)
{
	int SizeFlight = sizeof(FLIGHT) - sizeof(TICKET*);
	int SizeAirplane = sizeof(AIRPLANE) - sizeof(LIST_FLIGHT);
	fstream fileData("data.txt", ios::out | ios::binary);
	for (int i = 0; i <= pListAirplane->n; i++)
	{
		pListAirplane->listAirplane[i]->nFlight = pListAirplane->listAirplane[i]->listFlight.n;
		fileData.write(reinterpret_cast<const char*>(pListAirplane->listAirplane[i]), SizeAirplane);
		NODE_FLIGHT* p = pListAirplane->listAirplane[i]->listFlight.pHead;
		while (p != NULL)
		{
			fileData.write(reinterpret_cast<const char*>(&p->data), SizeFlight);
			int nTicket = p->data.nTicket;
			for (int i = 0; i < nTicket; i++)
				fileData.write(reinterpret_cast<const char*>(&p->data.listTicket[i]), sizeof(TICKET));
			p = p->pNext;
		}
	}
	fileData.close();
}
void WritePassengerToFile(NODE_PASSENGER* p, fstream &file, int size)
{
	if (p != NULL)
	{
		file.write(reinterpret_cast<const char*>(&p->data), size);
		WritePassengerToFile(p->pLeft, file, size);
		WritePassengerToFile(p->pRight, file, size);
	}
}
void SavePassenger(TREE_PASSENGER t)
{
	fstream myfile("passenger.txt", ios::out | ios::binary);
	myfile << nPassenger;
	int sizeData = sizeof(PASSENGER);
	TREE_PASSENGER p = t;
	WritePassengerToFile(p, myfile, sizeData);
	myfile.close();
}
void LoadPassenger(TREE_PASSENGER &t)
{
	fstream myfile("passenger.txt", ios::in | ios::binary);
	int nPassenger;
	myfile >> nPassenger;
	int sizeData = sizeof(PASSENGER);
	PASSENGER pa;
	for (int i = 0; i <= nPassenger; i++)
	{
		myfile.read(reinterpret_cast<char*>(&pa), sizeData);
		InsertPassengerToTree(t, pa);
	}
}
//--------------------------END DATABASE

//--------------------------STATISTIC
void OutputPassengerOnFlight(FLIGHT fl, TREE_PASSENGER t)
{
	int ordinal = -1;
	Display(keyDisplayPassenger, sizeof(keyDisplayPassenger) / sizeof(string));
	DeleteGuide(sizeof(keyDisplayPassenger) / sizeof(string) + 1);
	for (int i = 0; i < fl.nTicket; i++)
	{
		if (fl.listTicket[i].stt == TICKET_SOLD)
		{
			NODE_PASSENGER* pa = FindPassenger(t, fl.listTicket[i].idOwner);
			OutputPassenger(pa->data, ++ordinal);
		}
	}
}
bool StatisticPassengerOnFlightIsSucceed(PTR_LIST_AIRPLANE l, TREE_PASSENGER t)
{
	int indexAirplane = DisplayAndChooseIndexAirplane(l, "CHON MAY BAY MUON THONG KE");
	Gotoxy(X_TITLE, Y_TITLE); cout << "CHON CHUYEN BAY MUON DAT VE";
	if (indexAirplane == -1)
	{
		system("cls");
		return false;
	}
	system("cls");
	Gotoxy(X_TITLE, Y_TITLE); cout << "CHON CHUYEN BAY MUON HIEN THI";
	Display(keyDisplayFlight, sizeof(keyDisplayFlight) / sizeof(string));
	NODE_FLIGHT* fl = ChooseFlight(l->listAirplane[indexAirplane]->listFlight);
	if (fl == NULL)
	{
		system("cls");
		return false;
	}
	system("cls");
	Gotoxy(X_TITLE, Y_TITLE);
	cout << "DANH SACH HANH KHACH THUOC CHUYEN BAY " << fl->data.id;
	Gotoxy(X_TITLE, Y_TITLE + 1);
	cout << "NOI DEN " << fl->data.destiny;
	Gotoxy(X_TITLE, Y_TITLE + 2);
	cout << "NGAY KHOI HANH " << fl->data.dateLeave.d << "/" << fl->data.dateLeave.m << "/" << fl->data.dateLeave.y;
	
	if (fl->data.nTicketSold == 0)
	{
		Gotoxy(X_NOTIFY, Y_NOTIFY);
		cout << "Khong co du lieu";
	}
	else OutputPassengerOnFlight(fl->data, t);
	_getch();
	return true;
}

bool StatisticFlightOnDay(PTR_LIST_AIRPLANE l)
{
	system("cls");
	DATETIME dt;
	Gotoxy(X_ADD + 12 + 8, 3 + Y_ADD);
	cout << "/";
	Gotoxy(X_ADD + 12 + 11, 3 + Y_ADD);
	cout << "/";
	bool isMove = false;
	bool isSave = false;
	int newOrdinal = 2;
	Gotoxy(X_TITLE, Y_TITLE);
	cout << "NHAP NGAY GIO CAN THONG KE ";
	Gotoxy(X_TITLE, Y_TITLE + 1);
	cout << "Nhan F10 de hien thi ket qua";
	while (true)
	{
		switch (newOrdinal)
		{
		case 2:
			CheckMoveAndValidateDateTime(dt.d, isMove, newOrdinal, isSave, 31, 12);
			break;
		case 3:
			CheckMoveAndValidateDateTime(dt.m, isMove, newOrdinal, isSave, 12, 12);
			break;
		case 4:
			CheckMoveAndValidateDateTime(dt.y, isMove, newOrdinal, isSave, 10000, 12);
			break;
		} // end switch newordinal
		//check key move
		if (isMove)
		{
			if (newOrdinal == 2)
				isMove = false;
			else
				newOrdinal--;
		}
		else
		{
			if (newOrdinal == 4)
				isMove = true;
			else
				newOrdinal++;
		}
		if (isSave)
		{
			if (DateTimeIsRightFormat(dt))
				break;
			Gotoxy(X_NOTIFY, Y_NOTIFY);
			cout << "Ngay gio k hop le. Nhan 1 phim bat";
			_getch();
			Gotoxy(X_NOTIFY, Y_NOTIFY);
			cout << setfill(' ') << setw(30) << " ";
			isSave = false;
		}
			
	} // end while
	system("cls");
	
	Gotoxy(X_TITLE, Y_TITLE + 2);
	cout << "CAC CHUYEN BAY KHOI HANH " << dt.d << "/" << dt.m << "/" << dt.y;
	
	int index = -1;
	bool isHaveData = false;;
	for (int i = 0; i <= l->n; i++)
	{
		AutoChangeSttFlight(l->listAirplane[i]->listFlight);
		NODE_FLIGHT* p = l->listAirplane[i]->listFlight.pHead;
		while (p != NULL)
		{
			/*if (p->data.dateLeave.d == dt.d &&p->data.dateLeave.m == dt.m && p->data.dateLeave.y == dt.y)*/
			if (CompareDate(p->data.dateLeave,dt))
			{
				OutputFlight(p->data, ++index);
				isHaveData = true;
			}
				
			p = p->pNext;
		}
	}
	if (isHaveData)
	{
		Display(keyDisplayFlight, sizeof(keyDisplayFlight) / sizeof(string));
		DeleteGuide(sizeof(keyDisplayFlight) / sizeof(string));
	}
	else
	{
		Gotoxy(X_NOTIFY, Y_NOTIFY);
		cout << "Khong co chuyen bay";
	}
	_getch();
	return true;
}
bool StatisticTicketFlight(PTR_LIST_AIRPLANE l)
{
	int indexAirplane = DisplayAndChooseIndexAirplane(l, "CHON MAY BAY MUON THONG KE");
	if (indexAirplane == -1)
	{
		system("cls");
		return false;
	}
	system("cls");
	Gotoxy(X_TITLE, Y_TITLE); cout << "CHON CHUYEN BAY MUON THONG KE";
	Display(keyDisplayFlight, sizeof(keyDisplayFlight) / sizeof(string));
	Gotoxy(xKeyDisplay[0] + 1, Y_DISPLAY + 40);
	cout << setw(xKeyDisplay[sizeof(keyDisplayFlight) / sizeof(string)] - xKeyDisplay[0] - 1) << " " << setfill(' ');
	NODE_FLIGHT* fl = NULL;
	fl = ChooseFlight(l->listAirplane[indexAirplane]->listFlight);
	if (fl == NULL) return false;
	system("cls");

	
	Gotoxy(X_TITLE, Y_TITLE); cout << "DANH SACH VE CUA MAY BAY " << l->listAirplane[indexAirplane]->id;
	cout << "  CHUYEN BAY " << fl->data.id;
	
	DisplayMenuTicket(fl->data);
	_getch();
	return true;
}

bool StatisticFlightOfAirplane(PTR_LIST_AIRPLANE l)
{
	SortByNumberFlight(l);
	system("cls");
	Gotoxy(X_TITLE, Y_TITLE); cout << "THONG KE CAC CHUYEN BAY CUA MAY BAY";
	string key[] = { "Ma may bay","So lan bay" };
	Display(key, 2);
	DeleteGuide(2);
	for (int i = 0; i <= l->n; i++)
	{
		Gotoxy(xKeyDisplay[0] + 1, Y_DISPLAY + 3 + i); cout << l->listAirplane[i]->id;
		Gotoxy(xKeyDisplay[1] + 1, Y_DISPLAY + 3 + i); cout << l->listAirplane[i]->listFlight.n;
	}
	_getch();
	return true;
}
//--------------END STATISTIC



bool BookTicketIsSuceed(PTR_LIST_AIRPLANE &l, TREE_PASSENGER &t)
{
	system("cls");
	Gotoxy(X_TITLE, Y_TITLE); cout << "CHON HANH KHACH MUON DAT VE";
	//indexOutPassenger = -1;
	//QuickSort(0, nPassenger, arrPassengerId);

	Display(keyDisplayPassenger, sizeof(keyDisplayPassenger) / sizeof(string));
	/*Gotoxy(xKeyDisplay[0] + 1, Y_DISPLAY + 40);
	cout << setw(xKeyDisplay[sizeof(keyDisplayPassenger) / sizeof(string)] - xKeyDisplay[0] - 1) << " " << setfill(' ');*/
	DeleteNote(sizeof(keyDisplayPassenger) / sizeof(string));
	NODE_PASSENGER* chosenPassenger = ChoosePassenger(t);
	if (chosenPassenger == NULL)
	{
		system("cls");
		return false;
	}
	system("cls");

	int indexAirplane = DisplayAndChooseIndexAirplane(l, "CHON MAY BAY MUON DAT VE");
	if (indexAirplane == -1)
	{
		system("cls");
		return false;
	}
	system("cls");

	Gotoxy(X_TITLE, Y_TITLE); cout << "CHON CHUYEN BAY MUON DAT VE";
	Display(keyDisplayFlight, sizeof(keyDisplayFlight) / sizeof(string));
	Gotoxy(xKeyDisplay[0] + 1, Y_DISPLAY + 40);
	cout << setw(xKeyDisplay[sizeof(keyDisplayFlight) / sizeof(string)] - xKeyDisplay[0] - 1) << " " << setfill(' ');
	//OutputListFlight(l->listAirplane[indexAirplane]->listFlight);
	OutputListFlightPerPage(l->listAirplane[indexAirplane]->listFlight, 0);
	NODE_FLIGHT* fl; //= NULL;
	do
	{
		fl = ChooseFlight(l->listAirplane[indexAirplane]->listFlight);
		if (fl->data.stt != STT_REMAIN_TICKET)
		{
			Gotoxy(X_NOTIFY, Y_NOTIFY); cout << "CHON CHUYEN CON VE VA CHUA HOAN TAT";
			_getch();
		}
	} while (fl->data.stt != STT_REMAIN_TICKET && fl != NULL);
	if (fl == NULL)
	{
		system("cls");
		return false;
	}
	int k;
	system("cls");
	do
	{
		k = ChooseTicket(fl->data);
		if (fl->data.listTicket[k - 1].stt == TICKET_SOLD && k != -1)
		{
			Gotoxy(X_NOTIFY, Y_NOTIFY); cout << "VE DA CO NGUOI DAT";
			_getch();
			DeleteNotify();
		}
		
	} while (fl->data.listTicket[k - 1].stt == TICKET_SOLD && k != -1);
	if (k == -1)
	{
		system("cls");
		return false;
	}
	
	
		
	


	fl->data.listTicket[k - 1].stt = TICKET_SOLD;
	fl->data.nTicketSold++;
	fl->data.listTicket[k - 1].idOwner = chosenPassenger->data.id;
	chosenPassenger->data.isBooked = true;
	if (fl->data.nTicket == fl->data.nTicketSold) fl->data.stt = STT_FULL_TICKET;
	Gotoxy(X_NOTIFY, Y_NOTIFY); cout << "DAT VE THANH CONG";
	_getch();
	return true;
}

void Introduce()
{
	ShowCur(false);
	string a;
	char b;
	ifstream file("introduce.txt", ios::in);
	while (!file.eof())
	{
		getline(file, a);
		cout << a << endl;
	}
	Gotoxy(100, 35);
	cout << "Nguyen Thai Hai";
	Gotoxy(100, 36);
	cout << "N15DCCN033";
	Gotoxy(100, 37);
	cout << "D15CQCN01-N";
}

void MageAll(PTR_LIST_AIRPLANE &l, TREE_PASSENGER &t)
{
	while (true)
	{
		Introduce();
		MainMenu(keyMainMenu, sizeof(keyMainMenu) / sizeof(string));
		int type = ChooseMainMenu(keyMainMenu, sizeof(keyMainMenu) / sizeof(string));
		totalPageAirplane = l->n / QUANTITY_PER_PAGE + 1;
		totalPagePassenger = nPassenger / QUANTITY_PER_PAGE + 1;
		switch (type)
		{
		case -1:
			return;
		case 0:
		{
			MenuManageAirplane(l);
			break;
		}
		case 1:
		{

			int indexAirplanee = DisplayAndChooseIndexAirplane(l, "CHON MAY BAY DE QUAN LY CHUYEN BAY");
			if (indexAirplanee == -1)
			{
				system("cls");
				continue;
			}
			system("cls");
			Gotoxy(X_TITLE, Y_TITLE); cout << " QUAN LY CHUYEN BAY CUAY MAY BAY CO MA SO " << l->listAirplane[indexAirplanee]->id;
			totalPageFlight = ((l->listAirplane[indexAirplanee]->listFlight.n - 1) / QUANTITY_PER_PAGE) + 1;
			MenuManageFlight(l->listAirplane[indexAirplanee]->listFlight, l->listAirplane[indexAirplanee]->nChair);
			break;
		}
		case 3:
			if (BookTicketIsSuceed(l, t) == false) continue;
			break;
		case 2:
		{
			system("cls");
			Gotoxy(X_TITLE, Y_TITLE); cout << " QUAN LY HANH KHACH ";
			MenuManagePassenger(t);
			break;
		}
		case 4:
		{
			system("cls");
			MainMenu(keyStatistic, sizeof(keyStatistic) / sizeof(string));
			int chosenStatistic = ChooseMainMenu(keyStatistic, sizeof(keyStatistic) / sizeof(string));
			switch (chosenStatistic)
			{
			case 0:
				if (StatisticPassengerOnFlightIsSucceed(l, t) == false)	continue;
				break;
			case 1:
				if (StatisticFlightOnDay(l) == false)	continue;
				break;
			case 2:
				if (StatisticFlightOfAirplane(l) == false)	continue;
				break;
			case 3:
				if (StatisticTicketFlight(l) == false)	continue;
				break;
			default:
				break;
			}//end swtich case statistic
		}//end case 4 of type			
		}//end switch type
		system("cls");
	}//while true
}//void
#endif