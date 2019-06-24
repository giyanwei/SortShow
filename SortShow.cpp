// SortShow.cpp
#include "SortShow.h"
#include <conio.h>
#include <time.h>

int SortShow::nObjs = 0;								// 静态数据成员定义及初始化（对象的个数）
HMIDIOUT SortShow::hMidiOut=NULL;						// 静态数据成员定义及初始化（MIDI输出设备句柄）
HANDLE SortShow::hStdIn=NULL, SortShow::hStdOut=NULL;	// 静态数据成员定义及初始化（控制台标准输入/输出）

SortShow::SortShow(int Length, unsigned char Timbre, unsigned char Do)
					: length(Length), timbre(Timbre)
{
	int channel = 0;									// 只使用通道0
	srand(time(NULL));									// 初始化随机数发生器

	if(nObjs++ == 0)									// 当创建第一个对象时
	{
		hStdIn = GetStdHandle(STD_INPUT_HANDLE);
		hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTitle("SortShow排序秀 - 排序过程可视化");
		midiOutOpen(&hMidiOut, MIDIMAPPER, 0, 0, 0);	// 打开MIDI播放映射设备
	}
	MidiOutMessage(hMidiOut, 0xC0, channel, timbre, 0);	// 设置通道channel的音色timbre
	notes[0] = 0;										// 实际上没有使用该值
	notes[1] = Do;										// 唱名 do
	notes[2] = notes[1] + 2;							// 唱名 re
	notes[3] = notes[2] + 2;							// 唱名 mi
	notes[4] = notes[3] + 1;							// 七声音阶 mi 与 fa 之间为半音
	notes[5] = notes[4] + 2;
	notes[6] = notes[5] + 2;
	notes[7] = notes[6] + 2;
	
	if(length>N || length<=0)
		length = 16;
	SetData();											// 将自然是 1,2,3,...,length 打乱顺序存放在数组array0中
}

SortShow::SortShow(const SortShow &ss)
{
	*this = ss;						// 使用系统提供的浅赋值运算符函数即可
	nObjs++;						// 重要的是记录对象的个数
}

