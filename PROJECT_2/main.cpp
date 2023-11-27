#include <iostream>
#include <utility>
#include <vector>
#include <cctype>
#include <fstream>
#include <string>

using namespace std;

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



void parse(string inputstring, string originput)
{
    ofstream myFile;



    //NONE OF THIS IS FINISHED
    string result;
    if result = "accepted";
    myFile.open("tree_mydesign.txt");
    myFile << "Input: " << originput << endl
        << "Stack: " << endl;




    myFile.close();
}

int main()
{
 
 string inputFileName = "input.txt"; 
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

string useableString = stringFix(totalInput);


parse(useableString);

cout << endl << useableString << endl;

 return 0;   
}