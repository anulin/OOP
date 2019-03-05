#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include "1MatrixGraph.h"


using namespace std;

MatrixGraph::MatrixGraph(IGraph* Graph){
    vector<int> nextvertices;
    Matrix.resize((*Graph).VerticesCount());
    for(int i=0;i<(*Graph).VerticesCount();i++){
        Matrix[i].resize((*Graph).VerticesCount());
        (*Graph).GetNextVertices(i,nextvertices);
        for(int j : nextvertices){
            Matrix[i][j]=true;
        }
    }
}
MatrixGraph::MatrixGraph(){
    Matrix.resize(100);
    for(int i=0;i<100;i++){
        Matrix[i].resize(100);
    }
}
void MatrixGraph::AddEdge(int from, int to){
    Matrix[from][to]=true;
}
int MatrixGraph::VerticesCount()const{
    return(Matrix.size());
}
void MatrixGraph::GetNextVertices(int vertex, std::vector<int>& vertices)const{
    vertices.clear();
    for(int i=0;i<Matrix[vertex].size();i++ ){
        if (Matrix[vertex][i]){
            vertices.push_back(i);
        }
    }
}
void MatrixGraph::GetPrevVertices(int vertex, std::vector<int>& vertices)const{
    vertices.clear();
    for(int i=0;i<Matrix.size();i++ ){
        if(Matrix[i][vertex]){
            vertices.push_back(i);
        }
    }
}
int main(){
    MatrixGraph a;
    a.AddEdge(1,2);
    return(0);
}


