#ifndef FLIGHT_H
#define FLIGHT_H

typedef struct {
    char *flightID;
    char *airline;
    char *departure;
    char *arrival;
    char *plane;
} Flight;

// Function declarations
Flight *createFlight(const char *flightID, const char *airline, const char *departure, const char *arrival, const char *plane);
void freeFlight(Flight *flight);
void addFlightToFile(const Flight *flight, const char *filename);
void removeFlightFromFile(const char *flightID, const char *filename);
Flight *getFlightByID(const char *flightID, const char *filename);
void printAllFlights(const char *filename);
int getNumberOfFlights(const char *filename);
void printNumberOfFlights(const char *filename);

#endif /* FLIGHT_H */

