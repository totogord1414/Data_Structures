#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    double d;
    int n;
    
    if (cin >> d >> n) {
        double max_time = 0.0; 
        
        for (int i = 0; i < n; ++i) {
            double k, s;
            cin >> k >> s;
            
            double current_time = (d - k) / s; 
            
            max_time = max(max_time, current_time);
        }
        
        double max_speed = d / max_time;
        
        cout << fixed << setprecision(6) << max_speed << "\n";
    }

    return 0;
}