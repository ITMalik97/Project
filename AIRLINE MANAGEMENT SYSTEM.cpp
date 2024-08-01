#include "reservation.h"
#include "graph.h"

#define INFINITY 9999
using namespace std;

const int MAX_FLIGHTS = 450;

void loadFlights(Flight flights[], int &count, const string &filename) {
    ifstream read_s("details.txt");
    if (!read_s.is_open()) {
        cerr << "Failed to open file." << endl;
        exit(1);
    }

    string line;
    count = 0;
    while (getline(read_s, line) && count < MAX_FLIGHTS) {
        istringstream iss(line);
        iss >> flights[count].Flight_no >> flights[count].dep >> flights[count].des 
            >> flights[count].B_time >> flights[count].A_time >> flights[count].price 
            >> flights[count].plane_type >> flights[count].T_seats >> flights[count].B_seats;
        ++count;
    }
    read_s.close();
}

void saveFlights(Flight flights[], int count, const string &filename) {
    ofstream write_s("details.txt");
    if (!write_s.is_open()) {
        cerr << "Failed to open file." << endl;
        exit(1);
    }

    for (int i = 0; i < count; ++i) {
        write_s << flights[i].Flight_no << "   " << flights[i].dep << "   " << flights[i].des << "   "
                << flights[i].B_time << "   " << flights[i].A_time << "   " << flights[i].price << "   "
                << flights[i].plane_type << "   " << flights[i].T_seats << "   " << flights[i].B_seats << endl;
    }
    write_s.close();
}

bool deleteFlight(Flight flights[], int &count, int flight_no) {
    bool found = false;
    for (int i = 0; i < count; ++i) {
        if (flights[i].Flight_no == flight_no) {
            found = true;
            for (int j = i; j < count - 1; ++j) {
                flights[j] = flights[j + 1];
            }
            --count;
            break;
        }
    }
    return found;
}

struct City{
	string cities;
};

