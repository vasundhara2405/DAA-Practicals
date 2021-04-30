
#include<iostream>
#include<stdlib.h>
#include<stack>

using namespace std;

class BSTNode
{
    public:
    BSTNode()
    {
        left = right = parent = 0;
        el=-1;
    }
    BSTNode(const int& e, BSTNode *p = 0, BSTNode *l = 0, BSTNode *r = 0)
    {
        el = e; left = l; right = r; parent = p;
        color = false;
    }
    int el;
    bool color;
    BSTNode *left, *right, *parent;
};

class BST
{
    public:
    BST()
    {
        root = 0;
    }

    ~BST()
    {
        clear();
    }

    void clear()
    {
        clear(root);
        root = 0;
    }

    bool isEmpty()
    {
        return root == 0;
    }

    int search(int& el)
    {
        return search(root,el);
    }

    void iterativePreorder();
    void iterativeInorder();
    void insert(int&);
    void insertfixup(BSTNode*);
    void deletefixup(BSTNode*);
    void leftrotate(BSTNode*);
    void rightrotate(BSTNode*);
    void findAndDeleteByCopying(int&);
    void deleteByCopying(BSTNode*&);

    protected:
    BSTNode* root;
    void clear(BSTNode*);
    int search(BSTNode*,int&);

    void visit(BSTNode* p)
    {
        if(p->el==-1)
            return;

        cout <<"\nElement: "<< p->el <<"\t Color: ";

        if(p->color)
            cout<<"Black";
        else
            cout<<"Red";
    }
};

int BST::search(BSTNode* p,int& el)
{
    while (p != 0)
    {
        if (el == p->el)
        {
            cout<<"\n"<<p->el<<"color :";

            if(p->color)
                cout<<"black";
            else
                cout<<"red";

            return 0;
        }
        else if (el < p->el)
            p = p->left;
        else
            p = p->right;
    }
    return -1;
}

void BST::iterativePreorder()
{
    stack<BSTNode*> travStack;
    BSTNode *p = root;
    if (p != 0)
    {
        travStack.push(p);
        while (!travStack.empty())
        {
            p = travStack.top();
            travStack.pop();
            visit(p);

            if (p->right != 0)
                travStack.push(p->right);

            if (p->left != 0)
                travStack.push(p->left);
        }
    }
}

void BST::insert(int& el)
{
    BSTNode *p = root, *prev = 0;
    while (p != 0)
    {
        prev = p;
        if (el < p->el)
            p = p->left;
        else
            p = p->right;
    }

    if (root == 0)
        p = root = new BSTNode(el);
    else if (el < prev->el)
        p = prev->left = new BSTNode(el,prev);
    else
        p = prev->right = new BSTNode(el,prev);

    insertfixup(p);
}

void BST::leftrotate(BSTNode* x)
{
    BSTNode* y=x->right;
    x->right=y->left;

    if(y->left!=0)
        (y->left)->parent=x;

    y->parent=x->parent;

    if(x->parent==0)
        root=y;
    else if(x==(x->parent)->left)
        (x->parent)->left=y;
    else
        (x->parent)->right=y;

    y->left=x;
    x->parent=y;
}

void BST::rightrotate(BSTNode* x)
{
    BSTNode* y=x->left;
    x->left=y->right;

    if(y->right!=0)
        (y->right)->parent=x;

    y->parent=x->parent;

    if(x->parent==0)
        root=y;
    else if(x==(x->parent)->right)
        (x->parent)->right=y;
    else
        (x->parent)->left=y;

    y->right=x;
    x->parent=y;
}
void BST::deletefixup(BSTNode* x)
{
    BSTNode* w;
    BSTNode* nil=new BSTNode();
    nil->color=true;

    while(x!=root && x->color)
    {
        if(x==(x->parent)->left)
        {
            w=((x->parent)->right)?((x->parent)->right):nil;
            if(!(w->color))
            {
                w->color=true;
                (x->parent)->color=false;
                leftrotate(x->parent);
                w=((x->parent)->right)?((x->parent)->right):nil;
            }

            if((w->left)?(w->left)->color:true && (w->right)?(w->right)->color:true)
            {
                w->color=false;
                x=x->parent;
            }
            else
            {
                if((w->right)?(w->right)->color:true)
                {
                    if(w->left)
                        (w->left)->color=true;

                    w->color=false;
                    rightrotate(w);
                    w=((x->parent)->right)?((x->parent)->right):nil;
                }
                w->color=(x->parent)->color;
                (x->parent)->color=true;
                if(w->right)
                    (w->right)->color=true;

                leftrotate(x->parent);
                x=root;
            }
        }
        else
        {
            w=((x->parent)->left)?((x->parent)->left):nil;
            if(!(w->color))
            {
                w->color=true;
                (x->parent)->color=false;
                rightrotate(x->parent);
                w=((x->parent)->left)?((x->parent)->left):nil;
            }

            if((w->left)?(w->left)->color:true && (w->right)?(w->right)->color:true)
            {
                w->color=false;
                x=x->parent;
            }
            else
            {
                if((w->left)?(w->left)->color:true)
                {
                    if(w->right)
                        (w->right)->color=true;

                    w->color=false;
                    leftrotate(w);
                    w=((x->parent)->left)?((x->parent)->left):nil;
                }
                w->color=(x->parent)->color;
                (x->parent)->color=true;
                if(w->left)
                    (w->left)->color=true;

                rightrotate(x->parent);
                x=root;
            }
        }
    }
    x->color=true;
}

