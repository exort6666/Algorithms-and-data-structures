#include <iostream>
#include <string>

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    Node* root;
    //Помещаем элемент через рекурсию
    Node* insertRecursive(Node* node, int value) {
        if (node == nullptr ) {
            return new Node(value);
        }
        // если значение меньше,то нужно поместить в левую ветвь,если больше в правую
        if (value < node->data) {
            node->left = insertRecursive(node->left, value);
        }
        else if (value > node->data) {
            node->right = insertRecursive(node->right, value);
        }
        return node; //если уже есть такой элемент ничего не делаем
    }
    // для поиска самого левого элемента ветви
    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    //Удаляет элемент через рекурсию
    Node* removeRecursive(Node* node, int value) {
        if (node == nullptr) {
            return node;
        }
        // если не элемент вершины, то в случае больше сдвигаемся вправо, а меньше влево
        if (value < node->data) { 
            node->left = removeRecursive(node->left, value);
        }
        else if (value > node->data) {
            node->right = removeRecursive(node->right, value);
        }
        else {
            //если совпадает
            if (node->left == nullptr) { // и слева ничего нет
                Node* temp = node->right;
                delete node;
                return temp; // возвращаем правую ветвь
            }
            else if (node->right == nullptr) { // если справа ничего нет
                Node* temp = node->left;
                delete node;
                return temp; //возвращаем левую ветвь
            }
            //в случае когда обе ветви есть
            Node* temp = findMin(node->right); // находим самую левую ветвь правой ветви (минимальный элемент)
            node->data = temp->data;
            node->right = removeRecursive(node->right, temp->data); //и так сдвигаем и удаляем в правой ветви
        }

        return node;
    }
    //нахождение через рекурсию
    bool searchRecursive(Node* node, int value) {
        if (node == nullptr) { // если после сдвигов ничего не находим
            return false; // то ложь
        }

        if (value == node->data) {  
            return true;
        }
        else if (value < node->data) { // ищем в левой ветви если меньше
            return searchRecursive(node->left, value);
        }
        else { // в правой если больше
            return searchRecursive(node->right, value);
        }
    }
    //вывод дерева 
    std::string generateLinearBracketNotation(Node* node) {
        if (node == nullptr) {
            return "";
        }

        std::string result = std::to_string(node->data);

        if (node->left != nullptr || node->right != nullptr) {
            result += "(" + generateLinearBracketNotation(node->left) + ")";
            if (node->right != nullptr) {
                result += "(" + generateLinearBracketNotation(node->right) + ")";
            }
        }

        return result;
    }
public:
    BinarySearchTree() : root(nullptr) {}
    //1.Поместить элемент
    void insert(int value) {
        root = insertRecursive(root, value);
    }
    //2.Убрать элемент
    void remove(int value) {
        root = removeRecursive(root, value);
    }
    //3.Найти элемент
    bool search(int value) {
        return searchRecursive(root, value);
    }
    std::string getLinearBracketNotation() {
        return generateLinearBracketNotation(root);
    }
    //4.Получить дерево
    void printLinearBracketNotation() {
        std::cout << "Binary Search Tree (Linear Bracket Notation): " << getLinearBracketNotation() << std::endl;
    }
};


void main() {
    BinarySearchTree bst;

    std::string input;
    std::cout << "Enter Binary Search Tree in linear bracket notation: ";
    std::getline(std::cin, input);

    // Парсинг линейно-скобочной записи и вставка узлов в дерево
    for (char c : input) {
        if (isdigit(c)) {
            int value = c - '0';
            bst.insert(value);
        }
    }

    while (true) {
        std::cout << "\nMenu:\n1. Add Node\n2. Remove Node\n3. Search Node\n4. Print Linear Bracket Notation\n5. Exit\n";
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::cout << "Enter value to add: ";
            int value;
            std::cin >> value;
            bst.insert(value);
            break;
        }
        case 2: {
            std::cout << "Enter value to remove: ";
            int value;
            std::cin >> value;
            bst.remove(value);
            break;
        }
        case 3: {
            std::cout << "Enter value to search: ";
            int value;
            std::cin >> value;
            std::cout << (bst.search(value) ? "Node found" : "Node not found") << std::endl;
            break;
        }
        case 4:
            bst.printLinearBracketNotation();
            break;
        case 5:
            std::cout << "Binary Search Tree (Linear Bracket Notation): " << bst.getLinearBracketNotation() << std::endl;
            std::cout << "Exiting program." << std::endl;
        default:
            std::cout << "Invalid choice. Please enter a valid option." << std::endl;
        }
    }
}
// (5(3(1)(4))(7(6)(8)))