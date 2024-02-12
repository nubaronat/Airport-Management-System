#ifndef ROUTE_H
#define ROUTE_H

#define MAX_LINE_LENGTH 256

typedef struct {
    char *airline;
    char *departure;
    char *arrival;
    int plane;
} Route;

Route *createRoute(const char *airline, const char *departure, const char *arrival, int plane);
void freeRoute(Route *route);
void addRouteToFile(const Route *route, const char *filename);
Route *getRouteByAttributes(const char *airline, const char *departure, const char *arrival, int plane, const char *filename);
void printAllRoutes(const char *filename);
int getNumberOfRoutes(const char *filename);
void printNumberOfRoutes(const char *filename);
void removeRouteFromFile(const char *airline, const char *departure, const char *arrival, int plane, const char *filename);

#endif /* ROUTE_H */

