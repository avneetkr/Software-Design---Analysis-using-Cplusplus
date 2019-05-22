//Objective:to practice operator-overloading
/*
This programming module is to get you to practice Overloading operators
Questions: Write member functions for Class Complex to define/overload the
     basic arithmetic operations   '+','-'.'*','/','!=','==','>','<' 
           Also, create the "print_magnitude()" and "calculate_magnitude()" function.


*/

#include <iostream>
using namespace std;

class Complex
{
public:
	Complex(float=1.0,float=1.0);
	void set_real_and_imag (float, float);
	void print_complex();
	void print_magnitude();  //Print the Magnitude of the Complex number.
/*

WRITE MISSING FUNCTION DECLARATIONS HERE

*/
	friend ostream &operator<<(ostream &, Complex &);
	friend istream &operator>>(istream &, Complex &);
  // CAN You OVERLOAD AN OPERATOR USING "friend" keyword ????

private:
	float real;       //Real part
	float imaginary;  //Imaginary part
	float calculate_magnitude();   //Returns the magnitude of the Complex number.

};

/*

WRITE FUNCTION DEFINITIONS HERE



*/




/*--------------------------------------------------------*/

Complex::Complex(float m, float n)
{
	set_real_and_imag(m,n);
}

/*--------------------------------------------------------*/

void Complex::set_real_and_imag(float x, float y)
{
	
	real = x;
	imaginary = y;

}

/*--------------------------------------------------------*/

void Complex::print_complex()
{
	cout<<real<<" + j"<<imaginary<<endl;
}

/*--------------------------------------------------------*/

ostream &operator<<(ostream &output, Complex &object)
{
	output<<object.real<<" + j"<<object.imaginary<<endl;
	return output;
}

/*--------------------------------------------------------*/

istream &operator>>(istream &input, Complex &object)
{
	cout<<"Enter real, imaginary:"<<endl;
	input>>object.real;
	input>>object.imaginary;
	return input;
}



/*--------------------------------------------------------*/

int main()
{
	Imaginary x(3,4),y(3,4),z1,z2,z3,z4;
	cout<<"x=";
	x.print_complex();
	x.print_magnitude();
	cout<<"y=";
	y.print_fraction();
	y.print_magnitude();
	
	// Rational Number  k & l are of Class type Rational
	Imaginary k(1,1),l(1,1),z6,z7,z8,z9,z10;
	cin>>k>>l; // Input two Complex numbers k and l  , where k = 3 + j4 and l = 4 + j5
	if(k==l) // You need to define '==' operation for this line to work
	{cout<<"These 2 complex numbers are equal."<<endl;}
	if(k!=l) // You need to define '!=' operation for this line to work
	{cout<<"These 2 complex numbers are not equal."<<endl;}
    if(k>l) // You need to define '>' operation for this line to work
	{cout<<"k is bigger than l."<<endl;}
	if(k<l) // You need to define '<' operation for this line to work
	{cout<<"k is smaller than l."<<endl;}
	z6=k+l; // You need to define '+' operation for this line to work
	z7=k-l; // You need to define '-' operation for this line to work
	z8=k*l; // You need to define '*' operation for this line to work
	z9=k/l; // You need to define '=' operation for this line to work
	
	cout<<"z6="<<z6<<"z7="<<z7<<"z8="<<z8<<"z9="<<z9;
	cout<<"k="<<k<<"l="<<l;

	return(0);
}

