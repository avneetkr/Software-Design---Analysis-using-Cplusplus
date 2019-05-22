//Use only the following libraries:
#include "parserClasses.h"
#include <string>
#include <cctype> //for tolower
#include <iostream> //remove after testing

//Takes in a string and returns the string in lowercase
string tolowercase(string str);

//*****Token class function definition*******
//Copy constructor
Token::Token(const Token &token)
{
	next = token.next;
	prev = token.prev;
	stringRep = token.stringRep;
	_isKeyword = token._isKeyword;
	type = token.type;
	if((token.details)!=nullptr)
	{
		details = new tokenDetails;
		details->type = (token.details)->type;
		details->width = (token.details)->width;
	}
}

//Destructor, free any memory owned by this object
Token::~Token()
{
	if(details!=nullptr)
	{
		delete details;
	}
}

//Assignment operator
void Token::operator =(const Token& token)
{
	next = token.next;
	prev = token.prev;
	stringRep = token.stringRep;
	_isKeyword = token._isKeyword;
	type = token.type;
	/*if(details!=nullptr && details!=(token.details))
	{
		//delete details;
		details = nulllptr;
	}
	*/
	if((token.details)!=nullptr)
	{
		//details = new tokenDetails;
		if(details==nullptr)
			details = new tokenDetails;
		details->type = (token.details)->type;
		details->width = (token.details)->width;
	}

	return;
}

//Set's the tokenDetails given a string type and optional vector width
//Allocates tokenDetails if it doesn't already exist
//void Token::setTokenDetails(const string &type, int width = 0)
void Token::setTokenDetails(const string &type, int width)
{
	if(details==nullptr)
	{
		details = new tokenDetails;
	}
	details->type = type;
	details->width = width;

	return;
}

//true if all token details are set
 /* bool Token::AreTokenDetailsSet()
  {
  	if(type==T_Operator || type==T_Identifier || type==T_Literal || type==T_CommentBody || type==T_Other)
  		return true;
  	else
  		return false;
  }*/

//****TokenList class function definitions******
//           function implementations for append have been provided and do not need to be modified


//destructor
 TokenList::~TokenList()
 {
 	if(head!=nullptr)
 	{
 		Token* temp = nullptr;
 		temp = head;
 		Token* next = nullptr;
 		next = head;
 		while(temp)
 		{
 			next = temp->getNext();
 			delete temp;
 			temp = next;
 		}
 	}
 }
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
	//cout<<endl<<"token being appended: ";
	//cout<<token->getStringRep();
	if (!head) {
		head = token;
		tail = token;
		token->setPrev(nullptr);
	}
	else {
		tail->setNext(token);
		token->setPrev(tail);
		tail = token;
	}
	token->setNext(nullptr);
	numberoftokens++;
}

