#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#define INFINITY 9999
using namespace std;

struct Flight{
    string dep, des, plane_type;
    string B_time, A_time, delay, cancel;
	int Flight_no, price, T_seats, B_seats;
};
	
class graph{
    private:
    int **mat;
    bool check;
    vector<string> names;
    map<string, int> cityIndexMap;
    int total = 43, *d;
    bool *v;

    public:
    graph();
    void accept();
    int minDistance();
    void shortest();
};

graph::graph(){ 
    mat = new int *[total + 1];
    for (int i = 0; i <= total; ++i)
        mat[i] = new int[total + 1];

    v = new bool[total + 1];
    d = new int[total + 1];

    accept();
}

void graph::accept(){
    ifstream namesFile("city_names.txt");
    ifstream distancesFile("city_distances.txt");

    if (!namesFile.is_open() || !distancesFile.is_open()){
        cerr << "Error opening files." << endl;
        exit(1);
    }

    string line;
    int number = 1;

    while (getline(namesFile, line)){
        istringstream iss(line);
        string city;
        iss >> city;

        names.push_back(city);
        cityIndexMap[city] = number;
        number++;
    }

    for (int i = 0; i <= total; ++i){
        for (int j = 0; j <= total; ++j){
            mat[i][j] = (i == j) ? 0 : INFINITY;
        }
    }

    while (getline(distancesFile, line)){
        istringstream iss(line);
        int source, connectedCity, distance;
        iss >> source;

        while (iss >> connectedCity >> distance && distance != -999){
            mat[source][connectedCity] = distance;

            if (!check)
                mat[connectedCity][source] = distance;
        }
    }

    namesFile.close();
    distancesFile.close();
}

void graph::shortest(){
    string src, des;

    cout << "\nEnter the source city : ";
    cin.ignore();
    getline(cin, src);
    cout << "\nEnter destination city : ";
    getline(cin, des);

    int srcIndex = cityIndexMap[src];
    int desIndex = cityIndexMap[des];

    for (int i = 1; i <= total; i++){
        d[i] = INFINITY;
        v[i] = false;
    }

    d[srcIndex] = 0;

    for (int count = 1; count <= total; count++){
        int loc = minDistance();
        v[loc] = true;
        
        for (int i = 1; i <= total; i++){
            if (!v[i] && mat[loc][i] != INFINITY && (d[loc] + mat[loc][i]) < d[i]){
                d[i] = d[loc] + mat[loc][i];
            }
        }
    }

    if (d[desIndex] == INFINITY){
        cout << "\nNo path present from " << src << " to " << des << endl;
        return;
    }

    cout << "\nShortest path from " << src << " to " << des << " : " << d[desIndex] << " mi\n";
    cout << __TIME__ << "  " << __DATE__ << endl;
}

int graph::minDistance(){
    int min = INFINITY, min_loc;

    for (int i = 1; i <= total; i++){
        if (!v[i] && d[i] <= min){
            min = d[i];
            min_loc = i;
        }
    }

    return min_loc;
}