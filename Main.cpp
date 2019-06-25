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
	char str[][100] = {	"1 ---- ð������(B)",
						"2 ---- ѡ������(S)",
						"3 ---- ��������(Q)ע�������������ͣ�󣬰�g����",
						"4 ---- ��������(M��",
						"5 ---- ��������I��",
						"6 ---- ϣ������(H)",
						"7 ---- ˫������(�������ƣ�",
						"8 ---- ˫�����򣨻����ݹ飩",
						"9 ---- ˫��������������",
		                "10 ---- �ؾ�����(g)",
		                "11 ---- ˫��ð������(d)",
						"0 ---- �˳�(ESC)",
						"��ѡ��: "};
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

		ss.Start();						// ×"
		gettime(1);						// ¿ªÊ¼¼ÆÊ±
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
					ss.ShowText(2, 22, 0, 7, "û��ִ���κ������㷨");
		}
		t = gettime();					// ½áÊø¼ÆÊ±£¨·µ»ØÊ±¼ä²î£©
		ss.Finish();					// Êä³ö½á¹û

		sprintf(text, "��ʱ: %lf ��(���������������ʱ��ʱ��", t);
		ss.ShowText(30, 23, 0, 7, text);
		sprintf(text, "���س�����...");
		ss.ShowText(60, 24, 0, 7, text);
		system("pause");
		while(getch()!=13)
			;
	}
	return 0;
}
