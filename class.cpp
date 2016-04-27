#include "class.h"

Time::Time(int aSec, int aMin, int aHour, int aMilSec) {
	Sec = aSec, Min = aMin, Hour = aHour, MilSec = aMilSec;
}

void Time::TimeSet(int aSec, int aMin, int aHour) {
	Sec = aSec, Min = aMin, Hour = aHour;
}

void Time::TimeSet(int aSec, int aMin, int aHour, int aMilSec) {
	Sec = aSec, Min = aMin, Hour = aHour, MilSec = aMilSec;
}

void Time::CheckTick() {
	if (Sec < 60 && Sec >= 0) {
		Sec++;
		if (Sec >= 60 && Min >= 0 && Min < 60) {
			Sec = 0;
			Min++;
			if (Min >= 60 && Hour >= 0) {
				Min = 0;
				Hour++;
			}
		}
	}
	/*switch (i) {
	case 0: //0.1
		if (Min >= 59 && Sec >= 59 && MilSec >= 9) {
			MilSec = 0;
			Sec = 0;
			Min = 0;
			Hour++;
		}
		else {
			if (Sec >= 59 && MilSec >= 9) {
				MilSec = 0;
				Sec = 0;
				Min++;
			}
			else {
				if (MilSec >= 9) {
					MilSec = 0;
					Sec++;
				}
				else {
					MilSec++;
				}
			}
		}
		break;

	case 1: //기본, 1초
		
		break;

	case 2: //5배, 5초
		if (Sec < 60 && Sec >= 0) {
			Sec += 5;
			if (Sec >= 60 && Min >= 0 && Min < 60) {
				Sec = 0;
				Min++;
				if (Min >= 60 && Hour >= 0) {
					Min = 0;
					Hour++;
				}
			}
		}
		break;

	case 3: //10배, 10초
		if (Sec < 60 && Sec >= 0) {
			Sec += 10;
			if (Sec >= 60 && Min >= 0 && Min < 60) {
				Sec = 0;
				Min++;
				if (Min >= 60 && Hour >= 0) {
					Min = 0;
					Hour++;
				}
			}
		};
		break;

	case 4: // 60배, 60초
		if (Sec < 60 && Sec >= 0) {
			Sec += 60;
			if (Sec >= 60 && Min >= 0 && Min < 60) {
				Sec %= 60;
				Min++;
				if (Min >= 60 && Hour >= 0) {
					Min = 0;
					Hour++;
				}
			}
		}
		break;

	case 5:
		if (Sec < 60 && Sec >= 0) {
			Sec += 600;
			if (Sec >= 60 && Min >= 0 && Min < 60) {
				Min = Sec / 60;
				Sec %= 60;
				if (Min >= 60 && Hour >= 0) {
					Min = 0;
					Hour++;
				}
			}
		}
		break;
	}*/
}

void Time::WriteTick(TCHAR *STR) {

	switch (Time::Hour >= 10) {
	case TRUE:
		switch (Min >= 10) {
		case TRUE:
			switch (Sec >= 10) {
			case TRUE:
				wsprintf(STR, TEXT("%d:%d:%d"), Hour, Min, Sec);
				break;

			case FALSE:
				wsprintf(STR, TEXT("%d:%d:0%d"), Hour, Min, Sec);
				break;
			}
			break;

		case FALSE:
			switch (Sec >= 10) {
			case TRUE:
				wsprintf(STR, TEXT("%d:0%d:%d"), Hour, Min, Sec);
				break;

			case FALSE:
				wsprintf(STR, TEXT("%d:0%d:0%d"), Hour, Min, Sec);
				break;
			}
			break;
		}
		break;

	case FALSE:
		switch (Min >= 10) {
		case TRUE:
			switch (Sec >= 10) {
			case TRUE:
				wsprintf(STR, TEXT("0%d:%d:%d"), Hour, Min, Sec);
				break;

			case FALSE:
				wsprintf(STR, TEXT("0%d:%d:0%d"), Hour, Min, Sec);
				break;
			}
			break;

		case FALSE:
			switch (Sec >= 10) {
			case TRUE:
				wsprintf(STR, TEXT("0%d:0%d:%d"), Hour, Min, Sec);
				break;

			case FALSE:
				wsprintf(STR, TEXT("0%d:0%d:0%d"), Hour, Min, Sec);
				break;
			}
			break;
		}
		break;
	}
}


void Pawn::SetPosition(double ax, double ay) {
	NowPos.x = ax; NowPos.y = ay;
}

void Pawn::ToPosition(double ax, double ay) {
	FutPos.x = ax; FutPos.y = ay;
}

void Pawn::SetSpeed(double aSpeed) { // "Speed"m/s ..
	Speed = aSpeed;
}

void Pawn::MovePer() { //호출하면 거리를 더한다.
	Length += Speed;
}

void Pawn::CheckChange(int i) {
	double dx = NowPos.x - FutPos.x;
	double dy = NowPos.y - FutPos.y;
	double degree = atan(dx / dy);
	PastPos[i].x = NowPos.x + (cos(degree)*Length);
	PastPos[i].y = NowPos.y + (sin(degree)*Length);
}

void Pawn::TestReading(TCHAR *STR, int i) {
	int z, p;
	CHAR AA[50];

	z = sprintf_s(AA, "X : %f, Y : %f", PastPos[i].x, PastPos[i].y);
	p = wsprintf(STR, TEXT("%S"), AA);
	PastPos[i].x = _wtof(STR);
	PastPos[i].y = _wtof(STR);
}