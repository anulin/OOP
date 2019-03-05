#include <iostream>
#include <vector>
#include <unordered_set>
/*
Дан невзвешенный неориентированный граф. Найдите цикл минимальной длины.
Формат ввода
В первой строке вводятся два натуральных числа N и M, не превосходящих 10000. Далее идут M строк по 2 числа (от 0 до N-1) - индексы вершин между которыми есть ребро.

Формат вывода
Требуется вывести одно целое число равное длине минимального цикла. Если цикла нет, то вывести -1.
*/
using namespace std;

int MinimumCycle(vector<vector<int>> Graph, vector<vector<int>>WayLength, int N){
    int level=1, counter=-1;
    for(;level<(N+1)/2 && counter==-1;level++){
        for(int i = 0; i<N; i++){
            for(int j=0; j<N; j++){
                if(WayLength[i][j]==level){
                    for(int k : Graph[j]){
                        if(WayLength[i][k]==level+1 || WayLength[i][k]==level){
                            if(WayLength[i][k]==level){
                                cout << level+1+level << endl;
                                exit(0);
                            }
                            else{
                                counter= level+2 +level;
                            }
                        }
                        if(WayLength[i][k]==0){
                            if(level>1 || i!=k){
                                WayLength[i][k]=level+1;
                            }
                        }
                    }
                }
            }
        }
    }
    return counter;
}

bool in_prev(vector<int> prev_i, int i){
    for(int j : prev_i){
        if (j==i){return(true);}
    }
    return(false);
}
int main()
{
    int N, M, vert1, vert2 ;
    cin >> N >>M;
    vector<vector<int>> WayLength(N), Graph(N);
    vector<int> NextVertices;
    for(int i=0; i<N; i++){
        WayLength[i].resize(N);
    }
    for(int i=0; i<M;i++){
        cin >> vert1 >>vert2;
        Graph[vert1].push_back(vert2);
        Graph[vert2].push_back(vert1);
        WayLength[vert1][vert2]=1;
        WayLength[vert2][vert1]=1;
    }

    cout <<MinimumCycle(Graph,WayLength,N)<<endl;

}
