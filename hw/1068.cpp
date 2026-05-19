#include <bits/stdc++.h>

using namespace std;

//a double hash way to solve this problem

struct StringHash{
    const long long MOD1 = 1e9 + 7;
    const long long MOD2 = 1e9 + 13;
    const long long BASE1 = 131;
    const long long BASE2 = 13331;

    vector<long long> h1, h2;// this is the sting hash array
    vector<long long> p1, p2;// this is the pth base( base ^ n % mod)
    StringHash(string s)// init the hash
    {
        int n = s.length();

        h1.resize(n + 1, 0);
        h2.resize(n + 1, 0);
        p1.resize(n + 1, 1);
        p2.resize(n + 1, 1);

        for(int i = 0; i < n; i++)
        {
            h1[i + 1] = (h1[i] * BASE1 + s[i]) % MOD1;
            h2[i + 1] = (h2[i] * BASE2 + s[i]) % MOD2;

            p1[i + 1] = (p1[i] * BASE1) % MOD1;
            p2[i + 1] = (p2[i] * BASE2) % MOD2;
        }
    }

    long long get_hash(int l, int r)
    {
        l++;
        r++;

        int len = r - l + 1;
        long long hash2 = (h2[r] - h2[l - 1] * p2[len]) % MOD2;
        long long hash1 = (h1[r] - h1[l - 1] * p1[len]) % MOD1;
        hash1 = (hash1 + MOD1) % MOD1;
        hash2 = (hash2 + MOD2) % MOD2;
        return ((unsigned long long) hash1 << 32) | (unsigned long long) hash2;
    }

    bool is_equal(int l1, int r1, int l2, int r2)
    {
        if(r1 - l1 != r2 - l2)
        {
            return false;
        }
        return get_hash(l1, r1) == get_hash(l2, r2);
    }

};

bool check(int mid, int n, StringHash& hash_fw, StringHash& hash_bw)
{
    map<unsigned long long, int> min_pos;

    for(int i = 0; i <= n - mid; i++)
    {
        unsigned long long h = hash_fw.get_hash(i, i + mid - 1);
        if(min_pos.find(h) == min_pos.end())
        {
            min_pos[h] = i;
        }
    }

    for(int j = 0; j <= n - mid; j++)
    /*this j is from the original string's location, 
    so rev_l and rev_r converts them into the reverse string's location*/
    {
        int rev_r = n - j - 1;
        int rev_l = n - j - mid;
        unsigned long long h = hash_bw.get_hash(rev_l, rev_r);
        if(min_pos.find(h) != min_pos.end())
        {
            int i = min_pos[h];
            if(i + mid - 1< j)
            {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;
    StringHash hash_fw(s);
    reverse(s.begin(), s.end());
    StringHash hash_bw(s);
    int len = s.length();
    int min = 1;
    int ans = 0;
    int max = len / 2;
    int mid;
    while(min <= max)
    {
        mid = (min + max) / 2;
        if(check(mid, len, hash_fw, hash_bw))
        {
            ans = mid;
            min = mid + 1;
        }
        else
        {
            max = mid - 1;
        }
    }
    cout << ans << endl;
    return 0;
}