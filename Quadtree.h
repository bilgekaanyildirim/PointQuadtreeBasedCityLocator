//
// Created by Bilge Kaan Yıldırım on 6.11.2024.
//

#ifndef PROJECTHW2_QUADTREE_H
#define PROJECTHW2_QUADTREE_H

#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Enumeration to represent the four directions in a quadtree (Southeast, Southwest, Northeast, Northwest)
enum Directions
{
    SE,
    SW,
    NE,
    NW
};

// Struct to represent a City in the quadtree
struct City
{
    string name;   // Name of the city
    int x;         // X-coordinate of the city
    int y;         // Y-coordinate of the city

    // Pointers to the four quadrants (subtrees) of the city
    City * SE;
    City * SW;
    City * NE;
    City * NW;

    // Default constructor to initialize a City object with default values
    City()
    {
        name = "";
        x = -1;
        y = -1;
        SE = nullptr;
        SW = nullptr;
        NE = nullptr;
        NW = nullptr;
    }

    // Constructor to initialize a City object with specific values
    City(string cityName, int coordinateX, int coordinateY)
    {
        name = cityName;
        x = coordinateX;
        y = coordinateY;
        SE = nullptr;
        SW = nullptr;
        NE = nullptr;
        NW = nullptr;
    }
};

// Class to represent a Quadtree
class Quadtree
{
private:
    City * root; // Root of the quadtree

    // Helper function to print the quadtree (recursively) to an output file
    void PrettyPrint(City * root, ofstream & output);

    // Helper function to recursively delete all elements in the quadtree
    void MakeEmpty(City * & root);

    // Compares given coordinates with the coordinates of a city and determines the direction
    Directions PointCompare(const int & coordinateX, const int & coordinateY, City * root);

    // Helper function to insert a city into the quadtree (recursively)
    void Insert(const string & cityName, const int & coordinateX, const int & coordinateY, City * & root);

    // Helper function to search for cities within a specified radius from a point (recursively)
    void Search(const int & coordinateX, const int & coordinateY, const int & radius,
                City * & root, vector<string> & visitedCities, vector<string> & citiesInCircle);

    // Calculates the Euclidean distance between two points
    double CalculateDistance(const int & rootCoordinateX, const int & rootCoordinateY,
                             const int & circleCoordinateX, const int & circleCoordinateY);

public:
    Quadtree(); // Default constructor to initialize the quadtree
    ~Quadtree(); // Destructor to clean up dynamically allocated memory

    // Public function to print the entire quadtree to an output file
    void Print(ofstream & output);

    // Public function to insert a city into the quadtree
    void Insert(const string & cityName, const int & coordinateX, const int & coordinateY);

    // Public function to search for cities within a radius from a point
    void Search(const int &coordinateX, const int &coordinateY, const int &radius,
                vector<string> & visitedCities, vector<string> & citiesInCircle);
};

#endif //PROJECTHW2_QUADTREE_H
