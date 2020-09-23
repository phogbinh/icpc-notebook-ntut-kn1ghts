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

    cin >> s ;
    for(int i = 1 ; i < s.length() ; i++ ){
        z[i] = max(0,min(z[i-x] , y - i + 1));
        while(i + z[i] < s.length() && s[z[i]] == s[i+z[i]] ){
            x = i ;
            y = i + z[i] ;
            z[i]++ ;
        }
    }

    for(int i = 0 ; i < s.length() ; i++)
        if(z[i] == s.length() - i && maxn >= s.length()-i ){
            cout << s.substr(0,z[i]);
            return 0 ;
        }
        maxn = max(maxn , z[i]);
    }
    cout << "Just a legend" ;
    return 0;
}