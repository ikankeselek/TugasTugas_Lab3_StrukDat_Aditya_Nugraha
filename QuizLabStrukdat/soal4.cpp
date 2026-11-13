
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

const int UKURAN = 20;

// status slot: 0 = kosong, 1 = terisi, 2 = sudah dihapus
long long tabelNim[UKURAN];
string tabelNama[UKURAN];
int status[UKURAN];

int hash1(long long key) { return key % 20; }
int hash2(long long key) { return 19 - (key % 19); }

void bersihkanLayar() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// cari NIM, hasilnya indeks atau -1 jika tidak ada
int cari(long long nim) {
    for (int i = 0; i < UKURAN; i++) {
        int idx = (hash1(nim) + i * hash2(nim)) % UKURAN;
        if (status[idx] == 0) return -1;                    
        if (status[idx] == 1 && tabelNim[idx] == nim) return idx;
    }
    return -1;
}

void insert(long long nim, string nama) {
    if (cari(nim) != -1) { cout << "Gagal: NIM sudah ada.\n"; return; }

    for (int i = 0; i < UKURAN; i++) {
        int idx = (hash1(nim) + i * hash2(nim)) % UKURAN;
        if (status[idx] != 1) {                
            tabelNim[idx] = nim;
            tabelNama[idx] = nama;
            status[idx] = 1;
            cout << "Data telah ditambahkan di indeks " << idx << endl;
            if (i > 0) cout << "Terjadi collision, probing " << i << " kali.\n";
            return;
        }
    }
    cout << "Gagal: tidak ada slot yang bisa dipakai.\n";
}

void search(long long nim) {
    int idx = cari(nim);
    if (idx == -1) cout << "NIM tidak ditemukan.\n";
    else cout << "Ditemukan di indeks " << idx << ": " << tabelNim[idx] << " - " << tabelNama[idx] << endl;
}

void remove(long long nim) {
    int idx = cari(nim);
    if (idx == -1) cout << "NIM tidak ditemukan.\n";
    else {
        status[idx] = 2;
        cout << "Data pada indeks " << idx << " dihapus.\n";
    }
}

void display() {
    for (int i = 0; i < UKURAN; i++) {
        cout << i << " : ";
        if (status[i] == 1) cout << tabelNim[i] << " - " << tabelNama[i];
        else if (status[i] == 2) cout << "(dihapus)";
        else cout << "-";
        cout << endl;
    }
}

int main() {
    string pilih, ulang;
    long long nim;
    string nama;

    while (true) {
        bersihkanLayar();
        cout << "=== HASH TABLE MAHASISWA ===\n\n";
        cout << "1. Insert\n";
        cout << "2. Search\n";
        cout << "3. Remove\n";
        cout << "4. Display\n";
        cout << "0. Keluar\n\n";
        cout << "Pilihan: ";
        getline(cin, pilih);

        if (pilih == "0") break;

        if (pilih == "1") {
            do {
                bersihkanLayar();
                cout << "=== INSERT ===\n\n";
                cout << "Nama : "; cin >> nama;
                cout << "NIM  : "; cin >> nim;
                cin.ignore(1000, '\n');

                bersihkanLayar();
                insert(nim, nama);
                cout << "\nKetik 1 untuk tambah lagi, Enter untuk kembali ke menu: ";
                getline(cin, ulang);
            } while (ulang == "1");
        }
        else if (pilih == "2") {
            do {
                bersihkanLayar();
                cout << "=== SEARCH ===\n\n";
                cout << "NIM : "; cin >> nim;
                cin.ignore(1000, '\n');

                bersihkanLayar();
                search(nim);
                cout << "\nKetik 1 untuk cari lagi, Enter untuk kembali ke menu: ";
                getline(cin, ulang);
            } while (ulang == "1");
        }
        else if (pilih == "3") {
            do {
                bersihkanLayar();
                cout << "=== REMOVE ===\n\n";
                cout << "NIM : "; cin >> nim;
                cin.ignore(1000, '\n');

                bersihkanLayar();
                remove(nim);
                cout << "\nKetik 1 untuk hapus lagi, Enter untuk kembali ke menu: ";
                getline(cin, ulang);
            } while (ulang == "1");
        }
        else if (pilih == "4") {
            bersihkanLayar();
            cout << "=== DISPLAY ===\n\n";
            display();
            cout << "\nTekan Enter untuk kembali ke menu...";
            getline(cin, ulang);
        }
    }
    return 0;
}
