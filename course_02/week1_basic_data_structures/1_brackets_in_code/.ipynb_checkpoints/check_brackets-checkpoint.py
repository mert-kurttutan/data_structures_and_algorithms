#! /usr/bin/env python3

from collections import namedtuple

Bracket = namedtuple("Bracket", ["char", "position"])


def are_matching(left, right):
    return (left + right) in ["()", "[]", "{}"]


def find_mismatch(text):
    opening_brackets_stack = []
    for i, next in enumerate(text):
        if next in "([{":
            # Process opening bracket, write your code here
            opening_brackets_stack.append(Bracket(next,i+1))

        if next in ")]}":
            # Process closing bracket, write your code here
            if len(opening_brackets_stack) == 0:
                return i+1
            left, right = opening_brackets_stack[-1].char, next
            if are_matching(left, right):
                opening_brackets_stack.pop()
            # If there is non-matching closing bracket return postion
            else:
                return i+1

    return opening_brackets_stack


def main():
    text = input()
    mismatch = find_mismatch(text)
    # Printing answer, write your code here

    # If integer returned -> mismatched closing bracket
    if isinstance(mismatch, int):
        print(mismatch)

    else:
        # Mismatched openinig bracket
        if len(mismatch) != 0:
            print(mismatch[0].position)
        else:
            print("Success")
        

if __name__ == "__main__":
    main()
