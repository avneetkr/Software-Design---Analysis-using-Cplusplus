#include <iostream>
#include <string>
#include "stringobjects.h"

using namespace std;

//Default Constructor used to create an empty StringObject object.
//When there is no string stored in the array, the num_char should equal 0
StringObject::StringObject()
{
	str = NULL;
	num_char = 0;
}

//Destructor for StringObject objects.
StringObject::~StringObject()
{
	if(num_char!=0)
	{
		delete[] str;
	}
}

//PreCondition: Start with a StringObject (MUTATOR FUNCTION)
//PostCondition: Stores the string "s" in the StringObject and update num_char.
void StringObject::set_string(string& s)
{
    string *temp = NULL;
    if(num_char!=0)
    {
        temp = str;
        delete temp;
    }
	str = new string(s);
	num_char = str->length();
	return;
}

//PreCondition: Start with StringObject. (ACCESSOR FUNCTION)
//PostCondition: Returns the string stored in the object without changing the object.
string* StringObject::get_string()
{
    string* return_value = NULL;
    if(num_char!=0)
    {
         return_value = new string(*str);
         //assign(return_value, str);
      // *(return_value) = str;
    }
    return return_value;
}

//PreCondition: Start with StringObject. (ACCESSOR FUNCTION)
//PostCondition: Returns the number of characters in the string in that object.
int StringObject::get_num_char()
{
    return num_char;
}


//Checks to see if the object is currently storing a string or if it is empty.
bool StringObject::empty()
{
    return (num_char==0);
}


//PreCondition: Two valid string objects.
//PostCondition: Compares the strings stored in these objects and returns
//               true if they are equal and false if they are not.
bool operator ==(StringObject object1, StringObject object2)
{
    if(object1.num_char==0 || object1.num_char==0)
    {
        return false;
    }

    return(object1.str==object2.str);
}


//PreCondition: Two valid string objects.
//PostCondition: Compares the strings stored in these objects and returns
//               true if the first string comes *before* the second string
//               alphabetically.
bool operator <(StringObject object1, StringObject object2)
{
    if(object1.num_char == 0 || object2.num_char== 0)
    {
        return false;
    }

    return(object1.str<object2.str);
}


//PreCondition: Two valid string objects.
//PostCondition: Compares the strings stored in these objects and returns
//               true if the first string comes *after* the second string
//               alphabetically.
bool operator >(StringObject object1, StringObject object2)
{
    if(object1.num_char == 0 || object2.num_char== 0)
    {
        return false;
    }
    return(object1.str>object2.str);
}

//Sends the string stored in this string object to the stream *without* changing
//the string object.
ostream &operator<<(ostream &os, StringObject &mystr)
{
    if(mystr.num_char!=0)
    {
        string temp = *(mystr.str);
        os<<temp;
    }
    return os;

}

//Reads in the value and stores it in the string portion of the string object and
//then initializes the num_char based on its length.
istream &operator>>(istream &ins, StringObject &mystr)
{
    string newstr;
    ins>>newstr;
    mystr.set_string(newstr);
    return ins;
}

//HELPER Function
//Searches for string pointed by "my_str" using binary search method recursively
//PostCondition: Returns index of the object if found, otherwise returns -1
int recursive_binary_search(StringObject* str_object_array, string* my_str, int lo, int hi)
{
    string temp = "\0";
    int mid = 0;
    if(lo<=hi)
    {
        mid = (lo+hi)/2;
        cout<<endl<<mid;
        temp = *(str_object_array[mid].get_string());
        if(*(my_str)==temp)
        {
            return mid;
        }
        else if(*(my_str)<temp)
        {
            return recursive_binary_search(str_object_array, my_str, lo, mid-1);
        }
        else //if(*(my_str)>temp)
        {
            return recursive_binary_search(str_object_array, my_str, mid+1, hi);
        }

    }
    else
    {
        return -1;
    }
}
//Searches the sorted StringObject array for string, "str".
//Returns the index in the array of the string if it is found, otherwise, returns
//-1
int search_sorted_string_object_array (StringObject* str_obj_array, string *my_str, int size)
{
   int return_value = recursive_binary_search(str_obj_array, my_str, 0, size-1);
   return return_value;

}


//Sorts the StringObject array alphabetically (using selection sort). The size of the array is passed
//to the algorithm in the variable "size". Function returns 0 if successful and
//-1 if the str_object_array is empty.
int sort_string_object_array (StringObject* str_object_array, int size)
{
    //int return_value = -1;
    string temp1 =  "\0";
    string temp2 = "\0";
    string min = "\0";
    int min_pos = 0;
    if(size==0)
    {
        return -1;
    }

    for(int i=0;i<size-1;i++)
    {
        min = *(str_object_array[i].get_string());
        min_pos = i;
        for(int j=i; j<size; j++)
        {
            temp2 = *(str_object_array[j].get_string());
            if(temp2<min)
            {
                min = temp2;
                min_pos = j;
            }
        }
        //Swapping
        if(min_pos!=i)
        {
            temp1 = *(str_object_array[i].get_string());
            str_object_array[i].set_string(min);
            str_object_array[min_pos].set_string(temp1);
        }
    }

    return 0;

}

