// Main.cpp
#include "SortShow.h"
#include <cstdlib>
#include <ctime>
#include <conio.h>

double gettime(int restart=0)
{
	const double c = 1.0/CLOCKS_PER_SEC;
	static clock_t t = clock();				// ��̬�ֲ�����
	if(restart) t = clock();
	return c*(clock()-t);
}

int main()
{
	char text[100];
	char str[][100] = {	"1 ---- ð������(B)",
						"2 ---- ѡ������(S)",
						"3 ---- ��������(Q)��ע: �����������ͣ�󣬰�g������",
						"4 ---- ��������(M��",
						"5 ---- ��������I��",
						"6 ---- ϣ������(H)",
						"7 ---- ˫������(�������ƣ�(N)",
						"8 ---- ˫�����򣨻����ݹ飩(X)",
						"9 ---- ˫��������������(R)",
						"10 ---- �ؾ�����(G)",
						"11 ---- ˫��ð������(D)",
						"12 ---- ��������(J)",
						"13 ---- Ͱ����(T)",
						"0 ---- ��  ��(ESC)",
						"��ѡ��: "};
	int choice, n=sizeof(str)/sizeof(*str);
	double t;
	unsigned char timbre = 19;	// �볢������ֵ�����磺0���٣�19�ܷ��٣�24�����Ҽ�����56С�ţ�64��������˹��101�ϳ���Ч6��101�ݣ��ȵ�
	unsigned char Do = 48;		// 36��������C����48��С����c����60��c1С��һ�飩�ȵ�
	int length = 16;			// ���ݵĸ���

	SortShow ss(length, timbre, Do);		// ��������
	
	while(true)
	{
		system("cls");
		for(int i=0; i<n; i++)
			ss.ShowText(20, i+2, 0, 7, str[i]);		// ��ʾ�˵�
		choice = _getwch();
		if(choice==27 || choice=='0')
			break;

		ss.Start();						// ׼�������"ԭʼ����"
		gettime(1);						// ��ʼ��ʱ
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
					ss.ShowText(2, 22, 0, 7, "û��ִ���κ������㷨");
		}
		t = gettime();					// ������ʱ������ʱ��
		ss.Finish();					// ������

		sprintf(text, "��ʱ: %lf ��(���������������ʱ��ʱ��)", t);
		ss.ShowText(30, 23, 0, 7, text);
		sprintf(text, "���س�������...");
		ss.ShowText(60, 24, 0, 7, text);
		while(_getch()!=13)
			;
	}
	return 0;
}
