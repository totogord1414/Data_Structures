#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

#define NIL nullptr

typedef int ElemType;

typedef struct ListNode *Position;  // 指针即结点位置
struct ListNode {
    ElemType data_;   // 存储数据
    Position next_;  // 线性表中下一个元素的位置
};

class LinkedList {
private:
    Position head_;  // 单链表头指针,指向空头结点
    int length_;    // 表长
public:
    struct ListException   // 异常处理
    {
        std::string error_;
        ListException(std::string s) :error_(s) {};
    };
        LinkedList();  // 构造函数，初始化一个空的线性表
    ~LinkedList();  // 析构函数,释放线性表占用的空间
    bool check_circle(); // 检查是否成环
    LinkedList(const LinkedList&); // 拷贝构造函数
    LinkedList& operator=(const LinkedList&);  // 赋值运算符重载
    int Josephus(const int& n, const int& m, const int& k);  // 约瑟夫问题
};

LinkedList::LinkedList(const LinkedList& other):length_(other.length_)
{
    ListNode* NewNode = new ListNode;
    this->head_ = NewNode;

    Position other_pointer = other.head_->next_;
    Position curr_tail = head_;
    while(other_pointer != NIL)
    {
       ListNode* NewNode = new ListNode;
       NewNode->data_ = other_pointer->data_; 
       curr_tail->next_ = NewNode;
       curr_tail = NewNode;
       other_pointer = other_pointer->next_;
    }
    curr_tail ->next_ = NIL;
}
LinkedList& LinkedList::operator=(const LinkedList& other)
{
    if(this == &other)
    {
        return *this;
    }
    LinkedList temp(other);
    swap(temp.length_, this->length_);
    swap(temp.head_, this->head_);
    return *this;
}  // 赋值运算符重载
int LinkedList::Josephus(const int& n, const int& m, const int& k)
{
    if(n <= 0 || k > n || m <= 0 || k <= 0)
        return -1;
    Position p = head_ -> next_;
    while(p != NIL)
    {
        Position temp = p;
        p = p->next_;
        delete temp;
    }
    head_->next_ = NIL;
    length_ = n;
    p = head_;
    for(int i = 1; i <= length_ ;i++)
    {
        ListNode* New_Node = new ListNode;
        p->next_ = New_Node;
        New_Node->data_ = i;
        New_Node->next_ = NIL;
        p = New_Node;
    }
    
    p->next_ = head_->next_;
    int answer = 0;
    for(int i = 1;i <= k;i++)
    {
        int p_curr = 1;
        while(p_curr < m)
        {
            p = p->next_;
            p_curr++;
        }
        if(i == k)
        {
            answer =  p->next_->data_;
            break;
        }
        Position temp = p->next_;
        p->next_ = temp->next_;
        length_--;
        delete temp;
    }
    if (length_ == 0)
    {
        head_->next_ = NIL;
    }
    else
    {
        head_->next_ = p;
        p = head_;
        for (int i = 0; i < length_; i++)
        {
            p = p->next_;
        }
        p->next_ = NIL;
    }
    return answer;
}  // 解决，约瑟夫问题，给出答案