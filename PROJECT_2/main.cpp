#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;


vector<char> myVector;                  // vector will store input string
vector<char> stack = {'$', '0'};        // starting stack

void string_to_vector(string s);                    //used to take input string and store into vector
void print_vector(const vector<char>& v);           //prints vectors
void check_stack(char c);                           //checks each character of input against the stack
void check_vector();                                //takes vector character by character to check inside check_stack function
void reduce_stack(int reduce, vector<char>& stk);   //takes care of reduce actions
void nonterm_num(char nonterm);                     // when reduce_stack is called, this function is also called to determine what digit                                                         goes after non-terminal

int indent = 20;            //used solely for formatting output
int ruleCounter = 0;        //used to determine size of rule array. used for looping
bool accepted = false;      // used to determine how long to keep feeding vector after modificationsinsed check_vector
int step = 0;               // used to count what step we are currently on



// takes in string and stores chars into a vector called myVector
// (,),*,+,$ are stored as chars and "id" is stored as "i"
void string_to_vector(string s)
{
    for( int i = 0; i < s.length(); i++ )
    {
        if( s[i] == '(' || s[i] == ')' || s[i] == '+' || s[i] == '*' || s[i] == '$' ) //terminals that are accepted
        {
            myVector.push_back(s[i]);

        }
        else if( s[i] == 'i' && s[i+1] == 'd')  // vector does not store 'id' as one character. it onlys stores "i" in this case
        {
            myVector.push_back(s[i]);
        }
        else if( s[i] == 'd' || s[i] == ' ')       // ignore "d" in "id" and ignore spaces
        {
            continue; // do nothing
        }
        else{
            cout << "ERROR: Not a valid string" << endl;    // anything else is not accepted
            exit(0);
        }
        
    }

}

// function takes myVector and sends one element to check_stack to compare in check_stack
void check_vector(){

    while( myVector.size() > 1 || !accepted )
    {
        step++;
        check_stack(myVector[0]);
    }
}