void BST::insertfixup(BSTNode* z)
{    bool color;
    BSTNode* y;
    BSTNode* inil=new BSTNode();
    inil->color=true;
    while((z->parent)!=0 && ((z->parent)->parent)!=0 && !((z->parent)->color))
    {
        if(z->parent==((z->parent)->parent)->left)
        {
            y=(((z->parent)->parent)->right)?(((z->parent)->parent)->right):inil;
            if(!(y->color))
            {
                (z->parent)->color=true;
                y->color=true;
                ((z->parent)->parent)->color=false;
                z=(z->parent)->parent;
            }
            else
            {
                if(z==(z->parent)->right)
                {
                    z=z->parent;
                    leftrotate(z);
                }
                (z->parent)->color=true;
                ((z->parent)->parent)->color=false;
                rightrotate((z->parent)->parent);
            }
        }
        else
        {
            y=(((z->parent)->parent)->left)?(((z->parent)->parent)->left):inil;
            if(!(y->color))
            {
                (z->parent)->color=true;
                y->color=true;
                ((z->parent)->parent)->color=false;
                z=(z->parent)->parent;
            }
            else
            {
                if(z==(z->parent)->left)
                {
                    z=z->parent;
                    rightrotate(z);
                }
                cout<<color;
                (z->parent)->color=true;
                ((z->parent)->parent)->color=false;
                leftrotate((z->parent)->parent);
            }
        }
    }
    root->color=true;
}

void BST::findAndDeleteByCopying(int& el)
{
    BSTNode *node = root, *prev = 0;
    while (node != 0)
    {
        if (node->el == el)
            break;

        prev = node;

        if (el < node->el)
            node = node->left;
        else
            node = node->right;
    }

    if (node != 0 && node->el == el)
    {
        if (node == root)
            deleteByCopying(root);
        else if (prev->left == node)
            deleteByCopying(prev->left);
        else
            deleteByCopying(prev->right);
    }
    else if (root != 0)
        cout << "Element is not in the tree\n";
    else
        cout << "The tree is empty\n";
}
void BST::deleteByCopying(BSTNode*& node)
{
    bool check,check2;
    BSTNode *previous, *tmp = node,*par=node->parent;
    BSTNode *cnil=new BSTNode();
    cnil->color=true;
    cnil->parent=par;

    if (node->right == 0)
    {
        node = node->left;
        check=false;
    }
    else if (node->left == 0)
    {
        node = node->right;
        check=false;
    }
    else
    {
        tmp = node->left;
        previous = node;
        while (tmp->right != 0)
        {
            previous = tmp;
            tmp = tmp->right;
        }

        node->el = tmp->el;
        node->color = tmp->color;

        if(tmp->left)
            (tmp->left)->parent=previous;
        else
            cnil->parent=previous;

        if (previous == node)
        {
            previous ->left = tmp->left;
            check=true;
            check2=false;
        }
        else
        {
            previous ->right = tmp->left;
            check=true;
            check2=true;
        }
    }

    if(tmp->color)
    {
        if(!check)
        {
            if(!node)
                node=cnil;

            node->parent=par;
            deletefixup(node);

            if(par && par->left==cnil)
                par->left=0;
            else if(par && par->right==cnil)
                par->right=0;
        }
        else if(check2)
        {
            if(!previous->right)
                previous->right=cnil;

            deletefixup(previous->right);

            if(previous->right==cnil)
                previous->right=0;
        }
        else
        {
            if(!previous->left)
                previous->left=cnil;

            deletefixup(previous->left);

            if(previous->left==cnil)
                previous->left=0;
        }
    }
    delete cnil;
    delete tmp;
}

void BST::clear(BSTNode * p)
{
    if(p!=0)
    {
        clear(p->left);
        clear(p->right);
        delete p;
    }
}

void BST::iterativeInorder()
{
    stack<BSTNode*> travStack;
    BSTNode *p = root;
    while (p != 0)
    {
        while (p != 0)
        {
            if (p->right)
            travStack.push(p->right);
            travStack.push(p);
            p = p->left;
        }

        p = travStack.top();
        travStack.pop();

        while (!travStack.empty() && p->right == 0)
        {
            visit(p);
            p = travStack.top();
            travStack.pop();
        }

        visit(p);

        if (!travStack.empty())
        {
            p = travStack.top();
            travStack.pop();
        }
        else
            p = 0;
    }
}

int main()
{
    BST t1;
    int dtchoice;
    do
    {
        int x;
        system("cls");
        cout<<"Enter your choice.\n1.Insertion.\n2.Deletion.\n3.Search a number.\n4.Display its preorder and inorder transversals.\n5.Exit.\n";
        cin>>dtchoice;

        switch(dtchoice)
        {
            case 1: system("cls");
                        cout<<"\nEnter the number to be inserted in tree.\n";
                        cin>>x;
                        t1.insert(x);
                        break;

            case 2: system("cls");
                        cout<<"\nEnter number to be deleted.\n";
                        cin>>x;
                        t1.findAndDeleteByCopying(x);
                        system("pause");
                        break;

            case 3: system("cls");
                        if(t1.isEmpty())
                        cout<<"\nTree is empty.\n";
                        else{
                            cout<<"\nEnter number to be searched.\n";

                        cin>>x;
                        int a=t1.search(x);
                        if(a==-1)
                            cout<<"\nNumber is not present.";}

                        system("pause");
                        break;

            case 4: system("cls");
                        if(t1.isEmpty())
                            cout<<"\nTree is empty.\n";
                        else{
                            cout<<"\nPreorder:\n";

                        t1.iterativePreorder();
                        cout<<"\nInorder:\n";
                        t1.iterativeInorder();}
                        system("pause");
                        break;

            case 5: system("cls");
                        exit(0);
                        break;

            default:system("cls");
                cout<<"Enter correct choice.";
            }
    }while(true);
    return 0;
}