//find token details and type and update token.  May require examining properties of neighbouring tokens
void TokenList::findAndSetTokenDetails(Token *token)
{
	Token* temp_prev = nullptr; //to store the previous token of the current token
	Token* temp_next = nullptr; //to store the next token of the current token
	string current_str = "\0"; //to store the stringRep of the current token
	size_t tokensize = 0; //to store the size of current_str
	size_t literal_pos1 = 0; //to store the position of the first occurrence of "bBoOxX"
	size_t literal_pos2 = 0; //to store the first occurence of "
	size_t literal_pos3 = 0; //to store the second occurence of "
	size_t tokenwidth = 0; //to store the width of token if the token is a vector
	size_t i=0; //used to iterate through loop
	int flag = 0; //used to signify a change for various cases
	size_t operator_pos = 0; //to store the first occurence of one of "*/+-&=<>"
	Token* identifier_type_token = nullptr; //to store the type of identifier, if the identifier is for a signal or variable
	string identifier_type_string = "\0";//to store identifier type
	Token* tokenlist_parser = nullptr; //to parse through the tokenlist to find any repeated occurence of the current token (if the current token is an identifier)
	Token* identifier_width1 = nullptr; //to store the upper limit of identifier width
	Token* identifier_width2 = nullptr; //to store the lower width of identifier width
	//Token* temp_ptr = nullptr;
	string temp_str = "\0"; //to store the stringRep of the token when parsing through the tokenlist
	int token_width1 = 0; //to store the upper limit of identifier width as an integer
	int token_width2 = 0; //to store the lower limit of identifier width as an integer
	bool isSignalorVariable = false; //true if the identifier token is a signal/variable name
	int countIdentifiers = 0; //counts number of identifier definitions
	Token* identifier_token = nullptr; //stores token ptr of the identifier token in case of multiple identifier definitions
	int j = 0;
	//Token* parser2 = nullptr;
	string identifier_str = "\0";
	
	//cout<<endl<<endl<<"current string being tested: "<<token->getStringRep();
	//cout<<endl<<"are details of this already token set? "<<token->AreTokenDetailsSet();
	/*if(token->AreTokenDetailsSet())
	{
		cout<<endl<<"token type: "<<token->type;
		if(token->details!=nullptr)
			cout<<endl<<"token type type: "<<(token->details)->type<<endl<<"token width: "<<(token->details)->width;
	}
*/
	if(token==nullptr || head==nullptr || tail==nullptr || token->AreTokenDetailsSet())
	{
		//cout<<endl<<"returned 1";
		return;
	}

	temp_prev = token->getPrev();
	temp_next = token->getNext();
	current_str = token->getStringRep();
	//cout<<endl<<"current string being tested: "<<current_str;
	
	//***CHECKING FOR COMMENT BODY***
	if(temp_prev!=nullptr && (temp_prev->getStringRep())==comments) //this token is comment body
	{
		token->type = T_CommentBody;
		token->detailsSet = true;
		//cout<<endl<<"returned 2";
		return;
	}


	//***CHECKING FOR KEYWORDS***
	for(i=0; i<numberofkeywords; i++)
	{
		if(keywords[i]==current_str)
		{
			token->_isKeyword = true;
			//cout<<"Keyword found"<<endl;
			//token->setKeyword();
			break;
		}

	}



	
//cout<<endl<<"TESTED"<<endl;

	//***CHECKING FOR LITERALS*****

	//checking for std_logic_vectors
	literal_pos1 = current_str.find_first_of(literal_vectors,0);//if the first character is one of 'bBoOxX' for binary/octal/hexadecimal numbers
	literal_pos2 = current_str.find(literal_doublequotes,0);//position of first double quote
	literal_pos3 = current_str.find(literal_doublequotes,2);//position of second double quote
	tokensize = current_str.size();
	//cout<<endl<<"token size= "<<tokensize<<endl;
	//cout<<"literal_pos1= "<<literal_pos1<<endl;
	//cout<<"literal_pos2= "<<literal_pos2<<endl;
	//cout<<"literal_pos3= "<<literal_pos3<<endl;

	if( ( ( (literal_pos1==0) && (literal_pos2==1) ) || (literal_pos2==0) ) && (literal_pos3==tokensize-1))
	{
		//cout<<endl<<"is a literal vector"<<endl;
		token->type = T_Literal;
		tokenwidth = (literal_pos3-literal_pos2)-1;

		if(current_str[0]=='o' || current_str[0]=='O')//octal
		{
			tokenwidth = 3*tokenwidth;
		}
		else if(current_str[0]=='x' || current_str[0]=='X')//hexagonal
		{
			tokenwidth = 4*tokenwidth;
		}


		token->setTokenDetails(std_logic_vector, tokenwidth);
		token->detailsSet = true;
		//cout<<endl<<"returned 3";
		return;
	}

	//checking for std_logic
	if(tokensize==3 && current_str[0]==literal_singlequotes && current_str[2]==literal_singlequotes)
	{
		token->type = T_Literal;
		tokenwidth = 1;
		token->setTokenDetails(std_logic, tokenwidth);
		token->detailsSet = true;
		//cout<<endl<<"returned 4";
		return;
	}

	//checking for integers
	for(i=0; i<tokensize;i++)
	{

		//if(!(current_str[i]=='0' || current_str[i]=='1' || current_str[i]=='2' || current_str[i]=='3'
		//|| current_str[i]=='4' || current_str[i]=='5' || current_str[i]=='6' || current_str[i]=='7'
		//|| current_str[i]=='8' || current_str[i]=='9'))
		if( !( current_str[i]>='0' && current_str[i]<='9' ) )
		{
			flag = 1;
			break;
		}
	}

	if(flag==0)//token is an integer
	{
		token->type = T_Literal;
		token->setTokenDetails(integer);//can find width for bonus
		token->detailsSet = true;
		//cout<<endl<<"returned 5";
		return;
	}


	//checking for boolean type

	//converting the string to lower case
	/*for(i=0; i<tokensize; i++)
	{
		current_str[i] = tolower(current_str[i]);
	}*/

	current_str = tolowercase(current_str);

	if(current_str==literal_true || current_str==literal_false)
	{
		token->type = T_Literal;
		token->setTokenDetails(boolean);
		token->detailsSet = true;
		//cout<<endl<<"returned 6";
		return;
	}



	//***CHECKING FOR OPERATORS***

	//checking for single character operators
	//cout<<endl<<"token size= "<<tokensize<<endl;
	if(tokensize==1)
	{
		operator_pos = current_str.find_first_of(operators[0],0);
		if(operator_pos==0)
		{
			token->type = T_Operator;
			token->detailsSet = true;
			//cout<<endl<<"returned 7";
			return;
		}
	}

	//checking for the rest of operators
	flag = 0;
	for(i=1; i<numberofoperators; i++)
	{
		if(current_str==operators[i])
		{
			flag = 1;
			break;
		}
	}

	if(flag==1)
	{
		token->type = T_Operator;
		token->detailsSet = true;
		//cout<<endl<<"returned 8";
		return;
	}

	//***CHECKING FOR IDENTIFIER***

	if(current_str[0]>='a' && current_str[0]<='z') //considering first occurence of the identifier
	{
		token->type = T_Identifier;

		countIdentifiers = 1;


		//checking if the identifier is a signal or variable name
		if(temp_prev!=nullptr)
		{
			temp_str=temp_prev->getStringRep();
			if(temp_str==identifier_signal || temp_str==identifier_variable)
			{
				isSignalorVariable = true; //this identifier token is a signal/variable name

				//setting identifier width & type
				//assuming signal/variable <name1>,<name2>,<name3>,..: <type>, or
				//         signal <name1>,<name2>,<name3>,..: <type> := <default value>, or
				//         signal <name1>,<name2>,<name3>,..: <type>(# downto/to #)

				//checking for multiple definitions
				//cout<<endl<<"first identifier: "<<current_str;
				for(tokenlist_parser = token->getNext(); tokenlist_parser!=nullptr; tokenlist_parser=tokenlist_parser->getNext())
				{
					temp_str = tokenlist_parser->getStringRep();
					if(temp_str==":")//end
					{
						break;
					}
					if(temp_str==",")
					{
						countIdentifiers++;
					}
					//cout<<endl<<"identifier in multiple definition checking: "<<temp_str;
				}

				//cout<<endl<<"number of identifiers being defined: "<<countIdentifiers;
				j=1;
				identifier_token = token;
				while(j<countIdentifiers)
				{
					identifier_token = (identifier_token->getNext());
					if(identifier_token) identifier_token = identifier_token->getNext();
					j++;
				}
				//identifier_type_token = temp_next->getNext();//stores <type>
				identifier_type_token = identifier_token->getNext();
				if(identifier_type_token) identifier_type_token = identifier_type_token->getNext();//new Token(*( (identifier_token->getNext())->getNext() ) );//stores <type> token
				if(identifier_type_token) identifier_type_string = identifier_type_token->getStringRep();//stores <type>
				tokenwidth = 0;//stores width (=0 for non-vector type)



				//if(identifier_type_token!=nullptr)

				//checking if the identifier is a vector
				tokenlist_parser = identifier_type_token->getNext();
				//cout<<endl<<"token after identifier type and : is "<<tokenlist_parser->getStringRep();
				if(tokenlist_parser!=nullptr)
				{
					if( (tokenlist_parser->getStringRep()) == identifier_vectorcheck) //checking if the next token is "("
					{

						//this identifier will be a vector type
						identifier_width1 = tokenlist_parser->getNext();
						identifier_width2 = (identifier_width1->getNext())->getNext();

						//converting the width strings to integers
						token_width1 = atoi( (identifier_width1->getStringRep()).c_str() );
						token_width2 = atoi( (identifier_width2->getStringRep()).c_str() );

						//storing vector width
						tokenwidth = abs(token_width1-token_width2)+1;
						//cout<<endl<<"upper limit of token width = "<<token_width1;
						//cout<<endl<<"lower limit of token width = "<<token_width2;
						//cout<<endl<<"tokenwidth is "<<tokenwidth;
					}

				}//cout<<endl<<"TESTED";
				//cout<<endl<<"identifier_type_token is "<<identifier_type_string;
				//identifier_type_token->getStringRep();
				//cout<<endl<<"TESTED"<<" Is signal or variable name? "<<isSignalorVariable;
				j=1;

				//Setting details of all the identifiers being defined at the same time
				identifier_token = token;
				while(j<=countIdentifiers && identifier_token!=nullptr)
				{
					identifier_token->type = T_Identifier;
					identifier_token->setTokenDetails(identifier_type_string, tokenwidth);
					identifier_token->detailsSet = true;
					//if(identifier_token) cout<<endl<<"setting detail of identifier: "<<identifier_token->getStringRep();
					identifier_token = (identifier_token->getNext());
					if(identifier_token) identifier_token = identifier_token->getNext();
					
					j++;

				}

				//cout<<endl<<"Identifier width= "<<tokenwidth;
				//Setting the token details of repeated occurences of all the identifiers being defined 
				identifier_token = token;
				j=1;
				while(j<=countIdentifiers && identifier_token!=nullptr)
				{
					identifier_str = identifier_token->getStringRep();

					//cout<<endl<<"j = "<<j;
					
					for(tokenlist_parser = identifier_token->getNext(); tokenlist_parser!=nullptr; tokenlist_parser= tokenlist_parser->getNext())
					{
						temp_str = tokenlist_parser->getStringRep();
						if(temp_str==identifier_str)
						{
							tokenlist_parser->type = token->type;
							if(isSignalorVariable)
							{
								tokenlist_parser->setTokenDetails(identifier_type_string,tokenwidth);
								//if(tokenlist_parser) cout<<endl<<"setting detail of identifier: "<<tokenlist_parser->getStringRep();
								tokenlist_parser->detailsSet = true;
							}

						}
					}

					identifier_token = (identifier_token->getNext());
					if(identifier_token) identifier_token = identifier_token->getNext();
					//if(identifier_token) cout<<endl<<"setting detail for identifier: "<<identifier_token->getStringRep();
					j++;
				}
			}


		}
		token->detailsSet = true;
		//cout<<endl<<"returned 9";
		return;
	}

	//***IF THE TOKEN IS NOT COMMENTBODY, LITERAL, OPERATOR OR IDENTIFIER, IT IS T_OTHER***
	token->type = T_Other;
	token->detailsSet = true;
	//cout<<endl<<"TESTED other";
	//cout<<endl<<"returned 10";
	return;

}



