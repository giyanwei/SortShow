// SortShow.cpp
#include "SortShow.h"
#include <conio.h>
#include <time.h>

int SortShow::nObjs = 0;								// ��̬���ݳ�Ա���弰��ʼ��������ĸ�����
HMIDIOUT SortShow::hMidiOut=NULL;						// ��̬���ݳ�Ա���弰��ʼ����MIDI����豸�����
HANDLE SortShow::hStdIn=NULL, SortShow::hStdOut=NULL;	// ��̬���ݳ�Ա���弰��ʼ��������̨��׼����/�����

SortShow::SortShow(int Length, unsigned char Timbre, unsigned char Do)
					: length(Length), timbre(Timbre)
{
	int channel = 0;									// ֻʹ��ͨ��0
	srand(time(NULL));									// ��ʼ�������������

	if(nObjs++ == 0)									// ��������һ������ʱ
	{
		hStdIn = GetStdHandle(STD_INPUT_HANDLE);
		hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTitle("SortShow������ - ������̿��ӻ�");
		midiOutOpen(&hMidiOut, MIDIMAPPER, 0, 0, 0);	// ��MIDI����ӳ���豸
	}
	MidiOutMessage(hMidiOut, 0xC0, channel, timbre, 0);	// ����ͨ��channel����ɫtimbre
	notes[0] = 0;										// ʵ����û��ʹ�ø�ֵ
	notes[1] = Do;										// ���� do
	notes[2] = notes[1] + 2;							// ���� re
	notes[3] = notes[2] + 2;							// ���� mi
	notes[4] = notes[3] + 1;							// �������� mi �� fa ֮��Ϊ����
	notes[5] = notes[4] + 2;
	notes[6] = notes[5] + 2;
	notes[7] = notes[6] + 2;
	
	if(length>N || length<=0)
		length = 16;
	SetData();											// ����Ȼ�� 1,2,3,...,length ����˳����������array0��
}

SortShow::SortShow(const SortShow &ss)
{
	*this = ss;						// ʹ��ϵͳ�ṩ��ǳ��ֵ�������������
	nObjs++;						// ��Ҫ���Ǽ�¼����ĸ���
}

SortShow::~SortShow()
{
	if(--nObjs==0)					// �������һ��������������������ʴ�ʱ��Ҫ�ر�MIDI����豸
		midiOutClose(hMidiOut);
}

void SortShow::SetData()
{
	int i;
	for(i=0; i < length; i++)
		array0[i] = 0;
	for(int x=1; x<=length; x++)
	{
		while(true)
		{
			i = rand() % length;
			if(array0[i]==0)
			{
				array0[i] = x;
				break;
			}
		}
	}
}

void SortShow::ReSetData()			// �ָ����ݣ�������array0�е����ݵ��뵽����array�У�
{
	for(int i=0; i < length; i++)
		array[i] = array0[i];
}

DWORD SortShow::MidiOutMessage(HMIDIOUT hMidiOut, int iStatus, int iChannel, int iNote, int iVolume)
{
	DWORD dwMessage = (iVolume << 16) | (iNote << 8) | iStatus         | iChannel;
					//      ����      |     ����     | ״̬�ֽ�(��4λ) | ͨ��(��4λ)
	return midiOutShortMsg(hMidiOut, dwMessage);
}

void SortShow::ShowText(int x, int y, int bkcolor, int color, const char *str)
{
	DWORD result;
	COORD coord = {x, y};
	SetConsoleCursorPosition(hStdOut, coord);
	SetConsoleTextAttribute(hStdOut, bkcolor<<4 | color);
	WriteConsole(hStdOut, str, strlen(str), &result, NULL);
}

