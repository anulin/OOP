#include <iostream>
#include <iomanip>
using namespace std;

/*
Реализуйте структуру данных “массив строк” на основе декартового дерева по неявному ключу со следующими методами:
// Добавление строки в позицию position.
// Все последующие строки сдвигаются на одну позицию вперед.
void InsertAt( int position, const std::string& value );
// Удаление строки из позиции position.
// Все последующие строки сдвигаются на одну позицию назад.
void DeleteAt( int position );
// Получение строки из позиции position.
std::string GetAt( int position );
Все методы должны работать за O(log n) в среднем, где n – текущее количество строк в массиве.

Формат входных данных.
Первая строка содержит количество команд k ≤ 106.
Последующие k строк содержат описания команд:
Команда "+ 10 hello" означает добавление строки hello в позицию 10.
Команда “- 14 16” означает удаление строк от позиции 14 до позиции 16 включительно.
Команда “? 33” означает запрос на вывод строки из массива в позиции 33.

Формат выходных данных.
Выведите все строки, запрошенные командами “?”.
*/

// Treap with implicit key
class ImplicitTreap{
public:
    ImplicitTreap();
    ~ImplicitTreap();

    // InsertAts string into position
    void InsertAt(int position, const string& value);
    // DeleteAts string by position
    void DeleteAt(int position);
    // Clears tree
    void clear();
    // Returns string by position
    string GetAt(int position) const;

private:
    // Structure implementing node
    struct Node{
        Node(const string& value);

        // Fixes treeSize
        void fix();

        // Stores size of subtree
        int treeSize;
        // Priority of current node
        int priority;
        // Value to store
        string value;

        // Pointers tp left and right children
        Node* left;
        Node* right;
    };

private:
    // Splits tree by position, returns two result trees
    pair<Node*, Node*> split(Node* node, int position);
    // Merges two trees, returns result tree
    Node* merge(Node* node1, Node* node2);
    // Recursive function for clearing the tree
    void clear(Node* node);

private:
    // Pointer to root
    Node* _root;
};



int main() {
    int n = 0;
    cin >> n;
    ImplicitTreap stringArray;
    for (int i = 0; i < n; i++) {
        char cmd;
        cin >> cmd;
       // cout <<cmd<<';'<<endl;
        switch(cmd){
            case '+': {
                int position = 0;
                string val = "";
                cin >> position >> val;
                stringArray.InsertAt(position, val);
                break;
            }
            case '?': {
                int position = 0;
                cin >> position;
                cout << stringArray.GetAt(position) << '\n';
                break;
            }
            default: {
                int pos1, pos2;
                cin >> pos1 >> pos2;
                for(int i = 0; i <=pos2-pos1;i++)
                    stringArray.DeleteAt(pos1+i);
                break;
            }
        }
    }
    return 0;
}



ImplicitTreap::ImplicitTreap()
        : _root(nullptr)
{}



ImplicitTreap::~ImplicitTreap()
{
    clear();
}



void ImplicitTreap::clear()
{
    clear(_root);
    _root = nullptr;
}


void ImplicitTreap::clear(Node* node)
{
    if (node == nullptr)
        return;
    clear(node->left);
    clear(node->right);
    delete node;
}

void ImplicitTreap::InsertAt(int position, const string& value)
{
    Node* current = new Node(value);
    // Split tree by position and merge new node with right tree then merge result with left tree
    pair<Node*, Node*> ans = split(_root, position);
    Node* right = merge(current, ans.second);
    _root = merge(ans.first, right);
}


void ImplicitTreap::DeleteAt(int position)
{
    // Split required node from both sides and merge two other trees
    pair<Node*, Node*> ans1 = split(_root, position);
    pair<Node*, Node*> ans2 = split(ans1.second, 1);// было 1
    delete ans2.first;
    _root = merge(ans1.first, ans2.second);
}



string ImplicitTreap::GetAt(int position) const
{
    // Going down the tree
    int l;
    Node* node = _root;
    do {
        l = (node->left != nullptr)?(node->left->treeSize):0;//
        if (l == position)
            break;
        if (position < l) {
            node = node->left;
        }
        else {
            position -= l + 1;
            node = node->right;
        }
    } while (true);
    return node->value;
}



pair<ImplicitTreap::Node*, ImplicitTreap::Node*> ImplicitTreap::split(Node* node, int position)
{
    if (node == nullptr)
        return pair<Node*, Node*>(nullptr, nullptr);
    int leftSize = (node->left != nullptr)?(node->left->treeSize) : 0;
    if (leftSize >= position) {
        pair<Node*, Node*> ans = split(node->left, position);
        node->left = ans.second;
        node->fix();
        return make_pair(ans.first, node);
    }
    else {
        pair<Node*, Node*> ans = split(node->right, position - leftSize - 1);
        node->right = ans.first;
        node->fix();
        return make_pair(node, ans.second);
    }
}



ImplicitTreap::Node* ImplicitTreap::merge(Node* node1, Node* node2)
{
    if (node2 == nullptr)
        return node1;
    if (node1 == nullptr)
        return node2;
    if (node1->priority > node2->priority) {
        node1->right = merge(node1->right, node2);
        node1->fix();
        return node1;
    }
    else {
        node2->left = merge(node1, node2->left);
        node2->fix();
        return node2;
    }
}



ImplicitTreap::Node::Node(const string& value)
        : value(value)
        , priority(rand())
        , left(nullptr)
        , right(nullptr)
        , treeSize(1)
{}



void ImplicitTreap::Node::fix()
{
    treeSize = 1;
    if (left != nullptr)
        treeSize += left->treeSize;
    if (right != nullptr)
        treeSize += right->treeSize;
}
