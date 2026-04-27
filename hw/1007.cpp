#include <iostream>
#include <string>

#define NIL nullptr
typedef int ElemType;
typedef struct ListNode *Position; // 指针即结点位置
struct ListNode {
  ElemType data_; // 存储数据
  Position next_; // 线性表中下一个元素的位置
};

class LinkedList {
private:
  Position head_; // 单链表头指针,指向
  int length_;    // 表长
public:
  struct ListException // 异常处理
  {
    std::string error_;
    ListException(std::string s) : error_(s) {};
  };
  LinkedList(); // 构造函数，初始化空线性表
  LinkedList(const LinkedList &);
  LinkedList &operator=(const LinkedList &);
  ~LinkedList(); // 析构函数

  Position
  Search(ElemType x); // 在线性表中查找元素x，查找成功，返回x的位置，否则返回NIL
  void Insert(ElemType tar,
              ElemType x); // 在线性表的元素值为tar的结点后插入元素x
  void Remove(ElemType x); // 从线性表中删除第一个值为x的元素

  friend std::ostream &operator<<(std::ostream &,
                                  const LinkedList &); // 输出一个链表
  friend std::istream &operator>>(std::istream &, LinkedList &); // 输入一个链表
};

/**
 * 【线性链表查找】
 * @param  x [搜索元素值]
 * @return   [x所在的结点指针]
 */
Position LinkedList::Search(ElemType x) {
  // TODO
  Position p = head_->next_;
  while (p != NIL && p->data_ != x) {
    p = p->next_;
  }
  return p;
}

/**
 * 【线性链表插入】
 * @param  tar [目标结点值]
 * @param  x [需要插入的结点值]
 * @return   [无返回值]
 */
void LinkedList::Insert(ElemType tar, ElemType x) {
  // TODO
  if (head_->next_ == NIL) {
    Position Newnode = new ListNode;
    Newnode->data_ = x;
    Newnode->next_ = NIL;
    head_->next_ = Newnode;
    length_ += 1;
    return;
  }

  Position p = Search(tar);
  if (p != NIL) {
    Position Newnode = new ListNode;
    Newnode->data_ = x;
    Newnode->next_ = p->next_;
    p->next_ = Newnode;
    length_ += 1;
  }
}

/**
 * 【线性链表删除】
 * @param  x [需要删除的结点值]
 * @return   [无返回值]
 */
void LinkedList::Remove(ElemType x) {
  // TODO
  if (head_->next_ == NIL) {
    return;
  }
  
  Position p = head_;
  while (p->next_ != NIL) {
    if (p->next_->data_ == x) {
      Position temp = p->next_;
      p->next_ = temp->next_;
      delete temp;
      length_--;
      return;
    }
    p = p->next_;
  }
}
