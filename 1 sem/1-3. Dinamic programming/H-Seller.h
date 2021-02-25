#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// гамильтонов цикл
// https://habr.com/ru/post/191498/
// https://codeforces.com/blog/entry/337

int INT_MAX = 10e6;

void compound(){
    int n;
    cin >> n;
    vector<vector<int>> cities(n, vector<int>(n));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> cities[i][j]; 
        }
    }

    vector<vector<int>> dp((1 << n), vector<int>(n));
    vector<vector<int>> from((1 << n), vector<int>(n));

    for (int i = 0; i < n; i++)
            for (int j = 0; j < (1 << n); j++)
                dp[j][i] = INT_MAX;

    for (int i = 0; i < n; i++)
        dp[0][i] = 0;

    for (int mask = 0; mask < (1 << n); mask++){
        for (int i = 0; i < n; i++){
            if ((mask>>i & 1) == 1){
                for (int j = 0; j < n; j++){
                    int value = dp[mask - (1 << i)][j] + cities[i][j];
                    if (value < dp[mask][i]){
                        dp[mask][i] = value;
                        from[mask][i] = j;
                    }
                }
            }
        
        }
    }

    long long k, last, temp;
    long long minimum = INT_MAX;

    for (int i = 0; i < n; i++)
        if (dp[(1 << n) - 1][i] < minimum)
        {
            minimum = dp[(1 << n) - 1][i];
            last = i;
        }

    long long x = (1 << n) - 1;
    vector<long long> way;

    for (int i = 0; i < n; i++)
    {
        way.push_back(last + 1);
        temp = last;
        last = from[x][last];
        x -= (1 << temp);
    }

    cout << minimum << endl;
    
    for (int i = n - 1; i >= 0; i--)
        cout << way[i] << " ";
}