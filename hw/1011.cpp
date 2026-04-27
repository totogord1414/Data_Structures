#define NIL nullptr
#include <string>

typedef int ElemType;

typedef struct ListNode *Position; // 指针即结点位置
struct ListNode {
  ElemType data_; // 存储数据
  Position next_; // 线性表中下一个元素的位置
};

class LinkedList {
private:
  Position head_; // 单链表头指针,指向空头结点
  int length_;    // 表长
public:
  struct ListException // 异常处理
  {
    std::string error_;
    ListException(std::string s) : error_(s) {};
  };
  LinkedList();                              // 构造函数，初始化一个空的线性表
  ~LinkedList();                             // 析构函数,释放线性表占用的空间
  bool check_circle();                       // 检查是否成环
  LinkedList(const LinkedList &);            // 拷贝构造函数
  LinkedList &operator=(const LinkedList &); // 赋值运算符重载
  int Josephus(const int &n, const int &m, const int &k); // 约瑟夫问题
};

#include <algorithm>

LinkedList::LinkedList(const LinkedList &other)
    : length_(other.length_) // 拷贝构造函数
{
  head_ = new ListNode;
  // 标准循环链表：空表时头结点指向自己，而不是 NIL
  head_->next_ = head_;

  if (length_ == 0)
    return;

  Position other_ptr = other.head_->next_;
  Position current_tail = head_;

  for (int i = 0; i < length_; i++) {
    Position NewNode = new ListNode;
    NewNode->data_ = other_ptr->data_;
    current_tail->next_ = NewNode;
    current_tail = NewNode;
    other_ptr = other_ptr->next_;
  }

  // 闭合成环：尾结点必须指向头结点 head_
  current_tail->next_ = head_;
}

LinkedList &LinkedList::operator=(const LinkedList &other) // 赋值运算符重载
{
  if (this == &other) {
    return *this;
  }
  // Copy-and-swap 惯用法，非常安全，不需要修改
  LinkedList temp(other);
  std::swap(this->length_, temp.length_);
  std::swap(this->head_, temp.head_);
  return *this;
}

int LinkedList::Josephus(const int &n, const int &m, const int &k) // 约瑟夫问题
{
  if (n <= 0 || m <= 0 || k <= 0 || n < k)
    return -1;

  // 1. 安全清除原链表（如果非空）
  if (length_ > 0 && head_->next_ != head_ && head_->next_ != NIL) {
    Position clean_p = head_->next_;
    for (int i = 0; i < length_; i++) {
      Position temp = clean_p;
      clean_p = clean_p->next_;
      delete temp;
    }
  }

  length_ = n;
  head_->next_ = head_; // 重新初始化为一个空的规范循环链表

  // 2. 初始化 1 到 n 个结点的循环链表
  Position p_curr_tail = head_;
  for (int i = 1; i <= n; i++) {
    Position NewNode = new ListNode;
    NewNode->data_ = i;
    p_curr_tail->next_ = NewNode;
    p_curr_tail = NewNode;
  }

  // 首尾相连，形成循环链表（尾部指向头结点）
  p_curr_tail->next_ = head_;

  int result = 0;
  Position pre_pointer = head_; // 从头结点开始作为前驱起点

  // 3. 执行约瑟夫游戏
  for (int i = 1; i <= k; i++) {
    // 利用取模优化，避免 m 极大时导致 TLE
    int moves = (m - 1) % length_;
    for (int step = 0; step < moves; step++) {
      pre_pointer = pre_pointer->next_;
      // 如果碰到了 dummy head_，它不算作一个人，直接跳过
      if (pre_pointer == head_) {
        pre_pointer = pre_pointer->next_;
      }
    }

    Position target = pre_pointer->next_;
    // 如果要淘汰的目标刚好是头结点，跳过头结点，淘汰下一个
    if (target == head_) {
      pre_pointer = head_;
      target = pre_pointer->next_;
    }

    if (i == k) {
      result = target->data_;
    }

    // 从环中摘除被淘汰的人
    pre_pointer->next_ = target->next_;
    delete target;
    length_--;
  }

  // 4. 不需要像之前那样特殊维护链表结构，因为环始终通过 head_ 闭合
  // 残留的人依然围着 head_ 构成一个完美的循环链表

  return result;
}