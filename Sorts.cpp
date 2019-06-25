// Sorts.cpp	具体的排序算法成员函数定义（相应的函数声明在文件SortShow.h的SortShow类中）
#include "SortShow.h"
#include <conio.h>

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


int mpartition(int a[], int l, int r) {
	int pivot = a[l];

	while (l < r) {
		while (l < r && pivot <= a[r]) r--;
		if (l < r) a[l++] = a[r];
		while (l<r && pivot>a[l]) l++;
		if (l < r) a[r--] = a[l];
	}
	a[l] = pivot;
	return l;
}

void quick_sort(int a[], int l, int r) {

	if (l < r) {
		int q = mpartition(a, l, r);
		msort(a, l, q - 1);
		msort(a, q + 1, r);
	}
}


void SortShow::void heapAdjust(int a[], int i, int nLength) // 堆排序算法
{
	int nChild;
	int nTemp;
	for (nTemp = a[i]; 2 * i + 1 < nLength; i = nChild)
	{
		// 子结点的位置=2*（父结点位置）+ 1
		nChild = 2 * i + 1;
		// 得到子结点中较大的结点
		if (nChild < nLength - 1 && a[nChild + 1] > a[nChild])
			++nChild;
		// 如果较大的子结点大于父结点那么把较大的子结点往上移动，替换它的父结点
		if (nTemp < a[nChild])
		{
			a[i] = a[nChild];
			a[nChild] = nTemp;
		}
		else
			// 否则退出循环
			break;
	}
}

// 堆排序算法
void heap_sort(int a[], int length)
{
	int tmp;
	// 调整序列的前半部分元素，调整完之后第一个元素是序列的最大的元素
	//length/2-1是第一个非叶节点，此处"/"为整除
	for (int i = length / 2 - 1; i >= 0; --i)
		heapAdjust(a, i, length);
	// 从最后一个元素开始对序列进行调整，不断的缩小调整的范围直到第一个元素
	for (int i = length - 1; i > 0; --i)
	{
		// 把第一个元素和当前的最后一个元素交换，
		// 保证当前的最后一个位置的元素都是在现在的这个序列之中最大的
	  ///  Swap(&a[0], &a[i]);
		tmp = a[i];
		a[i] = a[0];
		a[0] = tmp;
		// 不断缩小调整heap的范围，每一次调整完毕保证第一个元素是当前序列的最大值
		heapAdjust(a, 0, i);
	}
}

// 归并排序算法
void merge(int *arry, int left, int mid, int right)
{
    int *temp = new int[right - left];
    int t = 0;
    int i = left;
    int j = mid;
    while (i < mid || j < right)
    {
        if (i>= mid)
        {
            temp[t++] = arry[j++];
        }
        else if (j>= right)
        {
            temp[t++] = arry[i++];
        }
        else
        {
            if (arry[i] < arry[j])
            {
                temp[t++] = arry[i++];
            }
            else
            {
                temp[t++] = arry[j++];
            }
        }
    }
    t = 0;
    for (int i = left; i < right; i++)
    {
        arry[i] = temp[t++];
    }
    delete[] temp;
}

void mysort(int *arry, int left, int right)  // 归并排序算法
{
    if (left + 1 < right)
    {
        int mid = (left + right) / 2;
        mysort(arry, left, mid);
        mysort(arry, mid, right);
        merge(arry, left, mid, right);
    }
}


