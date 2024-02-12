#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Flight.h"

#define MAX_LINE_LENGTH 256

Flight *createFlight(const char *flightID, const char *airline, const char *departure, const char *arrival, const char *plane) {
    Flight *newFlight = (Flight *)malloc(sizeof(Flight));
    if (newFlight == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    newFlight->flightID = strdup(flightID);
    newFlight->airline = strdup(airline);
    newFlight->departure = strdup(departure);
    newFlight->arrival = strdup(arrival);
    newFlight->plane = strdup(plane);

    return newFlight;
}

void freeFlight(Flight *flight) {
    if (flight != NULL) {
        free(flight->flightID);
        free(flight->airline);
        free(flight->departure);
        free(flight->arrival);
        free(flight->plane);
        free(flight);
    }
}

void addFlightToFile(const Flight *flight, const char *filename) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "%s,%s,%s,%s,%s\n", flight->flightID, flight->airline, flight->departure, flight->arrival, flight->plane);
    fclose(file);
}

void removeFlightFromFile(const char *flightID, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[MAX_LINE_LENGTH];
    char tempFilename[] = "temp.csv"; // Temporary file to store updated content

    FILE *tempFile = fopen(tempFilename, "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }

    int found = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        // Check if the line contains the flight to be removed
        if (strstr(line, flightID) == NULL) {
            // If not, write the line to the temporary file
            fputs(line, tempFile);
        } else {
            found = 1;
        }
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
        printf("Flight '%s' not found in the file.\n", flightID);
    } else {
        printf("Flight '%s' removed from the file.\n", flightID);
    }
}

Flight *getFlightByID(const char *flightID, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return NULL;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, flightID) != NULL) {
            char *token = strtok(line, ",");
            if (strcmp(token, flightID) == 0) {
                char *airline = strtok(NULL, ",");
                char *departure = strtok(NULL, ",");
                char *arrival = strtok(NULL, ",");
                char *plane = strtok(NULL, ",");

                Flight *foundFlight = createFlight(flightID, airline, departure, arrival, plane);
                fclose(file);
                return foundFlight;
            }
        }
    }

    fclose(file);
    return NULL;
}

void printAllFlights(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }

    fclose(file);
}

int getNumberOfFlights(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return -1;
    }

    int count = 0;
    char c;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            count++;
        }
    }

    fclose(file);
    return count;
}

void printNumberOfFlights(const char *filename) {
    int count = getNumberOfFlights(filename);
    if (count != -1) {
        printf("Number of Flights: %d\n", count);
    }
}


