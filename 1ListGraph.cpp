#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include "1ListGraph.h"

using namespace std;

ListGraph::ListGraph(IGraph* Graph){
    vector<int> nextvertices;
    List.clear();
    for(int i=0;i<(*Graph).VerticesCount();i++){
        (*Graph).GetNextVertices(i,nextvertices);
        List.push_back(nextvertices);
    }
}
ListGraph::ListGraph(){
    List.clear();
    List.resize(100);
}
void ListGraph::AddEdge(int from, int to)
{
    for(int i=0; i<List[from].size();i++)
    {
        if(List[from][i]==to){return;}
    }
    List[from].push_back(to);
}
int ListGraph::VerticesCount()const{
    return List.size();
    }
void ListGraph::GetNextVertices(int vertex, std::vector<int>& vertices)const{
    vertices.clear();
    for(int i=0;i<List[vertex].size();i++ ){
        vertices.push_back(List[vertex][i]);
        }
    }
void ListGraph::GetPrevVertices(int vertex, std::vector<int>& vertices)const{
    vertices.clear();
    for(int i=0;i<List.size();i++ ){
        for (int j=0; j<List[i].size();j++){
            if(List[i][j]==vertex){
                vertices.push_back(i);
                break;
            }
        }
    }
}
int main(){
    ListGraph a;
    a.AddEdge(1,2);
    return(0);
}
