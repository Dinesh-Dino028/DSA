#include <iostream>
using namespace std;

struct lNode
{
    int data;
    lNode *next; // self referential structure
};

typedef struct lNode node;

node *head = NULL;

class LinkedList
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
        if (head == NULL)
        {
            newNode->next = NULL;
            head = newNode;
        }
        else
        {
            newNode->next = head;
            head = newNode;
        }
    }
    void insertAtEnd(int val)
    {
        node *temp = head;
        node *prev;
        node *newNode = (node *)malloc(sizeof(node));
        if (newNode == NULL)
        {
            cout << "Memory Error";
        }
        newNode->data = val;
        while (temp != NULL)
        {
            prev = temp;
            temp = temp->next;
        }
        prev->next = newNode;
        newNode->next = NULL;
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
        prev->next = newNode;
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
    }
    void display()
    {
        node *temp = head;
        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
    }
};

int main()
{
    LinkedList list;
    int choice, pos, val;

    while (true)
    {
        cout << "\n ----------------List Menu---------------- \n";
        cout << "1.Insert at the Begin \n";
        cout << "2.Insert at the end \n";
        cout << "3.Insert at the position \n";
        cout << "4.Delete at the position \n";
        cout << "5.Display \n";
        cout << "6.Exit \n";
        cout << "-------------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value to insert At Begin: \n";
            cin >> val;
            list.insertAtBegin(val);
            break;
        case 2:
            cout << "Enter value to insert At End: \n";
            cin >> val;
            list.insertAtEnd(val);
            break;
        case 3:
            cout << "Enter position at insert: \n";
            cin >> pos;
            cout << "Enter Value: \n";
            cin >> val;
            list.insertAtPost(pos, val);
            break;
        case 4:
            cout << "Enter position at delete: \n";
            cin >> pos;
            list.deleteAtPos(pos);
            break;
        case 5:
            cout << "Array List values: ";
            list.display();
            break;
        case 6:
            exit(0);
            break;
        default:
        cout<<"Invalid Choice";
            break;
        }
    }
}