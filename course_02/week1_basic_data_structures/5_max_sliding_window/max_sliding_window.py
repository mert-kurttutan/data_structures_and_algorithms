#! /usr/bin/env python3


def max_finder(arr:list) -> list:

    max_value = max(arr)
    occurences_max = [index for index, value in enumerate(arr) if value == max_value]

    return  occurences_max


def max_sliding_window_naive(sequence, m):
    maximums = []
    indices_max = max_finder(sequence[:m])
    for i in range(len(sequence) - m + 1):
        if indices_max[0] == 0:
            indices_max.pop(0)
        
       #if 
        maximums.append(max(sequence[i:i + m]))

    return maximums

if __name__ == '__main__':
    n = int(input())
    input_sequence = [int(i) for i in input().split()]
    assert len(input_sequence) == n
    window_size = int(input())

    print(*max_sliding_window_naive(input_sequence, window_size))