void SortShow::ShowElements(const int *a, int i, int j, bool pause) const	// ���������array���±�index
{
	static char spaces[76] = "                                                                           ";
														// 75���ո���ַ���
	int i1 = a-array + i;								// ת����array���±�
	int j1 = a-array + j;								// ת����array���±�
	if(i1<0 || i1>=length || j1<0 || j1>=length) return;
	
	DWORD result;
	COORD coord1={5, i1+1}, coord2={5, j1+1};
	int color1, color2;
	char str[8];
	int note1 = notes[array[i1]%7+1] + 12*(array[i1]/7);// ����Ԫ�ص�ֵ����������ÿ����7��������8��(����12)��
	int note2 = notes[array[j1]%7+1] + 12*(array[j1]/7);// ����Ԫ�ص�ֵ����������ÿ����7��������8��(����12)��
	int r = (length ? 75/length : 1);					// r���ո��ַ���ȴ�������1
	color1 = array[i1] % 15;
	if(color1==0) color1 = 15;							// ��ʹ�ú�ɫ
	color2 = array[j1] % 15;
	if(color2==0) color2 = 15;							// ��ʹ�ú�ɫ

	MidiOutMessage(hMidiOut, 0x90, 0, note1, 127);		// 0x9*Ϊ������������note1�����������:127
	if(note2!=note1)
		MidiOutMessage(hMidiOut, 0x90, 0, note2, 127);	// 0x9*Ϊ������������note2�����������:127

	while(true)											// ����"��˸"Ч��
	{
		coord1.X = coord2.X = 5;
		SetConsoleCursorPosition(hStdOut, coord1);
		SetConsoleTextAttribute(hStdOut, color1<<4 | color1);	// ������ǰ��ͬɫ
		WriteConsole(hStdOut, spaces, r*array[i1], &result, NULL);
		coord1.X += r*array[i1];								// �ú�ɫ���Ǳ���β���ո��Ը���֮ǰ���ܵ���ɫ��
		SetConsoleCursorPosition(hStdOut, coord1);
		SetConsoleTextAttribute(hStdOut, 0);					// ������ǰ��ͬɫ���ڣ�
		WriteConsole(hStdOut, spaces, 75-r*array[i1], &result, NULL);
		if(j1 != i1)
		{
			SetConsoleCursorPosition(hStdOut, coord2);
			SetConsoleTextAttribute(hStdOut, color2<<4 |color2);// ������ǰ��ͬɫ
			WriteConsole(hStdOut, spaces, r*array[j1], &result, NULL);
			coord2.X += r*array[j1];							// �ú�ɫ���Ǳ���β���ո��Ը���֮ǰ���ܵ���ɫ��
			SetConsoleCursorPosition(hStdOut, coord2);
			SetConsoleTextAttribute(hStdOut, 0);				// ������ǰ��ͬɫ���ڣ�
			WriteConsole(hStdOut, spaces, 75-r*array[j1], &result, NULL);
		}
		Sleep(100);												// ��ͣ���Ժ���Ϊ��λ��1���� = 1e-6�룩
		coord1.X = coord2.X = 5;
		SetConsoleCursorPosition(hStdOut, coord1);
		SetConsoleTextAttribute(hStdOut, 0);					// ������ǰ��ͬɫ���ڣ�
		WriteConsole(hStdOut, spaces, r*array[i1], &result, NULL);
		if(j1 != i1)
		{
			SetConsoleCursorPosition(hStdOut, coord2);
			WriteConsole(hStdOut, spaces, r*array[j1], &result, NULL);
		}
		Sleep(100);
		SetConsoleCursorPosition(hStdOut, coord1);
		SetConsoleTextAttribute(hStdOut, color1<<4 | color1);	// ������Ԫ��ֵ��Ӧ����ɫ
		WriteConsole(hStdOut, spaces, r*array[i1], &result, NULL);
		if(j1 != i1)
		{
			SetConsoleCursorPosition(hStdOut, coord2);
			SetConsoleTextAttribute(hStdOut, color2<<4 | color2);// ������Ԫ��ֵ��Ӧ����ɫ
			WriteConsole(hStdOut, spaces, r*array[j1], &result, NULL);
		}
		if(pause==false)
			break;
		else
		{
			if(_kbhit())											// ���û�л���������0���ú���ԭ����conio.h�У�
			{
				_getch();
				break;
			}
		}
	}
	coord1.X = coord2.X = 0;
	SetConsoleCursorPosition(hStdOut, coord1);
	SetConsoleTextAttribute(hStdOut, 7);						// ����0��ǰ��7����Ĭ�����ԣ�
	sprintf(str, "%2d", array[i1]);
	WriteConsole(hStdOut, str, 2, &result, NULL);

	SetConsoleCursorPosition(hStdOut, coord2);
	sprintf(str, "%2d", array[j1]);
	WriteConsole(hStdOut, str, 2, &result, NULL);

	if(j1 != i1)
		MidiOutMessage(hMidiOut, 0x80, 0, note2, 127);			// 0x8*Ϊ��������ֹͣ����note2�����ٶ���죨�����رգ�:127
	MidiOutMessage(hMidiOut, 0x80, 0, note1, 127);				// 0x8*Ϊ��������ֹͣ����note1�����ٶ���죨�����رգ�:127
}

