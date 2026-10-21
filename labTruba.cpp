#include <iostream>
#include <string>
#include <fstream>
#include <limits>

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
    int i;
    while(1)
    {
        if (cin >> i && cin.peek() == '\n' && i >= 0){
            cin.ignore(10000,'\n');
            return i;
        } else {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Wrong action" << endl;
        }
    }
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
    while (s.activeNasos > s.totalNasos || s.activeNasos < 0) {
        cout << "wrong number";
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

bool readDataFile(Pipe &p, Station &s,
                  bool &hasPipe, bool &hasStation) {
    ifstream f("data.txt");

    hasPipe = false;
    hasStation = false;

    if (!f.is_open()) {
        return false;
    }

    string section;

    while (getline(f, section)) {
        if (section == "PIPE") {
            if (!getline(f, p.kmZnach)) {
                return false;
            }

            if (!(f >> p.ProtKm
                    >> p.diameterMm
                    >> p.RepairWorks)) {
                return false;
            }

            f.ignore(numeric_limits<streamsize>::max(), '\n');
            hasPipe = true;
        }
        else if (section == "STATION") {
            if (!getline(f, s.name)) {
                return false;
            }

            if (!(f >> s.totalNasos
                    >> s.activeNasos
                    >> s.totalRepairWorksNasos)) {
                return false;
            }

            f.ignore(numeric_limits<streamsize>::max(), '\n');
            hasStation = true;
        }
        else if (!section.empty()) {
            return false;
        }
    }

    return !f.bad();
}

bool writeDataFile(Pipe &p, Station &s,
                   bool hasPipe, bool hasStation) {
    ofstream f("data.txt");

    if (!f.is_open()) {
        cout << "Cannot open data.txt for saving\n";
        return false;
    }

    if (hasPipe) {
        f << "PIPE\n";
        f << p.kmZnach << '\n';
        f << p.ProtKm << '\n';
        f << p.diameterMm << '\n';
        f << p.RepairWorks << '\n';
    }

    if (hasStation) {
        f << "STATION\n";
        f << s.name << '\n';
        f << s.totalNasos << '\n';
        f << s.activeNasos << '\n';
        f << s.totalRepairWorksNasos << '\n';
    }

    if (!f) {
        cout << "Error while saving data\n";
        return false;
    }

    return true;
}

void savePipeFile(Pipe &p) {
    Pipe oldPipe{};
    Station s{};
    bool hasPipe = false;
    bool hasStation = false;

    readDataFile(oldPipe, s, hasPipe, hasStation);

    if (writeDataFile(p, s, true, hasStation)) {
        cout << "Pipe information saved to data.txt\n";
    }
}

void saveStationFile(Station &s) {
    Pipe p{};
    Station oldStation{};
    bool hasPipe = false;
    bool hasStation = false;

    readDataFile(p, oldStation, hasPipe, hasStation);

    if (writeDataFile(p, s, hasPipe, true)) {
        cout << "Station information saved to data.txt\n";
    }
}

void loadFile(Pipe &p, Station &s) {
    bool hasPipe = false;
    bool hasStation = false;

    if (!readDataFile(p, s, hasPipe, hasStation)) {
        cout << "File not found or data.txt contains invalid data\n";
        return;
    }

    if (!hasPipe && !hasStation) {
        cout << "No saved data found\n";
        return;
    }

    cout << "Loaded from data.txt\n";

    if (hasPipe) {
        cout << "Pipe data loaded\n";
    }

    if (hasStation) {
        cout << "Station data loaded\n";
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
            if (pipeCreated) {
                showPipe(truba);
            } 
            else {
                cout << "Create pipe at first\n";  
            }
            if (stationCreated) {
                showStation(station);
            }else {
                cout << "Create station at first\n";
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
        else if (choice == 6) {
            cout << "What do you want to save? 1. Pipe 2. Station 3. All ";
            int vopros = getInt();
            if (vopros == 1) {
                savePipeFile(truba);
                cout << "Pipe information saved to data.txt";
            }
            else if (vopros == 2) {
                saveStationFile(station);
                cout << "Station information saved to data.txt";   
            }
            else if (vopros = 3) {
                savePipeFile(truba);
                saveStationFile(station);
                cout << "All saved to data.txt";
            } else {
                cout << "wrong input";
            }
        }
        else if (choice == 7) {
            loadFile(truba, station);
            pipeCreated = true;
            stationCreated = true;
        }
        else {
            cout << "wrong option\n";
        }
    }

    return 0;
}