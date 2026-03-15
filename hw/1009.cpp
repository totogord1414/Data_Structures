#include<bits/stdc++.h>
using namespace std;

struct node{
    int c;//系数
    int e;//指数
    node *next;
    node(){}
    node(int c,int e):c(c),e(e),next(NULL){}
};
//Polynomial 是一个用线性链表来表示多项式的类，定义如下：

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
    //TODO
    node *NewNode = new node(c,e);
    if(head == NULL)
    {
        head = NewNode;
        return;
    }
    else if(head->e < e)
    {
        NewNode->next = head;
        head = NewNode;
        return;
    }
    else if(head->e == e)
    {
        delete NewNode;
        head->c += c;
        if(head->c == 0)
        {
            node* temp = head->next;
            delete head;
            head = temp;
        }
        return;
    }
    node *p = head;
    while(p->next != NULL && p->next->e > e)
    {
        p = p -> next;
    }
    if(p -> next == NULL)
    {
        p -> next = NewNode;
        return;
    }
    else if(p->next->e == e)
    {
        delete NewNode;
        p->next->c += c;
        if(p->next->c == 0)
        {
            node* temp = p->next->next;
            delete p->next;
            p->next = temp;
        }
        return;
    }
    else
    {
        NewNode -> next = p -> next;
        p -> next = NewNode;
        return;
    }
}



Polynomial Polynomial::derivative(){
    //TODO
    Polynomial result;
    node *curr = head;
    while(curr != NULL)
    {
        if(curr -> e != 0)
        {
            int new_e = curr->e - 1;
            int new_c = curr->c * curr->e;
            result.insert(new_c,new_e);
        }
        curr = curr -> next;
    }
    return result;

}


//通过二级指针优化的insert 函数

void Polynomial::insert(int c, int e) {
    // 1. 定义二级指针，最初指向 head 的地址
    node **curr = &head;

    // 2. 遍历链表：只要当前箭头指向的节点存在，且它的指数大于我们要插入的 e
    // 我们就让 curr 移动到下一个箭头（即当前节点的 next 指针的地址）
    while (*curr != NULL && (*curr)->e > e) {
        curr = &((*curr)->next);
    }

    // --- 循环结束，此时的 *curr 就是我们需要操作的那个指针！ ---
    // （它可能是 head，也可能是某个节点的 next，但这已经不重要了）

    // 3. 情况 A：找到了同类项（指数相等），执行合并逻辑
    if (*curr != NULL && (*curr)->e == e) {
        (*curr)->c += c; // 系数相加
        
        // 如果系数抵消为 0，执行删除逻辑
        if ((*curr)->c == 0) {
            node *temp = *curr;        // 暂存这个废弃节点
            *curr = (*curr)->next;     // 让当前的箭头直接指向下一个节点（完美跨越！）
            delete temp;               // 释放内存
        }
        // 注意：因为我们采用了“延迟创建”的思想，到目前为止还没 new 过节点
        // 所以这里不需要写 delete NewNode，直接 return 即可。
        return;
    }

    // 4. 情况 B：没有同类项，需要插入新节点
    // 只有到这一步，我们才真正去堆内存申请空间（延迟创建）
    node *NewNode = new node(c, e);
    
    // 经典的链表插入两步走：
    NewNode->next = *curr; // 新节点的 next 指向原本当前箭头所指的节点
    *curr = NewNode;       // 让当前的箭头（head 或是前一个节点的 next）指向新节点
}