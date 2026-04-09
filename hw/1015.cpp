#include <string>
#include <stack>
#include <cstdlib>
#include <iostream>

using namespace std;
//recursion vension





double evaluate()
{
    string token;
    if(cin >> token)
    {
       if(token.length() == 1 && (token == "+" || token == "-" || token == "*" || token == "/")) 
       {
            double left = evaluate();
            double right = evaluate();
            switch(token[0])
            {
                case '+': return left + right;
                case '-': return left - right;
                case '*': return left * right;
                case '/': return left / right;
                
            }
       }
       return atof(token.c_str());
    }
    return 0.0;
}
int main()
{
   double result = evaluate();
   printf("%.6f", result);
   return 0; 
}