//Complete the implementation of the following member functions:
//****Tokenizer class function definitions******

//Computes a new tokenLength for the next token
//Modifies: size_t tokenLength, and bool complete
//(Optionally): may modify offset
//Does NOT modify any other member variable of Tokenizer
void Tokenizer::prepareNextToken()
{
	size_t pos[11] = {0}; //stores positions of different delimiters based on their constraints
	size_t min = 0;
	size_t temp_pos = 0;
	size_t temp_pos2 = 0;
	size_t temp_pos3 = 0;
	string temp_str = "\0";
	//cout<<endl<<"initial offset= "<<offset;
	//cout<<endl<<"Completion status initially= "<<complete;

	/*if(isComplete()) //to check if string parsing is complete
	{
		return;
	}
*/


	pos[0] = str->find_first_of(str_delimiters,offset);
	pos[1] = str->find_first_of(whitespace_char,offset);
	pos[2] = str->find(signal_assignment,offset);
	pos[3] = str->find(signal_assignment1, offset);
	pos[4] = str->find(signal_assignment2,offset);
	pos[5] = str->find(comments,offset);
	//pos[6] = str->find_first_of(newline_char,offset);
	pos[6] = str->length();
	pos[7] = str->find(singlequote,offset);
	pos[8] = str->find(signal_assignment3,offset);
	pos[9] = str->find(signal_assignment4,offset);
	pos[10] = str->find(another_operator,offset);
	temp_str=(*str);



	//TESTING
	//for(int i=0;i<7;i++)
	//	cout<<endl<<"pos["<<i<<"]= "<<pos[i];

	//to check if last token was '--', so this token will be a comment
	if(offset>=2)
	{
		temp_pos2 = str->find(comments,(offset-2));
		//cout<<endl<<"temp_pos2= "<<temp_pos2;//TESTING
		if(temp_pos2==(offset-2))
{

		temp_pos = pos[6];//position of end of line
		tokenLength = temp_pos-offset;
		complete = true;
		offset = offset + tokenLength;
		//cout<<endl<<"Final offset= "<<offset;//TESTING
		//cout<<endl<<"Tokenlength= "<<tokenLength;//TESTING
		return;
	}
	}


	//moves over all consecutive whitespace characters
	while(offset==pos[1])//there is a whitespace character at the current position
	{
		offset = offset+1;
		pos[1] = str->find_first_of(whitespace_char,offset); //finds the next occurence of whitespace character(if any)
		//cout<<endl<<"pos of next whitespace= "<<pos[1];
		if(temp_str[offset]=='\n')
		{
			complete = true;
			return;
		}

	}

	//cout<<endl<<"offset now= "<<offset;


	/*if(offset==pos[6])//there is a newline character at the current position
	{
		complete = true;
		return;
	}
*/


	if(offset==pos[2] || offset==pos[3] || offset==pos[4] || offset==pos[5] || offset==pos[8] || offset==pos[9] || offset==pos[10]) //there is a multi character operator('=>',<=',':=','--','/=', '>=', '**') at the current position
	{
		tokenLength = 2;
		offset = offset+tokenLength;

	}
	else if(offset==pos[7])//there is a single quote at the current position
	{
		temp_pos3 = str->find(singlequote,offset+2);

		//Checking for tokens like '0','1',etc
		if(temp_pos3==(offset+2))//there is a only one character between the two single quotes,i.e, current token is a bit literal
		{
			tokenLength = 3;
			offset = offset+tokenLength;
		}
		else
		{
			tokenLength = 1;
			offset = offset+tokenLength;
		}
	}
	else if(offset==pos[0]) //there is a single character delimiter at the current position
	{
		tokenLength = 1;
		offset = offset+tokenLength;
	}
	else
	{
		//finding minimum of pos0,1,2,3,4,5,6 to determine which delimiter occurs first
		min = pos[0];
		for(int j=1;j<11;j++)
		{
			if(min>pos[j])
			{
				min = pos[j];
			}
		}

		tokenLength = min-offset;
		offset = min;

	}


	temp_pos = str->find_first_not_of(whitespace_char,offset);
	//cout<<endl<<"pos of not whitespace_char after parsing= "<<temp_pos<<endl;
	if(pos[6] == offset || pos[6] < temp_pos )//string parsing is now complete
	{
			complete=true;
	}

	//cout<<endl<<"Final offset= "<<offset;//TESTING
	//cout<<endl<<"Tokenlength= "<<tokenLength;//TESTING
	return;

}

