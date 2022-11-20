#include<bits/stdc++.h>
#define rep(i,N) for(int i=0;i<N;i++)
#define rep2(i,N) for(int i=1;i<=N;i++)
using namespace std;

int RangedRand(int range_min, int range_max)
{
    int r=((double)rand() / RAND_MAX) * (range_max - range_min) + range_min;
    return r;
}
//  同じ文字列かどうか反転する
bool isSameStr(string str1,string str2){
    if(str1.size()!=str2.size())return false;

    int n=str1.size();
    rep(i,n){
        if(str1[i]!=str2[i])return false;
    }
    return true;
}
//  文字列間の違う文字の数を数える
int getDiffBetweenStrs(string str1,string str2){
    
    int diff=0;
    int n=str1.size();
    rep(i,n)if(str1[i]!=str2[i])diff++;

    return diff;
}
//  文字列の各桁を確立epsで反転する
void addErrorToString(string& str,double eps){
    int len=str.size();
    rep(i,len){
        double randomNum=RangedRand(0,100);
        if(randomNum<=eps*100){
            if(str[i]=='0')str[i]='1';
            else if(str[i]=='1')str[i]='0';
        }
    }
    return;
}
void printDebug(int index,string nowHk,string original_graph){
        cout<<"# minIndex "<<index<<endl;;
        cout<<"# nowHk          "<<nowHk<<endl;
        cout<<"# original_graph "<<original_graph<<endl;
        return;
}
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
string getStringFromUnionFind(UnionFind uf,int N){
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
        #if debug
        cout<<"elem         "<<i<<" tree size ="<<uf.size(i)<<" root = " <<uf.root(i) <<endl;
        #endif
    }
    auto it=mp.begin();
    vector<int>vecInt;
    while(it!=mp.end()){
        #if debug
        cout<<"root = "<<it->first<<" size = "<<it->second<<endl;
        #endif
        vecInt.push_back(it->second);
        it++;
    }  
    sort(vecInt.begin(),vecInt.end());
    string str;
    rep(i,vecInt.size()){
        str.insert(0,to_string(vecInt[i]));
    }
    return str;
}
//  グラフを表す01の文字列を構造を表す文字列に変換する
string get01toString(string str,int N){
    return getStringFromUnionFind(getGraphFromString(str,N),N);
}


#define debug 0
int main(){
    int M;
    double eps;
    cin>>M>>eps;
    int N=(int)(floor)(sqrt(10*(double)M));
    N=4;
    cout<<N<<endl;
    multimap<string,int>graphStr;

    string graphStrVec[M];
    string graphStructureStrings[M];
    //  M個のグラフを生成
    rep(i,M){
            //ランダムにグラフを作成
        bool connect[N+2][N+2]={};
        rep(k,i){
            int x=RangedRand(0,N-1);
            int y=RangedRand(0,N-1);
            if(x==y){
                continue;
            }
            connect[x][y]=true;
        }
        string tmpStr="";
        for(int k=0;k<N;k++){
            for(int l=k+1;l<N;l++){
                if(connect[k][l]){
                    cout<<"1";
                    tmpStr.push_back('1');
                }else{
                    cout<<"0";
                    tmpStr.push_back('0');
                }
            }
        }
        cout<<endl;
        //rep(k,i)tmpStr[k]='1';  //グラフの辺の本数を変更
        //addErrorToString(tmpStr,eps);

        graphStrVec[i]=tmpStr;  //作成したグラフ
        graphStructureStrings[i]=get01toString(tmpStr,N);   //グラフの構造を保存
    }

    //ランダムなエラー率を反映する
    // rep(i,M){
    //     addErrorToString(graphStrVec[i],eps);
    // }
    

    rep(i,100){
        string nowHk;
        cin>>nowHk;
        int index=0;
        int min=1e9;
        //  現在得たグラフHkの構造
        string nowStructureHk=get01toString(nowHk,N);
        
#if 0
        //距離が最も近いものを探す
        rep(k,M){
            int nowDiff=getDiffBetweenStrs(nowStructureHk,graphStructureStrings[k]);
            if(min>nowDiff){
                min=nowDiff;
                index=k;
            }
        }
        
#elif 0
        //完全に一致するものを探す
        rep(k,M){
            if(isSameStr(nowStructureHk,graphStructureStrings[k])){
                index=k;
                break;
            }
        }
#else
        //  辺の数を数える
        int len=nowHk.size();
        int hLoadNum=0;
        rep(k,len)if(nowHk[k]=='1')hLoadNum++; 

        index=std::min(hLoadNum,M-1);
#endif

#if 0 //debug
        //printDebug(index,nowHk,graphStrVec[index]);
        printDebug(index,nowStructureHk,graphStructureStrings[index]);
#endif
        cout<<index<<endl;

    }
    
    return 0;
}