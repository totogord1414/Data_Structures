#include <bits/stdc++.h>

using namespace std;

struct StringHash{
    const int BASE1 = 131;
    const int BASE2 = 13331;
    const long long MOD1 = 1e9 + 7;
    const long long MOD2 = 1e9 - 3;

    vector<long long> h1;
    vector<long long> h2;
    vector<long long> p1;
    vector<long long> p2;

    StringHash(string s)
    {
        int len = s.length();

        h1.resize(len + 1, 0);
        h2.resize(len + 1, 0);
        p1.resize(len + 1, 1);
        p2.resize(len + 1, 1);

        for(int i = 0; i < len; i++)
        {
            h1[i + 1] = (h1[i] * BASE1 + s[i]) % MOD1;
            p1[i + 1] = (p1[i] * BASE1) % MOD1;

            h2[i + 1] = (h2[i] * BASE2 + s[i]) % MOD2;
            p2[i + 1] = (p2[i] * BASE2) % MOD2;
        }
    }

    pair<long long, long long> get_hash(int l, int r)
    {
        long long hash1 = (h1[r + 1] - h1[l] * p1[r - l + 1]) % MOD1;
        hash1 = (hash1 + MOD1) % MOD1;

        long long hash2 = (h2[r + 1] - h2[l] * p2[r - l + 1]) % MOD2;
        hash2 = (hash2 + MOD2) % MOD2;

        return {hash1, hash2};
    }


};

bool is_equal(int l1, int r1, int l2, int r2, StringHash& h)//returns true if these strings are the same
{
    pair<long long, long long> hash1 = h.get_hash(l1, r1);
    pair<long long, long long> hash2 = h.get_hash(l2, r2);
    return hash1 == hash2;
}

int find_lcp(int len, int i1, int i2, StringHash& h)// find the longest common perflix with O(log n) (i1 must be less than i2)
{
    //using binary search
    int ans = 1;//since i1 must be equal to i2
    int min = 1;
    int max = i1 + 1;
    while(min <= max)
    {
        int mid = (min + max) / 2;
        if(is_equal(i1 - mid + 1, i1, i2 - mid + 1, i2, h))
        {
            ans = mid;
            min = mid + 1;
        }
        else
        {
            max = mid - 1;
        }
    }
    return ans;
}


int find_lcd(int len, int i1, int i2, StringHash& h)
{
    int ans = 1;
    int min = 1;
    int max = len - i2;
    while(min <= max)
    {
        int mid = (min + max) / 2;
        if(is_equal(i1, i1 + mid - 1, i2, i2 + mid - 1, h))
        {
            ans = mid;
            min = mid + 1;
        }
        else
        {
            max = mid - 1;
        }
    }
    return ans;
}

int main()
{
    string s;
    cin >> s;
    StringHash sh(s);
    int len = s.length();    
    int ans = 0;
    for(int i = len / 2; i >=  1; i--)
    {
        for(int j = 0; j + i < len; j += i)
        {
            if(s[j] == s[i + j])
            {
                int lcd = find_lcd(len, j, i + j, sh);
                int lcp = find_lcp(len, j, i + j, sh);
                if(lcd + lcp - 1 >= i)
                {
                    ans = i;
                    break;
                }
            }
        }
        if(ans != 0)
        {
            break;
        }
    }
    cout << 2 * ans << "\n";
    return 0;
}