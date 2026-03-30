struct Node {
    int value; // 节点值
    Node* next; // 指向下一个节点的指针
    Node(int v, Node* n = nullptr); // 构造函数
};

class CustomStack {
private:
    Node* stackTop; // 主堆栈的栈顶指针
    Node* maxStackTop; // 最大值堆栈的栈顶指针

public:   
    CustomStack(); // 构造函数
    ~CustomStack(); // 析构函数，释放所有节点
    void push(int x); // 入栈操作
    void pop(); // 出栈操作
    int getMax(); // 获取当前最大值
};

void CustomStack::push(int x) {
    Node* NewNode = new Node(x, stackTop) ;
    stackTop = NewNode;
    if(maxStackTop == nullptr ||x >= maxStackTop->value)
    {
        Node* NewMaxNode = new Node(x, maxStackTop);
        maxStackTop = NewMaxNode;
    }

}

void CustomStack::pop() {
    if(maxStackTop == nullptr)
        return;
    Node* temp = stackTop;
    stackTop = stackTop->next;
    if(temp->value == maxStackTop->value)
    {
        Node* temp_max = maxStackTop;
        maxStackTop = maxStackTop->next;
        delete temp_max;
    }
    delete temp;
}

int CustomStack::getMax() {
    if(maxStackTop == nullptr)
    {
        return;
    }
    return maxStackTop->value;
}