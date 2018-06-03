#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

void read_data(std::vector<int> &value, std::vector<int> &weight, int &bag_size, const std::string &filename, int n) {
    std::fstream f;
    f.open("/Users/wenhe/Documents/我的坚果云/课件/大二下课件/算法设计与分析/上机作业-第3章-2018/" + filename, std::ios::in);
    f >> bag_size;
    for (int i = 0; i < n; ++i) {
        int temp;
        f >> temp;
        weight.push_back(temp);
    }
    for (int i = 0; i < n; ++i) {
        int temp;
        f >> temp;
        value.push_back(temp);
    }
    f.close();
}

void knapsack(const std::vector<int> &value, const std::vector<int> &weight, int limited) {
    int n = int(value.size() - 1);
    int bag_size = limited;
    std::vector<std::vector<int>> m(value.size() + 1, std::vector<int>(bag_size + 1, 0));
    std::vector<int> result;
    int jMax = (weight[n] - 1) >= bag_size ? bag_size : (weight[n] - 1);
    for (int j = 0; j <= jMax; j++) {
        m[n][j] = 0;
    }
    for (int j = weight[n]; j <= bag_size; ++j) {
        m[n][j] = value[n];
    }
    for (int i = n - 1; i > 1; --i) {
        if ((weight[i] - 1) >= limited)
            jMax = limited;
        else
            jMax = weight[i] - 1;
        for (int j = 0; j <= jMax; ++j) {
            m[i][j] = m[i + 1][j];
        }
        for (int j = weight[i]; j <= limited; ++j) {
            if (m[i + 1][j] < m[i + 1][j - weight[i]] + value[i]) {
                m[i][j] = m[i + 1][j - weight[i]] + value[i];
            } else
                m[i][j] = m[i + 1][j];
        }
    }
    m[1][limited] = m[2][limited];
    if (bag_size >= weight[1])
        m[1][bag_size] =
                m[1][bag_size] >= (m[2][bag_size - weight[1]] + value[1]) ? m[1][bag_size] : (
                        m[2][bag_size - weight[1]] +
                        value[1]);

    for (int i = 1; i < n; ++i) {
        if (m[i][bag_size] != m[i + 1][bag_size]) {
            result.push_back(i);
            bag_size -= weight[i];
        }
    }
    std::cout << "m[n][limited]:" << m[n][limited] << std::endl;
    if (m[n][limited] > 0)
        result.push_back(n);
    int total_weight = 0, total_value = 0;
    for (auto i :result) {
        std::cout << i << " ";
        total_weight += weight[i];
        total_value += value[i];
    }
    std::cout << std::endl << "value: " << total_value << " weight: " << total_weight << std::endl;
}

int main() {
    std::vector<int> weight1, weight2, value1, value2;
    int bag_size1, bag_size2;
    read_data(value1, weight1, bag_size1, "bag1.txt", 50);
    read_data(value2, weight2, bag_size2, "bag2.txt", 100);
    knapsack(value1, weight1, bag_size1);
    knapsack(value2, weight2, bag_size2);
    return 0;
}