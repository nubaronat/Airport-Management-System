#ifndef PLANES_H
#define PLANES_H

#define MAX_LINE_LENGTH 256

typedef struct {
    char *name;
    char *IATA;
    char *ICAO;
} Plane;

Plane *createPlane(const char *name, const char *IATA, const char *ICAO);
void freePlane(Plane *plane);
void addPlaneToFile(const Plane *plane, const char *filename);
Plane *getPlaneByName(const char *name, const char *filename);
void printAllPlanes(const char *filename);
int getNumberOfPlanes(const char *filename);
void printNumberOfPlanes(const char *filename);
void removePlaneFromFile(char *planeName, const char *filename);

#endif /* PLANES_H */

