#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Airport.h"
#include "Airline.h"
#include "Plane.h"
#include "Route.h"
#include "Passenger.h"
#include "Flight.h"


#define MAX_INPUT_LENGTH 50
#define AIRPORTFILENAME "Airports.csv"
#define AIRLINES_FILENAME "Airlines.csv"
#define PLANES_FILENAME "Planes.csv"
#define ROUTES_FILENAME "Routes.csv"
#define FLIGHTS_FILENAME "Flights.csv"

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void printMainMenu() {
    printf("Airport Management System Main Menu:\n");
    printf("1. Airport Menu\n");
    printf("2. Airline Menu\n");
    printf("3. Planes Menu\n");
    printf("4. Routes Menu\n");
    printf("5. Passengers Menu\n");
    printf("6. Flights Menu\n");
    printf("7. Exit\n");
    printf("Select an option: ");
}

void printAirportMenu() {
    printf("\nAirport Management System\n");
    printf("1. Add an airport\n");
    printf("2. Remove an airport\n");
    printf("3. View all airports\n");
    printf("4. View number of airports\n");
    printf("5. Get Airports in a city\n");
    printf("6. Get Airports in a Country\n");
    printf("7. Exit\n");
    printf("Select an option: ");
}
void printAirlinesMenu() {
    printf("\nAirline Management System\n");
    printf("1. Add an airline\n");
    printf("2. Remove an airline\n");
    printf("3. Find an airline by name\n");
    printf("4. Print all airlines\n");
    printf("5. Get number of airlines\n");
    printf("6. Exit\n");
    printf("Select an option: ");
}
void printPlanesMenu() {
    printf("\nPlanes Management System\n");
    printf("1. Add a plane\n");
    printf("2. Find a plane by name\n");
    printf("3. Print all planes\n");
    printf("4. Get number of planes\n");
    printf("5. Remove a plane\n");
    printf("6. Exit\n");
    printf("Select an option: ");
}
void printRoutesMenu() {
    printf("\nRoutes Management System\n");
    printf("1. Add a route\n");
    printf("2. Find a route\n");
    printf("3. Print all routes\n");
    printf("4. Get number of routes\n");
    printf("5. Remove a route\n");
    printf("6. Exit\n");
    printf("Select an option: ");
}
void printPassengerMenu() {
    printf("\nPassenger Management System\n");
    printf("1. Add a passenger\n");
    printf("2. Remove a passenger\n");
    printf("3. View all passengers\n");
    printf("4. Find a passenger by name\n");
    printf("5. Number of passengers\n");
    printf("6. Exit\n");
    printf("Select an option: ");
}
void printFlightsMenu() {
    printf("\nFlight Management System\n");
    printf("1. Add a Flight\n");
    printf("2. Remove a Flight\n");
    printf("3. Find a Flight by ID\n");
    printf("4. View all Flights\n");
    printf("5. View number of Flights\n");
    printf("6. Exit\n");
    printf("Select an option: ");
}

