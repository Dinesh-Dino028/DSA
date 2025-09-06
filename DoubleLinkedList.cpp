#include <bits/stdc++.h>
using namespace std;

struct Node
{
public:
    Node *prev;
    int data;
    Node *next;

    Node(int val)
    {
        data = val;
        prev = nullptr;
        next = nullptr;
    }
};

class DoubleLinkedList
{
private:
    Node *head;

public:
    DoubleLinkedList()
    {
        head = nullptr;
    }

    void insertAtEnd(int val)
    {
        Node *newNode = new Node(val);
        if (!head)
        {
            head = newNode;
            return;
        }

        Node *temp = head;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }

    void display()
    {
        Node *temp = head;
        while (temp)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    void deleteNode(int val)
    {
        Node *temp = head;

        while (temp && temp->data != val)
        {
            temp = temp->next;
        }
        if (!temp)
        {
            cout << "value not found";
            return;
        }
        if (temp->prev)
        {
            temp->prev->next = temp->next;
        }
        else
        {
            head = temp->next;
        }

        if (temp->next)
        {
            temp->next->prev = temp->prev;
        }
        delete temp;
        cout << "Node deleted. \n";
    }

    void reverseDLL()
    {
        if (!head || !head->next)
        {
            return;
        }
        Node *curr = head;
        Node *temp = nullptr;
        while (curr)
        {
            temp = curr->prev;
            curr->prev = curr->next;
            curr->next = temp;

            curr = curr->prev;
        }
        if (temp)
        {
            head = temp->prev;
        }
    }

    Node* findTail(Node* head){
        Node* tail = head;
        while(tail->next){
            tail = tail->next;
        }
        return tail;
    }

    vector<pair<int, int>> findPairsWithGivenSum(int target)
    {
        vector<pair<int, int>> pair;
        if (!head)
        {
            return pair;
        }
        Node *left = head;
        Node *right = findTail(head);

        while (left->data < right->data)
        {
            if ((left->data + right->data) == target)
            {
                pair.push_back({left->data, right->data});
                left = left->next;
                right = right->prev;
            }
            else if ((left->data + right->data) < target)
            {
                left = left->next;
            }
            else
            {
                right = right->prev;
            }
        }
        return pair;
    }
};

int main()
{
    DoubleLinkedList list;
    list.insertAtEnd(1);
    list.insertAtEnd(2);
    list.insertAtEnd(4);
    list.insertAtEnd(5);
    list.insertAtEnd(6);
    list.insertAtEnd(8);
    list.insertAtEnd(9);

    list.display();
    // list.deleteNode(30);
    // list.reverseDLL();
    list.findPairsWithGivenSum(7);

    list.display();
    return 0;
};