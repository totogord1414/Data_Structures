#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> num(n);
    for(int i = 0; i < n; i++)
    {
        cin >> num[i];
    }
    int maxLength = 0;
    int l1, r1, l2, r2;
    for(l1 = 0;l1 < n; ++l1)
    {
        for(r1 = l1; r1 < n; ++r1)
        {

            bool first_valid = true;
            unordered_set<int> first_set;
            for(int i = l1; i <= r1; i++)
            {
                if(first_set.count(num[i]))
                {
                    first_valid = false;
                    break;
                }
                first_set.insert(num[i]);
            }
            if(!first_valid)
                continue;
            for(l2 = r1 + 1; l2 < n; ++l2)
            {
                for(r2 = l2; r2 < n; ++r2)
                {
                    bool valid = true;
                    unordered_set<int> unique_num = first_set;
                    for(int i = l2; i <= r2; i++)
                    {
                        if(unique_num.count(num[i]))
                        {
                            valid = false;
                            break;
                        }
                        unique_num.insert(num[i]);
                    }
                    if(valid)
                    {
                        maxLength = max(maxLength, r2 - l2 + r1 - l1 + 2);
                    }
                }
            }
        }
    }
    cout << maxLength << endl;
    return 0;
}