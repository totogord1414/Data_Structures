#include <bits/stdc++.h>

struct node{
    int c;//系数
    int e;//指数
    node *next;
    node(){}
    node(int c,int e):c(c),e(e),next(NULL){}
};

class Polynomial{
    private:
        node* head;
    public:
        Polynomial();// 默认构造函数
        Polynomial(const Polynomial& other);// 拷贝构造函数
        Polynomial& operator=(const Polynomial& other);// 赋值运算符重载
        ~Polynomial();// 析构函数
        void insert(int c, int e);// 参数 c 表示系数，e 表示指数。
        Polynomial derivative();// 根据每项的指数进行求导，新的系数是原系数乘以指数，指数减 1
        void print();//打印函数：按顺序打印多项式的每一项
        void clear();// 清除函数：释放链表中所有节点的内存并将头指针置为 NULL
};

void Polynomial::insert(int c,int e){
    if(c == 0) return;
    node** node_pointer = &head;//node pointer points to the next pointer of the previous node
    while(*node_pointer != NULL && (*node_pointer) -> e > e)
    {
        node_pointer = &((*node_pointer) -> next);
    }
    if(*node_pointer != NULL && (*node_pointer) -> e == e)
    {
       (*node_pointer)->c += c;
        if((*node_pointer)->c == 0)
        {
            node* temp = *node_pointer;
            *node_pointer = (*node_pointer) -> next;
            delete temp;
        }
        return;
    }
    node* NEW_NODE = new node(c,e);
        NEW_NODE -> next = *node_pointer;
        *node_pointer = NEW_NODE;
        return;
    
}

Polynomial Polynomial::derivative(){
    //TODO
}