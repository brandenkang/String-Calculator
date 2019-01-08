#include<iostream>
#include<cstdlib>
#include<string>
#include<cmath>
#include<stack>
#include<vector>
#include<string>
#include<map>
#include<fstream>
#include<limits>

using namespace std;

map<string,string> expressionTable;
map<string,float> symbolTable;
vector<string> variablesAndExpressions;
vector<string> infixToPostfix(string x);
float evaluate(vector<string> postfixvector);
void readFileAndStore(string fileName);
double inf = std::numeric_limits<double>::infinity();


void readFileAndStore(string fileName) { 
	ifstream infile(fileName);
	if(infile.is_open()) {
		string line;	
		while (getline(infile, line)) { //for every line 
			for(int i=0; i<line.length(); i++) //remove whitespace
     			{if(line[i] == ' ') line.erase(i,1);}
     		for (int i=0; i<line.length(); i++) //remove semicolon 
     			{if(line[i] == ';') line.erase(i,1);} 
     		int i = 0; //convert mod to m 
			for (i = 0; i+2 < line.length(); i++) {
				if (line[i] == 'm' && line.substr(i,3) == "mod") {
					line.erase(i, 3); 
					line.insert(i, "~");
				}
				// i++;

			}
			i = line.find('=');
			string variable = line.substr(0,i);
     		string expression = line.substr(i+1);
     		// cout << "variable is " << variable << " expression is " << expression << endl;
     		variablesAndExpressions.push_back(variable);
     		// variablesAndExpressions.push_back(expression);
     		expressionTable[variable] = expression; //store variable  and expression //use a vector instead
     		symbolTable[variable] = inf;
		}
		infile.close();
	}
};


//helper methods 
//check to see if char is operator 
bool isOperator(char ch)
{
	if( ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='%' || ch=='~' || ch=='&' || ch=='$' || ch=='#' || ch=='@' || ch=='!') 
		return true;
	else
		return false;
};

//convert operators into int to compare precendence 
int convertOpToInt (char ch)
{
    if (ch=='+' || ch=='-') return 1;
    if (ch=='*' || ch=='/' || ch=='%' || ch=='~') return 2;  
    if (ch=='&' || ch=='$' || ch=='#' || ch=='@'  || ch=='!') return 3;
    return 0;
};

int convertOpToIntString (string ch)
{
    if (ch=="+" || ch=="-") return 1;
    if (ch=="*" || ch=="/" || ch=="%" || ch=="~") return 2;  
    if (ch=="&" || ch=="$" || ch=="#" || ch=="@"  || ch=="!") return 3;
    return 0;
};
//compare operators and return true if first operator has less or equal precedence than right operator
bool isleq(char opA, char opB)
{
	return (convertOpToInt(opA)<=convertOpToInt(opB));
};