void airportMenu() {
    int choice;
    char name[50], city[50], country[50], iata[4], icao[4], dst[2];
    double latitude, longitude;
    int altitude, timezone;

    while (1) {
        printAirportMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter Airport details:\n");
                printf("Name: ");
                scanf(" %[^\n]", name); // Reads until encountering ^\n
                clearInputBuffer();
                printf("City: ");
                scanf("%s", city);
                printf("Country: ");
                scanf(" %[^\n]", country); // Reads until encountering ^\n
                clearInputBuffer();
                printf("IATA code: ");
                scanf("%s", iata);
                printf("ICAO code: ");
                scanf("%s", icao);
                printf("Latitude: ");
                scanf("%lf", &latitude);
                printf("Longitude: ");
                scanf("%lf", &longitude);
                printf("Altitude: ");
                scanf("%d", &altitude);
                printf("Timezone: ");
                scanf("%d", &timezone);
                printf("Daylight Saving Time (Y/N): ");
                scanf("%s", dst);

                struct Airport* newAirport = createAirport(name, city, country, iata, icao, latitude, longitude, altitude, timezone, dst);
                addAirportToFile(newAirport, AIRPORTFILENAME);
                printf("Airport added successfully.\n");
                break;

            case 2:
                printf("Enter name of Airport to remove: ");
                scanf(" %[^\n]", name);
                clearInputBuffer();
                removeAirportFromFile(name, AIRPORTFILENAME);
                printf("Airport removed successfully.\n");
                break;

            case 3:
                printAllAirports(AIRPORTFILENAME);
                break;

            case 4:
                printf("Number of Airports:\n");
                printNumberOfAirports(AIRPORTFILENAME);
                break;
            
			case 5:
                printf("Enter the city name to view airports: ");
                scanf(" %[^\n]", city);
                clearInputBuffer();

                printAirportsByCity(city, AIRPORTFILENAME);
                break;
                
            case 6:
                printf("Enter the country name to view airports: ");
                scanf(" %[^\n]", country);
                clearInputBuffer();

                printAirportsByCountry(country, AIRPORTFILENAME);
                break;
            
			case 7:
                printf("Exiting...\n");
                return;
            
            default:
                printf("Invalid choice.\n");
        }

        clearInputBuffer(); // Clear input buffer
    }
}

void airlineMenu() {
    int choice;
    char airlineName[50], airlineIATA[4], airlineICAO[4], airlineCountry[50], active;
    Airline *foundAirline;

    while (1) {
        printAirlinesMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter Airline details:\n");
                printf("Name: ");
                scanf(" %[^\n]", airlineName);
                clearInputBuffer();
                printf("IATA: ");
                scanf("%s", airlineIATA);
                printf("ICAO: ");
                scanf("%s", airlineICAO);
                printf("Country: ");
                scanf(" %[^\n]", airlineCountry);
                printf("Active (Y/N): ");
                scanf(" %c", &active);

                Airline *newAirline = createAirline(airlineName, airlineIATA, airlineICAO, airlineCountry, active);
                addAirlineToFile(newAirline, AIRLINES_FILENAME);
                printf("Airline added successfully.\n");
                break;
			
			case 2:
				printf("Enter name of Airline to remove: ");
                scanf(" %[^\n]s", airlineName);
                clearInputBuffer();
                removeAirlineFromFile(airlineName, AIRLINES_FILENAME);
                printf("Airline removed successfully.\n");
                break;
                
            case 3:
                printf("Enter Airline name to find: ");
                scanf(" %[^\n]", airlineName);
                clearInputBuffer();

                foundAirline = getAirlineByName(airlineName, AIRLINES_FILENAME);
                if (foundAirline != NULL) {
                    printf("Airline found:\n");
                    printf("Name: %s\nIATA: %s\nICAO: %s\nCountry: %s\nActive: %c\n",
                           foundAirline->name, foundAirline->IATA, foundAirline->ICAO, foundAirline->country, foundAirline->active);
                } else {
                    printf("Airline not found.\n");
                }
                break;

            case 4:
                printf("All Airlines:\n");
                printAllAirlines(AIRLINES_FILENAME);
                break;

            case 5:
                printf("Number of Airlines: %d\n", getNumberOfAirlines(AIRLINES_FILENAME));
                break;
            
			case 6:
                printf("Exiting...\n");
                return;

            default:
                printf("Invalid choice.\n");
        }

        clearInputBuffer(); // Clear input buffer
    }
}

