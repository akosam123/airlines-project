#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

const int MAX_PASSENGERS = 200;
const int MIN_PASSENGERS = 100;
const int NUM_FLIGHTS = 4;
const double ONE_WAY_FARE = 250.00;
const double ROUND_TRIP_FARE = 450.00;
const double TAX_RATE = 0.15;
const double BAGGAGE_FEE = 25.00;
const double INSURANCE_FEE = 10.00;
const double OVERHEAD = 0.77;

const double FOOD_PRICES[4] = {9.50, 11.00, 12.00, 13.00};
const double DRINK_PRICES[4] = {4.50, 5.00, 6.00, 6.50};

// Struct to store passenger information
struct Passenger {
    string name;
    bool roundTrip;
    bool luggageInsurance;
    int numBags;
    int foodChoice;
    int drinkChoice;
};

// Struct to store flight information
struct Flight {
    int flightNumber;
    string destination;
    string flightTime;
    string flightDate;
    int numPassengers;
    Passenger passengers[MAX_PASSENGERS];

    // Function to calculate total revenue for the flight
    double calculateRevenue() {
        double revenue = 0;
        for (int i = 0; i < numPassengers; i++) {
            double ticketPrice = passengers[i].roundTrip ? ROUND_TRIP_FARE : ONE_WAY_FARE;
            double tax = ticketPrice * TAX_RATE;
            double baggageFee = passengers[i].numBags * BAGGAGE_FEE;
            double insuranceFee = passengers[i].luggageInsurance ? passengers[i].numBags * INSURANCE_FEE : 0.00;
            double foodPrice = FOOD_PRICES[passengers[i].foodChoice - 1];
            double drinkPrice = DRINK_PRICES[passengers[i].drinkChoice - 1];

            revenue += ticketPrice + tax + baggageFee + insuranceFee + foodPrice + drinkPrice;
        }
        return revenue;
    }
};

int main() {
    // Creating 4 flights with predefined destinations, times, and dates
    Flight flights[NUM_FLIGHTS] = {
        {101, "New York", "08:00 AM", "2025-02-15"},
        {102, "Los Angeles", "09:30 AM", "2025-02-15"},
        {103, "Chicago", "10:45 AM", "2025-02-15"},
        {104, "Miami", "12:00 PM", "2025-02-15"}
    };

    // Generating random passenger data for each flight
    for (int f = 0; f < NUM_FLIGHTS; f++) {
        flights[f].numPassengers = MIN_PASSENGERS + (rand() % (MAX_PASSENGERS - MIN_PASSENGERS + 1));

        for (int i = 0; i < flights[f].numPassengers; i++) {
            flights[f].passengers[i].name = "Passenger_" + to_string(i + 1);
            flights[f].passengers[i].roundTrip = (rand() % 2 == 0);
            flights[f].passengers[i].luggageInsurance = (rand() % 2 == 0);
            flights[f].passengers[i].numBags = rand() % 3; // 0 to 2 bags
            flights[f].passengers[i].foodChoice = (rand() % 4) + 1;
            flights[f].passengers[i].drinkChoice = (rand() % 4) + 1;
        }
    }

    // Calculate and display total revenue for each flight
    double totalIncome = 0;
    for (int f = 0; f < NUM_FLIGHTS; f++) {
        double flightRevenue = flights[f].calculateRevenue();
        cout << "Flight " << flights[f].flightNumber << " to " << flights[f].destination
             << " generated: $" << fixed << setprecision(2) << flightRevenue << endl;
        totalIncome += flightRevenue;
    }

    // Compute net income after overhead
    double netIncome = totalIncome * (1 - OVERHEAD);
    cout << "\nTotal income from all flights: $" << totalIncome << endl;
    cout << "Net income after 77% overhead: $" << netIncome << endl;

    return 0;
}
