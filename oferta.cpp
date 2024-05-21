#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

/* Functiom what calculate the best price for two products */
double best_price_two_products(double first_price, double second_price) {
    if (first_price > second_price) {
        return first_price + second_price * 0.5;
    } else {
        return second_price + first_price * 0.5;
    }
}

/* Macro for calculate the minimum of three numbers */
double triple_min(double a, double b, double c) {
    return min(a, min(b, c));
}

/* Function what calculate the best price for three products */
double best_price_three_products(double first_price,
                                 double second_price, double third_price) {
    double minimal_price = triple_min(first_price, second_price, third_price);
    double total_price = first_price + second_price + third_price;
    return total_price - minimal_price;
}

int main() {
    ifstream fin("oferta.in");
    ofstream fout("oferta.out");

    int n, k, i;
    double best_price_2;
    double best_price_3;

    fin >> n >> k;
    vector<double> price_list(n);
    for (i = 0; i < n; i++) {
        fin >> price_list[i];
    }

    // Create a vector for dynamic programming
    vector<double> dp(n, 0);

    // Populate the first three elements of the vector
    dp[0] = price_list[0];

    best_price_2 = best_price_two_products(price_list[0], price_list[1]);
    dp[1] = min(best_price_2 , price_list[0] + price_list[1]);

    best_price_2 = best_price_two_products(price_list[1], price_list[2]);
    best_price_3 = best_price_three_products(price_list[0],
                                             price_list[1], price_list[2]);
    dp[2] = triple_min(best_price_3, best_price_2 + price_list[0],
                                                    price_list[2] + dp[1]);

    // Iterate over the rest of the elements and calculate the best price
    for (i = 3; i < n; i++) {
        best_price_2 = best_price_two_products(price_list[i],
                                                price_list[i - 1]);
        best_price_3 = best_price_three_products(price_list[i],
                                        price_list[i - 1], price_list[i - 2]);
        dp[i] = triple_min(best_price_3 + dp[i - 3], best_price_2 + dp[i - 2],
                                                    price_list[i] + dp[i - 1]);
    }

    // Get the best price
    fout << fixed << setprecision(1) << dp[n - 1] << "\n";

    fin.close();
    fout.close();
    return 0;
}
