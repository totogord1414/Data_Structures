#include <bits/stdc++.h>

using namespace std;

string geno_to_pheno(const string& geno) {
    if (geno == "AA" || geno == "AO" || geno == "OA") return "A";
    else if (geno == "BB" || geno == "BO" || geno == "OB") return "B";
    else if (geno == "AB" || geno == "BO") return "AB";
    else return "O";
}

set<string> get_child_blood_types(const string& father, const string& mother) {
    map<string, vector<string>> pheno_to_geno = {{"A", {"AA", "AO"}}, {"B", {"BB", "BA"}}, {"O", {"OO"}}, {"AB", {"AB"}}};

    vector<string> father_geno = pheno_to_geno[father];
    vector<string> mother_geno = pheno_to_geno[mother];

    set<string> child_blood_types;
    for (string f_g : father_geno) {
        for (string m_g : mother_geno) {
            for (char f: f_g) {
                for (char m: m_g) {
                    string child_geno = "";
                    child_geno += f;
                    child_geno += m;
                    child_blood_types.insert(geno_to_pheno(child_geno));
                }
            }
        }
    }

    return child_blood_types;
}

void print_blood_types(const set<string>& blood_types) {
    if (blood_types.empty()) {
        cout << "impossible";
        return;
    }
    cout << "{";
    bool is_first = true;
    for (const auto& s : blood_types) {
        if (!is_first) {
            cout << ",";
        }
        is_first = false;
        cout << s;
    }
    cout << "}";
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string father, mother, child;
    cin >> father >> mother >> child;

    if (child == "?") {
        cout << father << " " << mother << " ";
        print_blood_types(get_child_blood_types(father, mother));
        cout << "\n";
    } else if (father == "?") {
        set<string> blood_types;
        vector<string> all_types = {"A", "B", "AB", "O"};
        for (const string& type: all_types) {
            set<string> child_blood_types = get_child_blood_types(type, mother);
            if (child_blood_types.count(child)) {
                blood_types.insert(type);
            }
        }
        print_blood_types(blood_types);

        cout << " " << mother << " " << child << "\n";
    } else if (mother == "?") {
        cout << father << " ";

        set<string> blood_types;
        vector<string> all_types = {"A", "B", "AB", "O"};
        for (const string& type: all_types) {
            set<string> child_blood_types = get_child_blood_types(father, type);
            if (child_blood_types.count(child)) {
                blood_types.insert(type);
            }
        }
        print_blood_types(blood_types);



        cout << " " << child << "\n";
    }


    return 0;
}