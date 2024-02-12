#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Passenger.h"

#define MAX_LINE_LENGTH 1024

Passenger *createPassenger(const char *name, const char *passportNumber, const char *nationality, const char *flightCode) {
    Passenger *newPassenger = (Passenger *)malloc(sizeof(Passenger));
    if (newPassenger == NULL) {
        printf("Memory allocation failed for Passenger.\n");
        return NULL;
    }

    newPassenger->name = strdup(name);
    newPassenger->passportNumber = strdup(passportNumber);
    newPassenger->nationality = strdup(nationality);
    newPassenger->flightCode = strdup(flightCode);

    return newPassenger;
}

void freePassenger(Passenger *passenger) {
    if (passenger != NULL) {
        free(passenger->name);
        free(passenger->passportNumber);
        free(passenger->nationality);
        free(passenger->flightCode);
        free(passenger);
    }
}

void removePassengerFromFile(const char *passengerName, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        char line[MAX_LINE_LENGTH];
        char tempFilename[] = "temp_passengers.csv"; // Temporary file to store updated content

        FILE *tempFile = fopen(tempFilename, "w");
        if (tempFile == NULL) {
            printf("Error creating temporary file.\n");
            fclose(file);
            return;
        }

        int found = 0;
        while (fgets(line, sizeof(line), file) != NULL) {
            char *token;
            char *lineCopy = strdup(line);
            token = strtok(lineCopy, ",");

            // Check if the line contains the passenger to be removed
            if (strcmp(token, passengerName) != 0) {
                fputs(line, tempFile); // If not, write the line to the temporary file
            } else {
                found = 1;
            }
            free(lineCopy);
        }

        fclose(file);
        fclose(tempFile);

        // Remove the original file and rename the temporary file
        if (remove(filename) != 0) {
            printf("Error removing original file.\n");
            return;
        }

        if (rename(tempFilename, filename) != 0) {
            printf("Error renaming temporary file.\n");
            return;
        }

        if (!found) {
            printf("Passenger '%s' not found in the file.\n", passengerName);
        } else {
            printf("Passenger '%s' removed from the file.\n", passengerName);
        }
    } else {
        printf("Error opening file for reading.\n");
    }
}

void addPassengerToFile(const Passenger *passenger, const char *filename) {
    FILE *file = fopen(filename, "a");
    if (file != NULL && passenger != NULL) {
        fprintf(file, "%s,%s,%s,%s\n", passenger->name, passenger->passportNumber, passenger->nationality, passenger->flightCode);
        fclose(file);
    } else {
        printf("Error opening file or invalid passenger data.\n");
    }
}

Passenger *getPassengerByName(const char *name, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        char line[MAX_LINE_LENGTH];
        while (fgets(line, sizeof(line), file) != NULL) {
            char *token;
            char *lineCopy = strdup(line);
            token = strtok(lineCopy, ",");

            // Check if the name matches
            if (strcmp(token, name) == 0) {
                char *passportNumber = strtok(NULL, ",");
                char *nationality = strtok(NULL, ",");
                char *flightCode = strtok(NULL, ",\n");

                Passenger *foundPassenger = createPassenger(name, passportNumber, nationality, flightCode);
                free(lineCopy);
                fclose(file);
                return foundPassenger;
            }
            free(lineCopy);
        }
        fclose(file);
    } else {
        printf("Error opening file for reading.\n");
    }
    return NULL;
}

void printAllPassengers(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        char line[MAX_LINE_LENGTH];
        printf("All Passengers:\n");
        while (fgets(line, sizeof(line), file) != NULL) {
            printf("%s", line); // Print the entire line containing passenger details
        }
        fclose(file);
    } else {
        printf("Error opening file for reading.\n");
    }
}

int getNumberOfPassengers(const char *filename) {
    int count = 0;
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        char line[MAX_LINE_LENGTH];
        while (fgets(line, sizeof(line), file) != NULL) {
            count++;
        }
        fclose(file);
    } else {
        printf("Error opening file for reading.\n");
    }
    return count;
}

void printNumberOfPassengers(const char *filename) {
    int count = getNumberOfPassengers(filename);
    if (count >= 0) {
        printf("Number of Passengers: %d\n", count);
    } else {
        printf("Failed to get the number of passengers.\n");
    }
}

