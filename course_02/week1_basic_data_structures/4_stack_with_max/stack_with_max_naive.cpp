#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <numeric>
#include <algorithm>

using std::cin;
using std::string;
using std::vector;
using std::cout;
using std::max_element;

class StackWithMax {
    vector<int> stack;
  public:
    vector<int> idx;

    void Push(int value) {
        stack.push_back(value);
        if (idx.empty())
            idx.push_back(value);

        else if( value > idx.back())
            idx.push_back(value);
        else
            idx.push_back(idx.back());
    }

    void Pop() {
        assert(stack.size());
        stack.pop_back();
        idx.pop_back();
    }

    int Max() const {
        assert(stack.size());
        return *max_element(stack.begin(), stack.end());
    }
};

int main() {
    int num_queries = 0;
    cin >> num_queries;

    string query;
    string value;

    StackWithMax stack;

    for (int i = 0; i < num_queries; ++i) {
        cin >> query;
        if (query == "push") {
            cin >> value;
            stack.Push(std::stoi(value));
        }
        else if (query == "pop") {
            stack.Pop();
        }
        else if (query == "max") {
            cout << stack.idx.back() << "\n";
        }
        else {
            assert(0);
        }
    }
    return 0;
}