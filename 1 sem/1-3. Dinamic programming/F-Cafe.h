#pragma once
#include <iostream>
#include <vector>

void compound() {
    int n;
    std::vector<int> v;
    std::vector<std::vector<int>> d; //min cost
    std::vector<std::vector<int>> t;
    
    std::cin >> n;
    v.resize(n+1);
    int s = 0;
    for (int i = 1; i <= n; i ++){
        std::cin >> v[i];
        s += v[i];
    }

    //init d
    d.resize(n+1, std::vector<int>(n+1));

    for (int i = 0; i <= n;i++){
        std::fill(d[i].begin(), d[i].end(), s+1);
    }
    // for (int i = 0; i <= n;i++){ 
    //     d[i][0] = 0;
    // }
    d[1][0] = v[1];
    d[1][1] = (v[1] > 100) ? v[1] : s+1;
    for (int i = 1; i <= n; i++){
        for (int j = 0; j < n; j++){
            if (v[i] <= 100){
                d[i][j] = std::min(d[i-1][j] + v[i], d[i-1][j+1]);
            } else if(j > 0){
                d[i][j] = std::min(d[i-1][j-1] + v[i], d[i-1][j+1]);  
            }
            else{
                d[i][j] = d[i-1][j+1];
            }
        }
    }
    
    int ans = 0;
    for (int i = s; i >=0;i--){
        if (d[n][i]!=s+1){
            ans = d[n][i];
            break;
        }
    }

    std::cout << ans << "\n";
    
}


// 5
// 3
// 1
// 4
// 2
// 1
