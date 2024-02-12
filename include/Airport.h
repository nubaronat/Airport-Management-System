#ifndef AIRPORT_H
#define AIRPORT_H

typedef struct Airport {
    char name[50]; // Name of the airport
    char city[50]; // City of the airport
    char country[50]; // Country of the airport
    char iata[4]; // IATA code of the airport
    char icao[4]; // ICAO code of the airport
    double latitude; // Latitude of the airport
    double longitude; // Longitude of the airport
    int altitude; // Altitude of the airport
    int timezone; // Timezone of the airport
    char dst[2]; // Daylight saving time of the airport
} Airport;

void removeAirportFromFile(char* airportName, char* filename);
struct Airport* createAirport(char* name, char* city, char* country, char* iata, char* icao, double latitude, double longitude, int altitude, int timezone, char* dst);
void freeAirport(struct Airport* airport, char* filename);
void addAirportToFile(struct Airport* airport, char* filename);
void printAllAirports(char* filename);
void printNumberOfAirports(char* filename);
void printAirportsByCity(const char *city, const char *filename);
void printAirportsByCountry(const char *country, const char *filename);

#endif /* AIRPORT_H */

