#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef int dataType;
/*  Huffman Tree    */
typedef struct HuffmanNode
{
    dataType key;               // 权值
    struct HuffmanNode *left;   // 左孩子
    struct HuffmanNode *right;  // 右孩子
    struct HuffmanNode *parent; // 父节点
} HuffmanNode, *HuffmanTree;

/*    minHeap    */
static HuffmanNode *m_heap; // 最小堆的数组
static int m_capacity;      // 总的容量
static int m_size;          // 当前有效数据的数量

void minheap_filterup(int start);
void minheap_filterdown(int start, int end);
void create_minheap();
// 新建一个节点，并将最小堆中最小节点的数据复制给该节点。
HuffmanNode *dump_from_minheap();
// 将node插入到二叉堆中
int dump_to_minheap(HuffmanNode *node);
void destory_minheap();

// 中序遍历"Huffman树"
void inorder_huffman(HuffmanTree tree);
//创建Huffman树节点
HuffmanNode *huffman_create_node(dataType key, HuffmanNode *left, HuffmanNode *right, HuffmanNode *parent);
// 创建Huffman树
HuffmanNode *create_huffman(dataType arr[], int size);
// 销毁Huffman树
void destroy_huffman(HuffmanTree tree);
void encode(HuffmanTree tree, char tmp[], int deepth);
int main()
{
    HuffmanTree root;
    char ch[] = "abc";
    int fre[] = {2, 3, 1};
    char tmp[11];
    //char* code[256];
    root = create_huffman(fre, 3);
    encode(root, tmp, 0);

    return 0;
}
/*    heap    */
void minheap_filterup(int start)
{
    int i = start; //child
    int j = (start - 1) / 2;
    HuffmanNode tmp = m_heap[i];
    while (i > 0)
    {
        if (m_heap[j].key <= tmp.key)
            break;
        else
        {
            m_heap[i] = m_heap[j];
            i = j;
            j = (j - 1) / 2;
        }
    }
    m_heap[i] = tmp;
}
void minheap_filterdown(int start, int end)
{
    int i = start;
    int j = start + start + 1; //leftchild
    HuffmanNode tmp = m_heap[start];
    while (j <= end)
    {
        if (j < end && m_heap[j].key > m_heap[j + 1].key)
            j++;
        if (tmp.key <= m_heap[j].key)
            break;
        else
        {
            m_heap[i] = m_heap[j];
            i = j;
            j = i + i + 1;
        }
    }
    m_heap[i] = tmp;
}
void create_minheap(dataType a[], int size)
{
    int i;
    m_size = size;
    m_capacity = size;
    m_heap = (HuffmanNode *)malloc(sizeof(HuffmanNode) * size);
    for (i = 0; i < size; i++)
    {
        m_heap[i].key = a[i];
        m_heap[i].parent = m_heap[i].left = m_heap[i].right = NULL;
    }
    for (i = size / 2 - 1; i >= 0; i--)
        minheap_filterdown(i, size - 1);
}
void destory_minheap()
{
    m_size = 0;
    m_capacity = 0;
    free(m_heap);
    m_heap = NULL;
}
HuffmanNode *dump_from_minheap()
{
    if (m_size == 0)
        return NULL;
    HuffmanNode *node = (HuffmanNode *)malloc(sizeof(HuffmanNode));
    *node = m_heap[0];

    HuffmanNode tmp = m_heap[0];
    m_heap[0] = m_heap[m_size - 1];
    m_heap[m_size - 1] = tmp;
    m_size--;
    minheap_filterdown(0, m_size - 1);
    return node;
}

int dump_to_minheap(HuffmanNode *node)
{
    if (m_size == m_capacity)
        return -1;
    m_heap[m_size++] = *node;
    minheap_filterup(m_size - 1);
    return 0;
}
/*    huffman    */

void inorder_huffman(HuffmanTree tree)
{
    if (tree != NULL)
    {
        inorder_huffman(tree->left);
        printf("%d ", tree->key);
        inorder_huffman(tree->right);
    }
}

HuffmanNode *huffman_create_node(dataType key, HuffmanNode *left, HuffmanNode *right, HuffmanNode *parent)
{
    HuffmanNode *p;

    if ((p = (HuffmanNode *)malloc(sizeof(HuffmanNode))) == NULL)
        return NULL;
    p->key = key;
    p->left = left;
    p->right = right;
    p->parent = parent;

    return p;
}

HuffmanNode *create_huffman(dataType arr[], int size) // size 数组大小
{
    int i;
    HuffmanNode *left, *right, *parent;

    create_minheap(arr, size);
    for (i = 0; i < size - 1; i++)
    {
        left = dump_from_minheap();
        right = dump_from_minheap();
        parent = huffman_create_node(left->key + right->key, left, right, NULL);
        left->parent = parent;
        right->parent = parent;

        // 将parent节点数据拷贝到"最小堆"中
        if (dump_to_minheap(parent) != 0)
        {
            printf("插入失败!\n结束程序\n");
            destroy_huffman(parent);
            parent = NULL;
            break;
        }
    }
    destory_minheap();
    return parent;
}

void destroy_huffman(HuffmanTree tree)
{
    if (tree == NULL)
        return;
    if (tree->left != NULL)
        destroy_huffman(tree->left);
    if (tree->right != NULL)
        destroy_huffman(tree->right);
    free(tree);
}

void encode(HuffmanTree tree, char tmp[], int deepth)
{

    int i = 0;

    if (tree->left == NULL && tree->right == NULL)
    {
        tmp[deepth] = '\0';
        printf("%d->%s\n", tree->key, tmp);
    }
    if (tree->left != NULL)
    {
        tmp[deepth] = '0';
        encode(tree->left, tmp, deepth + 1);
    }
    if (tree->right != NULL)
    {
        tmp[deepth] = '1';
        encode(tree->right, tmp, deepth + 1);
    }
}