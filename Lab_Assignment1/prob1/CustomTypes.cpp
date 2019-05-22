#include<cstdint>
#include<iostream>
using namespace std;

/*
Find the size of these user defined types (as well as the 
predefined types listed on the assignment handout).
*/

//19)
class UserDefinedType19 
{
public:
	char value;
	int max_length;
};

//20)
class UserDefinedType20 
{
public:
	char value;
	long partb;
	float fraction;
	double long_fraction;
};

//21)
class UserDefinedType21
{
private:
	char value;
	long partb;
	float fraction;
	double long_fraction;
};

//22)
struct UserDefinedType22
{
	char value;
	long partb;
	float fraction;
	double long_fraction;
	uint8_t value_2;
	uint16_t value3;
};

//23)
struct UserDefinedType23
{
	char value;
	long partb;
	float fraction;
	double long_fraction;
	uint8_t value_2;
	uint16_t value3;
	UserDefinedType22 other;
};

//24)
union UserDefinedType24
{
	char value;
	long partb;
	float fraction;
	double long_fraction;
	uint8_t value_2;
	uint16_t value3;
};

//25)
union UserDefinedType25
{
	char value;
	long partb;
	float fraction;
	double long_fraction;
	uint8_t value_2;
	uint16_t value3;
	UserDefinedType22 other;
};

//26) 
union UserDefinedType26
{
	UserDefinedType22 varA;
	UserDefinedType23 varB;
};
