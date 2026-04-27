#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    int m, n;
    cin >> m >> n;
    vector<int> tray(m);
    vector<queue<int>> rail(n);
    vector<queue<int>> result(n);
    int current_size = 0;
    for(int i = 0; i < m; i++)
    {
        cin >> tray[i];
    }
    
    int next_num = 1;
    for(int i = 0; i < m; i++)
    {
        while(true)
        {
            int prev = next_num;
            for(int j = 0; j < current_size; j++)
            {
                if(!rail[j].empty() && rail[j].front() == next_num)
                {
                    result[j].push(rail[j].front());
                    rail[j].pop();
                    next_num++;
                }
            }
            if(prev == next_num)
                break;
        }
        int fit_place = -1;
        int fit_num = tray[i];
        for(int j = 0; j < current_size; j++)
        {
            if(!rail[j].empty() && rail[j].back() < tray[i] && tray[i] - rail[j].back() < fit_num)
            {
                fit_place = j;
                fit_num = tray[i] - rail[j].back();
            }
        }
        if(fit_place == -1)
        {
            for(int k = 0;k < current_size;k++)
            {
                if(rail[k].empty())
                {
                    fit_place = k;
                    break;
                }
            }
        }
        if(fit_place == -1)
        {
            current_size++;
            if(current_size > n)
            {
                cout << -1 << endl;
                return 0;
            }
            fit_place = current_size - 1;
        }
        rail[fit_place].push(tray[i]);
    }
    while(next_num <= m)
    {

        for(int j = 0; j < current_size; j++)
        {
            if(!rail[j].empty() && rail[j].front() == next_num)
            {
                result[j].push(rail[j].front());
                rail[j].pop();
                next_num++;
            }
        }
    }
    cout << current_size << endl;
    for(int i = 0; i < current_size; i++)
    {
        while(!result[i].empty())
        {
            cout << result[i].front();
            result[i].pop();
            if(!result[i].empty())
                cout << " ";
            else
                cout << endl;
        }
    }
    return 0;
}