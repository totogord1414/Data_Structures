#include <string>
#include <iostream>
#include <vector>

using namespace std;
#define MAXNUM 200001
struct Node{
    int num;
    int group;
    Node* next;
    Node (int n, int g, Node* np = nullptr):num(n),group(g),next(np){};
};

struct Group_Member
{
    int group;
    Node* pos;
};
vector<Node*> group_pointer(MAXNUM, nullptr);
vector<Group_Member> group_member(MAXNUM, {-1, nullptr});

Node* head = nullptr;
Node* tail = nullptr;

void enter_queue(Node* x)
{
    if(group_pointer[x->group] == nullptr)// if x is the first element in queue in this group
    {
        group_pointer[x->group] = x;
        if(head == nullptr && tail == nullptr)//if x is the first element in queue
        {
            head = x;
            tail = x;
            return;
        }
        tail->next = x;
        tail = x;
        return;
    }
    else{
        Node* curr = group_pointer[x->group];
        group_pointer[x->group] = x;
        if(curr->next == nullptr)//tail of the queue
        {
            curr->next = x;
            tail = x;
            return;
        }
        {
            x->next = curr->next;
            curr->next = x;
            return;
        }
    }
}
bool in_queue(int x)
{
    if(group_member[x].pos == nullptr)
    {
        return false;
    }
    return true;
}

int depart_queue()
{
    if(head == nullptr)
    {
        return -1;
    }
    group_member[head->num].pos = nullptr;
    if (head == tail)
    {
        Node* temp = head;
        int temp_n = temp->num;
        head = nullptr;
        tail = nullptr;
        group_pointer[temp->group] = nullptr; 
        delete temp;
        return temp_n;
    }
    else
    {
        Node* temp = head;
        int temp_n = temp->num;
        if(head->group != head->next->group)
        {
            group_pointer[head->group] = nullptr;
        }
        head = head->next;
        delete temp;
        return temp_n;
    }
}
int main()
{
    int member_num;
    cin >> member_num;
    for(int i = 0;i < member_num;i++)
    {
        cin >> group_member[i].group;
    }
    int command_num;
    cin >> command_num;
    for (int i = 0;i < command_num; i++)
    {
        string command;
        cin >> command;
        if(command == "ENQUEUE")
        {
            int x;
            cin >> x;
            if(in_queue(x) == true)
            {
                continue;
            }
            else
            {
                Node* NewNode = new Node(x, group_member[x].group);
                enter_queue(NewNode);
                group_member[x].pos = NewNode;
            }
        }
        else if(command == "DEQUEUE")
        {
            cout << depart_queue() << endl;
        }
        else 
        {
            cout << "command error" << endl;
            return -1;
        }
    }
    while(head != nullptr)
    {
        Node* temp = head;
        head = head->next ;
        delete temp;
    }
    tail = nullptr;
    return 0;
}