/*
/* Title: linkedlist.h
/* Author(s): Lesley Shannon
/* Student Number: N/A
/* Related Files: linkedlist.cpp
/* Project: ENSC 251 Lab Assignment 2
/* Version: 1.0
/* Date of last Revision: September 27, 2015
                          October 1, 2015
/* Revision History: V1.0- File creation
/*                   V2.0- Adding #define
/*
/**************************************************************************************


//Objective: To create the basic member functions to be able to create
//           and manipulate a linked list.

/* Requirements for your LinkedList class:
    1) This class must remain an ADT- you are not allowed to change any public function
       declarations.
    2) You can add new private member functions as helper functions.
    3) You are not allowed to add any new global variables to this file or new private
       member fields to your LinkedList class.
    4) You need to create the corresponding .cpp file, ensure that these files will compile
       properly when used in compilation with multiple other file instances (that may or
       may not also include references to the LinkedList class).
    5) You need to provide sufficient comments and well chosen variable names to demonstrate
       a clean and readable coding style.

*/
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;


struct ListNode
{
	int value; //Value stored at the node; values need not be consecutive for adjacent
	           //nodes in a list.
	int position; //Values position in the linked list (Normally this isn't included in a
				  //Linked List, but it will help you visualize your list and debug it.
				  //Position values must be sequential for adjacent nodes in a list.
	ListNode * next; // Points to the next Queue object in your linked list.
};

typedef ListNode* ListNodePtr; //Type defined as a pointer to a ListNode structure

//A Linked List with Head and Tail pointer that allows users to insert beginning/
//insert end
//Note that by default, this Linked List is *UNSORTED*
class LinkedList
{
public:
	LinkedList();
	//Default Constructor used to create an empty list object.

	~LinkedList();
	//Destructor for LinkedList.

	void insert_beginning(int val);
	//PreCondition: Start with LinkedList object.
	//PostCondition: Add the "value" to position 1 in the list (at the front)
	//               The position value of all other nodes needs to be adjusted
	//               accordingly.

	void insert_end(int val);
	//PreCondition: Start with LinkedList object.
	//PostCondition: Add the "value" to position N+1 in the list (at the back),
	//               where N is the number of nodes previously in LinkedList object.

	ListNodePtr remove_value(int val);
	//PreCondition: Start with LinkedList object.
	//PostCondition: Find all objects with value "val" and 1) remove them from the
	//               current list and 2) return then as their own linked list with the
	//               position values correctly updated. Adjust the position value of all
	//               the nodes in your LinkedList object accordingly.

	int removefront();
	//PreCondition: Start with LinkedList object.
	//PostCondition: The node at the "front" of the original list has been removed and
	//               its value has been returned by this function.  The positions of all
	//               remaining nodes in the LinkedList object have been updated.

    bool empty();
    //Checks to see if the LinkedList is empty.  Returns true if empty, else returns false.
    //LinkedList remains unchanged after function call.

    void sort_linkedlist();
    //PreCondition: Start with a LinkedList object (likely unsorted).
    //PostCondition The LinkedList object will be updated so that it is now sorted with
    //              the smaller values located at the front and the larger values located
    //              at the back.

 	friend ostream &operator<<(ostream &, LinkedList &);
	//Starting at the head of the list, writes out the LinkedList for each node in the
	//list from front to back. Uses the format:
	// <position>. <value>
	// <position>. <value>
	// <position>. <value>
	// ... (until the end of the list)
	//Note the "position" numbers should be sequential counting from 1 to N, where N is
	//the number of nodes in the list.

	friend istream &operator>>(istream &, LinkedList &);
	//Reads in the "value" and stores it in the N+1 position in the
	//linked List, given that there are currently N items in the LinkedList.


private:

   // void remove(int pos);
    //PreCondition: Start with LinkedList object
    //PostCondition: Removes the node with position pos from the list and
    //               updates positions accordingly.

	ListNodePtr front; // Points to the front or "head" of the linked list.
						// Items are removed from here. This will always be
						// position 1
	ListNodePtr back;	// Points to the back or "tail" of the linked list.
						// Items are added here. This will always be position
						// N, where N is the number of items in the linked list.

};

#endif

