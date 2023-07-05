#include <bits/stdc++.h>
#include "printer.hpp"
using namespace std;
using namespace CP;
mt19937 kkksc03;
uniform_int_distribution<int> uid(0,36);
bool dfs(int sum[10],int mz,int qt){
    if (mz==4 && qt==1) return true;
    bool flag=false;
    if (mz<4){
        for (int i=1;i<=9;i++){
            if (sum[i]>=3){
                sum[i]-=3;
                flag=max(flag,dfs(sum,mz+1,qt));
                sum[i]+=3;
            }
        }
        for (int i=1;i<=7;i++){
            if (sum[i] && sum[i+1] && sum[i+2]){
                sum[i]--;sum[i+1]--;sum[i+2]--;
                flag=max(flag,dfs(sum,mz+1,qt));
                sum[i]++;sum[i+1]++;sum[i+2]++;
            }
        }
    }
    if (qt<1){
        for (int i=1;i<=9;i++){
            if (sum[i]>=2){
                sum[i]-=2;
                flag=max(flag,dfs(sum,mz,qt+1));
                sum[i]+=2;
            }
        }
    }
    return flag;
}
bool checkSevenPairs(int sum[10]){
    int tot=0;
    for (int i=1;i<=9;i++){
        if (sum[i]==2) tot++;
    }
    return tot==7;
}
vector<int> getTenpai(vector<int>v){
    int sum[10]={0,0,0,0,0,0,0,0,0,0};
    for (int i=0;i<v.size();i++) sum[v[i]]++;
    set<int>res;
    for (int i=1;i<=9;i++){
        sum[i]++;
        if (sum[i]<=4 && dfs(sum,0,0)) res.insert(i);
        if (checkSevenPairs(sum)) res.insert(i);
        sum[i]--;
    }
    vector<int>retval;
    for (int i=1;i<=9;i++){
        if (res.count(i)) retval.push_back(i);
    }
    return retval;
}
vector<int> RandomCards(){
    vector<int>v,res;
    for (int i=0;i<=35;i++){
        v.push_back(i/4+1);
    }
    bool vis[36];
    memset(vis,0,sizeof(vis));
    while (res.size()<13){
        int num=uid(kkksc03);
        if (vis[num]) continue;
        vis[num]=true;
        res.push_back(v[num]);
    }
    // sort(res.begin(),res.end());
    // for (int i=0;i<res.size();i++) cerr<<res[i];
    return res;
}
vector<int> Gen(){
    vector<int>res=RandomCards();
    vector<int>tp=getTenpai(res);
    while (tp.size()==0){
        res=RandomCards();
        tp=getTenpai(res);
    }
    return res;
}
bool Check(vector<int> c,vector<int> ans){
    printer(CLEARSCREEN,0);
    sort(c.begin(),c.end());
    cout<<"Question: ";
    for (int i=0;i<c.size();i++){
        printer(FG_BLUE | BOLD,1,to_string(c[i]).c_str());
    }
    cout<<endl;
    fflush(stdout);
    string k;cin>>k;
    bool a[10],b[10];
    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));
    for (int i=0;i<k.size();i++){
        if (k[i]>='1' && k[i]<='9') a[k[i]-'0']=1;
    }
    for (int i=0;i<ans.size();i++) b[ans[i]]=1;
    for (int i=1;i<=9;i++){
        if (a[i]==0 && b[i]==0){
            printer(FG_BLACK | BOLD,2," ",to_string(i).c_str());
        }
        else if (a[i]==1 && b[i]==0){
            printer(FG_PURPLE | BOLD,2," ",to_string(i).c_str());
        }
        else if (a[i]==1 && b[i]==1){
            printer(FG_GREEN | BOLD,2," ",to_string(i).c_str());
        }
        else if (a[i]==0 && b[i]==1){
            printer(FG_RED | BOLD,2," ",to_string(i).c_str());
        }
    }
    cout<<"提示：黑、绿：正确；紫、红：错误\n";
    cout<<"Input -1 to ";
    printer(FG_RED | BOLD,1,"exit");
    cout<<". Otherwise, continue: ";
    int t;cin>>t;
    if (t==-1) return false;
    return true;
}
int main(){
    kkksc03.seed(time(0));
    while (true){
        vector<int> t=Gen();
        if (!Check(t,getTenpai(t))) break;
    }
    return 0;
}