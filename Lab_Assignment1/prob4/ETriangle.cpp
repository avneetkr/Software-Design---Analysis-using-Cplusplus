
/*
Qns PART 1. -- Calculate the height of the ETriangle for its constructor member functions
			--   and mutator function set_side_length().
			-- Add a Member function to the "ETriangle" Class called get_surface_area()
			
----------

Qns PART 2  -- Create a new derived class called  "ETriangularPrism" that 
			--	 includes one additional member variable, "length".
			-- Write a member function to overload get_surface_area()
			-- Write a member function called get_volume() 
			-- Write a constructor to initialize the ETriangularPrism's private
			--   member variable, "length", as well as its inherited member variables, 
			--   "side_length" and "height."

----------

Qns PART 3  -- Create a new derived class called "SquarePyramid" and write member 
			--   functions to overload get_volume()  and get_surface_area() .
			-- Write a constructor to initialize the SquarePyramid's private
			--   member variable "elevation" (from the base of the pyramid to the apex), 
			--   which can be used to initialize the inherited private member variables, 
			--   “side_length” and “height”.
			-- Write a SquarePyramid constructor that takes the triangle's side length as 
			--   input and uses it to initialize all the object's member variables.
									
						
NOTE:-  
You should use the version of main provided here to test and verify these classes and 
for in-lab marking only. Your electronic submission will require you to use a different 
“main” function. You should rewrite the main function to ask the user to do the following:
>Enter side length of equilateral triangle:
>Enter length of triangular prism:

Our auto-checker will then expect the following output. The output should be written in
8 lines. Only print the Numbers and NOTHING ELSE:
		First line :-   Contains the height of the ETriangle object
		Second Line:-   Contains the perimeter of the ETriangle object
		Third Line :-   Contains the "surface" area (i.e. Area) of the ETriangle object
		Fourth Line :-  Contains the surface area of the ETrianglePrism object
		Fifth Line :-   Contains the volume of the ETrianglePrism object
		Sixth Line :-   Contains the surface area of the SquarePyramid object
		Seventh Line :- Contains the volume of the SquarePyramid object
		Eighth Line:-   Contains the elevation of the SquarePyramid object 

*/

#include <iostream>    // using IO functions
using namespace std;

#define sqr_two  1.4142 // Please use this value of the square root of two in 
						  // in your calculations.

#define sqr_three  1.7321 // Please use this value of the square root of 3 in 
						  // in your calculations.

class ETriangle //EQUILATERAL TRIANGLE CLASS
{
public:
   ETriangle(double s_length);
   //Precondition: User provides side_length.
   //Postcondition: Both side_length and height member variables are initialized.

   ETriangle();
   //Default Constructor: initializes the side_length to 1 and the height accordingly.

   double get_side_length(); 
   //Member Function: Accessor
   //Precondition: Object initialized.
   //Postcondition: Returns the side_length of the equilateral triangle.
     
   double get_height();   
   //Member Function: Accessor
   //Precondition: Object initialized.
   //Postcondition: Returns the height of the equilateral triangle.

   double get_perimeter();   
   //Member Function: Accessor
   //Precondition: Object initialized.
   //Postcondition: Returns the perimeter of the equilateral triangle.

   void set_side_length(double s_length);   
   //Member Function: Mutator
   //Precondition: Object initialized.
   //Postcondition: Updates the side_length AND height according to the user input.


private:
   double height;      // Data member Variable
   double side_length; // Data member variable
 
};   // need to end the class declaration with a semi-colon
 

/////////////// ETriangle Member Function Definitions /////////////

//Precondition: User provides side_length.
//Postcondition: Both side_length and height member variables are initialized.
ETriangle::ETriangle(double s_length)
{
   	side_length = s_length;
   	height = ;  ///ADD THE MISSING CALCULATION HERE./////////
}

//Default Constructor: initializes the side_length to 1 and the height accordingly.
ETriangle::ETriangle()
{
   	side_length = 1;
   	height = ;  ///ADD THE MISSING CALCULATION HERE.////////
}

//Member Function: Accessor
//Precondition: Object initialized.
//Postcondition: Returns the side_length of the equilateral triangle.
double ETriangle::get_side_length() 
{
    return side_length;
}

//Member Function: Accessor
//Precondition: Object initialized.
//Postcondition: Returns the height of the equilateral triangle.
double ETriangle::get_height()   
{
    return height;
}

//Member Function: Accessor
//Precondition: Object initialized.
//Postcondition: Returns the perimeter of the equilateral triangle.
double ETriangle::get_perimeter()   
{
    return 3*side_length;
}

//Member Function: Mutator
//Precondition: Object initialized.
//Postcondition: Updates the side_length AND height according to the user input.
void ETriangle::set_side_length(double s_length);   
{
   	side_length = s_length;
   	height = ;  ///ADD THE MISSING CALCULATION HERE./////////
}

 

/////////////////////////////

/* Create a new class called ETriangularPrism  HERE   */

////////////////////////////



/////////////////////////////

/* Create a new class called SquarePyramid  HERE   */

////////////////////////////



// **Test** driver function- this is to get you started on testing your classes
// and to be used IN THE LAB for marking your assignment.
// This is NOT the format your final submission should use (SEE THE NOTE AT THE TOP OF 
// THE cpp file).

int main() {
   // Construct a ETriangle instance
   ETriangle t1(10.0);
   cout << " side length = " << t1.side_length() << endl;
   cout << " height = " << t1.get_height() << endl;
   cout << " perimeter = " << t1.get_perimeter() << endl;  

   // Create a new Object of Type Class ETriangularPrism and initialize it with 
   // side_length = 15 and length = 20
   // ETrianglePrism t2(15,10);
   //-------------------------------------------------
   // INSERT CODE HERE  TO CALCULATE THE PERIMETER OF THE TRIANGLE-----
   //---  Try t2.get_perimeter();    
   //---  Does it work ??? If yes, what perimeter value is calculated??
   //--------------------------------------------------

   // Create a new Object of Type Class SquarePyramid and initialize it with 
   // side_length = 25 
   // ETrianglePrism t3(15);
   //-------------------------------------------------
   // INSERT CODE HERE  TO CALCULATE THE PERIMETER OF THE TRIANGLE-----
   //---  Try t3.get_perimeter();    
   //---  Does it work ???
   // Report the Elevation of the pyramid here as well.
   //--------------------------------------------------


   //-------------------------------------------------
   // INSERT CODE HERE    
   // CALL THE MEMBER FUNCTIONS CREATED EARLIER to print the output of 
   // Surface area and volume of the triangle prism and square pyramid-----
   //--------------------------------------------------
	

   return 0;
}
