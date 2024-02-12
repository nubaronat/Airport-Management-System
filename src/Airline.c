#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Airline.h"

#define MAX_LINE_LENGTH 100

void removeAirlineFromFile(char* airlineName, char* filename) {
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
            // Check if the line contains the airline to be removed
            if (strstr(line, airlineName) == NULL) {
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
            printf("Airline '%s' not found in the file.\n", airlineName);
        } else {
            printf("Airline '%s' removed from the file.\n", airlineName);
        }
    } else {
        printf("Error opening file for reading.\n");
    }
}

Airline *createAirline(const char *name, const char *IATA, const char *ICAO, const char *country, char active) {
    Airline *newAirline = (Airline *)malloc(sizeof(Airline));
    if (newAirline == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    newAirline->name = strdup(name);
    newAirline->IATA = strdup(IATA);
    newAirline->ICAO = strdup(ICAO);
    newAirline->country = strdup(country);
    newAirline->active = active;

    return newAirline;
}

void freeAirline(Airline *airline) {
    free(airline->name);
    free(airline->IATA);
    free(airline->ICAO);
    free(airline->country);
    free(airline);
}

void addAirlineToFile(const Airline *airline, const char *filename) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s,%s,%s,%s,%c\n", airline->name, airline->IATA, airline->ICAO, airline->country, airline->active);

    fclose(file);
}

Airline *getAirlineByName(const char *name, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        if (strcmp(token, name) == 0) {
            char *IATA = strtok(NULL, ",");
            char *ICAO = strtok(NULL, ",");
            char *country = strtok(NULL, ",");
            char active = strtok(NULL, ",")[0]; // Get the first character as active

            fclose(file);

            return createAirline(name, IATA, ICAO, country, active);
        }
    }

    fclose(file);
    return NULL; // Airline not found
}

void printAllAirlines( const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    printf("Airlines:\n");
    while (fgets(line, sizeof(line), file)) {
        char *name = strtok(line, ",");
        char *IATA = strtok(NULL, ",");
        char *ICAO = strtok(NULL, ",");
        char *country = strtok(NULL, ",");
        char active = strtok(NULL, ",")[0]; // Get the first character as active

        printf("Name: %s, IATA: %s, ICAO: %s, Country: %s, Active: %c\n", name, IATA, ICAO, country, active);
    }

    fclose(file);
}

int getNumberOfAirlines( const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    int numberOfAirlines = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        numberOfAirlines++;
    }

    fclose(file);
    return numberOfAirlines;
}

void printNumberOfAirlines(const char* filename) {
    int numAirlines = getNumberOfAirlines(filename);
    printf("Number of Airlines: %d\n", numAirlines);
}


