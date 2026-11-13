
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

//queue
struct NodeQ {
    string nama;
    NodeQ* next;
};
NodeQ* depan = NULL;
NodeQ* belakang = NULL;

void enqueue(string nama) {
    NodeQ* baru = new NodeQ;
    baru->nama = nama;
    baru->next = NULL;
    if (depan == NULL) depan = belakang = baru;
    else { belakang->next = baru; belakang = baru; }
}

void dequeue() {
    if (depan == NULL) { cout << "Antrean kosong.\n"; return; }
    NodeQ* hapus = depan;
    cout << hapus->nama << " dilayani dan meminjam buku.\n";
    depan = depan->next;
    if (depan == NULL) belakang = NULL;
    delete hapus;
}

void tampilAntrean() {
    if (depan == NULL) { cout << "Antrean kosong.\n"; return; }
    cout << "Depan -> ";
    for (NodeQ* p = depan; p != NULL; p = p->next) cout << p->nama << " ";
    cout << "<- Belakang\n";
}

// stack
int riwayat[100];
int top = -1;

void push(int idBuku) {
    if (top == 99) { cout << "Stack penuh.\n"; return; }
    top++;
    riwayat[top] = idBuku;
}

void pop() {
    if (top == -1) { cout << "Riwayat kosong.\n"; return; }
    cout << "Buku " << riwayat[top] << " dihapus dari riwayat.\n";
    top--;
}

void tampilRiwayat() {
    if (top == -1) { cout << "Riwayat kosong.\n"; return; }
    cout << "Terbaru -> terlama: ";
    for (int i = top; i >= 0; i--) cout << riwayat[i] << " ";
    cout << endl;
}

//BST
struct NodeT {
    int id;
    NodeT* kiri;
    NodeT* kanan;
};
NodeT* root = NULL;

NodeT* insert(NodeT* n, int id) {
    if (n == NULL) {
        NodeT* baru = new NodeT;
        baru->id = id;
        baru->kiri = baru->kanan = NULL;
        return baru;
    }
    if (id < n->id) n->kiri = insert(n->kiri, id);
    else if (id > n->id) n->kanan = insert(n->kanan, id);
    return n;
}

bool cari(int id) {
    NodeT* p = root;
    while (p != NULL) {
        if (id == p->id) return true;
        if (id < p->id) p = p->kiri;
        else p = p->kanan;
    }
    return false;
}

void preOrder(NodeT* n) {
    if (n == NULL) return;
    cout << n->id << " ";
    preOrder(n->kiri);
    preOrder(n->kanan);
}
void inOrder(NodeT* n) {
    if (n == NULL) return;
    inOrder(n->kiri);
    cout << n->id << " ";
    inOrder(n->kanan);
}
void postOrder(NodeT* n) {
    if (n == NULL) return;
    postOrder(n->kiri);
    postOrder(n->kanan);
    cout << n->id << " ";
}

// display
void bersihkanLayar() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

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

//
void menuEnqueue() {
    string nama;
    do {
        bersihkanLayar();
        cout << "=== TAMBAH ANTREAN PEMINJAM ===\n\n";
        cout << "Nama mahasiswa : "; cin >> nama;
        cin.ignore(1000, '\n');

        bersihkanLayar();
        enqueue(nama);
        cout << nama << " masuk antrean.\n\n";
        tampilAntrean();
    } while (tanyaUlang("tambah"));
}

void menuDequeue() {
    do {
        bersihkanLayar();
        dequeue();
        cout << "\n";
        tampilAntrean();
    } while (tanyaUlang("layani"));
}

void menuTampilAntrean() {
    bersihkanLayar();
    cout << "=== ANTREAN PEMINJAMAN ===\n\n";
    tampilAntrean();
    tungguEnter();
}

void menuPush() {
    int id;
    do {
        bersihkanLayar();
        cout << "=== PENGEMBALIAN BUKU ===\n\n";
        cout << "ID buku dikembalikan : "; cin >> id;
        cin.ignore(1000, '\n');

        bersihkanLayar();
        push(id);
        cout << "Pengembalian buku " << id << " dicatat.\n\n";
        tampilRiwayat();
    } while (tanyaUlang("catat"));
}

void menuPop() {
    do {
        bersihkanLayar();
        pop();
        cout << "\n";
        tampilRiwayat();
    } while (tanyaUlang("hapus"));
}

void menuTampilRiwayat() {
    bersihkanLayar();
    cout << "=== RIWAYAT PENGEMBALIAN ===\n\n";
    tampilRiwayat();
    tungguEnter();
}

void menuTambahBuku() {
    int id;
    do {
        bersihkanLayar();
        cout << "=== TAMBAH ID BUKU (BST) ===\n\n";
        cout << "ID buku : "; cin >> id;
        cin.ignore(1000, '\n');

        bersihkanLayar();
        root = insert(root, id);
        cout << "ID " << id << " telah ditambahkan ke BST.\n";
    } while (tanyaUlang("tambah"));
}

void menuCariBuku() {
    int id;
    do {
        bersihkanLayar();
        cout << "=== CARI ID BUKU (BST) ===\n\n";
        cout << "ID dicari : "; cin >> id;
        cin.ignore(1000, '\n');

        bersihkanLayar();
        if (cari(id)) cout << "ID " << id << " ditemukan.\n";
        else cout << "ID " << id << " tidak ditemukan.\n";
    } while (tanyaUlang("cari"));
}

void menuTraversal() {
    bersihkanLayar();
    cout << "=== ISI BST ===\n\n";
    if (root == NULL) cout << "BST kosong.\n";
    else {
        cout << "Pre-Order  : "; preOrder(root);  cout << endl;
        cout << "In-Order   : "; inOrder(root);   cout << endl;
        cout << "Post-Order : "; postOrder(root); cout << endl;
    }
    tungguEnter();
}

int main() {
    string pilih;

    while (true) {
        bersihkanLayar();
        cout << "=== PERPUSTAKAAN ===\n\n";
        cout << "1. Tambah antrean peminjam\n";
        cout << "2. Layani antrean terdepan\n";
        cout << "3. Tampilkan antrean\n";
        cout << "4. Catat pengembalian buku\n";
        cout << "5. Hapus riwayat terakhir\n";
        cout << "6. Tampilkan riwayat pengembalian\n";
        cout << "7. Tambah ID buku (BST)\n";
        cout << "8. Cari ID buku (BST)\n";
        cout << "9. Tampilkan BST (Pre/In/Post-Order)\n";
        cout << "0. Keluar\n\n";
        cout << "Pilihan: ";
        getline(cin, pilih);

        if (pilih == "0") break;
        else if (pilih == "1") menuEnqueue();
        else if (pilih == "2") menuDequeue();
        else if (pilih == "3") menuTampilAntrean();
        else if (pilih == "4") menuPush();
        else if (pilih == "5") menuPop();
        else if (pilih == "6") menuTampilRiwayat();
        else if (pilih == "7") menuTambahBuku();
        else if (pilih == "8") menuCariBuku();
        else if (pilih == "9") menuTraversal();
    }
    return 0;
}
