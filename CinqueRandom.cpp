#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

// 生成所有可能的骰子点数
vector<int> generateDiceNumbers() {
    vector<int> diceNumbers;
    for (int i = 1; i <= 6; i++) {
        for (int j = 1; j <= 6; j++) {
            diceNumbers.push_back(i * 10 + j);
        }
    }
    return diceNumbers;
}

// 骰子1实现
int function1(int n, int diceValue) {
    if (diceValue <= n) {
        return diceValue;
    } else {
        return 2 * n - diceValue;
    }
}

// 骰子2实现
int function2(int n, int diceValue) {
    if (diceValue <= n) {
        return n - diceValue + 1;
    } else {
        return diceValue - n + 1;
    }
}

// 计算骰子1规则下无法得到的数字集合
set<int> getK1(int n) {
    vector<int> diceNumbers = generateDiceNumbers();
    set<int> possibleResults;
    
    for (int dice : diceNumbers) {
        int result = function1(n, dice);
        if (result >= 1 && result <= n) {
            possibleResults.insert(result);
        }
    }
    
    set<int> k1;
    for (int i = 1; i <= n; i++) {
        if (possibleResults.find(i) == possibleResults.end()) {
            k1.insert(i);
        }
    }
    
    return k1;
}

// 计算骰子2规则下无法得到的数字集合
set<int> getK2(int n) {
    vector<int> diceNumbers = generateDiceNumbers();
    set<int> possibleResults;
    
    for (int dice : diceNumbers) {
        int result = function2(n, dice);
        if (result >= 1 && result <= n) {
            possibleResults.insert(result);
        }
    }
    
    set<int> k2;
    for (int i = 1; i <= n; i++) {
        if (possibleResults.find(i) == possibleResults.end()) {
            k2.insert(i);
        }
    }
    
    return k2;
}

// 规则1和规则2抽不出来的结果进行一个交集
set<int> functionSet1(int n) {
    set<int> k1 = getK1(n);
    set<int> k2 = getK2(n);
    
    set<int> intersection;
    set_intersection(k1.begin(), k1.end(), k2.begin(), k2.end(),
                    inserter(intersection, intersection.begin()));
    
    return intersection;
}

int main() {
    cout << "请输入元素数量a的值,a取值应该在10-66:";
    
    int n;
    cin >> n;

    cout << endl;
    set<int> result = functionSet1(n);
    
    cout << "n=" << n << "时，骰子1和骰子2规则相交后永远得不到的结果: {";
    for (auto it = result.begin(); it != result.end(); ++it) {
        if (it != result.begin()) cout << ", ";
        cout << *it;
    }
    cout << "}" << endl;
    
    
    return 0;
}
