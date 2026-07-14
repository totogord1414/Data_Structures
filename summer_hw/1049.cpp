#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, s;
    cin >> n >> s;
    vector<int> v(n);

    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    sort(v.begin(), v.end());

    int width = 0;
    int height = 0;
    int total_height = v[0];
    while (s > width * height)
    {
        s -= width * height;
        width++;
        total_height += height;
        while(width < v.size() && v[width - 1] == v[width]) {
            width++;
        }
        if (width == v.size()) {
            break;
        }
        height = (v[width] - v[width - 1]);
    }

    string int_part = to_string(total_height + s/ width);
    string frac_part = "";
    if (s % width != 0) {
        int common_divisor = gcd(s, width);
        int rem = s % width;
        frac_part = to_string(rem / common_divisor) + "/" + to_string(width / common_divisor);
    }

    if (int_part == "0") {
        cout << frac_part << "\n";
    } else if (frac_part != ""){
        cout << int_part << "+" << frac_part << "\n";
    } else {
        cout << int_part << "\n";
    }

    return 0;
}