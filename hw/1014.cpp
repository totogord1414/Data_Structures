#include <iostream>
#include <vector>

using namespace std;


struct element{
    int row;
    int column;
    int value;
    };

int main()
{
    int row, column, numA = 0, numB= 0;
    cin >> row >> column >> numA;
    vector<element> discA(numA);
    
   for(int i = 0; i < numA; i++)
   {
        cin >> discA[i].row >> discA[i].column >> discA[i].value;
        //if you haven't use the num in the first place,than you have to push back vector like this:
        //cin >> row >> column >> v discA.pushback({row, column, value})
   }
   cin >> row >> column >> numB;
   vector<element> discB(numB);
   for(int i = 0; i < numB; i++)
   {
        cin >> discB[i].row >> discB[i].column >> discB[i].value;
   }
   int pointer_A = 0, pointer_B = 0;
   vector<element> discC;
   int pointer_C = 0;
   while(pointer_A < numA && pointer_B < numB)
   {
       if(discA[pointer_A].row < discB[pointer_B].row || (discA[pointer_A].row == discB[pointer_B].row && discA[pointer_A].column < discB[pointer_B].column))
        {
            discC.push_back(discA[pointer_A]);
            pointer_A++;
            pointer_C++;
        } 
       else if(discB[pointer_B].row < discA[pointer_A].row || (discA[pointer_A].row == discB[pointer_B].row && discB[pointer_B].column < discA[pointer_A].column))
       {
            discC.push_back(discB[pointer_B]);
            pointer_B++;
            pointer_C++;
       }
       else
       {
            int sum;
            sum = discA[pointer_A].value + discB[pointer_B].value;
            if (sum != 0)
            {
                discC.push_back({discA[pointer_A].row, discA[pointer_A].column, sum});
                pointer_C++;
            }
            pointer_A++;
            pointer_B++;
       }
   }
   while(pointer_A < numA)
   {
        discC.push_back(discA[pointer_A]);
        pointer_A++;
        pointer_C++;
   }
   while(pointer_B < numB)
   {
        discC.push_back(discB[pointer_B]);
        pointer_B++;
        pointer_C++;
   }
   for(int i = 0; i < pointer_C;i++)
   {
        cout << discC[i].row << " " << discC[i].column << " " << discC[i].value << "\n" ;
   }
    return 0;

}