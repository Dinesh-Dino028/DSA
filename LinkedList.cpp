#include <bits/stdc++.h>
#include <chrono>
#include <cmath>
using namespace std;

struct Node
{
public:
    int data;
    Node *next;

public:
    Node(int data1, Node *next1)
    {
        data = data1;
        next = next1;
    }

    Node(int data1)
    {
        data = data1;
        next = nullptr;
    }
};

class Linkedlist
{
public:
    Node *convertALToLL(vector<int> &arr)
    {
        Node *head = new Node(arr[0]);
        Node *mover = head;
        for (int i = 1; i < arr.size(); i++)
        {
            Node *temp = new Node(arr[i]);
            mover->next = temp;
            mover = temp;
        }
        return head;
    }

    void insertNode(Node *head, int pos, int val)
    {
        Node *temp = head;
        Node *newNode = new Node(val);
        int count = 1;
        while (temp)
        {
            if (count == pos)
            {
                newNode->next = temp->next;
                temp->next = newNode;
                return;
            }
            temp = temp->next;
            count++;
        }
    }

    void deleteNode(Node *head, int pos)
    {
        Node *prev = head;
        Node *temp = head->next;
        int count = 1;
        while (temp)
        {
            if (count == pos)
            {
                prev->next = temp->next;
            }
            temp = temp->next;
            prev = prev->next;
            count++;
        }
    }

    void printLL(Node *head)
    {
        Node *temp = head;
        while (temp)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
    }

