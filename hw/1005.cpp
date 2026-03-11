//主要问题：边界条件不是很清晰，另外忘记更新list里面的_last参数


#include <string>

#define MAX_SIZE 100000
#define NIL -1

typedef int ElemType; // 元素类型，本题中定义元素类型为整型
typedef int Position; // 元素位置，这里我们用元素在线性表存储数据的数组中的下标表示元素位置

class List
{
private:
    ElemType *_data;   // 存储数据的数组，数据从下标为 0 的位置开始存储
    Position _last;    // 线性表中最后一个元素在数组中的下标，注意数组的下标从 0 开始
    int _max_size;     // 线性表最大能容纳的元素个数
public:
    struct ListException // 异常处理
    {
        std::string error;
        ListException(std::string s) : error(s) {};
    };
    List(unsigned = MAX_SIZE); // 构造函数，初始化一个空的线性表，根据指定的最大长度分配连续的内存空间
    List(const List &);
    List &operator=(const List &);
    ~List(); // 析构函数，释放线性表占用的空间

    Position search(ElemType x);           // 在线性表中查找元素 x
    bool insert(Position idx, ElemType x); // 在线性表下标为 idx 的位置插入元素 x
    ElemType remove(Position idx);         // 删除线性表中下标为 idx 的元素

    friend std::istream &operator>>(std::istream &, List &); // 读入一个线性表
};

Position List::search(ElemType x)
{
    // TODO
    for(Position i = 0;i <= _last;i++)
    {
        if(_data[i] == x)
            return i;
    }
    return NIL;
}


bool List::insert(Position idx, ElemType x)
{
    // TODO
    if(idx < 0 || idx > _last + 1)
        return false;
    if(_last >= _max_size - 1)
        return false;
    for(Position i = _last;i >= idx;i--)
    {
        _data[i + 1] = _data[i];
    }
    _data[idx] = x;
    _last++;
    return true;
}


ElemType List::remove(Position idx)
{
    // TODO
    if(idx < 0 || idx > _last)
        return NIL;
    ElemType temp = _data[idx];
    for(Position i = idx;i < _last;i++)
    {
        _data[i] = _data[i + 1];
    }
    _last--;
    return temp;
}