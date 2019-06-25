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
						"4 ---- ������(A)",
						"5 ---- �ݹ�����(M)"
						"0 ---- ��  ��(ESC)",
						"��ѡ��: "};
	int choice, n=sizeof(str)/sizeof(*str);
	double t;
	unsigned char timbre = 0;	// �볢������ֵ�����磺0���٣�19�ܷ��٣�24�����Ҽ�����56С�ţ�64��������˹��101�ϳ���Ч6��101�ݣ��ȵ�
	unsigned char Do = 48;		// 36��������C����48��С����c����60��c1С��һ�飩�ȵ�
	int length = 20;			// ���ݵĸ���

	SortShow ss(length, timbre, Do);		// ��������
	
	while(true)
	{
		system("cls");
		for(int i=0; i<n; i++)
			ss.ShowText(20, i+2, 0, 7, str[i]);		// ��ʾ�˵�
		choice = getch();
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
		case '4':	ss.heap_sort();		break;
		case '5':	ss.mysort();		break;
		default:
					ss.ShowText(2, 22, 0, 7, "û��ִ���κ������㷨");
		}
		t = gettime();					// ������ʱ������ʱ��
		ss.Finish();					// ������

		sprintf(text, "��ʱ: %lf ��(���������������ʱ��ʱ��)", t);
		ss.ShowText(30, 23, 0, 7, text);
		sprintf(text, "���س�������...");
		ss.ShowText(60, 24, 0, 7, text);
		while(getch()!=13)
			;
	}
	return 0;
}
