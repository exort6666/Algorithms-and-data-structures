#include <iostream>
#include <string>
#include <stack>

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* newNode(int data) {
    Node* node = new Node;
    node->data = data;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

void preOrderRecursive(Node* node) {
    if (node == nullptr)
        return;

    std::cout << node->data << " ";
    preOrderRecursive(node->left);
    preOrderRecursive(node->right);
}

void inOrderRecursive(Node* node) {
    if (node == nullptr)
        return;

    inOrderRecursive(node->left);
    std::cout << node->data << " ";
    inOrderRecursive(node->right);
}

void postOrderRecursive(Node* node) {
    if (node == nullptr)
        return;

    postOrderRecursive(node->left);
    postOrderRecursive(node->right);
    std::cout << node->data << " ";
}

void preOrderNonRecursive(Node* node) {
    if (node == nullptr)
        return;

    std::stack<Node*> stack;
    stack.push(node);

    while (!stack.empty()) {
        Node* current = stack.top();
        stack.pop();

        std::cout << current->data << " ";

        if (current->right)
            stack.push(current->right);

        if (current->left)
            stack.push(current->left);
    }
}

int findIndex(const std::string& str, int si, int ei) {
    if (si > ei)
        return -1;

    std::stack<char> s;

    for (int i = si; i <= ei; i++) {
        if (str[i] == '(')
            s.push(str[i]);
        else if (str[i] == ')') {
            if (s.top() == '(') {
                s.pop();
                if (s.empty())
                    return i;
            }
        }
    }

    return -1;
}

Node* treeFromString(const std::string& str, int si, int ei) {
    if (si > ei)
        return nullptr;

    int num = 0;
    while (si <= ei && str[si] >= '0' && str[si] <= '9') {
        num *= 10;
        num += (str[si] - '0');
        si++;
    }

    Node* root = newNode(num);
    int index = -1;

    if (si <= ei && str[si] == '(')
        index = findIndex(str, si, ei);

    if (index != -1) {
        root->left = treeFromString(str, si + 1, index - 1);
        root->right = treeFromString(str, index + 2, ei - 1);
    }

    return root;
}

void main() {

    std::string str = "8(3(1)(6(4)(7)))(10(14)(13))";
    Node* root = treeFromString(str, 0, str.length() - 1);

    //Рекурсивный прямой
    preOrderRecursive(root);
    std::cout << std::endl;

    //Рекурсивный центральный
    inOrderRecursive(root);
    std::cout << std::endl;

    //Рекурсивный концевой
    postOrderRecursive(root);
    std::cout << std::endl;

    //Не рекурсивный прямой
    preOrderNonRecursive(root);
    std::cout << std::endl;
}
