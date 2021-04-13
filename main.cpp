#include <iostream>
#include <iostream>
#include <pthread.h>
#include <time.h>  
// number of threads
#define THREAD_MAX 4
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
void merge(int low, int mid, int high , int a[] , int n)
{
    int* left = new int[mid - low + 1];
    int* right = new int[high - mid];
  
    // n1 is size of left part and n2 is size
    // of right part
    int n1 = mid - low + 1, n2 = high - mid, i, j;
  
    // storing values in left part
    for (i = 0; i < n1; i++)
        left[i] = a[i + low];
  
    // storing values in right part
    for (i = 0; i < n2; i++)
        right[i] = a[i + mid + 1];
  
    int k = low;
    i = j = 0;
  
    // merge left and right in ascending order
    while (i < n1 && j < n2) {
        if (left[i] <= right[j])
            a[k++] = left[i++];
        else
            a[k++] = right[j++];
    }
  
    // insert remaining values from left
    while (i < n1) {
        a[k++] = left[i++];
    }
  
    // insert remaining values from right
    while (j < n2) {
        a[k++] = right[j++];
    }
}  
// merge sort function
void merge_sort(int low, int high,int arr[] , int n)
{
    // calculating mid point of array
    int mid = low + (high - low) / 2;
    if (low < high) {

        merge_sort(low, mid,arr,n);
        merge_sort(mid + 1, high,arr,n);
        merge(low, mid, high,arr,n);
    }
}
void* merge_sort(int arr[] , int n,void* arg)
{
    // which part out of 4 parts
    int thread_part = part++;
  
    // calculating low and high
    int low = thread_part * (MAX / 4);
    int high = (thread_part + 1) * (MAX / 4) - 1;
  
    // evaluating mid point
    int mid = low + (high - low) / 2;
    if (low < high) {
        merge_sort(low, mid,arr,n);
        merge_sort(mid + 1, high,arr,n);
        merge(low, mid, high,arr,n);
    }
}
void mergeSort(int arr[] , int n){
    pthread_t threads[THREAD_MAX];
  
    // creating 4 threads
    for (int i = 0; i < THREAD_MAX; i++)
        pthread_create(&threads[i], NULL, merge_sort(arr,n)  ,
                                        (void*)NULL);
  
    // joining all 4 threads
    for (int i = 0; i < 4; i++)
        pthread_join(threads[i], NULL);
  
    // merging the final 4 parts
    merge(0, (MAX / 2 - 1) / 2, MAX / 2 - 1);
    merge(MAX / 2, MAX/2 + (MAX-1-MAX/2)/2, MAX - 1);
    merge(0, (MAX - 1)/2, MAX - 1);
}
//----------------------QUICK SORT------------------------
int partition(int arr[],int low,int high)
{
    int pivot=arr[high];
    int i=low-1;
    for(int j=low;j<=high-1;j++)
    {
        if (arr[j]<pivot)
        {
            i++;
            int temp=arr[i];
            arr[i]=arr[j];
            arr[j]=temp;
        }
    }
    int temp=arr[i+1];
    arr[i+1]=arr[high];
    arr[high]=temp;
    return(i+1);
}
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
// Driver Ccodes to come here;
int main() {
	int n;
    cin>>n;
    int arr[n];
    for(int i=0 ; i<n ; ++i){
        cin>>arr[i];
    }
    mergeSort(arr,n);
    for(int i=0 ; i<n ; ++i){
        cout<<arr[i]<<" ";
    }
}