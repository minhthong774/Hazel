#pragma once
#include "Hazel/Core/TimeStep.h"
#include "Hazel/Renderer/OrthographicCamera.h"
#include <utility>

class Sort
{
public:
	static void Init();
	static void Draw();
	static void Run(Hazel::Timestep ts);

	static void InsertionSort(Hazel::Timestep ts);
	static void InsertionSort();

	static void SelectionSort(Hazel::Timestep ts);
	static void SelectionSort();

	static void BubbleSort(Hazel::Timestep ts);
	static void BubbleSort();

	static void MergeSort( int p , int r );
	static void Merge( int p, int q, int r);

	static void Quick3(int l, int r);
	static std::pair<int, int> PartitionQuick3(int l, int r);

	static void QuickSort(int l, int r);
	static int Partition(int l, int r);

	static void HeapSort();
	static void MaxHeap(int index, int n);
public:
	static bool run;
	static int i, j, last;
};

