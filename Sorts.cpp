// Sorts.cpp	����������㷨��Ա�������壨��Ӧ�ĺ����������ļ�SortShow.h��SortShow���У�
#include "SortShow.h"
#include <conio.h>

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


void SortShow::void heapAdjust(int a[], int i, int nLength) // �������㷨
{
	int nChild;
	int nTemp;
	for (nTemp = a[i]; 2 * i + 1 < nLength; i = nChild)
	{
		// �ӽ���λ��=2*�������λ�ã�+ 1
		nChild = 2 * i + 1;
		// �õ��ӽ���нϴ�Ľ��
		if (nChild < nLength - 1 && a[nChild + 1] > a[nChild])
			++nChild;
		// ����ϴ���ӽ����ڸ������ô�ѽϴ���ӽ�������ƶ����滻���ĸ����
		if (nTemp < a[nChild])
		{
			a[i] = a[nChild];
			a[nChild] = nTemp;
		}
		else
			// �����˳�ѭ��
			break;
	}
}

// �������㷨
void heap_sort(int a[], int length)
{
	int tmp;
	// �������е�ǰ�벿��Ԫ�أ�������֮���һ��Ԫ�������е�����Ԫ��
	//length/2-1�ǵ�һ����Ҷ�ڵ㣬�˴�"/"Ϊ����
	for (int i = length / 2 - 1; i >= 0; --i)
		heapAdjust(a, i, length);
	// �����һ��Ԫ�ؿ�ʼ�����н��е��������ϵ���С�����ķ�Χֱ����һ��Ԫ��
	for (int i = length - 1; i > 0; --i)
	{
		// �ѵ�һ��Ԫ�غ͵�ǰ�����һ��Ԫ�ؽ�����
		// ��֤��ǰ�����һ��λ�õ�Ԫ�ض��������ڵ��������֮������
	  ///  Swap(&a[0], &a[i]);
		tmp = a[i];
		a[i] = a[0];
		a[0] = tmp;
		// ������С����heap�ķ�Χ��ÿһ�ε�����ϱ�֤��һ��Ԫ���ǵ�ǰ���е����ֵ
		heapAdjust(a, 0, i);
	}
}

// �鲢�����㷨
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

void mysort(int *arry, int left, int right)  // �鲢�����㷨
{
    if (left + 1 < right)
    {
        int mid = (left + right) / 2;
        mysort(arry, left, mid);
        mysort(arry, mid, right);
        merge(arry, left, mid, right);
    }
}


