#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <unordered_set>
#include "1SetGraph.h"

using namespace std;


SetGraph::SetGraph(IGraph* Graph){
    vector<int> nextvertices;
    Set.resize((*Graph).VerticesCount());
    for(int i=0;i<(*Graph).VerticesCount();i++){
        (*Graph).GetNextVertices(i,nextvertices);
        for(int vertex: nextvertices){
            Set[i].insert(vertex);
        }
    }
}
SetGraph::SetGraph(){
    Set.resize(100);
}
void SetGraph::AddEdge(int from, int to){
    Set[from].insert(to);
}
int SetGraph::VerticesCount()const{
    return(Set.size());
}
void SetGraph::GetNextVertices(int vertex, std::vector<int>& vertices)const{
    vertices.clear();
    std::copy(Set[vertex].begin(), Set[vertex].end(), std::back_inserter(vertices));
}
void SetGraph::GetPrevVertices(int vertex, std::vector<int>& vertices)const{
    vertices.clear();
    for(int i=0;i<Set.size();i++ ){
        if (Set[i].find(vertex)!=Set[i].end()){
                vertices.push_back(i);
        }
    }
}
int main(){
    SetGraph a;
    a.AddEdge(1,2);
    return(0);
}


