#include<bits/stdc++.h>

#define rep(i,N) for(int i=0;i<N;i++)
#define rep2(i,N) for(int i=1;i<=N;i++)
using namespace std;
int RangedRand(int range_min, int range_max)
{
    int r=((double)rand() / RAND_MAX) * (range_max - range_min) + range_min;
    return r;
}
int main(){
    long long M;
    double eps;
    cin>>M>>eps;
    int N=10;
    cout<<N<<endl;
    vector<vector<int>>graph(N);

    //ランダムにグラフを作成
    bool connect[N][N]={};
    rep(k,10){
        connect[RangedRand(0,N)][RangedRand(0,N)]=true;
        //cout<<"rand ="<<RangedRand(0,N)<<endl;
    }
    rep(_,M){
        for(int k=0;k<N;k++){
            for(int l=k+1;l<N;l++){
                if(connect[k][l]){
                    cout<<"1";
                }else{
                    cout<<"0";
                }
            }
        }
        cout<<endl;
    }
    rep(i,100){
        cout<<RangedRand(0,M)<<endl;
    }
    
    return 0;
}