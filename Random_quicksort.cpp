#include <cstdlib>
#include <iostream>
#include <time.h>
using namespace std;

int comp =0;

int partition(int arr[], int low, int high)
{
	int pivot = arr[high];

	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{

		if (arr[j] <= pivot) {
			i++;
			swap(arr[i], arr[j]);
		}
		comp++;
	}
	swap(arr[i + 1], arr[high]);
	return (i + 1);
}


int partition_r(int arr[], int low, int high)
{

	srand(time(NULL));
	int random = low + rand() % (high - low);

	swap(arr[random], arr[high]);

	return partition(arr, low, high);
}


void quickSort(int arr[], int low, int high)
{
	if (low < high) {

		int pi = partition_r(arr, low, high);

		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}


void printArray(int arr[], int n)
{
	for (int i = 0; i < n; ++i)
		cout << arr[i] << " ";
	cout << "\n";
}

int main()
{

	int size,ext;
  begin:
  	comp=0;
	cout<<"Enter the size of array : ";
	cin>>size;
	int arr[size];
	cout<<"\n\n";
	for(int i=0;i<size;i++)
	{
		cout<<"Enter element "<<i+1<<" in an array : ";
		cin>>arr[i];
	}

    cout << "\n\nGiven array is :    ";
	printArray(arr, size);

	quickSort(arr, 0, size - 1);

	cout<<"\n\nSorted array is:   ";
	printArray(arr, size);
	cout<<"\nNo of comparisons are :  "<<comp;
	cout<<"\n\nPress 1 to start again / any other key to exit : ";
  	cin>>ext;
  	if(ext == 1)
     	goto begin;
	return 0;
}
