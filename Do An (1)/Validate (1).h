#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <Windows.h>

#include <iomanip>
#include <ctime>
#include "lib.h"
#include "Constant.h"
#include "GlobalVariable.h"

using namespace std;
int X = 110;
int Y = 6;

int ValidateDateHour(int condition)
{
	int result = 0;
	int count = 0;
	while (true)
		while (_kbhit())
		{
			int key = _getch();
			if (key >= 48 && key <= 57)
			{
				int f = key - 48;
				cout << f;
				result = result * 10 + (f);
				count++;
			}
			else if (key == ENTER)
			{
				if (result > condition)
					continue;
				return result;
			}
			else if (key == BACKSPACE && count >0)
			{
				cout << "\b" << " " << "\b";
				count--;
				result /= 10;
			}
		}
	return result;
}

unsigned int ValidateIdentityCard()
{
	unsigned int result = 0;
	int count = 0;
	while (true)
	{
		while (_kbhit())
		{
			int key = _getch();

			if (key >= 48 && key <= 57 && count <9)
			{
				int f = key - 48;
				if (count == 0 && key == 48)
				{
					continue;
				}
				else
				{
					cout << f;
					result = result * 10 + (f);
					count++;
				}
			}
			else if (key == 13)
			{

				return result;

			}
			else if (key == 8 && count >0)
			{
				cout << "\b" << " " << "\b";
				count--;
				result /= 10;
			}

		}
	}
	return result;
}

string ValidateName()
{
	string result = "";
	int count = 0;
	bool isSpaced = false;
	while (true)
	{
		while (_kbhit())
		{
			int key = _getch();

			//if ( (key >= 65 && key <= 90) || (key >= 97 && key <= 142) || key = 32)
			if ((key >= 65 && key <= 90) || (key >= 97 && key <= 122) || key == 32)
			{
				count++;
				if (!isSpaced && key == 32)
				{
					cout << (char)key;
					result += (char)key;
					isSpaced = true;
				}
				else if (key != 32)
				{
					cout << (char)key;
					result += (char)key;
					isSpaced = false;
				}

			}
			else if (key == 13)
			{

				return result;

			}
			else if (key == 8 && count >0)
			{
				cout << "\b" << " " << "\b";
				result.erase(1, result.length());

			}
			else if (key == 72)
			{

				return result;
			}
			else if (key == 80)
			{

				return result;
			}
		}
	}
	return result;
}


//only number and char
string ValidateID(bool &isMoveUp)
{
	string result = "";
	int count = 0;

	while (true)
	{
		while (_kbhit())
		{
			int key = _getch();

			//if ( (key >= 65 && key <= 90) || (key >= 97 && key <= 142) || key = 32)
			if ((key >= 65 && key <= 90) || (key >= 97 && key <= 122) || (key >= 48 && key <= 57))
			{
				count++;
				cout << (char)key;
				result += (char)key;
			}
			else if (key == 13)
			{
				isMoveUp = false;
				return result;

			}
			else if (key == 8 && count >0)
			{
				cout << "\b" << " " << "\b";
				result.erase(1, result.length());

			}
			else if (key == 72)
			{
				isMoveUp = true;
			}
			else if (key == 80)
			{
				isMoveUp = false;
				return result;
			}
		}
	}
	return result;
}






void CheckMoveAndValidateIdentityCard(unsigned int &result, bool &isMove, int &ordinal, bool &isSave, int distance)
{
	int lengh;
	if (result != 0)
		lengh = (int)log10(result) + 1;
	else lengh = 0;
	Gotoxy(X_ADD + distance, ordinal * 3 + Y_ADD);
	if (result != 0)
		cout << result;
	int count = lengh;
	bool isSpaced = false;
	while (true)
	{
		while (_kbhit())
		{
			int key = _getch();
			if (key != 224 && key != SPACE && key != 0)
			{
				if (key >= 48 && key <= 57 && count <9)
				{
					int f = key - 48;
					if (count == 0 && key == 48)
						continue;
					else
					{
						cout << f;
						result = result * 10 + (f);
						count++;
					}
				}
				else if (key == ENTER)
					return;
				else if (key == BACKSPACE && count >0)
				{
					cout << "\b" << " " << "\b";
					count--;
					result /= 10;
				}
			}
			else if (key == 224)
			{
				key = _getch();
				if (key == KEY_UP)
				{
					isMove = true;
					return;
				}
				else
				{
					isMove = false;
					return;
				}
			}
			else if (key == 0)
			{
				key = _getch();
				if (key == KEY_F10)
				{
					isSave = true;
					return;
				}
			}
		}//while kbhit
	} // while true

}