void SortShow::SWAP(int *a, int i, int j)
{				// ���ڿ����еݹ���㷨��a��һ��Ϊarray�������Ҫ����a-array��ֵ����ַ��Ϊ������
	int i1 = a-array + i;
	int j1 = a-array + j;
	if(i1<0 || j1<0 || i1>=length || j1>=length)
		return ;

	ShowElements(a, i, j, true);				// ����ǰ������ͣ��
	
	int note1 = notes[array[i1]%7+1] + 12*(array[i1]/7);
	int note2 = notes[array[j1]%7+1] + 12*(array[j1]/7);
	MidiOutMessage(hMidiOut, 0x90, 0, note1, 127);
	MidiOutMessage(hMidiOut, 0x90, 0, note2, 127);
	Sleep(500);
	MidiOutMessage(hMidiOut, 0x80, 0, note1, 127);
	MidiOutMessage(hMidiOut, 0x80, 0, note2, 127);

	int temp = array[i1];
	array[i1] = array[j1];
	array[j1] = temp;

	ShowElements(a, i, j);						// �����󣨲���ͣ��
}

void SortShow::ShowArray() const
{
	for(int i=0; i<length; i++)
		ShowElements(array, i, i);
}

void SortShow::Start()									// ����׼����ʼ
{
	DWORD result;
	COORD coord = {2, length+2};
	const char *str = "���������1���ӿ�ʼ...";
	
	ReSetData();										// �ָ����ݣ�ʹ����ͬ������׼������
	SetConsoleTextAttribute(hStdOut, 7);				// �ڵװ���
	system("cls");										// ����
	ShowArray();										// ԭʼ����
	
	SetConsoleCursorPosition(hStdOut, coord);
	SetConsoleTextAttribute(hStdOut, 4<<4 | 14);		// ����:��(4), ǰ��:��(14)
	WriteConsole(hStdOut, str, strlen(str), &result, NULL);
	_getch();
	SetConsoleCursorPosition(hStdOut, coord);
	WriteConsole(hStdOut, "���������......      ", 22, &result, NULL);
	MidiOutMessage(hMidiOut, 0x90, 0x09, 71, 127);		// ͨ��0x09��ָ����֣�71Ϊ Short Whistle ���ڣ�
	Sleep(1000);
}

void SortShow::Finish() const							// �������
{
	DWORD result;
	COORD coord = {2, length+2};
	const char *str = "������ɣ�������... ";

	MidiOutMessage(hMidiOut, 0x90, 0x09, 46, 127);		// ͨ��0x09��ָ����֣�46Ϊ Open Hi-Hat �������
	Sleep(1000);
	SetConsoleCursorPosition(hStdOut, coord);
	SetConsoleTextAttribute(hStdOut, 14<<4 | 4);		// ����:��(14); ǰ��:��(4)
	WriteConsole(hStdOut, str, strlen(str), &result, NULL);

	ShowArray();										// ������
	coord.X = 0;
	coord.Y = length+3;
	SetConsoleCursorPosition(hStdOut, coord);
	SetConsoleTextAttribute(hStdOut, 7);				// �ڵװ���
}
