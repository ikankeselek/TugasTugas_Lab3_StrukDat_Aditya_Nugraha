#include <iostream>
using namespace std;

int binarySearch(int data[], int l, int r, int target){
    if (l > r) return -1;

    int mid = l + (r - l)/2;

    if (data[mid] == target) return mid;
    else if (data[mid] < target) return binarySearch(data, mid + 1, r, target);
    else return binarySearch(data, l, mid - 1, target);
}

int main(){
    int data[] = {1, 2, 3, 4, 5, 6, 7};
    int n = 7;
    int target = 6;

    int hasil = binarySearch(data, 0, n-1,  target);

    if (hasil != -1){
        cout << "Data ditemukan pada indeks: " << hasil << endl;
    }else{
        cout << "Data tidak ditemukan" << endl;
    }

}