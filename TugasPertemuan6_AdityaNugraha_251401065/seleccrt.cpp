#include <iostream>
using namespace std;

int main() {
int data[] = {5, 2, 4, 1, 3};
int n = 5;

for (int i= 0; i < n - 1; i++) {
int minIndex = i;

for (int j= i+1; j <n; j++) {
if (data[j] < data[minIndex]) {
minIndex = j;

}
swap (data[i], data[minIndex]);

}
}


cout << "Hasil Selection Sort : ";
for (int i=0; i < n; i++) {
cout << data[i] << " ";}
}



