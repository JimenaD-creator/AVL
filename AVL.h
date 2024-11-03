#ifndef USERAVL_H
#define USERAVL_H
#include <string>
using namespace std;



class User {
public:
    int id;
    string name;
    string email;
    string creationDate;

    User(int id, string name, string email, string creationDate);
};


class Node {
public:
    User* user;
    Node* left;
    Node* right;
    int height;

    Node(User* user);
};

class AVLTree {
public:
    Node* root;

    AVLTree(); // Constructor del árbol AVL

    int height(Node* node);
    int getBalance(Node* node);
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
    Node* insert(Node* node, User* user);
    Node* leftRightRotate(Node* node);
    Node* rightLeftRotate(Node* node);
    Node* remove(Node* node, int id); // Eliminar un nodo por ID
    User* search(Node* node, int id);
    void inorder(Node* node);
    void inOrderTraversal(); // Recorrido In-order
    void preOrderTraversal(); // Recorrido Pre-order
    void postOrderTraversal(); // Recorrido Post-order

private:
    void inOrderTraversal(Node* node);
    void preOrderTraversal(Node* node);
    void postOrderTraversal(Node* node);
    Node* minValueNode(Node* node); // Encuentra el nodo con el valor mínimo
};




#endif //USERAVL_H

