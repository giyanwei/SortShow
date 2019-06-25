// Main.cpp
#include "SortShow.h"
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>


double gettime(int restart=0)
{
	const double c = 1.0/CLOCKS_PER_SEC;
	static clock_t t = clock();				// 
	if(restart) t = clock();
	return c*(clock()-t);
}

int main()
{
	char text[100];
	char str[][100] = {	"1 ---- 冒泡排序(B)",
						"2 ---- 选择排序(S)",
						"3 ---- 快速排序(Q)注：排序过程中暂停后，按g继续",
						"4 ---- 猴子排序(M）",
						"5 ---- 插入排序（I）",
						"6 ---- 希尔排序(H)",
						"7 ---- 双调排序(基本递推）",
						"8 ---- 双调排序（基本递归）",
						"9 ---- 双调排序（任意数）",
		                "10 ---- 地精排序(g)",
		                "11 ---- 双向冒泡排序(d)",
						"0 ---- 退出(ESC)",
						"请选择: "};
	int choice, n=sizeof(str)/sizeof(*str);
	double t;
	unsigned char timbre = 0;	// 
	unsigned char Do = 48;		//
	int length = 20
		  ;			// 

	SortShow ss(length, timbre, Do);		// 
	
	while(true)
	{
		system("cls");
		for(int i=0; i<n; i++)
			ss.ShowText(20, i+2, 0, 7, str[i]);		// 
		choice = getch();
		if(choice==27 || choice=='0')
			break;

		ss.Start();						// 脳"
		gettime(1);						// 驴陋脢录录脝脢卤
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
		case 'M':
		case 'm':	ss.MonkeySort();	break;
		case '5':	
		case 'I':	
		case 'i':	ss.InsertSort();	break;
		case '6':
		case 'h':	ss.ShellSort();		break;
		case '7':   ss.BitonicSort1(); break;
		case '8':   ss.BitonicSort2(); break;
		case 'g':   ss.gnomesort();     break;
		case '9':   ss.BitonicSort3(); break;
		case 'd':   ss.bidBubbleSort(); break;
	
		default:
					ss.ShowText(2, 22, 0, 7, "没有执行任何排序算法");
		}
		t = gettime();					// 陆谩脢酶录脝脢卤拢篓路碌禄脴脢卤录盲虏卯拢漏
		ss.Finish();					// 脢盲鲁枚陆谩鹿没

		sprintf(text, "用时: %lf 秒(包括输出、音乐延时的时间", t);
		ss.ShowText(30, 23, 0, 7, text);
		sprintf(text, "按回车继续...");
		ss.ShowText(60, 24, 0, 7, text);
		system("pause");
		while(getch()!=13)
			;
	}
	return 0;
}
