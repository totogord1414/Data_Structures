#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#define MAXWORD 100005
#define INSERT true
#define SEARCH false

using namespace std;

struct dictionary{string mandarin; string dialect;};

vector<dictionary> hash_table[MAXWORD];//every element is a argument with type vector<dictionary>
unsigned int make_hash(string dialect)
{
    unsigned int hash_value = 0;
    for(int i = 0; i < dialect.length(); i++)
    {
        hash_value = 31 * hash_value + dialect[i];
    }
    return hash_value % MAXWORD;
}

void insert_hash(string mandarin, string dialect)
{
    unsigned int hash_value = make_hash(dialect);
    hash_table[hash_value].push_back({mandarin, dialect});
}

string find_hash(string dialect)
{
    unsigned int hash_value = make_hash(dialect);
    for(int i = 0;i < hash_table[hash_value].size(); i++)
    {
        if(hash_table[hash_value][i].dialect == dialect)
        {
            return hash_table[hash_value][i].mandarin;
        }

    }
    return "eh";
}
int main()
{
    bool state = INSERT;
    while(state == INSERT)
    {
        string s;
        getline(cin, s);
        if(s == "")
        {
            state = SEARCH;
            break;
        }
        stringstream ss(s);    
        string mandarin, dialect;
        ss >> mandarin >> dialect;
        insert_hash(mandarin, dialect);
        
    }
    string s;
    while(cin >> s)
    {
        string result = find_hash(s);
        cout << result << "\n";
    }
    return 0;
       

}
