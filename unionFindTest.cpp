#include<bits/stdc++.h>
#define rep(i,N) for(int i=0;i<N;i++)
#define rep2(i,N) for(int i=1;i<=N;i++)
using namespace std;

//  UnionFindでグラフの構造を管理する
struct UnionFind {
    vector<int> par;

    UnionFind() { }
    UnionFind(int n) : par(n, -1) { }
    void init(int n) { par.assign(n, -1); }
    
    int root(int x) {
        if (par[x] < 0) return x;
        else return par[x] = root(par[x]);
    }
    
    bool issame(int x, int y) {
        return root(x) == root(y);
    }
    
    bool merge(int x, int y) {
        x = root(x); y = root(y);
        if (x == y) return false;
        if (par[x] > par[y]) swap(x, y); // merge technique
        par[x] += par[y];
        par[y] = x;
        return true;
    }
    
    int size(int x) {
        return -par[root(x)];
    }
};
int RangedRand(int range_min, int range_max)
{
    int r=((double)rand() / RAND_MAX) * (range_max - range_min) + range_min;
    return r;
}
//  01の文字列からグラフを生成する
UnionFind getGraphFromString(string graph,int n){
    int index=0;
    UnionFind uf(n);
    for(int i=0;i<n;i++){
        for(int k=i+1;k<n;k++){
            if(graph[index]=='1'){
                uf.merge(i,k);
            }
            index++;
        }
    }
    return uf;
}
//  unionFindのグラフの構造を文字列に変換
vector<int> getStringFromUnionFind(UnionFind uf,int N){
    map<int,int>mp;
    rep(i,N){
        int size,root;
        root=uf.root(i);
        size=uf.size(i);
        auto it=mp.find(root);
        // <key,value>=<root,size>でmapに格納する
        if(it==mp.end()){
            mp.insert(make_pair(root,size));
        }
        //cout<<"ufstring     "<<i<<" tree size ="<<uf_from_string.size(i)<<" root = " <<uf_from_string.root(i) <<endl;
        cout<<"elem         "<<i<<" tree size ="<<uf.size(i)<<" root = " <<uf.root(i) <<endl;
    }
    auto it=mp.begin();
    vector<int>vecInt;
    while(it!=mp.end()){
        cout<<"root = "<<it->first<<" size = "<<it->second<<endl;
        vecInt.push_back(it->second);
        it++;
    }  
    sort(vecInt.begin(),vecInt.end());
    
    return vecInt;
}

int main(){
    int M;
    double eps;
    cin>>M>>eps;
    int N=4;
    cout<<N<<endl;
    vector<vector<int>>graph(N);

    
    multimap<string,int>graphStr;
    string graphStrVec[M];
    vector<vector<int>> v(N);
    
    
    rep(i,M){
            //ランダムにグラフを作成
        bool connect[N+2][N+2]={};
        //UnionFind uf(N);
        rep(k,i){
            int x=RangedRand(0,N-1);
            int y=RangedRand(0,N-1);
            if(x==y){
                continue;
            }
            connect[x][y]=true;
            //cout<<"rand ="<<RangedRand(0,N)<<endl;
        }
        string tmpStr="";
        for(int k=0;k<N;k++){
            for(int l=k+1;l<N;l++){
                if(connect[k][l]){
                    cout<<"1";
                    tmpStr.push_back('1');
                    //v[k].push_back(l);
                    //v[l].push_back(k);
                    //uf.merge(k,l);
                }else{
                    cout<<"0";
                    tmpStr.push_back('0');
                }
            }
        }
        map<int,int>mp;
        UnionFind uf_from_string=getGraphFromString(tmpStr,N);
        graphStrVec[i]=tmpStr;
        cout<<endl;
        cout<<"graph string = "<<tmpStr<<endl;
        vector<int> strucVec=getStringFromUnionFind(uf_from_string,N);
        cout<<"graph size   = ";
        rep(i,strucVec.size())cout<<strucVec[i];
        cout<<endl;
        // rep(i,N){
        //     int size,root;
        //     root=uf.root(i);
        //     size=uf.size(i);
        //     auto it=mp.find(root);
        //     // <key,value>=<root,size>でmapに格納する
        //     if(it==mp.end()){
        //         mp.insert(make_pair(root,size));
        //     }
        //     //  cout<<"ufstring     "<<i<<" tree size ="<<uf_from_string.size(i)<<" root = " <<uf_from_string.root(i) <<endl;
        //     //  cout<<"elem         "<<i<<" tree size ="<<uf.size(i)<<" root = " <<uf.root(i) <<endl;
        // }
        // auto it=mp.begin();
        // while(it!=mp.end()){
        //     cout<<"root = "<<it->first<<" size = "<<it->second<<endl;
        //     it++;
        // }    
    }
    
    
    return 0;
}