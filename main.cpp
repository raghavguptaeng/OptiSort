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

