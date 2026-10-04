#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Pipe {
    string kmZnach;
    double ProtKm;
    int diameterMm;
    bool RepairWorks;
};

struct Station {
    string name;
    int totalNasos;
    int activeNasos;
    int totalRepairWorksNasos;
};

void fixInput() {
    cin.clear();
    cin.ignore(1000, '\n');
}
int getInt() {
    int x;
    while (!(cin >> x)) {
        cout << "wrong input";
        fixInput();
    }
    fixInput();
    return x;
}

double getDouble() {
    double x;
    while (!(cin >> x)) {
        cout << "Wrong input, try again: ";
        fixInput();
    }
    fixInput();
    return x;
}

int main() {
    Pipe truba;
    Station station;
    bool pipeCreated = false;
    bool stationCreatied = false;

    while (true) {
        cout << "\n____MENU____\n";
        cout << "1. add a pipe\n";
        cout << "2. add station\n";
        cout << "3. show all\n";
        cout << "4. Toggle pipe repair\n";
        cout << "5. Start/stop nasos\n";
        cout << "6. save\n";
        cout << "7. load\n";
        cout << "8. exit\n";
        cout << "Choice--> ";
    
        int choice = getInt();
        if (choice == 8) {
            cout << "Bye\n";
            break;
        }
        else {
            cout << "wrong option\n";
        }

    }

    return 0;
}