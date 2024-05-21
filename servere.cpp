#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <fstream>
using namespace std;

/* Function to calculate the power of servers by a given value */
double power_calculation(vector<int> power_of_servers,
                        vector<int> alimentation_limits, double best_power) {
    int i;
    double power = 0, optimal_power = INT32_MAX;

    for (i = 0; i < power_of_servers.size(); i++) {
        power = power_of_servers[i] - abs(best_power - alimentation_limits[i]);
        if (power < optimal_power) {
            optimal_power = power;
        }
    }

    return optimal_power;
}

int main() {
    ifstream fin("servere.in");
    ofstream fout("servere.out");

    int i;
    int number_of_servers;

    double min = INT32_MAX, max = 0;
    double best_power, best_power_left, best_power_right;
    double optimal_power_left, optimal_power_right, optimal_power;

    fin >> number_of_servers;

    vector<int> power_of_servers(number_of_servers);
    vector<int> alimentation_limits(number_of_servers);

    // Read from the file and find the minimum and maximum limits
    for (i = 0; i < number_of_servers; i++) {
        fin >> power_of_servers[i];
    }

    for (i = 0; i < number_of_servers; i++) {
        fin >> alimentation_limits[i];
        if (alimentation_limits[i] < min) {
            min = alimentation_limits[i];
        } else if (alimentation_limits[i] > max) {
            max = alimentation_limits[i];
        }
    }

    // Using binary search to find optimal power
    while (1) {
        best_power = (max + min) / 2;

        optimal_power_left = power_calculation(power_of_servers,
                                    alimentation_limits, best_power - 0.01);
        optimal_power = power_calculation(power_of_servers,
                                    alimentation_limits, best_power);
        optimal_power_right = power_calculation(power_of_servers,
                                    alimentation_limits, best_power + 0.01);

        // If the optimal power is higher in the left and right, we found it
        if (optimal_power_left < optimal_power
            && optimal_power > optimal_power_right) {
            break;
        // If the optimal power is higher in the left, we search the left side
        } else if (optimal_power_left > optimal_power) {
            max = best_power;
        // If the optimal power is higher in the right, we search the right side
        } else {
            min = best_power;
        }
    }


    fout << fixed << setprecision(1) << optimal_power << "\n";


    fin.close();
    fout.close();
    return 0;
}
