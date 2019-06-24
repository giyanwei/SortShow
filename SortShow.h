// SortShow.h
// 请注意添加连接库winmm，或添加连接选项 -lwinmm（均意指连接libwinmm库）。方法如下（Debug和Release两种配置均需要）
//      主菜单 | Project | Settings...[Alt+F7] | Link | Libraries:下方的编辑栏中输入winmm
// 或者 主菜单 | Project | Settings...[Alt+F7] | Link | Extra linking options:下方编辑栏中输入 -lwinmm
#ifndef SORTSHOW_H
#define SORTSHOW_H
#include <windows.h>
#include <iostream>
using namespace std;

#define N 30

class SortShow
{
public:
	SortShow(int Length=16, unsigned char Timbre=0, unsigned char Do=60);
												// 构造函数(默认数组元素个数:16; 音色:钢琴; DO:中央C)
	SortShow(const SortShow &ss);				// 拷贝构造函数
	virtual ~SortShow();						// 析构函数

	void SetData();								// 设置"原始数据"
	void ReSetData();							// 恢复到"原始数据"
	void Start();								// 排序准备开始
	void Finish() const;						// 排序结束

	void ShowArray() const;						// 输出数组的所有元素
	void ShowElements(const int *a, int i, int j, bool pause=false) const;	// 同时输出两个元素
	void SWAP(int *a, int i, int j);			// 交换元素i与元素j
	static DWORD MidiOutMessage(HMIDIOUT hMidiOut, int iStatus, int iChannel, int iNote, int iVolume);
												// 为方便调用 midiOutShortMsg 函数
	static void ShowText(int x, int y, int bkcolor, int color, const char *str);

	void BubbleSort();							// 冒泡排序（具体的排序算法）其定义在 Sorts.cpp 文件中
	void SelectionSort();						// 选择排序
	void QuickSort(int *a, int size);			// 快速排序（递归算法）
	void QuickSort()
	{
		ShowText(8, 0, 0, 7, "快速排序。带*号的条闪烁时表示此次划分完成，听到沙锤声时请按g或G继续");
		QuickSort(array, length);
	}
	// 请添加其他排序算法

private:
	int length;									// 数据个数
	int array0[N], array[N];					// 排序的数据（初始数据，确定后不变），每次排序前array[i]恢复成array0[i]
	unsigned char timbre, notes[8];				// 音色（0表示钢琴）、音阶唱名（基本音符，60代表中心C，数值增(减)1表示升(降)半音）
	static HANDLE hStdIn, hStdOut;				// 标准输入/输出的句柄
	static HMIDIOUT hMidiOut;					// MIDI输出设备句柄
	static int nObjs;							// 对象的个数（用于控制MidiOut设备的打开与关闭）
};
#endif
