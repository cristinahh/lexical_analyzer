#include <iostream>
#include <utility>
#include <vector>
#include <cctype>
#include <fstream>
#include <string>

using namespace std;

//This will store the output, pairs of (token type, value)
vector<pair<string, string > > myVect;

//This will store the characters of the string currently processed by lexer
vector<char> lexeme;

int countNeg = 0; // keeps track of negative signs. Used inside isReal. 
int countDec = 0; // keeps track of decimal signs. Used inside isReal.

//The word is passed here for checking if keyword
bool isKeyword(string word)
{
    if( word == "int" || word == "while" || word == "else" || word == "if" 
     || word == "double"|| word == "string"|| word == "for" || word == "cout")
    {
        return true;
    }

    return false;
}

//The word is passed here for checking if Separator
bool isSeparator(string word)
{
    if( word == "(" || word == ")" || word == ";" )
    {
        return true;
    }
    return false;
}

//The word is passed here for checking if identifier
// this is done by validating word as non-alphanumeric
bool isIdentifier(string word)
{
    if(isalpha(word[0]))
    {
        return true;
    }
    return false;
}

//The word is passed here for checking if Operator
bool isOperator(string word)
{
    
    if(word == "+" || word == "-" || word == "/" || word == "%" || 
    word == "*" || word == "<" || word == ">" || word == ">=" || 
    word == "<=" || word == "==" || word == "="|| word == "++" || 
     word == "<<" || word == "--")
    {
        return true;
    }
    return false;

}

//a loop is ran to determine if the value is negative or unreal. 
//Also checks if number entry is valid by counting '-' and '.'. More than 1 is invalid
bool isReal(string word)
{
    bool isR = true;
    
    for(int i = 0; i < word.length(); i++)
    {
        
        if(isdigit(word[i]) && countNeg < 2  && countDec < 2)
        {

            continue;
        }
        else if( word[i] == '-' && isdigit(word[i+1]))
        {
            countNeg++;
            if(countNeg >1)
            {
                return false;
            }
        }
        else if (word[i] == '.' && isdigit(word[i+1]))
        {
            countDec++;
           
            if(countDec >1)
            {
                return false;
            }
           
        }
        else
        {
            isR = false;
        }
    }
    return isR;
}


//When a token is identified, create
void createPair( string token, string lexeme)
{
    //myVect is the end Output, pairs of token type and value
	myVect.push_back(make_pair(token, lexeme));
}

//The vector to be lexed is passed here & identified
//This is the primary lexing function
void checkToken(vector<char> lexVect)
{
    // This concatenates the vector into a string
    string lexStr(lexVect.begin(), lexVect.end());

    // each string is checked to identify token
    if (isKeyword(lexStr))
    {
        createPair("keyword", lexStr);
    }
    else if (isSeparator(lexStr))
    {
        createPair("separator", lexStr);
    }
    else if (isOperator(lexStr))
    {
        createPair("operator", lexStr);
    }
    else if (isReal(lexStr))
    {
        createPair("real", lexStr);
    }
    else if( isIdentifier(lexStr))
    {
        createPair("identifier", lexStr);
    }
    else 
    {
        cout<< "Not a valid statement"<< endl;
    }
}


// This clears the lexing vector after determination of the specific key
vector<char> clearVect(vector<char>& vect)
{
    int size = vect.size();
    for( int i = 0; i < size; i++)
    {
        vect.pop_back();
    }
    return vect;
}


/* This lexer function acts as a print function. It prints all the tokens 
and lexemes once they are all separated and categorized appropriately.The output is saved in a file called output.txt*/
void lexer(vector<pair<string,string > > vect)
{
    ofstream myFile;
    myFile.open("output.txt");

    for ( int i = 0; i < vect.size(); i++)
    {
        myFile << ( vect[i].first) << ", " << vect[i].second << endl;
    }

    myFile.close();
}

//This function makes the input string something we can actually parse
string stringFix(string input)
{
    vector<char> outputVect;
    
    for (int i = 0; i < input.length(); ++i)
    {   
        if(input[i] == ' ' && i == 0) //gets rid of space if it is in the front of the string
        {
            continue;
        }
        //Alphanumeric & Spaces are Okay to push
        if (isalpha(input[i]))
        {
            if( input[i-1] == '<' || input[i-1] == '>'|| input[i-1] == '+' || input[i-1] == '-')
                outputVect.push_back(' ');

            outputVect.push_back(input[i]);
        }
        
        else if (isdigit(input[i]))
        {
            if( input[i-1] == '<' || input[i-1] == '>'|| input[i-1] == '+' || input[i-1] == '-' || input[i-1] == '*' || input[i-1] == '%' || input[i-1] == '=')
                outputVect.push_back(' ');
     
           outputVect.push_back(input[i]);
        }
        
        else if (input[i] == ' ')
        {
            outputVect.push_back(' ');
        }
        
        
        //This should work for negatives.
        else if(input[i] == '-' && isdigit(input[(i+1)]) && !isdigit(input[i-1]) )
        {
            outputVect.push_back('-');
        }
		
	 // This allows !=, ==, <<, etc statements to be pushed without a space between them
        else if( input[i] == '=' || input[i] == '+' || input[i] == '-' 
        || input[i] == '&'|| input[i] == '|'|| input[i] == '<' || input[i] == '>' || input[i] == '!' || input[i] == '.'  )
	    { 
                if( isalpha(input[i-1]) )
                    outputVect.push_back(' '); 

                 else if ( isdigit(input[i-1]) && input[i] != '.' )
                    outputVect.push_back(' ');     

                outputVect.push_back(input[i]); 

	    }
		
        else if (input[i] == '(' || ')' || ';')
        {
            //If no space before operator, add one
            if (input[(i-1)] != ' ')
            {
                outputVect.push_back(' ');
            }
            
            //Push the operator
            outputVect.push_back(input[i]);
            
            //If there's no space after, add one, unless it is the last parenthesis.
            if(input[(i+1)] != ' ' && input[i+1] != ';')
            {
                    outputVect.push_back(' ');
            }
        }
        
    
    }
    
    //Restring the Vector
    string outputstring(outputVect.begin(), outputVect.end());
    return outputstring;
}

// Driver Code
int main()
{
    string inputFileName = "input_scode.txt"; 
    ifstream inputFile(inputFileName);
    string input;
    string totalInput;
   
    if (!inputFile.is_open())
    {
        cout << "Error! Failed to open input file. " << endl;
        return 0;
    }

    while(inputFile.good())
    {
    
        getline(inputFile, input);
        totalInput = totalInput + input;
    }

    inputFile.close();

    // This is string you start with
    //cout << "Input from file:" << totalInput << endl;               
    string checkStr = stringFix(totalInput);
    // This is string with appropriate spaces
    //cout << "String fixed with spaces :" << checkStr << endl;  
    //string checkStr = "while ( t < upper ) s = 22.00 ;";

    for ( int i = 0; i < checkStr.length(); i++ ) {
        if(checkStr[0] == ' ') {
            continue;
        }
         else if(checkStr[i] != ' ') {
            lexeme.push_back(checkStr[i]);
            if (i == checkStr.length()-1)
            {
                checkToken(lexeme); 
            }
        }
        else if (checkStr[i] == ' ' && i != 0 ) {
            //Identify the Lexeme
            checkToken(lexeme);
            //Clear the Lexeme vect for the next iteration
            clearVect(lexeme);
        }
    }

    
    lexer(myVect);
	return 0;
}
