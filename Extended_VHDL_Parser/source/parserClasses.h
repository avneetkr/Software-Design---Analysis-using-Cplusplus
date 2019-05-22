#ifndef PARSERCLASSES_H_
#define PARSERCLASSES_H_

//Use only the string library DO NOT add any other libraries
#include <string>

using namespace std;


 const string str_delimiters = ",.;:<>[]{}()?/`~!@#$%^&*|-=+";
 const string singlequote = "'";
 const string signal_assignment= "=>"; //this is a token on its own. everything after => until we encounter wny whitespscae_char will be a single token.
 const string signal_assignment1="<=";
 const string comments="--";
 const string whitespace_char=" \t\r";
 const string signal_assignment2=":=";
 const string newline_char = "\n";
 const string signal_assignment3 = "/=";
 const string signal_assignment4 = ">=";
 const string another_operator = "**";
// const string signal_assignment5 = "=<";

 //Keywords possibilities
 const string keywords[97]={ "abs","access","after","alias","all","and","architecture","array","assert","attribute","begin"
				"block","body","buffer","bus","case","component","configuration","constant",
				"disconnect","downto","else","elsif","end","entity","exit","file","for","function",
			     "generate","generic","group","gaurded","if","impure","in","inertial","inout","is",
			      "label","library","linkage","literal","loop","map","mod","nand","new","next","nor",
			      "not","null","of","on","open","or","others","out","package","port","postponed","procedure","process","pure"
			      ,"range","record","register","reject","rem","report","return","rol","ror","select","severity","signal","shared",
			      "sla","sll","srl","sra","subtype","then","to","transport","type","unaffected","units","until","use","variable",
			      "wait","when","while","with","xnor","xor"};
const size_t numberofkeywords = 97;

//LITERAL POSSIBILITIES
 const string literal_vectors = "bBoOxX";
 const char literal_doublequotes = '\"';
 const char literal_singlequotes = '\'';
 const string literal_true = "true";
 const string literal_false = "false";

//OPERATOR POSSIBILITIES
 const string operators[21] = { "*/+-&=<>", "**", "abs", "not", "mod",
 								"rem", "sll", "srl", "sla", "sra", "rol",
 								"ror", "/=", "<=", ">=", "and", "or", "nand",
 								"nor", "xor", "xnor" };
 const size_t numberofoperators = 21;
 /*
 const string operator_exp = ;
 const string operator_abs = ;
 const string operator_not = ;
 const string operator_mod = ;
 const string operator_rem = ;
 const string operator_sll = ;
 const string operator_srl = ;
 const string operator_sla = ;
 const string operator_sra = ;
 const string operator_rol = ;
 const string operator_ror = ;
 const string operator_inequality = ;
 const string operator_lessequal = ;
 const string operator_greaterequal = ;
 const string operator_and = ;
 const string operator_or = ;
 const string operator_nand = ;
 const string operator_nor = ;
 const string operator_xor = ;
 const string operator_xnor = ;
 */

 //IDENTIFIER POSSIBILITIES
 //const string identifier_signalassignment = ":=";
 const string identifier_vectorcheck = "(";
 const string identifier_signal = "signal";
 const string identifier_variable = "variable";
 //const string identifier_vectorcheck1 = "downto";
 //const string identifier_vectorcheck2 = "to";
 //Definiting Literal types
 const string std_logic_vector = "std_logic_vector";
 const string std_logic = "std_logic";
 const string integer = "integer";
 const string boolean = "boolean";


enum tokenType {T_Operator, T_Identifier, T_Literal, T_CommentBody, T_Other};

struct tokenDetails {
  string type; //boolean, std_logic, std_logic_vector, integer etc.
  int width; //bit width for vector types
};

//Declare your variables for storing delimiters here:

//Token class for a doubly-linked list of string tokens
class Token {
private:
	Token *next; //Next pointer for doubly linked list
	Token *prev; //Previous pointer for doubly linked list
	string stringRep; //Token value

  bool _isKeyword; //true if token is a reserved keyword
  tokenType type; //enum that holds the type of the token
  tokenDetails *details; //pointer to tokenDetails struct, owned by this token, only valid if type is T_Literal or  is a T_Identifier and is a variable/signal.  Lazy allocation, only allocated when needed (see setTokenDetails function declaration).
  bool detailsSet;//true if token details are set
  	//Allow TokenList class to access Token member variables marked private
  //https://en.wikipedia.org/wiki/Friend_class
	friend class TokenList;

public:
	//Default Constructor, pointers initialized to NULL, and other variable initialization
  //tokenDetails should NOT be allocated here
	Token() : next(nullptr), prev(nullptr), type(T_Other), details(nullptr), detailsSet(false) {}

	//Constructor with string initialization
	Token(const string &stringRep) : next(nullptr), prev(nullptr), stringRep(stringRep), type(T_Other), details(nullptr), detailsSet(false) {}

  //Copy constructor
  Token(const Token &token);

  //Destructor, free any memory owned by this object
  ~Token();

  //Assignment operator
  void operator =(const Token& token);

	//Returns the Token's *next member
	Token* getNext ( ) const {  return next; }

	//Sets the Token's *next member
	void setNext (Token* next ) { this->next = next; }

	//Returns the Token's *prev member
	Token* getPrev ( ) const { return prev; }

	//Sets the Token's *prev member
	void setPrev (Token* prev ){ this->prev = prev; }

	//Returns a reference to the Token's stringRep member variable
	const string& getStringRep ( ) const { return stringRep; }