//Sets the current string to be tokenized
//Resets all Tokenizer state variables
//Calls Tokenizer::prepareNextToken() as the last statement before returning.
void Tokenizer::setString(string *str)
{
	//(*str)= string *stringTokenized;


	size_t pos_not_whitespace_char = str->find_first_not_of(whitespace_char,0);//to check if all the characters in this string are whitespace_char( /t/r)
	size_t lengthofstr = str->length();

	//deleting previous string
	if((this->str)!=nullptr)
	{
		delete (this->str);
		this->str = nullptr;
	}

	//cout<<endl<<"position of not_whitespace_char= "<<pos_not_whitespace_char<<endl;

	//error checking
	if( (lengthofstr==0) || (lengthofstr < pos_not_whitespace_char) )
	{
		complete = true;
		return;
	}




	//Resetting member variables
	tokenLength=0;
	offset=0;
	complete=false;
	this->str = new string(*str);
	return;


//	prepareNextToken();

}



//Returns the next token. Hint: consider the substr function
//Updates the tokenizer state
//Updates offset, resets tokenLength, updates processingABC member variables
//Calls Tokenizer::prepareNextToken() as the last statement before returning.
string Tokenizer::getNextToken()
{

	string nextstring = "\0";
	if(str!=nullptr)
	{
		if(!isComplete())
		prepareNextToken();
		nextstring=str->substr(offset-tokenLength,tokenLength);
		tokenLength=0;

	}


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
		temp2->setPrev(nullptr);
	}
	else if(temp2==nullptr)//token!=head and token=tail
	{
		tail=temp1;
		temp1->setNext(nullptr);
	}
	else
	{
		temp1->setNext(temp2);
		temp2->setPrev(temp1);
	}



	delete token;
	token = nullptr;
	numberoftokens--;

	return;

}

