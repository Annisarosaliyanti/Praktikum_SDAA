#include <iostream>
using namespace std;

void hanoi(int n, char asal, char tujuan, char sementara) {
    if (n == 1) {
        cout << "Pindahkan baskom 1 dari menara " << asal << " ke menara " << tujuan << endl;
        return;
    }

    hanoi(n - 1, asal, sementara, tujuan);
    cout << "Pindahkan baskom" << n << " dari menara " << asal << " ke menara " << tujuan << endl;
    hanoi(n - 1, sementara, tujuan, asal);
}

int main() {
    int n = 3; 
    hanoi(n, 'A', 'C', 'B');  
    return 0;
}