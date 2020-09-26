#include<iostream>
#include<bits/stdc++.h>
#define LOCAL
#define MAXN 50005
using namespace std;

int n , k , a , b ;
int ans , cnt ;
int Max[MAXN] , sz[MAXN] , rt ;
int head[MAXN], dis[MAXN];
bool vis[MAXN] ;
struct node{ 
    int v , nx ;
     //v = x 可以到此點，路徑為一 , nx 為 x 可以到此點的另外一個 Edge index，一樣是路徑為一 
}Edge[MAXN*2]; 
// 由於無向邊，但此結構是有向所以必須 *2， u -> v , v <- u 各一條。

void init(int n ){
    Max[0] = n ; 
    // Max 是此點最大子樹中的點加起來，0 我們不採用於是就將它設為題目初始長度
    ans = cnt = 0 ;
    for(int i = 0 ; i <= n ; i++){
        head[i] = -1 ; 
        //head 為 i 可以到某個點，路徑為一的 Edge index 
        // head = -1 是因為下面的遞迴停止關鍵為 ~i ， ~(-1) = 0  
        vis[i] = 0 ;
    }
}

void add(int u , int v){
    Edge[cnt].v = v ;
    Edge[cnt].nx = head[u] ;
    head[u] = cnt++ ;
}

//rt = root 
void get_rt(int u , int fa ){
    sz[u] = 1 ; Max[u] = 0 ; 
    //sz 是此點子樹的大小 // Max 是此點最大子樹中的點加起來
    for(int i = head[u] ; ~i ; i=Edge[i].nx){ 
        // 枚舉次點進行的兒子 = 進行長度為一的 BFS(玄學版)
        // 由於 i = Edge[i].nx 於是可以直接找到下一個 i to v 路徑為一的節點
        int v = Edge[i].v ; 
        if(vis[v] || v == fa )  continue ; 
        // vis 表示此點用過了，在第一次找重心時無用。之後會用到。
        get_rt(v,u); // 向下延伸
        Max[u] = max(Max[u] , sz[v]); 
        // 判斷這顆子樹有沒有比此點最大的子樹還要大
        sz[u] += sz[v] ; //更新 sz
    }
    Max[u] = max(Max[u] , n - sz[u]); 
    //用此點將樹分割，分割的兩部分是從此點展開的子樹與另外一個從父節點延伸的子樹 (n - sz[u])
    if(Max[rt] > Max[u]) 
    // 如果現在的最大子樹比較小那就採用現在的點
        rt =  u ;
}


void get_dis(int u , int fa , int d){ // fa = father , d = distance
    for(int i = head[u] ; ~i ; i= Edge[i].nx){
        int v = Edge[i].v ;
        if(vis[v] || v == fa ) continue ; 
        //如果 v == fa ，代表這點已經沒辦法再向下延伸
        // vis 如果此點有被用到就返回
        dis[++cnt] = d + 1 ; 
        // 由於這裡我們並不在意是哪個點到哪個點的路徑長，我們只在意此路徑長多少，於是我們就用 ++cnt，循序填滿。
        get_dis(v,u,dis[cnt]);
    }
}


int get_ans(int u , int d ){
    dis[cnt=1] = d ;
    get_dis(u,0,d) ;
    sort(dis+1 , dis+cnt+1) ; 
    // 由於 dis 裡面每一個都是從任意一個點到樹重心，透過公式(子樹 A 到樹重心 + 子樹 B 到樹重心 = k)，
    // 我們並不需要在意哪個點只需要在意距離長
    int l = 1 , ans = 0 ;

    while(l < cnt && dis[l] + dis[cnt] < k ) l++ ; 
    // 這時候的 cnt 因為 get_dis 不斷增加數量於是當前的 cnt 也會等於 dis 的右邊界。
    // 我們假設我們先使用 dis[l] 也就是最小路徑去跟其他條進行配合看是否能夠等於 k
    //如果 dis[l] + dis[cnt] 都沒有大於 k 就代表，怎樣都不會大於 k，於是將 l 範圍縮小增進，優化效率。

    while(l < cnt && dis[l] <= k - dis[l]){ 
        ans += upper_bound(dis + l + 1 , dis + cnt + 1 , k - dis[l]) -  \ 
                lower_bound(dis+l+1 , dis+cnt+1 , k-dis[l]);
        // 因為我們的 dis 右邊界是一，所以所有 dis +1
        // k - dis[l]，可以找出我們 k = dis[l] + x， x 為任意變數能夠滿足前述公式即可。
        l++ ; // 再換新的 dis[l] 來進行配合
    }
    return ans ;
}

void dfs(int u ){
    vis[u] = 1 ; // 被用過的點，也是我們用來分割子樹的標準
    //cout << rt << ' ' << u << '\n' ;
    ans += get_ans(u , 0); // 得到公式中的 k，裡面會有不合法狀態，圖片中的問題。 
    for(int i = head[u] ; ~i ; i = Edge[i].nx){
        int v = Edge[i].v ;
        if(vis[v]) continue ;
        ans -= get_ans(v , 1) ; // 移除掉不合法的狀態 
        // QUESTION: 為甚麼這行可以移除掉不合法狀態呢?
        /* 我們看看上面的圖，他們是不是共用了至少同一條路徑？，如果共用很多條也沒關係
        ，之後的 DFS 就會注意到他們並解決這些問題。
        於是我們就可以用 get_ans(v,1) 用子樹的下一個點來進行一次 DFS，
        我們在假設 x -> v 這條路徑會被共用，所以先直接設定成 1，
        這樣只要是不合法的答案在這邊都會被發現，就可以直接減掉就剩下合法答案了！

        讀者如果還是不懂，可以嘗試將途中橘色的線(共用路徑)進行 +1 後再用 son 去算 dis_ans(son,1)
         去算 a, b 看 k = 4 時是不是也會有一條 XD。
        */
        n = sz[v] , rt = 0 , get_rt(v,u); //由於子樹被切割，所以 n 的 size 也必須減少成子樹的大小。
        //由於樹被切割，所以必須重新尋找被切割樹後重心。
        dfs(rt); //再將樹進行切割，來配合公式。
    }
}

int main(){
//#ifdef LOCAL
//    freopen("in1.txt" , "r" , stdin);
//#endif // LOCAL

    cin >> n >> k ;
    init(n);
    for(int i =1; i < n ; i++){
        cin >> a >> b ;
        add(a,b);
        add(b,a);
    }
    rt = 0 ; get_rt(1,0);
    dfs(rt);
    cout << ans << '\n' ;

}