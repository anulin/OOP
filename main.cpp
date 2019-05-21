#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
/*Задано дерево с корнем, содержащее 𝑛 (1 ≤ 𝑛 ≤ 100 000) вершин, пронумерованных от 0 до n−1.
 Требуется ответить на 𝑚 (1 ≤ 𝑚 ≤ 10 000 000) запросов о наименьшем общем предке для пары вершин.
 Запросы генерируются следующим образом. Заданы числа 𝑎1, 𝑎2 и числа 𝑥, 𝑦 и 𝑧. Числа 𝑎3, . . . , 𝑎2𝑚       генерируются следующим образом: 𝑎𝑖 = (𝑥   ·𝑎𝑖−2+𝑦·𝑎𝑖−1+𝑧) mod 𝑛.
  Первый запрос имеет вид ⟨𝑎1, 𝑎2⟩. Если ответ на 𝑖−1-й запрос равен 𝑣, то 𝑖-й запрос имеет вид ⟨(𝑎2𝑖−1 + 𝑣) mod 𝑛, 𝑎2𝑖⟩.
Для решения задачи можно использовать метод двоичного подъёма.


Формат входных данных.
Первая строка содержит два числа: 𝑛 и 𝑚. Корень дерева имеет номер 0.
Вторая строка содержит 𝑛 − 1 целых чисел, 𝑖-е из этих чисел равно номеру родителя вершины 𝑖.
Третья строка содержит два целых числа в диапазоне от 0 до 𝑛−1: 𝑎1 и 𝑎2.
Четвертая строка содержит три целых числа: 𝑥, 𝑦 и 𝑧, эти числа неотрицательны и не превосходят 109.


Формат выходных данных.
Выведите в выходной файл сумму номеров вершин — ответов на все запросы.
*/

// Function object for solving LCA problem
class LCA{
public:
    // Builds and pre-processes tree using vector where i-th index stores father of i-th node
    LCA(vector<vector<unsigned>>& parents);

    // Returns LCA
    unsigned operator()(unsigned a, unsigned b);
    unsigned operator()(pair<unsigned, unsigned> query);

private:
    // DFS filling sparse table during pre-processing
    void DFS(unsigned node, unsigned parent);

    // Checks if a is ancestor of b
    bool isAncestor(unsigned a, unsigned b);

    // Timer used in DFS
    unsigned _timer;
    // Number of nodes
    size_t _n;
    // Size of ancestors table
    unsigned _l;

    // Stores children for i-th node
    vector<vector<unsigned>>& _tree;
    // Time of visiting i-th node
    vector<unsigned> _tin;
    // Time of leaving i-th node
    vector<unsigned> _tout;
    // Sparse table of ancestors
    vector<vector<unsigned>> _ancestors;
};

/******************************************************************************/

// Function object for generating next query
class NextQuery{
public:
    NextQuery(unsigned a0,
              unsigned b0,
              unsigned long x,
              unsigned long y,
              unsigned long z,
              unsigned n);

    pair<unsigned, unsigned> operator()(unsigned result);

private:
    unsigned _a;//вершина запроса 1
    unsigned _b;//вершина запроса 2
    unsigned long _x;//для генерации следующего запроса
    unsigned long _y;//для генерации следующего запроса
    unsigned long _z;//для генерации следующего запроса
    unsigned number_of_vertices;
};



int main() {
    // Initializing vector of parents
    unsigned n = 0;
    unsigned m = 0;
    cin >> n >> m;
    vector<vector<unsigned>> parents(n);
    for (unsigned i = 1; i < n; i++) {
        unsigned parent;
        cin >> parent; // parent of i
        parents[parent].push_back(i);
    }

    // Initializing queries
    unsigned a0 = 0;
    unsigned a1 = 0;
    cin >> a0 >> a1;
    unsigned long x = 0;
    unsigned long y = 0;
    unsigned long z = 0;
    cin >> x >> y >> z;
    NextQuery nextQuery(a0, a1, x, y, z, n);

    // Generating LCA object
    LCA lca(parents);
    unsigned long ans = 0;
    unsigned result = 0;
    for (unsigned i = 0; i < m; i++) {
        result = lca(nextQuery(result));
        ans += result;
    }
    cout << ans;

    return 0;
}



LCA::LCA(vector<vector<unsigned>>& parents)
        : _tree(parents)
        , _n(parents.size())
        , _l(static_cast<unsigned>(ceil(log2(_n))))
        , _tin(_n)
        , _tout(_n)
        , _ancestors(_n, vector<unsigned>(_l + 1))
        , _timer(0)
{
    DFS(0, 0);
}



unsigned LCA::operator()(unsigned a, unsigned b)
{
    if (isAncestor(a, b))
        return a;
    if (isAncestor(b, a))
        return b;
    // Rising up the tree
    for (int i = _l; i >= 0; --i)
        if (!isAncestor(_ancestors[a][i], b))
            a = _ancestors[a][i];
    return _ancestors[a][0];
}



unsigned LCA::operator()(pair<unsigned, unsigned> query)
{
    return LCA::operator()(query.first, query.second);
}



void LCA::DFS(unsigned node, unsigned parent)
{
    _tin[node] = _timer++;
    _ancestors[node][0] = parent;
    for (int i = 1; i <= _l; i++)
        _ancestors[node][i] = _ancestors[_ancestors[node][i - 1]][i - 1];
    for (size_t i = 0; i < _tree[node].size(); ++i) {
        unsigned to = _tree[node][i];
        if (to != parent)
            DFS(to, node);
    }
    _tout[node] = _timer++;
}



bool LCA::isAncestor(unsigned a, unsigned b)
{
    return _tin[a] <= _tin[b] && _tout[b] <= _tout[a];
}



NextQuery::NextQuery(unsigned a0,
                     unsigned b0,
                     unsigned long x,
                     unsigned long y,
                     unsigned long z,
                     unsigned n)
        : _a(a0)
        , _b(b0)
        , _x(x)
        , _y(y)
        , _z(z)
        , number_of_vertices(n)
{}



pair<unsigned, unsigned> NextQuery::operator()(unsigned result)
{
    pair<unsigned, unsigned> ans((_a + result) % number_of_vertices, _b);
    _a = (_a * _x + _b * _y + _z) % number_of_vertices;
    _b = (_b * _x + _a * _y + _z) % number_of_vertices;
    return ans;
}
