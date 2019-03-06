#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

/*dvudolnyy graph*/

bool dvudolnyy (vector<vector<int>> Graph, int N){
    vector<int> use(1), use2;
	vector<int> used(N);
	vector<bool> part1(N), part2(N);
	used[0]=true;
	part1[0]=true;
    while (true) {
		for (int vert : use) {
            used[vert]=true;
			for (int vvert : Graph[vert]) {
			    if (part1[vert] && !part1[vvert]) {
                    part2[vvert]=true;
                }
                else if(part2[vert] && !part2[vvert]){
                    part1[vvert]=true;
                }
                else{
                    return false;
                }
				if (!used[vvert]) {
                    use2.push_back(vvert);
				}
			}
		}
		if(use2.empty()){
            break;
		}
		use = use2;
		use2.clear();
	}
	return true;
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
	if(dvudolnyy(Graph,N)){
        cout << "YES" << endl;
	}
	else{
        cout << "NO" << endl;
	}
}
