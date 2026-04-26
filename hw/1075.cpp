#include <iostream>
#include <string>
using namespace std;
#define NIL nullptr
typedef struct node *Position; // 指针即结点位置

struct node {
    int val;
    node* next;
    node() {}
   node(int v) :val(v), next(NULL) {}
};

class LinkedList {
private:
    node* head;//头指针,指向不存数据的表头结点
public:
    LinkedList();// 默认构造函数
    LinkedList(const LinkedList& other);// 拷贝构造函数
    LinkedList& operator=(const LinkedList& other); // 赋值运算符重载
    ~LinkedList();// 析构函数

    void insert(int v);// 插入函数
    void print();// 打印链表
    void clear();// 清除链表
    void sortLinkedList();// 将单链表排序

};
node* merge_lists(node* left, node* right)//merge two lists together
{
    node dummy;
    node* tail = &dummy;
    while(left != NULL && right != NULL)
    {
        if(left->val < right->val)
        {
            tail->next = left;
            left = left->next;
        }
        else
        {
            tail->next = right;
            right = right->next;
        }
        tail = tail->next;
    }
    if(left != NULL)
    {
        tail->next = left;
    }
    else
    {
        tail->next = right;
    }
    return dummy.next;
}
node* sort_lists(node* startNode)//break lists apart and sort both of them
{
    if(startNode == NULL || startNode->next == NULL)
    {
        return startNode;
    }
    node* slow = startNode;
    node* fast = startNode->next;
    while(fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    node* mid = slow->next;
    slow->next = NULL;
    node* left = sort_lists(startNode);
    node* right = sort_lists(mid);
    return merge_lists(left, right);
}

void LinkedList::sortLinkedList(){
    if(head == NULL || head->next == NULL || head->next->next == NULL)
    {
        return;
    }
    head->next = sort_lists(head->next);
}