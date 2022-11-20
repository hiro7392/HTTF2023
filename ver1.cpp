#include<bits/stdc++.h>
#define rep(i,N) for(int i=0;i<N;i++)
#define rep2(i,N) for(int i=1;i<=N;i++)
using namespace std;

int RangedRand(int range_min, int range_max)
{
    int r=((double)rand() / RAND_MAX) * (range_max - range_min) + range_min;
    return r;
}

bool isSameStr(string str1,string str2){
    if(str1.size()!=str2.size())return false;

    int n=str1.size();
    rep(i,n){
        if(str1[i]!=str2[i])return false;
    }
    return true;
}
int getDiffBetweenStrs(string str1,string str2){
    
    int diff=0;
    int n=str1.size();
    rep(i,n)if(str1[i]!=str2[i])diff++;

    return diff;
}

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

#define printDebug 0
int main(){
    long long M;
    double eps;
    cin>>M>>eps;
    int N=5;
    cout<<N<<endl;
    vector<vector<int>>graph(N);

    
    multimap<string,int>graphStr;
    string graphStrVec[M];

    rep(i,M){
            //ランダムにグラフを作成
        bool connect[N][N]={};
        rep(k,i){
            connect[RangedRand(0,N)][RangedRand(0,N)]=true;
            //cout<<"rand ="<<RangedRand(0,N)<<endl;
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
        //graphStr.insert(make_pair(tmpStr,i));
        graphStrVec[i]=tmpStr;
        cout<<endl;
    }

    //ランダムなエラー率を反映する
    rep(i,M){
        addErrorToString(graphStrVec[i],eps);
    }
    //  グラフの辺の数
    int graphVNum[M]={};
   
    int p=(M*(M-1))/2;
    rep(i,M){
        rep(k,p){
            if(graphStrVec[i][k]=='1')graphVNum[i]++;
        }
    }

    rep(i,100){
        string nowHk;
        cin>>nowHk;
        int find=0;
        int min=1e9;
        int index=0;
#if 0
        //距離が最も近いものを探す
        rep(k,M){
            int nowDiff=getDiffBetweenStrs(nowHk,graphStrVec[k]);
            if(min>nowDiff){
                min=nowDiff;
                index=k;
            }
        }
        
#elif 0
        //完全に一致するものを探す
        rep(k,M){
            if(isSameStr(nowHk,graphStrVec[k])){
                index=k;
                break;
            }
        }
#else
        //  辺の数を数える
        int len=nowHk.size();
        int hLoadNum=0,gLoadNum=0;
        rep(k,len)if(nowHk[k]=='1')hLoadNum++; 
        rep(k,M){
            if(hLoadNum==graphVNum[k]){
                index=k;
                break;
            }
        }
#endif

#if debug
        printDebug(index,nowHk,raphStrVec[index]);
#endif
        cout<<index<<endl;
        
        // bitset<64> bs(131uL);
        // string bsStr=bs.to_string();

        // auto it =graphStr.find(bsStr);
        
        // if(it!=graphStr.end()){
        //     cout<<it->second<<endl;
        // }
        // else{
        //     cout<<RangedRand(0,M-1)<<endl;
        // }

    }
    
    return 0;
}