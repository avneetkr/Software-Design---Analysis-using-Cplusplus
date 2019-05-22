/*
/* Title: stringobjects.h
/* Author(s): Lesley Shannon
/* Student Number: N/A
/* Related Files: stringobjects.cpp, program.cpp
/* Project: ENSC 251 Lab Assignment 2
/* Version: 1.0
/* Date of last Revision: September 27, 2015
/* Revision History: V1.0- File creation
/*                   V2.0- ?????
/*
/**************************************************************************************


//Objective: To dynamically create an object array, initialize it with a series of strings,
//           sort the strings alphabetically, and then be able to search for any of the
//           strings using a binary search algorithm implemented *recursively*.

/* Requirements for your class:
    1) This class must remain an ADT- you are not allowed to change any public function
       declarations.
    2) You can add new private member functions as helper functions.
    3) You are not allowed to add any new global variables to this file or new private
       member fields to your StringObjects class.
    4) You need to create the corresponding .cpp file, and ensure that these files will
       compile properly when used in compilation with multiple other file instances (that
       may or may not also include references to the StringObject class).
    5) You need to provide sufficient comments and well chosen variable names to demonstrate
       a clean and readable coding style.

*/
#ifndef STRINGOBJECT_H
#define STRINGOBJECT_H


#include <iostream>
#include <string>
using namespace std;


//A StringObject that includes a string and the number of characters.
class StringObject
{
public:
	StringObject();
	//Default Constructor used to create an empty StringObject object.
	//When there is no string stored in the array, the num_char should equal 0

	~StringObject();
	//Destructor for StringObject objects.

	void set_string(string& s);
	//PreCondition: Start with a StringObject (MUTATOR FUNCTION)
	//PostCondition: Stores the string "str" in the StringObject and update num_char.


	string* get_string();
	//PreCondition: Start with StringObject. (ACCESSOR FUNCTION)
	//PostCondition: Returns the string stored in the object without changing the object.

    int get_num_char();
	//PreCondition: Start with StringObject. (ACCESSOR FUNCTION)
	//PostCondition: Returns the number of characters in the string in that object.

    bool empty();
    //Checks to see if the object is currently storing a string or if it is empty.

    friend bool operator ==(StringObject, StringObject);
    //PreCondition: Two valid string objects.
    //PostCondition: Compares the strings stored in these objects and returns
    //               true if they are equal and false if they are not.

    friend bool operator <(StringObject, StringObject);
    //PreCondition: Two valid string objects.
    //PostCondition: Compares the strings stored in these objects and returns
    //               true if the first string comes *before* the second string
    //               alphabetically.

	friend bool operator >(StringObject, StringObject);
    //PreCondition: Two valid string objects.
    //PostCondition: Compares the strings stored in these objects and returns
    //               true if the first string comes *after* the second string
    //               alphabetically.

	friend ostream &operator<<(ostream &, StringObject &);
	//Sends the string stored in this string object to the stream *without* changing
	//the string object.

	friend istream &operator>>(istream &, StringObject &);
	//Reads in the value and stores it in the string portion of the string object and
	//then initializes the num_char based on its length.

private:
	string* str; // Value stored at the node
	int num_char; //Stores the length of the string (excluding the termination
	              //character '/0'
};

int search_sorted_string_object_array (StringObject* str_obj_array, string *my_str, int size);
//Searches the sorted StringObject array for string, "str".
//Returns the index in the array of the string if it is found, otherwise, returns
//-1

int sort_string_object_array (StringObject* str_object_array, int size);
//Sorts the StringObject array alphabetically. The size of the array is passed
//to the algorithm in the variable "size". Function returns 0 if successful and
//-1 if the str_object_array is empty.

#endif
