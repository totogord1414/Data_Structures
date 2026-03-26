#include <iostream>


struct node // 表示单链表的一个节点
{
    int val;    // 表示当前节点的值
    node *next; // 表示指向下一节点的指针
    node() {}
    node(int v) : val(v), next(NULL) {} // 构造一个值为 v 的节点的构造函数
};

class Stack // 表示一个栈
{
private:
    int capacity; // 表示栈最多能存储的元素个数
    int size;     // 表示当前栈中存储的元素个数
    int *data;    // 存储栈中元素的数组，默认元素类型为整型
public:
    Stack(unsigned = MAX_SIZE);                               // 构造函数，初始化一个空栈
    ~Stack();                                                 // 析构函数
    friend std::istream &operator>>(std::istream &, Stack &); // 读入一个大整数，存储在栈中
    bool empty();                                             // 返回栈是否为空

    void push(int x); // 向栈顶压入一个元素
    int top();        // 返回栈顶元素
    void pop();       // 弹出栈顶的元素，注意这个函数没有返回值
};

void Stack::push(int x)
{
    // TODO
    if(size <  capacity)
    {
        data[size] = x;
        size += 1;
    }
    else
        std::cout << "error:stack full";
}


int Stack::top()
{
    // TODO
    if(size <= capacity && size > 0)
    {
        return data[size - 1];
    }
    else
    {
        std::cout << "error:no such element";
        return -1;
    }
}


void Stack::pop()
{
    // TODO
    if(size > 0)
    {
        size--;
        return;
    }
    else
    {
        std::cout << "error:stack empty";
    }
}
void insert_node(node* NewNode, node*& head)
{
    NewNode->next = head;
    head = NewNode;    
}
/**
 * 【大整数相加操作】
 * @param  s1,s2 [以栈的形式表示的非负大整数]
 * @return       [两个大整数的和的链表表头指针]
 */
node *add(Stack &s1, Stack &s2)
{
    // TODO
    int bonus = 0;
    node* head = NULL;
    while(!s1.empty() || !s2.empty() || bonus != 0)
    {
        int sum = bonus;
        if(!s1.empty())
        {
            sum += s1.top();
            s1.pop();
        }
        if(!s2.empty())
        {
            sum += s2.top();
            s2.pop();
        }
        bonus = sum / 10;
        sum = sum % 10;
        node* NewNode = new node(sum);
        insert_node(NewNode, head);
    }
    return head;
}