#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept> // For exception handling
using namespace std;

int main() {
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7}; // Example input
    int k = 3; // Number of rotations

    try {
        int l = nums.size();

        // Error handling: check if the array is empty
        if (l == 0) {
            throw runtime_error("Error: The array is empty. Cannot perform rotation.");
        }

        // Error handling: check if k is negative
        if (k < 0) {
            throw invalid_argument("Error: The number of rotations (k) cannot be negative.");
        }

        // Normalize k to ensure it's within the range of 0 to l-1
        k = k % l;

        // Special case: if k is 0 or the array length is 1, no need to rotate
        if (k == 0 || l == 1) {
            for (int num : nums) {
                cout << num << " ";
            }
            return 0; // Exit early
        }

        // Edge case: if l == 2 and k == 1, reverse the array
        if (l == 2 && k == 1) {
            reverse(nums.begin(), nums.end());
        } else {
            // Reverse the last k elements first
            reverse(nums.end() - k, nums.end());
            // Reverse the first l - k elements
            reverse(nums.begin(), nums.end() - k);
            // Reverse the entire array
            reverse(nums.begin(), nums.end());
        }

        // Print the rotated array
        for (int i = 0; i < l; i++) {
            cout << nums[i] << " ";
        }
    } catch (const exception &e) {
        // Print the error message if an exception is caught
        cerr << e.what() << endl;
    }

    return 0;
}
