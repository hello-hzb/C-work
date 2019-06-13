/************************************************************************
* 功能：秒计时，精确到微秒，计算耗时常用


************************************************************************/
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
void main()
{
	large_integer nfreq;//large_integer在64位系统中是longlong，在32位系统中是高低两个32位的long，在windows.h中通过预编译宏作定义
	large_integer nbegintime;//记录开始时的计数器的值
	large_integer nendtime;//记录停止时的计数器的值
	double time;

	queryperformancefrequency(&nfreq);//获取系统时钟频率
	queryperformancecounter(&nbegintime);//获取开始时刻计数值

	//to do:
	queryperformancecounter(&nendtime);//获取停止时刻计数值
	time = (double)(nendtime.quadpart - nbegintime.quadpart) / (double)nfreq.quadpart;//（开始-停止）/频率即为秒数，精确到小数点后6位
	printf("%2.9f", time);
}


//这种计时方法只能精确到ms
// DWORD start, end;
// start = GetTickCount();
// //to do
// end = GetTickCount();
// total_time = (end - start);
// printf("test1.mp4 test efficiency is %d us/frame.\n", total_time/3934);