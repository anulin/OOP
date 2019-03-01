#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <unordered_set>

using namespace std;
bool allused(vector<int> verts_of_i, unordered_set<int> used){
    for(int vert : verts_of_i){
        if (used.find(vert)==used.end()){return(false);}
    }
    return(true);
}
bool in_prev(vector<int> prev_i, int i){
    for(int j : prev_i){
        if (j==i){return(true);}
    }
    return(false);
}
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
    vector<int> prev_i, use, use2;
    prev_i.clear();
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