//convert infix to postfix 
vector<string> infixToPostfix(string x)
{
	// cout << "first it's " << x << ", then it's ";
	stack <char> mystack;
	string y=""; //postfix expression 
	// x=""; //infix expression 
	vector<string> postfixvector; //postfix expression 
	string z = "";
	//Push “(“onto Stack, and add “)” to the end of X.
	x=x+')';
	mystack.push('(');

	//Scan X from left to right and repeat Step 3 to 6 for each element of X until the Stack is empty.
	int i=0;
	// cout << x << endl;
	while(!mystack.empty())
	{	
		char ch = x[i];

		//mod  
		if (ch == '~') {
			//a.	Repeatedly pop from Stack and add to Y each operator (on the top of Stack) 
			//which has the same precedence as or higher precedence than operator.
			// cout << "case7" << endl;
			while (isOperator(mystack.top()) and isleq(ch,mystack.top()))
			{

				y=y+mystack.top();
				z=z+mystack.top();
					
				string tmpToken;
				tmpToken.push_back(mystack.top());
				postfixvector.push_back(tmpToken);
				
				mystack.pop();
			}
			//b.	Add operator to Stack.
			mystack.push(ch);
		}

		else if (isalnum(ch)) {
			// cout << "case1" << endl;
			y=y+ch, z=z+ch;
			while (i+1 < x.length() && isalnum(x[i+1])) {
				z=z+x[i+1];
				i++;
			}
			postfixvector.push_back(z);
		}
		//If a left parenthesis is encountered, push it onto Stack.
		else if (ch=='(') {
			// cout << "case2" << endl;
			mystack.push(ch);
		}
		// -74
		// z = -74
		else if (ch=='-' && i-1 < 0 && x[i+1] != '-') {
			// cout << "case3" << endl;
			// in this case if we see -al, we should be pushing (-1 * al)
			// y+= "!";
			z+= "!";
			postfixvector.push_back(z);
			while (i+1 < x.length() && isalnum(x[i+1])) {
				// get all the numbers;

				y += x[i+1];
				z += x[i+1];
				i++;
				// cout << "z: " << z << ", i: " << i << endl;		
			}
			// cout << "ending up with " << z << endl;
			postfixvector.push_back(y);
		}
		//if it is a unary (-a)
		else if (ch == '-' && x[i-1] =='(') {
			// cout << "case4" << endl;
			// mystack.push('!');
			// y+= "-";
			z+= "!";
			postfixvector.push_back(z);
			while (i+1 < x.length() && isalnum(x[i+1])) {
				// get all the numbers;
				y += x[i+1];
				z += x[i+1];
				i++;		
			}
			postfixvector.push_back(y);
			// y+= mystack.top();
			// z+= mystack.top();
			// mystack.pop();
		}

		//check for -(ell)
		else if (ch == '-' && x[i+1] == '(') {
			z+="!";
		postfixvector.push_back(z);
		}

		//if it is an operator: 
		else if (isOperator(ch))  {

			// cout << "case5" << endl;
			// cout << "i is "<< i << endl;
			//if it is a unary (-)
		 	if (ch == '-' && i-1 >= 0 && !isalnum(x[i-1]) && i+1 < x.length() &&  isalnum(x[i+1]) && x[i-1] != ')') {
				// mystack.push('!');
				// y+="-"; 
				z+="!";
				postfixvector.push_back(z);
				while (i+1 < x.length() && isalnum(x[i+1])) {
					y+= x[i+1];
					z+= x[i+1];
					// y+= mystack.top();
					// mystack.pop();
					i++;
				}
				// cout << "z being " << z << endl;
				postfixvector.push_back(y);
		 	}
		 	//check for -** 
		 	// else if (ch == '-' && x[i+1] == '*' && x[i+2] == '*') {
				// //a.	Repeatedly pop from Stack and add to Y each operator (on the top of Stack) 
				// //which has the same precedence as or higher precedence than operator.
				// while (isOperator(mystack.top()) and isleq(ch,mystack.top()))
				// {

				// 	y=y+mystack.top();
				// 	z=z+mystack.top();
					
				// 	string tmpToken;
				// 	tmpToken.push_back(mystack.top());
				// 	postfixvector.push_back(tmpToken);
					
				// 	mystack.pop();
				// }
				// //b.	Add operator to Stack.
				// mystack.push(ch);
		 	// }

			//if it is a unary operator:	
 			else if (isOperator(x[i+1]) || x[i-1]=='(') {
 				// cout << "case6" << endl;
 				if (x[i+1] == '*')
 					mystack.push('&'); //** 
 				else if (x[i+1] ==  '+') 
 					mystack.push('$'); //++
 				else if (x[i+1] == '-') 
 					mystack.push('@'); //--
	 			// while (i+2 < x.length() && isalnum(x[i+2])){
	 			// 	y+= x[i+2];
	 			// 	z+= x[i+2];
	 			y+= mystack.top();
	 			z+= mystack.top();
	 			postfixvector.push_back(z); 
	 			mystack.pop();
	 			if (i-1 < 0){
	 				i++;
	 			}
	 			else {
	 			i+=2;
	 			}
 			} 

			else { //if it is a  binary operator
				//a.	Repeatedly pop from Stack and add to Y each operator (on the top of Stack) 
				//which has the same precedence as or higher precedence than operator.
				// cout << "case7" << endl;
				while (isOperator(mystack.top()) and isleq(ch,mystack.top()))
				{

					y=y+mystack.top();
					z=z+mystack.top();
					
					string tmpToken;
					tmpToken.push_back(mystack.top());
					postfixvector.push_back(tmpToken);
					
					mystack.pop();
				}
				//b.	Add operator to Stack.
				mystack.push(ch);
			}	
		}
		//If a right parenthesis is encountered, then: 
		else if(ch==')')
		{
			//a.	Repeatedly pop from Stack and add to Y each operator 
			//(on the top of Stack) until a left parenthesis is encountered.
			while(mystack.top()!='(')
			{
				y+=mystack.top();
				z+=mystack.top();
				
				string tmpToken;
				tmpToken.push_back(mystack.top());	
				postfixvector.push_back(tmpToken);	

				mystack.pop();
			}
			//b.	Remove the left Parenthesis.
			mystack.pop();
		}
		z = ""; 
		i++;	
	}
	return postfixvector;
};

