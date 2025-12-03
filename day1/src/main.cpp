#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

int main() {
    std::ifstream file("/home/eliot/advent_of_code_2025/day1/src/input.txt");

    std::cout << "Current working dir: "
          << std::filesystem::current_path() << "\n";

    if (!file.is_open()) {
        std::cerr << "Failed to open file!" << std::endl;
        return 1;
    }
    int32_t constexpr lock_size = 100;
    int32_t lock[lock_size];
    int32_t position = 50;
    int32_t value_counter = 0;
    lock[0] = 1;
    for (int i = 1; i < 100; ++i) {
        lock[i] = 0;
    }

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        char direction = line[0];                 
        int32_t value = std::stoi(line.substr(1));  
        
        std::cout << "Direction: " << direction
                  << ", Value: " << value << "\n";
                  
        if (direction == 'R') {
            if (value >= lock_size - position) {
                position = (position + value) % lock_size;
            } else {
                position += value;
            }
        } else if (direction == 'L') {
            if (value > position) {
                int32_t scaled_value = value - position;
                if (scaled_value % lock_size == 0) {
                    position = 0;
                } else {
                    position = lock_size - (scaled_value % lock_size);
                }
            } else {
                position -= value;
            }
        }
        value_counter += lock[position]; 
    }

    std::cout << "Total Value Counter: " << value_counter << "\n";

    file.close();
    return 0;
}
