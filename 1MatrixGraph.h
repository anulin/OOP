#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include "Igraph.h"

using namespace std;

class MatrixGraph : IGraph{
    vector<vector<bool>> Matrix;
    public:
        MatrixGraph(IGraph* Graph);
        MatrixGraph();
        void AddEdge(int from, int to);
        int VerticesCount()const;
        void GetNextVertices(int vertex, std::vector<int>& vertices)const;
        void GetPrevVertices(int vertex, std::vector<int>& vertices)const;
};