// function checks each vector char against stack to determine the action
void check_stack(char c){

    char stack_char = stack[stack.size() -1];   // used to check the last char in stack
    char stack_char2 = stack[stack.size() -2];  // used to check whether the last char is a double digit number
    cout << setw(6) << "Step: " << left << setw(4) << step ;
    
    cout<< setw(6) << right ;
    print_vector(stack);
    print_vector(myVector);

    if( c == 'i')
    {
        if( stack_char == '0' && !isdigit(stack_char2))
        {
            cout<< setw(30)<< right<< "Shift 5" << endl;
            stack.push_back(c);
            stack.push_back('5');
            myVector.erase(myVector.begin());
        }
        else if( stack_char == '4')
        {
            cout<<setw(30)<< right<< "Shift 5" << endl;
            stack.push_back(c);
            stack.push_back('5');
            myVector.erase(myVector.begin());

        }
        else if( stack_char == '6')
        {
            cout<<setw(30)<< right<<  "Shift 5" << endl;
            stack.push_back(c);
            stack.push_back('5');
            myVector.erase(myVector.begin());
        }
        else if( stack_char == '7')
        {
            cout<<setw(30)<< right<<  "Shift 5" << endl;
            stack.push_back(c);
            stack.push_back('5');
            myVector.erase(myVector.begin());
        }
        else
        {
            cout << "Not accepted." << endl;
            exit(0);
        }
    }
    else if(c == '+')
    {
         if( stack_char == '1' && !isdigit(stack_char2))
        {
            cout<< setw(30)<< right<< "Shift 6" << endl;
            stack.push_back(c);
            stack.push_back('6');
            myVector.erase(myVector.begin());
        }
        else if( stack_char == '2')
        {
           reduce_stack(2,stack);
        }
        else if( stack_char == '3')
        {
            reduce_stack(4, stack);
        }
        else if( stack_char == '5')
        {
            reduce_stack(6, stack);
        }
        else if( stack_char == '8')
        {
            cout<< setw(30)<< right<< "Shift 6" << endl;
            stack.push_back(c);
            stack.push_back('6');
            myVector.erase(myVector.begin());
        }
        else if( stack_char == '9')
        {
            reduce_stack(1, stack);
        }
        else if( stack_char == '0' && stack_char2 == '1')
        {
            reduce_stack(3, stack);
        }
        else if( stack_char == '1'  && stack_char2 == '1')
        {
            reduce_stack(5, stack);
        }
        else
        {
            cout << "Not accepted." << endl;
            exit(0);
        }
        
    }
    else if(c == '*')
    {
        if( stack_char == '2')
        {
            cout<< setw(30)<< right<<  "Shift 7" << endl;
            stack.push_back(c);
            stack.push_back('7');
            myVector.erase(myVector.begin());
        }
        else if( stack_char == '3')
        {
            reduce_stack(4, stack);
        }
        else if( stack_char == '5')
        {
            reduce_stack(6, stack);
        }
        else if( stack_char == '9')
        {
            cout<< setw(30)<< right<< "Shift 7" << endl;
            stack.push_back(c);
            stack.push_back('7');
            myVector.erase(myVector.begin());
        }
        else if( stack_char == '0' && stack_char2 == '1')
        {
            reduce_stack(3, stack);
        }
        else if( stack_char == '1' && stack_char2 == '1')
        {
            reduce_stack(5, stack);
        }
        else
        {
            cout << "Not accepted." << endl;
            exit(0);
        }
    }
    else if(c == '(')
    {
        if( stack_char == '0' && !isdigit(stack_char2))
        {
            cout<< setw(30)<< right<< "Shift 4" << endl;
            stack.push_back(c);
            stack.push_back('4');
            myVector.erase(myVector.begin());
        }
        else if( stack_char == '4')
        {
            cout<< setw(30)<< right<< "Shift 4" << endl;
            stack.push_back(c);
            stack.push_back('4');
            myVector.erase(myVector.begin());
        }
        else if( stack_char == '6')
        {
            cout<< setw(30)<< right<< "Shift 4" << endl;
            stack.push_back(c);
            stack.push_back('4');
            myVector.erase(myVector.begin());
        }
        else if( stack_char == '7')
        {
            cout<< setw(30)<< right<< "Shift 4" << endl;
            stack.push_back(c);
            stack.push_back('4');
            myVector.erase(myVector.begin());
        }
        else
        {
            cout << "Not accepted." << endl;
            exit(0);
        }
        
    }
    else if(c == ')')
    {
        if( stack_char == '2')
        {
            reduce_stack(2, stack);
        }
        else if( stack_char == '3')
        {
            reduce_stack(4, stack);
        }
        else if( stack_char == '5')
        {
            reduce_stack(6, stack);
        }
        else if( stack_char == '8')
        {
            cout<< setw(30)<< right<< "Shift 11" <<  endl;
            stack.push_back(c);
            stack.push_back('1');
            stack.push_back('1');
            myVector.erase(myVector.begin());
        }
        else if( stack_char == '9')
        {
            reduce_stack(1, stack);
        }
        else if( stack_char == '0' && stack_char2 == '1')
        {
            reduce_stack(3, stack);
        }
        else if( stack_char == '1' && stack_char2 == '1')
        {
            reduce_stack(5, stack);
        }
        else
        {
            cout << "Not accepted." << endl;
            exit(0);
        }
            
    }
    else if(c == '$')
    {
        if( stack_char == '1' && !isdigit(stack_char2))
        {
            //this is the accepting state
            cout << setw(30)<< right<<"String is accepted!!!." << endl;
            accepted = true;
            exit(0);
            
        }
        else if( stack_char == '2')
        {
            reduce_stack(2, stack);
        }
        else if( stack_char == '3')
        {
            reduce_stack(4, stack);
        }
        else if( stack_char == '5')
        {
            reduce_stack(6, stack);
        }
        else if( stack_char == '9')
        {
            reduce_stack(1, stack);
        }
        else if( stack_char == '0' && stack_char2 == '1')
        {
            reduce_stack(3, stack);
        }
        else if( stack_char == '1' && stack_char2 == '1')
        {
            reduce_stack(5, stack);
        }
        else
        {
            cout << "Not accepted." << endl;
            exit(0);
        }
    }
    
}

