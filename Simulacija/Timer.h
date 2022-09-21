#include "Windows.h"
#include "DarkGDK.h"
#include <stdio.h>
#include <stdlib.h>
#include "resource.h"

#define TIMER_H "Timer.h"
#define XSCREENOFFSET 120

class MyTimer{
private:
	int ii;
    //float StartTime;
    float PauseTime;
	int timeSec;
	int _continue;
	int ret;
	char _tmp[20];
	char* _tmp2;
	char _strres[20];
	bool _run;
	
public:
	int m_countFrom;

	MyTimer();
    MyTimer(int);
    void Run();
	void Stop();
	void Restart();
    int  Elapsed() ;
	int  EndTime();
	int  TimeOut();
	bool CountDown();
	char* ElapsedFormatted();
};