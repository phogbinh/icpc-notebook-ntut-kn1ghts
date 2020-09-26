#include <iostream>
#include <bits/stdc++.h>
#define LOCAL
#define MAXN 1000020
using namespace std;
int z[MAXN] = {} ;
int x=0 , y=0 , maxn = 0;
string s ;


int main()
{
#ifdef LOCAL
    freopen("in1.txt","r",stdin);
#endif // LOCAL

string s ;
int z[s.length()] = {} ;

    for(int i = 1 ; i < s.length() ; i++ ){ 
        z[i] = max(0,min(z[i-x] , y - i + 1));
        // z[i-x] 直接詢問 z[i-x] 共同前綴嘗是多少，
        // 如果當前是在目前的共同前綴中，那理所當然現在的 i 必會等於最初的共同前綴 i-x 值，
        // 如果不是，那必定會是 0。
        // y-i+1  此共同前綴理應只會有 y-i+1 個
        //如果 z[i-x] 比較小，代表沒有從 i 位置開始的前綴字串，否則 z[i-x] 應該要更大，所以
        //也就表示 z[i] == z[k]。
        // 如果 y-i+1 比較小，代表這次的共同前綴比較小，因為 z[i-x] 更大，也就代表應該有從這
        //裡開始的共同前綴
        while(i + z[i] < s.length() && s[z[i]] == s[i+z[i]] ){
            x = i ;
            y = i + z[i] ;
            z[i]++ ;
            //進行比對，查看 s[z[i]] 的位置是否等於 s[i+z[i]] 的位置是的話就比對下一個
        }
    }

    for(int i = 0 ; i < s.length() ; i++)
        if(z[i] == s.length() - i && maxn >= s.length()-i ){
        // z[i] == s.length() - i -> 如果 z[i] 等於字串剩下的長度那保證會有
        //後綴，通常 i 都會接近 s.length() 時才會符合
        // maxn >= s.length()-i -> 再從 0 to s.length() 時勢必會找到並經過
        //「最長共同前綴總和 (Longest Common Prefix)」，只要他比後綴還要長或相等 
        //(還需要先滿足第一個條件，才能判斷到此條件)，就肯定代表中間已經也有經
        //過「最長共同前綴總和 (Longest Common Prefix)」，尾巴這個並不會是第一次經過，
        //如果尾巴是那就代表他只有兩次的共同前綴。
            cout << s.substr(0,z[i]); // 輸出答案
            return 0 ;
        }
        maxn = max(maxn , z[i]);
        //經過時更新 「最長共同前綴總和 (Longest Common Prefix)」
    }
    cout << "Just a legend" ;
    return 0;
}