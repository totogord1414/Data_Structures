#define STORE_STAGE 1
#define QUERY_STAGE 0
#define HASH_CONTAINER 100005

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

vector<pair<string , string>> hashtable[HASH_CONTAINER];

unsigned int hash_value(string dialect)
{
   unsigned int h = 0;
   for(int i = 0;i < dialect.length();i++)
   {
        h = 31 * h + dialect[i];

   }
   return h; 
}

void insert_dict(const string& dialect,const string& mandarin)
{
    unsigned int current_value = hash_value(mandarin);
    unsigned int index = current_value % HASH_CONTAINER;
    hashtable[index].push_back({dialect, mandarin});
}


string search_dict(string search_word)
{
    unsigned int search_value = hash_value(search_word);
    int index = search_value % HASH_CONTAINER;
    for(int i = 0; i < hashtable[index].size();i++)
    {
        if(hashtable[index][i].second == search_word)
            return hashtable[index][i].first;
    }
    return "eh";

}
int main()
{
    int stage = STORE_STAGE;
    string line;
    while(stage)
    {
       getline(cin, line);
       if(line == "")
       {
            stage = QUERY_STAGE;
            continue;
       }
       stringstream ss(line);
       string mandarin, dialect;
       ss >> mandarin >> dialect;
       insert_dict(mandarin , dialect);
    }
    string search;
    while(cin >> search)
    {
        string result = search_dict(search);
        cout << result << endl;
    }
    return 0;
}