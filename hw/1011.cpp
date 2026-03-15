#define NIL nullptr
#include <string>

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

#include <algorithm>

LinkedList::LinkedList(const LinkedList& other)// 拷贝构造函数
{
 //创建新列表的空头节点
    head_ = new ListNode;
    head_->next_ = NIL;
    length_ = 0;

    Position other_pointer = other.head_->next_;
    Position curr_tail = head_;
    while(other_pointer != NIL)
    {
        Position newNode = new ListNode;
        newNode->data_ = other_pointer->data_;
        newNode->next_ = NIL;

        curr_tail->next_ = newNode;
        curr_tail = curr_tail->next_;
        other_pointer = other_pointer->next_;
    }
    length_ = other.length_;

    
}
LinkedList& LinkedList::operator=(const LinkedList& other)  // 赋值运算符重载
{
    if(this == &other)
    {
        return *this;
    }
    LinkedList temp(other); 
    std::swap(this->length_,temp.length_);
    std::swap(this->head_,temp.head_);
    return *this;
}


int LinkedList::Josephus(const int& n, const int& m, const int& k)  // 解决，约瑟夫问题，给出答案
{
    if(n <= 0 || m <= 0 || k <= 0 || n < k)
        return -1;

    Position p = head_->next_;
    while(p != NIL)
    {
        Position temp = p;
        p = p -> next_;
        delete temp;
    }

    head_->next_ = NIL;
    length_ = 0;

    Position p_curr_tail = head_;
    for(int i = 1;i <= n;i++)
    {
        Position NewNode = new ListNode;
        NewNode->data_ = i;
        NewNode->next_ = NIL;
        
        p_curr_tail->next_ = NewNode;
        p_curr_tail = p_curr_tail->next_;
    }
    length_ = n;
    p_curr_tail->next_ = head_ -> next_;


    int result = 0;
    Position pre_pointer = p_curr_tail;
    for(int i = 1;i <= k;i++)
    {
        for(int j = 0;j < m - 1;j++)
        {
            pre_pointer = pre_pointer->next_;
        }
        if(i == k)
            result = pre_pointer->next_->data_;
        Position temp = pre_pointer->next_;
        pre_pointer->next_ = temp->next_;
        delete temp;
        length_--;
    }
    if(length_ == 0)
    {
        head_->next_ = NIL;
    }
    else
    {
        head_->next_ = pre_pointer->next_;
        pre_pointer->next_ = NIL;
    }

    return result;
}