#include <iostream>
#include <vector>
#include <unordered_set>
#include <map>
/*
Дан невзвешенный неориентированный граф. Найдите цикл минимальной длины.
Формат ввода
В первой строке вводятся два натуральных числа N и M, не превосходящих 10000. Далее идут M строк по 2 числа (от 0 до N-1) - индексы вершин между которыми есть ребро.

Формат вывода
Требуется вывести одно целое число равное длине минимального цикла. Если цикла нет, то вывести -1.
*/

using namespace std;
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
    vector<vector<int>> Graph(N);
    for(int i=0; i<M;i++){
        cin >> vert1 >>vert2;
        Graph[vert1].push_back(vert2);
        Graph[vert2].push_back(vert1);
    }
    vector<int> prev_i;
    prev_i.clear();
    unordered_set<int> used;
    used.clear();
    int i=0, j=0, length=200001, k;
    while(used.size()<N || i>0){
        for(;; ){
            for(j=0; used.find(Graph[i][j])!=used.end() && j<Graph[i].size();j++){
                if(Graph[i][j]!=prev_i[prev_i.size()-1]&& in_prev(prev_i,Graph[i][j])){
                    for(k=2;k<length && prev_i[prev_i.size()-k]!=Graph[i][j];k++ ){
                    }
                    if(k<length){length=k;}
                }
            }
            if(j<Graph[i].size()){
                prev_i.push_back(i);
                used.insert(i);
                i=Graph[i][j];
            }
            else{
                used.insert(i);
                break;
            }
        }
        i=prev_i.back();
        prev_i.pop_back();
    }
    if(length==200001){cout <<-1<<endl;}
    else{ cout << length+1 << endl;}

}
