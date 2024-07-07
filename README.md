# Route Optimization - Bhopal Metro

This project aims to optimize the routes for the Bhopal Metro by finding the shortest distance and time paths between stations using Dijkstra's algorithm.

## Features

1. **List all stations with their codes**
2. **Display the metro map**
3. **Find the shortest distance path between two stations**
4. **Find the shortest time path between two stations**

## Project Structure

- **GraphVertex Class**: Manages the metro stations and their respective codes.
- **DTC Class**: Stores distance and time information for edges.
- **graphedge Class**: Manages the edges of the metro network, representing connections between stations.
- **Adjacency List**: Converts the edge list into adjacency lists for distance and time.
- **Dijkstra's Algorithm**: Finds the shortest path based on distance or time.
- **Visualization**: Generates a DOT file to visualize the metro map and highlights the shortest path using Graphviz.

## Usage

### List All Stations

1. Run the program.
2. Select option `1` to list all the stations with their codes.

### Display Metro Map

1. Run the program.
2. Select option `2` to display the entire metro map with distances and times.

### Find Shortest Distance Path

1. Run the program.
2. Select option `3` to find the shortest distance path between two stations.
3. Choose to input either station names or codes.
4. Enter the source and destination stations.
5. The shortest distance and path will be displayed and saved as an image.

### Find Shortest Time Path

1. Run the program.
2. Select option `4` to find the shortest time path between two stations.
3. Choose to input either station names or codes.
4. Enter the source and destination stations.
5. The shortest time and path will be displayed and saved as an image.

### Exit

1. Select option `5` to exit the program.

## Dependencies

- C++ Standard Library
- Graphviz (for visualization)

## How to Run

1. Clone this repository.
2. Ensure you have the necessary compiler (e.g., g++) and Graphviz installed.
3. Compile the code using the following command:
   ```bash
   g++ -o bhopal_metro bhopal_metro.cpp -std=c++11
