#include <iostream>
#include "linkedlist.h"

using namespace std;

//Default Constructor used to create an empty list object.
LinkedList::LinkedList()
{
    front = NULL;
    back = NULL;
}


//Destructor for LinkedList.
LinkedList::~LinkedList()
{
    //LinkedList temp;
    ListNodePtr ptr1 = NULL;
    int number_of_values = 0;
    if(front!=NULL)
    {
        number_of_values = back->position;
        for(int i=1; i<=number_of_values;i++)
        {
            ptr1 = front;
            front = front->next;
            delete ptr1;
        }
        front = NULL;//confirm
        back = NULL;
    }

}


//PreCondition: Start with LinkedList object.
//PostCondition: Add the "value" to position 1 in the list (at the front)
//               The position value of all other nodes needs to be adjusted
//               accordingly.
void LinkedList::insert_beginning(int val)
{
    ListNodePtr new_node = new ListNode;
    int number_of_values = 0;
    ListNodePtr temp_node = NULL;

    new_node->value = val; //confirm
    new_node->position = 1;

    if(front == NULL) //empty list
    {
        front = new_node;
        back = new_node;
        //front->position = 1;
    }
    else
    {
        number_of_values = back->position;
        new_node->next = front;
        front = new_node;
        //temp_node = front->next;

        //updating positions of list nodes
        for(temp_node=front->next; temp_node!=NULL; temp_node=temp_node->next)
        {
             temp_node->position = (temp_node->position) + 1;
        }
    }

    return;
}

//PreCondition: Start with LinkedList object.
//PostCondition: Add the "value" to position N+1 in the list (at the back),
//               where N is the number of nodes previously in LinkedList object.
void LinkedList::insert_end(int val)
{
    ListNodePtr new_node = new ListNode;
    new_node->value = val; //confirm


     if(front == NULL) //empty list
    {
        new_node->position = 1;
        front = new_node;
        back = new_node;

    }
    else
    {
        new_node->position = (back->position) + 1;
        back->next = new_node;
        back = new_node;
    }

    return;
}


//PreCondition: Start with LinkedList object.
//PostCondition: Find all objects with value "val" and 1) remove them from the
//               current list and 2) return then as their own linked list with the
//               position values correctly updated. Adjust the position value of all
//               the nodes in your LinkedList object accordingly.
ListNodePtr LinkedList::remove_value(int val)
{
    ListNodePtr new_head = NULL; //head of new list
   // ListNodePtr new_temp = NULL; //used for creating list nodes for the new list
    ListNodePtr new_current = NULL; //used for linking new nodes to the new linked list
    ListNodePtr current_ptr = front; //used for traversing through the old linked list
    ListNodePtr previous_ptr = front; //points to node that occurs before the current node in the old linked list
    int number_of_values = 0;
    int counter = 0; //counts number of values in the new linked list
    int remaining_values = 0;//stores number of values remaining in the old lnked list

    if(front==NULL) //empty list
    {
        return new_head;
    }

    number_of_values = back->position;

    for(int i=1; i<=number_of_values && current_ptr!=NULL; i++)
    {
        if(current_ptr->value == val)
        {
           //Adding the node to the new linked list
           counter++;
           if(counter==1)
           {
               new_head = current_ptr;
               new_current = current_ptr;
           }
           else
           {
               new_current->next = current_ptr;
               new_current = current_ptr;

           }

           //Removing the node from the old linked list
           if(current_ptr==front)
           {
               front = front->next;
           }
           else
           {
               previous_ptr->next = current_ptr->next;
           }
           new_current->next = NULL;
        }

        //moving forward
        previous_ptr = current_ptr;
        current_ptr = current_ptr->next;
    }

    //updating positions of remaining nodes in linked list
    remaining_values = number_of_values-counter;
    current_ptr = front;
    for(int i=1; i<=remaining_values && current_ptr!=NULL; i++)
    {
        current_ptr->position = i;
        if(i==remaining_values) //last node in the old linked list
        {
            back = current_ptr;
        }
        current_ptr = current_ptr->next;
    }
    return new_head;
}


