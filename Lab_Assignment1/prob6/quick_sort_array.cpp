/* Quick sort an array of objects using the quick sort algorithm from prob2
   If you want more information about the quick sort algorithm, checkout
   wikipedia. */

/*
   Below I've created the definition of a class called CoordinatePairs
   based on the one we saw in lecture. Use your quicksort algorithm to
   sort an array of these objects in order of increasing manhattan distance.
   I've provided the basic framework for the class code you need (including
   a function that calculates the manhattan distance). Feel free to add
   new member functions, but you MUST maintain the ADT definition of the
   class as we discussed in class.

   I've provided you pseudocode for the main function as well, but don't forget
   to copy over your quicksort code from part 2 to get you started. You'll need to
   read in the CoordinatePairs from the file "input.txt." Do NOT hardcode the size of
   the file. Use the constant from the define macro to limite the size of your array
   (100), which will be the maximum size of the file.

   HINTS: Use the I/O code from prob2/prob5 to get yourself started.
          When adapting your sorting algorithm, your trying to swap the type int for
             CoordinatePairs, but pay attention to the comparison points as you are
             comparing the Manhattan Distance.

//---------------------------------------------------------------
NOTE: DO NOT INCLUDE ANY ADDITIONAL COUT STATEMENTS IN YOU FINAL
SUBMISSION. ONLY OUTPUT THE FINAL SORTED ARRAY AS I HAVE INCLUDED
IN MAIN.
//---------------------------------------------------------------
*/

#include <cstdlib>  //Includes abs()
#include <iostream>
#include <fstream>
using namespace std;

#define MAX_ARRAY_LEN 100

//A class for integer coordinate pairs in the (x,y) space
class CoordinatePairs
{
public:
	CoordinatePairs();
	//Default Constructor
	//Initializes (x1,y1) = (0,0) and (x2,y2) = (0,0)

	CoordinatePairs(int in_x1, int in_y1, int in_x2, int in_y2);
	//Constructor initializing all member values to input parameter values in
	//the order x1, y1, x2, y2.

	void set_pair1(int in_x1, int in_y1);
	//Pre-condition:  Properly initialized CoordinatePair object.
	//Post-condition: The values of (x1, y1) will be changed to the input parameter
	//                values of this function.

	void set_pair2(int in_x2, int in_y2);
	//Pre-condition:  Properly initialized CoordinatePair object.
	//Post-condition: The values of (x2, y2) will be changed to the input parameter
	//                values of this function.

	void get_pair1(int &out_x1, int &out_y1);
	//Pre-condition:  Properly initialized CoordinatePair object.
	//Post-condition: Call by Reference.
	//                Let's the user read the values of (x1, y1) out into (out_x1, out_y1).

	void get_pair2(int &out_x2, int &out_y2);
	//Pre-condition:  Properly initialized CoordinatePair object.
	//Post-condition: Call by Reference.
	//                Let's the user read the values of (x2, y2) out into (out_x2, out_y2).

	int calculate_manhattan_distance();
	//Pre-condition:  Properly initialized CoordinatePair object.
	//Post-condition: Returns the Manhattan distance between a pair of (x,y) coordinates,
	//                equal to |x1-x2| + |y1-y2|. Google for more information.


    friend ostream &operator<<(ostream &outs, CoordinatePairs &pair);
    //Overloads the << operator so it can be used to output values of type CoordinatePairs
    //Output Format: x1 y1 x2 y2
    //Precondition: If outs is a file output stream,
    //then outs has already been connected to a file.

	friend istream &operator>>(istream &ins, CoordinatePairs &pair);
	//Overloads the >> operator ao it can be used to input values of type CoordinatePairs
	//Format for input is x1 y1 x2 y2
	//Precondition: If ins is a file input stream, then ins has already been
	//connected to a file



private:


	int x1;  //Coordinate pair 1: x value
	int y1;  //Coordinate pair 1: y value
	int x2;  //Coordinate pair 2: x value
	int y2;  //Coordinate pair 2: y value

};

//////////////////CoordinatePairs Class Implementation ///////////////////////////

//Default Constructor
//Initializes (x1,y1) = (0,0) and (x2,y2) = (0,0)
CoordinatePairs::CoordinatePairs()
{
	x1 = 0;
	y1 = 0;
	x2 = 0;
	y2 = 0;
}


//Constructor initializing all member values to input parameter values in
//the order x1, y1, x2, y2.
CoordinatePairs::CoordinatePairs(int in_x1, int in_y1, int in_x2, int in_y2)
{
	x1 = in_x1;
	y1 = in_y1;
	x2 = in_x2;
	y2 = in_y2;
}

//Pre-condition:  Properly initialized CoordinatePair object.
//Post-condition: The values of (x1, y1) will be changed to the input parameter
//                values of this function.
void CoordinatePairs::set_pair1(int in_x1, int in_y1)
{
	x1 = in_x1;
	y1 = in_y1;
	return;
}

