#include "hzpch.h"
#include "Sort.h"
#include <ctime>
#include <stdlib.h>
#include <Hazel/Renderer/Renderer2D.h>
#include "Hazel/Renderer/RenderCommand.h"
#include "Hazel/Core/Application.h"
#include "Hazel/Core/Window.h"

const int size = 200;
const int maxValue = 20;
static int arr[size]{0};
static int arrMerge[size];
static int arrColor[size]{0};

void Sort::Init()
{
	srand(time(NULL));
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand() % maxValue + 1;
		arrColor[i] = 0;
	}
}

void Sort::DrawArray()
{
	Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Hazel::RenderCommand::Clear();

	for (int x = 0; x < size; x++)
	{
		int a = arr[x];
		glm::vec4 color;
		if (arrColor[x] == 0)
			color = { 0.2f, 0.3f, 0.8f, 1.0f };
		else if (arrColor[x] == 1)
			color = { 0.8f, 0.3f, 0.2f, 1.0f };
		else if (arrColor[x] == 2)
			color = { 0.3f, 0.8f, 0.2f, 1.0f };

		float aspectRatio = 1280 / 720.0;
		float posX = (x + 1/2.0) * (1 / (float)size ) * aspectRatio * 2.0f - aspectRatio;
		float posY = -1.0f;
		float scaleX = 1 / float(size * 1.2) * aspectRatio * 2.0f;
		float scaleY = (1 / (float)maxValue) * 4.0 * a;
		Hazel::Renderer2D::DrawQuad({ posX, posY }, { scaleX, scaleY }, color);
	}
	Hazel::Window& window = Hazel::Application::Get().GetWindow();
	window.OnUpdate();
}

void Sort::Swap(int a, int b)
{
	arrColor[a] = 2;
	arrColor[b] = 2;
	DrawArray();
	int tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
	arrColor[a] = 0;
	arrColor[b] = 0;
	DrawArray();
}

void Sort::InsertionSort()
{
	DrawArray();
	for (int i = 1; i < size; i++)
	{
		for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--)
		{
			Swap(j, j - 1);
		}
	}
}

void Sort::SelectionSort()
{
	int min;
	for (int i = 0; i < size-1; i++)
	{
		min = i;
		arrColor[i] = 1;
		for (int j = i+1; j < size; j++)
		{
			arrColor[j] = 1;
			DrawArray();
			if (arr[j] < arr[min])
			{
				min = j;
			}
			arrColor[j] = 0;
		}
		Swap(min, i);
	}
}

void Sort::BubbleSort()
{
	DrawArray();
	for (int i = 0; i < size; i++)
	{
		for (int j = size-1; j > i; j--)
		{
			if (arr[j] < arr[j-1])
			{
				Swap(j-1, j);
			}
			arrColor[j] = 0;
		}
	}
}

void Sort::MergeSort()
{
	MergeSort(0, size - 1);
}

void Sort::MergeSort( int p, int r)
{
	DrawArray();
	if (p < r)
	{
		int q = (p + r) / 2;
		arrColor[q] = 1;
		MergeSort( p, q);
		MergeSort( q+1, r);
		Merge( p, q, r);
	}
}

void Sort::Merge(int p, int q, int r)
{
	int it = p;
	int i = p;
	int j = q+1;
	while (i <= q && j <= r)
	{
		arrMerge[it] = arr[i] < arr[j] ? arr[i] : arr[j];
		if (arr[i] < arr[j])
			i++;
		else
			j++;
		it++;
	}
	if(i<=q)
		for (; i <= q; i++)
		{
			arrMerge[it] = arr[i];
			it++;
		}
	else 
		for (; j <= r; j++)
		{
			arrMerge[it] = arr[j];
			it++;
		}
	for (int i = p; i <= r; i++)
	{
		arr[i] = arrMerge[i];
		if (i > p && i < r)
		{
			arrColor[i] = 2;
		}
		DrawArray();
	}
}

void Sort::QuickSort()
{
	QuickSort(0, size - 1);
}

void Sort::QuickSort(int l, int r)
{
	DrawArray();
	if (l < r)
	{
		int pivot = Partition(l, r);
		QuickSort(l, pivot - 1);
		QuickSort(pivot + 1, r);
	}
}

int Sort::Partition(int l, int r)
{
	int left = l;
	int right = r - 1;
	int pivot = arr[r];
	arrColor[r] = 1;
	while (true) {
		while (left <= right && arr[left] < pivot) left++;
		while (right >= left && arr[right] > pivot) right--;
		if (left >= right) break;
		Swap(left, right);
		left++;
		right--;
	}
	Swap(left, r);
	arrColor[left] = 1;

	DrawArray();

	return left;
}

void Sort::HeapSort()
{
	for (int i = (size - 1) / 2; i >= 0; i--)
	{
		MaxHeap(i, size-1);
	}
	for (int j = size-1; j > 0; j--)
	{
		MaxHeap(0, j);
		Swap(0, j);
	}
}

void Sort::MaxHeap(int index, int n)
{
	arrColor[index] = 1;
	int l = index * 2 + 1;
	int r = index * 2 + 2;
	arrColor[l] = 2;
	arrColor[r] = 2;
	DrawArray();
	int largest;
	if (l <= n && arr[l] > arr[index])
		largest = l;
	else largest = index;
	if (r <= n && arr[r] > arr[largest])
		largest = r;
	arrColor[l] = 0;
	arrColor[r] = 0;
	arrColor[largest] = 1;
	DrawArray();
	arrColor[largest] = 0;
	arrColor[index] = 0;
	if (largest != index)
	{
		int tmp = arr[largest];
		arr[largest] = arr[index];
		arr[index] = tmp;
		MaxHeap(largest, n);
	}
}


