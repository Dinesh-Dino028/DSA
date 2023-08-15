#include <iostream>
using namespace std;

class BinaryTree
{
    struct Node
    {
        int data;
        Node *left;
        Node *right;
        Node(int d) : data(d), left(nullptr), right(nullptr){};
    };
    Node *root;

    BinaryTree(int d)
    {
        root = new Node(d);
    }

public:
    void insertLeft(Node *r, int val)
    {
        Node *newNode = new Node(val);
        r->left = newNode;
    }

    void insertright(Node *r, int val)
    {
        Node *newNode = new Node(val);
        r->right = newNode;
    }

    static void preOrder(Node *root)
    {
        if (root != nullptr)
        {
            cout << root->data << " ";
            preOrder(root->left);
            preOrder(root->right);
        }
    }

    static void inOrder(Node *root)
    {
        if (root != nullptr)
        {
            inOrder(root->left);
            cout << root->data << " ";
            inOrder(root->right);
        }
    }

    static void postOrder(Node *root)
    {
        if (root != nullptr)
        {
            postOrder(root->left);
            postOrder(root->right);
            cout << root->data << " ";
        }
    }
};

int main()
{
    BinaryTree tree(10);
    BinaryTree::Node *root = tree.root;

    tree.insertLeft(root, 5);
    tree.insertright(root, 15);

    BinaryTree::Node *leftNode = root->left;

    tree.insertLeft(leftNode, 3);
    tree.insertright(leftNode, 8);

    BinaryTree::Node *rightNode = root->right;

    tree.insertLeft(rightNode, 12);

    cout << "Preorder traversal:" << endl;
    BinaryTree::preOrder(root);

    cout << endl
         << "Inorder traversal:" << endl;
    BinaryTree::inOrder(root);

    cout << endl
         << "Postorder traversal:" << endl;
    BinaryTree::postOrder(root);

    return 0;
};