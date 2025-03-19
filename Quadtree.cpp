//
// Created by Bilge Kaan Yıldırım on 6.11.2024.
//

#include "Quadtree.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

// Default constructor for Quadtree
Quadtree::Quadtree()
{
    root = nullptr;
}

// Destructor for Quadtree
Quadtree::~Quadtree()
{
    MakeEmpty(root);
}

// Recursively frees memory for all nodes in the tree
void Quadtree::MakeEmpty(City * & root)
{
    if (root == nullptr) // Base case: if the node is null, return
        return;

    // Recursively delete all child nodes
    MakeEmpty(root->NE);
    MakeEmpty(root->NW);
    MakeEmpty(root->SE);
    MakeEmpty(root->SW);

    // Delete the current node
    delete root;
    root = nullptr;
}

// Helper function to pretty-print the tree in a structured format
void Quadtree::PrettyPrint(City *root, ofstream & output)
{
    if (root != nullptr)    // If the current node exists
    {
        output << root->name;   // Output the city's name
        /*
        cout << endl << "-------------------" << endl;

        if (root->NW != nullptr)
            cout << "(Norht west: " << root->NW->name;
        if (root->NE != nullptr)
            cout << ", Norht east: " << root->NE->name;
        if (root->SW != nullptr)
            cout << ", south west: " << root->SW->name;
        if (root->SE != nullptr)
            cout << ", south east: " << root->SE->name << ")";

        cout << endl;
        */
        //cout << " " << root->x << " " << root->y;
        output << endl;

        // Recursively print all child nodes in order (SE, SW, NE, NW)
        PrettyPrint(root->SE, output);
        PrettyPrint(root->SW, output);
        PrettyPrint(root->NE, output);
        PrettyPrint(root->NW, output);
    }
}

// Public interface to print the entire tree
void Quadtree::Print(ofstream & output)
{
    PrettyPrint(root, output);
}

// Public interface to insert a new city into the Quadtree
void Quadtree::Insert(const string & cityName, const int & coordinateX, const int & coordinateY)
{
    Insert(cityName, coordinateX, coordinateY, root);
}

// Recursive function to insert a new city into the tree
void Quadtree::Insert(const string & cityName, const int & coordinateX, const int & coordinateY, City *&root)
{
    if (root == nullptr) // If the current node is empty, create a new city node
    {
        root = new City(cityName, coordinateX, coordinateY);
    }
    else if (root->x == coordinateX && root->y == coordinateY) // If coordinates match an existing node, do nothing
    {
        return;
    }
    else
    {
        // Determine which quadrant the new city belongs to
        Directions direction = PointCompare(coordinateX, coordinateY, root);

        // Insert the city into the appropriate quadrant
        if (direction == SE)
        {
            Insert(cityName, coordinateX, coordinateY, root->SE);
        }
        else if (direction == SW)
        {
            Insert(cityName, coordinateX, coordinateY, root->SW);
        }
        else if (direction == NE)
        {
            Insert(cityName, coordinateX, coordinateY, root->NE);
        }
        else
        {
            Insert(cityName, coordinateX, coordinateY, root->NW);
        }
    }
}

// Public interface to search for cities within a radius
void Quadtree::Search(const int &coordinateX, const int &coordinateY, const int &radius, vector<string> & visitedCities, vector<string> & citiesInCircle)
{
    Search(coordinateX, coordinateY, radius, root, visitedCities, citiesInCircle);
}