//Removes all comments from the tokenList including the -- marker
//Returns the number of comments removed
int removeComments(TokenList &tokenList)
{

	Token* temp_head = tokenList.getFirst();//head of tokenList
	Token* current_token = nullptr;//stores the current token being tested
	Token* next_token = nullptr;//stores the next token of the current token being tested
	string current_str="\0";//stores the string in the current token being tested
	int count = 0;//counts the number of comments removed
	int flag = 0;//is 1 if the last token tested was '--', 0 otherwise

	if(temp_head==nullptr)//empty list
	{
		return count;
	}

	current_token = temp_head;
	//current_str = current_token->getStringRep();

	while(current_token!=nullptr)
	{
		current_str = current_token->getStringRep();
		next_token = current_token->getNext();
		//cout<<endl<<"token being tested: "<<current_str;

		if(flag==1 && current_str=="\n")//empty comment
		{
			flag=0;
		}
		else if(flag==1)//previous token tested was '--'
		{
			tokenList.deleteToken(current_token);
			flag=0;
		}
		else if(current_str=="--")
		//if(current_str[0]=='-' && current_str[1]=='-') //current_str is '--'
		{
			tokenList.deleteToken(current_token);
			count++;
			flag=1;
		}

		current_token = next_token;


	}

	return count;


}



//Removes all tokens of the given tokenType
//Returns the number of tokens removed
int removeTokensOfType(TokenList& tokenList, tokenType type)
{
	Token* temp_head = tokenList.getFirst();//head of tokenList
	Token* current_token = nullptr;//stores the current token being tested
	Token* next_token = nullptr;//stores the next token of the current token being tested
	int count = 0;//counts the number of comments removed

	if(temp_head==nullptr)//empty list
	{
		return count;
	}


	current_token = temp_head;

	//if the tokens through the list is of token type remove it from the list
	//otherwise just skip it.
	while(current_token!=nullptr)
	{
	    next_token=current_token->getNext();
	    if(current_token->getTokenType()==type)
	    {
	            tokenList.deleteToken(current_token);
	            count++;
	    }
	    current_token=next_token;//moving to the next postion.
	}

	return count;
}


//Takes in a string and returns the string in lowercase
string tolowercase(string str)
{
	size_t stringsize = str.size();
	size_t i = 0;
	string newstring = "\0";
	newstring = str;
	for(i=0;i<stringsize;i++)
	{
		newstring[i] = tolower(newstring[i]);
	}
	return newstring;
}

//Creates a new TokenList, and returns a pointer to this list
//Searches for all conditional expressions in tokenList and appends them to the new list
//Format is as follows:
//Each token that is part of a condtional expression is appended sequentially
//At the end of a conditional expression a newline character is appened
   //Example: if (a = true) then
   //Your list should include "(", "a", "=", "true", ")" and "\n"
//tokenList is NOT modified
TokenList* findAllConditionalExpressions(const TokenList &tokenList)
{
	//Token* temp_prev = nullptr;


	Token* current_token = nullptr;
	string current_str = "\0";
	Token* temp_head = tokenList.getFirst();
	TokenList* newtokenlist = nullptr;
	int i = 0;
	Token* prev_token = nullptr;
	string prev_str = "\0";
	//Token* temp_token = nullptr;
	//string temp_str = "\0";

	if(temp_head==nullptr)
	{
		return newtokenlist;
	}



	current_token = temp_head;

	while(current_token!=nullptr)
	{
		current_str = tolowercase(current_token->getStringRep());
		
		//checking for end if
		prev_token = current_token->getPrev();
		if(prev_token) 
			prev_str = tolowercase(prev_token->getStringRep());

		//if(next_token) //&& next_str=="end")
		//	temp_token = next_token->getNext;

		//if(temp_token)
		//	temp_str = tolowercase(temp_token->getStringRep());
				

		if( (!(prev_str=="end" && current_str=="if")) && (current_str=="if" || current_str=="elsif") )
		{
			i++;
			if(i==1)//first conditional expression detected
				newtokenlist = new TokenList;

			current_token = current_token->getNext();
			if(current_token) current_str = current_token->getStringRep();

			while(current_str!="then" && current_token!=nullptr)
			{
				//cout<<endl<<"tested in function "<<++i;
 				//fflush(stdout);
 				//cout<<endl<<"current token is nullptr? "<<(current_token==nullptr);

				Token *newtoken = new Token(*current_token);
				newtokenlist->append(newtoken);

				current_token = current_token->getNext();
				if(current_token!=nullptr) current_str=current_token->getStringRep();

			}
			newtokenlist->append("\n");
		}
		else if(current_str=="when")
		{
			i++;
			if(i==1)//first conditional expression detected
				newtokenlist = new TokenList;

			current_token = current_token->getNext();
			if(current_token) current_str = current_token->getStringRep();

			while(current_str!="else" && current_token!=nullptr)
			{
				Token* newtoken = new Token(*current_token);
				newtokenlist->append(newtoken);

				current_token = current_token->getNext();
				if(current_token!=nullptr) current_str = current_token->getStringRep();
			}
			newtokenlist->append("\n");
		}
		if(current_token!=nullptr)
		current_token = current_token->getNext();
	}
   
	return newtokenlist;
}



