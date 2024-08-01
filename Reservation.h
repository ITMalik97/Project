#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#define INFINITY 9999
using namespace std;

struct Passenger {
    string name;
    int age;
    int tel;
    string passportNumber;
    string NAT;
    Passenger* next;
};

struct FFlight {
    int flightNumber;
    Passenger* passengerHead;
};

class ReservationSystem {
private:
    vector<FFlight> flights;

public:
    void addFlight(const int& flightNumber) {
        flights.push_back({flightNumber, nullptr});
    }

    void addPassengerToFlight(const int& flightNumber, const string& name, int age, const string& passportNumber, const string& NAT, int tel) {
        for (auto& flight : flights) {
            if (flight.flightNumber == flightNumber) {
                Passenger* newPassenger = new Passenger{name, age, tel, passportNumber, NAT, nullptr};
                if (!flight.passengerHead) {
                    flight.passengerHead = newPassenger;
                } else {
                    Passenger* temp = flight.passengerHead;
                    while (temp->next) {
                        temp = temp->next;
                    }
                    temp->next = newPassenger;
                }
                return;
            }
        }
        cout << "Flight not found!" << endl;
    }

    void displayPassengersInFlight(const int& flightNumber) const {
        for (const auto& flight : flights) {
            if (flight.flightNumber == flightNumber) {
                Passenger* temp = flight.passengerHead;
                cout << "Passengers for flight " << flightNumber << ":\n";
                while (temp) {
                    cout << "Name: " << temp->name << ", Age: " << temp->age << ", Passport Number: " << temp->passportNumber << ", Telephone: " << temp->tel << ", Nationality: " << temp->NAT << endl;
                    temp = temp->next;
                }
                return;
            }
        }
        cout << "Flight not found!" << endl;
    }
    
    void cancelReservation(const int& flightNumber, const string& passportNumber) {
        for (auto& flight : flights) {
            if (flight.flightNumber == flightNumber) {
                Passenger* temp = flight.passengerHead;
                Passenger* prev = nullptr;

                while (temp) {
                    if (temp->passportNumber == passportNumber) {
                        if (prev) {
                            prev->next = temp->next;
                        } else {
                            flight.passengerHead = temp->next;
                        }
                        delete temp;
                        cout << "Reservation cancelled for passport number: " << passportNumber << endl;
                        return;
                    }
                    prev = temp;
                    temp = temp->next;
                }
                cout << "Passenger with passport number " << passportNumber << " not found!" << endl;
                return;
            }
        }
        cout << "Flight not found!" << endl;
    }

    ~ReservationSystem() {
        for (auto& flight : flights) {
            while (flight.passengerHead) {
                Passenger* temp = flight.passengerHead;
                flight.passengerHead = flight.passengerHead->next;
                delete temp;
            }
        }
    }
};
