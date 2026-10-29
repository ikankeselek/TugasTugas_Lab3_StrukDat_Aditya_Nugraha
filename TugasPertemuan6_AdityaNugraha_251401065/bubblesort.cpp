#include <iostream>
using namespace std;


int main () {
int data[] = {5, 2, 4, 1, 3};
int n = 5;

for (int i= 0; i < n - 1; i++) {
for (int j=0; j < n -1 - i; j++) {
if (data[j] > data[j + 1]) {
swap(data[j], data[j + 1]);
}
}
}

cout << "Hasil Bubble Sort: ";
for (int i=0; i < n; i++) {
cout << data[i] << " ";
}
}