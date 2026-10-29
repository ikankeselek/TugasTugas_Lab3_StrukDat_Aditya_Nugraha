#include <iostream>
using namespace std;

int main() {
int data[] = {5, 2, 4, 1, 3};
int n = 5;

for (int i=1; i <n; i++) {
int key = data[i];
int j=i -1;

while (j >= 0 && data[j] > key) {
data[j+1] = data[j];
j --;

}

data[j+1] = key;

}

cout << "Hasil Insertion Sort : ";
for (int i= 0; i < n; i++) {
cout << data[i] << " ";}
}