//finds and prints (for error_token_list) number of missing thens and endifs in conditional statements
void ConditionalErrorChecking(TokenList& tokenList)
{
	Token* temp_head = tokenList.getFirst();
	Token* current_token = nullptr;
	string current_str = "\0";
	int missing_thens = 0;
	int missing_endifs = 0;
	string temp_str = "\0";
	int numberoflines = 0;
	Token* prev_token = nullptr;
	string prev_str = "\0";
	//TokenList* stacklist_then=nullptr;
	//TokenList* stacklist_endif=nullptr;
	//Token* temp1 = nullptr;
	//Token* temp2 = nullptr;
	//Token* parser1 = nullptr;
	string parser1_str = "\0";
	int linenumber = 1;

	//bool first_if = false;

	if(temp_head==nullptr)//empty list
	{
		return;
	}

	current_token = temp_head;

	while(current_token)
	{
		if(current_token->getStringRep()=="\n")
			numberoflines++;
		current_token = current_token->getNext();

	}
	//const int number = numberoflines;
	//int array_of_missing_endifs[number] = {0}; 
	//int array_of_missing_thens[number] = {0};
	int *array_of_missing_thens = new int[numberoflines];
	int *array_of_missing_endifs = new int[numberoflines];
	//cout<<endl<<"number of lines1: "<<numberoflines;
	
	//cout<<endl<<"missing_endifs: "<<missing_endifs<<endl<<"missing_thens: "<<missing_thens;
	current_token = temp_head;
	prev_token = temp_head;
	prev_str = prev_token->getStringRep();
	while(current_token!=nullptr)
	{

		current_str=current_token->getStringRep();
		current_str = tolowercase(current_str);
		//cout<<endl<<"previous string: "<<prev_str;
		//cout<<endl<<"current_str: "<<current_str;
		//cout<<endl<<"current_str: "<<current_str;
		if(prev_str=="\n")//its a new line
		{
			linenumber = atoi(current_str.c_str());
			cout<<endl<<"line being tested: "<<linenumber;
		}
		if(current_str=="if")
		// || current_str=="elsif")
		{//cout<<endl<<"in if thing";
			missing_endifs++;
			missing_thens++;
			array_of_missing_endifs[linenumber-1] = 1;
			array_of_missing_thens[linenumber-1] = 1;
			
		}
		else if(current_str=="elsif")
		{//cout<<endl<<"in elsif thing";
			//array_of_missing_endifs[linenumber-1] = 1;
			array_of_missing_thens[linenumber-1] = 1;
			missing_thens++;
		}
		else if(current_str=="end")
		{
			
			Token *next = nullptr;
			next = current_token->getNext();
			if(next)
				temp_str = tolowercase(next->getStringRep());	
			int lnumber = -1;
			string str2 = "\0";
			string str3 = "\0";
			Token* t1 = prev_token;
			if(temp_str=="if")
			{	//cout<<endl<<"one less endif missing";
				
				string str1 = tolowercase(prev_token->getStringRep());
				
				
				while(prev_token && str1!="if")
				{ 
					if(str1=="if") break;
					prev_token  = prev_token->getPrev();
					if(prev_token) str1 = tolowercase(prev_token->getStringRep());
				}
				t1 = prev_token;
				while(str1=="if" && t1)
				{
					str2 = t1->getStringRep();
					if(str2=="\n")
					{
						if(t1->getNext())
						{
							str3 = t1->getStringRep();
							lnumber = atoi(str3.c_str());
						}
					}

					else if(numberoflines==1)
					{
						str3 = t1->getStringRep();
						lnumber = atoi(str3.c_str());
							//cout<<endl<<"str3= "<<str3;
					}
					t1 = t1->getPrev();
				}
//cout<<"lnumber for not missing end if:"<<lnumber;
				if(lnumber>0) array_of_missing_endifs[lnumber-1] = 0;

				missing_endifs--;
				//current_token = current_token->getNext();
			}

		}
		else if(current_str=="then")
		{//cout<<endl<<"one less then missing";
			int lnumber = -1;
			string str2 = "\0";
			string str3 = "\0";
			Token* t1 = prev_token;
			string str1 = tolowercase(prev_token->getStringRep());
				
				
				while(prev_token && (str1!="if" || str1!="elsif"))//!(str1=="if" || str1=="elsif"))
				{ 
					//cout<<endl<<str1;
					if(str1=="if" || str1=="elsif") break;
					prev_token  = prev_token->getPrev();
					if(prev_token) str1 = tolowercase(prev_token->getStringRep());
				}//cout<<endl<<"str1: "<<str1;

				t1 = prev_token;
				while((str1=="if" || str1=="elsif") && t1)
				{
					str2 = t1->getStringRep();
					//cout<<endl<<"str2: "<<str2;
					if(str2=="\n")
					{
						if(t1->getNext())
						{
							str3 = t1->getStringRep();
							lnumber = atoi(str3.c_str());
							//cout<<endl<<"str3= "<<str3;
						}
					}
					else if(numberoflines==1)
					{
						str3 = t1->getStringRep();
							lnumber = atoi(str3.c_str());
							//cout<<endl<<"str3= "<<str3;

					}
					t1 = t1->getPrev();
				}
			//cout<<endl<<"lnumber for not missing then: "<<lnumber;
			if(lnumber>0) array_of_missing_thens[lnumber-1] = 0;
			//array_of_missing_thens[linenumber-1] = 0;
			
			missing_thens--;
		}
		prev_token = current_token;
		prev_str = current_str;
		current_token = current_token->getNext();
	}

	Token* t=temp_head;
	int k=0;
	//cout<<endl<<"lines with error: "<<endl;
	/*k=0;
	cout<<endl<<"number of lines: "<<numberoflines;
	cout<<endl<<"   Is then missing?  Is endif missing?";
	while(k<numberoflines)
	{
		cout<<endl<<k<<" "<<array_of_missing_thens[k]<<" "<<array_of_missing_endifs[k];
		k++;
	}
	while(k<numberoflines)
	{
		if(array_of_missing_endifs[k]==1 || array_of_missing_thens[k]==1)
			cout<<k<<" ";
		k++;
	}
*/
	for(k=0,t=temp_head; k<numberoflines && t!=nullptr; k++,t=t->getNext())
	{
		if(array_of_missing_thens[k]==1)
		{
			Token* parser = t;
			cout<<endl<<"Missing \"then\" in line "<<k+1<<": "<<endl;
			while(parser && parser->getStringRep()!="\n")
			{
				cout<<parser->getStringRep()<<" ";
				parser = parser->getNext();
			}
		}
		if(array_of_missing_endifs[k]==1)
		{
			Token* parser = t;
			cout<<endl<<"Missing \"end if\" in line "<<k+1<<": "<<endl;
			while(parser && parser->getStringRep()!="\n")
			{
				cout<<parser->getStringRep()<<" ";
				parser = parser->getNext();
			}
		}
	}
	cout<<endl<<"The number of missing \"end if\"s: "<<missing_endifs;
	cout<<endl<<"The number of missing \"then\"s: "<<missing_thens<<endl;

	return;

}