// Recursive function to search for cities within a given radius
void Quadtree::Search(const int & coordinateX, const int & coordinateY, const int & radius, City * & root, vector<string> & visitedCities, vector<string> & citiesInCircle)
{
    if (root == nullptr) // Base case: if node is null, return
        return;

    visitedCities.push_back(root->name); // Mark the current city as visited

    //cout << root->name << " " << root->x << " " << root->y << endl;

    //Checks circle
    if (CalculateDistance(root->x, root->y, coordinateX, coordinateY) <= radius)
    {
        //Append
        citiesInCircle.push_back(root->name);
        //Search in all directions
        Search(coordinateX, coordinateY, radius, root->SE, visitedCities, citiesInCircle);
        Search(coordinateX, coordinateY, radius, root->SW, visitedCities, citiesInCircle);
        Search(coordinateX, coordinateY, radius, root->NE, visitedCities, citiesInCircle);
        Search(coordinateX, coordinateY, radius, root->NW, visitedCities, citiesInCircle);
    }
    else
    {
        int upperHorizontalLine = coordinateY + radius;
        int lowerHorizontalLine = coordinateY - radius;
        int leftVerticalLine = coordinateX - radius;
        int rightVerticalLine = coordinateX + radius;

        Directions direction = PointCompare(coordinateX, coordinateY, root);
        Directions newDirection;

        //Left upper area
        if (direction == SE)
        {
            newDirection = PointCompare(leftVerticalLine, upperHorizontalLine, root);

            //Area 1
            if (newDirection == SE)
            {
                Search(coordinateX, coordinateY, radius, root->SE, visitedCities, citiesInCircle);
            }
            //Area 2
            else if (newDirection == SW)
            {
                Search(coordinateX, coordinateY, radius, root->SE, visitedCities, citiesInCircle);
                Search(coordinateX, coordinateY, radius, root->SW, visitedCities, citiesInCircle);
            }
            //Area 4
            else if (newDirection == NE)
            {
                Search(coordinateX, coordinateY, radius, root->SE, visitedCities, citiesInCircle);
                Search(coordinateX, coordinateY, radius, root->NE, visitedCities, citiesInCircle);
            }
            //Area 9
            else
            {
                Search(coordinateX, coordinateY, radius, root->SE, visitedCities, citiesInCircle);
                Search(coordinateX, coordinateY, radius, root->SW, visitedCities, citiesInCircle);
                Search(coordinateX, coordinateY, radius, root->NE, visitedCities, citiesInCircle);
            }
        }
        //Right upper area
        else if (direction == SW)
        {
            newDirection = PointCompare(rightVerticalLine, upperHorizontalLine, root);

            //Area 2
            if (newDirection == SE)
            {
                Search(coordinateX, coordinateY, radius, root->SE, visitedCities, citiesInCircle);
                Search(coordinateX, coordinateY, radius, root->SW, visitedCities, citiesInCircle);
            }
            //Area 3
            else if (newDirection == SW)
            {
                Search(coordinateX, coordinateY, radius, root->SW, visitedCities, citiesInCircle);
            }
            //Area 10
            else if (newDirection == NE)
            {
                Search(coordinateX, coordinateY, radius, root->SE, visitedCities, citiesInCircle);
                Search(coordinateX, coordinateY, radius, root->SW, visitedCities, citiesInCircle);
                Search(coordinateX, coordinateY, radius, root->NW, visitedCities, citiesInCircle);
            }
            //Area 5
            else
            {
                Search(coordinateX, coordinateY, radius, root->SE, visitedCities, citiesInCircle);
                Search(coordinateX, coordinateY, radius, root->SW, visitedCities, citiesInCircle);
                Search(coordinateX, coordinateY, radius, root->NE, visitedCities, citiesInCircle);
            }
        }
        //Left lower area
        else if (direction == NE)
        {
            newDirection = PointCompare(leftVerticalLine, lowerHorizontalLine, root);

            //Area 4
            if (newDirection == SE)
            {
                Search(coordinateX, coordinateY, radius, root->SE, visitedCities, citiesInCircle);
                Search(coordinateX, coordinateY, radius, root->NE, visitedCities, citiesInCircle);
            }
            //Area 11
            else if (newDirection == SW)
            {
                Search(coordinateX, coordinateY, radius, root->SE, visitedCities, citiesInCircle);
                Search(coordinateX, coordinateY, radius, root->NE, visitedCities, citiesInCircle);
                Search(coordinateX, coordinateY, radius, root->NW, visitedCities, citiesInCircle);
            }
            //Area 6
            else if (newDirection == NE)
            {
                Search(coordinateX, coordinateY, radius, root->NE, visitedCities, citiesInCircle);
            }
            //Area 7
            else
            {
                Search(coordinateX, coordinateY, radius, root->NE, visitedCities, citiesInCircle);
                Search(coordinateX, coordinateY, radius, root->NW, visitedCities, citiesInCircle);
            }
        }
        //Right lower area
        else
        {
            newDirection = PointCompare(rightVerticalLine, lowerHorizontalLine, root);

            //Area 12
            if (newDirection == SE)
            {
                Search(coordinateX, coordinateY, radius, root->SW, visitedCities, citiesInCircle);
                Search(coordinateX, coordinateY, radius, root->NE, visitedCities, citiesInCircle);
                Search(coordinateX, coordinateY, radius, root->NW, visitedCities, citiesInCircle);
            }
            //Area 5
            else if (newDirection == SW)
            {
                Search(coordinateX, coordinateY, radius, root->SW, visitedCities, citiesInCircle);
                Search(coordinateX, coordinateY, radius, root->NW, visitedCities, citiesInCircle);
            }
            //Area 7
            else if (newDirection == NE)
            {
                Search(coordinateX, coordinateY, radius, root->NE, visitedCities, citiesInCircle);
                Search(coordinateX, coordinateY, radius, root->NW, visitedCities, citiesInCircle);
            }
            //Area 7
            else
            {
                Search(coordinateX, coordinateY, radius, root->NW, visitedCities, citiesInCircle);
            }
        }
    }
}

// Helper function to calculate the Euclidean distance between two points
double Quadtree::CalculateDistance(const int & rootCoordinateX, const int & rootCoordinateY, const int & circleCoordinateX, const int & circleCoordinateY)
{
    return sqrt(pow(circleCoordinateX - rootCoordinateX, 2) + pow(circleCoordinateY - rootCoordinateY, 2));
}

// Determines the relative position (quadrant) of a point compared to a root node
Directions Quadtree::PointCompare(const int &coordinateX, const int &coordinateY, City *root)
{
    if (coordinateX < root->x)
    {
        if (coordinateY < root->y)
        {
            return SW;
        }
        else
        {
            return NW;
        }
    }
    else if (coordinateY < root->y)
    {
        return SE;
    }
    else
    {
        return NE;
    }
}