	//Sets the token's stringRep variable
	void setStringRep (const string& stringRep ) { this->stringRep = stringRep; }

  //Returns true if token is a keyword
  bool isKeyword () const { return _isKeyword; }

  //Sets isKeyword to true
  void setKeyword() { _isKeyword = true; }

  //Returns the token type
  tokenType getTokenType() const { return type; }

  //Set's the token type
  void setTokenType(tokenType type) { this->type = type; }

  //Returns true if token matches this type
  bool isOperator() const { return (type == T_Operator); }
  //Returns true if token matches this type
  bool isIdentifier() const { return (type == T_Identifier); }
  //Returns true if token matches this type
  bool isLiteral() const { return (type == T_Literal); }
  //Returns true if token matches this type
  bool isComment() const { return (type == T_CommentBody); }
  //Returns true if token matches this type
  bool isOther() const { return (type == T_Other); }

  //Returns a pointer to tokenDetails
  tokenDetails* getTokenDetails() const { return details; }

  //Set's the tokenDetails given a string type and optional vector width
  //Allocates tokenDetails if it doesn't already exist
  void setTokenDetails(const string &type, int width = 0);

  //true if all token details are set
  bool AreTokenDetailsSet() const {return detailsSet;}

};

//A doubly-linked list class consisting of Token elements
class TokenList {
private:
	Token *head; //Points to the head of the token list (doubly linked)
	Token *tail; //Points to the tail of the function list (doubly linked)
	int numberoftokens; //counts number of tokens in the tokenlist

public:
	//Default Constructor, Empty list with pointers initialized to NULL
	TokenList() : head(nullptr), tail(nullptr), numberoftokens(0) { }

	//destructor
	~TokenList();

	//Returns a pointer to the head of the list
	Token* getFirst() const { return head; }

	//Returns a pointer to the tail of the list
	Token* getLast() const { return tail; }

	//Creates a new token for the string input, str
	//Appends this new token to the TokenList
	//On return from the function, it will be the last token in the list
	//increments numberoftokens by 1
	void append(const string &str); //example comment

	//Appends the token to the TokenList if not null
	//On return from the function, it will be the last token in the list
	//increments numberoftokens by 1
	void append(Token *token);

  //Removes the token from the linked list if it is not null
	//Deletes the token
	//On return from function, head, tail and the prev and next Tokens (in relation to the provided token) may be modified.
	//decrements numberoftokens by 1
	void deleteToken(Token *token);

  //find token details and type and update token.  May require examining properties of neighbouring tokens
  void findAndSetTokenDetails(Token *token);

  //returns number of tokens in the tokenlist
  int getnumberoftokens() { return numberoftokens; }






};

//A class for tokenizing a string of VHDL  code into tokens
class Tokenizer {
private:
	/*State tracking variables for processing a single string*/
	bool complete; //True if finished processing the current string

	size_t offset; //Current position in string
	size_t tokenLength; //Current token length
	string *str; //A pointer to the current string being processed

	//Include any helper functions here
	//e.g. trimming whitespace, comment processing

	//Computes a new tokenLength for the next token
	//Modifies: size_t tokenLength, and bool complete
	//(Optionally): may modify offset
	//Does NOT modify any other member variable of Tokenizer
	void prepareNextToken();

public:
	//Default Constructor- YOU need to add the member variable initializers.
	Tokenizer(): complete(false),offset(0), tokenLength(0), str(nullptr){}

	//Sets the current string to be tokenized
	//Resets all Tokenizer state variables
	//Does not Call Tokenizer::prepareNextToken() as the last statement before returning.
	void setString(string *str);

	//Returns true if all possible tokens have been extracted from the current string (string *str)
	bool isComplete() const { return complete; }

	//Returns the next token. Hint: consider the substr function
	//Updates the tokenizer state
	//Updates offset, resets tokenLength, updates processingABC member variables
	//Calls Tokenizer::prepareNextToken() as the last statement before returning.
	string getNextToken();
};


//Removes all comments from the tokenList including the -- marker
//Returns the number of comments removed
int removeComments(TokenList &tokenList);

//Removes all tokens of the given tokenType
//Returns the number of tokens removed
int removeTokensOfType(TokenList &tokenList, tokenType type);


//Creates a new TokenList, and returns a pointer to this list
//Searches for all conditional expressions in tokenList and appends them to the new list
//Format is as follows:
//Each token that is part of a condtional expression is appended sequentially
//At the end of a conditional expression a newline character is appened
   //Example: if (a = true) then
   //Your list should include "(", "a", "=", "true", ")" and "\n"
//tokenList is NOT modified
TokenList* findAllConditionalExpressions(const TokenList &tokenList);

//finds and prints number of missing "endif"s and "then"s in the tokenlist
void ConditionalErrorChecking(TokenList& tokenList);

//finds and prints the number of type and width mismatch in conditional expressions
//inputs the tokenlist containing all conditional expressions produced in findAllConditionalExpressions function
//Also assumes that token details of all the tokens in the list are already set
void TypeandWidthMismatchChecking(TokenList& tokenList);

//Takes in tokenList for which the details are already set (by findAndSetTokenDetials function)
//assumes correct syntax for the VHDL file
//Finds and prints identifiers that are declared as constant and replaces all occurrences of a given constant with its value
//Also allocates details->type (and details->width if its a vector)
void bonusConstantDeclarationSupport(TokenList& tokenList);


#endif /* PARSERCLASSES_H_ */
