#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Plane.h"

Plane *createPlane(const char *name, const char *IATA, const char *ICAO) {
    Plane *newPlane = (Plane *)malloc(sizeof(Plane));
    if (newPlane == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    newPlane->name = strdup(name);
    newPlane->IATA = strdup(IATA);
    newPlane->ICAO = strdup(ICAO);

    return newPlane;
}

void freePlane(Plane *plane) {
    free(plane->name);
    free(plane->IATA);
    free(plane->ICAO);
    free(plane);
}

void addPlaneToFile(const Plane *plane, const char *filename) {
    FILE *file = fopen(filename, "a");
    if (file != NULL) {
        fprintf(file, "%s,%s,%s\n", plane->name, plane->IATA, plane->ICAO);
        fclose(file);
    } else {
        printf("Error opening file for appending.\n");
    }
}

Plane *getPlaneByName(const char *name, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        char line[MAX_LINE_LENGTH];
        while (fgets(line, sizeof(line), file) != NULL) {
            char *token;
            token = strtok(line, ",");
            if (strcmp(token, name) == 0) {
                Plane *foundPlane = createPlane(token, strtok(NULL, ","), strtok(NULL, ","));
                fclose(file);
                return foundPlane;
            }
        }
        fclose(file);
    } else {
        printf("Error opening file for reading.\n");
    }
    return NULL;
}

void printAllPlanes(const char *filename) {
    FILE *file = fopen(filename, "r");
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

int getNumberOfPlanes(const char *filename) {
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

void printNumberOfPlanes(const char *filename) {
    int count = getNumberOfPlanes(filename);
    printf("Number of Planes: %d\n", count);
}

void removePlaneFromFile(char *planeName, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
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
            // Check if the line contains the plane to be removed
            if (strstr(line, planeName) == NULL) {
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
            printf("Plane '%s' not found in the file.\n", planeName);
        } else {
            printf("Plane '%s' removed from the file.\n", planeName);
        }
    } else {
        printf("Error opening file for reading.\n");
    }
}

