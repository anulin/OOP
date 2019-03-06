#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;
/*
Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами. Найдите количество различных кратчайших путей между заданными вершинами. Требуемая сложность O(V+E).
Ввод: v:кол-во вершин(макс. 50000), n:кол-во ребер(макс. 200000), n пар реберных вершин, пара вершин v, w для запроса.
Вывод:количество кратчайших путей от v к w
*/
int minimalWays(vector<vector<int>> Graph, int vert1, int vert2, int N){
    vector<int> use(1), use2;
	use[0]=vert1;
	vector<bool> used(N);
	used[vert1]=true;
	int  counter = 0;
	bool finish = false;
    while (!finish) {
		for (int vert : use) {
			for (int vvert : Graph[vert]) {
				if (!used[vvert]) {
					use2.push_back(vvert);
				}
				if (vvert == vert2) { counter++; finish = true; }
			}
		}
		for(int vert : use2){
            used[vert]=true;
		}
		if(use2.empty()){
            break;
		}
		use = use2;
		use2.clear();
	}
	return counter;
}

int main() {
	int N, M, vert1, vert2;
	cin >> N >> M;
    vector<vector<int>> Graph(N);
	for (int i = 0; i < M; i++) {
		cin >> vert1 >> vert2;
		Graph[vert1].push_back(vert2);
		Graph[vert2].push_back(vert1);
	}
	cin >> vert1 >> vert2;
    cout << minimalWays(Graph,vert1,vert2, N) << endl;
}
