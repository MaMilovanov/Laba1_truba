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
        cout << "wrong input";
        fixInput();
    }
    fixInput();
    return x;
}

void inputPipe(Pipe &p) {
    cout << "Enter km pipe of your pipe--> ";
    getline(cin, p.kmZnach);
    cout << "Enter lenght(kilometers)--> ";
    p.ProtKm = getDouble();
    while (p.ProtKm <=0) {
        cout << "Must be >0 ";
        p.ProtKm = getDouble();
    }

    cout << "Enter diameter (milimeters)--> ";
    p.diameterMm=getInt();
    while (p.diameterMm <= 0) {
        cout << "Must be >0 --> ";
        p.diameterMm = getInt();
    }

    p.RepairWorks = false;
}

void inputStation(Station &s){
    cout << "Enter name of your station";
    getline(cin, s.name);
    cout << "Enter number of shops";
    s.totalNasos = getInt();
    while (s.totalNasos <=0) {
        cout << "Must be >0 ";
        s.totalNasos=getInt(); 
    }
    cout << "How many shops are active?";
    s.activeNasos =getInt();
    while (s.activeNasos > s.totalNasos) {
        cout << "Number of active nasos can not be more then their total number";
        s.activeNasos = getInt();
    }
    s.totalRepairWorksNasos = 0;
}

void showStation(Station &s) {
    cout << "\nStation:\n";
    cout << "Name: " << s.name <<endl;
    cout << "Shops: " << s.activeNasos << "/" << s.totalNasos << endl;
    cout << "N_of_repairing_shops" << s.totalRepairWorksNasos << endl;
}

void showPipe(Pipe &p) {
    cout << "\nPipe: \n";
    cout << "Mark: " << p.kmZnach <<endl;
    cout << "Lenght: " << p.ProtKm << "km\n";
    cout << "Diameter: " << p.diameterMm << "mm\n";
    if (p.RepairWorks) {
        cout << "Repair works: active\n";
    } else {
        cout << "Repair works: do not need\n";
    }
}

int main() {
    Pipe truba;
    Station station;
    bool pipeCreated = false;
    bool stationCreated = false;

    while (true) {
        cout << "\n____MENU____\n";
        cout << "1. add a pipe\n";
        cout << "2. add station\n";
        cout << "3. show all\n";
        cout << "4. Toggle pipe repair\n";
        cout << "5. Start/stop ships/start rw in them\n";
        cout << "6. save\n";
        cout << "7. load\n";
        cout << "8. exit\n";
        cout << "Choice--> ";
    
        int choice = getInt();
        if (choice == 8) {
            cout << "Bye\n";
            break;
        }
        else if (choice == 1) {
            inputPipe(truba);
            pipeCreated = true;
        }
        else if (choice == 2) {
            inputStation(station);
            stationCreated = true;
        }
        else if (choice == 3) {
            if (!pipeCreated) {
                cout << "Create something at first\n";
            } else {
                if (pipeCreated) showPipe(truba);
                if (stationCreated) showStation(station);
            }
        }
        else if (choice == 4) {
            if (!pipeCreated) {
                cout << "Create pipe at first\n";
            } else {
                truba.RepairWorks = !truba.RepairWorks;
                cout << "Status changed\n";
            }
        }
        
        else if (choice == 5) {
            if (!stationCreated) {
                cout << "Create station at first\n";
            } else {
                cout << "1. Start shops\n2. Stop Shops\n3. Start rw on some shops\n Choice: ";
                int vibor = getInt();
                if (vibor ==1) {
                    if (station.activeNasos < station.totalNasos) {
                        cout << "How much of shops you want activate? ";
                        station.activeNasos=getInt();
                        while (station.activeNasos > (station.totalNasos - station.totalRepairWorksNasos)) {
                            cout << "you dont have enought free shops\n";
                            station.activeNasos = getInt();
                        }
                    } else {
                        cout << "All shops are in work";
                    }
                }
                else if (vibor ==2) {
                    if (station.activeNasos>0) {
                        cout << "How much of shops you want disactivate? ";
                        station.activeNasos=station.activeNasos - getInt();
                        while (station.activeNasos<0) {
                            cout << "you dont have enought working shops\n";
                            station.activeNasos = station.activeNasos - getInt();
                        } 
                        
                    } else {
                            cout << "There is no active shops";
                    }
                }
                else if (vibor ==3) {
                    cout << "Warning! You cant start rw on active shops, remember this";
                    if (station.totalNasos ==(station.activeNasos +station.totalRepairWorksNasos)) {
                        cout << "There are no free shops";
                    } else {
                        cout << "In how many shops you want to turn in rw? ";
                        station.totalRepairWorksNasos = getInt();
                        while (station.totalRepairWorksNasos > (station.totalNasos-station.activeNasos)) {
                            cout << "you dont have enought free shops";
                            station.totalRepairWorksNasos = getInt();
                        }
                    }
                }
                else {
                    cout << "wrong command";
                }
            }
        }
        
        else {
            cout << "wrong option\n";
        }
    }

    return 0;
}