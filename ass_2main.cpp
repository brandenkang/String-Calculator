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
#include "ass_2header.h"

using namespace std;

// map<string,string> expressionTable;
// map<string,float> symbolTable;
// vector<string> variablesAndExpressions;
// vector<string> infixToPostfix(string x);
// float evaluate(vector<string> postfixvector);
// void readFileAndStore(string fileName);
// double inf = std::numeric_limits<double>::infinity();

int main(int count, char* args[]) {
	string filename = "";
	string outfilename = "";
	int wordcount=-1;

	for(int i=1; i<count; i++){
		if((string(args[i])=="-i") && i+1 < count)
			filename=args[i+1];
		else if ((string(args[i])=="-o") && i+1<count)
			outfilename=args[i+1];
	}

	if (filename == "" ){ 
		cout<<"mymachine-promt >> ./mycalc -i <inputfile> -o <outfile>"<<endl;
		return -1;
	}

	vector<string> postfixvector; 
	string s;
	float a; 
	readFileAndStore(filename);

/*
	map<string, string>::iterator it;

	for ( it = expressionTable.begin(); it != expressionTable.end(); it++ )
	{
	    std::cout << it->first  // string (key)
	              << ':'
	              << it->second   // string's value 
	              << std::endl ;
	}
*/
	int size = variablesAndExpressions.size();
	for (int i = 0; i<variablesAndExpressions.size(); i++) {
		s = expressionTable.find(variablesAndExpressions[i])->second;
		// cout<<"S is "<<s<<endl; 
		postfixvector = infixToPostfix(s); 
	
		// for (int i=0; i<postfixvector.size(); i++){
		// 	cout << postfixvector.at(i) << ", "; 
		// }

		cout << endl;

		a = evaluate(postfixvector); 
		if (a==inf) {
			variablesAndExpressions.push_back(variablesAndExpressions[i]); 
		}
		else {
			symbolTable[variablesAndExpressions[i]] = a; 
		}
		// if infinity, convert into infix or string and push back what were evaluating 
		// if else, change the value 
	}
	for (int i =0; i<size; i++) {
		cout << variablesAndExpressions[i] << " = " << symbolTable.find(variablesAndExpressions[i])->second << endl;
		// cout << postfixvector[i];
	}
}

// void readFileAndStore(string fileName) { 
// 	ifstream infile(fileName);
// 	if(infile.is_open()) {
// 		string line;	
// 		while (getline(infile, line)) { //for every line 
// 			for(int i=0; i<line.length(); i++) //remove whitespace
//      			{if(line[i] == ' ') line.erase(i,1);}
//      		for (int i=0; i<line.length(); i++) //remove semicolon 
//      			{if(line[i] == ';') line.erase(i,1);} 
//      		int i = 0; //convert mod to m 
// 			while (i+2 < line.length()) {
// 				if (line[i] == 'm' && line.substr(i,3) == "mod") 
// 				{line.erase(i+1, i+2);}
// 				i++;
// 			}
// 			i = line.find('=');
// 			string variable = line.substr(0,i);
//      		string expression = line.substr(i+1);
//      		// cout << "variable is " << variable << " expression is " << expression << endl;
//      		variablesAndExpressions.push_back(variable);
//      		// variablesAndExpressions.push_back(expression);
//      		expressionTable[variable] = expression; //store variable  and expression //use a vector instead
//      		symbolTable[variable] = inf;
// 		}
// 		infile.close();
// 	}
// }

// //2 convert infix notation to postfix notation in order to evaluate it 
// //helper methods 
// //check to see if char is operator 
// bool isOperator(char ch)
// {
// 	if( ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='%' || ch=='m' || ch=='&' || ch=='$' || ch=='#' || ch=='@' || ch=='!') 
// 		return true;
// 	else
// 		return false;
// }

// //convert operators into int to compare precendence 
// int convertOpToInt (char ch)
// {
//     if (ch=='+' || ch=='-') return 1;
//     if (ch=='*' || ch=='/' || ch=='%' || ch=='m') return 2;  
//     if (ch=='&' || ch=='$' || ch=='#' || ch=='@'  || ch=='!') return 3;
//     return 0;
// }
// //compare operators and return true if first operator has less or equal precedence than right operator
// bool isleq(char opA, char opB)
// {
// 	return (convertOpToInt(opA)<=convertOpToInt(opB));
// }

// //convert infix to postfix 
// vector<string> infixToPostfix(string x)
// {
// 	stack <char> mystack;
// 	string y=""; //postfix expression 
// 	// x=""; //infix expression 
// 	vector<string> postfixvector; //postfix expression 
// 	string z = "";
// 	//Push “(“onto Stack, and add “)” to the end of X.
// 	x=x+')';
// 	mystack.push('(');

// 	//Scan X from left to right and repeat Step 3 to 6 for each element of X until the Stack is empty.
// 	int i=0;
// 	while(!mystack.empty())
// 	{	
// 		char ch = x[i];
// 		//If an operand is encountered, add it to Y.
// 		if (isalnum(ch)) {
// 			y=y+ch, z=z+ch;
// 			while (i+1 < x.length() && isalnum(x[i+1])) {
// 				z=z+x[i+1];
// 				i++;
// 			}
// 			postfixvector.push_back(z);
// 		}
// 		//If a left parenthesis is encountered, push it onto Stack.
// 		else if (ch=='(') {
// 			mystack.push(ch);
// 		}
// 		//if it is a unary (-a)
// 		else if (ch == '-' &&  x[i-1] =='(') {
// 			// mystack.push('!');
// 			y+= "-";
// 			z+= "-";
// 			while (i+1 < x.length() && isalnum(x[i+1])) {
// 				// get all the numbers;
// 				y += x[i+1];
// 				z += x[i+1];
// 				i++;		
// 			}
// 			postfixvector.push_back(z);
// 			// y+= mystack.top();
// 			// z+= mystack.top();
// 			// mystack.pop();
// 		}

