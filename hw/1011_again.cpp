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

LinkedList::LinkedList(const LinkedList& other) : length_(other.length_)
{
    head_ = new ListNode;
    head_->next_ = NIL;
    
    if (length_ == 0) return;

    Position other_ptr = other.head_->next_;
    Position current_tail = head_;
    
    for (int i = 0; i < length_; i++)
    {
        Position NewNode = new ListNode;
        NewNode->data_ = other_ptr->data_;
        NewNode->next_ = NIL;
        current_tail->next_ = NewNode;
        current_tail = NewNode;
        other_ptr = other_ptr->next_;
    }
    
    // 闭合成环
    current_tail->next_ = head_->next_;
}

LinkedList& LinkedList::operator=(const LinkedList& other)  // 赋值运算符重载
{
    if(this == &other)
    {
        return *this;
    }
    LinkedList temp(other);
    swap(temp.length_, this->length_);
    swap(temp.head_, this->head_);
    return *this;
}

int LinkedList::Josephus(const int& n, const int& m, const int& k)  // 约瑟夫问题
{
    if(n <= 0 || k > n || m <= 0 || k <= 0)
        return -1;
    
    // 1. 根据原有的 length_ 安全清除原链表
    Position clean_p = head_->next_;
    int initial_len = length_;
    for (int i = 0; i < initial_len; i++)
    {
        Position temp = clean_p;
        clean_p = clean_p->next_;
        delete temp;
    }
    head_->next_ = NIL;
    length_ = n;

    // 2. 初始化 1 到 n 个结点的循环链表
    Position p = head_;
    for(int i = 1; i <= length_; i++)
    {
        ListNode* New_Node = new ListNode;
        New_Node->data_ = i;
        New_Node->next_ = NIL;
        p->next_ = New_Node;
        p = New_Node;
    }
    
    // 首尾相连，形成循环链表
    p->next_ = head_->next_;
    
    int answer = 0;

    // 3. 执行约瑟夫游戏
    for(int i = 1; i <= k; i++)
    {
        // 利用取模优化，避免 m 极大时导致 TLE
        int moves = (m - 1) % length_;
        for(int step = 0; step < moves; step++)
        {
            p = p->next_;
        }
        
        Position target = p->next_;
        if(i == k)
        {
            answer = target->data_;
        }
        
        // 从环中摘除被淘汰的人
        p->next_ = target->next_;
        delete target;
        length_--;
    }
    
    // 4. 维护循环链表结构：保持环不断开，析构函数会根据 length_ 安全释放
    if (length_ > 0)
    {
        head_->next_ = p->next_;
    }
    else
    {
        head_->next_ = NIL;
    }

    return answer;
}