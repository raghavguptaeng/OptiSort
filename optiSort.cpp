#include <iostream>
#include <iostream>
#include <pthread.h>
#include <time.h>  
#define MAX 4000

// number of threads
#define THREAD_MAX 4
  
using namespace std;
  
// array of size MAX
int a[MAX];
int part = 0;

// merge function for merging two parts
void merge(int low, int mid, int high)
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
void merge_sort(int low, int high)
{
	// calculating mid point of array
	int mid = low + (high - low) / 2;
	if (low < high) {

		// calling first half
		merge_sort(low, mid);

		// calling second half
		merge_sort(mid + 1, high);

		// merging the two halves
		merge(low, mid, high);
	}
}

// thread function for multi-threading
void* merge_sort(void* arg)
{
	// which part out of 4 parts
	int thread_part = part++;

	// calculating low and high
	int low = thread_part * (MAX / 4);
	int high = (thread_part + 1) * (MAX / 4) - 1;

	// evaluating mid point
	int mid = low + (high - low) / 2;
	if (low < high) {
		merge_sort(low, mid);
		merge_sort(mid + 1, high);
		merge(low, mid, high);
	}
}

// Driver Code
int startMerge()
{
    

	// t1 and t2 for calculating time for
	// merge sort
	clock_t t1, t2;

	t1 = clock();
	pthread_t threads[THREAD_MAX];

	// creating 4 threads
	for (int i = 0; i < THREAD_MAX; i++)
		pthread_create(&threads[i], NULL, merge_sort,
										(void*)NULL);

	// joining all 4 threads
	for (int i = 0; i < 4; i++)
		pthread_join(threads[i], NULL);

	// merging the final 4 parts
	merge(0, (MAX / 2 - 1) / 2, MAX / 2 - 1);
	merge(MAX / 2, MAX/2 + (MAX-1-MAX/2)/2, MAX - 1);
	merge(0, (MAX - 1)/2, MAX - 1);

	t2 = clock();

	// displaying sorted array
	cout << "Sorted array: ";
	for (int i = 0; i < MAX; i++)
		cout << a[i] << " ";

	// time taken by merge sort in seconds
	cout << "Time taken: " << (t2 - t1)<< endl;

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
//------------------- MERGE SORT SINGLE THREAD ---------------  
void mergeSingle(int arr[], int l, int m, int r)
{
	int n1 = m - l + 1;
	int n2 = r - m;

	// Create temp arrays
	int L[n1], R[n2];

	// Copy data to temp arrays L[] and R[]
	for (int i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (int j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	// Merge the temp arrays back into arr[l..r]

	// Initial index of first subarray
	int i = 0;

	// Initial index of second subarray
	int j = 0;

	// Initial index of merged subarray
	int k = l;

	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	// Copy the remaining elements of
	// L[], if there are any
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	// Copy the remaining elements of
	// R[], if there are any
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

// l is for left index and r is
// right index of the sub-array
// of arr to be sorted */
void mergeSortSingle(int arr[],int l,int r){
	if(l>=r){
		return;//returns recursively
	}
	int m =l+ (r-l)/2;
	mergeSortSingle(arr,l,m);
	mergeSortSingle(arr,m+1,r);
	mergeSingle(arr,l,m,r);
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
void Optimize(bool seeMulti = false){
    int arr[MAX],a1[MAX],a2[MAX],a3[MAX],a4[MAX];
    for(int i=0 ; i<MAX ; ++i){
        arr[i] = a[i];
        a1[i] = a[i];
        a2[i] = a[i];
        a3[i] = a[i];
        a4[i] = a[i];
    }
    int n=MAX;
    if(true){
        startMerge();
    }
    int sortfinderCount = 0;
    for(int i=0 ; i<n-1 ; ++i){
        if(arr[i]<arr[i+1]){
            sortfinderCount++;
        }
        else{
            break;
        }
    }
    clock_t t1, t2 ,t3,t4,t5,t6,t7,t8,t9,t10;
    cout<<endl;
        t1 = clock();
        insertionSort(a1,n);
        cout<<"Insertion Sort "<<endl;
        t2 = clock();
        cout<<"Time taken : "<<(t2-t1);
    cout<<endl;
        t3 = clock();
        bubbleSort(a2,n);
        cout<<"Bubble Sort "<<endl;
        t4 = clock();
        cout<<"Time taken : "<<(t4-t3);
    cout<<endl;
        t5 = clock();
        selectionSort(a3,n);
        cout<<"Selection Sort "<<endl;
        t6 = clock();
        cout<<"Time taken : "<<(t6-t5);
    cout<<endl;
        t7 = clock();
        mergeSortSingle(a4,0,n);
        cout<<"Merge Sort "<<endl;
        t8 = clock();
        cout<<"Time taken : "<<(t8-t7);
    cout<<endl;
    //----------------------------------------
    t9 = clock();
    if(n-sortfinderCount<5 && n<10){
        insertionSort(arr,n);
        cout<<"Insertion Sort ";
    }
    else if(n-sortfinderCount<5 && n>=10){
        bubbleSort(arr,n);
        cout<<"Bubble Sort ";
    }
    else if(n<10){
        selectionSort(arr,n);
        cout<<"Selection Sort ";
    }
    else{
        mergeSortSingle(arr,0,n);
        cout<<"Merge Sort ";
    }
    t10 = clock();
    cout<<"time Taken for Opti Sort: "<<t10-t9;
    /*
    for(int i=0 ; i<n ; ++i){
        cout<<arr[i]<<" ";
    }*/
}
int main(){
	for (int i = 0; i < MAX; i++)
        a[i] = rand()%4000;
    Optimize();
}
