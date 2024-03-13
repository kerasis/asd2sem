#include <iostream>
#include <vector>

struct Item 
{
    int weight;
    int value;
};

int backpack(std::vector<Item>& items, int capacity) 
{
    int n = items.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacity + 1, 0)); // задаем матрицу которую потом будем заполнять динамически (изначально первый ряд нулевой тк в алгоритме мы используем предыдущий ряд матрицы))
    // суть в том что мы разделяем вес рюкзака на capacity частей и заполнять максимальную стоимость для текцщего веса рюкзака (для рюкзака вместимостью 1, 2 и тд -> сводим задачу к задаче для меньших размерностей)
    for (int i = 1; i <= n; i++) 
    {
        for (int w = 1; w <= capacity; w++) 
        {
            if (items[i - 1].weight <= w) 
            {
                dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - items[i - 1].weight] + items[i - 1].value); // рассматриваем 2 случая берем текущюю вещь или не берем с условием того что она не перевещивает
            }
            else 
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        std::cout << i + 1 << " " << dp[i][capacity]<< std::endl;
    }
    std::cout << std::endl;
    return dp[n][capacity];
}

int main() 
{
    int capacity;
    std::cout << "Size of backpack: ";
    std::cin >> capacity;

    int n;
    std::cout << "Number of things: ";
    std::cin >> n;

    std::vector<Item> items(n);

    for (int i = 0; i < n; i++) 
    {
        std::cout << "Weighi and walue " << i + 1 << ": ";
        std::cin >> items[i].weight >> items[i].value;
    }

    int maxTotalValue = backpack(items, capacity);
    std::cout << "Max value in backpack: " << maxTotalValue << std::endl;

}