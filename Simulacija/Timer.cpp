#include "Timer.h"

MyTimer::MyTimer(): ii(0) {}

MyTimer::MyTimer(int CountFrom) 
{
	LoadString(0, IDS_VRIJEME, _strres, sizeof(_strres));
	m_countFrom = CountFrom;
	ii = 0;
}
void MyTimer::Run()
{	
	ii++;
}
void MyTimer::Stop()
{	
	_run = false;
}
void MyTimer::Restart()
{
	ii = 0;
	_run = true;
}
int MyTimer::Elapsed()
{
	sprintf(_tmp, "%s %d %c", _strres, m_countFrom - ii/10, 's');

	if ( _run )
		dbText(  dbScreenWidth() - XSCREENOFFSET, 5, _tmp);

	return ii;
}
int MyTimer::TimeOut()
{
	if ( Elapsed() / 10 >= m_countFrom )
	{
		_run = false;
		return 1;
	}
	return 0;
}
bool MyTimer::CountDown()
{
	if( timeSec <  m_countFrom) 
		return true;
	return false;
}	
int MyTimer::EndTime()
{
	return m_countFrom;
}