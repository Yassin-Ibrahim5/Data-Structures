#include <iostream>

using namespace std;

struct Contact
{
    string name;
    string phone;
    string email;
};

struct Node
{
    int id;
    Contact contact;
    Node *left;
    Node *right;
    int height;

    Node(int k, const Contact &c) : id(k), contact(c), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree
{
private:
    Node *root;

public:
    AVLTree() : root(nullptr) {}

    ~AVLTree() { clearTree(root); }

    bool insert(int key, const Contact &c)
    {
        bool success = false;
        root = insert(root, key, c, success);
        return success;
    }

    bool remove(int key)
    {
        bool success = false;
        root = deleteNode(root, key, success);
        return success;
    }

    Node *search(int key)
    {
        return search(root, key);
    }

    void inorder()
    {
        inorder(root);
    }

    void printTree()
    {
        if (!root)
        {
            cout << "Empty tree" << endl;
        } else
        {
            printTree(root, "", true);
        }
    }

private:

    int height(Node *node) const;

    int balanceFactor(Node *node) const;

    void updateHeight(Node *node);

    Node *rightRotate(Node *node);

    Node *leftRotate(Node *node);

    Node *insert(Node *node, int key, const Contact &c, bool &success);

    Node *findMin(Node *node) const;

    Node *deleteNode(Node *node, int key, bool &success);

    Node *search(Node *node, int key) const;

    void inorder(Node *node) const;

    void printTree(Node *node, string indent, bool last) const;

    void clearTree(Node *node);

};

int AVLTree::height(Node *node) const
{
    if (node)
    {
        return node->height;
    }
    return 0;
}

int AVLTree::balanceFactor(Node *node) const
{
    if (node)
    {
        return height(node->left) - height(node->right);
    }
    return 0;
}

void AVLTree::updateHeight(Node *node)
{
    node->height = 1 + max(height(node->left), height(node->right));
}

Node *AVLTree::rightRotate(Node *node)
{
    Node *temp1 = node->left;
    Node *temp2 = temp1->right;

    temp1->left = node;
    node->right = temp2;

    updateHeight(node);
    updateHeight(temp1);
    return temp1;
}

Node *AVLTree::leftRotate(Node *node)
{
    Node *temp1 = node->right;
    Node *temp2 = temp1->left;

    temp1->left = node;
    node->right = temp2;

    updateHeight(node);
    updateHeight(temp1);
    return temp1;
}

Node *AVLTree::insert(Node *node, int key, const Contact &c, bool &success)
{
    if (!node)
    {
        success = true;
        return new Node(key, c);
    }
    if (key < node->id)
    {
        node->left = insert(node->left, key, c, success);
    } else if (key > node->id)
    {
        node->right = insert(node->right, key, c, success);
    } else
    {
        success = false;
        return node;
    }

    updateHeight(node);
    int bf = balanceFactor(node);

    if (bf > 1 && key < node->left->id)
    {
        return rightRotate(node);
    }
    if (bf < -1 && key > node->right->id)
    {
        return leftRotate(node);
    }
    if (bf > 1 && key > node->left->id)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (bf < -1 && key < node->right->id)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node *AVLTree::findMin(Node *node) const
{
    Node *current = node;
    while (current && current->left != nullptr)
    {
        current = current->left;
    }
    return current;
}

Node *AVLTree::deleteNode(Node *node, int key, bool &success)
{
    if (!node)
    {
        success = false;
        return node;
    }
    if (key < node->id)
    {
        node->left = deleteNode(node->left, key, success);
    } else if (key > node->id)
    {
        node->right = deleteNode(node->right, key, success);
    } else
    {
        success = true;
        if (!node->left || !node->right)
        {
            Node *temp = node->left ? node->left : node->right;
            if (!temp)
            {
                temp = node;
                node = nullptr;
            } else
            {
                *node = *temp;
            }
            delete temp;
        } else
        {
            Node *temp = findMin(node->right);
            node->id = temp->id;
            node->contact = temp->contact;
            node->right = deleteNode(node->right, temp->id, success);
        }
    }


    updateHeight(node);
    int bf = balanceFactor(node);

    if (bf > 1 && balanceFactor(node->left) >= 0)
    {
        return rightRotate(node);
    }

    if (bf > 1 && balanceFactor(node->left) < 0)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (bf < -1 && balanceFactor(node->right) <= 0)
    {
        return leftRotate(node);
    }

    if (bf < -1 && balanceFactor(node->right) > 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node *AVLTree::search(Node *node, int key) const
{
    if (!node)
    {
        return nullptr;
    }
    if (key == node->id)
    {
        return node;
    } else if (key < node->id)
    {
        return search(node->left, key);
    } else
    {
        return search(node->right, key);
    }
}

void AVLTree::inorder(Node *node) const
{
    if (!node)
    {
        return;
    }
    inorder(node->left);
    cout << "ID: " << node->id << ", Name: " << node->contact.name << ", Phone: " << node->contact.phone
         << ", Email: " << node->contact.email << endl;
    inorder(node->right);
}

void AVLTree::printTree(Node *node, string indent, bool last) const
{
    if (node)
    {
        cout << indent;
        if (last)
        {
            cout << "--";
            indent += "  ";
        } else
        {
            cout << "|--";
            indent += "| ";
        }

        cout << node->id << endl;

        printTree(node->left, indent, false);
        printTree(node->right, indent, true);
    }
}

void AVLTree::clearTree(Node *node)
{
    if (!node)
    {
        return;
    }
    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

//int main()
//{
//    AVLTree addressBook;
//
//    string choice;
//
//    while (true)
//    {
//        cout << "\nAddress Book Application\n";
//        cout << "------------------------\n";
//        cout << "1. Add New Contact\n";
//        cout << "2. Search for Contact\n";
//        cout << "3. Delete Contact (Optional)\n";
//        cout << "4. List All Contacts (Sorted by ID)\n";
//        cout << "5. Display Current Tree Structure\n";
//        cout << "6. Exit\n";
//        cout << "------------------------\n";
//        cout << "Enter operation (1-6): ";
//
//        cin >> choice;
//        cin.ignore(1, '\n');
//
//        while (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5" && choice != "6")
//        {
//            cerr << "Please enter a valid choice.\n";
//            cout << "------------------------\n";
//            cout << "1. Add New Contact\n";
//            cout << "2. Search for Contact\n";
//            cout << "3. Delete Contact (Optional)\n";
//            cout << "4. List All Contacts (Sorted by ID)\n";
//            cout << "5. Display Current Tree Structure\n";
//            cout << "------------------------\n";
//            cout << "Enter operation (1-6): ";
//
//            cin >> choice;
//        }
//
//        if (choice == "1")
//        {
//            int id;
//            Contact contact;
//
//            cout << "Enter unique ID (integer): ";
//            cin >> id;
//            cin.ignore(1, '\n');
//
//            cout << "Enter name: ";
//            getline(cin, contact.name);
//            cin.ignore(0, '\n');
//
//
//            cout << "Enter phone number: ";
//            getline(cin, contact.phone);
//            cin.ignore(0, '\n');
//
//
//            cout << "Enter email address: ";
//            getline(cin, contact.email);
//            cin.ignore(0, '\n');
//
//
//            if (addressBook.insert(id, contact))
//            {
//                cout << "Contact added successfully." << endl;
//            } else
//            {
//                cerr << "Error: Contact with ID " << id << " already exists." << endl;
//            }
//        } else if (choice == "2")
//        {
//            int id;
//            cout << "Enter ID to search for: ";
//            cin >> id;
//            cin.ignore(1, '\n');
//            Node *node = addressBook.search(id);
//            if (node)
//            {
//                cout << "Contact found:" << endl;
//                cout << "Name: " << node->contact.name << endl;
//                cout << "Phone: " << node->contact.phone << endl;
//                cout << "Email: " << node->contact.email << endl;
//            } else
//            {
//                cout << "Contact not found." << endl;
//            }
//        } else if (choice == "3")
//        {
//            int id;
//            cout << "Enter ID to delete: ";
//            cin >> id;
//            cin.ignore(1, '\n');
//            if (addressBook.remove(id))
//            {
//                cout << "Contact deleted successfully." << endl;
//            } else
//            {
//                cout << "Contact not found." << endl;
//            }
//        } else if (choice == "4")
//        {
//            addressBook.inorder();
//        } else if (choice == "5")
//        {
//            addressBook.printTree();
//        } else if (choice == "6")
//        {
//            break;
//        }
//    }
//}
