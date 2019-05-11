#include <iostream>
#include <random>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <ctime>
#include <math.h>

using namespace std;
/*

*/
struct edge{
    short vert1;
    short vert2;
    double weight;
};
bool operator< (const edge p, const edge q){
    return q.weight < p.weight;
}
short find_set (short v, vector<short> &vertices) {
	if (v == vertices[v]){
		return v;
	}
	return vertices[v] = find_set (vertices[v],vertices);
}
void dsu_unite (short a, short b, vector<short> &vertices,vector<short> &Rank) {
	a = find_set (a,vertices);
	b = find_set (b,vertices);
	if (a != b){
        if (Rank[a] < Rank[b]){
			swap (a, b);
        }
		vertices[b] = a;
        if (Rank[a] == Rank[b]){
			++Rank[a];
        }
	}
}
vector<double> MinPairs(vector<vector<double>>&Graph, int N){
    vector<double> potentV (N+1), potentU(N+1), pairs (N+1), way (N+1);
    int inf=10000000;
    for (int i=1; i<=N; ++i) {
        pairs[0] = i;
        int j0 = 0;
        vector<double> minv (N+1, inf);
        vector<bool> used (N+1, false);
        do {
            used[j0] = true;
            double i0 = pairs[j0],  delta = inf,  j1;
            for (int j=1; j<=N; ++j){
                if (!used[j]) {
                    double cur = Graph[i0][j]-potentU[i0]-potentV[j];
                    if (i0==j)
                        cur=inf;
                    if (cur < minv[j])
                        minv[j] = cur,  way[j] = j0;
                    if (minv[j] < delta)
                        delta = minv[j],  j1 = j;
                }
            }
            for (int j=0; j<=N; ++j){
                if (used[j])
                    potentU[pairs[j]] += delta,  potentV[j] -= delta;
                else
                    minv[j] -= delta;
            }
            j0 = j1;
        } while (pairs[j0] != 0);
        do {
            int j1 = way[j0];
            pairs[j0] = pairs[j1];
            j0 = j1;
        } while (j0);
    }
    return pairs;
}
void search_euler (int v, vector<vector<short>> &tree, vector <short> &path){
    int tmp;
    for (int i = 0; 0 < tree[v].size (); ++ i){
        tmp=tree[v][0];
        for(int j=0;j<tree[tmp].size();j++){//удаляем то, откуда пришли
            if(tree[tmp][j]==v){
                tree[tmp].erase(tree[tmp].begin()+j);
                break;
            }
        }
        tree[v].erase(tree[v].begin());
        search_euler (tmp, tree, path);
    }
    path.push_back (v);
}

double Kruskal(vector<vector<double>>Graph, short N) {
    priority_queue<edge>use;
	edge edg;
	for(short i=1;i<=N;i++){
        for(short j=i+1;j<=N;j++){
            edg.vert1=i;
            edg.vert2=j;
            edg.weight=Graph[i][j];
            use.push(edg);
        }
    }

	vector<short> vertices(N+1);
	vector<short>Rank(N+1);
	vector<vector<short>>tree(N+1);
	double weight=0;
	int counter=0;
    vector<bool>Odd(N+1);
    for (short i=0; i<=N; ++i){
        vertices[i] = i;
        Rank[i]=0;
    }
    while (counter<N-1){
        edg = use.top();

        if (find_set(edg.vert1,vertices) != find_set(edg.vert2,vertices)) {
            tree[edg.vert1].push_back(edg.vert2);
            tree[edg.vert2].push_back(edg.vert1);
            Odd[edg.vert1]=!Odd[edg.vert1];
            Odd[edg.vert2]=!Odd[edg.vert2];
            counter++;
            dsu_unite (edg.vert1, edg.vert2,vertices,Rank);
        }
		use.pop();
	}
	counter=0;
	for(short i=1;i<=N;i++){
        if(Odd[i])
            counter++;
	}
	vector<short> dict(counter+1);
	vector<vector<double>> oddgraph(counter+1,vector<double>(counter+1));
	short k=1,m=1;
	for(short i=1;i<=N;i++){
        if(Odd[i]){
            dict[k]=i;
            for(short j=1;j<=N;j++){
                if(Odd[j]){
                    oddgraph[k][m]=Graph[i][j];
                    m++;
                }
            }
            m=1;
            k++;
        }
	}
	vector<double> added(counter+1);
	added=MinPairs(oddgraph,counter);
	for(double i=1;i<counter+1; i++){//дополняем дерево до эйлерова
        tree[dict[i]].push_back(dict[added[i]]);
	}
	vector<bool>used(N+1);
	short prev=100;

	vector <short> path;
	search_euler(1,tree, path);
	for(short i=0; i< path.size();i++){
        if(!used[path[i]] && i!=0){
            used[path[i]]=1;
            weight+=Graph[prev][path[i]];
            //cout<<prev<<';'<<path[i]<<';'<<Graph[prev][path[i]]<<' '<< path[0]<<endl;
            prev=path[i];
        }
        else if(i==0)
            prev=path[i];

	}

	return weight+Graph[path[0]][prev];
}


void GenerateGraph(vector<vector<double>>&Graph, int N){
    normal_distribution<double> distribution(0,1);
    default_random_engine generator;
    generator.seed(time(0));
    vector<pair<double,double>> Vertices(N+1);
    double x,y;
    for(int i=1;i<N+1;i++){
        Vertices[i].first=distribution(generator);
        Vertices[i].second=distribution(generator);
        y=Vertices[1].second;
    }
    for (int i = 1; i < N+1; i++) {
		for(int j=i+1; j<N+1;j++){

            x=Vertices[i].first-Vertices[j].first;
            y=Vertices[i].second-Vertices[j].second;
            Graph[i][j]=sqrt(x*x+y*y);
            //cout<<Vertices[i].second<<' '<<Vertices[j].second<<' '<<Graph[i][j]<<endl;
            Graph[j][i]=Graph[i][j];
		}
	}
}
double recursion(vector<vector<double>>Graph,vector<int> vertices, double way, int pos){
    vector<int> verts=vertices;
    int vert;
    double temp,currentWay;
    bool first=1;
    if(vertices.size()==1){
        return way+Graph[1][pos];
    }
    currentWay=way;
    for(int i=1;i< verts.size();i++){
        vert=verts[i];
        verts.erase(verts.begin()+i);
        temp=recursion(Graph, verts, way+Graph[pos][vert], vert);
        if(temp<currentWay||currentWay==0||first){
            currentWay=temp;
            //if(vertices.size()==10)
                //cout<<Graph[pos][vert]<<endl;
            first=false;
        }
        verts=vertices;
    }
    return currentWay;
}
double solve (vector<vector<double>>Graph,int N){
    vector<int> vertices(N);
    for(int i=1;i<=N;i++){
        vertices[i-1]=i;
    }

    return recursion(Graph,vertices,0,1);
}

int main() {
	int M,vert1,vert2,weight;
	double counter;
	edge edg;
	for(int sz=2;sz<11;sz++){
        vector<vector<double>>Graph(sz+1,vector<double>(sz+1));
        for(int j=0;j<100;j++){
            GenerateGraph(Graph,sz);
            counter+=(Kruskal(Graph, sz)-solve(Graph, sz));
            M++;
        }
        cout<<sz<<':'<<counter/M<<endl;
        counter=0;
        M=0;
	}

}
