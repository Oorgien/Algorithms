#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void compound(){
    int n,m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m, 1));
    vector<vector<vector<long long>>> d(n+1, vector<vector<long long>>(m, vector<long long>((1 << m))));

    for (int i = 0; i < n; i ++){
        for (int j = 0; j < m; j ++){
            char tmp;
            cin >> tmp;
            if (tmp == '.'){
                a[i][j] = 1;
            }
            else{ 
                a[i][j] = 0;
            }
        }
    }
    d[0][0][0] = 1;
    // по столбцам
    for (int i = 0; i < n; i++){
        // по строкам
        for (int j = 0; j < m; j++){
            // по профилям
            for (int p = 0; p < (1 << m); p++){
                // доминошка уже торчит
                if ( (p & (1 << j) ) || a[i][j] == 0){
                    long long p_new = (p | (1 << j)) - (1 << j);
                    d[i + ((j+1)/m)][(j+1) % m][p_new] += d[i][j][p];  
                }
                // можно поставить горизонтальную доминошку
                if (i < n-1 &&
                    a[i][j] == 1 && 
                    a[i+1][j] == 1 &&
                    ((p & (1 << j)) == 0))
                {
                    long long p_new = p + (1 << j);
                    d[i + ((j+1)/m)][(j+1) % m][p_new] += d[i][j][p];
                }
                // можно поставить вертикальную доминошку
                if (j < m-1 &&
                    ((p & (3 << j)) == 0) &&
                    a[i][j] == 1 && a[i][j+1] == 1)
                    {
                        long long p_new = p + (2 << j);
                        d[i + ((j+1)/m)][(j+1) % m][p_new] += d[i][j][p];
                }
                
            }
        }
        
    }
    
    cout << d[n][0][0] << endl;
}