SortShow::~SortShow()
{
	if(--nObjs==0)					// 这是最后一个对象调用析构函数，故此时需要关闭MIDI输出设备
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

void SortShow::ReSetData()			// 恢复数据（将数组array0中的数据导入到数组array中）
{
	for(int i=0; i < length; i++)
		array[i] = array0[i];
}

DWORD SortShow::MidiOutMessage(HMIDIOUT hMidiOut, int iStatus, int iChannel, int iNote, int iVolume)
{
	DWORD dwMessage = (iVolume << 16) | (iNote << 8) | iStatus         | iChannel;
					//      音量      |     音符     | 状态字节(高4位) | 通道(低4位)
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

void SortShow::ShowElements(const int *a, int i, int j, bool pause) const	// 相对于数组array的下标index
{
	static char spaces[76] = "                                                                           ";
														// 75个空格的字符串
	int i1 = a-array + i;								// 转换成array的下标
	int j1 = a-array + j;								// 转换成array的下标
	if(i1<0 || i1>=length || j1<0 || j1>=length) return;
	
	DWORD result;
	COORD coord1={5, i1+1}, coord2={5, j1+1};
	int color1, color2;
	char str[8];
	int note1 = notes[array[i1]%7+1] + 12*(array[i1]/7);// 根据元素的值设置音符（每超过7倍，升高8度(即加12)）
	int note2 = notes[array[j1]%7+1] + 12*(array[j1]/7);// 根据元素的值设置音符（每超过7倍，升高8度(即加12)）
	int r = (length ? 75/length : 1);					// r个空格字符宽度代表数组1
	color1 = array[i1] % 15;
	if(color1==0) color1 = 15;							// 不使用黑色
	color2 = array[j1] % 15;
	if(color2==0) color2 = 15;							// 不使用黑色

	MidiOutMessage(hMidiOut, 0x90, 0, note1, 127);		// 0x9*为开音（即播放note1），音量最大:127
	if(note2!=note1)
		MidiOutMessage(hMidiOut, 0x90, 0, note2, 127);	// 0x9*为开音（即播放note2），音量最大:127

	while(true)											// 做成"闪烁"效果
	{
		coord1.X = coord2.X = 5;
		SetConsoleCursorPosition(hStdOut, coord1);
		SetConsoleTextAttribute(hStdOut, color1<<4 | color1);	// 背景和前景同色
		WriteConsole(hStdOut, spaces, r*array[i1], &result, NULL);
		coord1.X += r*array[i1];								// 用黑色覆盖本行尾部空格（以覆盖之前可能的颜色）
		SetConsoleCursorPosition(hStdOut, coord1);
		SetConsoleTextAttribute(hStdOut, 0);					// 背景和前景同色（黑）
		WriteConsole(hStdOut, spaces, 75-r*array[i1], &result, NULL);
		if(j1 != i1)
		{
			SetConsoleCursorPosition(hStdOut, coord2);
			SetConsoleTextAttribute(hStdOut, color2<<4 |color2);// 背景和前景同色
			WriteConsole(hStdOut, spaces, r*array[j1], &result, NULL);
			coord2.X += r*array[j1];							// 用黑色覆盖本行尾部空格（以覆盖之前可能的颜色）
			SetConsoleCursorPosition(hStdOut, coord2);
			SetConsoleTextAttribute(hStdOut, 0);				// 背景和前景同色（黑）
			WriteConsole(hStdOut, spaces, 75-r*array[j1], &result, NULL);
		}
		Sleep(100);												// 暂停，以毫秒为单位（1毫秒 = 1e-6秒）
		coord1.X = coord2.X = 5;
		SetConsoleCursorPosition(hStdOut, coord1);
		SetConsoleTextAttribute(hStdOut, 0);					// 背景和前景同色（黑）
		WriteConsole(hStdOut, spaces, r*array[i1], &result, NULL);
		if(j1 != i1)
		{
			SetConsoleCursorPosition(hStdOut, coord2);
			WriteConsole(hStdOut, spaces, r*array[j1], &result, NULL);
		}
		Sleep(100);
		SetConsoleCursorPosition(hStdOut, coord1);
		SetConsoleTextAttribute(hStdOut, color1<<4 | color1);	// 用数组元素值对应的颜色
		WriteConsole(hStdOut, spaces, r*array[i1], &result, NULL);
		if(j1 != i1)
		{
			SetConsoleCursorPosition(hStdOut, coord2);
			SetConsoleTextAttribute(hStdOut, color2<<4 | color2);// 用数组元素值对应的颜色
			WriteConsole(hStdOut, spaces, r*array[j1], &result, NULL);
		}
		if(pause==false)
			break;
		else
		{
			if(_kbhit())											// 如果没有击键，返回0（该函数原型在conio.h中）
			{
				_getch();
				break;
			}
		}
	}
	coord1.X = coord2.X = 0;
	SetConsoleCursorPosition(hStdOut, coord1);
	SetConsoleTextAttribute(hStdOut, 7);						// 背景0，前景7（即默认属性）
	sprintf(str, "%2d", array[i1]);
	WriteConsole(hStdOut, str, 2, &result, NULL);

	SetConsoleCursorPosition(hStdOut, coord2);
	sprintf(str, "%2d", array[j1]);
	WriteConsole(hStdOut, str, 2, &result, NULL);

	if(j1 != i1)
		MidiOutMessage(hMidiOut, 0x80, 0, note2, 127);			// 0x8*为关音（即停止播放note2），速度最快（立即关闭）:127
	MidiOutMessage(hMidiOut, 0x80, 0, note1, 127);				// 0x8*为关音（即停止播放note1），速度最快（立即关闭）:127
}

void SortShow::SWAP(int *a, int i, int j)
{				// 由于可能有递归等算法，a不一定为array，因此需要考虑a-array的值（地址差为整数）
	int i1 = a-array + i;
	int j1 = a-array + j;
	if(i1<0 || j1<0 || i1>=length || j1>=length)
		return ;

	ShowElements(a, i, j, true);				// 交换前（含暂停）
	
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

	ShowElements(a, i, j);						// 交换后（不暂停）
}

void SortShow::ShowArray() const
{
	for(int i=0; i<length; i++)
		ShowElements(array, i, i);
}

void SortShow::Start()									// 排序准备开始
{
	DWORD result;
	COORD coord = {2, length+2};
	const char *str = "按任意键后1秒钟开始...";
	
	ReSetData();										// 恢复数据（使用相同的数据准备排序）
	SetConsoleTextAttribute(hStdOut, 7);				// 黑底白字
	system("cls");										// 清屏
	ShowArray();										// 原始数据
	
	SetConsoleCursorPosition(hStdOut, coord);
	SetConsoleTextAttribute(hStdOut, 4<<4 | 14);		// 背景:红(4), 前景:黄(14)
	WriteConsole(hStdOut, str, strlen(str), &result, NULL);
	_getch();
	SetConsoleCursorPosition(hStdOut, coord);
	WriteConsole(hStdOut, "排序进行中......      ", 22, &result, NULL);
	MidiOutMessage(hMidiOut, 0x90, 0x09, 71, 127);		// 通道0x09特指打击乐（71为 Short Whistle 短哨）
	Sleep(1000);
}

void SortShow::Finish() const							// 排序结束
{
	DWORD result;
	COORD coord = {2, length+2};
	const char *str = "排序完成，输出结果... ";

	MidiOutMessage(hMidiOut, 0x90, 0x09, 46, 127);		// 通道0x09特指打击乐（46为 Open Hi-Hat 开音踩镲）
	Sleep(1000);
	SetConsoleCursorPosition(hStdOut, coord);
	SetConsoleTextAttribute(hStdOut, 14<<4 | 4);		// 背景:黄(14); 前景:红(4)
	WriteConsole(hStdOut, str, strlen(str), &result, NULL);

	ShowArray();										// 排序结果
	coord.X = 0;
	coord.Y = length+3;
	SetConsoleCursorPosition(hStdOut, coord);
	SetConsoleTextAttribute(hStdOut, 7);				// 黑底白字
}
