// Sorts.cpp	����������㷨��Ա�������壨��Ӧ�ĺ����������ļ�SortShow.h��SortShow���У�
#include "SortShow.h"
#include <conio.h>
#include <stdlib.h>

void SortShow::BubbleSort()
{
	int lastExchangeIndex = 0;				// ��¼���һ�ν�����λ��
	int sortBorder = length - 1;			// �������еı߽磬ÿ�αȽ�ֻ��Ҫ���е���
	bool isSorted;
	
	for(int i=0; i<length; i++)
	{
		isSorted = true;					// �����ǣ�ÿһ�ֵĳ�ʼ��true
		for(int j=0; j<sortBorder; j++)
		{
			if(array[j] > array[j+1])		// ��Ԫ����Ҫ����ʱ
			{
				SWAP(array, j, j+1);		// �˺������ô���ɫ����������ʾ���� array[j]��array[j+1]
				isSorted = false;			// ���Ǳ�Ϊfalse
				lastExchangeIndex = j;		// ���ҽ��������еı߽����Ϊ���һ�ν���Ԫ�ص�λ��
			}
		}
		sortBorder = lastExchangeIndex;
		if(isSorted) break;
	}
}

void SortShow::SelectionSort()				// ѡ������
{
	int minpos, maxpos, i, left=0, right=length-1;

	while(left < right)
	{
		minpos = maxpos = left;
		for(i=left; i<=right; i++)			// ȷ�����ֵ�±��Լ���Сֵ�±�
		{
			if(array[i] > array[maxpos])
				maxpos = i;
			if(array[i] < array[minpos])
				minpos = i;
		}
		if(maxpos != right)					// �����ֵ�嵽���
			SWAP(array, maxpos, right);
		if(minpos == right)					// �����ʱ��Сֵ��λ��ǡ�������ұߣ�������һ��䣬�Ѿ�����Сֵ����maxposλ���ˡ�
			minpos = maxpos;				// ����Ҫ����minpos�����磺3(left), 4(maxpos), 2, 1(minpos,right) ����һ��佻���� 3(left), 1(maxpos), 2, 4(minpos)
											// ��Ȼ��Ҫ��ɣ�3(left), 1(minpos), 2, 4
		if(minpos != left)					// �������µ�minpos��leftִ�н���: 1, 3, 2, 4
			SWAP(array, minpos, left);
		left++;								// 1, 3(left), 2(right), 4��Ȼ�������һ��ѭ��
		right--;
	}
}

void SortShow::QuickSort(int *a, int size)
{
	if(size<=1) return ;
	if(size==2)
	{
		if(a[0]>a[1]) SWAP(a, 0, 1);
		return;
	}
	ShowText(3, a-array+1, 7, 0, "[");			// �ݹ�ֶ����
	ShowText(3, a-array+size, 7, 0, "*");		// �ݹ�ֶ��յ㣬�ô���Ԫ��ֵ��Ϊ�ֽ������ֵ
	
	int left=0, right=size-1;
	int pivot = a[right];
	do
	{
		while(left<right && a[left] <= pivot)
			left++;
		while(left<right && a[right] >= pivot)
			right--;
		if(left < right)
			SWAP(a, left, right);
	}while(left<right);
	SWAP(a, size-1, left);

	ShowText(3, a-array+left+1, 7, 0, "-"); 
	MidiOutMessage(hMidiOut, 0x90, 0x09, 69, 127);		// ͨ��0x09��ָ����֣�69, 82 Shaker ɳ����
	Sleep(200);
	MidiOutMessage(hMidiOut, 0x90, 0x09, 82, 127);		// ͨ��0x09��ָ����֣�69, 82 Shaker ɳ����
	for(int key=0; key!='g' && key!='G'; )
		key = getch();
	QuickSort(a, left);
	QuickSort(a+left+1, size-left-1);
}

void SortShow::MonkeySort(int *a)
{
	int h=0, k=0;
	bool flag=false;
	while(1){
		h=rand();
		k=rand();
		SWAP(a , h, k);
		for (int i = 0; i < 16; i++)
		{
			if(array[i+1]>array[i])
				flag = true;
		}
		if (flag)
			break;
	}
}

void SortShow::InsertSort(int *a, int size) 
{
	for (int i = 1; i < size; i++) {
		int key = array[i];
		int j = i - 1;
		while ((j >= 0) && (key < array[j])) {
			SWAP(a, j, j + 1);
			j--;
		}
		array[j + 1] = key;
	}
}

void SortShow ::ShellSort(int *a, int size)
{
		int h = 1;
		while (h < size / 3) {
			h = 3 * h + 1;
		}
		while (h >= 1) {
			for (int i = h; i < size; i++) {
				for (int j = i; j >= h && array[j] < array[j - h]; j -= h) {
					SWAP(a,j, j - h);
				}
			}
			h = h / 3;
	}
}