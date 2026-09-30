#include <iostream>
#include <string>
using namespace std;

struct Node {
    char data;
    Node* next;
};

int main(){

    string kata;
    cout << "Masukkan kata: ";
    cin >> kata;

    Node* head = nullptr;

    for (int i = 0; i < kata.length(); i++) {
        Node* baru = new Node();
        baru->data = kata[i];
        baru->next = head;
        head = baru;
    }

    cout << "Hasil dibalik: ";

    while (head != nullptr) {
        Node* temp = head;
        cout << temp->data;
        head = head->next;
        delete(temp);
    }

    cout << endl;
}