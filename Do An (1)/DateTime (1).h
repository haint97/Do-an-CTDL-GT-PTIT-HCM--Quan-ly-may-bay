#pragma once 
#include "Validate.h"
int nDayOfMonth[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

struct DateTime
{
	int y = 0, m = 0, d = 0, h = 0, mi = 0;
};
typedef struct DateTime DATETIME;

bool DateTimeIsRightFormat(DATETIME dt)
{
	nDayOfMonth[2] = 28;
	if ((dt.y % 400 == 0) || (dt.y % 4 == 0 && dt.y % 100 != 0))
		nDayOfMonth[2] = 29;
	if (dt.d > nDayOfMonth[dt.m]) return false;
	return true;
}

bool DateTimeIsValid(DATETIME dt)
{
	if (!DateTimeIsRightFormat(dt)) return false;

	nDayOfMonth[2] = 28;
	time_t baygio = time(0);
	tm *ltm = localtime(&baygio);
	DATETIME dtNow;
	dtNow.y = 1900 + ltm->tm_year;
	dtNow.m = 1 + ltm->tm_mon;
	dtNow.d = ltm->tm_mday;
	dtNow.h = ltm->tm_hour;
	dtNow.mi = ltm->tm_min;

	if (dt.y < dtNow.y) return false;
	if ((dt.y == dtNow.y) && (dt.m < dtNow.m))  return false;
	if ((dt.y % 400 == 0) || (dt.y % 4 == 0 && dt.y % 100 != 0))
		nDayOfMonth[2] = 29;
	if (dt.y == dtNow.y && dt.m == dtNow.m && dt.d < dtNow.d)return false;
	if (dt.y == dtNow.y && dt.m == dtNow.m && dt.d == dtNow.d && dt.h < dtNow.h)return false;
	if (dt.y == dtNow.y && dt.m == dtNow.m && dt.d == dtNow.d && dt.h == dtNow.h && dt.mi <= dtNow.mi)return false;
	return true;
}


void OutputDateTime(DATETIME &dt)
{
	cout << dt.h << ":" << dt.mi << " " << dt.d << "/" << dt.m << "/" << dt.y;
}
bool CompareDate(DATETIME dt1, DATETIME dt2)
{
	return dt1.d == dt2.d && dt2.m == dt1.m && dt1.y == dt2.y;

}