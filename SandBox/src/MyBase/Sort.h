#pragma once
#include "Hazel/Core/TimeStep.h"
#include "Hazel/Renderer/OrthographicCamera.h"
#include <utility>

class Sort
{
public:
	static void Init();
	static void DrawArray();
	static void Swap(int a, int b);

	static void InsertionSort();

	static void SelectionSort();

	static void BubbleSort();

	static void MergeSort();
	static void MergeSort( int p , int r );
	static void Merge( int p, int q, int r);

	static void QuickSort();
	static void QuickSort(int l, int r);
	static int Partition(int l, int r);

	static void HeapSort();
	static void MaxHeap(int index, int n);
};

