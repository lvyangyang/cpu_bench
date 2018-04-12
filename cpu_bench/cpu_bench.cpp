// cpu_bench.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include<iostream>
#include <conio.h>
#include "cpu_queen.hpp"
#include "julia_mandel.hpp"
int main()
{
	double time;
//	cpu_queen queen_test;
//	double time = queen_test.runtest();
	julia_mandel ju_man(1024,1024);
//	time=ju_man.julia_test();
	time = ju_man.mandel_test();
	cout << "time is " << time << '\n' << endl;
	_getch();
}