//PreCondition: Start with LinkedList object.
//PostCondition: The node at the "front" of the original list has been removed and
//              its value has been returned by this function.  The positions of all
//               remaining nodes in the LinkedList object have been updated.

int LinkedList::removefront()
{

    ListNodePtr current_ptr = front;
    int return_value = -1;


    if(current_ptr==NULL) //Empty list
    {
        return return_value;
    }

    return_value = front->value;
    front = front->next;
    delete current_ptr;

    //updating positions of nodes in the linked list
    for(current_ptr=front; current_ptr!=NULL; current_ptr=current_ptr->next)
    {
        current_ptr->position = (current_ptr->position)-1;
    }

    return return_value;
}



//Checks to see if the LinkedList is empty.  Returns true if empty, else returns false.
//LinkedList remains unchanged after function call.
bool LinkedList::empty()
{
    return(front==NULL);
}

//PreCondition: Start with a LinkedList object (likely unsorted).
//PostCondition: The LinkedList object will be updated so that it is now sorted with
//              the smaller values located at the front and the larger values located
//              at the back.
void LinkedList::sort_linkedlist()
{
    int number_of_values = 0;
    ListNodePtr min = NULL;
    ListNodePtr ptr1_current = NULL;
    ListNodePtr ptr1_previous = NULL;
    ListNodePtr ptr2_current = NULL;
    ListNodePtr ptr2_previous = NULL;
    ListNodePtr temp1 = NULL;
    ListNodePtr temp2 = NULL;
    int i=0;


    if(front==NULL) //Empty list
    {
        return;
    }
    number_of_values = back->position;
    //Sorting of the linked list using the selection sort method
    ptr1_previous = front;

    for(i=1,ptr1_current=front; i<number_of_values; i++, ptr1_current = ptr1_current->next)
    {
        min = ptr1_current;
        ptr2_previous = ptr1_current;
        for(ptr2_current = ptr1_current->next; ptr2_current!=NULL; ptr2_current = ptr2_current->next, ptr2_previous = ptr2_previous->next)
        {
            //ptr2_previous = ptr2_previous->next;
            if(ptr2_current->value < min->value)
            {
                min = ptr2_current;
            }
        }
        //Swapping
        if(min!=ptr1_current)
        {
            temp1 = ptr1_current;
            ptr1_previous->next = min;
            ptr2_previous->next = temp1;

            temp2 = ptr1_current->next;
            ptr1_current->next = min->next;
            min->next = temp2;
        }

        ptr1_previous = ptr1_current;
    }

    //updating positions in the sorted linked list
    ptr1_current = front;
    for(int i=1; i<=number_of_values && ptr1_current!=NULL; i++)
    {
        ptr1_current->position = i;
        if(i==number_of_values) //last node in the old linked list
        {
            back = ptr1_current;
        }
        ptr1_current = ptr1_current->next;
    }

    return;
}

//Starting at the head of the list, writes out the LinkedList for each node in the
//list from front to back. Uses the format:
// <position>. <value>
// <position>. <value>
// <position>. <value>
// ... (until the end of the list)
//Note the "position" numbers should be sequential counting from 1 to N, where N is
//the number of nodes in the list.
ostream &operator<<(ostream &os, LinkedList &list)
{
    for(ListNodePtr ptr1=list.front; ptr1!=NULL; ptr1 = ptr1->next)
    {
        os<<ptr1->position<<". "<<ptr1->value<<endl;
    }
    return os;
}

//Reads in the "value" and stores it in the N+1 position in the
//linked List, given that there are currently N items in the LinkedList.
istream &operator>>(istream &ins, LinkedList &list)
{
    int val = 0;
    ins>>val;
    list.insert_end(val);
    return ins;
}
