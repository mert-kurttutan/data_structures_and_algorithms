#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>



std::tuple <int, int> maxNumber(const std::vector<int>& numbers, int index);
int MaxPairwiseProduct(const std::vector<int>& numbers);

int main() {
    int n;
    std::cin >> n;
    std::vector<int> numbers(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
    }
    int max1, max2, idx1, idx2;
    std::tie(max1, idx1) = maxNumber(numbers, -1);
    std::tie(max2, idx2) = maxNumber(numbers, idx1);

    long long int result = (long long)(max1) * max2;
    std::cout << result << std::endl;
    
    return 0;
}


std::tuple <int, int> maxNumber(const std::vector<int>& numbers, int index){
	int max_num = -100;
	int max_idx = -1;
	int n = numbers.size();
	
	for (int i = 0; i < n; i++){
		if (i != index){
		    if(max_num < numbers[i]){
		        max_num = numbers[i];
		        max_idx = i;
		    }
		}
    }
	return std::make_tuple(max_num, max_idx);
}


int MaxPairwiseProduct(const std::vector<int>& numbers) {
    int max_product = 0;
    int n = numbers.size();

    for (int first = 0; first < n; ++first) {
        for (int second = first + 1; second < n; ++second) {
            max_product = std::max(max_product,
                numbers[first] * numbers[second]);
        }
    }

    return max_product;
}