//finds and prints the number of type and width mismatch in conditional expressions
//inputs the tokenlist containing all conditional expressions produced in findAllConditionalExpressions function
void TypeandWidthMismatchChecking(TokenList& tokenList)
{
	Token* temp_head = tokenList.getFirst();
	Token* current_token = nullptr;
	string current_str = "\0";
	int type_mismatch = 0;
	int width_mismatch = 0;
	bool isVector = false;
	bool isSignalorVariable = false;

	//tokenType current_token_type1
	string current_token_type2 = "\0";
	int current_token_width = 0;
	tokenDetails* current_token_details = nullptr;

	Token* comparingToken = nullptr;
	string comparingToken_type2 = "\0";
	tokenDetails* comparingToken_details = nullptr;
	int comparingToken_width = 0;

	Token* parser1 = nullptr;
	Token* parser2 = nullptr;

	if(temp_head==nullptr)//empty list
	{
		return;
	}

	/*current_token = temp_head;
	cout<<endl<<"input token list: "<<endl;
	while(current_token)
	{
		cout<<current_token->getStringRep()<<endl;
		current_token = current_token->getNext();
	}*/

	current_token = temp_head;
	while(current_token!=nullptr)
	{
		//getting current token details
		current_str = current_token->getStringRep();
		//current_token_type1 = current_token->getTokenType();
		current_token_details = current_token->getTokenDetails();
		//cout<<endl<<"current_str: "<<current_str;
		//cout<<endl<<"does current_token_details exist? "<<(!(current_token_details==nullptr));
		fflush(stdout);
		if( current_token_details!=nullptr)
		{
			isSignalorVariable = true;
			current_token_width = current_token_details->width;
			current_token_type2 = current_token_details->type;
			if(current_token_width!=0)
				isVector = true;
		}


		//if(current_token_type==T_Identifier)
		if(isSignalorVariable)
		{
			//getting the token the current token is being compared to
			comparingToken= (current_token->getNext());
			if(comparingToken) comparingToken = comparingToken->getNext();
			//cout<<endl<<"current_str: "<<current_str;
			if(comparingToken)
			//cout<<endl<<"comparing str: "<<comparingToken->getStringRep();
			if(comparingToken!=nullptr)
			{
				//comparingToken_type = comparingToken->getTokenType();
				/*if(!( (comparingToken_type== T_Literal) || (comparingToken_type==T_Identifier) ) )
				{
					type_mismatch++;
				}*/
				comparingToken_details = comparingToken->getTokenDetails();
				if(comparingToken_details==nullptr)
				{
					//later
				}
				if(comparingToken_details)
				comparingToken_type2 = comparingToken_details->type;

				//cout<<endl<<"type of current token: "<<current_token_type2;
				//cout<<endl<<"type of comparing token: "<<comparingToken_type2;
				fflush(stdout);
				if(comparingToken_type2!=current_token_type2)
				{
					parser2 = current_token;//->getPrev();
					while(parser2 && parser2->getStringRep()!="\n")
					{
						parser1 = parser2;
						parser2 = parser2->getPrev();

					}
					cout<<endl;
					while(parser1 && parser1->getStringRep()!="\n")
					{
						cout<<parser1->getStringRep()<<" ";
						parser1 = parser1->getNext();
					}
					cout<<"-- Type Mismatch for "<<current_str<<" with "<<comparingToken->getStringRep()<<endl;

					//cout<<endl<<"TYPE MISMATCH!";	
					type_mismatch++;
				}
				else if(isVector) //need to check for width mismatch if current token is a vector
				{
					comparingToken_width = comparingToken_details->width;
					//cout<<endl<<"current token width: "<<current_token_width;
					//cout<<endl<<"comparing token width: "<<comparingToken_width;
					if(comparingToken_width!=current_token_width)
					{
						//cout<<endl<<"WIDTH MISMATCH!";
						parser2 = current_token;//->getPrev();
						while(parser2 && parser2->getStringRep()!="\n")
						{
							parser1 = parser2;
							parser2 = parser2->getPrev();

						}
						cout<<endl;
						while(parser1 && parser1->getStringRep()!="\n")
						{
							cout<<parser1->getStringRep()<<" ";
							parser1 = parser1->getNext();
						}
						cout<<"-- Width Mismatch for "<<current_str<<" with "<<comparingToken->getStringRep()<<endl;
						width_mismatch++;
					}
					//comparingToken_details = comparingToken->getTokenDetails();
					//if( (comparingToken_details==nullptr) || )
				}
			}
			current_token = comparingToken;
		}

		if(current_token)
		current_token = current_token->getNext();

		isSignalorVariable = false;
		isVector = false;

	}

	cout<<endl<<"The number of type mismatches: "<<type_mismatch;
	cout<<endl<<"The number of width mismatches: "<<width_mismatch<<endl;

	return;
}

