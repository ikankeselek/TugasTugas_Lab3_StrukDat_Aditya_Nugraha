
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

// linked list
struct Mahasiswa {
    string nim;
    string nama;
    int nilai;
    Mahasiswa* next;
};
Mahasiswa* head = NULL;

// dynamic array
int* arrNilai;
int jumlah = 0;   
int kapasitas = 2;  
bool terurut = false;

void tambahKeArray(int nilai) {
    if (jumlah == kapasitas) {
        kapasitas = kapasitas * 2;
        int* baru = new int[kapasitas];
        for (int i = 0; i < jumlah; i++) baru[i] = arrNilai[i];
        delete[] arrNilai;
        arrNilai = baru;
    }
    arrNilai[jumlah] = nilai;
    jumlah++;
}

void tambahMahasiswa(string nim, string nama, int nilai) {
    Mahasiswa* baru = new Mahasiswa;
    baru->nim = nim;
    baru->nama = nama;
    baru->nilai = nilai;
    baru->next = NULL;

    if (head == NULL) head = baru;
    else {
        Mahasiswa* p = head;
        while (p->next != NULL) p = p->next;
        p->next = baru;
    }
    tambahKeArray(nilai);
    terurut = false;
}

void tampilMahasiswa() {
    if (head == NULL) { cout << "Belum ada data.\n"; return; }
    for (Mahasiswa* p = head; p != NULL; p = p->next)
        cout << p->nim << " | " << p->nama << " | " << p->nilai << endl;
}

void tampilArray() {
    for (int i = 0; i < jumlah; i++) cout << arrNilai[i] << " ";
    cout << endl;
}

// insertion sort
void insertionSort() {
    for (int i = 1; i < jumlah; i++) {
        int kunci = arrNilai[i];
        int j = i - 1;
        while (j >= 0 && arrNilai[j] > kunci) {
            arrNilai[j + 1] = arrNilai[j];
            j--;
        }
        arrNilai[j + 1] = kunci;
    }
    terurut = true;
}

// linier search
void linearSearch(string nim) {
    for (Mahasiswa* p = head; p != NULL; p = p->next) {
        if (p->nim == nim) {
            cout << "Ditemukan: " << p->nim << " | " << p->nama << " | " << p->nilai << endl;
            return;
        }
    }
    cout << "NIM " << nim << " tidak ditemukan.\n";
}

// binary search
void binarySearch(int target) {
    int low = 0, high = jumlah - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arrNilai[mid] == target) {
            cout << "Nilai " << target << " ditemukan di indeks " << mid << endl;
            cout << "Mahasiswa dengan nilai tersebut:\n";
            for (Mahasiswa* p = head; p != NULL; p = p->next)
                if (p->nilai == target)
                    cout << "- " << p->nim << " | " << p->nama << endl;
            return;
        }
        else if (arrNilai[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    cout << "Nilai " << target << " tidak ditemukan.\n";
}

// display
void bersihkanLayar() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// true jika pengguna mengetik 1, false jika hanya Enter
bool tanyaUlang(string aksi) {
    string s;
    cout << "\nKetik 1 untuk " << aksi << " lagi, Enter untuk kembali ke menu: ";
    getline(cin, s);
    return s == "1";
}

void tungguEnter() {
    string s;
    cout << "\nTekan Enter untuk kembali ke menu...";
    getline(cin, s);
}

// menu
void menuTambah() {
    string nim, nama;
    int nilai;
    do {
        bersihkanLayar();
        cout << "=== TAMBAH DATA ===\n\n";
        cout << "NIM   : "; cin >> nim;
        cout << "Nama  : "; cin >> nama;
        cout << "Nilai : "; cin >> nilai;
        cin.ignore(1000, '\n');

        bersihkanLayar();
        tambahMahasiswa(nim, nama, nilai);
        cout << "Data telah ditambahkan.\n";
    } while (tanyaUlang("tambah"));
}

void menuTampil() {
    bersihkanLayar();
    cout << "=== DATA MAHASISWA ===\n\n";
    tampilMahasiswa();
    cout << "\nArray nilai: ";
    tampilArray();
    tungguEnter();
}

void menuUrut() {
    bersihkanLayar();
    cout << "=== INSERTION SORT ===\n\n";
    if (jumlah == 0) cout << "Belum ada data.\n";
    else {
        cout << "Sebelum : "; tampilArray();
        insertionSort();
        cout << "Sesudah : "; tampilArray();
    }
    tungguEnter();
}

void menuLinear() {
    string nim;
    do {
        bersihkanLayar();
        cout << "=== LINEAR SEARCH (NIM) ===\n\n";
        cout << "NIM dicari : "; cin >> nim;
        cin.ignore(1000, '\n');

        bersihkanLayar();
        linearSearch(nim);
    } while (tanyaUlang("cari"));
}

void menuBinary() {
    if (!terurut) {
        bersihkanLayar();
        cout << "Nilai belum diurutkan. Jalankan menu Insertion Sort dulu.\n";
        tungguEnter();
        return;
    }
    int target;
    do {
        bersihkanLayar();
        cout << "=== BINARY SEARCH (NILAI) ===\n\n";
        cout << "Nilai dicari : "; cin >> target;
        cin.ignore(1000, '\n');

        bersihkanLayar();
        binarySearch(target);
    } while (tanyaUlang("cari"));
}

int main() {
    arrNilai = new int[kapasitas];
    string pilih;

    while (true) {
        bersihkanLayar();
        cout << "=== NILAI MAHASISWA ===\n\n";
        cout << "1. Tambah data\n";
        cout << "2. Tampilkan data mahasiswa\n";
        cout << "3. Urutkan nilai (Insertion Sort)\n";
        cout << "4. Cari berdasarkan NIM (Linear Search)\n";
        cout << "5. Cari nilai (Binary Search)\n";
        cout << "0. Keluar\n\n";
        cout << "Pilihan: ";
        getline(cin, pilih);

        if (pilih == "0") break;
        else if (pilih == "1") menuTambah();
        else if (pilih == "2") menuTampil();
        else if (pilih == "3") menuUrut();
        else if (pilih == "4") menuLinear();
        else if (pilih == "5") menuBinary();
    }
    return 0;
}
