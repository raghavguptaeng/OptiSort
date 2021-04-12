#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	return 0;
}

//----------------------SELECTION SORT------------------------
void selectionSort(int arr[], int n) 
{ 
    int min_pos; 
  
    for (int i=0;i<n-1;i++) 
    { 
        min_pos=i; 
        for (int j=i+1;j<n;j++) 
        {
            if(arr[j]<arr[min_pos]) 
                min_pos=j;
        }
        int temp=arr[i];
        arr[i]=arr[min_pos];
        arr[min_pos]=temp;
    } 
} 


//----------------------BUBBLE SORT------------------------
void bubbleSort(int arr[], int n) 
{ 
    for (int i=0;i<n-1;i++) 
    {
        for (int j=0;j<n-1-i;j++) 
        {
            if(arr[j]>arr[j+1]) 
            {
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    } 
} 


//----------------------INSERTION SORT------------------------
void insertionSort(int arr[], int n) 
{ 
    int key,j;
    for(int i=1;i<n;i++)
    {
        key = arr[i];
        j=i-1;
        while(j>=0&&arr[j]>key)
        {
            arr[j+1]=arr[j];
            j=j-1;
        }
        arr[j+1]=key;
    } 
} 


//----------------------MERGE SORT------------------------
void merge(int arr[],int l,int m, int r)
{
    int n1=m-l+1;
    int n2=r-m;
    int L[n1],R[n2];
 
    for(int i=0;i<n1;i++)
        L[i]=arr[l+i];
    for(int j=0;j<n2;j++)
        R[j]=arr[m+1+j];
    int i = 0;
    int j = 0;
    int k = l;
    while(i<n1 && j<n2) {
        if(L[i]<=R[j]) {
            arr[k]=L[i];
            i++;
        }
        else {
            arr[k]=R[j];
            j++;
        }
        k++;
    }
    while(i<n1) {
        arr[k]=L[i];
        i++;
        k++;
    }
    while (j<n2) {
        arr[k]=R[j];
        j++;
        k++;
    }
}

void mergesort(int arr[],int l,int r)
{
    if(l<r)
    {
        int mid=(r+l)/2;
        mergesort(arr,l,mid);
        mergesort(arr,mid+1,r);
        merge(arr,l,mid,r);
    }
}

