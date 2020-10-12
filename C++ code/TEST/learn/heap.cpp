#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
// #include <queue>
#include <deque>

using namespace std;
struct node
{
    int a, b;
};
typedef struct node Node;
typedef struct node *NodePtr;
template <typename Container>
void print(Container container)
{
    for (auto i : container)
    {
        cout << i << ' ';
    }
    cout << endl;
}

int main()
{
    vector<int> vec = {1, 8, 4, 3, 3, 5, 4, 5, 6, 7, 9};
    make_heap(vec.begin(), vec.end());
    // make_heap(vec.begin(), vec.end(), less<int>());
    print(vec);
    deque<int> deq;

    vec.push_back(100);
    push_heap(vec.begin(), vec.end());
    print(vec);
    sort_heap(vec.begin(), vec.end());
    print(vec);
    return 0;
}