//this function reduces the stack according to the production rules
void reduce_stack(int reduce, vector<char>& stk)
{
  
  //rule we are using and converting
  char rule1[] = {'E','+','T'};  // Replaced with E
  char rule2[] = {'T'};          // Replaced with E
  char rule3[] = {'T','*','F'};  // Replaced with T
  char rule4[] = {'F'};          // Replaced with T
  char rule5[] = {'(', 'E', ')'};// Replaced with F
  char rule6[] = {'i'};          // Replaced with F
  
  //initialize stack size to usable variable
  int stack_size = stack.size();
  
    if( reduce == 1)
    {
        cout <<setw(30)<< right<< "Reduce 1" << endl;
      int ruleCounter = sizeof(rule1);
      
      // traverse stack backwards to pop out E+T and push in E
      for (int i = stack_size - 1; i >= stack_size - 6; i--)
      {
        if(stack[i] == rule1[ruleCounter-1])
        {
          //when the stack and the rule are the same LETTER,
          //we pop the letter off the stack
          stack.pop_back();
          ruleCounter--;      //decrement ruleCounter. Used to keep track of size of rule
          
        }
        else if (isdigit(stack[i]))  // if stack has number, pop it out
        {
          stack.pop_back();
        }
        else{    //program quits if the string is not accepted
          cout << "Error. String not accepted! ";
          exit(0);
        }
      }
      //This pushes E into stack according to rule1
      stk. push_back('E');
        nonterm_num('E'); //this adds a number to end of stack according to parse table
    }
  
  if( reduce == 2)
  {
      cout << setw(30)<< right<<"Reduce 2" << endl;
    int ruleCounter = sizeof(rule2);
    
    // traverse stack backwards to pop out T and push in E
    for (int i = stack_size - 1; i >= stack_size - 2; i--)
    {
      if(stack[i] == rule2[ruleCounter-1])
      {
        stack.pop_back();
        ruleCounter--;
 
      }
      else if (isdigit(stack[i]))  // if vector and stack do not match, get rid of number
      {
        stack.pop_back();
      }
      else{
        cout << "Error. String not accepted! ";
        exit(0);
      }
    }
    //This pushes E into stack according to rule2
    stk. push_back('E');
      nonterm_num('E');
  }
  
  if( reduce == 3)
  {
      cout <<setw(30)<< right<< "Reduce 3" << endl;
    int ruleCounter = sizeof(rule3);
      int num = 6;
      if( stack[stack_size-2] == '1')
      {
          num = 7;
          // traverse stack backwards to pop out E+T and push in E
          for (int i = stack_size - 1; i >= stack_size - num; i--)
          {
              if(stack[i] == rule3[ruleCounter-1])
              {
                  stack.pop_back();
                  ruleCounter--;

              }
              else if (isdigit(stack[i]))  // if vector and stack do not match, get rid of number
              {
                  stack.pop_back();
              }
              else{
                  cout << "Error. String not accepted! ";
                  exit(0);
              }
          }
      }
    //This pushes T into stack according to the rule
    stk. push_back('T');
      nonterm_num('T');
  }

  if( reduce == 4)
  {
      cout << setw(30)<< right<<"Reduce 4" << endl;
    int ruleCounter = sizeof(rule4);
   
    // traverse stack backwards to pop out F and push in T
    for (int i = stack_size - 1; i >= stack_size - 2; i--)
    {
      if(stack[i] == rule4[ruleCounter-1])
      {
        stack.pop_back();
        ruleCounter--;
      }
      else if (isdigit(stack[i]))  // if vector and stack do not match, get rid of number
      {
        stack.pop_back();
      }
      else{
        cout << "Error. String not accepted! ";
        exit(0);
      }
    }
    //This pushes T into stack according to the rule
    stk. push_back('T');
      nonterm_num('T');
  }

  if( reduce == 5)
  {
      cout <<setw(30)<< right<< "Reduce 5" << endl;
    int ruleCounter = sizeof(rule5);
      //make an int. initialize it to 7 if the number is 11 or 10 otherwize initialize it to 6
      int num = 6; //this is the number or characters we will check in stack. if we have a double digit then we want num to be 7
      if( stack[stack_size-2] == '1')
      {
          num = 7;
          // traverse stack backwards to pop out E+T and push in E
          for (int i = stack_size - 1; i >= stack_size - num; i--)
          {
              if(stack[i] == rule5[ruleCounter-1])
              {
                  stack.pop_back();
                  ruleCounter--;
              }
              else if (isdigit(stack[i]))  // if vector and stack do not match, get rid of number
              {
                  stack.pop_back();
              }
              else{
                  cout << "Error. String not accepted! ";
                  exit(0);
              }
          }
      }
    //This pushes F into stack according to the rule
    stk. push_back('F');
      nonterm_num('F');
  }

  if( reduce == 6)
  {
      cout << setw(30)<< right<<"Reduce 6" << endl;
    int ruleCounter = sizeof(rule6);
    
    // traverse stack backwards to pop out id and push in F
    for (int i = stack_size - 1; i >= stack_size - 2; i--)
    {
      if(stack[i] == rule6[ruleCounter-1])
      {
        stack.pop_back();
        ruleCounter--;

      }
      else if (isdigit(stack[i]))  // if vector and stack do not match, get rid of number
      {
        stack.pop_back();
      }
      else{
        cout << "Error. String not accepted! ";
        exit(0);
      }
    }
    //This pushes E into stack according to the rule
    stk. push_back('F');
    nonterm_num('F');
  }
    
}

