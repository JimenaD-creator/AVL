#include "AVL.h"
#include <string>
#include <iostream>
using namespace std;

User::User(int id, string name, string email, string creationDate): id(id), name(name), email(email), creationDate(creationDate) {}

Node::Node(User *user): user(user), left(nullptr), right(nullptr), height(1) {}

AVLTree::AVLTree() : root(nullptr) {}

int AVLTree::height(Node *node) {
    return node ? node->height : 0;
};

int AVLTree::getBalance(Node *node) {
    return node ? height(node->left) - height(node->right) : 0;
}

Node *AVLTree::rightRotate(Node *y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) +1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node *AVLTree::leftRotate(Node *x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) +1;
    y->height = max(height(y->left), height(y->right)) +1;

    return y;
}
// Rotación doble izquierda-derecha
Node* AVLTree::leftRightRotate(Node* node) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
}

// Rotación doble derecha-izquierda
Node* AVLTree::rightLeftRotate(Node* node) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
}

Node* AVLTree::insert(Node *node, User *user) {
    if (!node) return new Node(user);

    if (user->id < node->user->id) {
        node->left = insert(node->left, user);
    } else if (user->id > node->user->id) {
        node->right = insert(node->right, user);
    } else {
        return node;  // No se permiten IDs duplicados
    }

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    // Desbalance Izquierda-Izquierda
    if (balance > 1 && user->id < node->left->user->id) {
        return rightRotate(node);
    }

    // Desbalance Derecha-Derecha
    if (balance < -1 && user->id > node->right->user->id) {
        return leftRotate(node);
    }

    // Desbalance Izquierda-Derecha
    if (balance > 1 && user->id > node->left->user->id) {
        return leftRightRotate(node);
    }

    // Desbalance Derecha-Izquierda
    if (balance < -1 && user->id < node->right->user->id) {
        return rightLeftRotate(node);
    }

    return node;
}
Node* AVLTree::minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

Node* AVLTree::remove(Node* node, int id) {
    if (!node) return node;

    if (id < node->user->id) {
        node->left = remove(node->left, id);
    } else if (id > node->user->id) {
        node->right = remove(node->right, id);
    } else {
        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;
            if (!temp) {
                temp = node;
                node = nullptr;
            } else {
                *node = *temp;
            }
            delete temp;
        } else {
            Node* temp = minValueNode(node->right);
            node->user = temp->user;
            node->right = remove(node->right, temp->user->id);
        }
    }

    if (!node) return node;

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && getBalance(node->left) >= 0) {
        return rightRotate(node);
    }

    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && getBalance(node->right) <= 0) {
        return leftRotate(node);
    }

    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Función para buscar un usuario en el árbol AVL por ID
User* AVLTree::search(Node* node, int id) {
    if (!node)
        return nullptr;

    if (node->user->id == id)
        return node->user;

    if (id < node->user->id)
        return search(node->left, id);

    return search(node->right, id);
}

// Función para recorrer el árbol en orden y mostrar los usuarios
void AVLTree::inorder(Node* root) {
    if (!root)
        return;

    inorder(root->left);
    std::cout << "ID: " << root->user->id << ", Nombre: " << root->user->name
         << ", Email: " << root->user->email
         << ", Fecha de creacion: " << root->user->creationDate << endl;
    inorder(root->right);
}
void AVLTree::inOrderTraversal() {
    inOrderTraversal(root);
}

void AVLTree::inOrderTraversal(Node* node) {
    if (node) {
        inOrderTraversal(node->left);
        cout << "ID: " << node->user->id << ", Nombre: " << node->user->name
             << ", Email: " << node->user->email
             << ", Fecha de creacion: " << node->user->creationDate << endl;
        inOrderTraversal(node->right);
    }
}

void AVLTree::preOrderTraversal() {
    preOrderTraversal(root);
}

void AVLTree::preOrderTraversal(Node* node) {
    if (node) {
        cout << "ID: " << node->user->id << ", Nombre: " << node->user->name << endl;
        preOrderTraversal(node->left);
        preOrderTraversal(node->right);
    }
}

void AVLTree::postOrderTraversal() {
    postOrderTraversal(root);
}

void AVLTree::postOrderTraversal(Node* node) {
    if (node) {
        postOrderTraversal(node->left);
        postOrderTraversal(node->right);
        cout << "ID: " << node->user->id << ", Nombre: " << node->user->name << endl;
    }
}


