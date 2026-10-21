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
    double i;
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

void inputPipe(Pipe &p) { 
    cout << "Enter km pipe of your pipe--> ";
    getline(cin, p.kmZnach);
    cout << "Enter lenght(kilometers)--> ";
    p.ProtKm = getDouble();
    while (p.ProtKm <=0) {
    }

    cout << "Enter diameter (milimeters)--> ";
    p.diameterMm=getInt();

    p.RepairWorks = false;
}

void inputStation(Station &s){
    cout << "Enter name of your station";
    getline(cin, s.name);
    cout << "Enter number of shops";
    s.totalNasos = getInt();
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

void savePipeFile(Pipe &p) {
    ofstream f("data.txt");
    f << p.kmZnach << endl;
    f << p.ProtKm << endl;
    f << p.diameterMm << endl;
    f << p.RepairWorks << endl;
    f.close();
}
void saveStationFile(Station &s) {
    ofstream f("data.txt");
    f << s.name << endl;
    f << s.totalNasos << endl;
    f << s.activeNasos << endl;
    f << s.totalRepairWorksNasos << endl;
    f.close(); 
}

void loadFile(Pipe &p, Station &s) {
    ifstream f("data.txt");
    if (!f.is_open()) {
        cout << "File not found\n";
        return;
    }
    getline(f, p.kmZnach);
    f >> p.ProtKm;
    f >> p.diameterMm;
    f >> p.RepairWorks;
    f.ignore(1000, '\n');
    getline(f, s.name);
    f >> s.totalNasos;
    f >> s.activeNasos;
    f >> s.totalRepairWorksNasos;
    f.close();
    cout << "Loaded from data.txt\n";
}

void changeStatus (bool stationCreated, Station &s) {
        if (!stationCreated) {
        cout << "Create station at first\n";
    } else {
        cout << "1. Start shops\n2. Stop Shops\n3. Start rw on some shops\n Choice: ";
        int vibor = getInt();
        if (vibor ==1) {
            if (s.activeNasos < s.totalNasos) {
                cout << "How much of shops you want activate? ";
                s.activeNasos=getInt();
                while (s.activeNasos > (s.totalNasos - s.totalRepairWorksNasos)) {
                    cout << "you dont have enought free shops\n";
                    s.activeNasos = getInt();
                }
            } else {
                cout << "All shops are in work";
            }
        }
        else if (vibor ==2) {
            if (s.activeNasos>0) {
                cout << "How much of shops you want disactivate? ";
                s.activeNasos=s.activeNasos - getInt();
                while (s.activeNasos<0) {
                    cout << "you dont have enought working shops\n";
                    s.activeNasos = s.activeNasos - getInt();
                } 
                
            } else {
                    cout << "There is no active shops";
            }
        }
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
        switch (choice)
        {
        case 8:
        {
            cout << "Bye\n";
            break;
        }
        case 1:
        {
            inputPipe(truba);
            pipeCreated = true;
            break;
        }
        case 2:
        {
            inputStation(station);
            stationCreated = true;
            break;
        }
        case 3:
        {
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
            break;
        }
        case 4:
        {
            if (!pipeCreated) {
                cout << "Create pipe at first\n";
            } else {
                truba.RepairWorks = !truba.RepairWorks;
                cout << "Status changed\n";
            }
            break;
        }
        case 5:
        {
            changeStatus(stationCreated, station);
            break;
        }
        case 6:
        {
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
            break;
        }
        case 7:
        {
            loadFile(truba, station);
            pipeCreated = true;
            stationCreated = true;
            break;
        }
        default:
        {
            cout << "wrong option\n";
            break;
        }
        }
    }

    return 0;
}