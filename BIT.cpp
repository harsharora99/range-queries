#include<bits/stdc++.h>

using namespace std;

//Here comes the code to process updates and range queries using Fenwick tree.

const int N = 1e6 + 5;

long long BIT[N];

void update(int x,long long val) {
  while(x < N) {  
    BIT[x] += val;  
    x += (x & (-x));  
  } 
}

long long query(int x) {  
  long long res = 0;  
  while(x > 0) {  
    res += BIT[x];  
    x -= (x & (-x));  
  } 
  return res; 
} 

int main(){
  memset(BIT, 0, sizeof(BIT));
  
  return 0;
}
