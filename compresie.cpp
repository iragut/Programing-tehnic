#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {
    ifstream fin("compresie.in");
    ofstream fout("compresie.out");

    int n, m, i, j, k = 1, l = 1;
    int array_length = 0, sum_first = 0, sum_second = 0;

    fin >> n;
    vector<int> first_array(n);
    for (i = 0; i < n; i++) {
        fin >> first_array[i];
        sum_first += first_array[i];
    }

    fin >> m;
    vector<int> second_array(m);
    for (i = 0; i < m; i++) {
        fin >> second_array[i];
        sum_second += second_array[i];
    }

    // We iterate through the arrays and compress them element by element
    i = 0; j = 0;
    while (i < n && j < m) {
        if (first_array[i] == -1) {
            i++;
        } else  if (second_array[j] == -1) {
            j++;
        } else if (first_array[i] == second_array[j]) {
            array_length++;
            i++; j++; k++; l++;
        } else if (first_array[i] > second_array[j]) {
            second_array[j] += second_array[k];
            second_array[k] = -1;
            k++;
        } else if (first_array[i] < second_array[j]) {
            first_array[i] += first_array[l];
            first_array[l] = -1;
            l++;
        }
    }

    // If the sum of both arrays is different, we cant compress them
    if (sum_first != sum_second) {
        array_length = -1;
    }

    fout << array_length << "\n";

    fin.close();
    fout.close();
    return 0;
}
