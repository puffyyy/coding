#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
typedef int datatype; 

struct BST_node{
    datatype data;
    struct BST_node* lchild, *rchild;
};
struct BSTREE{
    struct BST_node* root;
};
typedef struct BST_node bSTNode;
typedef struct BST_node* bSTNodeptr;

struct BSTREE* bsTree;

void initBST(struct BSTREE** tree){
    *tree=(struct BSTREE*)malloc(sizeof(struct BSTREE));
    (*tree)->root=NULL;
}
bSTNodeptr insertBST_(bSTNodeptr root, datatype item)// 递归算法
{
    if(root==NULL){
        root=(bSTNodeptr)malloc(sizeof(bSTNode));
        root->data=item;
        root->lchild=root->rchild=NULL;
    }
    else if(item<root->data){
        root->lchild=insertBST_(root->lchild,item);
    }
    else if(item>root->data){
        root->rchild=insertBST_(root->rchild,item);
    }
    else if(item==root->data){
        root->rchild=insertBST_(root->rchild,item);
    }
    return root;
}
bSTNodeptr insertBST(bSTNodeptr root, datatype item){
    bSTNodeptr p,q;
    p=(bSTNodeptr)malloc(sizeof(bSTNode));
    p->data=item;
    p->lchild=NULL;
    p->rchild=NULL;

    if(root==NULL)root=p;
    else{
        q=root;
        while(1){
            if(item<q->data){
                if(q->lchild==NULL){
                    q->lchild=p;
                    break;
                }
                else q=q->lchild;
            }
            else if(item>q->data){
                if(q->rchild==NULL){
                    q->rchild=p;
                    break;
                }
                else q=q->rchild;
            }
            else {
                if(q->rchild==NULL){
                    q->rchild=p;
                    break;
                }
                else q=q->rchild;
            }
        }
    }
    return root;
}
bSTNodeptr searchBST(bSTNodeptr root,datatype val){
    bSTNodeptr p=root;
    while(p!=NULL){
        if(p->data==val)return p;
        else if(p->data<val)p=p->lchild;
        else p=p->rchild;
    }
    return NULL;
}
bSTNodeptr delete_node(bSTNodeptr root,datatype val){
    bSTNodeptr cur=root,parent;
    while(cur!=NULL){
        if(cur->data==val)break;
        parent=cur;
        if(val>cur->data)cur=cur->rchild;
        else cur=cur->lchild;
    }
    if(cur==NULL){
        printf("can not find.\n");
        return root;
    }
    if(cur==root){
        //根节点
        if(cur->lchild==NULL&&cur->rchild==NULL){
            free(cur);
            return NULL;
        }   
        else if(cur->lchild==NULL||cur->rchild==NULL){
            bSTNodeptr q;
            q=cur->lchild==NULL?cur->rchild:cur->lchild;
            free(cur);
            return q;
        }
        else{
            bSTNodeptr q=cur->rchild,preq=cur;
            while(q->lchild!=NULL){
                preq=q;
                q=q->lchild;
            }
            if(preq==cur){
                q->lchild=preq->lchild;
            }
            else{
                
                preq->lchild=NULL;
                q->lchild=cur->lchild;
                q->rchild=cur->rchild;    
            }
            free(cur);
            cur=NULL;
            return q;
        }
    }
    else{
        if(cur->lchild==NULL&&cur->rchild==NULL){
            if(parent->lchild==cur){
                parent->lchild=NULL;
            }
            else parent->rchild=NULL;
            free(cur);
            cur=NULL;
            return root;
        }
        else if(cur->lchild==NULL||cur->rchild==NULL){
            bSTNodeptr childcur=cur->lchild==NULL?cur->rchild:cur->lchild;
            if(parent->lchild==cur){
                parent->lchild=childcur;
            }
            else {
                parent->rchild=childcur;
            }
            free(cur);
            cur=NULL;
            return root;
        }
        else {
            bSTNodeptr q=cur->rchild,preq=cur;
            while(q->lchild!=NULL){
                preq=q;
                q=q->lchild;
            }
            if(preq==cur){//cur的右子树无左孩子
                if(parent->lchild==cur){
                    parent->lchild=q;
                }
                else parent->rchild=q;
                q->lchild=preq->lchild;
            }
            else{
                if(parent->lchild==cur){
                    parent->lchild=q;
                }
                else parent->rchild=q;
                preq->lchild=NULL;
                q->lchild=cur->lchild;
                q->rchild=cur->rchild;
            }
            free(cur);
            cur=NULL;
            return root;
        }
    }
}
int main(){
    int a=1,b=2,c=3;
    initBST(&bsTree);
    /*test*/
    bsTree->root=insertBST(bsTree->root,5);
    insertBST(bsTree->root,8);
    insertBST(bsTree->root,4);
    insertBST(bsTree->root,7);
    insertBST(bsTree->root,10);
    bsTree->root=delete_node(bsTree->root,8);

    return 0;
}