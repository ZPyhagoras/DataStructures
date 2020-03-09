#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <stack>
using namespace std;

struct Word {
    bool flag;
    double num;
    char sign;
};

int Sign2Num(char ch) {
    switch (ch) {
    case '+':
        return 0;
    case '-':
        return 1;
    case '*':
        return 2;
    case '/':
        return 3;
    case '^':
        return 4;
    case '(':
        return 5;
    case ')':
        return 6;
    case '#':
        return 7;
    }
    return 8;
}

int SignPriority(char in, char out) {
    int sp[9][9] = {{ 1,  1, -1, -1, -1, -1,  1,  1, 99},
                    { 1,  1, -1, -1, -1, -1,  1,  1, 99},
                    { 1,  1,  1,  1, -1, -1,  1,  1, 99},
                    { 1,  1,  1,  1, -1, -1,  1,  1, 99},
                    { 1,  1,  1,  1, -1, -1,  1,  1, 99},
                    {-1, -1, -1, -1, -1, -1,  0, 99, 99},
                    { 1,  1,  1,  1,  1, 99,  1,  1, 99},
                    {-1, -1, -1, -1, -1, -1, 99,  0, 99},
                    {99, 99, 99, 99, 99, 99, 99, 99, 99}};
    return sp[Sign2Num(in)][Sign2Num(out)];
}

vector<Word> LexicalAnalysis(string func) {
    func = func+ "#";
    int l = func.length();
    vector<Word> ans;
    for (int i = 0; i < l; i++) {
        if (func[i] >= '0' && func[i] <= '9') {
            double num = 0;
            bool df = false;
            double mi = 0;
            for ( ; i < l; i++) {
                if (!df) {
                    if (func[i] >= '0' && func[i] <= '9') {
                        num = num * 10 + static_cast<double>(func[i] - '0');
                    }
                    else if (func[i] == '.') {
                        df = true;
                        mi = 10.0;
                    }
                }
                else {
                    if (func[i] >= '0' && func[i] <= '9') {
                        num = num + (func[i] - '0') / mi;
                        mi *= 10;
                    }
                }
                if (!(func[i] >= '0' && func[i] <= '9') && (func[i] != '.')){
                    Word n;
                    n.flag = true;
                    n.num = num;
                    ans.push_back(n);
                    num = 0;
                    break;
                }
            }
            i--;
        }
        else {
            Word s;
            s.flag = false;
            s.sign = func[i];
            if (s.sign != '#') {
                ans.push_back(s);
            }
        }
    }
    return ans;
}

vector<Word> ParseAnalysis(vector<Word> lpword) {
    stack<Word> SignStack;
    vector<Word> ans;
    Word fst;
    fst.flag = false;
    fst.sign = '#';
    SignStack.push(fst);
    for (Word w : lpword) {
        if (w.flag) {
            ans.push_back(w);
        }
        else {
            if (w.sign == ')') {
                while (!SignStack.empty()) {
                    if (SignStack.top().sign == '(') {
                        SignStack.pop();
                        break;
                    }
                    ans.push_back(SignStack.top());
                    SignStack.pop();
                }
            }
            else if (SignPriority(SignStack.top().sign, w.sign) > 0) {
                ans.push_back(SignStack.top());
                SignStack.pop();
                SignStack.push(w);
            }
            else {
                SignStack.push(w);
            }
        }
    }
    while (!SignStack.empty()) {
        if (SignStack.top().sign != '#') {
            ans.push_back(SignStack.top());
        }
        SignStack.pop();
    }
    return ans;
}

double Calculatoin(vector<Word> paword) {
    stack<double> ans;
    for (Word w : paword) {
        if (w.flag) {
            ans.push(w.num);
        }
        else {
            double a, b;
            b = ans.top(); ans.pop();
            a = ans.top(); ans.pop();
            switch (w.sign) {
            case '+':
            ans.push(a + b);
            break;
            case '-':
            ans.push(a - b);
            break;
            case '*':
            ans.push(a * b);
            break;
            case '/':
            ans.push(a / b);
            break;
            case '^':
            ans.push(pow(a, b));
            break;
            }
        }
    }
    return ans.top();
}

void VCPrint(vector<Word> vw) {
    for (Word w : vw) {
        cout << "|";
        if (w.flag) {
            cout << w.num;
        }
        else {
            cout << w.sign;
        }
    }
    cout << "|" << endl;
}

int main() {
    string func;
    cin >> func;
    vector<Word> words = LexicalAnalysis(func);
    vector<Word> Post = ParseAnalysis(words);
    VCPrint(words);
    VCPrint(Post);
    cout << Calculatoin(Post) << endl;;
    return 0;
}
