#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <cmath>

using namespace std;

vector<int> dzielnik;
mutex mtx;

void find_divisors(long long n, int start, int end) {
    vector<int> thread_dzielnik;
    for (int i = start; i <= end; i++) {
        if (n % i == 0) {
            thread_dzielnik.push_back(i);
        }
    }
}
int main() {
    long long n = 123456789;
    int num_threads = 4;
    int range = sqrt(n);
    vector<thread> threads;
    for (int i = 0; i < num_threads; i++) {
        int start = i * range / num_threads + 1;
        int end = (i + 1) * range / num_threads;
        threads.push_back(thread(find_divisors, n, start, end));
    }
    for (int i = 0; i < num_threads; i++) {
        threads[i].join();
    }
    for (int i = range; i >= 1; i--) {
        if (n % i == 0) {
            dzielnik.push_back(n / i);
        }
    }
    for (int dzielnik : dzielnik) {
        cout << dzielnik << " ";
    }
    return 0;
}
