#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <unordered_set>

using namespace std;

int main()
{
    int N, M, vert1, vert2 ;
    cin >> N >>M;
    vector<vector<int>> Graph(N);
    for(int i=0; i<M;i++){
        cin >> vert1 >>vert2;
        Graph[vert1].push_back(vert2);
        Graph[vert2].push_back(vert1);
    }
    cin>>vert1>>vert2;
    vector<int> use, use2;
    use=Graph[vert1];
    int i=vert1, j=0, length=200001, way_length=1, counter=0, level=1;
    for(;level!=-1;){
        for(int vert:use){
            for(int vvert:Graph[vert]){
                use2.push_back(vvert);
                if(vvert==vert2){counter++; level=-1;}
            }

        }
        use=use2;

        use2.clear();
    }

    cout << counter << endl;

}
