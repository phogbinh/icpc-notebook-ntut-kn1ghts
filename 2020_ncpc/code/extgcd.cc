// ax mod b = 1
// ax + by = 1,x=y=0
// a,b Relatively Prime
LL exgcd(LL a,LL b,LL &x,LL &y){
  if(b){
    LL tmd=exgcd(b,a%b,y,x);
    y-=a/b*x;
    return tmd;
  }
  x=1,y=0;
  return a;
}