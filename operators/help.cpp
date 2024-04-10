#include <iostream>
using namespace std;


int main(int argc, char const *argv[]) {

    int i, j;
    cin >> i >> j;

    cout << "A[(" << i+1 << "," << j << ") + (" << i-1 << "," << j << ")] + B[(" << i << "," << j+1 << ") + (" << i << "," << j-1 << ")]" << endl;

    return 0;
}
