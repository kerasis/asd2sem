
//
//vector<int> greedySubsetSum(int N) {
//    vector<int> subset;
//
//    while (N > 0) {
//        int largestPowerOfTwo = 1;
//        while (largestPowerOfTwo * 2 <= N) {
//            largestPowerOfTwo *= 2;
//        }
//
//        subset.push_back(largestPowerOfTwo);
//        N -= largestPowerOfTwo;
//    }
//
//    return subset;
//}

#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> greedySubsetSum(std::vector<int>& nums,int subsetSum) {
    std::vector<int> subset;

    std::sort(nums.begin(), nums.end(), [](int a, int b) { return abs(a) > abs(b); }); // Сортировка по убыванию модуля

    for (int num : nums) 
    {
        if (num >= 0) 
        {
            subset.push_back(num);
        }
        else 
        {
            subset.insert(subset.begin(), num); // Вставляем отрицательные числа в начало
        }

        int sum = 0; // Проверяем сумму подмножества
        for (int element : subset)  { sum += element; }
        if (sum == subsetSum)   { break;  }
    }

    return subset;
}

int main() {
    std::vector<int> nums = { -7, -3, -2, 5, 8 };
    std::vector<int> result = greedySubsetSum(nums, 10);

    std::cout << "subset with null sum: ";
    for (int num : result) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
