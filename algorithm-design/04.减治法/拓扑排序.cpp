
/*引自华为oj22,拓扑排序
题目描述如下：
输入：第一行包括两个数字：n和m(1<=m<=500),表示事务的数目和将要给出的关系数，接下来的m行，每行将给出某两个事物的大小关系，用小于号连接
输出：如果能够确定事物的关系，则输出，sorted sequence determined:xxxx;如果不能确定，则输出sorted sequence cannot be determined,
如果有矛盾则输出：confict
应该说这是非常基本与经典的拓扑排序题目,书上推荐的dfs出栈逆序法并不实用，还是找源的办法比较实用,特别注意的是对两种异常的识别
样例：
4 5
A<B
A<C
B<C
C<D
B<D
输出：
sorted sequence determined:ABCD*/
```cpp
#include<stack>
#include<iostream>
#include<vector>
using namespace std;
int mp[50][50];
int degree[50];
int N;
int M;
stack<int> source;
vector<int> v;
int ret;
int main(){
    cin>>N;
    cin>>M;
    char temp1,temp2,sym;
    for(int i=0;i<M;i++){
        cin>>temp1;
        cin>>sym;
        cin>>temp2;
        mp[temp1-'A'][temp2-'A']=1;
        degree[temp2-'A']++;
    }
    for(int i=0;i<N;i++){
        if(degree[i]==0) source.push(i);
    }
    int node=0;
    int count=0;
    while(!source.empty()) {
        //ret为1时，为多源，顺序不定
        if (source.size() > 1) ret = 1;
        node = source.top();
        v.push_back(node);
        count++;
        source.pop();
        for (int i = 0; i < N; i++) {
            if (mp[node][i]) {
                degree[i]--;
                if (degree[i] == 0) {
                    source.push(i);
                }
            }
        }
    }
    // count<N说明，有一些没有进入遍历，进入遍历的条件是成为源，不能成为源说明有环
    if(count<N){
        ret=2;
        cout<<"conflict";
    }
    if(ret==1) cout<<"sorted sequence cannot be determined";
    else if(!ret) {
        cout<<"sorted sequence determined:";
        for(int vv:v){
            char word=vv+'A';
            cout<<word;
        }
    }
}

     
```


