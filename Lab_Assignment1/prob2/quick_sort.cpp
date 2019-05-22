/*quick sort algorithm */ 

//Read Quick Sort Algorithm from wikipedia
/*
The code is close but it has some errors so it is not doing 
what it is supposed to do. Read the Quick Sort Algorithm 
and debug the code to print the correct output.

Also write the code for reading the numbers from the file "input.txt" 
provided in the folder "prob2" 
NOTE:- DO NOT hardcode the size of the file . Create a constant variable 
max_length = 200, which will be the maximum size of the file.
//---------------------------------------------------------------
NOTE: DO NOT ADD ANY COUT STATEMENTS IN THE FINAL SUBMISSION 
OF THE CODE. ALSO, DO NOT MODIFY THE SEQUENCE OF THE INPUT, OR 
CHANGE THE INPUT 
//---------------------------------------------------------------
*/

#include <cstdlib>
#include <iostream>
using namespace std; 

void print_array(int array[], int low, int hi) 
{ 
	cout<< "quick sort partition steps: "; 
	for (int j=low; j<=hi;j++) 
		cout <<" "<< array[j]; 
	cout << endl;
}//end of print_array 

int partition (int arr[], int low, int hi)
{
	int pivot = arr[hi];
	int i = low;
	
	for (int j = low; j<hi; j++)
	{
		if (arr[j] <= pivot)
		{
			swap(arr, i, j);
			i++;
		}
	}
	print_array(arr, low, hi);
	swap(arr, i, hi);
	return i;
}
	
void swap (int arr[], int i, int j)
{
	
	arr[i] = arr[j];
	arr[j] = arr[i];
	
	return;
}
		
void quick_sort(int arr[], int low, int high) 
{ 
	int pivot
	
	if (low < hi)
	{
		pivot = partition(arr, low, high);
		quick_sort(arr, low, pivot-1);
		quicksort(arr, pivot+1, high);
	}
	
	return;
}
	
	int main() 
	{ 
		int size;
		//DECLARE YOUR ARRAY HERE?:
		//For example: int array[5]= {5,4,3,2,1}; 
		/*
				INSERT YOUR CODE HERE - TO READ THE NUMBERS FROM "input.txt" and store it in an array
		*/
		print_array(array, size); 
		quick_sort(array, size); 
		return 0;
	}//end of main
