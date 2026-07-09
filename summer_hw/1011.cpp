#include <bits/stdc++.h>

using namespace std;


const string MONTHS[] = {
    "pop", "no", "zip", "zotz", "tzec", "xul", "yoxkin", "mol", 
    "chen", "yax", "zac", "ceh", "mac", "kankin", "muan", "pax", 
    "koyab", "cumhu", "uayet"
};

int getMonthIndex (const string& month) {
    for (int i = 0; i < 19; i++) {
        if (month == MONTHS[i]) {
            return i;
        }
    }

    return -1;
}

struct Date{
    int day;
    int year;
    string month_name;
    int month_index;
};

bool cmp(const Date& a, const Date& b) {
    if (a.year == b.year) {
        if (a.month_index == b.month_index) {
            return a.day < b.day;
        }
        return a.month_index < b.month_index;
    }
    return a.year < b.year;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        vector<Date> v;
        int N;
        cin >> N;
        v.reserve(N);
        for (int n = 0; n < N; n++) {
            char dot;
            string month_name;
            int day, month_index, year;
            cin >> day >> dot >> month_name >> year;
            v.push_back({day, year, month_name, getMonthIndex(month_name)});
        }

        sort(v.begin(), v.end(), cmp);

        cout << "case #" << t << ":" << "\n";
        for (int i = 0; i < N; ++i) {
            cout << v[i].day << ". " << v[i].month_name << " " << v[i].year << "\n";
        } 
    }

    return 0;
}