#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <unordered_set>
#include "Igraph.h"

using namespace std;

class SetGraph : IGraph{
    vector<unordered_set<int>> Set;
    public:
        SetGraph(IGraph* Graph);
        SetGraph();
        void AddEdge(int from, int to);
        int VerticesCount()const;
        void GetNextVertices(int vertex, std::vector<int>& vertices)const;
        void GetPrevVertices(int vertex, std::vector<int>& vertices)const;
};