    bool searchKey(int n, Node *head, int key)
    {
        if (n == 0 || head == NULL)
        {
            return false;
        }
        Node *temp = head;
        while (temp)
        {
            if (temp->data == key)
            {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    int checkIfPresent(Node *head, int val)
    {
        Node *temp = head;
        while (temp)
        {
            if (temp->data == val)
            {
                return temp->data;
            }
            temp = temp->next;
        }
        return 0;
    }

    Node *reverseLL(Node *head)
    {
        Node *temp = head;
        Node *prev = NULL;
        Node *front;
        while (temp)
        {
            front = temp->next;
            temp->next = prev;
            prev = temp;
            temp = front;
        }
        return prev;
    }

    bool isPalindrome(Node *head)
    {
        Node *temp = head;
        stack<int> st;
        while (temp)
        {
            st.push(temp->data);
            temp = temp->next;
        }
        temp = head;
        while (temp)
        {
            if (st.top() != temp->data)
            {
                return false;
            }
            st.pop();
            temp = temp->next;
        }
        return true;
    }

    Node *insertInMiddle(Node *head, int x)
    {
        if (head == NULL)
        {
            return new Node(x); // If the list is empty, create a new node as the head
        }

        Node *slow = head;
        Node *fast = head;

        while (fast != NULL && fast->next != NULL && fast->next->next != NULL)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        Node *newNode = new Node(x);
        newNode->next = slow->next;
        slow->next = newNode;

        return head;
    }

    Node *createLL(int length)
    {
        if (length <= 0)
        {
            return NULL;
        }
        srand(time(0));                      // Seed for random number generation
        Node *head = new Node(rand() % 100); // Random value between 0 and 99
        Node *temp = head;
        for (int i = 1; i < length; i++)
        {
            temp->next = new Node(rand() % 100);
            temp = temp->next;
        }
        return head;
    }

    Node *intersectPoint(Node *head1, Node *head2)
    {
        Node *temp1 = head1;
        Node *temp2 = head2;
        if (!head1 || !head2)
            return nullptr;

        // Traverse both lists, switching heads when reaching end
        while (temp1 != temp2)
        {
            temp1 = temp1 ? temp1->next : head2;
            temp2 = temp2 ? temp2->next : head1;
        }

        return temp1; // This will be null if no intersection, or the intersection node
    }

    Node *makeUnion(struct Node *head1, struct Node *head2)
    {

        set<int> s;

        Node *temp1 = head1;
        Node *temp2 = head2;

        while (temp1)
        {
            s.insert(temp1->data);
            temp1 = temp1->next;
        }

        while (temp2)
        {
            s.insert(temp2->data);
            temp2 = temp2->next;
        }

        Node *newhead = nullptr;
        Node *tail = nullptr;
        for (int val : s)
        {
            Node *newNode = new Node(val);
            if (!newhead)
            {
                newhead = newNode;
                tail = newNode;
            }
            else
            {
                tail->next = newNode;
                tail = newNode;
            }
        }
        return newhead;
    }

    void deleteNode(Node *del_node)
    {
        del_node->data = del_node->next->data;
        del_node->next = del_node->next->next;
    }

    int countPairs(struct Node *head1, struct Node *head2, int x)
    {
        Node *temp = head2;
        int countPairs = 0;
        unordered_set<int> s;
        while (temp)
        {
            s.insert(temp->data);
            temp = temp->next;
        }
        temp = head1;
        while (temp)
        {
            if (s.find(x - temp->data) != s.end())
            {
                countPairs++;
            }
            temp = temp->next;
        }
        return countPairs;
    }

    Node *reverseKGroup(Node *head, int k)
    {
        if (!head || k <= 1)
            return head;

        Node *current = head;
        Node *prevTail = NULL;
        Node *newHead = NULL;

        while (current)
        {
            Node *groupHead = current;
            Node *prev = NULL;
            int count = 0;

            // Reverse k nodes (or less if at end)
            while (current && count < k)
            {
                Node *nextNode = current->next;
                current->next = prev;
                prev = current;
                current = nextNode;
                count++;
            }

            if (!newHead)
                newHead = prev; // First group's new head

            if (prevTail)
                prevTail->next = prev; // Connect previous group to current

            prevTail = groupHead; // Last node of this group after reverse
        }
        return newHead;
    }

    bool detectLoop(Node *head)
    {
        // Node* temp = head;
        // unordered_map<Node*, int> map;
        // while(temp){
        //     if(map.find(temp) != map.end()){
        //         return true;
        //     }
        //     map[temp]++;
        //     temp = temp->next;
        // }

        // return false;

        // optimal

        Node *slow = head;
        Node *fast = head;

        while (fast != NULL && fast->next != NULL)
        {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
            {
                return true;
            }
        }
        return false;
    }

    int findLength(Node *slow, Node *fast)
    {
        fast = fast->next;
        int count = 1;
        while (fast != slow)
        {
            count++;
            fast = fast->next;
        }
        return count;
    }
    int countNodesinLoop(Node *head)
    {
        Node *slow = head;
        Node *fast = head;
        while (fast != NULL && fast->next != NULL)
        {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
            {
                return findLength(slow, fast);
            }
        }
        return 0;
    }

    Node *findFirstNode(Node *head)
    {
        Node *slow = head;
        Node *fast = head;

        while (fast != NULL && fast->next != NULL)
        {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
            {
                slow = head;
                while (slow != fast)
                {
                    slow = slow->next;
                    fast = fast->next;
                }
                return slow;
            }
        }
        // If no loop is detected, return a special value (e.g., nullptr or -1 as data)
        return nullptr;
    }
    void removeLoop(Node *head)
    {
        if (!head || !head->next)
            return;

        Node *slow = head, *fast = head;

        // Step 1: Detect loop using Floyd’s Cycle Detection
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast)
            {
                break; // Loop detected
            }
        }

        // Step 2: If loop exists
        if (slow == fast)
        {
            slow = head;

            // Special case: If loop starts at head
            if (slow == fast)
            {
                while (fast->next != slow)
                {
                    fast = fast->next;
                }
            }
            else
            {
                while (slow->next != fast->next)
                {
                    slow = slow->next;
                    fast = fast->next;
                }
            }

            // Step 3: Remove loop
            fast->next = NULL;
        }
    }

    Node *segregate(Node *head)
    {
        Node *temp = head;

        Node *zeroHead = new Node(-1);
        Node *oneHead = new Node(-1);
        Node *twoHead = new Node(-1);

        Node *zero = zeroHead;
        Node *one = oneHead;
        Node *two = twoHead;

        if (head == NULL || head->next == NULL)
        {
            return head;
        }
        while (temp)
        {
            if (temp->data == 0)
            {
                zero->next = temp;
                zero = temp;
            }
            else if (temp->data == 1)
            {
                one->next = temp;
                one = temp;
            }
            else
            {
                two->next = temp;
                two = temp;
            }
            temp = temp->next;
        }
        zero->next = oneHead->next ? oneHead->next : twoHead->next;
        one->next = twoHead->next;
        two->next = NULL;

        Node *newHead = zeroHead->next;

        delete zeroHead;
        delete oneHead;
        delete twoHead;
        return newHead;
    }

    Node *pairWiseSwap(Node *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        Node *prev = nullptr;
        Node *curr = head;
        head = head->next; // New head will be second node

        while (curr && curr->next)
        {
            Node *nextNode = curr->next;
            Node *nextPair = nextNode->next;

            // Swap
            nextNode->next = curr;
            curr->next = nextPair;

            if (prev)
                prev->next = nextNode;

            // Move pointers ahead
            prev = curr;
            curr = nextPair;
        }

        return head;
    }

    Node *sortedMerge(Node *head1, Node *head2)
    {
        if (!head1)
            return head2;
        if (!head2)
            return head1;

        Node *newHead = nullptr;
        Node *tail = nullptr;

        while (head1 && head2)
        {
            Node *temp = nullptr;
            if (head1->data < head2->data)
            {
                temp = head1;
                head1 = head1->next;
            }
            else
            {
                temp = head2;
                head2 = head2->next;
            }

            if (!newHead)
            {
                newHead = temp;
                tail = temp;
            }
            else
            {
                tail->next = temp;
                tail = temp;
            }
        }

        if (head1)
        {
            tail->next = head1;
        }
        else if (head2)
        {
            tail->next = head2;
        }

        return newHead;
    }

    // Merge Sort in LL
    Node *findMiddle(Node *head)
    {
        Node *slow = head;
        Node *fast = head;

        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
    Node *merge(Node *left, Node *right)
    {
        if (!left)
            return right;
        if (!right)
            return left;

        Node *result;

        if (left->data < right->data)
        {
            result = left;
            result->next = merge(left->next, right);
        }
        else
        {
            result = right;
            result->next = merge(left, right->next);
        }
        return result;
    }
    Node *mergeSort(Node *head)
    {
        if (!head || !head->next)
            return head;

        Node *middle = findMiddle(head);
        Node *nextToMiddle = middle->next;

        middle->next = nullptr;

        Node *left = mergeSort(head);
        Node *right = mergeSort(nextToMiddle);

        return merge(left, right);
    }

    // Quick Sort in LL
    Node *partition(Node *head, Node *end, Node **newHead, Node **newEnd)
    {
        Node *pivot = end;
        Node *prev = nullptr, *cur = head, *tail = pivot;

        while (cur != pivot)
        {
            if (cur->data < pivot->data)
            {
                if ((*newHead) == nullptr)
                    (*newHead) = cur;

                prev = cur;
                cur = cur->next;
            }
            else
            {
                if (prev)
                    prev->next = cur->next;

                Node *temp = cur->next;
                cur->next = nullptr;
                tail->next = cur;
                tail = cur;
                cur = temp;
            }
        }

        if ((*newHead) == nullptr)
            (*newHead) = pivot;

        (*newEnd) = tail;

        return pivot;
    }
    Node *quickSortRecur(Node *head, Node *end)
    {
        if (!head || head == end)
            return head;

        Node *newHead = nullptr, *newEnd = nullptr;

        Node *pivot = partition(head, end, &newHead, &newEnd);

        if (newHead != pivot)
        {
            Node *temp = newHead;
            while (temp->next != pivot)
                temp = temp->next;
            temp->next = nullptr;

            newHead = quickSortRecur(newHead, temp);

            temp = newHead;
            while (temp->next)
                temp = temp->next;
            temp->next = pivot;
        }

        pivot->next = quickSortRecur(pivot->next, newEnd);

        return newHead;
    }
    Node *quickSort(Node *head)
    {
        Node *end = head;
        while (end->next)
            end = end->next;

        return quickSortRecur(head, end);
    }

    Node *removeDuplicatesInSortedLL(Node *head)
    {
        if (!head || !head->next)
            return head;

        Node *prev = head;
        Node *curr = head->next;

        while (curr)
        {
            if (prev->data == curr->data)
            {
                prev->next = curr->next;
                delete curr; // Free memory of the duplicate node
                curr = prev->next;
            }
            else
            {
                prev = curr;
                curr = curr->next;
            }
        }
        return head;
    }

    Node *removeDuplicatesInUnsortedLL(Node *head)
    {
        if (!head || !head->next)
            return head;

        unordered_set<int> seen;
        Node *prev = nullptr;
        Node *curr = head;

        while (curr)
        {
            if (seen.find(curr->data) != seen.end())
            {
                prev->next = curr->next;
                delete curr; // Free memory of the duplicate node
                curr = prev->next;
            }
            else
            {
                seen.insert(curr->data);
                prev = curr;
                curr = curr->next;
            }
        }
        return head;
    }

    Node *divide(Node *head)
    {
        if (!head || !head->next)
        {
            return head;
        }

        Node *evenHead = nullptr;
        Node *evenTail = nullptr;
        Node *oddHead = nullptr;
        Node *oddTail = nullptr;

        Node *current = head;

        while (current)
        {
            if (current->data % 2 == 0)
            {
                if (!evenHead)
                {
                    evenHead = current;
                    evenTail = current;
                }
                else
                {
                    evenTail->next = current;
                    evenTail = current;
                }
            }
            else
            {
                if (!oddHead)
                {
                    oddHead = current;
                    oddTail = current;
                }
                else
                {
                    oddTail->next = current;
                    oddTail = current;
                }
            }
            current = current->next;
        }

        if (evenTail)
        {
            evenTail->next = oddHead;
        }
        if (oddTail)
        {
            oddTail->next = nullptr;
        }

        return evenHead ? evenHead : oddHead;
    }

    // Node* reverseLL(Node* head) {
    //     Node* prev = nullptr;
    //     Node* curr = head;
    //     Node* next = nullptr;
    //     while (curr) {
    //         next = curr->next;
    //         curr->next = prev;
    //         prev = curr;
    //         curr = next;
    //     }
    //     return prev;
    // }

    int helper(Node *temp)
    {
        if (!temp)
            return 1;
        int carry = helper(temp->next);
        temp->data += carry;
        if (temp->data < 10)
        {
            return 0;
        }
        else
        {
            temp->data = 0;
            return 1;
        }
    }
    Node *addOne(Node *head)
    {
        Node *temp = head;

        int carry = helper(temp);

        if (carry == 1)
        {
            Node *newNode = new Node(1);
            newNode->next = head;
            return newNode;
        }
        else
        {
            return head;
        }
    }

    Node *reverseLL2(Node *head)
    {
        Node *prev = nullptr, *curr = head, *next = nullptr;
        while (curr)
        {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }

    Node *addTwoLists(Node *num1, Node *num2)
    {
        num1 = reverseLL2(num1);
        num2 = reverseLL2(num2);

        Node *dummy = new Node(0);
        Node *temp = dummy;
        int carry = 0;

        while (num1 || num2 || carry)
        {
            int sum = carry;
            if (num1)
            {
                sum += num1->data;
                num1 = num1->next;
            }
            if (num2)
            {
                sum += num2->data;
                num2 = num2->next;
            }
            carry = sum / 10;
            temp->next = new Node(sum % 10);
            temp = temp->next;
        }

        return reverseLL2(dummy->next);
    }

    void reorderList(Node *head)
    {
        if (!head || !head->next || !head->next->next)
        {
            return;
        }

        // find middle
        Node *slow = head;
        Node *fast = head;
        while (fast->next && fast->next->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        // reverse second half
        Node *second = reverseLL(slow->next);
        slow->next = nullptr;

        Node *first = head;

        // merge two halves
        while (second)
        {
            Node *temp1 = first->next;
            Node *temp2 = second->next;

            first->next = second;
            second->next = temp1;

            first = temp1;
            second = temp2;
        }
    }

    /* Node* mergeRoot(Node *a, Node* b){
        Node* temp = new Node(0);
        Node* res = temp;

        while(a && b){
            if(a->data < b->data){
                temp->bottom = a;
                temp = temp->bottom;
                a = a->bottom;
            }
            else{
                temp->bottom = b;
                temp = temp->bottom;
                b = b->bottom;
            }
        }

        if(a){
            temp->bottom = a;
        }
        else{
            temp->bottom = b;
        }
        return res->bottom;
    }*/
    Node *flatten(Node *root)
    {
        if (!root || !root->next)
        {
            return root;
        }

        root->next = flatten(root->next);

        // root = mergeRoot(root, root->next);
        return root;
    }

    Node *compute(Node *head)
    {
        head = reverseLL(head);

        int maxVal = head->data;

        Node *prev = head;
        Node *curr = head->next;

        while (curr)
        {
            // include
            if (curr->data >= maxVal)
            {
                prev = curr;
                maxVal = curr->data;
            }
            // delete
            else
            {
                prev->next = curr->next;
            }
            curr = curr->next;
        }

        return reverseLL(head);
    }

    Node *linkdelete(Node *head, int m, int n)
    {
        if (!head || m == 0)
        {
            // If m is 0, delete all nodes
            return nullptr;
        }
        Node *curr = head;
        while (curr)
        {
            // Skip m-1 nodes
            for (int i = 1; i < m && curr; i++)
            {
                curr = curr->next;
            }
            if (!curr)
                break;

            // Start deleting next n nodes only if there are enough nodes
            Node *temp = curr->next;
            int i = 0;
            while (i < n && temp)
            {
                Node *del = temp;
                temp = temp->next;
                delete del;
                i++;
            }
            curr->next = temp;
            curr = temp;
        }
        return head;
    }

    int countCommon(Node *a, Node *b)
    {
        int count = 0;
        while (a && b)
        {
            if (a->data == b->data)
            {
                count++;
            }
            else
            {
                break;
            }
            a = a->next;
            b = b->next;
        }
        return count;
    }
    int maxPalindrome(Node *head)
    {
        Node *prev = nullptr;
        Node *curr = head;
        int result = 0;
        while (curr)
        {
            Node *next = curr->next;
            curr->next = prev;

            // odd length
            result = max(result, 2 * countCommon(prev, next) + 1);

            result = max(result, 2 * countCommon(curr, next));
            prev = curr;
            curr = next;
        }
        return result;
    }
};

int main()
{
    Linkedlist ll;
    vector<int> arr = {12, 15, 10, 11, 5, 6, 2, 3};
    Node *head = ll.convertALToLL(arr);

    vector<int> arr2 = {3, 4, 5};
    Node *head2 = ll.convertALToLL(arr2);

    //    Node * head = createLL(4);
    // Node* temp = head;
    // int count=0;
    // while(temp){
    //     cout<<temp->data<<" ";
    //     temp = temp->next;
    //     count++;
    // }
    // cout<<"count: "<<count;
    // int result = checkIfPresent(head, 5);
    // cout<<"result:"<<result;

    //  insert(head, 1, 15);
    // deleteNode(head, 1);
    // cout << searchKey(3, NULL, 4);

    // cout<<reverseLL(head)->data;

    // cout << isPalindrome(head);

    //   insertInMiddle(head, 2);
    //  Node* del_node = head->next;
    //  deleteNode(del_node);
    // Create a loop for testing

    // loop
    //   head->next->next->next->next = head->next;

    // Find the first node in the loop
    // Node * sortedNode = segregate(head);
    // Node *res = pairWiseSwap(head);
    Node *res =
        //    cout << ll.maxPalindrome(head);
        ll.compute(head);
    ll.printLL(res);
}
