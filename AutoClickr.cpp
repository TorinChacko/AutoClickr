#include <iostream>
#include <windows.h>
#include <thread>
#include <atomic>

// Flag to control the auto-clicker state
std::atomic<bool> is_running(false);

// Function to perform mouse clicks
void AutoClicker() {
    while (is_running) {
        // Simulate a left mouse button click
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Click duration
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

        // Delay between clicks
        std::this_thread::sleep_for(std::chrono::milliseconds(400)); // Change this value as needed
    }
}

int main() {
    std::cout << "Press 's' to start/stop the auto-clicker and 'q' to quit." << std::endl;

    char input;
    std::thread clicker_thread;

    while (true) {
        std::cin >> input;

        if (input == 's') {
            if (is_running) {
                // Stop the auto-clicker
                is_running = false;
                if (clicker_thread.joinable()) {
                    clicker_thread.join();
                }
                std::cout << "Auto-clicker stopped." << std::endl;
            } else {
                // Start the auto-clicker
                is_running = true;
                clicker_thread = std::thread(AutoClicker);
                std::cout << "Auto-clicker started." << std::endl;
            }
        } else if (input == 'q') {
            // Quit the program
            is_running = false;
            if (clicker_thread.joinable()) {
                clicker_thread.join();
            }
            break;
        }
    }

    return 0;
}