void planesMenu() {
    int choice;
    char planeName[50];

    while (1) {
        printPlanesMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter Plane details:\n");
                printf("Name: ");
                scanf(" %[^\n]", planeName);
                clearInputBuffer();

                // Assuming IATA and ICAO are provided by the user here. You can modify this accordingly.
                char planeIATA[4], planeICAO[4];
                printf("IATA: ");
                scanf("%s", planeIATA);
                printf("ICAO: ");
                scanf("%s", planeICAO);

                Plane *newPlane = createPlane(planeName, planeIATA, planeICAO);
                addPlaneToFile(newPlane, PLANES_FILENAME);
                printf("Plane added successfully.\n");
                break;

            case 2:
                printf("Enter Plane name to find: ");
                scanf(" %[^\n]", planeName);
                clearInputBuffer();

                Plane *foundPlane = getPlaneByName(planeName, PLANES_FILENAME);
                if (foundPlane != NULL) {
                    printf("Plane found:\n");
                    printf("Name: %s\nIATA: %s\nICAO: %s\n",
                           foundPlane->name, foundPlane->IATA, foundPlane->ICAO);
                } else {
                    printf("Plane not found.\n");
                }
                break;

            case 3:
                printf("All Planes:\n");
                printAllPlanes(PLANES_FILENAME);
                break;

            case 4:
                printf("Number of Planes: %d\n", getNumberOfPlanes(PLANES_FILENAME));
                break;

            case 5:
                printf("Enter Plane name to remove: ");
                scanf(" %[^\n]", planeName);
                clearInputBuffer();
                removePlaneFromFile(planeName, PLANES_FILENAME);
                break;

            case 6:
                printf("Exiting...\n");
                return;

            default:
                printf("Invalid choice.\n");
        }

        clearInputBuffer(); // Clear input buffer
    }
}

void routesMenu() {
    int choice;
    
    char airline[50];


    while (1) {
        printf("\nRoutes Management System\n");
        printf("1. Add a route\n");
        printf("2. Find a route by it's details\n");
        printf("3. Print all routes\n");
        printf("4. Get number of routes\n");
        printf("5. Remove a route\n");
        printf("6. Exit\n");
        printf("Select an option: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter Route details:\n");
                printf("Airline: ");
                scanf(" %[^\n]", airline);
                clearInputBuffer();

                char departure[4], arrival[4];
                int plane;
                printf("Departure: ");
                scanf("%s", departure);
                printf("Arrival: ");
                scanf("%s", arrival);
                printf("Plane: ");
                scanf("%d", &plane);

                Route *newRoute = createRoute(airline, departure, arrival, plane);
                addRouteToFile(newRoute, ROUTES_FILENAME);
                printf("Route added successfully.\n");
                break;

			case 2:
			    printf("Enter Route details to find route:\n");
			    printf("Airline: ");
			    scanf(" %[^\n]", airline);
			    printf("Departure: ");
			    scanf("%s", departure);
			    printf("Arrival: ");
			    scanf("%s", arrival);
			    printf("Plane: ");
			    scanf("%d", &plane);
			    clearInputBuffer();
			
			    Route *foundRoute = getRouteByAttributes(airline, departure, arrival, plane, ROUTES_FILENAME);
			    if (foundRoute != NULL) {
			        printf("Route found:\n");
			    } else {
			        printf("Route not found.\n");
			    }
			    break;

            case 3:
                printf("All Routes:\n");
                printAllRoutes(ROUTES_FILENAME);
                break;

            case 4:
                printf("Number of Routes: %d\n", getNumberOfRoutes(ROUTES_FILENAME));
                break;

            case 5:
			    printf("Enter Route details for removal:\n");
			    printf("Airline: ");
			    scanf(" %[^\n]", airline);
			    printf("Departure: ");
			    scanf("%s", departure);
			    printf("Arrival: ");
			    scanf("%s", arrival);
			    printf("Plane: ");
			    scanf("%d", &plane);
			    clearInputBuffer();
			    
			    removeRouteFromFile(airline, departure, arrival, plane, ROUTES_FILENAME);
			    break;

            case 6:
                printf("Exiting...\n");
                return;

            default:
                printf("Invalid choice.\n");
        }

        clearInputBuffer(); // Clear input buffer
    }
}

