#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <unordered_set>
using namespace std;
struct IGraph {
    virtual ~IGraph() {}


    virtual void AddEdge(int from, int to) = 0;

	virtual int VerticesCount() const  = 0;

    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const = 0;
    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const = 0;
};
struct SetGraph : IGraph{
    vector<unordered_set<int>> Set;

    SetGraph(IGraph* Graph){
        vector<int> nextvertices;
        Set.resize(Graph.VerticesCount())
        for(int i=0;i<Graph.VerticesCount();i++){
            Graph.GetNextVertices(i,nextvertices);
            for(int vertex: nextvertices){
                Set[i].insert(vertex);
            }
        }
    }
    SetGraph(){
        Set.resize(100);
    }
    void AddEdge(int from, int to)
    {
        Set[from].insert(to);
    }
    int VerticesCount(){return(Set.size());}
    void GetNextVertices(int vertex, std::vector<int>& vertices)
    {
        vertices.clear();
        std::copy(Set[vertex].begin(), Set[vertex].end(), std::back_inserter(vertices));
    }
    void GetPrevVertices(int vertex, std::vector<int>& vertices)
    {
        vertices.clear();
        for(int i=0;i<Set.size();i++ ){
            if (Set[i].find(vertex)!=used.end()){
                    vertices.push_back(i);
            }
        }
    }


};
