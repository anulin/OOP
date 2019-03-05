#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <unordered_set>
#include "Igraph.h"

using namespace std;

class ArcGraph : IGraph{
    vector<pair<int,int>> Arc;
    int counter;
    public :
        ArcGraph(IGraph* Graph);
        ArcGraph();
        void AddEdge(int from, int to);
        int VerticesCount()const;
        void GetNextVertices(int vertex, std::vector<int>& vertices)const;
        void GetPrevVertices(int vertex, std::vector<int>& vertices)const;
};
