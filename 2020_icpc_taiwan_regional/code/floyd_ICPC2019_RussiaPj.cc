#include <iostream>
#include <bits/stdc++.h>
#define LOCAL
using namespace std;
char before[520][520] = {} ;
int after[520][520] = {} ;

int main()
{
#ifdef LOCAL
    freopen("in1.txt" , "r" , stdin );
#endif // LOCAL

    int n ;
    cin >> n ;
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++)
            cin >> before[i][j] ;
    }

    for(int i = 0 ; i < n ; i++){
        for(int j = i+1 ; j < n ; j++){
            int sum = 0 ;
            for(int k = i + 1 ; k < j ; k++){
                if(after[i][k])
                    sum += before[k][j]-'0' ;
            }

            if( (sum +1) % 10 == before[i][j] - '0'){
                after[i][j] = 1 ;
            }

        }
    }

    for(int i = 0 ; i < n ; i++){
        for(int j = 0; j < n ; j++)
            cout << after[i][j] ;
        cout << '\n' ;
    }

    return 0;
}