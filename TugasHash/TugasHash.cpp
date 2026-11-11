#include <iostream>
#include <string>
#include <limits>
using namespace std;

const int SIZE = 10;

enum State { EMPTY, OCCUPIED, DELETED };

struct Slot {
    long long nim;
    string nama;
    State state;
    Slot() : nim(0), nama(""), state(EMPTY) {}
};

class HashTable {
private:
    Slot table[SIZE];

    int hash1(long long key) const {
        return key % SIZE;
    }

    int hash2(long long key) const {
        return 7 - (key % 7);
    }

    int probe(long long key, int i) const {
        return (hash1(key) + i * hash2(key)) % SIZE;
    }

public:
    bool insert(long long nim, const string &nama) {
        int firstDeleted = -1;
        for (int i = 0; i < SIZE; i++) {
            int idx = probe(nim, i);
            if (table[idx].state == OCCUPIED) {
                if (table[idx].nim == nim) {
                    table[idx].nama = nama;
                    cout << "NIM sudah ada, nama diperbarui di indeks " << idx << endl;
                    return true;
                }
            } else if (table[idx].state == DELETED) {
                if (firstDeleted == -1) firstDeleted = idx;
            } else {
                int target = (firstDeleted != -1) ? firstDeleted : idx;
                table[target].nim = nim;
                table[target].nama = nama;
                table[target].state = OCCUPIED;
                cout << "Data disimpan di indeks " << target << " (percobaan ke-" << i + 1 << ")" << endl;
                return true;
            }
        }
        if (firstDeleted != -1) {
            table[firstDeleted].nim = nim;
            table[firstDeleted].nama = nama;
            table[firstDeleted].state = OCCUPIED;
            cout << "Data disimpan di indeks " << firstDeleted << endl;
            return true;
        }
        cout << "Hash table penuh atau slot tidak dapat dijangkau" << endl;
        return false;
    }

    int search(long long nim) const {
        for (int i = 0; i < SIZE; i++) {
            int idx = probe(nim, i);
            if (table[idx].state == EMPTY) return -1;
            if (table[idx].state == OCCUPIED && table[idx].nim == nim) return idx;
        }
        return -1;
    }

    bool remove(long long nim) {
        int idx = search(nim);
        if (idx == -1) return false;
        table[idx].state = DELETED;
        table[idx].nim = 0;
        table[idx].nama = "";
        return true;
    }

    string getNama(int idx) const {
        return table[idx].nama;
    }

    void display() const {
        cout << "\n=== Isi Hash Table ===" << endl;
        for (int i = 0; i < SIZE; i++) {
            cout << "[" << i << "] ";
            if (table[i].state == OCCUPIED)
                cout << table[i].nim << " - " << table[i].nama;
            else if (table[i].state == DELETED)
                cout << "(dihapus)";
            else
                cout << "(kosong)";
            cout << endl;
        }
    }
};

int main() {
    HashTable ht;
    int pilihan;

    do {
        cout << "\n1. Insert" << endl;
        cout << "2. Search" << endl;
        cout << "3. Remove" << endl;
        cout << "4. Tampilkan" << endl;
        cout << "0. Selesai" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        if (pilihan == 1) {
            long long nim;
            string nama;
            cout << "NIM  : ";
            cin >> nim;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Nama : ";
            getline(cin, nama);
            ht.insert(nim, nama);
        } else if (pilihan == 2) {
            long long nim;
            cout << "NIM yang dicari: ";
            cin >> nim;
            int idx = ht.search(nim);
            if (idx != -1)
                cout << "Ditemukan di indeks " << idx << ": " << ht.getNama(idx) << endl;
            else
                cout << "Data tidak ditemukan" << endl;
        } else if (pilihan == 3) {
            long long nim;
            cout << "NIM yang dihapus: ";
            cin >> nim;
            if (ht.remove(nim))
                cout << "Data berhasil dihapus" << endl;
            else
                cout << "Data tidak ditemukan" << endl;
        } else if (pilihan == 4) {
            ht.display();
        }
    } while (pilihan != 0);

    ht.display();
    return 0;
}