void passengersMenu() {
    int choice;
    char passengerName[MAX_INPUT_LENGTH];
    char passportNumber[MAX_INPUT_LENGTH];
    char nationality[MAX_INPUT_LENGTH];
    char flightCode[MAX_INPUT_LENGTH];
    Passenger *foundPassenger;

    while (1) {
        printPassengerMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter Passenger details:\n");
                printf("Name: ");
                scanf(" %[^\n]", passengerName);
                clearInputBuffer();
                printf("Passport Number: ");
                scanf("%s", passportNumber);
                printf("Nationality: ");
                scanf("%s", nationality);
                printf("Flight Code: ");
                scanf("%s", flightCode);

                Passenger *newPassenger = createPassenger(passengerName, passportNumber, nationality, flightCode);
                addPassengerToFile(newPassenger, "Passengers.csv");
                printf("Passenger added successfully.\n");
                break;

            case 2:
                printf("Enter name of Passenger to remove: ");
                scanf(" %[^\n]", passengerName);
                clearInputBuffer();
                removePassengerFromFile(passengerName, "Passengers.csv");
                printf("Passenger removed successfully.\n");
                break;

            case 3:
                printf("All Passengers:\n");
                printAllPassengers("Passengers.csv");
                break;

            case 4:
                printf("Enter Passenger name to find: ");
                scanf(" %[^\n]", passengerName);
                clearInputBuffer();
                foundPassenger = getPassengerByName(passengerName, "Passengers.csv");
                if (foundPassenger != NULL) {
                    printf("Passenger found:\n");
                    printf("Name: %s\nPassport Number: %s\nNationality: %s\nFlight Code: %s\n",
                           foundPassenger->name, foundPassenger->passportNumber, foundPassenger->nationality, foundPassenger->flightCode);
                } else {
                    printf("Passenger not found.\n");
                }
                break;

            case 5:
                printf("Number of Passengers: %d\n", getNumberOfPassengers("Passengers.csv"));
                break;

            case 6:
                printf("Exiting...\n");
                return;

            default:
                printf("Invalid choice.\n");
        }

        clearInputBuffer(); // Clear input buffer
    }
}

void flightsMenu() {
    int choice;
    char flightID[50], airline[50], departure[50], arrival[50], plane[50];
    Flight *foundFlight;

    while (1) {
        printFlightsMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter Flight details:\n");
                printf("ID: ");
                scanf(" %[^\n]", flightID);
                clearInputBuffer();
                printf("Airline: ");
                scanf(" %[^\n]", airline);
                printf("Departure: ");
                scanf(" %[^\n]", departure);
                printf("Arrival: ");
                scanf(" %[^\n]", arrival);
                printf("Plane: ");
                scanf(" %[^\n]", plane);

                Flight *newFlight = createFlight(flightID, airline, departure, arrival, plane);
                addFlightToFile(newFlight, FLIGHTS_FILENAME);
                printf("Flight added successfully.\n");
                break;

            case 2:
                printf("Enter ID of Flight to remove: ");
                scanf(" %[^\n]", flightID);
                clearInputBuffer();
                removeFlightFromFile(flightID, FLIGHTS_FILENAME);
                printf("Flight removed successfully.\n");
                break;

            case 3:
                printf("Enter Flight ID to find: ");
                scanf(" %[^\n]", flightID);
                clearInputBuffer();

                foundFlight = getFlightByID(flightID, FLIGHTS_FILENAME);
                if (foundFlight != NULL) {
                    printf("Flight found:\n");
                    printf("ID: %s\nAirline: %s\nDeparture: %s\nArrival: %s\nPlane: %s\n",
                           foundFlight->flightID, foundFlight->airline, foundFlight->departure, foundFlight->arrival, foundFlight->plane);
                    freeFlight(foundFlight);
                } else {
                    printf("Flight not found.\n");
                }
                break;

            case 4:
                printf("All Flights:\n");
                printAllFlights(FLIGHTS_FILENAME);
                break;

            case 5:
                printf("Number of Flights: %d\n", getNumberOfFlights( FLIGHTS_FILENAME));
                break;

            case 6:
                printf("Exiting...\n");
                return;

            default:
                printf("Invalid choice.\n");
        }

        clearInputBuffer(); // Clear input buffer
    }
}

void MainMenu() {
    int choice;

    while (1) {
        printMainMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (choice) {
            case 1:
                airportMenu();
                break;
            case 2:
                airlineMenu();
                break;
            case 3:
                planesMenu();
                break;
            case 4:
                routesMenu();
                break;
            case 5:
                passengersMenu();
                break;
            case 6:
                flightsMenu();
                break;
            case 7:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }
}

int main() {
    
	MainMenu();
	return 0;
}