void CheckMoveAndValidateName(string &result, bool &isMove, int &ordinal, bool &isSave,int distance)
{
	int lengh = result.length();
	Gotoxy(X_ADD + distance, ordinal * 3 + Y_ADD);
	cout << result;
	int count = lengh;
	bool isSpaced = false;
	while (true)
	{
		while (_kbhit())
		{
			int key = _getch();
			if (key != 224  && key != 0)
			{
				if ((key >= 65 && key <= 90) || (key >= 97 && key <= 122) || key == SPACE )
				{
					if (count < MAX_LENGTH)
					{
						count++;
						if (!isSpaced && key == SPACE)
						{
							cout << (char)key;
							result += (char)key;
							isSpaced = true;
						}
						else
						{
							cout << (char)key;
							result += (char)key;
							isSpaced = false;
						}
					}
				}
				else if (key == ENTER)
					return;
				else if (key == BACKSPACE && count >0)
				{
					cout << "\b" << " " << "\b";
					result.erase(result.length() - 1, 1);
					count--;
				}
			}
			else if (key == 224)
			{
				key = _getch();
				if (key == KEY_UP)
				{
					isMove = true;
					return;
				}
				else
				{
					isMove = false;
					return;
				}
			}
			else if (key == 0)
			{
				key = _getch();
				if (key == KEY_F10)
				{
					isSave = true;
					return;
				}
			}
		}//kbhit
	}//true
}


//only char and number
void CheckMoveAndValidateID(string &result, bool &isMove, int &ordinal, bool &isSave, int distance)
{
	int lengh = result.length();
	Gotoxy(X_ADD + distance , ordinal * 3 + Y_ADD);
	cout << result;
	int count = lengh;
	while (true)
	{
		while (_kbhit())
		{
			int key = _getch();
			if (key != 224 && key != SPACE && key != 0)
			{
				if ((key >= 65 && key <= 90) || (key >= 97 && key <= 122)  || (key >= 48 && key <= 57))
				{
					if (count < MAX_LENGTH)
					{
						count++;
						cout << (char)key;
						result += (char)key;
					}
					
				}
				else if (key == ENTER)
					return;
				else if (key == BACKSPACE && count >0)
				{
					cout << "\b" << " " << "\b";
					result.erase(result.length() - 1,1);
					count--;

				}
			}
			else if (key == 224)
			{
				key = _getch();
				if (key == KEY_UP)
				{
					isMove = true;
					return;
				}
				else
				{
					isMove = false;
					return;
				}
			}
			else if (key == 0)
			{
				key = _getch();
				if (key == KEY_F10)
				{
					isSave = true;
					return;
				}
			}
		}//kbhit
	}//while true

}

void CheckMoveAndValidateNumber(int &result, bool &isMove, int &ordinal, bool &isSave,int distance, int condition)
{
	int lengh;
	if (result != 0)
		lengh = (int)log10(result)+1;
	else lengh = 0;
	Gotoxy(X_ADD + distance, ordinal * 3 + Y_ADD);
	if (result != 0)
	cout << result;
	int count = lengh;
	while (true)
	{
		while (_kbhit())
		{
			int key = _getch();
			if (key != 224 && key != SPACE && key!= 0 )
			{
				if (key >= 48 && key <= 57)
				{
					int f = key - 48;
					if (count == 0 && key == 48)
						continue;
					else
						if (result * 10 + (f) <= condition)
						{
							cout << f;
							result = result * 10 + (f);
							count++;
						}
				}
				else if (key == ENTER)
				{
					if (result > condition)
						continue;
					return;
					
				}
				else if (key == BACKSPACE && count >0)
				{
					cout << "\b" << " " << "\b";
					count--;
					result /= 10;
				}
			}
			else if (key == 224)
			{
				key = _getch();
				if (key == KEY_UP)
				{
					isMove = true;
					return;
				}
				else
				{
					isMove = false;
					return;
				}
			}
			else if (key == 0)
			{
				key = _getch();
				if (key == KEY_F10)
				{
					isSave = true;
					return;
				}
			}
		}//kbhit
	}//while tru

}


void CheckMoveAndValidateDateTime(int &result, bool &isMove, int &ordinal, bool &isSave, int condition, int distance)
{
	int lengh;
	if (result != 0)
		lengh = (int)log10(result) + 1;
	else lengh = 0;
	Gotoxy(X_ADD + distance + ordinal * 3, 3 + Y_ADD);
	if (result !=0)
	cout << result;
	int count = lengh;
	bool isSpaced = false;
	while (true)
	{
		while (_kbhit())
		{
			int key = _getch();
			if (key != 224 && key != SPACE && key != 0)
			{
				if (key >= 48 && key <= 57)
				{
					int f = key - 48;
					if (count == 0 && key == SPACE)
						continue;
					else
					{
						if (result * 10 + (f) <= condition)
						{
							cout << f;
							result = result * 10 + (f);
							count++;
						}
						
						
					}
				}
				else if (key == ENTER)
				{
					if (result > condition)
						continue;
					return;
				}
				else if (key == 8 && count >0)
				{
					cout << "\b" << " " << "\b";

					count--;
					result /= 10;

				}
			}
			else if (key == 224)
			{
				key = _getch();
				if (key == KEY_UP)
				{
					isMove = true;
					return;
				}
				else
				{
					isMove = false;
					return;
				}
			}
			else if (key == 0)
			{
				key = _getch();
				if (key == KEY_F10)
				{
					isSave = true;
					return;
				}
			}
		}
	}

}
void StandardName(char *a)
{
	a[0] = toupper(a[0]);
	int length = strlen(a);
	for (int i = 1; i < length; ++i)
	{
		if (a[i -1] == ' ' && a[i] != ' ') a[i] = toupper(a[i]);
		else a[i] = tolower(a[i]);
	}
}

