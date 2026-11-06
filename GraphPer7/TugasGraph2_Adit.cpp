
#include <iostream>
#include <queue>
#include <cctype>
using namespace std;

const int N = 6;

int adj[N][N];

int toIndex(char c) {
    c = toupper(c);
    if (c < 'A' || c >= 'A' + N) return -1;
    return c - 'A';
}

void printMatrix() {
    cout << "\nAdjacency Matrix:\n   ";
    for (int i = 0; i < N; i++) cout << char('A' + i) << " ";
    cout << "\n";
    for (int i = 0; i < N; i++) {
        cout << char('A' + i) << "  ";
        for (int j = 0; j < N; j++) cout << adj[i][j] << " ";
        cout << "\n";
    }
}

void bfs(int start) {
    bool visited[N] = {false};
    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "\nUrutan kunjungan BFS: ";
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << char('A' + u) << " ";

        for (int v = 0; v < N; v++) {
            if (adj[u][v] == 1 && !visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    cout << "\n";
}

int main() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            adj[i][j] = 0;

    int m;
    cout << "=== BFS pada Graf Tidak Berarah (Vertex A-F) ===\n";
    cout << "Jumlah edge: ";
    cin >> m;

    cout << "Masukkan edge (format: vertex1 vertex2, contoh: A B)\n";
    for (int i = 0; i < m; i++) {
        char a, b;
        cout << "Edge " << i + 1 << ": ";
        cin >> a >> b;

        int u = toIndex(a), v = toIndex(b);
        if (u == -1 || v == -1) {
            cout << "  Vertex tidak valid (gunakan A-F), ulangi.\n";
            i--;
            continue;
        }
        if (u == v) {
            cout << "  Self-loop tidak diperbolehkan, ulangi.\n";
            i--;
            continue;
        }
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    printMatrix();

    char s;
    int start;
    do {
        cout << "\nVertex awal (A-F): ";
        cin >> s;
        start = toIndex(s);
        if (start == -1) cout << "Vertex tidak valid!\n";
    } while (start == -1);

    bfs(start);
    return 0;
}
