#pragma once
#include "common.h"
#include<iostream>
using namespace std;
class cpu_queen
{
public:
	cpu_queen() { gEightQueen[8] = 0; gCount = 0; };
	double runtest();
private:
	int check_pos_valid(int loop, int value);
	void eight_queen(int index);
	int gEightQueen[8], gCount;
	void print();
	CStopWatch timer;


};
void cpu_queen::print()//输出每一种情况下棋盘中皇后的摆放情况
{
	for (int i = 0; i < 8; i++)
	{
		int inner;
		for (inner = 0; inner < gEightQueen[i]; inner++)
			cout << "0";
		cout << "#";
		for (inner = gEightQueen[i] + 1; inner < 8; inner++)
			cout << "0";
		cout << endl;
	}
	cout << "==========================\n";
}
int cpu_queen::check_pos_valid(int loop, int value)//检查是否存在有多个皇后在同一行/列/对角线的情况
{
	int index;
	int data;
	for (index = 0; index < loop; index++)
	{
		data = gEightQueen[index];
		if (value == data)
			return 0;
		if ((index + data) == (loop + value))
			return 0;
		if ((index - data) == (loop - value))
			return 0;
	}
	return 1;
}
void cpu_queen::eight_queen(int index)
{
	int loop;
	for (loop = 0; loop < 8; loop++)
	{
		if (check_pos_valid(index, loop))
		{
			gEightQueen[index] = loop;
			if (7 == index)
			{
				gCount++;

#ifdef SHOW_PRINT
				print();
#endif // 			
				gEightQueen[index] = 0;
				return;
			}
			eight_queen(index + 1);
			gEightQueen[index] = 0;
		}
	}
}

double cpu_queen::runtest()
{
	timer.start();
	eight_queen(0);
	timer.stop();
	return timer.getElapsedTime();
}
