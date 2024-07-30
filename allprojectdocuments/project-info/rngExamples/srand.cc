#include <iostream>
#include <string>
#include <stdlib.h> // srand/rand
#include <sys/types.h> // getpid
#include <unistd.h>
using namespace std;

void createRandomRow(int*& row, int size) {
    row = new int[size];
    for (int i = 0; i < size; ++i) row[i] = rand()%100;
} // createRandomRow


int main(int argc, char* argv[]) {
    int seed = getpid();
    if ( argc == 2 ) seed = stoi(string{argv[1]});
    srand(seed); // only seed the random number generator once!

    int *row = nullptr;
    int size = rand() % 5 + 5;
    createRandomRow(row, size);
    cout << "row: ";
    for (int i = 0; i < size; ++i) cout << row[i] << ' ';
    cout << endl;
    delete [] row;
} // main