int main() {
	ReservationSystem system;
	graph g;
	int m;
    Flight data[450];
    char datas[100];
    
    while (true){
        cout << "-----------------------------------------------";
			
			cout << "\n\t AIRLINE MANAGEMENT SYSTEM \n\n";
			cout << "Please pick an option from the menu below. \n";
			cout << "1. Show all cities. \n"; // 1
			cout << "2. Add new flights \n"; // 3
			cout << "3. Delete flights \n"; // 5
			cout << "4. Display flights scheduled \n"; // 2
			cout << "5. Display flight details \n"; // 4
			cout << "6. Passenger information \n"; // 8
			cout << "7. Book reservation \n"; // 7
			cout << "8. Cancel reservation \n"; // 9
			cout << "9. Optimized Distance \n"; // 6
			cout << "0. Exit \n\n"; // 10
			
			cout << "-----------------------------------------------" << endl;
			
			cout << "Enter the number of a menu option: ";
			cin >> m;
        
        if (m == 2) {
            string dep, des, plane_type;
         	string B_time, A_time, delay, cancel;
            int Flight_no, price, T_seats, B_seats, a = 1;
            while(a){
                cout << "Add new Flight by giving the following details: " << endl;
                
                cout << "Flight number: ";
                cin >> Flight_no;
                cout << "Departure City: ";
                cin >> dep;
                cout << "Destination City: ";
                cin >> des;
                cout << "Boarding Time: ";
                cin >> B_time;
                cout << "Arriving Time: "; 
                cin >> A_time;
                cout << "Ticket Price: "; // Can be entered manually
                cin >> price;
                cout << "Aeroplane type: "; // Airbus, Boeing, Cargo and Private.
                cin >> plane_type;
                cout << "Total Seats: ";
                cin >> T_seats;
                cout << "Already Booked Seats: ";
                cin >> B_seats;
                cout << "Enter yes if the flight is delayed: ";
                cin >> delay;
                cout << "Enter yes if the flight is cancelled: ";
                cin >> cancel;
                cout << "enter 1 to continue" << endl;
                cout << "enter the 2 to exit" << endl;
                cin >> a;
                
                if (a == 2){
                    break;
                }
            }
            
            ofstream outfile("details.txt",ios::app);
            outfile << endl << Flight_no << "    " << dep << "    " << des << "    " << B_time << "    " << A_time << "    " << price << "    " << plane_type << "    " << T_seats << "    " << B_seats << "    " << delay << "    " << cancel;
            cout << "Flight added successfully!" << endl;
            ofstream time("Activity.txt",ios::app); 
            time << __DATE__ << "  " << __TIME__ << endl;
            cout << __DATE__ << endl << __TIME__ << endl;
		}
		
		else if (m == 3) {
            Flight flights[MAX_FLIGHTS];
            int flightCount;

            loadFlights(flights, flightCount, "details.txt");

            int flight_no;
            cout << "Enter the flight no.: ";
            cin >> flight_no;

            if (deleteFlight(flights, flightCount, flight_no)) {
                saveFlights(flights, flightCount, "details.txt");
                cout << "Flight deleted successfully." << endl;
            } 
			
			else {
                cout << "This flight hasn't been added!" << endl;
            }     
		}                                    
		
		else if (m == 4) {
			ifstream reads("details.txt");
			
            if (!reads.is_open()) {
                cerr << "Failed to open file." << endl;
                return 1;
            }

            Flight data[450];
            int i = 0;
            string lines;

            while (getline(reads, lines) && i < 450) {
                istringstream iss(lines);
                iss >> data[i].Flight_no >> data[i].dep >> data[i].des >> data[i].B_time >> data[i].A_time >> data[i].price >> data[i].plane_type >> data[i].T_seats >> data[i].B_seats >> data[i].delay >> data[i].cancel;
                ++i;
            }
    
            reads.close();
    
            cout << endl << "                                               ACTIVE FLIGHTS " << endl << endl;
            cout << "Flight no.  Departure  Destination  Boarding time  Arriving time  Ticket price  Plane type  Total seats  Booked seats  Delayed  Cancel flights" << endl << endl;
            
			for (int j = 0; j < i; ++j) {
                cout << data[j].Flight_no << "   " << data[j].dep << "   " << data[j].des << "   " << data[j].B_time << "   " << data[j].A_time << "   " << data[j].price << "   " << data[j].plane_type << "   " << data[j].T_seats << "   " << data[j].B_seats << "   " << data[j].delay << "   " << data[j].cancel << endl;
            }			
		}
			
		else if (m == 5){
            ifstream read("details.txt");
            
            if (!read.is_open()) {
                cerr << "Failed to open file." << endl;
                return 1;
            }

            Flight data[450];
            int i = 0;
            string line;

            while (getline(read, line) && i < 450) {
                istringstream iss(line);
                iss >> data[i].Flight_no >> data[i].dep >> data[i].des >> data[i].B_time >> data[i].A_time >> data[i].price >> data[i].plane_type >> data[i].T_seats >> data[i].B_seats >> data[i].delay >> data[i].cancel;
                ++i;
            }
            read.close();

            int Flight_no;
            cout << "Enter the flight no.: ";
            cin >> Flight_no;

            bool found = false;
            for (int i = 0; i < 450; ++i) {
                if (Flight_no == data[i].Flight_no) {
                    cout << "Flight no. Departure Destination Boarding time Arriving time Ticket price Plane type Total seats Booked seats Delayed Cancelled flights" << endl;
                    cout << data[i].Flight_no << "   " << data[i].dep << "   " << data[i].des << "   " << data[i].B_time << "   " << data[i].A_time << "   " << data[i].price << "   " << data[i].plane_type << "   " << data[i].T_seats << "   " << data[i].B_seats << "   " << data[i].delay << "   " << data[i].cancel << endl;
                    found = true;
                    break;
                }
            }
 
            if (!found) {
                cout << "This flight hasn't been added!" << endl;
            }
		}
		
		else if (m == 6) {
			int fflightNumber;
			cout << "\nEnter flight number to display passengers info: ";
            cin >> fflightNumber;
            system.displayPassengersInFlight(fflightNumber);
		}
		
		else if (m == 7) {
			ifstream readsss("details.txt");
            
            if (!readsss.is_open()) {
                cerr << "Failed to open file." << endl;
                return 1;
            }

            Flight data[450];
            int i = 0;
            string linesss;

            while (getline(readsss, linesss) && i < 450) {
                istringstream issss(linesss);
                issss >> data[i].Flight_no;
                ++i;
            }
            readsss.close();

            int Flight_no1;
            cout << "Enter the flight no.: ";
            cin >> Flight_no1;
            
            system.addFlight(Flight_no1);

            bool found = false;
            for (int i = 0; i < 450; ++i) {
                if (Flight_no1 == data[i].Flight_no) {
                    cout << data[i].Flight_no;
                    found = true;
                    break;
                }
            }
 
            if (!found) {
                cout << "This flight hasn't been added!" << endl;
            }

            int age, tel, flightNumber;
            string name, NAT, passportNumber;
            char choice;

            do {
                flightNumber = Flight_no1;
                cout << endl << "Enter passenger name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter passenger age: ";
                cin >> age;
                cout << "Enter passport number: ";
                cin >> passportNumber;
                cout << "Enter the nationality: ";
                cin >> NAT;
                cout << "Enter telephone number: ";
                cin >> tel;
                
                system.addPassengerToFlight(flightNumber, name, age, passportNumber, NAT, tel);
                
                cout << "Passenger added! " << endl;
                cout << "Do you want to add another passenger? (y/n): ";
                cin >> choice;
                
            } while (choice == 'y' || choice == 'Y');
        }
		
		else if (m == 8) {
			string passport_Number;
			int flight_Number;
			
			cout << "\nEnter flight number to cancel reservation: ";
            cin >> flight_Number;
            cout << "Enter passport number: ";
            cin >> passport_Number;
            system.cancelReservation(flight_Number, passport_Number);
		}
		
		else if (m == 9) {
		    g.shortest();
		}
		
		else if (m == 1) {
			ifstream readss("cities.txt");
    
            if (!readss.is_open()) {
                cerr << "Failed to open file." << endl;
                return 1;
            }

            City datas[45];
            int ia = 0;
            string liness;

    		while (getline(readss, liness) && ia < 45) {
        		istringstream isss(liness);
        		isss >> datas[ia].cities;
        		++ia;
    		}

    		readss.close();

    		cout << " -Cities- " << endl << endl;
   
    		for (int ja = 0; ja < ia; ++ja) {
    		    cout << datas[ja].cities << endl;
    		}

		}
		
		else if (m == 0) {
			cout << endl << "THANK YOU FOR USING THE SYSTEM" << endl;
			break;
		}
		
		else {
			cout << endl << "Invalid Selection!" << endl << endl;
		}
    }
    
	return 0;
}
