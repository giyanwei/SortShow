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
						"4 ---- 堆排序(A)",
						"5 ---- 递归排序(M)"
						"0 ---- 退  出(ESC)",
						"请选择: "};
	int choice, n=sizeof(str)/sizeof(*str);
	double t;
	unsigned char timbre = 0;	// 请尝试其他值，例如：0钢琴，19管风琴，24尼龙弦吉他，56小号，64高音萨克斯，101合成特效6，101筝，等等
	unsigned char Do = 48;		// 36（大字组C），48（小字组c），60（c1小组一组）等等
	int length = 20;			// 数据的个数

	SortShow ss(length, timbre, Do);		// 创建对象
	
	while(true)
	{
		system("cls");
		for(int i=0; i<n; i++)
			ss.ShowText(20, i+2, 0, 7, str[i]);		// 显示菜单
		choice = getch();
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
		case '4':	ss.heap_sort();		break;
		case '5':	ss.mysort();		break;
		default:
					ss.ShowText(2, 22, 0, 7, "没有执行任何排序算法");
		}
		t = gettime();					// 结束计时（返回时间差）
		ss.Finish();					// 输出结果

		sprintf(text, "用时: %lf 秒(包括输出、音乐延时的时间)", t);
		ss.ShowText(30, 23, 0, 7, text);
		sprintf(text, "按回车键继续...");
		ss.ShowText(60, 24, 0, 7, text);
		while(getch()!=13)
			;
	}
	return 0;
}
