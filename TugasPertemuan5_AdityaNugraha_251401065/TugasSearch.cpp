#include <iostream>
using namespace std;

int binarySearch(int data[], int n, int target){
    int l = 0, r = n-1;

    while (l <= r){
        int mid = l + (r-l)/2;

        if (data[mid] == target) return mid;
        else if (data[mid] < target) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}

int main(){
    int n;

    cout << "Masukkan jumlah data nilai mahasiswa: ";
    cin >> n;

    int data[100];

    cout << "Masukkan nilai (urut ascending):" << endl;
    for (int i = 0; i < n; i++){
        cout << "Nilai ke-" << i+1 << ": ";
        cin >> data[i];
    }

    int target;
    cout << "Masukkan nilai yang ingin dicari: ";
    cin >> target;

    int hasil = binarySearch(data, n, target);

    if (hasil != -1){
        cout << "Data ditemukan pada indeks: " << hasil << endl;
    }else{
        cout << "Data tidak ditemukan" << endl;
    }

    return 0;
}