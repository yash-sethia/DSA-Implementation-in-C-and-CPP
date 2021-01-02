#include <bits/stdc++.h> 
  
using namespace std; 
  

bool cmp(pair <int, int> a, pair <int, int> b) 
{ 
    double r1 = (double)a.first / (double)a.second; 
    double r2 = (double)b.first / (double)b.second; 
    return r1 > r2; 
} 
  

double fractionalKnapsack(int W, pair <int, int> arr[], int n) 
{ 
    sort(arr, arr + n, cmp); 
  
    int curWeight = 0; 
    double finalvalue = 0.0; 
  
    
    for (int i = 0; i < n; i++)  
    { 
        
        if (curWeight + arr[i].second <= W)  
        { 
            curWeight += arr[i].second; 
            finalvalue += arr[i].first; 
        } 
  
        
        else 
        { 
            int remain = W - curWeight; 
            finalvalue += arr[i].first * ((double)remain / (double)arr[i].second); 
            break; 
        } 
    } 
  
    return finalvalue; 
} 

int knapSack(int W, pair <int, int> arr[], int n) 
{ 
    int i, w; 
    int K[n + 1][W + 1]; 
  
    for (i = 0; i <= n; i++)  
    { 
        for (w = 0; w <= W; w++)  
        { 
            if (i == 0 || w == 0) 
                K[i][w] = 0; 
            else if (arr[i - 1].second <= w) 
                K[i][w] = max(arr[i - 1].first + K[i - 1][w - arr[i - 1].second], K[i - 1][w]); 
            else
                K[i][w] = K[i - 1][w]; 
        } 
    } 
  
    return K[n][W]; 
} 
  

int main() 
{ 
    int W = 50; 
    pair <int, int> arr[] = { make_pair(60, 10), make_pair(100, 20), make_pair(120, 30) }; 
  
    int n = sizeof(arr) / sizeof(arr[0]); 
  
    cout << "Maximum value we can obtain in Fractional Kanpsack is = "<< fractionalKnapsack(W, arr, n)<<endl; 
    cout << "Maximum value we can obtain in 0 / 1 Knapsack by DP is = "<< knapSack(W, arr, n)<<endl; 
    return 0; 
}