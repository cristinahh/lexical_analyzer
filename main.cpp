#include <string>
#include <iostream>
#include <utility>
#include <vector>
#include <cctype>
#include <fstream>

using namespace std;

//This will store the output, pairs of (token type, value)
vector<pair<string, string > > myVect;

//This will store the characters of the string currently processed by lexer
vector<char> lexeme;

//The word is passed here for checking if keyword
bool isKeyword(string word)
{
    if( word == "int" || word == "while" || word == "else" || word == "if" || word == "double"|| word == "string")
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
    word == "*" || word == "<" || word == ">" || word == "=>" || word == "=<" || word == "==" || word == "=")
    {
        return true;
    }
    return false;

}
//The word is passed here for checking if keyword
//a loop is ran to determine if the value is negative or unreal
bool isReal(string word)
{
    
    for(int i = 0; i < word.length(); i++)
    {
        int countNeg = 0;
        int countDec = 0;
        
        if( word[0] == '-' && isdigit(word[1]))
        {
            if(countNeg == 0)
            {
                countNeg++;
                break;
            }
            else
                return false;
        }
        else if(isdigit(word[i]))
        {
            break;
        }
        else if ( word[i] == '.' )
        {
            if(countDec == 0)
            {
            countDec++;
            break;
            }
            else 
            return false;
        }
        else
            return false;
    }
    return true;
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
    else
    {
        createPair("identifier", lexStr);
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


// This is the print function for the Output myVect pairs
void print(vector<pair<string,string > > vect)
{
    for ( int i = 0; i < vect.size(); i++)
    {
        cout<< ( vect[i].first) << ", " << vect[i].second << endl;
    }
}

//This function makes the input string something we can actually parse
string stringFix(string input)
{
    vector<char> outputVect;
    
    for (int i = 0; i < input.length(); ++i)
    {
        //Alphanumeric & Spaces are Okay to push
        if (isalpha(input[i]))
        {
           outputVect.push_back(input[i]);
        }
        
        else if (isdigit(input[i]))
        {
           outputVect.push_back(input[i]);
        }
        
        else if (input[i] == ' ')
        {
            outputVect.push_back(' ');
        }
        
        //If there's a decimal or period, push here
        // I tried to implement a hyphen/ negative check here, but it didnt work
        //There might be a better way to do this, this started as a couple different funcitons and this is just the result 
        else if(input[i] == '.')
        {
            outputVect.push_back('.');  
        }
        
        //This should work for negatives.
        else if(input[i] == '-' && isdigit(input[(i+1)]))
        {
            outputVect.push_back('-');
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
            
            //If there's no space after, add one
            if(input[(i+1)] != ' ')
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
    string inputFileName = "input.txt"; 
    ifstream inputFile(inputFileName);
    if (!inputFile.is_open())
    {
        cout << "Error! Failed to open input file. " << endl;
        return 0;
    }
    string input;
    getline(inputFile, input); 
    inputFile.close();

    cout << "Input from file: " << input << endl;
    string checkStr = stringFix(input);
    //string checkStr = "while ( t < upper ) s = 22.00 ;";

    for ( int i = 0; i < checkStr.length(); i++ ) {
        if(checkStr[0] == ' ') {
        break;
        }
         if(checkStr[i] != ' ') {
            lexeme.push_back(checkStr[i]);
            if (i == checkStr.length()-1)
            {
                checkToken(lexeme); 
            }
        }
        else if (checkStr[i] == ' ' ) {
            //Identify the Lexeme
            checkToken(lexeme);
            //Clear the Lexeme vect for the next iteration
            clearVect(lexeme);
        }
    }
   print(myVect);
	return 0;
}
