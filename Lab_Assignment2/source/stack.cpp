#include <iostream>
#include "stack.h"
#include <string>
#include <cstddef>

using namespace std;

//Default Constructor used to create an empty Stack object.
Stack::Stack():top(NULL)
{

}
//Destructor for Stack objects.
Stack:: ~Stack()
{
    string next;
    while (!empty())
        next=pop();
}


//PreCondition: Start with a Stack object.
//PostCondition: Add the string in a new frame at the top of the Stack.

void Stack::push(string& str)
{
    StackFramePtr temp_ptr;

    temp_ptr= new StackFrame;
    temp_ptr->str= new string;
    *(temp_ptr->str)=str;
    temp_ptr->next=top;
    top=temp_ptr;

    return;

}

//PreCondition: Start with Stack object.
//PostCondition: Remove the top Stack Frame and return the string stored at the top.
//               of the Stack.
string Stack::pop()
{
    string return_value="\0";
    StackFramePtr temp_ptr = NULL;

    if(empty())
    {
        return return_value;
    }

    else
    {
        return_value= *(top->str);
        temp_ptr=top;
        top=top->next;
        delete temp_ptr;

        return return_value;
    }
}

//PreCondition: Start with a Stack.
//PostCondition: Search the ENTIRE Stack and remove all frames that have a string of
//               length "length". All frames with strings of length "length" should
//               be returned in a new stack where those frames that were closest to
//               the top are still at the top of this new stack. Furthermore, the
//               orignal Stack should be returned with these selected frames removed
//               and the relative ordering of the remaining frames unchanged.
StackFramePtr Stack::remove_strings_length(int length)
{
    StackFramePtr current_ptr=top;//
    StackFramePtr new_top=NULL;// the new top pointer of the new stack
    StackFramePtr new_current=NULL;
    StackFramePtr previous_ptr=NULL;

    if(empty())
    {
        return new_top;
    }

    previous_ptr = top;
    current_ptr = top;
    while(current_ptr!=NULL)
    {

       if(current_ptr->num_char==length)
       {
         if (new_top==NULL )
         {
             new_top=current_ptr;
             new_current=current_ptr;
         }
         else
         {

            new_current->next=current_ptr;
            new_current=new_current->next;
         }

         //Unlinking the selected node from the old stack
         if(current_ptr==top)
         {
             top = top->next;
         }
         else
         {
            previous_ptr->next=current_ptr->next;
         }

         new_current->next = NULL;

       }

         previous_ptr=current_ptr;//moving part
         current_ptr=current_ptr->next;//moving part
    }
     return new_top;


}

//Checks to see if the Stack is empty.  Returns true if empty, else returns false.
//Stack remains unchanged after function call.
bool Stack::empty()
{
    return (top==NULL);
}

//Starting at the top of the stack and writes out each StackFrame on a separate line.
//Uses the format:
// "<string>" [<num_char>]
// "<string>" [<num_char>]
// "<string>" [<num_char>]
// ... (down to the bottom of the stack)
//Note the first printed entry should be from the top of the stack and the values in
//the stack should remain unchanged.

ostream &operator<<(ostream &os, Stack &mystack )
{
    for(StackFramePtr ptr1=mystack.top; ptr1!=NULL; ptr1=ptr1->next )
    {
        os<<"\""<<ptr1->str<<"\" ["<<ptr1->num_char<<"]"<<endl;
    }
    return os;
}

//Reads in the value and stores it in a StackFrame at the top of the Stack.
istream &operator>>(istream &ins, Stack &stack)
{
    string new_string;
    ins>>new_string;
    stack.push(new_string);
    return ins;
}

