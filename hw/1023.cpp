struct Node
{
        int citizen; // 存储数据
        Node *next; // 线性表中下一个元素的位置
        Node(int c) : citizen(c), next(nullptr) {}
};
//Queue是一个不包含表头结点的线性链表，定义如下：

class Queue
{
private:
    struct Node
    {
        int citizen;
        Node *next;
        Node(int c) : citizen(c), next(nullptr) {}
    };

    Node *front; // 队列的头指针
    Node *rear;  // 队列的尾指针

public:
    Queue();                   // 无参构造函数
    Queue(const Queue &q);      // 拷贝构造函数
    Queue &operator=(const Queue &q); // 赋值运算符重载
    ~Queue();                  // 析构函数

    bool isEmpty() const;
    void enqueueFront(int citizen);
    void enqueueRear(int citizen);
    int dequeue();
    void remove(int citizen);
};

bool Queue::isEmpty() const
{
    if(front == nullptr)
    {
        return true;
    }
    return false;
}
//说明：检查队列是否为空，若为空，则返回 true，否则返回 false。

void Queue::enqueueFront(int citizen)
{

    Node* newNode = new Node(citizen);
    if(isEmpty())
    {
        front = newNode;
        rear = newNode;
        return;
    }
    newNode->next = front;
    front = newNode;
}
//说明：从队列前端插入元素 citizen。

void Queue::enqueueRear(int citizen)
{
    Node* newNode = new Node(citizen);
    if(isEmpty())
    {
        front = newNode;
        rear = newNode;
        return;
    }
    rear->next = newNode;
    rear = newNode;
}
//说明：从队列后端插入元素 citizen。

int Queue::dequeue()
{
    if(isEmpty())
    {
        return -1;
    }
    int temp = front->citizen;
    Node* temp_pointer = front;
    front = front -> next;
    if(front == nullptr)
    {
        rear = nullptr;
    }
    delete temp_pointer;
    return temp;
}
//说明：从队列前端移除并返回元素。如果队列为空，返回 -1 表示错误。

void Queue::remove(int citizen)
{
    if(isEmpty())
    {
        return;
    }
    if(front->citizen == citizen)
    {
        dequeue();
        return;
    }
    Node* pointer = front;
    while(pointer->next != nullptr && pointer->next->citizen != citizen)
    {
        pointer = pointer->next;
    }
    Node* temp = pointer->next;
    if(temp->next == nullptr)
    {
        rear = pointer;
    }
    pointer->next = temp->next;
    delete temp;

}
//说明：从队列中移除指定的元素 citizen。