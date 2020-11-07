#include "hzpch.h"
#include "Sort.h"
#include <ctime>
#include <stdlib.h>
#include <Hazel/Renderer/Renderer2D.h>
#include "Hazel/Renderer/RenderCommand.h"
#include "Hazel/Core/Application.h"
#include "Hazel/Core/Window.h"

const int size = 200;
static int arr[size]{ 0 };
static int arrMerge[size];
static int arrColor[size]{0};

bool Sort::run = true;
int Sort::i = 0;
int Sort::j = 0;
int Sort::last = 0;
static float timesort = 0.0f;

void Sort::Init()
{
	srand(time(NULL));
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand() % 10 + 1;
	}
	i = 0;
	j = 1;
	last = 0;
	//SelectionSort();
}

void Sort::Draw()
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
		for (int i = 0; i < a; i++)
			Hazel::Renderer2D::DrawQuad({ x * (1 / (float)size) * 1280 / 720.0 * 1.90 - 1280 / 720.0 + 0.1, i * 1 / 50.0 * 1.95 - 0.95f }, { 1 / float(size * 1.2) * 1280 / 720.0 * 1.90, 1 / 50.0 * 1.95 }, color);
	}
	Hazel::Window& window = Hazel::Application::Get().GetWindow();
	window.OnUpdate();
}

void Sort::Run(Hazel::Timestep ts)
{
	SelectionSort(ts);
}

void Sort::InsertionSort(Hazel::Timestep ts)
{
	timesort += ts;
	HZ_CORE_TRACE("{0}", ts);
	if (i < size)
	{
		timesort = 0.0f;
		if (j > 0 && arr[j - 1] > last)
		{
			arr[j] = arr[j - 1];
			arr[j - 1] = last;
			j--;
		}
		else
		{
			i++;
			j = i;
			last = arr[i];
		}
	}
	Draw();
}

void Sort::InsertionSort()
{
	for (; i < size; i++)
	{
		int last = arr[i];
		for (j = i; j > 0&&arr[j-1]>last; j--)
		{
			arr[j] = arr[j - 1];
			arr[j - 1] = last;
		}
	}
}

void Sort::SelectionSort(Hazel::Timestep ts)
{
	timesort += ts;
	HZ_CORE_TRACE("{0}", ts);
	if (i < size-1)
	{
		timesort = 0.0f;
		if (arr[j] < arr[last])
		{
			last = j;
		}
		j++;
		if (j > size - 1)
		{
			int tmp = arr[i];
			arr[i] = arr[last];
			arr[last] = tmp;
			i++;
			j = i+1;
			last = i;
		}
	}
	Draw();
}

void Sort::SelectionSort()
{

}
void Sort::BubbleSort(Hazel::Timestep ts)
{
	timesort += ts;
	HZ_CORE_TRACE("{0}", ts);
	if (i>0)
	{
		timesort = 0.0f;
		if (arr[j] > arr[j+1])
		{
			last = arr[j];
			arr[j] = arr[j + 1];
			arr[j + 1] = last;
		}
		j++;
		if(j == i)
		{
			i--;
			j = 0;
			last = arr[j];
		}
	}
	Draw();
}

void Sort::BubbleSort()
{

}

void Sort::MergeSort( int p, int r)
{
	//arrColor[p] = 1;
	//arrColor[r] = 1;
	Draw();
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
		Draw();
	}
}

void Sort::Quick3(int l, int r)
{
	Draw();
	if (l < r)
	{
		std::pair<int, int> pivot = PartitionQuick3(l, r);
		arrColor[pivot.first] = 1;
		arrColor[pivot.second] = 1;
		Quick3(l, pivot.first-1);
		Quick3(pivot.second + 1, r);
	}
}

std::pair<int, int> Sort::PartitionQuick3(int l, int r)
{
	i = l;
	j = r - 1;
	arrColor[r] = 1;
	while (i <= j)
	{
		arrColor[i] = 2;
		arrColor[j] = 2;
		Draw();
		if (arr[i] >= arr[r] && arr[j] < arr[r])
		{
			int tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}
		arrColor[i] = 0;
		arrColor[j] = 0;
		if (arr[i] < arr[r])
			i++;
		if (arr[j] >= arr[r])
			j--;
	}

	int tmp = arr[r];
	arr[r] = arr[i];
	arr[i] = tmp;

	arrColor[r] = 0;
	arrColor[i] = 1;

	j = i+1;
	while (arr[i] == arr[j])
	{
		j++;
	}
	j--;

	Draw();
	
	return std::make_pair(i,j);
}

void Sort::QuickSort(int l, int r)
{
	Draw();
	if (l < r)
	{
		int pivot = Partition(l, r);
		QuickSort(l, pivot - 1);
		QuickSort(pivot + 1, r);
	}
}

int Sort::Partition(int l, int r)
{
	i = l;
	j = r - 1;
	arrColor[r] = 1;
	while (i <= j)
	{
		arrColor[i] = 2;
		arrColor[j] = 2;
		Draw();
		if (arr[i] >= arr[r] && arr[j] < arr[r])
		{
			int tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}
		arrColor[i] = 0;
		arrColor[j] = 0;
		if (arr[i] < arr[r])
			i++;
		if (arr[j] >= arr[r])
			j--;
	}

	int tmp = arr[r];
	arr[r] = arr[i];
	arr[i] = tmp;

	arrColor[r] = 0;
	arrColor[i] = 1;

	Draw();

	return i;
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
		int tmp = arr[j];
		arr[j] = arr[0];
		arr[0] = tmp;
	}
}

void Sort::MaxHeap(int index, int n)
{
	arrColor[index] = 1;
	int l = index * 2 + 1;
	int r = index * 2 + 2;
	arrColor[l] = 2;
	arrColor[r] = 2;
	Draw();
	int largest;
	if (l <= n && arr[l] > arr[index])
		largest = l;
	else largest = index;
	if (r <= n && arr[r] > arr[largest])
		largest = r;
	arrColor[l] = 0;
	arrColor[r] = 0;
	arrColor[largest] = 1;
	Draw();
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


