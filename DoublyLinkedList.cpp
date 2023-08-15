#include <iostream>
using namespace std;

struct lNode
{
    int data;
    lNode *next;
    lNode *prev;
};

typedef struct lNode node;

node *head = NULL;
node *tail = NULL;

class DoublyLinkedList
{
public:
    void insertAtBegin(int val)
    {
        node *newNode = (node *)malloc(sizeof(node));
        if (newNode == NULL)
        {
            cout << "Memory Error";
            return;
        }
        newNode->data = val;
        newNode->prev = NULL;
        if (head == NULL)
        {
            newNode->next = NULL;
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    void insertAtEnd(int val)
    {
        node *newNode = (node *)malloc(sizeof(node));
        if (newNode == NULL)
        {
            cout << "Memory Error";
        }
        if (head == NULL || tail == NULL)
        {
            insertAtBegin(val);
        }
        else
        {
            newNode->data = val;

            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;

            newNode->next = NULL;
        }
    }
    void insertAtPost(int pos, int val)
    {
        node *temp = head;
        node *prev;
        node *newNode = (node *)malloc(sizeof(node));
        if (newNode == NULL)
        {
            cout << "Memory Error";
        }
        newNode->data = val;
        for (int i = 0; i < pos; i++)
        {
            prev = temp;
            temp = temp->next;
        }
        newNode->next = prev->next;
        prev->next->prev = newNode;
        prev->next = newNode;
        newNode->prev = prev;
    }
    void deleteAtPos(int pos)
    {
        node *temp = head;
        node *prev;
        for (int i = 0; i <= pos - 1; i++)
        {
            prev = temp;
            temp = temp->next;
        }
        prev->next = temp->next;
        temp->next->prev = prev;
    }
    void display()
    {
        cout << endl
             << "Display Forward: ";
        node *temp = head;
        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
    }
    void displayRev()
    {
        node *temp = tail;
        cout << endl
             << "Display Reverse: ";
        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->prev;
        }
    }
};

int main()
{
    DoublyLinkedList list;

    list.insertAtBegin(3);
    list.insertAtBegin(2);
    list.insertAtBegin(1);
    list.display();
    list.displayRev();
    list.insertAtEnd(4);
    list.display();
    list.displayRev();
    list.insertAtPost(2, 9);
    list.display();
    list.displayRev();
    list.deleteAtPos(2);
    list.display();
    list.displayRev();
}