#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
using namespace std;

char letter;

/* Function what compare two strings by the apperence of a letter */
bool compare(string a, string b) {
    map<char, int> letter_apperence_a, letter_apperence_b;

    int i, j;
    int count_a = 0, count_b = 0;

    double size_a = a.size();
    double size_b = b.size();

    for (i = 0; i < size_a; i++) {
        letter_apperence_a[a[i]]++;
    }
    for (i = 0; i < size_b; i++) {
        letter_apperence_b[b[i]]++;
    }

    for (auto letters : letter_apperence_a) {
        if (letters.first == letter) {
            count_a = letters.second;
        }
    }
    for (auto letters : letter_apperence_b) {
        if (letters.first == letter) {
            count_b = letters.second;
        }
    }


    return count_a / size_a > count_b / size_b;
}


int main() {
    ifstream fin("criptat.in");
    ofstream fout("criptat.out");

    int n, i, j, k, cap;

    fin >> n;
    vector<string> list_of_string(n);

    map<char, bool> letter_apperence;
    map<char, int> letter_apperence_count;

    int rest_letter_count = 0, current_password = 0, password_lenght = 0;
    int dominant_letter_count = 0, count_letter_can_use = 0;
    int best_password = 0;

    // Read the strings and mark the letters that appear
    for (i = 0; i < n; i++) {
        fin >> list_of_string[i];
        for (j = 0; j < list_of_string[i].size(); j++) {
            letter_apperence[list_of_string[i][j]] = true;
        }
    }

    // For every letter that appears, we calculate the password
    // that respects the condition
    for (auto letters : letter_apperence) {
        letter = letters.first;
        dominant_letter_count = 0;
        rest_letter_count = 0;
        password_lenght = 0;

        // Sort the strings by the number of apperence of the letter
        sort(list_of_string.begin(), list_of_string.end(), compare);

        // For every string, we add it if the letter dominates
        // the other letters
        for (i = 0; i < n; i++) {
            letter_apperence_count.clear();
            for (j = 0; j < list_of_string[i].size(); j++) {
                letter_apperence_count[list_of_string[i][j]]++;
            }
            if (letter_apperence_count[letter] > list_of_string[i].size() / 2) {
                password_lenght += list_of_string[i].size();
                dominant_letter_count += letter_apperence_count[letter];
                rest_letter_count += list_of_string[i].size() -
                                    letter_apperence_count[letter];
            } else {
                break;
            }
        }

        // For the rest of the strings, we find if we can add them
        // to the password using dynamic programming
        count_letter_can_use = dominant_letter_count - rest_letter_count;
        if (password_lenght != 0) {
            vector<vector<int>> dp(n - i + 1,
                                vector<int>(count_letter_can_use, 0));

            int necesary_letters = 0, remain_letters = 0, saved_i = i;
            int lenght_of_string = 0;

            // Populate the first column of the dp matrix
            for (j = 1; j <= n - i; j++) {
                lenght_of_string = list_of_string[saved_i].size();
                necesary_letters = 0;
                remain_letters = 0;

                // Calculate the number of dominant letters and the rest
                for (k = 0; k < lenght_of_string; k++) {
                    if (list_of_string[saved_i][k] == letter) {
                        necesary_letters++;
                    } else {
                        remain_letters++;
                    }
                }
                // If they are equal, we can add the string to the password
                if (necesary_letters == remain_letters) {
                    dp[j][0] = dp[j - 1][0] + lenght_of_string;
                } else {
                    dp[j][0] = dp[j - 1][0];
                }
                saved_i++;
            }

            saved_i = i;
            // Poulate the rest of the dp matrix by findig if we can add
            // the string to the password and respect the condition
            for (j = 1; j <= n - i; j++) {
                lenght_of_string = list_of_string[saved_i].size();
                for (cap = 1; cap < count_letter_can_use; cap++) {
                    dp[j][cap] = dp[j - 1][cap];
                    necesary_letters = 0;
                    remain_letters = 0;

                    for (k = 0; k < lenght_of_string; k++) {
                        if (list_of_string[saved_i][k] == letter) {
                            necesary_letters++;
                        } else {
                            remain_letters++;
                        }
                    }

                    if (remain_letters - necesary_letters <= cap) {
                        dp[j][cap] = max(dp[j][cap], dp[j - 1][cap -
                        remain_letters + necesary_letters] + lenght_of_string);
                    }
                }
                saved_i++;
            }

            // The biggest password is the best password
            current_password = dp[n - i][count_letter_can_use - 1]
                                                + password_lenght;
            if (current_password > best_password) {
                best_password = current_password;
            }
        }
    }

    fout << best_password << "\n";

    fout.close();
    fin.close();
    return 0;
}