//after reduce function is called, this will put a number in front of the non-terminal according to the parse table
void nonterm_num( char nt)
{
    step++;
    
    cout << setw(6) << left<< "Step: " << left<< setw(4) << step  ;
    
    cout<< setw(6) << right;
    print_vector(stack);
    print_vector(myVector);
 
    if( nt == 'E' )
    {
        if( stack[stack.size() -2] == '0' && !isdigit(stack[stack.size() -3]) )
        {
            cout <<setw(30)<< right<< "1" <<endl;
            stack.push_back('1');
        }
        else if (stack[stack.size() -2] == '4')
        {
            cout <<setw(30)<< right<< "8" << endl;
            stack.push_back('8');
        }
        else
        {
            cout << " String not accepted" << endl;
            exit(0);
        }
            
    }
    else if( nt == 'T')
    {
        if( stack[stack.size() -2] == '0' && !isdigit(stack[stack.size() -3]))
        {
            cout <<setw(30)<< right<< "2" << endl;
            stack.push_back('2');
        }
        else if (stack[stack.size() -2] == '4')
        {
            cout <<setw(30)<< right<< "2" << endl;
            stack.push_back('2');
        }
        else if (stack[stack.size() -2] == '6')
        {
            cout << setw(30)<< right<<"9" <<endl;
            stack.push_back('9');
        }
        else
        {
            cout << " String not accepted" << endl;
            exit(0);
        }
    }
    else if (nt == 'F')
    {
        
        if( stack[stack.size() -2] == '0' && !isdigit(stack[stack.size() -3]))
        {
            cout << setw(30)<< right<<"3" << endl;
            stack.push_back('3');
        }
        else if (stack[stack.size() -2] == '4')
        {
            cout << setw(30)<< right<<"3" << endl;
            stack.push_back('3');
        }
        else if (stack[stack.size() -2] == '6')
        {
            cout <<setw(30)<< right<< "3" << endl;
            stack.push_back('3');
        }
        else if (stack[stack.size() -2] == '7')
        {
            cout << setw(30)<< right<<"10" <<endl;
            stack.push_back('1');
            stack.push_back('0');
        }
        else
        {
            cout << " String not accepted" << endl;
            exit(0);
        }
    }
}

//prints vector
void print_vector(const vector<char>& v)
{
    cout << setw(15 - v.size())<< left << "\t";
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i];
        if( v[i] == 'i')        // bc vector does not store "id" as one character, it stores it as "i". This print will add a 'd" after the i
            cout <<'d';
    }
}

int main(){


    //PLACE INPUT STRING HERE
    string str = "(id+id)*id$";


    //Printing the table
    cout << "Input string: " << str << endl;
    string_to_vector(str);
    cout << "string as vector: " << endl;
    print_vector(myVector);
    cout << "\n" ;
    cout << "Starting stack: " << endl;
    print_vector(stack);
    cout<< "\nGrammar rules: " << endl;
    cout << "1. E -> E + T " << endl;
    cout << "2. E -> T " << endl;
    cout << "3. T -> T * F " << endl;
    cout << "4. T -> F " << endl;
    cout << "5. E -> ( E ) " << endl;
    cout << "6. F -> id " << endl;
    cout << "\n" ;
    cout << "--------------------------------------------------------------------------- " << endl;
    
    // start the process
    check_vector();
    
    
}
