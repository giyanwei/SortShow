// SortShow.h
// ��ע��������ӿ�winmm�����������ѡ�� -lwinmm������ָ����libwinmm�⣩���������£�Debug��Release�������þ���Ҫ��
//      ���˵� | Project | Settings...[Alt+F7] | Link | Libraries:�·��ı༭��������winmm
// ���� ���˵� | Project | Settings...[Alt+F7] | Link | Extra linking options:�·��༭�������� -lwinmm
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
												// ���캯��(Ĭ������Ԫ�ظ���:16; ��ɫ:����; DO:����C)
	SortShow(const SortShow &ss);				// �������캯��
	virtual ~SortShow();						// ��������

	void SetData();								// ����"ԭʼ����"
	void ReSetData();							// �ָ���"ԭʼ����"
	void Start();								// ����׼����ʼ
	void Finish() const;						// �������

	void ShowArray() const;						// ������������Ԫ��
	void ShowElements(const int *a, int i, int j, bool pause=false) const;	// ͬʱ�������Ԫ��
	void SWAP(int *a, int i, int j);			// ����Ԫ��i��Ԫ��j
	static DWORD MidiOutMessage(HMIDIOUT hMidiOut, int iStatus, int iChannel, int iNote, int iVolume);
												// Ϊ������� midiOutShortMsg ����
	static void ShowText(int x, int y, int bkcolor, int color, const char *str);

	void BubbleSort();							// ð�����򣨾���������㷨���䶨���� Sorts.cpp �ļ���
	void SelectionSort();						// ѡ������
	void QuickSort(int *a, int size);			// �������򣨵ݹ��㷨��
	void QuickSort()
	{
		ShowText(8, 0, 0, 7, "�������򡣴�*�ŵ�����˸ʱ��ʾ�˴λ�����ɣ�����ɳ����ʱ�밴g��G����");
		QuickSort(array, length);
	}
	// ��������������㷨

private:
	int length;									// ���ݸ���
	int array0[N], array[N];					// ��������ݣ���ʼ���ݣ�ȷ���󲻱䣩��ÿ������ǰarray[i]�ָ���array0[i]
	unsigned char timbre, notes[8];				// ��ɫ��0��ʾ���٣������׳���������������60��������C����ֵ��(��)1��ʾ��(��)������
	static HANDLE hStdIn, hStdOut;				// ��׼����/����ľ��
	static HMIDIOUT hMidiOut;					// MIDI����豸���
	static int nObjs;							// ����ĸ��������ڿ���MidiOut�豸�Ĵ���رգ�
};
#endif
