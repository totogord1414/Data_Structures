#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;

    while (cin >> s) {
        if (s.find('.') != string::npos) {
            double d = stod(s);

            unsigned char* pos = (unsigned char*) &d;

            for (size_t i = 0; i < sizeof(d); i++) {
                cout << hex << setw(2) << setfill('0') << (int)pos[i] << " ";
            }

            cout << '\n';
        } else {
            int num = stoi(s);

            unsigned char* pos = (unsigned char*) &num;

            for (size_t i = 0; i < sizeof(num); i++) {
                cout << hex << setw(2) << setfill('0') << (int)pos[i] << " ";
            }

            cout << "\n";
        }
    }

    return 0;
}