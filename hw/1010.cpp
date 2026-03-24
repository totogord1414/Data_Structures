#include <bits/stdc++.h>

struct node {
    int val;
    node* next;
    node() {}
    node(int v) :val(v), next(NULL) {}
};


class LinkedList {
private:
    node* head;//头指针，指向不存数据的表头结点
public:
    LinkedList();// 默认构造函数
    LinkedList(const LinkedList& other);// 拷贝构造函数
    LinkedList& operator=(const LinkedList& other); // 赋值运算符重载
    ~LinkedList();// 析构函数

    void insert(int v);// 插入函数
    void print();// 打印链表
    void clear();// 清除链表
    void K_Reverse(int k);// K 反转函数

};



//尾插法
void LinkedList::K_Reverse (int k)
{
      //TODO
      if(k < 1)
        return;
      node* slow = head;
      node* fast = head;
      int count = 0;
      while (fast->next != NULL)
      {
        for(count = 0;count < k && fast->next != NULL;count++)
        {
            fast = fast->next;
        }
        if(count == k)
        {
            node* fur = slow->next->next;
            node* ne_p = slow->next;
            for(count = 0;count < k - 1;count++)
            {
                fur = slow->next->next;
                slow -> next -> next = fast ->next;
                fast -> next = slow -> next;
                slow -> next = fur;
            }
            slow = ne_p;
            fast = slow;
        }
        else
        {
            return;
        }
      }
    return;
}

//头插法
void LinkedList::K_Reverse (int k)
{
    if(k < 1)
        return;
    node* first = head;
    node* pre = head -> next;
    node* curr = pre -> next;
    while(curr != NULL)
    {
        for(int i = 0; i < k && curr != NULL;i++)
        {
            
        }
    }
}
