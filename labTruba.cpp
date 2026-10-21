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
        cout << "5. Start/stop shops/start rw in them\n";
        cout << "6. save\n";
        cout << "7. load\n";
        cout << "8. exit\n";
        cout << "Choice--> ";

        int choice = getInt();

        switch (choice) {
            case 1:
                inputPipe(truba);
                pipeCreated = true;
                break;

            case 2:
                inputStation(station);
                stationCreated = true;
                break;

            case 3:
                if (pipeCreated) {
                    showPipe(truba);
                } else {
                    cout << "Create pipe at first\n";
                }

                if (stationCreated) {
                    showStation(station);
                } else {
                    cout << "Create station at first\n";
                }
                break;

            case 4:
                if (!pipeCreated) {
                    cout << "Create pipe at first\n";
                } else {
                    truba.RepairWorks = !truba.RepairWorks;
                    cout << "Status changed\n";
                }
                break;

            case 5:
                if (!stationCreated) {
                    cout << "Create station at first\n";
                } else {
                    cout << "1. Start shops\n";
                    cout << "2. Stop shops\n";
                    cout << "3. Start rw on some shops\n";
                    cout << "Choice: ";

                    int vibor = getInt();

                    switch (vibor) {
                        case 1:
                            if (station.activeNasos < station.totalNasos) {
                                cout << "How many shops you want to activate? ";
                                int count = getInt();

                                while (count < 0 ||
                                       count > station.totalNasos
                                               - station.activeNasos
                                               - station.totalRepairWorksNasos) {
                                    cout << "You don't have enough free shops\n";
                                    count = getInt();
                                }

                                station.activeNasos += count;
                            } else {
                                cout << "All shops are in work\n";
                            }
                            break;

                        case 2:
                            if (station.activeNasos > 0) {
                                cout << "How many shops you want to deactivate? ";
                                int count = getInt();

                                while (count < 0 || count > station.activeNasos) {
                                    cout << "You don't have enough working shops\n";
                                    count = getInt();
                                }

                                station.activeNasos -= count;
                            } else {
                                cout << "There are no active shops\n";
                            }
                            break;

                        case 3:
                            cout << "Warning! You can't start repair works on active shops\n";

                            if (station.totalNasos ==
                                station.activeNasos + station.totalRepairWorksNasos) {
                                cout << "There are no free shops\n";
                            } else {
                                cout << "In how many shops you want to turn on repair works? ";
                                int count = getInt();

                                while (count < 0 ||
                                       count > station.totalNasos
                                               - station.activeNasos
                                               - station.totalRepairWorksNasos) {
                                    cout << "You don't have enough free shops\n";
                                    count = getInt();
                                }

                                station.totalRepairWorksNasos += count;
                            }
                            break;

                        default:
                            cout << "Wrong command\n";
                            break;
                    }
                }
                break;

            case 6: {
                cout << "What do you want to save?\n";
                cout << "1. Pipe\n";
                cout << "2. Station\n";
                cout << "3. All\n";

                int vopros = getInt();

                switch (vopros) {
                    case 1:
                        if (pipeCreated) {
                            savePipeFile(truba);
                        } else {
                            cout << "Create pipe at first\n";
                        }
                        break;

                    case 2:
                        if (stationCreated) {
                            saveStationFile(station);
                        } else {
                            cout << "Create station at first\n";
                        }
                        break;

                    case 3:
                        if (pipeCreated && stationCreated) {
                            savePipeFile(truba);
                            saveStationFile(station);
                        } else if (pipeCreated) {
                            savePipeFile(truba);
                        } else if (stationCreated) {
                            saveStationFile(station);
                        } else {
                            cout << "Create pipe and station at first\n";
                        }
                        break;

                    default:
                        cout << "Wrong input\n";
                        break;
                }
                break;
            }

            case 7:
                loadFile(truba, station);
                break;

            case 8:
                cout << "Bye\n";
                return 0;

            default:
                cout << "Wrong option\n";
                break;
        }
    }

    return 0;
}