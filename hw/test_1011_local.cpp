#include <iostream>
#include <string>

using namespace std;
#define NIL nullptr
typedef int ElemType;
typedef struct ListNode *Position;
struct ListNode {
    ElemType data_;
    Position next_;
};

class LinkedList {
public:
    Position head_;
    int length_;
    LinkedList() { head_ = new ListNode; head_->next_=NIL; length_=0; }
    ~LinkedList() {} // dummy
    int Josephus(const int& n, const int& m, const int& k);
};

int LinkedList::Josephus(const int& n, const int& m, const int& k)
{
    if(n <= 0 || m <= 0 || k <= 0 || n < k)
        return -1;
    
    Position clean_p = head_->next_;
    int initial_len = length_;
    for (int i = 0; i < initial_len; i++)
    {
        if (clean_p == head_) clean_p = clean_p->next_;
        Position temp = clean_p;
        clean_p = clean_p->next_;
        delete temp;
    }
    head_->next_ = NIL;
    length_ = n;

    Position p_curr_tail = head_;
    for(int i = 1; i <= length_; i++)
    {
        Position NewNode = new ListNode;
        NewNode->data_ = i;
        NewNode->next_ = NIL;
        p_curr_tail->next_ = NewNode;
        p_curr_tail = NewNode;
    }
    
    p_curr_tail->next_ = head_;
    
    int result = 0;
    Position pre_pointer = p_curr_tail; 
    
    for(int i = 1; i <= k; i++)
    {
        int moves = (m - 1) % length_;
        for(int step = 0; step < moves; step++)
        {
            pre_pointer = pre_pointer->next_;
            if (pre_pointer == head_) {
                pre_pointer = pre_pointer->next_; 
            }
        }
        
        Position target = pre_pointer->next_;
        if (target == head_) {
            pre_pointer = target;
            target = target->next_; 
        }
        
        if(i == k)
        {
            result = target->data_;
        }
        
        pre_pointer->next_ = target->next_;
        delete target;
        length_--;
    }
    
    if (length_ == 0)
    {
        head_->next_ = NIL; 
    }

    return result;
}

int main() {
    LinkedList l;
    cout << l.Josephus(5, 2, 1) << endl;
    cout << l.Josephus(5, 2, 2) << endl;
    cout << l.Josephus(5, 2, 3) << endl;
    cout << l.Josephus(5, 2, 4) << endl;
    cout << l.Josephus(5, 2, 5) << endl;
    return 0;
}
