#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <unordered_set>
#include "1ArcGraph.h"


using namespace std;

ArcGraph::ArcGraph(IGraph* Graph){
    vector<int> nextvertices;
    counter=(*Graph).VerticesCount();
    for(int i=0;i<(*Graph).VerticesCount();i++){
        (*Graph).GetNextVertices(i,nextvertices);
        for(int vertex: nextvertices){
            Arc.push_back(make_pair(i,vertex));
        }
    }
}
ArcGraph::ArcGraph(){
    counter=100;
}
void ArcGraph::AddEdge(int from, int to){
    Arc.push_back(make_pair(from,to));
}
int ArcGraph::VerticesCount()const{
    return counter;
}
void ArcGraph::GetNextVertices(int vertex, std::vector<int>& vertices)const{
    vertices.clear();
    for(pair<int,int> edge : Arc){
        if(edge.first==vertex){
            vertices.push_back(edge.second);
        }
    }
}
void ArcGraph::GetPrevVertices(int vertex, std::vector<int>& vertices)const{
    vertices.clear();
    for(pair<int,int> edge : Arc){
        if(edge.second==vertex){
            vertices.push_back(edge.first);
        }
    }
}
int main(){
    ArcGraph a;
    a.AddEdge(1,2);
    return(0);
}
