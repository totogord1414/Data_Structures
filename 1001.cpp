//栈版本
/*
#include<iostream>
#include<vector>

using namespace std;

int main()
{
    int num = 0;
    cin >> num;
    vector<int> n;
    vector<int> n_count;
    for(int i = 0;i < num;i++)
    {
        int n_temp;
        cin >> n_temp;
        n_count.push_back(n_temp);
        for(int j = 0;j < n_count[i];j++)
        {
            int temp;
            cin >> temp;
            n.push_back(temp);
        }
    }
    for(int i = num;i;i--)
    {
        for(int j = n_count[i - 1];j;j--)
        {
            cout << n.back() << " ";
            n.pop_back();
        }
        cout << "\n";
    }
    return 0;

}
    */

//二维vector

#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int num;
    cin >> num;

    vector<vector<int>> data(num);//通过添加num,预留空间，防止因为push_back后内存不够导致搬家，损失性能
    for(int i = 0;i < num;i++)
    {
        int c;
        cin >> c;
        data[i].resize(c);
        for(int j = 0;j < c;j++)
        {
            cin >> data[i][j];
        }
    }
    for(int i = num-1 ;i >= 0;i--)
    {
        for(int j = data[i].size() - 1;j >= 1;j--)
        {
            cout << data[i][j] << " ";
        }
        cout << data[i][0] << "\n";
    }
    return 0;
}