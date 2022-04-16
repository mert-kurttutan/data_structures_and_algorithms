#include <iostream> 
int positive_modulo(long int n, long int m); 
long periodFib(long m); long FibModule(long long n, long long m); 
long long get_fibonacci_partial_sum_naive(long long from, long long to); 
int fibonacci_sum_squares_naive(long long n); 



int main() { 
    long long n = 0; 
    std::cin >> n; int fib_n = FibModule(n, 10); 
    int fib_n_1 = FibModule(n-1, 10); 
    int sum_square = positive_modulo(fib_n*(fib_n + fib_n_1), 10); 
    std::cout << sum_square; 
} 

int positive_modulo(long int n, long int m){ 
    return (n % m + m) % m; 
} 
long periodFib(long m){ 
    int prev=0; 
    int curr=1; 
    int period; 
    bool per_reached=false; 
    int i=0; 
    while(!per_reached){ 
        int temp = curr; 
        curr = (curr + prev) % m; 
        prev = temp; 
        if (prev==0 && curr==1){ 
            period=i+1; per_reached = true; 
        } 
        i++; 
    } 
    return period; 
    } 

long FibModule(long long n, long long m){ 
    long int period_m = periodFib(m); 
    n = n % period_m; 
    long prev = 0; 
    long curr = 1; 
    if (n == 0) 
    return 0; 
    else if (n == 1) 
    return 1; 
    for(int i = 0; i < n - 1; i++) { 
        long temp = 0; 
        temp = curr; 
        curr = (prev + curr) % m; prev = temp; 
    } 
    return curr % m; 
} 
long long get_fibonacci_partial_sum_naive(long long from, long long to) { 
    long long sum = 0; 
    long long current = 0; 
    long long next  = 1; 
    for (long long i = 0; i <= to; ++i) { 
        if (i >= from) { 
            sum += current; 
        } 
        long long new_current = next; 
        next = next + current; 
        current = new_current; 
    } 
    return sum % 10; 
}

int fibonacci_sum_squares_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current * current;
    }

    return sum % 10;
}