#include <iostream>
#include <stack>
#include <string>

bool Isbalanced(std::string text, int &d);

struct Bracket {
    Bracket(char type, int position):
        type(type),
        position(position)
    {}

    bool Matchc(char c) {
        if (type == '[' && c == ']')
            return true;
        if (type == '{' && c == '}')
            return true;
        if (type == '(' && c == ')')
            return true;
        return false;
    }

    char type;
    int position;
};

int main() {
    std::string text;
    getline(std::cin, text);
    int d=0;

    #ifdef _DEBUG
        std::cout << "heresdfs fdsafasf" << std::endl;
    #endif

    // Printing answer, write your code here
    bool success=Isbalanced(text,d);
    if (success){
        std::cout << "Success";
    }
    else{
        std::cout << d;
    }

    return 0;
}

bool Isbalanced(std::string text, int &d){
    // stack-based implementation of problem of determining bracket sets is balanced
    // It will keep stacking the opening bracket in a stack of "Bracket" structs
    // or will check if top of the stack matches with the current text,
    // if it is a matching closing bracket, it will proceed
    // otherwise, this is unmatched brackets, it will return false.
    // all other, non-bracket, characters will be ignored

    // create a stack to keep track of opening brackets
    std::stack <Bracket> opening_brackets_stack;

    // go through each character in the text
    for (int position = 0; position < text.length(); ++position) {
        char next = text[position];

        // if opening character
        if (next == '(' || next == '[' || next == '{') {
            // push the current symbol to the stack
            Bracket current(next, position);
            opening_brackets_stack.push(current);
        }

        //if closing bracket
        if (next == ')' || next == ']' || next == '}') {

            //if empty, there is no opening bracket to match, and keep the position
            if (opening_brackets_stack.empty()){
                d = position+1;
                return false;
            }
            //will affect only if there is a match, i.e. no return false
            Bracket top = opening_brackets_stack.top();
            opening_brackets_stack.pop();

            //if they dont match return false, keep the position
            if (!top.Matchc(next)){
                d = position+1;
                return false;
            }
        }
    }

    //if not empty, d=index of last openinig character
    if (!opening_brackets_stack.empty()){
        d = opening_brackets_stack.top().position + 1;
    }
    //if not empty, there is some unmatched characters.
    return opening_brackets_stack.empty();

}

