
#include <iostream>
using namespace std;

int interpolationSearch(int data[], int l, int r, int target){
    if (l > r || target < data[l] || target > data[r]) return -1;

    if (data[l] == data[r]){
        if (data[l] == target) return l;
        return -1;
    }

    int pos = l + ((target - data[l]) * (r - l)) / (data[r] - data[l]);

    if (data[pos] == target) return pos;
    else if (data[pos] < target) return interpolationSearch(data, pos + 1, r, target);
    else return interpolationSearch(data, l, pos - 1, target);
}

int main(){
    int data[] = {1, 2, 3, 4, 5, 6, 7};
    int n = 7;
    int target = 6;

    int hasil = interpolationSearch(data, 0, n - 1, target);

    if (hasil != -1){
        cout << "Data ditemukan pada indeks: " << hasil << endl;
    }else{
        cout << "Data tidak ditemukan" << endl;
    }
}