//checks if string is numbers
bool onlyDigit(string s) {
	for (int n = 0; n<s.length(); n++){
		if (!isdigit(s[n])) {return false;}
		else {return true;}
	}
};

//checks if string is alphabets
bool onlyString(string s) {
	for (int n = 0; n<s.length(); n++) {
		if (!isalpha(s[n])) {return false;}
		else {return true;}
	}
};

// bool unaryMinus(string s) {
// 	if (s.substr(0,1) == '-' && isalpha(s.substr(1,2))) 
// 		{return true;};
// 	else {return false;};
// }

//Method which will evaluate a PostfixExpression and return the result
float evaluateBinary(string c, float a, float b)		
{	
	switch(c[0])			
	{
		case '+': return (b+a); break;
		case '-': return (b-a); break;
		case '*': return (b*a); break;
		case '/': return (b/a); break;
		case '%': return (floor(b/a)); break; //integer division
		case '~': return (int(b)%int(a)); break; //mod
	}
	return 0;				
};

float evaluateUnary(string c, float a)
{
	switch(c[0])
	{
		case '&': return(a*a); break;
		case '$': return(a+1); break;
		case '@': return(a-1); break;
		case '!': return(0-a); break;
	}
	return 0;
};

float evaluate(vector<string> postfixvector)
{
	double inf = std::numeric_limits<double>::infinity();
	stack <float> myStack;				//Create a stack of type float to store the operands
	for (int i = 0; i<postfixvector.size(); i++) {
		string token = postfixvector.at(i);
		// cout << "token: " << token << endl;
		// cout << token << endl;
		if (onlyDigit(token)) {

			myStack.push(stoi(token)); //if the token is an operand push it to the stack
		}


		else if (convertOpToIntString(token) == 1 || convertOpToIntString(token) == 2)
		//else if (token.find('+'|'-'|'*'|'/'|'%'|'m')!=std::string::npos)
		{
			float a = myStack.top(); myStack.pop();
			// cout << " hi " << endl;
			float b = myStack.top(); myStack.pop();
			float c = evaluateBinary(token, a, b);
			myStack.push(c);
		}
		else if (convertOpToIntString(token) == 3)
		//else if (token.find('&'|'$'|'#'|'@'|'!') != std::string::npos) 
		{
			string nextToken = postfixvector.at(i+1);
			if (onlyString(nextToken)) {
				if (/*symbolTable.count(nextToken) < 0 ||*/ symbolTable[nextToken] == inf) { //if token not in map or if we haven't seen it yet
					
					return inf; //set expression (c) as infinity
					//later when we see this token, somehow come back to this expression (c) // in the main
				}
				else { //if token is defined then we get the value of it from the map and put it in the stack and continue along 
				// assuming both a and b are defined 
				// if a is defined then we get the value of a from the map and put it in the stack and continue along 
				// one extra step before pushing it into stack 
					myStack.push(evaluateUnary(token, symbolTable[nextToken]));
					i++; 
				}
			}
			else if (onlyDigit(nextToken)){
				// nextToken is a number
				float a = stoi(nextToken);
				myStack.push(evaluateUnary(token, a));
				i++;
			} 
			// else {
				// cout << "encountered an error" << endl;
			// }

			// float a = myStack.top(); myStack.pop();
			// float a = myStack.top(); myStack.pop();
			// float c = evaluateUnary(token, a);
			// myStack.push(c);
		}
		else if (onlyString(token)) {
			if (/*symbolTable.count(nextToken) < 0 ||*/ symbolTable[token] == inf) { //if token not in map or if we haven't seen it yet
				return inf; //set expression (c) as infinity
				//later when we see this token, somehow come back to this expression (c) //in the main
			}
			else { //if token is defined then we get the value of it from the map and put it in the stack and continue along 
			// assuming both a and b are defined 
			// if a is defined then we get the value of a from the map and put it in the stack and continue along 
			// one extra step before pushing it into stack 
				myStack.push(symbolTable[token]); 
			}
		}
	}
	// cout<<"STOP. evaluated: "<<myStack.top()<<endl;
	return myStack.top();
};











