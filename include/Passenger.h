#ifndef PASSENGER_H
#define PASSENGER_H

typedef struct Passenger{
    char *name;
    char *passportNumber;
    char *nationality;
    char *flightCode;
} Passenger;

Passenger *createPassenger(const char *name, const char *passportNumber, const char *nationality, const char *flightCode);
void freePassenger(Passenger *passenger);
void removePassengerFromFile(const char *passengerName, const char *filename);
void addPassengerToFile(const Passenger *passenger, const char *filename);
Passenger *getPassengerByName(const char *name, const char *filename);
void printAllPassengers(const char *filename);
int getNumberOfPassengers(const char *filename);
void printNumberOfPassengers(const char *filename);

#endif /* PASSENGER_H */

