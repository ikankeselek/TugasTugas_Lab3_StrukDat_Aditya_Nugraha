
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

const int N = 6;
const int INF = 9999;
char nama[N] = {'A', 'B', 'C', 'D', 'E', 'F'};
int adj[N][N];          
bool visited[N];

void tambahSisi(char a, char b, int jarak) {
    adj[a - 'A'][b - 'A'] = jarak;
    adj[b - 'A'][a - 'A'] = jarak;   
}

void tampilMatrix() {
    cout << "  ";
    for (int j = 0; j < N; j++) cout << nama[j] << " ";
    cout << endl;
    for (int i = 0; i < N; i++) {
        cout << nama[i] << " ";
        for (int j = 0; j < N; j++) cout << adj[i][j] << " ";
        cout << endl;
    }
}

void bfs(int mulai) {
    int antrean[N];
    int depan = 0, belakang = 0;
    for (int i = 0; i < N; i++) visited[i] = false;

    visited[mulai] = true;
    antrean[belakang++] = mulai;
    while (depan < belakang) {
        int u = antrean[depan++];
        cout << nama[u] << " ";
        for (int v = 0; v < N; v++) {
            if (adj[u][v] != 0 && !visited[v]) {
                visited[v] = true;
                antrean[belakang++] = v;
            }
        }
    }
    cout << endl;
}

void dfs(int u) {
    visited[u] = true;
    cout << nama[u] << " ";
    for (int v = 0; v < N; v++)
        if (adj[u][v] != 0 && !visited[v]) dfs(v);
}

void dijkstra(int awal, int tujuan) {
    int jarak[N], asal[N];
    bool selesai[N];
    for (int i = 0; i < N; i++) {
        jarak[i] = INF;
        asal[i] = -1;
        selesai[i] = false;
    }
    jarak[awal] = 0;

    for (int k = 0; k < N; k++) {

        int u = -1;
        for (int i = 0; i < N; i++)
            if (!selesai[i] && (u == -1 || jarak[i] < jarak[u])) u = i;
        selesai[u] = true;


        for (int v = 0; v < N; v++) {
            if (adj[u][v] != 0 && jarak[u] + adj[u][v] < jarak[v]) {
                jarak[v] = jarak[u] + adj[u][v];
                asal[v] = u;
            }
        }
    }

    if (jarak[tujuan] == INF) { cout << "Tidak ada rute.\n"; return; }


    int rute[N], n = 0;
    for (int v = tujuan; v != -1; v = asal[v]) rute[n++] = v;

    cout << "Rute        : ";
    for (int i = n - 1; i >= 0; i--) {
        cout << nama[rute[i]];
        if (i > 0) cout << " -> ";
    }
    cout << "\nTotal jarak : " << jarak[tujuan] << endl;
}

// dispaly
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

// baca satu huruf vertex
char bacaVertex(string teks) {
    char c;
    cout << teks;
    cin >> c;
    if (c >= 'a' && c <= 'z') c = c - 32;
    return c;
}

bool vertexValid(char c) {
    return c >= 'A' && c <= 'F';
}

// menu
void menuMatrix() {
    bersihkanLayar();
    cout << "=== ADJACENCY MATRIX ===\n\n";
    tampilMatrix();
    tungguEnter();
}

void menuBFS() {
    do {
        bersihkanLayar();
        cout << "=== BFS ===\n\n";
        char a = bacaVertex("Vertex awal (A-F) : ");
        cin.ignore(1000, '\n');

        bersihkanLayar();
        if (!vertexValid(a)) cout << "Vertex tidak valid.\n";
        else {
            cout << "BFS dari " << a << " : ";
            bfs(a - 'A');
        }
    } while (tanyaUlang("jalankan BFS"));
}

void menuDFS() {
    do {
        bersihkanLayar();
        cout << "=== DFS ===\n\n";
        char a = bacaVertex("Vertex awal (A-F) : ");
        cin.ignore(1000, '\n');

        bersihkanLayar();
        if (!vertexValid(a)) cout << "Vertex tidak valid.\n";
        else {
            for (int i = 0; i < N; i++) visited[i] = false;
            cout << "DFS dari " << a << " : ";
            dfs(a - 'A');
            cout << endl;
        }
    } while (tanyaUlang("jalankan DFS"));
}

void menuDijkstra() {
    do {
        bersihkanLayar();
        cout << "=== DIJKSTRA ===\n\n";
        char a = bacaVertex("Vertex awal   (A-F) : ");
        char b = bacaVertex("Vertex tujuan (A-F) : ");
        cin.ignore(1000, '\n');

        bersihkanLayar();
        if (!vertexValid(a) || !vertexValid(b)) cout << "Vertex tidak valid.\n";
        else {
            cout << "Rute terpendek " << a << " ke " << b << "\n\n";
            dijkstra(a - 'A', b - 'A');
        }
    } while (tanyaUlang("cari rute"));
}

int main() {
    tambahSisi('A', 'B', 4);
    tambahSisi('A', 'C', 2);
    tambahSisi('B', 'C', 1);
    tambahSisi('B', 'D', 5);
    tambahSisi('B', 'E', 3);
    tambahSisi('C', 'D', 8);
    tambahSisi('C', 'E', 6);
    tambahSisi('D', 'E', 2);
    tambahSisi('D', 'F', 4);
    tambahSisi('E', 'F', 3);

    string pilih;
    while (true) {
        bersihkanLayar();
        cout << "=== RUTE KAMPUS ===\n\n";
        cout << "1. Tampilkan Adjacency Matrix\n";
        cout << "2. BFS\n";
        cout << "3. DFS\n";
        cout << "4. Dijkstra (rute terpendek)\n";
        cout << "0. Keluar\n\n";
        cout << "Pilihan: ";
        getline(cin, pilih);

        if (pilih == "0") break;
        else if (pilih == "1") menuMatrix();
        else if (pilih == "2") menuBFS();
        else if (pilih == "3") menuDFS();
        else if (pilih == "4") menuDijkstra();
    }
    return 0;
}
