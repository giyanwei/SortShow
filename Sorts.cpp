// Sorts.cpp	具体的排序算法成员函数定义（相应的函数声明在文件SortShow.h的SortShow类中）
#include "SortShow.h"
#include <conio.h>
#include <stdlib.h>


void SortShow::BubbleSort()
{
	int lastExchangeIndex = 0;				// 记录最后一次交换的位置
	int sortBorder = length - 1;			// 无序数列的边界，每次比较只需要进行到此
	bool isSorted;
	
	for(int i=0; i<length; i++)
	{
		isSorted = true;					// 有序标记，每一轮的初始是true
		for(int j=0; j<sortBorder; j++)
		{
			if(array[j] > array[j+1])		// 有元素需要交换时
			{
				SWAP(array, j, j+1);		// 此函数采用带颜色、声音地显示数据 array[j]和array[j+1]
				isSorted = false;			// 则标记变为false
				lastExchangeIndex = j;		// 并且将无序数列的边界更新为最后一次交换元素的位置
			}
		}
		sortBorder = lastExchangeIndex;
		if(isSorted) break;
	}
}

void SortShow::SelectionSort()				// 选择排序
{
	int minpos, maxpos, i, left=0, right=length-1;

	while(left < right)
	{
		minpos = maxpos = left;
		for(i=left; i<=right; i++)			// 确定最大值下标以及最小值下标
		{
			if(array[i] > array[maxpos])
				maxpos = i;
			if(array[i] < array[minpos])
				minpos = i;
		}
		if(maxpos != right)					// 将最大值插到最后
			SWAP(array, maxpos, right);
		if(minpos == right)					// 如果此时最小值的位置恰好在最右边，由于上一语句，已经将最小值换至maxpos位置了。
			minpos = maxpos;				// 故需要更新minpos。例如：3(left), 4(maxpos), 2, 1(minpos,right) 则上一语句交换成 3(left), 1(maxpos), 2, 4(minpos)
											// 当然需要变成，3(left), 1(minpos), 2, 4
		if(minpos != left)					// 将根据新的minpos及left执行交换: 1, 3, 2, 4
			SWAP(array, minpos, left);
		left++;								// 1, 3(left), 2(right), 4。然后进入下一轮循环
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
	ShowText(3, a-array+1, 7, 0, "[");			// 递归分段起点
	ShowText(3, a-array+size, 7, 0, "*");		// 递归分段终点，该处的元素值作为分界的轴心值
	
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
	MidiOutMessage(hMidiOut, 0x90, 0x09, 69, 127);		// 通道0x09特指打击乐（69, 82 Shaker 沙锤）
	Sleep(200);
	MidiOutMessage(hMidiOut, 0x90, 0x09, 82, 127);		// 通道0x09特指打击乐（69, 82 Shaker 沙锤）
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
{ // asd 升序
	if (length > 1)
	{
		int m = length / 2;
		bitonicSortAnyN(array, m, !asd); // 前半降序
		bitonicSortAnyN(array + m, length - m, asd); // 后半升序
		// 前2个sort之后形成了双调序列，然后传入merge合并成asd规定的序列
//        bitonicMerge(arr, len, asd); // 注释掉基本双调排序
		bitonicMergeAnyN(array, length, asd);
	}
}

void SortShow::BitonicSort1() //双调递归
{
	bool asd = true;
	bitonicSortAnyN(array, length, asd);
}

/*void SortShow::bitonicSort(int *array, int length, bool asd) // asd 升序
{
	if (length > 1)
	{
		int m = length / 2;
		bitonicSort(array, m, !asd); // 前半降序
		bitonicSort(array + m, length - m, asd); // 后半升序
		// 前2个sort之后形成了1个双调序列，然后传入merge合并成asd规定的序列
		bitonicMerge(array, length, asd); // 合并
	}
}
*/



int getGreatest2nLessThan(int length) {
	int k = 1;
	while (k < length) k = k << 1; // 注意一定要加k=
	return k >> 1;
}
void SortShow::bitonicMergeAnyN(int *array, int length, bool asd) // 合并
{
	if (length > 1)
	{
		int m = getGreatest2nLessThan(length);
		for (int i = 0; i < length - m; ++i)
		{
			if (array[i] > array[i + m] == asd)
				SWAP(array, i, i + m); // 根据asd判断是否交换
		}
		// for循环结束后又生成了2个双调序列，分别merge直到序列长度为1
		bitonicMergeAnyN(array, m, asd); // 都是按照asd进行merge
		bitonicMergeAnyN(array + m, length - m, asd);
	}
}



/* 基本双调排序归并
void bitonicMerge(int *arr, int len, bool asd) {
	if (len > 1) {
		int m = len / 2;
		for (int i = 0; i < m; ++i) {
			if (arr[i] > arr[i + m] == asd)
				swap(arr[i], arr[i + m]); // 根据asd判断是否交换
		}
		// for循环结束后又生成了2个双调序列，分别merge直到序列长度为1
		bitonicMerge(arr, m, asd);
		bitonicMerge(arr + m, m, asd);
	}
}
*/
// 任意双调排序归并
/*void SortShow::bitonicMergeAnyN(int *array, int length, bool asd)
 {
	if (length > 1) {
		int m = getGreatest2nLessThan(length);
		for (int i = 0; i < length - m; ++i) {
			if (array[i] > array[i + m] == asd)
				swap(array[i], array[i + m]); // 根据asd判断是否交换
		}
		bitonicMergeAnyN(array, m, asd); // 一般情况下，m > len-m
		bitonicMergeAnyN(array + m, length - m, asd);
	}
}
*/
// 双调排序（基本 + 任意）

