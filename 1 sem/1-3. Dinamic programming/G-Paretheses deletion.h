#pragma once
#include <iostream>
#include <vector>
#include <string>

void compound(){
    std::string s;
    std::cin >> s;
    int n = s.size();
    std::vector<std::vector<int>> d(n, std::vector<int>(n));
    std::vector<std::vector<std::string>> ans(n, std::vector<std::string>(n));
    for (int i = 0; i < n;i++){
        for (int j = 0; j < n; j++){
            d[i][j]= (i == j); //Если одну эту скобку убрать, то получится правильная посл-ть размера 0
        }
    }

    for (int j = 0; j < n; j++){// идем по диагонали
        for (int i = j-1; i >=0; i--){

            int id = 101;
            int m = 101;
            std::string best_s = "";
            if (s[i] == '(' && s[j] == ')' ||s[i] == '[' && s[j] == ']' || s[i] == '{' && s[j] == '}'){
                m = d[i+1][j-1];
                best_s = s[i] + ans[i+1][j-1] + s[j];
            }
            for (int k = i; k < j; k++){
                if (d[i][k]+d[k+1][j] < m){
                    m = d[i][k]+d[k+1][j];
                    best_s = ans[i][k]+ans[k+1][j];  
                }
            }

            ans[i][j] = best_s;    
            d[i][j] = m;
        }
    }

    std::cout << ans[0][n-1] << std::endl;

}