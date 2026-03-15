#include <string>
//LinkedList是一个带表头结点的线性链表，定义如下

using ElemType = int;
using Position = struct ListNode*; // 指针即结点位置

struct ListNode
{
    ElemType data_; // 存储数据
    Position next_; // 线性表中下一个元素的位置
};

class LinkedList
{
private:
    Position head_; // 单链表头指针,指向空头结点
    int length_;    // 表长
public:
    struct ListException // 异常处理
    {
        std::string error_;
        ListException(std::string s) : error_(s) {};
    };
    LinkedList(); // 构造函数，初始化一个空的线性表
    LinkedList(const LinkedList &);
    LinkedList &operator=(const LinkedList &);
    ~LinkedList(); // 析构函数,释放线性表占用的空间
    void Insert(ElemType x); // 尾插法
    ElemType findKthToTail(int k); // 查询链表倒数第k个结点值，位置从1开始
};
//head_ 指向链表的表头结点，如果链表为空，head_->next_为NULL


ElemType LinkedList::findKthToTail(int k)
{
   // TODO
   if(length_ < k || k <= 0)
   {
        return -1;
   }
   int count = length_ - k;
   Position p = head_;
   for(int i = 0 ;i < count; i++)
   {
        p = p->next_;
   }
   return p->next_->data_;
}