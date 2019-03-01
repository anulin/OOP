#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <unordered_set>

using namespace std;
struct IGraph {
    virtual ~IGraph() {}

	// Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

	virtual int VerticesCount() const  = 0;

    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const = 0;
    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const = 0;
};
struct ArcGraph : IGraph{
    vector<pair<int,int>> Arc;
    int counter;
    ArcGraph(IGraph* Graph){
        vector<int> nextvertices;
        counter=Graph.VerticesCount();
        for(int i=0;i<Graph.VerticesCount();i++){
            Graph.GetNextVertices(i,nextvertices);
            for(int vertex: nextvertices){
                Arc.push_back(make_pair(i,vertex));
            }
        }
    }
    ArcGraph(){
        counter=100;
    }
    void AddEdge(int from, int to){
        vector Arc.push_back(make_pair(from,to));
    }
    int VerticesCount(){
        return(counter);
    }
    void GetNextVertices(int vertex, std::vector<int>& vertices)
    {
        vertices.clear();
        for(pair<int,int> edge : Arc){
            if(edge.first()==vertex){
                vertices.push_back(edge.second());
            }
        }
    }
    void GetPrevVertices(int vertex, std::vector<int>& vertices){
        vertices.clear();
        for(pair<int,int> edge : Arc){
            if(edge.second()==vertex){
                vertices.push_back(edge.first());
            }
        }
    }


};