// 		//if it is an operator: 
// 		else if (isOperator(ch))  {
// 			//if it is a unary (-)
// 		 	if (ch == '-' && i-1 >= 0 && !isalnum(x[i-1]) && i+1 < x.length() &&  isalnum(x[i+1])) {
// 				// mystack.push('!');
// 				y+="-";
// 				z+="-";
// 				while (i+1 < x.length() && isalnum(x[i+1])) {
// 					y+= x[i+1];
// 					z+= x[i+1];
// 					// y+= mystack.top();
// 					// mystack.pop();
// 					i++;
// 				}
// 				postfixvector.push_back(z);
// 		 	}
// 			//if it is a unary operator:	
//  			else if (isOperator(x[i+1]) || x[i-1]=='(') {
//  				if (x[i+1] == '*')
//  					mystack.push('&');
//  				else if (x[i+1] ==  '+')
//  					mystack.push('$');
//  				else if (x[i+1] == '-') 
//  					mystack.push('@');
// 	 			// while (i+2 < x.length() && isalnum(x[i+2])){
// 	 			// 	y+= x[i+2];
// 	 			// 	z+= x[i+2];
// 	 			y+= mystack.top();
// 	 			z+= mystack.top();
// 	 			postfixvector.push_back(z); 
// 	 			mystack.pop();
//  			} 

// 			else { //if it is a  binary operator
// 				//a.	Repeatedly pop from Stack and add to Y each operator (on the top of Stack) 
// 				//which has the same precedence as or higher precedence than operator.
// 				while (isOperator(mystack.top()) and isleq(ch,mystack.top()))
// 				{
// 					y=y+mystack.top();
// 					z=z+mystack.top();
// 					postfixvector.push_back(z);
// 					mystack.pop();
// 				}
// 				//b.	Add operator to Stack.
// 				mystack.push(ch);
// 			}	
// 		}
// 		//If a right parenthesis is encountered, then: 
// 		else if(ch==')')
// 		{
// 			//a.	Repeatedly pop from Stack and add to Y each operator 
// 			//(on the top of Stack) until a left parenthesis is encountered.
// 			while(mystack.top()!='(')
// 			{
// 				y+=mystack.top();
// 				z+=mystack.top();
// 				postfixvector.push_back(z);
// 				mystack.pop();
// 			}
// 			//b.	Remove the left Parenthesis.
// 			mystack.pop();
// 		}
// 		z = ""; 
// 		i++;	
// 	}
// 	return postfixvector;
// }

// //checks if string is numbers
// bool onlyDigit(string s) {
// 	for (int n = 0; n<s.length(); n++){
// 		if (!isdigit(s[n])) {return false;}
// 		else {return true;}
// 	}
// }

// //checks if string is alphabets
// bool onlyString(string s) {
// 	for (int n = 0; n<s.length(); n++) {
// 		if (!isalpha(s[n])) {return false;}
// 		else {return true;}
// 	}
// }

// //Method which will evaluate a PostfixExpression and return the result
// float evaluateBinary(string c, float a, float b)		
// {	
// 	switch(c[0])			
// 	{
// 		case '+': return (b+a); break;
// 		case '-': return (b-a); break;
// 		case '*': return (b*a); break;
// 		case '/': return (b/a); break;
// 		case '%': return (static_cast<int>(b/a)); break; //integer division
// 		case 'm': return (static_cast<int>(b)%static_cast<int>(a)); break; //mod
// 	}
// 	return 0;				
// }

// float evaluateUnary(string c, float a)
// {
// 	switch(c[0])
// 	{
// 		case '&': return(a*a); break;
// 		case '$': return(a+1); break;
// 		case '@': return(a-1); break;
// 		case '!': return(0-a); break;
// 	}
// 	return 0;
// }

// float evaluate(vector<string> postfixvector)
// {
// 	double inf = std::numeric_limits<double>::infinity();
// 	stack <float> myStack;				//Create a stack of type float to store the operands
// 	for (int i = 0; i<postfixvector.size(); i++) {
// 		string token = postfixvector.at(i);
// 		if (onlyDigit(token)) {
// 			myStack.push(stoi(token)); //if the token is an operand push it to the stack
// 		}
// 		// else if (convertOpToInt(token) == 1 || convertOpToInt(token) == 2)
// 		else if (token.find('+'|'-'|'*'|'/'|'%'|'m')!=std::string::npos)
// 		{
// 			float a = myStack.top(); myStack.pop();
// 			float b = myStack.top(); myStack.pop();
// 			float c = evaluateBinary(token, a, b);
// 			myStack.push(c);
// 		}
// 		// else if (convertOpToInt(token) == 3)
// 		else if (token.find('&'|'$'|'#'|'@'|'!') != std::string::npos) 
// 		{
// 			float a = myStack.top(); myStack.pop();
// 			float c = evaluateUnary(token, a);
// 			myStack.push(c);
// 		}
// 		else if (onlyString(token)) {
// 			if (symbolTable.count(token) < 0 || symbolTable[token] == inf) { //if token not in map or if we haven't seen it yet
// 				return inf; //set expression (c) as infinity
// 				//later when we see this token, somehow come back to this expression (c) // in the main
// 			}
// 			else { //if token is defined then we get the value of it from the map and put it in the stack and continue along 
// 			// assuming both a and b are defined 
// 			// if a is defined then we get the value of a from the map and put it in the stack and continue along 
// 			// one extra step before pushing it into stack 
// 				myStack.push(symbolTable[token]); 
// 			}
// 		}
// 	}
// 	return myStack.top();
// }































