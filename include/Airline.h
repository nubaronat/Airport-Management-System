#ifndef AIRLINE_H
#define AIRLINE_H

typedef struct {
    char *name;
    char *IATA;
    char *ICAO;
    char *country;
    char active;
} Airline;

// Function declarations
void removeAirlineFromFile(char* airlineName, char* filename);
Airline *createAirline(const char *name, const char *IATA, const char *ICAO, const char *country, char active);
void freeAirline(Airline *airline);
void addAirlineToFile(const Airline *airline, const char *filename);
Airline *getAirlineByName(const char *name, const char *filename);
void printAllAirlines(const char* filename); // Function declaration for printing all airlines
int getNumberOfAirlines(const char* filename); // Function declaration for getting number of airlines
void printNumberOfAirlines(const char* filename); // Function declaration for printing number of airlines

#endif /* AIRLINE_H */

