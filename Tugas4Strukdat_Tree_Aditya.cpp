#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* kiri;
    Node* kanan;
};

void tambah(Node*& root, int data) {
    if (root == NULL) {
        root = new Node();
        root->data = data;
        root->kiri = NULL;
        root->kanan = NULL;

        return;
    }

    if (data < root->data) {
        tambah (root->kiri, data);
    }

    if (data > root->data) {
        tambah (root->kanan, data);
    }

    return;
}

void preOrder(Node* root) {
    if (root == NULL) {
        return;
    }

    cout << root->data << " ";
    preOrder(root->kiri);
    preOrder(root->kanan);
}

void inOrder(Node* root) {
    if (root == NULL) {
        return;
    }

    inOrder(root->kiri);
    cout << root->data << " ";
    inOrder(root->kanan);
}

void postOrder(Node* root) {
    if (root == NULL) {
        return;
    }

    postOrder(root->kiri);
    postOrder(root->kanan);
    cout << root->data << " ";
}

void hapus(Node* root) {
    if (root == NULL) {
        return;
    }

    hapus(root->kiri);
    hapus(root->kanan);
    delete(root);
}

int main() {
    Node* root = NULL;
    int angka;

    cout << "Masukkan angka, jika ingin stop memasukkan angka, ketik 0 : \n";
    cin >> angka;

    while (angka != 0) {
        tambah(root, angka);
        cin >> angka;
    }

    cout << "Pre-order  : ";
    preOrder(root);
    cout << endl;

    cout << "In-order   : ";
    inOrder(root);
    cout << endl;

    cout << "Post-order : ";
    postOrder(root);
    cout << endl;

    hapus(root);

    return 0;
}