
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cctype>
using namespace std;

const int N = 6;
const int INF = INT_MAX;

int graph[N][N];

int toIndex(char c) {
    c = toupper(c);
    if (c < 'A' || c >= 'A' + N) return -1;
    return c - 'A';
}

void addEdge(char a, char b, int w) {
    int u = toIndex(a), v = toIndex(b);
    graph[u][v] = w;
    graph[v][u] = w;
}

void initGraph() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            graph[i][j] = 0;

    addEdge('A', 'B', 4);
    addEdge('A', 'C', 2);
    addEdge('B', 'C', 1);
    addEdge('B', 'D', 5);
    addEdge('B', 'E', 3);
    addEdge('C', 'D', 8);
    addEdge('C', 'E', 6);
    addEdge('D', 'E', 2);
    addEdge('D', 'F', 4);
    addEdge('E', 'F', 3);
}

void dijkstra(int src, int dist[], int parent[]) {
    bool done[N] = {false};

    for (int i = 0; i < N; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[src] = 0;

    for (int count = 0; count < N; count++) {
        int u = -1;
        for (int i = 0; i < N; i++)
            if (!done[i] && (u == -1 || dist[i] < dist[u]))
                u = i;

        if (u == -1 || dist[u] == INF) break;
        done[u] = true;

        for (int v = 0; v < N; v++) {
            if (graph[u][v] > 0 && !done[v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }
}

vector<int> buildPath(int target, const int parent[]) {
    vector<int> path;
    for (int v = target; v != -1; v = parent[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}

void printPath(const vector<int>& path) {
    for (size_t i = 0; i < path.size(); i++) {
        cout << char('A' + path[i]);
        if (i + 1 < path.size()) cout << " -> ";
    }
}

void showFromA() {
    int dist[N], parent[N];
    dijkstra(0, dist, parent);

    cout << "\n=== Rute Terpendek dari A ke Semua Lokasi ===\n";
    for (int i = 1; i < N; i++) {
        cout << "A ke " << char('A' + i) << " : ";
        if (dist[i] == INF) {
            cout << "tidak ada rute\n";
            continue;
        }
        printPath(buildPath(i, parent));
        cout << "  | Total jarak: " << dist[i] << " km\n";
    }
}

void recommendRoute() {
    char a, b;
    cout << "\n=== Rekomendasi Rute Tercepat ===\n";
    cout << "Lokasi asal   (A-F): ";
    cin >> a;
    cout << "Lokasi tujuan (A-F): ";
    cin >> b;

    int src = toIndex(a), dst = toIndex(b);
    if (src == -1 || dst == -1) {
        cout << "Lokasi tidak valid! Gunakan huruf A-F.\n";
        return;
    }

    int dist[N], parent[N];
    dijkstra(src, dist, parent);

    cout << "\nRute tercepat " << char(toupper(a)) << " ke " << char(toupper(b)) << ":\n";
    if (dist[dst] == INF) {
        cout << "Tidak ada rute yang tersedia.\n";
        return;
    }
    cout << "Rute         : ";
    printPath(buildPath(dst, parent));
    cout << "\nTotal jarak  : " << dist[dst] << " km\n";
}

int main() {
    initGraph();

    int pilihan;
    do {
        cout << "\n===== SISTEM NAVIGASI KOTA =====\n";
        cout << "1. Rute terpendek dari A ke semua lokasi\n";
        cout << "2. Rekomendasi rute tercepat (input pengguna)\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: showFromA(); break;
            case 2: recommendRoute(); break;
            case 0: cout << "Terima kasih!\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 0);

    return 0;
}
