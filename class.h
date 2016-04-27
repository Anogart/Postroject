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

//가장 기본적인 Character로써의 기능을 가진 클래스.
class Pawn {
	/* 좌표 x, y, z 속력 Speed 피로도 TP (Tiredness Point .. )
	** 체력 HP 집중력 FP
	** 적성 CEIPBA
	** 능력 Str, Sta, Wis, Agi, Cha, Dex
	*/

protected:
	//좌표에 대한 구조체를 만들어보는 건 어떨까
	//short x, y, Speed, TP;
	double Speed, Length;//속력과 거리
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