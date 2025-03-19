#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Quadtree.h" // Include custom Quadtree implementation
#include <vector>

using namespace std;

int main()
{
    // Create an input file stream to read city data from "cities.txt"
    ifstream input;
    input.open("cities.txt");

    // Initialize the Quadtree structure
    Quadtree tree;

    // Variables to store city data and coordinates
    string line, cityName, xs, ys;
    int x, y, r;

    // Skip the header line in the input file
    getline(input, line);

    // Read the file line by line
    while (getline(input, line))
    {
        // Use stringstream to parse each line
        istringstream iss(line);
        iss >> cityName >> x >> y; // Extract city name and coordinates (x, y)

        // Insert city data into the Quadtree
        tree.Insert(cityName, x, y);
    }

    // Close the city data input file
    input.close();

    // Create an output file stream for writing results to "output.txt"
    ofstream output("output.txt");

    // Print the structure of the Quadtree to the output file
    tree.Print(output);
    cout << endl; // Add a blank line to the console for readability

    // Vectors to store visited cities and cities within the search circle
    vector<string> citiesVisited;
    vector<string> citiesInCircle;

    // Open the query file "queries0.txt"
    input.open("queries0.txt");

    // Process each query line in the query file
    while (getline(input, line))
    {
        output << endl; // Add a blank line before each query result in the output

        // Parse the query line to extract coordinates and radius
        istringstream iss(line);
        iss >> xs >> ys >> r;

        // Convert string coordinates (with trailing commas) to integers
        x = stoi(xs.substr(0, xs.length() - 1));
        y = stoi(ys.substr(0, ys.length() - 1));

        // Search for cities in the Quadtree within the given radius
        tree.Search(x, y, r, citiesVisited, citiesInCircle);

        // Output cities within the search circle
        if (citiesInCircle.size() == 0)
        {
            output << "<None>" << endl; // No cities found in the circle
        }
        else
        {
            // List all cities in the circle, separated by commas
            for (int i = 0; i < citiesInCircle.size(); ++i)
            {
                if (i == 0)
                {
                    output << citiesInCircle[i];
                }
                else
                {
                    output << ", " << citiesInCircle[i];
                }
            }
            output << endl;
        }

        // Output all visited cities during the search
        for (int i = 0; i < citiesVisited.size(); ++i)
        {
            if (i == 0)
            {
                output << citiesVisited[i];
            }
            else
            {
                output << ", " << citiesVisited[i];
            }
        }
        output << endl;

        // Clear vectors for the next query
        citiesInCircle.clear();
        citiesVisited.clear();
    }
    cout << "Output file created successfully!" << endl;

    // Close the output and input files
    output.close();
}
