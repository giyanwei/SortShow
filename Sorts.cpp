// Sorts.cpp	具体的排序算法成员函数定义（相应的函数声明在文件SortShow.h的SortShow类中）
#include "SortShow.h"
#include <conio.h>
#include <vector>

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
		key = _getch();
	
	QuickSort(a, left);
	QuickSort(a+left+1, size-left-1);
}

void SortShow::RadixSortLSD(int *b, int size)
 {
	int a[16];
	for (int i = 0; i < size; i++)
	{
		a[i] = b[i];
	}
	int i, bucket[16], maxVal = 0, digitPosition = 1;
	for (i = 0; i < size; i++) 
	{
		if (a[i] > maxVal) 
		{ 
			maxVal = a[i]; 
		}
	}
	int pass = 1;  // used to show the progress
	/* maxVal: this variable decide the while-loop count
	if maxVal is 3 digits, then we loop through 3 times */
	while (maxVal / digitPosition > 0) {
		/* reset counter */
		int digitCount[10] = { 0 };
		/* count pos-th digits (keys) */
		for (i = 0; i < size; i++)
		{
			digitCount[a[i] / digitPosition % 10]++;
		}
		/* accumulated count */
		for (i = 1; i < 10; i++)
		{
			digitCount[i] += digitCount[i - 1];
		}
		/* To keep the order, start from back side */
   		for (i = size - 1; i >= 0; i--)
		{
   			bucket[--digitCount[a[i] / digitPosition % 10]] = a[i];
		}
		/* rearrange the original array using elements in the bucket */
		for (i = 0; i < size; i++)
		{
			a[i] = bucket[i];
			array[i] = a[i];
		}
		/* at this point, a array is sorted by digitPosition-th digit */
		if (digitPosition == 1)
		{
			ShowText(8, 0, 0, 7, "基于数字的个位进行第一轮排序");
		}
		else if (digitPosition == 10)
		{
			ShowText(8, 0, 0, 7, "基于数字的十位进行第二轮排序");
		}
		ShowArray();
		/* move up the digit position */
		digitPosition *= 10;
	}
}

struct ListNode 
{
	explicit ListNode(int i = 0) :mData(i), mNext(NULL) {}
	ListNode* mNext;
	int mData;
};

const int BUCKET_RANGE = 10;
const int BUCKET_NUM = 3;

ListNode* insert(ListNode* head, int val) 
{
	ListNode dummyNode;
	ListNode* newNode = new ListNode(val);
	ListNode* pre, * curr;
	dummyNode.mNext = head;
	pre = &dummyNode;
	curr = head;
	while (NULL != curr && curr->mData <= val)	// 遍历链表寻找节点应该所处的正确位置
	{
		pre = curr;
		curr = curr->mNext;
	}
	newNode->mNext = curr;						// 将节点插入其正确位置
	pre->mNext = newNode;						
	return dummyNode.mNext;
}

ListNode* Merge(ListNode* head1, ListNode* head2) 
{
	ListNode dummyNode;
	ListNode* dummy = &dummyNode;
	while (NULL != head1 && NULL != head2) 
	{
		if (head1->mData <= head2->mData) 
		{
			dummy->mNext = head1;
			head1 = head1->mNext;
		}
		else 
		{
			dummy->mNext = head2;
			head2 = head2->mNext;
		}
		dummy = dummy->mNext;
	}
	if (NULL != head1) dummy->mNext = head1;
	if (NULL != head2) dummy->mNext = head2;

	return dummyNode.mNext;
}

void SortShow::BucketSort(int a[], int size) 
{
	int arr[16];    // 拷贝一份与array一样的数组为arr
	for (int i = 0; i < 16; i++)
	{
		arr[i] = a[i];
	}

	// 将array中的数字按照index放入桶中的同时将每一个桶里的数字排序
	vector<ListNode*> buckets(3, (ListNode*)(0));
	for (int i = 0; i < size; ++i) 
	{
		int index = arr[i] / BUCKET_RANGE;
		ListNode* head = buckets.at(index);
		buckets.at(index) = insert(head, arr[i]);
	}

	// 第一次刷新显示
	ListNode* point = buckets.at(0);
	int i = 0;
	int k = i;
	for (int j = 0; j < BUCKET_NUM; j++)
	{
		point = buckets.at(j);
		if (point == NULL)
		{
			break;
		}
		ShowText(3, k + 1, 0, 7, "[");
		while (point->mNext != NULL)
		{
			array[i] = point->mData;
			point = point->mNext;
			i++;
			k++;
		}
		ShowText(3, k + 1, 0, 7, "[");
		k++;
	}
	ShowText(8, 0, 0, 7, "将数字放入[]桶中");
	ShowArray();

	// 将所有的桶按顺序合并
	ListNode* head = buckets.at(0);
	for (int i = 1; i < BUCKET_NUM; ++i) 
	{
		head = Merge(head, buckets.at(i));	// 合并两个桶 
		//将此次合并后的head中的变化刷新在屏幕上
		ShowText(8, 0, 0, 7, "将所有的桶按顺序合并");
		point = head;
		int j;
		for (j = 0; point != NULL; j++)
		{
			array[j] = point->mData;
			point = point->mNext;
		}
		for (j++; j < 16; j++)
		{
			array[j] = 0;
		}
		ShowArray();
	}

	// 从桶中的结果得出排好序的数组
	for (int i = 0; i < size; ++i) 
	{
		array[i] = head->mData;
		head = head->mNext;
	}
}

