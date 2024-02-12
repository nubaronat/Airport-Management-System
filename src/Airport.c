#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Airport.h"

#define MAX_LINE_LENGTH 256

void removeAirportFromFile(char* airportName, char* filename) {
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        char line[MAX_LINE_LENGTH];
        char tempFilename[] = "temp.csv"; // Temporary file to store updated content

        FILE* tempFile = fopen(tempFilename, "w");
        if (tempFile == NULL) {
            printf("Error creating temporary file.\n");
            fclose(file);
            return;
        }

        int found = 0;
        while (fgets(line, sizeof(line), file) != NULL) {
            // Check if the line contains the airport to be removed
            if (strstr(line, airportName) == NULL) {
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
            printf("Airport '%s' not found in the file.\n", airportName);
        } else {
            printf("Airport '%s' removed from the file.\n", airportName);
        }
    } else {
        printf("Error opening file for reading.\n");
    }
}

struct Airport* createAirport(char* name, char* city, char* country, char* iata, char* icao, double latitude, double longitude, int altitude, int timezone, char* dst) {
    struct Airport* newAirport = (struct Airport*)malloc(sizeof(struct Airport));
    if (newAirport != NULL) {
        strncpy(newAirport->name, name, 50);
        strncpy(newAirport->city, city, 50);
        strncpy(newAirport->country, country, 50);
        strncpy(newAirport->iata, iata, 4);
        strncpy(newAirport->icao, icao, 4);
        newAirport->latitude = latitude;
        newAirport->longitude = longitude;
        newAirport->altitude = altitude;
        newAirport->timezone = timezone;
        strncpy(newAirport->dst, dst, 2);
    }
    return newAirport;
}

void freeAirport(struct Airport* airport, char* filename) {
    removeAirportFromFile(airport->name, filename);
    free(airport);
}

void addAirportToFile(struct Airport* airport, char* filename) {
    FILE* file = fopen(filename, "a");
    if (file != NULL) {
        fprintf(file, "%s,%s,%s,%s,%s,%.6f,%.6f,%d,%d,%s\n", airport->name, airport->city, airport->country,
                airport->iata, airport->icao, airport->latitude, airport->longitude, airport->altitude,
                airport->timezone, airport->dst);
        fclose(file);
    } else {
        printf("Error opening file for writing.\n");
    }
}

void printAllAirports(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        char line[MAX_LINE_LENGTH];
        while (fgets(line, sizeof(line), file) != NULL) {
            printf("%s", line);
        }
        fclose(file);
    } else {
        printf("Error opening file for reading.\n");
    }
}

void printNumberOfAirports(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        int count = 0;
        char line[MAX_LINE_LENGTH];
        while (fgets(line, sizeof(line), file) != NULL) {
            count++;
        }
        fclose(file);
        printf("Number of Airports: %d\n", count);
    } else {
        printf("Error opening file for reading.\n");
    }
}

void printAirportsByCity(const char *city, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        char line[MAX_LINE_LENGTH];
        printf("Airports in %s:\n", city);
        while (fgets(line, sizeof(line), file) != NULL) {
            char *token;
            char *lineCopy = strdup(line); // Create a copy to preserve the original line
            token = strtok(lineCopy, ",");
            char airportCity[100];

            // Skip columns until reaching the City column
            int i;
            for (i = 1; i < 2; ++i) {
                token = strtok(NULL, ",");
            }
            strcpy(airportCity, token); // Copy the City column value

            // Check if the city matches the specified city
            if (strcmp(airportCity, city) == 0) {
                printf("%s", line); // Print the entire line containing airport details
            }
            free(lineCopy);
        }
        fclose(file);
    } else {
        printf("Error opening file for reading.\n");
    }
}

void printAirportsByCountry(const char *country, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        char line[MAX_LINE_LENGTH];
        printf("Airports in %s:\n", country);
        while (fgets(line, sizeof(line), file) != NULL) {
            char *token;
            char *lineCopy = strdup(line); // Create a copy to preserve the original line
            token = strtok(lineCopy, ",");
            char airportCountry[100];

            // Skip columns until reaching the Country column
            int i;
            for (i = 1; i < 3; ++i) {
                token = strtok(NULL, ",");
            }
            strcpy(airportCountry, token); // Copy the Country column value

            // Check if the country matches the specified country
            if (strcmp(airportCountry, country) == 0) {
                printf("%s", line); // Print the entire line containing airport details
            }
            free(lineCopy);
        }
        fclose(file);
    } else {
        printf("Error opening file for reading.\n");
    }
}