//Pre-condition:  Properly initialized CoordinatePair object.
//Post-condition: The values of (x2, y2) will be changed to the input parameter
//                values of this function.
void CoordinatePairs::set_pair2(int in_x2, int in_y2)
{
	x2 = in_x2;
	y2 = in_y2;
	return;
}


//Pre-condition:  Properly initialized CoordinatePair object.
//Post-condition: Call by Reference.
//                Let's the user read the values of (x1, y1) out into (out_x1, out_y1).
void CoordinatePairs::get_pair1(int &out_x1, int &out_y1)
{
	out_x1 = x1;
	out_y1 = y1;
	return;
}


//Pre-condition:  Properly initialized CoordinatePair object.
//Post-condition: Call by Reference.
//                Let's the user read the values of (x2, y2) out into (out_x2, out_y2).
void CoordinatePairs::get_pair2(int &out_x2, int &out_y2)
{
	out_x2 = x2;
	out_y2 = y2;
	return;
}


//Pre-condition:  Properly initialized CoordinatePair object.
//Post-condition: Returns the Manhattan distance between a pair of (x,y) coordinates,
//                equal to |x1-x2| + |y1-y2|. Google for more information.
int CoordinatePairs::calculate_manhattan_distance()
{
	return abs(x1-x2)+ abs(y1-y2); //abs() from cstdlib.
}


//Overloads the << operator so it can be used to output values of type CoordinatePairs
    //Output Format: x1 y1 x2 y2
    //Precondition: If outs is a file output stream,
    //then outs has already been connected to a file.
ostream &operator<<(ostream &outs, CoordinatePairs &pair)
{
	outs<<pair.x1<<" "<<pair.y1<<" "<<pair.x2<<" "<<pair.y2;

	return outs;

}


//Overloads the >> operator ao it can be used to input values of type CoordinatePairs
	//Format for input is x1 y1 x2 y2
	//Precondition: If ins is a file input stream, then ins has already been
	//connected to a file
istream &operator>>(istream &ins, CoordinatePairs &pair)
{
	ins>>pair.x1>>pair.y1>>pair.x2>>pair.y2;

	return ins;

}


///TO GET YOU STARTED ON YOUR QUICK SORT ALGORITHM FOR THE COORDINATEPAIRS CLASS:////


//Recall Prob2:
//You might want a print_array function to help you with debugging.
//NOTE: ONLY USE FOR DEBUGGING; DO NOT INCLUDE IN YOUR FINAL SUBMISSION.
/*void print_array(CoordinatePairs array[], int low, int hi)
{
	cout<<"quick sort partition steps: ";
	for (int j=low; j<=hi;j++) {
		//print Manhattan Distance for array[j];
		cout<<array[j].calculate_manhattan_distance()<<" ";
	}

	cout<<endl;
	return;

}//end of print_array
*/


	void swap (CoordinatePairs arr[], int i, int j)
{
    CoordinatePairs temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;

        return;
}

int partition (CoordinatePairs arr[], int low, int hi)
{
        CoordinatePairs pivot = arr[hi];
        int i = low;

        for (int j = low; j<hi; j++)
        {
                if (arr[j].calculate_manhattan_distance() <= pivot.calculate_manhattan_distance())
                {
                       swap(arr, i, j);
                        i++;
                }
        }
        //print_array(arr, low, hi);
        swap(arr, i, hi);
        return i;
}



void quick_sort(CoordinatePairs arr[], int low, int hi)
{
        int pivot = 0;

        if (low < hi)
        {
                pivot = partition(arr, low, hi);
                quick_sort(arr, low, pivot-1);
                quick_sort(arr, pivot+1, hi);
        }

        return;
}


int main()
{
	int num_pairs = 0; //Number of objects initialized in the array

	//Declare your CoordinatePairs Array here.
	CoordinatePairs array[MAX_ARRAY_LEN];
	/*
			INSERT YOUR CODE HERE - TO READ THE NUMBERS FROM "input.txt" and store
			it in "array".  Count how many CoordinatePairs objects you initialized
			as you read in the values and store that value in num_pairs
	*/
	ifstream in_stream;
    in_stream.open("input.txt");

    if(in_stream.fail()){ //if input.txt fails to open
    	cout<<" Input file opening failed."<<endl;
        exit(1);
     }

    while((!in_stream.eof()) && num_pairs < MAX_ARRAY_LEN){
        in_stream>>array[num_pairs];
       if(!in_stream.eof()) //to prevent from reading one extra int
     	num_pairs++;

     }

	quick_sort(array, 0, num_pairs-1);
	//print_array(array, 0, num_pairs-1);

	for (int i=0; i<num_pairs; i++)
	{
		//		Insert code to print out the object values in the following format:
		//		>x1 y1 x2 y2 manhattan_distance			[Values for array[0]]
		//		>x1 y1 x2 y2 manhattan_distance			[Values for array[1]]
		cout<<array[i]<<" "<<array[i].calculate_manhattan_distance()<<endl;

	}
	return 0;
}//end of main
