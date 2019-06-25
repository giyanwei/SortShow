// Main.cpp
#include "SortShow.h"
#include <cstdlib>
#include <ctime>
#include <conio.h>

double gettime(int restart=0)
{
	const double c = 1.0/CLOCKS_PER_SEC;
	static clock_t t = clock();				// 静态局部变量
	if(restart) t = clock();
	return c*(clock()-t);
}

int main()
{
	char text[100];
	char str[][100] = {	"1 ---- 冒泡排序(B)",
						"2 ---- 选择排序(S)",
						"3 ---- 快速排序(Q)【注: 排序过程中暂停后，按g继续】",
						"4 ---- 猴子排序(M）",
						"5 ---- 插入排序（I）",
						"6 ---- 希尔排序(H)",
						"7 ---- 双调排序(基本递推）(N)",
						"8 ---- 双调排序（基本递归）(X)",
						"9 ---- 双调排序（任意数）(R)",
						"10 ---- 地精排序(G)",
						"11 ---- 双向冒泡排序(D)",
						"12 ---- 基数排序(J)",
						"13 ---- 桶排序(T)",
						"0 ---- 退  出(ESC)",
						"请选择: "};
	int choice, n=sizeof(str)/sizeof(*str);
	double t;
	unsigned char timbre = 19;	// 请尝试其他值，例如：0钢琴，19管风琴，24尼龙弦吉他，56小号，64高音萨克斯，101合成特效6，101筝，等等
	unsigned char Do = 48;		// 36（大字组C），48（小字组c），60（c1小组一组）等等
	int length = 16;			// 数据的个数

	SortShow ss(length, timbre, Do);		// 创建对象
	
	while(true)
	{
		system("cls");
		for(int i=0; i<n; i++)
			ss.ShowText(20, i+2, 0, 7, str[i]);		// 显示菜单
		choice = _getwch();
		if(choice==27 || choice=='0')
			break;

		ss.Start();						// 准备并输出"原始数据"
		gettime(1);						// 开始计时
		switch(choice)
		{
		case '1':
		case 'b':
		case 'B':	ss.BubbleSort();	break;
		case '2':
		case 's':
		case 'S':	ss.SelectionSort();	break;
		case '3':
		case 'q':
		case 'Q':	ss.QuickSort();		break;
		case '4':
		case 'm':
		case 'M':	ss.MonkeySort();	break;
		case '5':
		case 'i':
		case 'I':	ss.InsertSort();	break;
		case '6':
		case 'h':
		case 'H':	ss.ShellSort();		break;
		case '7':
		case 'n':
		case 'N':	ss.BitonicSort1();	break;
		case '8':
		case 'x':
		case 'X':	ss.BitonicSort2();	break;
		case '9':
		case 'r':
		case 'R':	ss.BitonicSort3();	break;
		case 'g':
		case 'G':	ss.gnomesort();	break;
		case 'd':
		case 'D':	ss.bidBubbleSort();	break;
		case 'j':
		case 'J':	ss.RadixSortLSD();	break;
		case 't':
		case 'T':	ss.BucketSort();	break;
		default:
					ss.ShowText(2, 22, 0, 7, "没有执行任何排序算法");
		}
		t = gettime();					// 结束计时（返回时间差）
		ss.Finish();					// 输出结果

		sprintf(text, "用时: %lf 秒(包括输出、音乐延时的时间)", t);
		ss.ShowText(30, 23, 0, 7, text);
		sprintf(text, "按回车键继续...");
		ss.ShowText(60, 24, 0, 7, text);
		while(_getch()!=13)
			;
	}
	return 0;
}
