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

