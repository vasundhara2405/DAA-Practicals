#include <iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
int count=0,count1=0;
void max_heapify(int a[], int i, int n)
{    int j, temp;
    temp = a[i];
    j = 2*i;
    while (j <= n)
    {
        count++;
        if (j < n && a[j+1] > a[j])
            j = j+1;

        if (temp > a[j])
            break;

        else if (temp <= a[j])
        {
            a[j/2] = a[j];
            j = 2*j;
        }
    }
    a[j/2] = temp;
    return;
}

void heapsort(int a[], int n)
{
    int i, temp;
    for (i = n; i >= 2; i--)
    {
        temp = a[i];
        a[i] = a[1];
        a[1] = temp;
        max_heapify(a, 1, i - 1);
    }
    cout<<"\nNo of comparisons="<<count<<endl;
}

void min_heapify(int a[],int i,int n)
{
    int j, temp;
    temp = a[i];
    j = 2 * i;
    while (j <= n)
    {
        count1++;
        if (j < n && a[j+1] < a[j])
            j = j + 1;

        if (temp < a[j])
            break;

        else if (temp >= a[j])
        {
            a[j/2] = a[j];
            j = 2 * j;
        }
    }
    a[j/2] = temp;
    return;
}

void build_minheap(int a[], int n)
{
    int i;
    for(i = n/2; i >= 1; i--)
    {
        min_heapify(a,i,n);
    }
}

void heapsort1(int a[], int n)
{
    int i, temp;
    for (i = n; i >= 2; i--)
    {
        temp = a[i];
        a[i] = a[1];
        a[1] = temp;
        min_heapify(a, 1, i - 1);
    }
    cout<<"\nNo of comparisons="<<count1<<endl;
}

void build_maxheap(int a[], int n)
{
    int i;
    for(i = n/2; i >= 1; i--)
    {
        max_heapify(a, i, n);
    }
}

int main()
{
    system("cls");
    int n, i, x, choice;
    char ch;
    do
    {
        cout<<"enter no of elements of array\n";
        cin>>n;

        int a[20];
        for (i = 1; i <= n; i++)
        {
            cout<<"enter element"<<(i)<<endl;
            cin>>a[i];
        }

        cout<<"1. Build max heap "<<"2. Build min heap"<<endl;
        cin>>choice;
        switch(choice)
        {
            case 1: build_maxheap(a,n);
                        cout<<"MAXHEAP\n";
                        for (i = 1; i <= n; i++)
                        {
                            cout<<a[i]<<endl;
                        }
                        heapsort(a, n);
                        cout<<"SORTED HEAP\n";
                        for (i = n; i >= 1; i--)
                        {
                            cout<<a[i]<<endl;
                        }
                        break;

            case 2: build_minheap(a,n);
                        cout<<"MINHEAP\n";
                        for (i = 1; i <= n; i++)
                        {
                            cout<<a[i]<<endl;
                        }
                        heapsort1(a, n);
                        cout<<"SORTED HEAP\n";
                        for (i = n; i >= 1; i--)
                        {
                            cout<<a[i]<<endl;
                        }
                        break;
        }
        cout<<"\n do you want to continue: ";
        cin>>ch;
    }while(ch=='y'||ch=='Y');
    return 0;
}
