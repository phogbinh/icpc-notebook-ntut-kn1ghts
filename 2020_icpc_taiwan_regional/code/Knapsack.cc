#define W 1000 // Knapsack weight
#define N 100  // n item
int weight[N]; //item weight
int value[N];  //item value 
int bag[W][2];

// 0/1 Knapsack
void ZeroOne(){
  memset(bag,0,sizeof(bag));
  for(int i = 0 ; i < N ; i++ ){
    for(int j = 0 ; j < W ; j++ )
      if( j >= weight[i] )
        bag[j][1] = max( bag[j][0] ,bag[j-weight[i]][0] + value[i] );
    
    for(int j = 0 ; j < W ; j++ )
      bag[j][0] = bag[j][1];
  }
}


// group knapsack
int group;    // hou much groups?
int how_many; // one group has many items? 
int WEIGHT,VALUE;

void Grouping(){
  memset(bag,0,sizeof(bag));
  for(int i = 0 ; i < group ; i++ ){
    for(int j = 0 ; j < how_many ; j++ ){
      scanf("%d %d",&WEIGHT,&VALUE);

      for(int k = 0 ; k < W ; k++ ){
        if( j >= WEIGHT ){
          bag[j][1] = max( bag[j][1] , bag[j][0] );
          bag[j][1] = max( bag[j][1] ,bag[j-WEIGHT][0] + VALUE );
        }
      }
    }
    
    for(int j = 0 ; j < W ; j++ )
      bag[j][0] = bag[j][1];
  }
}

// mulipte knapsack
int limit[N]; // item limit 
void Multiple() {
  for(int i = 0 ; i < N ; i++ ){
    int tmp = 1;
    while( tmp <= weight[i] ){
      for(int j = 0 ; j < W ; j++)
        if( j >= weight[i]*tmp )
          bag[j][1] = max( bag[j-weight[i]*tmp][0] + value[i]*tmp
                        , bag[j][0] );
      
      for(int j = 0 ; j < W ; j++ )
        bag[j][0] = bag[j][1];
      
      weight[i] = weight[i]-tmp;
      tmp = tmp*2;
    }
    if( weight[i] > 0 ){
      for(int j = 0 ; j < W ; j++)
        if( j >= weight[i]*tmp )
          bag[j][1] = max( bag[j-weight[i]*tmp][0] + value[i]*tmp , bag[j][0] );
      
      for(int j = 0 ; j < W ; j++ )
        bag[j][0] = bag[j][1];
    }
  }
}

// inf
void Unlimited(){
  memset(bag,0,sizeof(bag));
  for(int i = 0 ; i < N ; i++ ){
    for(int j = 0 ; j < W ; j++ )
      if( j >= weight[i] )
        bag[j][1] = max( bag[j][0] ,bag[j-weight[i]][1] + value[i] );
    
    for(int j = 0 ; j < W ; j++ )
      bag[j][0] = bag[j][1];
  }
}
