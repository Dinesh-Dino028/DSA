#include <iostream>

using namespace std;

class BinarySearchTree
{
public:
    struct Node
    {
        int val;
        Node *left;
        Node *right;

        Node(int data) : val(data), left(NULL), right(NULL){};
    };

    Node *root;

    BinarySearchTree(int d)
    {
        root = new Node(d);
    }

    Node *insert(Node *node, int val)
    {
        if (node == NULL)
        {
            return new Node(val);
        }
        if (val < node->val)
        {
            node->left = insert(node->left, val); // Corrected: Use "node" instead of "root"
        } 
        else if (val > node->val)
        {
            node->right = insert(node->right, val); // Corrected: Use "node" instead of "root"
        }
        return node;
    }

    void inOrder(Node *node)
    {
        if (node != NULL)
        {
            inOrder(node->left);
            cout << node->val << " ";
            inOrder(node->right);
        }
    }
};

int main()
{
    BinarySearchTree tree(10);

    BinarySearchTree::Node *root = tree.root;

    tree.insert(root, 2);
    tree.insert(root, 5);
    tree.insert(root, 10);
    tree.insert(root, 15);

    tree.inOrder(root);

    return 0;
}
