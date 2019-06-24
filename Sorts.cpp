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

void SortShow::MonkeySort(int *a, int size)
{
	int count0 = 0;
	for (int i = 0; i < size; i++) {
		if (array[i + 1] > array[i])
			count0++;
	}
	if (count0 == size - 1)	return;
	int h=0, k=0,count=0;
	while(1){
		if (count == size-1)
			break;
		h=rand()%size;
		do{
		k=rand()%size;
		} while (k == h);
		SWAP(a, h, k);
		count = 0;
		for (int i = 0; i < size; i++) {
			if (array[i + 1] > array[i]) 
				count++;
		}
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

void SortShow::bitonicSortAnyN(int *array, int length, bool asd)
{ // asd ����
	if (length > 1)
	{
		int m = length / 2;
		bitonicSortAnyN(array, m, !asd); // ǰ�뽵��
		bitonicSortAnyN(array + m, length - m, asd); // �������
		// ǰ2��sort֮���γ���˫�����У�Ȼ����merge�ϲ���asd�涨������
//        bitonicMerge(arr, len, asd); // ע�͵�����˫������
		bitonicMergeAnyN(array, length, asd);
	}
}

void SortShow::BitonicSort1() //˫���ݹ�
{
	bool asd = true;
	bitonicSortAnyN(array, length, asd);
}

/*void SortShow::bitonicSort(int *array, int length, bool asd) // asd ����
{
	if (length > 1)
	{
		int m = length / 2;
		bitonicSort(array, m, !asd); // ǰ�뽵��
		bitonicSort(array + m, length - m, asd); // �������
		// ǰ2��sort֮���γ���1��˫�����У�Ȼ����merge�ϲ���asd�涨������
		bitonicMerge(array, length, asd); // �ϲ�
	}
}
*/



int getGreatest2nLessThan(int length) {
	int k = 1;
	while (k < length) k = k << 1; // ע��һ��Ҫ��k=
	return k >> 1;
}
void SortShow::bitonicMergeAnyN(int *array, int length, bool asd) // �ϲ�
{
	if (length > 1)
	{
		int m = getGreatest2nLessThan(length);
		for (int i = 0; i < length - m; ++i)
		{
			if (array[i] > array[i + m] == asd)
				SWAP(array, i, i + m); // ����asd�ж��Ƿ񽻻�
		}
		// forѭ����������������2��˫�����У��ֱ�mergeֱ�����г���Ϊ1
		bitonicMergeAnyN(array, m, asd); // ���ǰ���asd����merge
		bitonicMergeAnyN(array + m, length - m, asd);
	}
}



/* ����˫������鲢
void bitonicMerge(int *arr, int len, bool asd) {
	if (len > 1) {
		int m = len / 2;
		for (int i = 0; i < m; ++i) {
			if (arr[i] > arr[i + m] == asd)
				swap(arr[i], arr[i + m]); // ����asd�ж��Ƿ񽻻�
		}
		// forѭ����������������2��˫�����У��ֱ�mergeֱ�����г���Ϊ1
		bitonicMerge(arr, m, asd);
		bitonicMerge(arr + m, m, asd);
	}
}
*/
// ����˫������鲢
/*void SortShow::bitonicMergeAnyN(int *array, int length, bool asd)
 {
	if (length > 1) {
		int m = getGreatest2nLessThan(length);
		for (int i = 0; i < length - m; ++i) {
			if (array[i] > array[i + m] == asd)
				swap(array[i], array[i + m]); // ����asd�ж��Ƿ񽻻�
		}
		bitonicMergeAnyN(array, m, asd); // һ������£�m > len-m
		bitonicMergeAnyN(array + m, length - m, asd);
	}
}
*/
// ˫�����򣨻��� + ���⣩

