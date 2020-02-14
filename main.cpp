#include <iostream>
#include <thread>
#include <vector>
#include "key_value_store.h"

struct simple_worker {

    key_value_store &store;

    explicit simple_worker(key_value_store &store) : store(store) {
    }

    void operator()(const std::string& id) {
        for (int i = 0; i < 10000; i++) {
            std::string val = "val" + id + " - " + std::to_string(i);
            std::string key = "key" + id + " - " + std::to_string(i);
            store.insert(val, key);
        }

        for (int i = 0; i < 10; i++) {
            for (int n = 0; n < 10000; n++) {
                int number = n % (1000 * (n + 1));
                std::string val = "val" + id + " - " + std::to_string(number);
                std::string key = "key" + id + " - " + std::to_string(number);
                if (key != store.get(val).second) {
                    std::cerr << "Key Value Store returned wrong value. Going to abort." << std::endl;
                    exit(1);
                }
            }
        }

        for (int i = 0; i < 10000; i++) {
            std::string val = "val" + id + " - " + std::to_string(i);
            store.remove(val);
        }

        for (int i = 0; i < 10000; i++) {
            std::string val = "val" + id + " - " + std::to_string(i);

            if (store.get(val).first) {
                std::cerr << "Key Value Store returned old value. Going to abort." << std::endl;
                exit(2);
            }
        }
    }
};

const int NUMBER_OF_WORKERS = 10;
const int STORE_SIZE = 2000;

int main() {
    key_value_store key_value_store(STORE_SIZE);

    std::vector<std::thread> workers;

    std::cout << "Start workers" << std::endl;
    auto start = std::chrono::system_clock::now();

    for (int i = 0; i < NUMBER_OF_WORKERS; i++) {
        simple_worker worker(key_value_store);
        workers.emplace_back(worker, std::to_string(i));
    }

    for (auto &worker : workers) {
        worker.join();
    }

    auto end = std::chrono::system_clock::now();
    std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Workers finished after " << duration.count() << " ms" << std::endl;
    return 0;
}