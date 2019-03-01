#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
using namespace std;
struct IGraph {
    virtual ~IGraph() {}

	// Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

	virtual int VerticesCount() const  = 0;

    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const = 0;
    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const = 0;
};
struct MatrixGraph : IGraph{
    vector<vector<bool>> Matrix;

    MatrixGraph(IGraph* Graph){
        vector<int> nextvertices;
        Matrix.resize(Graph.VerticesCount())
        for(int i=0;i<Graph.VerticesCount();i++){
            Matrix[i].resize(Graph.VerticesCount())
            Graph.GetNextVertices(i,nextvertices);
            for(int j : nextvertices){
                Matrix[i][j]=true;
            }
        }
    }
    MatrixGraph(){
        Matrix.resize(100)
        for(int i=0;i<100;i++){
            Matrix[i].resize(100)
        }
    }
    void AddEdge(int from, int to)
    {
        vector Matrix[from][to]=true;
    }
    int VerticesCount(){return(Matrix.size());}
    void GetNextVertices(int vertex, std::vector<int>& vertices)
    {
        vertices.clear();
        for(int i=0;i<Matrix[vertex].size();i++ ){
            if (Matrix[vertex][i]){
                vertices.push_back(i);
            }
        }
    }
    void GetPrevVertices(int vertex, std::vector<int>& vertices)
    {
        vertices.clear();
        for(int i=0;i<Matrix.size();i++ ){
            if(Matrix[i][vertex]){
                vertices.push_back(i);
            }
        }
    }


};

