#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#define LOCAL
using namespace std;

int fp[100010] ,fq[100010] ;
int vfp[100010] ,vfq[100010] ;
int turn = 0 ;
vector<int> cp[100010] , cq[100010];

int BFSBMfp(int n){
    vfp[n] = turn  ;
    for(int i = 0 ; i < cp[n].size() ; i++ ){
        if(vfq[cp[n][i]] != turn){
            vfq[cp[n][i]] = turn ;
            if(fq[cp[n][i]] == -1 || BFSBMfp(fq[cp[n][i]])){
                fp[n] = cp[n][i] ;
                fq[cp[n][i]] = n ;
                return 1 ;
            }
        }
    }
    return 0 ;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n ,p ,q ,k ,x, y ;
    cin >> n ;
    while(n--){
        cin >> p >> q >> k ;
        int MaxnPQ = max(p,q);
        for(int i = 1 ; i <= MaxnPQ ; i++){
            cp[i].clear();
            fp[i] = -1;
            cq[i].clear();
            fq[i] = -1;
        }
        int cnt = 0;
        for(int i = 0 ; i < k ; i++){
            cin >> x >> y ;
            cp[x].push_back(y) ;
            cq[y].push_back(x) ;
            if(fp[x] == -1 && fq[y] == -1 ){
                fp[x] = y ;
                fq[y] = x ;
                cnt++ ;
            }
        }
        for(int i = 1 ; i <= p ; i++){
            if(fp[i] == -1 ){
                turn++;
                if(BFSBMfp(i))
                   cnt++;
            }
        }
        cout << cnt << '\n';
    }
    return 0;
}