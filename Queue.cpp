#include <iostream>

using namespace std;

struct lNode
{
    int data;
    struct lNode *next;
};

typedef struct lNode node;

struct Queue
{
    node *front;
    node *rear;
};

class Queues
{

public:
    struct Queue *createQueue()
    {
        struct Queue *q = (struct Queue *)malloc(sizeof(struct Queue));
        q->front = NULL;
        q->rear = NULL;
        return q;
    }

    void enqueue(struct Queue *q, int val)
    {
        node *newNode = (node *)malloc(sizeof(node));
        if (newNode == NULL)
        {
            cout << "Out of memory";
            return;
        }
        newNode->data = val;
        newNode->next = NULL;
        if (q->rear == NULL)
        {
            q->front = newNode;
        }
        else
        {
            q->rear->next = newNode;
        }
            q->rear = newNode;
        cout << "Enqueued value " << val << endl;
    }

    int dequeue(struct Queue *q)
    {
        if (q->front == NULL)
        {
            printf("\nQueue is empty");
            return INT_MIN;
        }
        node *del = q->front;
        q->front = q->front->next;
        if(q->front == NULL){
            q->rear = NULL;
        }
        int temp = del->data;
        free(del);
        return temp;
    }
};
    int main()
    {
        Queues q;
        struct Queue *q1 = q.createQueue();
        struct Queue *q2 = q.createQueue();
        struct Queue *q3 = q.createQueue();

        q.enqueue(q1, 1);
        q.enqueue(q1, 2);
        q.enqueue(q1, 3);

        cout<<"dequeue: "<< q.dequeue(q1);

        return 0;
    };