#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include "Igraph.h"


class ListGraph : IGraph{
    vector<vector<int>> List;
    public:
        ListGraph(IGraph* Graph);
        ListGraph();
        void AddEdge(int from, int to);
        int VerticesCount()const;
        void GetNextVertices(int vertex, std::vector<int>& vertices)const;
        void GetPrevVertices(int vertex, std::vector<int>& vertices)const;


};
