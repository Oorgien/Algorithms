#pragma once
#include <iostream>
#include <vector>



void compound() {
    std::string s1 = "", s2 = "";
    std::cin >> s1 >> s2;
    int n = s1.size();
    int m = s2.size();
    std::vector<std::vector<int>> d(n+1, std::vector<int>(m+1));

     for (int i = 0; i <= n; i++){
        for (int j = 0; j <= m; j++){
            if (i == 0 || j == 0){
                d[i][j] = i + j;
                continue;
            }
            if (s1[i-1] == s2[j-1]){
                d[i][j] = d[i-1][j-1];
            }
             else {
                 d[i][j] = std::min(std::min(d[i-1][j],d[i-1][j-1]),d[i][j-1])+1;
             }
         }
    }
    std::cout << d[n][m] << std::endl;
}