//Use only the following three libraries:
#include "parserClasses.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <sstream>
//#include <cstdlib>
using namespace std;


//Example Test code for interacting with your Token, TokenList, and Tokenizer classes
//Add your own code to further test the operation of your Token, TokenList, and Tokenizer classes
int main() {
	ifstream sourceFile;
	TokenList tokens;

	


	//ifstream errorPrintingFile;
	//TokenList error_tokenlist;
	/*Tokenizer error_tokenizer;
	int flag = 0;

	errorPrintingFile.open("test1.vhd");
	if(!errorPrintingFile.is_open())
	{
		cout<<endl<<"failed to open file"<<endl;
		return;
	}

	while(!errorPrintingFile.eof())
	{
		string line;
		getline(errorPrintingFile,line);

		error_tokenizer.setString(&line);
		while(!error_tokenizer.isComplete())
		{
			error_tokenlist.append(error_tokenizer.getNextToken());
			flag = 1;
		}
		if(flag==1)
		{
			Token* error_parser = error_tokenlist.getFirst();
			while(error_parser)
			{
				error_tokenlist.findAndSetTokenDetails(error_parser);
				error_parser = error_parser->getNext();
			}
			ErrorPrinting(error_tokenlist);
		}
			

	}*/

  //Lists for types of tokens
  TokenList operatorTokens;
  TokenList identifierTokens;
  TokenList literalTokens;
  TokenList commentBodyTokens;
  TokenList otherTokens;
  int numberofConditionalExpressions = 0;
	Tokenizer tokenizer;
   TokenList error_tokenlist;
   string nexttoken = "\0";
   int j = 0;
   string str2 = "\0";
   //stringstream ss;//create a stringstream
  
   //char *str1 = nullptr;
   //
 // TokenList test;

	
	//str1 = itoa(j);
	//str1 = itoa(j,str1,10);
	//		if(str1) str2 = string(str1);
			//cout<<endl<<"str2: "<<str2;


	//Read in a file line-by-line and tokenize each line
	sourceFile.open("test1.vhd");
	if (!sourceFile.is_open()) {
		cout << "Failed to open file" << endl;
		return 1;
	}

	while(!sourceFile.eof()) {
		string line;
		getline(sourceFile, line);

		tokenizer.setString(&line);
		if(!tokenizer.isComplete())
		{
			j++;
			stringstream ss;
			//str1 = itoa(j);
			//if(str1) str2 = string(str1);
			 ss << j;//add number to the stream
   			str2 = ss.str();//return a string with the contents of the stream
			
		//	error_tokenlist.append("line");
			error_tokenlist.append(str2);

		}
		
		while(!tokenizer.isComplete()) {
			nexttoken = tokenizer.getNextToken();
			//tokens.append(tokenizer.getNextToken());
			tokens.append(nexttoken);
			error_tokenlist.append(nexttoken);
		}
		error_tokenlist.append("\n");
	}


	/*Test your tokenization of the file by traversing the tokens list and printing out the tokens*/
	Token *t = tokens.getFirst();
	while(t) {
		cout << t->getStringRep() << " ";
		t = t->getNext();
	}

	t = error_tokenlist.getFirst();
	while(t) {
		cout << t->getStringRep() << " ";
		t = t->getNext();
	}

//cout<<endl<<"here";
  /* For your testing purposes only */


  /* Ensure that tokens have all type information set*/



  /* Create operator,identifier,literal, etc. tokenLists from the master list of tokens */
	for(Token* temp_ptr = tokens.getFirst();temp_ptr!=nullptr; temp_ptr = temp_ptr->getNext())
	{
		//cout<<endl<<"before";
		tokens.findAndSetTokenDetails(temp_ptr);
		//error_tokenlist.findAndSetTokenDetails(temp_ptr);
		//cout<<endl<<"after"<<endl;
		Token *temp = new Token(*temp_ptr);
		if(temp->isOperator())
			operatorTokens.append(temp);

		else if(temp->isIdentifier())
			identifierTokens.append(temp);

		else if(temp->isLiteral())
			literalTokens.append(temp);

		else if(temp->isComment())
			commentBodyTokens.append(temp);

		else if(temp->isOther())
			otherTokens.append(temp);

	}

/*
t = tokens.getFirst();
while(t)
{
	cout<<endl<<t->getStringRep()<<" is of type "<<t->getTokenType();
	t = t->getNext();
}
*/

t = operatorTokens.getFirst();
cout<<endl<<"Operators found in test file are:"<<endl;
while(t)
{
	cout<<t->getStringRep()<<endl;
	t = t->getNext();
}



t = identifierTokens.getFirst();
cout<<endl<<"Identifiers found in test file are:"<<endl;
while(t)
{
	cout<<t->getStringRep()<<endl;
	t = t->getNext();
}


Token *t2 = literalTokens.getFirst();
cout<<endl<<"Literals found in test file are:"<<endl;
while(t2)
{
	cout<<t2->getStringRep()<<endl;
	t2 = t2->getNext();
}


t = commentBodyTokens.getFirst();
cout<<endl<<"Comment Bodies found in test file are:"<<endl;
while(t)
{
	cout<<t->getStringRep()<<endl;
	t = t->getNext();
}


t = otherTokens.getFirst();
cout<<endl<<"Other tokens found in test file are:"<<endl;
while(t)
{
	cout<<t->getStringRep()<<endl;
	t = t->getNext();
}


cout<<endl<<"Keywords in the file are: "<<endl;
while(t)
{
	if(t->isKeyword())
		cout<<t->getStringRep()<<endl;
	t = t->getNext();
}


//***PART2 TESTING***

TokenList* test = nullptr;
test = findAllConditionalExpressions(tokens);

//cout<<endl<<"tested";
//fflush(stdout);

Token* test2 =nullptr;
if(test) test2 = test->getFirst();


cout<<endl<<"Conditional expressions in this file are: "<<endl;
while(test2)
{
	cout<<test2->getStringRep()<<" ";
	test2 = test2->getNext();
}

//***PART3 TESTING***
if(test) test2 = test->getFirst();
//int k = 0;
while(test2)
{//cout<<endl<<"here"<<++k;
	if(test2->getStringRep() == "\n") numberofConditionalExpressions++;	
	test2 = test2->getNext();
}
//cout<<endl<<"Non-Verbose Mode: "<<endl;
cout<<endl<<"The number of tokens: "<<tokens.getnumberoftokens();
cout<<endl<<"The number of conditional expressions: "<<numberofConditionalExpressions;
ConditionalErrorChecking(tokens);
if(test) TypeandWidthMismatchChecking(*test);

//cout<<endl<<"Verbose Mode: "<<endl;

//***ERROR PRINTING***

ConditionalErrorChecking(error_tokenlist);

//***BONUS TASK TESTING***
bonusConstantDeclarationSupport(tokens);
t = tokens.getFirst();
cout<<endl<<endl<<"token list with constant declaration support: "<<endl;
while(t)
{
	cout<<t->getStringRep()<<" ";
	t = t->getNext();
}
cout<<endl;
//delete test; 
//test = nullptr;
//test = findAllConditionalExpressions(tokens);
//if(test) TypeandWidthMismatchChecking(*test);

delete t;
delete test2;
delete test;

	return 0;
}
