#include <iostream>

using namespace std;

struct lNode
{
    int data;
    lNode *next;
};

typedef struct lNode node;

lNode *last = NULL;

class CircularLinkedList
{
public:
    void insertAtBeginning(int val)
    {
        node *newNode = (node *)malloc(sizeof(node));
        newNode->data = val;
        if (last == NULL)
        {
            last = newNode;
            newNode->next = last;
        }
        else
        {
            newNode->next = last->next;
            last->next = newNode;
        }
        cout << "Value Inserted at Begenning" << endl;
    }
    void insertAtEnd(int val)
    {
        node *newNode = (node *)malloc(sizeof(node));
        newNode->data = val;
        if (last == NULL)
        {
            last = newNode;
            newNode->next = last;
        }
        else
        {
            newNode->next = last->next;
            last->next = newNode;
            last = newNode;
        }
        cout << "Value Inserted at End" << endl;
    }
    void deletAtBeginning()
    {
        if (last == NULL)
        {
            cout << "List is empty" << endl;
            return;
        }
        node *del;

        if (last->next == last)
        {
            del = last;
            last = NULL;
        }
        else
        {
            del = last->next;
            last->next = last->next->next;
        }
        cout << "Deleted the begenning value: " << del->data << endl;
        free(del);
    }
    void deleteAtEnd()
    {
        if (last == NULL)
        {
            cout << "List is empty" << endl;
            return;
        }
        node *del;
        if (last->next == last)
        {
            del = last;
            last = NULL;
        }
        else
        {
            node *temp = last->next;
            del = last;
            while (temp->next != last)
            {
                temp = temp->next;
            }
            temp->next = last->next;

            last = temp;
            cout << "Deleted the end value: " << del->data << endl;
            free(del);
        }
    }
    void display()
    {
        if (last == NULL)
        {
            cout << "List is emoty" << endl;
            return;
        }
        node *temp = last->next;
        do
        {
            cout << "List values are: " << temp->data << endl;
            temp = temp->next;

        } while (temp != last->next);
    }
};

int main()
{
    CircularLinkedList list;
    list.insertAtBeginning(3);
    list.insertAtBeginning(2);
    list.insertAtBeginning(1);
    list.insertAtEnd(4);
    list.display();
    list.deletAtBeginning();
    list.display();
    list.deleteAtEnd();
    list.display();

    return 0;
}