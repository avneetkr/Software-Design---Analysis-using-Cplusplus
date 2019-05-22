//Use only the following libraries:
#include "parserClasses.h"
#include <string>



//****TokenList class function definitions******
//           function implementations for append have been provided and do not need to be modified

//Creates a new token for the string input, str
//Appends this new token to the TokenList
//On return from the function, it will be the last token in the list
void TokenList::append(const string &str) {
	Token *token = new Token(str);
	append(token);
}

//Appends the token to the TokenList if not null
//On return from the function, it will be the last token in the list
void TokenList::append(Token *token) {
	if (!head) {
		head = token;
		tail = token;
	}
	else {
		tail->setNext(token);
		token->setPrev(tail);
		tail = token;
	}
}


//Complete the implementation of the following member functions:
//****Tokenizer class function definitions******

//Computes a new tokenLength for the next token
//Modifies: size_t tokenLength, and bool complete
//(Optionally): may modify offset
//Does NOT modify any other member variable of Tokenizer
void Tokenizer::prepareNextToken()
{
	size_t pos[7] = {0}; //stores positions of different delimiters based on their constraints
	size_t min = 0;
	size_t temp_pos = 0;
	size_t temp_pos2 = 0;
	string temp_str = "\0";

	if(isComplete()) //to check if string parsing is complete
	{
		return;
	}

	temp_pos = str->find_first_not_of(whitespace_char,offset);

	if(temp_pos==-1) //to check if the remaining characters in the string are all whitespace characters( \t\r)
	{
		complete = true;
		return;
	}



	pos[0] = str->find_first_of(str_delimiters,offset);
	pos[1] = str->find_first_of(whitespace_char,offset);
	pos[2] = str->find(signal_assignment,offset);
	pos[3] = str->find(signal_assignment1, offset);
	pos[4] = str->find(signal_assignment2,offset);
	pos[5] = str->find(comments,offset);
	pos[6] = str->find_first_of(newline_char,offset);
	temp_pos2 = str->find(comments,(offset-2));//to check if the last token was a '--'
										     //making this token a comment
	temp_str=(*str);



	if(temp_pos2==(offset-2))//last token was '--', so this token will be a comment
	{
		temp_pos = pos[6];//position of newline character
		tokenLength = temp_pos-offset;
		complete = true;
		offset = offset + tokenLength;
		return;
	}


	//moves over all consecutive whitespace characters
	while(offset==pos[1])//there is a whitespace character at the current position
	{
		offset = offset+1;
		pos[1] = str->find_first_of(whitespace_char,offset); //finds the next occurence of whitespace character(if any)
		if(temp_str[offset]=='\n')
		{
			complete = true;
			return;
		}
	}



	if(offset==pos[6])//there is a newline character at the current position
	{
		complete = true;
		return;
	}

	if(offset==pos[0]) //there is a single character delimiter at the current position
	{
		tokenLength = 1;
		offset = offset+tokenLength;
		return;
	}
	else if(offset==pos[2] || offset==pos[3] || offset==pos[4] || offset==pos[6]) //there is a multi character operator('=>',<=',':=','--') at the current position
	{
		tokenLength = 2;
		offset = offset + tokenLength;
		return;
	}
	else //find which of the pos's come first. that will be the tokenlength
	{
		//finding minimum of pos0,1,2,3,4,5,6 to determine which delimiter occurs first
		min = pos[0];
		for(int j=1;j<6;j++)
		{
			if(min<pos[j])
			{
				min = pos[j];
			}
		}

		tokenLength = min-offset;
		offset = min;
		return;

	}




}

//Sets the current string to be tokenized
//Resets all Tokenizer state variables
//Calls Tokenizer::prepareNextToken() as the last statement before returning.
void Tokenizer::setString(string *str)
{
	//(*str)= string *stringTokenized;
	if((this->str)!=nullptr)
	{
		delete (this->str);
		this->str = nullptr;
	}

	this->str = new string(*str);
	//*(this->str) = *str;
	tokenLength=0;
	offset=0;
	complete=false;
	prepareNextToken();

}

//Returns the next token. Hint: consider the substr function
//Updates the tokenizer state
//Updates offset, resets tokenLength, updates processingABC member variables
//Calls Tokenizer::prepareNextToken() as the last statement before returning.
string Tokenizer::getNextToken()
{

	string nextstring=str->substr(offset-tokenLength,tokenLength);
	tokenLength=0;
	//offset=position;

	prepareNextToken();
	return nextstring;
}



//****Challenge Task Functions******

//Removes the token from the linked list if it is not null
//Deletes the token
//On return from function, head, tail and the prev and next Tokens (in relation to the provided token) may be modified.
void TokenList::deleteToken(Token *token)
{
	Token* temp1 = nullptr;
	Token* temp2 = nullptr;

	if(token==nullptr)
	{
		return;
	}

	temp1 = token->getPrev();
	temp2 = token->getNext();

	if(temp1==nullptr && temp2==nullptr)//token is the only token in the linked list
	{
		head = nullptr;
		tail = nullptr;
	}
	else if(temp1==nullptr) //token=head and token!=tail
	{
		head=temp2;
	}
	else if(temp2==nullptr)//token!=head and token=tail
	{
		tail=temp1;
	}
	else
	{
		temp1->setNext(temp2);
	}



	delete token;
	token = nullptr;

	return;

}

//Removes all comments from the tokenList including the -- marker
//Returns the number of comments removed
int removeComments(TokenList &tokenList)
{

	Token* temp_head = tokenList.getFirst();//head of tokenList
	Token* current_token = nullptr;//stores the current token being tested
	Token* next_token = nullptr;//stores the next token of the current token being tested
	string current_str=nullptr;//stores the string in the current token being tested
	int count = 0;//counts the number of comments removed
	int flag = 0;//is 1 if the last token tested was '--', 0 otherwise

	if(temp_head==nullptr)//empty list
	{
		return count;
	}

	current_token = temp_head;
	current_str = current_token->getStringRep();

	while(current_token!=nullptr)
	{
		next_token = current_token->getNext();

		if(flag==1 && current_str=="\n")//empty comment
		{
			flag=0;
		}
		else if(flag==1)//previous token tested was '--'
		{
			tokenList.deleteToken(current_token);
			flag=0;
		}
		else if(current_str[0]=='-' && current_str[1]=='-') //current_str is '--'
		{
			tokenList.deleteToken(current_token);
			count++;
			flag=1;
		}


		current_token = next_token;
		current_str = current_token->getStringRep();

	}

	return count;


}