void SortShow::MonkeySort(int* a, int size)		// 猴子排序
{
	int count0 = 0;
	for (int i = 0; i < size; i++) {
		if (array[i + 1] > array[i])
			count0++;
	}
	if (count0 == size - 1)	return;
	int h = 0, k = 0, count = 0;
	while (1) {
		if (count == size - 1)
			break;
		h = rand() % size;
		do {
			k = rand() % size;
		} while (k == h);
		SWAP(a, h, k);
		count = 0;
		for (int i = 0; i < size; i++) {
			if (array[i + 1] > array[i])
				count++;
		}
	}
}

void SortShow::InsertSort(int* a, int size)		// 插入排序
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

void SortShow::ShellSort(int* a, int size)		// 希尔排序
{
	int h = 1;
	while (h < size / 3) {
		h = 3 * h + 1;
	}
	while (h >= 1) {
		for (int i = h; i < size; i++) {
			for (int j = i; j >= h && array[j] < array[j - h]; j -= h) {
				SWAP(a, j, j - h);
			}
		}
		h = h / 3;
	}
}
void SortShow::BitonicSort1() //双调递推
{
	bool asd = true;
	for (int step = 2; step < length; step *= 2)
	{
		for (int i = 0; i < length; i += 2 * step)
		{
			sortSeq(array + i, step, asd); // 前半升序
			sortSeq(array + i + step, step, !asd); // 后半降序
		}
	}
	sortSeq(array, length, asd);
}

void SortShow::sortSeq(int* array, int length, bool asd)
{
	int step = length / 2;
	for (; step > 0; step /= 2)
	{
		for (int i = 0; i < length; i += 2 * step)
		{
			for (int j = 0; j < step; ++j)
			{
				if (asd)
				{
					if (array[i + j] > array[i + step + j])
						SWAP(array, i + j, i + step + j);
				}
				else
				{
					if (array[i + j] < array[i + step + j])
						SWAP(array, i + j, i + step + j);
				}
			}
		}

	}
}
void SortShow::BitonicSort2() //双调递归
{
	bool asd = true;
	bitonicSort(array, length, asd);
}
void SortShow::bitonicSort(int* array, int length, bool asd) // asd 升序
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

void SortShow::bitonicMerge(int* array, int length, bool asd) // 合并
{
	if (length > 1)
	{
		int m = length / 2;
		for (int i = 0; i < m; ++i)
		{
			if (array[i] > array[i + m] == asd)
				SWAP(array, i, i + m); // 根据asd判断是否交换
		}
		// for循环结束后又生成了2个双调序列，分别merge直到序列长度为1
		bitonicMerge(array, m, asd); // 都是按照asd进行merge
		bitonicMerge(array + m, m, asd);
	}
}


void SortShow::bitonicSortAnyN(int* array, int length, bool asd)
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

void SortShow::BitonicSort3() //双调递归
{
	bool asd = true;
	bitonicSortAnyN(array, length, asd);
}




int getGreatest2nLessThan(int length) {
	int k = 1;
	while (k < length) k = k << 1; // 注意一定要加k=
	return k >> 1;
}
void SortShow::bitonicMergeAnyN(int* array, int length, bool asd) // 合并
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


void SortShow::gnomesort(int n, int* array)		// 地精排序
{
	int i = 0;

	while (i < n)
	{
		if (i == 0 || array[i - 1] <= array[i])
			i++;
		else
		{
			SWAP(array, i, i - 1);
			i--;
		}
	}
}


void SortShow::bidBubbleSort(int* array, int n)		// 双向冒泡排序
{
	int left, right, t, l, r, j, i = 0;

	left = 0;
	right = n - 1;


	while (left < right)
	{

		l = left + 1;
		r = right - 1;


		for (j = left; j < right; j++)
		{
			if (array[j] > array[j + 1])
			{
				SWAP(array, j, j + 1);
				r = j;
			}
		}
		right = r;


		for (j = right; j > left; j--)
		{
			if (array[j] < array[j - 1])
			{
				SWAP(array, j, j - 1);
				l = j;
			}
		}
		left = l;
	}
}
