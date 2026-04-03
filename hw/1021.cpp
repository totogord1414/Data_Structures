class CircularQueue {
private:
    int *data;      // 存储队列元素的数组
    int front;      // 队列头部索引
    int rear;       // 队列尾部索引
    int size;       // 当前队列中的元素数量
    int capacity;   // 队列的最大容量（包括一个额外的空间用于区分队列满和空）

public:
    CircularQueue(int capacity);                // 构造函数，初始化队列
    CircularQueue(const CircularQueue& other);  // 拷贝构造函数
    CircularQueue& operator=(const CircularQueue& other); // 赋值运算符重载
    ~CircularQueue();                           // 析构函数，释放动态分配的内存
    bool isFull();                              // 判断队列是否已满
    bool isEmpty();                             // 判断队列是否为空
    int enqueue(int x);                         // 入队操作，返回0表示成功，返回-1表示队列已满
    int dequeue();                              // 出队操作，返回出队元素，返回-1表示队列为空
};

int CircularQueue:: enqueue(int x){
    if(front == (rear + 1) % capacity)
    {
        return -1;
    }
    else
    {
        data[rear] = x;
        rear = (rear + 1) % capacity;
        size += 1;
        return 0;
    }
}
int CircularQueue:: dequeue(){
    if(front == rear)
    {
        return -1;
    }
    else
    {
        int temp = data[front];
        front = (front + 1) % capacity;
        size -= 1;
        return temp;
    }
}