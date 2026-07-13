#include <bits/stdc++.h>

using namespace std;

enum State {
    NORMAL,
    IN_STRING,
    IN_CHAR,
    IN_LINE_COMMENT,
    IN_BLOCK_COMMENT
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string code;
    char ch;
    while(cin.get(ch)) {
        code += ch;
    }

    int n = code.length();
    State state = NORMAL;

    for (int i = 0; i < n; i++) {
        char c = code[i];
        switch (state)
        {
        case NORMAL:
            if (c == '/' && i + 1 < n && code[i + 1] == '/') {
                state = IN_LINE_COMMENT;
                i++;
                } else if (c == '/' && i + 1 < n && code[i] == '*') {
                    state = IN_BLOCK_COMMENT;
                    i++;
                } else if (c == '"') {
                    cout << c;
                    state = IN_STRING;
                } else if (c == '\'') {
                    cout << c;
                    state = IN_CHAR;
                } else {
                    cout << c;
                }
            break;
        case IN_STRING:
                if (c == '"') {
                    state = NORMAL;
                    cout << c;
                } else if (c == '\\') {
                    cout << c;
                    if (i + 1 < n) {
                        cout << code[++i];
                    }
                } else {
                    cout << c;
                }
            break;
        case IN_CHAR:
                if (c == '\'') {
                    state = NORMAL;
                } else if (c == '\\') {
                    cout << c;
                    if (i + 1 < n) {
                        cout << code[++i];
                    }
                } else {
                    cout << c;
                }
                cout << c;
            break;
        case IN_BLOCK_COMMENT:
                if (c == '*' && i + 1 < n && code[++i] == '/') {
                    state = NORMAL;
                }
            break;
        case IN_LINE_COMMENT:
                if (c == '\n') {
                    cout << c;
                    state = NORMAL;
                }
            break;
        }
    }
}