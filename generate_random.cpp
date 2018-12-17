#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Error, specify m and n\n";
        return 1;
    }

    int m = stoi(argv[1]);
    int n = stoi(argv[2]);

    cout << m << "\n" << n << "\n";

    srand(time(0));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << (rand() & 1) << " ";
        }
        cout << "\n";
    }
}
