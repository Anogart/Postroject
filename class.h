#pragma once
#include <windows.h>
#include <math.h>
#include <stdio.h>

class Time {
protected:
	int MilSec;
	int Sec;
	int Min;
	int Hour;

	/*typedef struct Date {
		int Ms;
		int S;
		int M;
		int H;
	} Date;*/

public:
	Time() { MilSec = 0;  Sec = 0; Min = 0; Hour = 0; }
	Time(int aSec, int aMin, int aHour, int aMilSec);
	void TimeSet(int aSec, int aMin, int aHour);
	void TimeSet(int aSec, int aMin, int aHour, int aMilSec);
	void Time::CheckTick();
	void WriteTick(TCHAR *STR);

};

//���� �⺻���� Character�ν��� ����� ���� Ŭ����.
class Pawn {
	/* ��ǥ x, y, z �ӷ� Speed �Ƿε� TP (Tiredness Point .. )
	** ü�� HP ���߷� FP
	** ���� CEIPBA
	** �ɷ� Str, Sta, Wis, Agi, Cha, Dex
	*/

protected:
	//��ǥ�� ���� ����ü�� ������ �� ���
	//short x, y, Speed, TP;
	double Speed, Length;//�ӷ°� �Ÿ�
	typedef struct Position {
		double x, y;
	} Pos;

	Pos NowPos;
	Pos FutPos;
	Pos PastPos[10];

public:
	Pawn() { PastPos[1].x = 0, PastPos[1].y = 0; }
	void SetPosition(double ax, double ay);
	void ToPosition(double ax, double ay);
	void SetSpeed(double aSpeed);
	void MovePer();
	void CheckChange(int i);
	void TestReading(TCHAR *STR, int i);

};