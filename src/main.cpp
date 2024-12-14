#include "Simulation.h"
#include "Action.h" // Includes the header that declares backup
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    cout << "kishkashta" << std::endl;

    if (argc != 2) {
        cout << "usage: simulation <config_path>" << endl;
        return 0;
    }
    string configurationFile = argv[1];
    Simulation simulation(configurationFile);
    simulation.start();

    // Check if backup exists, delete if necessary
    if (backup != nullptr) {
        delete backup;
        backup = nullptr;
    }

    return 0;
}