//Takes in tokenList for which the details are already set (by findAndSetTokenDetials function)
//assumes correct syntax for the VHDL file
//Finds identifiers that are declared as constant and replace all occurrences of a given constant with its value & width if its a vector
void bonusConstantDeclarationSupport(TokenList& tokenList)
{
	Token* temp_head = tokenList.getFirst();

	Token* prev_token = nullptr;
	string prev_str = "\0";

	Token* current_token = nullptr;
	string current_str = "\0";
	tokenType current_token_type;
	//tokenDetails* current_token_details;

	Token* token_value = nullptr;
	string token_value_str = "\0";

	Token* temp_token = nullptr;
	string temp_str = "\0";
	string token_type_str = "\0";
	Token* identifier_width1 =  nullptr;
	Token* identifier_width2 = nullptr;
	int  token_width1 = 0;
	int  token_width2 = 0;
	int tokenwidth = 0;

	Token* tokenlist_parser = nullptr;


	if(temp_head==nullptr)//empty list
	{
		return;
	}

	//current_token = temp_head;
	prev_token = temp_head;
	current_token = prev_token->getNext();

	while(current_token && current_token->AreTokenDetailsSet())
	{
		//getting current and previous token details
		prev_str = tolowercase(prev_token->getStringRep());
		current_token_type = current_token->getTokenType();
		//current_token_details = current_token->getTokenDetails();

		//finding a constant identifier
		if( current_token_type==T_Identifier && prev_str=="constant")
		{
			temp_token = current_token->getNext();
			if(temp_token) temp_str = temp_token->getStringRep();

			//finding value of the current token if its a constant identifier
			//assuming constant <name> : <type> := <value>;
			//     or  constant <name> : <type> ;
			//     or  constant <name> : <type>(# downto/to #);
			//     or  constant <name> : <type>(# downto/to #) := <value>; (for std_logic_vector)
			while(temp_token  && temp_str!=";")//if the line ends at ";" before getting ":=" - token doesnt have a value //&& temp_str!=":="
			{
				//temp_token = temp_token->getNext();
				//if(temp_token) 
				temp_str = temp_token->getStringRep();
				//token_type_str = (temp_token->getNext())->getStringRep();
				if(temp_str == ":")
				{
	                //getting identifier type: integer/std_logic/etc..
	                temp_token = temp_token->getNext();
	                if(temp_token)
	                {
	                    token_type_str = tolowercase(temp_token->getStringRep()); //stores <type> 

	                    //getting token width if its a vector
	                    temp_token = temp_token->getNext();
	                    temp_str = temp_token->getStringRep();
	                    if(temp_token && temp_str == identifier_vectorcheck) //checking if the next token is "("
	                    {

	                        //this identifier will be a vector type
	                        identifier_width1 = temp_token->getNext();

	                        if(identifier_width1) identifier_width2 = (identifier_width1->getNext());
	                    	if(identifier_width2) identifier_width2 = identifier_width2->getNext();

	                        //converting the width strings to integers
	                        if(identifier_width1) token_width1 = atoi( (identifier_width1->getStringRep()).c_str() );

	                        if(identifier_width2) token_width2 = atoi( (identifier_width2->getStringRep()).c_str() );

	                        //storing vector width
	                        tokenwidth = abs(token_width1-token_width2)+1;
	                        //cout<<endl<<"upper limit of token width = "<<token_width1;
	                        //cout<<endl<<"lower limit of token width = "<<token_width2;
	                        //cout<<endl<<"tokenwidth is "<<tokenwidth;
	                    }

	                }
	                current_token->setTokenDetails(token_type_str,tokenwidth);
            	}


            	if(temp_token && temp_str==":=") //the token next to temp will be the value of the current_token
				{
					token_value = temp_token->getNext();
					if(token_value) token_value_str = tolowercase(token_value->getStringRep());
					if(token_value_str!= "\0")
					{
	                    current_str = tolowercase(current_token->getStringRep());
	                    current_token->setStringRep(token_value_str);//Replacing the token with its value
	                   // cout<<endl<<"Identifier "<<current_str<<" is being set to "<<token_value_str<<endl;

	                    //replacing each occurence of this token with its value
	                    //for(temp_token = current_token; temp_token)
	                    for(tokenlist_parser = current_token->getNext(); tokenlist_parser!=nullptr; tokenlist_parser= tokenlist_parser->getNext())
						{
							string str1 = tolowercase(tokenlist_parser->getStringRep());
							if(str1==current_str)
							{
								tokenlist_parser->setStringRep(token_value_str);
								tokenlist_parser->setTokenDetails(token_type_str,tokenwidth);
					
							}

						}

					}
				}
       

                if(temp_token)
                	temp_token = temp_token->getNext();
			}

		}

		prev_token = current_token;
		current_token = current_token->getNext();

	}

	return;
}

//Takes in token list for which all token details have been set
//assumes that each line of code is separated by "\n"
/*void ErrorPrinting(TokenList &tokenList)
{
	Token* temp_head = tokenList.getFirst();
	Token* current_token = nullptr;
	string current_str = "\0";
	Token* tokenlist_parser = nullptr;
	TokenList line;
	string prev_str = "\0";

	if(temp_head==nullptr)
	{
		cout<<endl<<"empty list!";
		return;
	}

	for(tokenlist_parser = temp_head; tokenlist_parser!=nullptr; tokenlist_parser = tokenlist_parser->getNext())
	{
		prev_str = current_str;
		current_str = tolowercase(tokenlist_parser->getStringRep());
		current_token = tokenlist_parser;
		while( prev_str=="\n" && ((current_token->getStringRep())!="\n") )
		{
			line.append(current_token);
			current_token = current_token->getNext();
		}




	}
		





}*/
