#include <iostream>
#include <string>
using namespace std;

void tampil(string data[], int n){
    cout << "   [ ";
    for (int i = 0; i < n; i++){
        cout << data[i] << " ";
    }
    cout << "]" << endl;
}

void insertionSort(string data[], int n){
    for (int i = 1; i < n; i++){
        string key = data[i];
        int j = i - 1;

        cout << "\nLangkah " << i << ": key = " << key << endl;

        // geser elemen yang lebih besar dari key ke kanan
        while (j >= 0 && data[j] > key){
            cout << "   geser " << data[j] << " dari indeks " << j
                 << " ke indeks " << j + 1 << endl;
            data[j + 1] = data[j];
            j--;
        }

        // sisipkan key pada posisi yang tepat
        data[j + 1] = key;
        cout << "   sisipkan " << key << " di indeks " << j + 1 << endl;

        tampil(data, n);
    }
}

int main(){
    int n;
    string data[100];

    cout << "Masukkan jumlah kata: ";
    cin >> n;

    cout << "Masukkan kata-kata: \n";
    for (int i = 0; i < n; i++){
        cin >> data[i];
    }

    cout << "\nData awal:" << endl;
    tampil(data, n);

    insertionSort(data, n);

    cout << "\nHasil insertion sort: ";
    for (int i = 0; i < n; i++){
        cout << data[i] << " ";
    }
    cout << endl;

    return 0;
}