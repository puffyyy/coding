#include <iostream>
using namespace std;

struct Pair // 多项式每个节点的数据
{
    int coef;
    int exp;
    Pair(int c = 0, int e = 0) : coef(c), exp(e) {}
};

template <class T>
struct Node // 多项式节点
{
    T data;
    Node<T> *next;
    
    Node(T val = T(), Node<T> *n = nullptr) : data(val), next{n} {}
};

template <class T>
class Polynomial // 多项式类
{
private:
    Node<T> *head;

public:
    Polynomial();                                         // 初始化构造
    void readData(size_t n);                              // 读入n组数据来构造多项式
    void add(const Polynomial &P1, const Polynomial &P2); // 多项式相加 P3 = P1 + P2;
    void print() const;                                   // 显示一个多项式
    void clear();                                         // 释放多项式空间
    ~Polynomial()
    {
        clear();
        delete head;
    }
};

template <class T>
Polynomial<T>::Polynomial()
{
    head = new Node<T>;
}

template <class T>
void Polynomial<T>::readData(size_t n)
{
    Node<T> *p = head;
    int coef, exp;
    while (n--)
    {
        cin >> coef >> exp;
        p->next = new Node<T>({coef, exp});
        p = p->next;
    }
}
template <class T>
void Polynomial<T>::print() const
{
    Node<T> *p = head->next;
    
    while (p)
    {
        int coef = p->data.coef, exp = p->data.exp;
        if (coef < 0)
            cout << " - ", coef = -coef;
        if (coef != 1 || exp == 0)
            cout << coef;
        if (exp > 0)
            cout << "x";
        if (exp >= 2)
            cout << "^" << exp;
        if (p->next && p->next->data.coef > 0)
            cout << " + ";
        p = p->next;
    }
    cout << endl;
}
template <class T>
void Polynomial<T>::clear()
{
    Node<T> *p = head->next, *prev;
    while (p)
    {
        prev = p;
        p = p->next;
        delete prev;
    }
}
template <class T>
void Polynomial<T>::add(const Polynomial &P1, const Polynomial &P2)
{
    Node<T> *listc = head;

    Node<T> *p = P1.head->next, *q = P2.head->next, *r;
    if (p->data.exp >= q->data.exp)
    {
        listc->next = new Node<T>({p->data.coef, p->data.exp});
        r = listc->next;
        p = p->next;
    }
    else
    {
        listc->next = new Node<T>({q->data.coef, q->data.exp});
        r = listc->next;
        q = q->next;
    }
    while (p != NULL && q != NULL)
    {
        if (p->data.exp == q->data.exp)
        {
            r->next = new Node<T>({p->data.coef + q->data.coef, p->data.exp});
            if (p->data.coef + q->data.coef == 0)
                r->next = NULL;
            else
                r = r->next;
            q = q->next;
            p = p->next;
        }
        else if (p->data.exp > q->data.exp)
        {
            r->next = new Node<T>({p->data.coef, p->data.exp});
            r = r->next;
            p = p->next;
        }
        else
        {
            r->next = new Node<T>({q->data.coef, q->data.exp});
            r = r->next;
            q = q->next;
        }
    }
    Node<T> *s = ((q == NULL) ? p : q);
    while (s != NULL)
    {
        r->next = new Node<T>({s->data.coef, s->data.exp});
        r = r->next;
        s = s->next;
    }
    r->next = NULL;
    p=head->next;
    if(p->next->data.exp==p->data.exp){
        p->next->data.coef+=p->data.coef;
        head->next=p->next;
    }

}

int main(int argc, char const *argv[])
{

    size_t n, m; // P1, P2 的项数
    cin >> n >> m;

    Polynomial<Pair> P1, P2, P3;
    P1.readData(n);
    P2.readData(m);
    // P1.print();
    // P2.print();

    P3.add(P1, P2);
    P3.print();

    return 0;
}