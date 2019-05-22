/* Strict Requirement --- Valid data values must be either zero or greater - 
                          no negative numbers allowed. */

/*
Concepts: Sorting and swapping values in a static array. Using file I/O
1. In the main function, read the numbers from the file "input.txt" and insert 
   the elements into the array. The terminating "character" for the data in the array 
   is -1.
2. Write a member function that returns the number of array members that have valid data.
3. Write a search function - the function should look for a number the user 
   gives and if it exists - DELETE it from the array. NOTE: This will require adjusting 
   the positions of the remaining values in the array accordingly so that data is still 
   stored contiguously and terminated with a -1.
4. You will be given a search.txt file (as found in this folder) of values we plan to 
   search your array for.

HINTS: The search function would benefit from helper functions to make your code more
readable (they should be private member functions). 
       A "value" may appear more than once in the array in *ANY* position. 
       A value may not appear in your array at all.
*/


#include <iostream>
using namespace std;

//Defines the Max Array size- DO NOT change this value.
#definte MAX_ARRAY_SIZE 201

//A Searchable Array Class
class S_Array 
{
public:

    S_Array ();
    //Default Constructor
    
    int number_of_data_points();
    //PreCondition: Initialized data_array.
    //PostCondition: Returns the number of data points in the array.
    //WRITTEN BY THE YOU!!!

	int search_and_remove(int value);
	//PreCondition: Initialized data_array and a valid "value" (i.e. zero or a positive
	//              Number.
	//PostCondition: Any occurrences of "value" have been removed from data_array. The 
	//               return value indicates how many times "value" was found in data_array.
    //WRITTEN BY THE YOU!!!
      
private:

	//INSERT ANY HELPER FUNCTIONS YOU WANT HERE!!
	
	int next;
	int data_array[MAX_ARRAY_SIZE];
};

//Default Constructor
S_Array::S_Array()
{
	next = 0;               //New array, next data insertion point is at the beginning.
	data_array[next] = -1;  //Used to indicate that there is no valid data in the array yet.
}

//PreCondition: Initialized data_array.
//PostCondition: Returns the number of data points in the array.
//WRITTEN BY THE YOU!!!
int S_Array::number_of_data_points()
{
    //WRITTEN BY THE YOU!!!
      
}

//PreCondition: Initialized data_array and a valid "value" (i.e. zero or a positive
//              Number.
//PostCondition: Any occurrences of "value" have been removed from data_array. The 
//               return value indicates how many times "value" was found in data_array.
//WRITTEN BY THE YOU!!!
int S_Array::search_and_remove(int value)
{
    //WRITTEN BY THE YOU!!!
      

}

}
void main()
{
	S_Array my_array;

	// Here is pseudocode for your main():
	// 1) open the file input.txt
	// 2) Read the numbers in sequentially from the input.txt file and store them in
	//    my_array.
	// 3) use number_of_data_points to tell the user how many data points were in the file.
	// 4) Search for the value(s) listed in search.txt and tell the user how many times 
	//    each of these values occurred using the format:
	//    >Search Value ?? occurred ?? times.
	// 5) End the program when you are done searching for values.
	
	
	// INSERT YOUR CODE HERE
	

}



