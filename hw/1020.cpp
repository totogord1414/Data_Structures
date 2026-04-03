#include <string>
#define ERROR -1
#define kMaxSize 100

typedef int QElemSet;/* 队列元素类型定义为整型 */
typedef enum { Push, Pop, Inject, Eject, End } Operation; /* 操作类型 */
typedef int Position;
class Deque {
private:
    int capacity;/* 双端队列的容量 */
    Position front;/* 双端队列的队首指针，初始化为0 */
    Position rear;/* 双端队列的队尾指针，初始化为0 */
    QElemSet* data;/* 存储数据的数组 */
public:
    struct DequeException {
        std::string error_;
        DequeException(std::string s);
    };
    Deque(unsigned = kMaxSize);//构造函数，初始化一个空的线性表
    Deque(const Deque&);//拷贝构造函数
    Deque& operator=(const Deque&);//重载赋值运算符=
    ~Deque();// 析构函数,释放线性表占用的空间

    void InitDeque(int n);//初始化
    bool Push(QElemSet x);//从头部入队列，如果队满，无法入队列返回false, 否则返回true
    QElemSet Pop();//从头部出队列, 如果队空，返回ERROR，否则返回出队列元素
    bool Inject(QElemSet x);//从尾部入队列，如果队满，无法入队列返回false, 否则返回true
    QElemSet Eject();//从尾部出队列, 如果队空，返回ERROR，否则返回出队列元素
    void PrintDeque();//打印队列
};

bool Deque::Push(QElemSet x) {
    if((rear + 1) % capacity == front)
    {
        return false;
    }
    else
    {
        front = (front - 1 + capacity) % capacity;
        data[front] = x;
        return true;
    }
}
QElemSet Deque::Pop() {
    if(rear == front)
    {
        return ERROR;
    }
    else
    {
        QElemSet temp = data[front];
        front = (front + 1) % capacity;
        return temp;
    }
}
bool Deque::Inject(QElemSet x) {
    if((rear + 1) % capacity == front)
    {
        return false;
    }
    else
    {
        data[rear] = x;
        rear = (rear + 1) % capacity;
        return true;
    }
}
QElemSet Deque::Eject() {
    if(front == rear)
    {

        return ERROR;
    }
    else
    {
        rear = (rear - 1 + capacity) % capacity;
        return data[rear];
    }
}