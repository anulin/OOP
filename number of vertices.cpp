#include <iostream>
#include <vector>
#include <unordered_set>
/*
number of vertices for connected graph
*/

using namespace std;

int NumberOfVertices (vector<vector<int>>Graph, vector<vector<int>> WayLength, int N){
    int level=1;
    bool NoVert;
    vector<bool> self(N), Out(N), In(N);
    for(;level<N;level++){
        NoVert=true;
        for(int i = 0; i<N; i++){
            for(int j=0; j<N; j++){
                if(WayLength[i][j]==level){
                    NoVert=false;
                    for(int k : Graph[j]){
                        if(WayLength[i][k]==0){
                            WayLength[i][k]=level+1;
                        }
                    }
                }
            }
        }
        if(NoVert){
            break;
        }
    }
    for(int i=0; i<N; i++){
        if(!self[i]){
            for(int j=0; j<N;j++){
                if(WayLength[i][j]!=0){
                    if(WayLength[j][i]==0){
                        Out[i]=true;
                        In[j]=true;
                    }
                    else if(j!=i){
                        self[j]=true;
                        In[j]=true;
                        Out[j]=true;
                    }
                }
            }
        }
    }
    int counterIn=0, counterOut=0;
    bool same;
    for(int i=0; i<N;i++){
        if(!In[i]){
            counterIn++;
        }
        if(!Out[i]){
            counterOut++;
        }
        if(!Out[i]&&!In[i]){
            same=true;
        }
    }
    if(counterIn==1 && counterOut==1 && same){
        return 0;
    }
    else if(counterIn>counterOut){
        return counterIn;
    }
    else{
        return counterOut;
    }
}


int main()
{
    int N, M, vert1, vert2 ;
    cin >> N >>M;
    vector<vector<int>> WayLength(N), Graph(N);
    for(int i=0; i<N; i++){
        WayLength[i].resize(N);
    }
    for(int i=0; i<M;i++){
        cin >> vert1 >>vert2;
        if(vert1 != vert2){
            Graph[vert1-1].push_back(vert2-1);
            WayLength[vert1-1][vert2-1]=1;
        }
    }
    cout << NumberOfVertices(Graph, WayLength, N);

}
