#include <iostream>
#include <string>

struct Node {      // Node为链式存储的栈内结点类
  int element_;    // 结点存储的元素
  Node *next_;     // 下一个结点地址（自顶向下）
  Node() = delete; // 创建结点必须指定元素值和下一个结点地址
  Node(int element, Node *next) : element_(element), next_(next) {}
};

class MyStackAndGetAns { // 栈的实现和答案输出
public:
  MyStackAndGetAns(); // 构造函数，重置栈顶和栈内元素个数
  virtual ~MyStackAndGetAns();                    // 析构函数，清空栈
  void Push(int element);                         // 将element push进栈
  int Top();                                      // 查看栈顶元素
  void Pop();                                     // 弹出栈顶元素
  bool Empty();                                   // 检查栈是否为空
  static void GetAns(int n, std::string out_seq); // 求解并输出答案
private:
  size_t size_; // 栈内元素数量
  Node *top_;   // 栈顶指针
};

void MyStackAndGetAns::Push(int element) {
    Node* NewNode = new Node(element, top_);
    size_ += 1;
    top_ = NewNode;
}
int MyStackAndGetAns::Top() {
    return top_->element_;
}
void MyStackAndGetAns::Pop() {
    Node* temp = top_;
    top_ = top_->next_;
    size_ --;
    delete temp;
}
bool MyStackAndGetAns::Empty() {
    return size_ == 0;
}
#include <sstream>
#include <vector>

void MyStackAndGetAns::GetAns(int n, std::string out_seq) {
    int target_p = 0;
    MyStackAndGetAns My_Stack;
    for(int current_num = 1;current_num <= n;current_num++)
    {
        My_Stack.Push(current_num);
        while(!My_Stack.Empty() && My_Stack.Top() == out_seq[target_p] - '0')
        {
            My_Stack.Pop();
            target_p ++;
        }
    }
    if(My_Stack.Empty())
    {
        std::cout << 'yes' << std::endl;
        return;
    }
    else
    {
        std::cout << 'no' << std::endl;
        return;
    }
}
/*
if n could be larger than 10,and the input is string,you can use stringstream to get the integers and document them in a vector


*/