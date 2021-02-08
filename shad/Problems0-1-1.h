#pragma once
#include <vector>
#include <iostream> 
#include <algorithm>

std::pair<std::vector<int>,int> read() {
    int n;
    std::cin >> n;
    std::vector<int> res;
    for (int i = 0; i < n; i++) {
        int val = 0;
        std::cin >> val;
        res.push_back(val);
    }
    return std::make_pair(res, n);
}


std::vector<int> solve(std::vector<int> arr, const int n) {
    /* las[i][0] = Длина самой длинной чередующейся подпоследовательности
        заканчивающийся индексом i и последний элемент больше
        чем его предыдущий элемент
        las[i][1] = длина самой длинной чередующейся подпоследовательности
        заканчивающийся индексом i и последний элемент меньше
        чем его предыдущий элемент */
    std::vector<size_t> las_length[] = {
        std::vector<size_t>(n, 1),
        std::vector<size_t>(n, 1)
    };
    std::vector<size_t> next_num[] = {
        std::vector<size_t>(n, 0),
        std::vector<size_t>(n, 0)
    };
    //Рассчитать значения снизу вверх
    std::vector<size_t> max_l = { 1, 1 };
    std::vector<int> res;
    for (int i = n-1; i >= 0; i--){
        // Рассмотрим все элементы как предыдущие arr [i]
        for (int j = i; j < n; j++){
            // Если arr [i] больше, то проверяем с помощью las_length [1][j]
            if (arr[j] < arr[i] && las_length[0][i] < las_length[1][j] + 1) {
                las_length[0][i] = las_length[1][j] + 1;
                next_num[0][i] = j;
            }
            // Если arr [i] меньше, то проверяем с помощью las_length [0][j]
            if (arr[j] > arr[i] && las_length[1][i] < las_length[0][j] + 1) {
                las_length[1][i] = las_length[0][j] + 1;
                next_num[1][i] = j;
            }
            if (las_length[0][i] > max_l[0]) {
                max_l[0] = las_length[0][i];
            }
            if (las_length[1][i] > max_l[1]) {
                max_l[1] = las_length[1][i];
            }
        }

    }
    size_t i = 0;
    int dir = max_l[0] > max_l[1] ? 0 : 1;
    do {
        res.push_back(arr[i]);
        i = next_num[dir][i];
        dir = !dir;
    } while (i != 0);

    return res;
}


//10
//1 4 2 3 5 8 6 7 9 10
//13
//8 7 4 3 2 5 6 9 8 7 3 2 4

void show(std::vector<int> res) {
    for (auto item : res) {
       std::cout << item << " ";
    }
}
