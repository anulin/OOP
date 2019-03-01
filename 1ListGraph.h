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
struct ListGraph : IGraph{
    vector<vector<int>> List;

    ListGraph(IGraph* Graph){
        vector<int> nextvertices;
        List.clear();
        for(int i=0;i<Graph.VerticesCount();i++){
            Graph.GetNextVertices(i,nextvertices);
            List.push_back(nextvertices);
        }
    }
    ListGraph(){
        List.clear().resize(100);
    }
    void AddEdge(int from, int to)
    {
        for(int i=0; i<List[from].size();i++)
        {
            if(List[from][i]==to){return;}
        }
        vector List[from].push_back(to);
    }
    int VerticesCount(){return(List.size());}
    void GetNextVertices(int vertex, std::vector<int>& vertices)
    {
        vertices.clear;
        for(int i=0;i<List[vertex].size();i++ ){
            vertices.push_back(List[vertex][i]);
        }
    }
    void GetPrevVertices(int vertex, std::vector<int>& vertices)
    {
        vertices.clear;
        for(int i=0;i<List.size();i++ ){
            for (int j=0; j<List[i].size();j++){
                if(List[i][j]==vertex){
                    vertices.push_back(i);
                    break;
                }
            }
        }
    }


};
