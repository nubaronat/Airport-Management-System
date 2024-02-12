#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Route.h"

Route *createRoute(const char *airline, const char *departure, const char *arrival, int plane) {
    Route *newRoute = (Route *)malloc(sizeof(Route));
    if (newRoute == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    newRoute->airline = strdup(airline);
    newRoute->departure = strdup(departure);
    newRoute->arrival = strdup(arrival);
    newRoute->plane = plane;

    return newRoute;
}

void freeRoute(Route *route) {
    free(route->airline);
    free(route->departure);
    free(route->arrival);
    free(route);
}

void addRouteToFile(const Route *route, const char *filename) {
    FILE *file = fopen(filename, "a");
    if (file != NULL) {
        fprintf(file, "%s,%s,%s,%d\n", route->airline, route->departure, route->arrival, route->plane);
        fclose(file);
    } else {
        printf("Error opening file for appending.\n");
    }
}

Route *getRouteByAttributes(const char *airline, const char *departure, const char *arrival, int plane, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        char line[MAX_LINE_LENGTH];
        while (fgets(line, sizeof(line), file) != NULL) {
            char *token;
            char *lineCopy = strdup(line); // Create a copy to preserve the original line
            token = strtok(lineCopy, ",");
            if (strcmp(token, airline) == 0) {
                char *depart = strtok(NULL, ",");
                char *arrive = strtok(NULL, ",");
                int planeVal = atoi(strtok(NULL, ",\n"));

                // Check if all attributes match
                if (strcmp(depart, departure) == 0 && strcmp(arrive, arrival) == 0 && planeVal == plane) {
                    Route *foundRoute = createRoute(token, depart, arrive, planeVal);
                    fclose(file);
                    free(lineCopy);
                    return foundRoute;
                }
            }
            free(lineCopy);
        }
        fclose(file);
    } else {
        printf("Error opening file for reading.\n");
    }
    return NULL;
}

void printAllRoutes(const char *filename) {
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

int getNumberOfRoutes(const char *filename) {
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

void printNumberOfRoutes(const char *filename) {
    int count = getNumberOfRoutes(filename);
    printf("Number of Routes: %d\n", count);
}

void removeRouteFromFile(const char *airline, const char *departure, const char *arrival, int plane, const char *filename) {
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
            char *token;
            char *lineCopy = strdup(line); // Create a copy to preserve the original line
            token = strtok(lineCopy, ",");
            if (strcmp(token, airline) == 0) {
                char *depart = strtok(NULL, ",");
                char *arrive = strtok(NULL, ",");
                int planeVal = atoi(strtok(NULL, ",\n"));

                // Check if all attributes match for removal
                if (strcmp(depart, departure) == 0 && strcmp(arrive, arrival) == 0 && planeVal == plane) {
                    found = 1;
                    continue; // Skip writing this line to the temporary file
                }
            }
            // Write lines not matching the removal criteria to the temporary file
            fputs(line, tempFile);
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
            printf("Route not found for removal.\n");
        } else {
            printf("Route removed successfully.\n");
        }
    } else {
        printf("Error opening file for reading.\n");
    }
}


