#include <bits/stdc++.h>
#include <fstream>
#include <cstdlib>

using namespace std;

class GraphVertex
{
public:
    unordered_map<string, int> stations;

    void addStation(string stationName, int code)
    {
        stations[stationName] = code;
    }

    void printStations()
    {

        vector<pair<string, int>> sortedStations(stations.begin(), stations.end());

        sort(sortedStations.begin(), sortedStations.end(), [](pair<string, int> &a, pair<string, int> &b)
             { return a.second < b.second; });

        int maxWidth = 0;
        for (auto &station : sortedStations)
        {
            if (station.first.size() > maxWidth)
            {
                maxWidth = station.first.size();
            }
        }

        cout << setw(maxWidth) << "Station" << " | " << "Code" << endl;
        cout << string(maxWidth + 6, '-') << endl;

        for (auto &station : sortedStations)
        {
            cout << setw(maxWidth) << station.first << " | " << station.second << endl;
        }
    }
};

class DTC
{
public:
    int dist;
    int time;

    DTC(int d, int t)
    {
        dist = d;
        time = t;
    }
};

class graphedge
{
public:
    map<string, vector<pair<string, DTC>>> m;

    void addEdge(string from, string to, int dist, int time)
    {

        DTC e(dist, time);
        m[from].push_back(make_pair(to, e));
    }

    void printEdges() const
    {
        // Print header
        cout << left << setw(20) << "From" << setw(20) << "To" << setw(10) << "Distance" << setw(10) << "Time" << endl;
        cout << string(60, '-') << endl;

        // Print edges
        for (const auto &from_vertex : m)
        {
            const string &from = from_vertex.first;
            const auto &edges = from_vertex.second;
            for (const auto &edge : edges)
            {
                const string &to = edge.first;
                const DTC &e = edge.second;
                cout << left << setw(20) << from << setw(20) << to
                     << setw(10) << e.dist << setw(10) << e.time << endl;
            }

            cout << endl;
        }
    }
};

void adjlist(vector<vector<pair<int, int>>> &adjdist, vector<vector<pair<int, int>>> &adjtime, const graphedge &g, const GraphVertex &vertex)
{
    unordered_map<string, int> mp1 = vertex.stations;
    const map<string, vector<pair<string, DTC>>> &mp = g.m;

    adjdist.resize(mp1.size());
    adjtime.resize(mp1.size());

    for (const auto &from_vertex : mp)
    {
        string from = from_vertex.first;
        int from_index = mp1[from];
        const auto &edges = from_vertex.second;

        for (const auto &edge : edges)
        {
            string to = edge.first;
            DTC e = edge.second;
            int to_index = mp1[to];

            adjdist[from_index].push_back(make_pair(to_index, e.dist));
            adjtime[from_index].push_back(make_pair(to_index, e.time));

            adjdist[to_index].push_back(make_pair(from_index, e.dist));
            adjtime[to_index].push_back(make_pair(from_index, e.time));
        }
    }
}

typedef pair<int, int> pii;
// Function to find the shortest distance using Dijkstra's Algorithm
void dijkstra(int V, vector<vector<pii>> &adj, int source, int destination, vector<int> &dist, vector<int> &pred)
{

    priority_queue<pii, vector<pii>, greater<pii>> pq;

    pq.push({0, source});
    dist[source] = 0;

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        for (auto &neighbor : adj[u])
        {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                pred[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}

void printPath(vector<int> &pred, int destination, unordered_map<int, string> &codeToStation)
{
    stack<int> path;
    int crawl = destination;
    path.push(crawl);

    while (pred[crawl] != -1)
    {
        path.push(pred[crawl]);
        crawl = pred[crawl];
    }

    while (!path.empty())
    {
        cout << codeToStation[path.top()] << "   --->   ";
        path.pop();
    }
    cout << "end"<<endl;
}

void generateDOTFile(vector<int> &pred, int destination, unordered_map<int, string> &codeToStation, vector<vector<pii>> &adj)
{
    ofstream dotFile("metro_map.dot");
    dotFile << "digraph G {\n";

    for (int i = 0; i < adj.size(); ++i)
    {
        for (auto edge : adj[i])
        {
            dotFile << "  \"" << codeToStation.at(i) << "\" -> \"" << codeToStation.at(edge.first)
                    << "\" [label=\"" << edge.second << "\", color=\"black\"];\n";
        }
    }

    stack<int> path;
    int crawl = destination;
    path.push(crawl);

    while (pred[crawl] != -1)
    {
        path.push(pred[crawl]);
        crawl = pred[crawl];
    }

    while (path.size() > 1)
    {
        int from = path.top();
        path.pop();
        int to = path.top();
        dotFile << "  \"" << codeToStation.at(from) << "\" -> \"" << codeToStation.at(to)
                << "\" [color=\"red\", penwidth=2.0];\n";
    }

    dotFile << "}\n";
    dotFile.close();
}

int main()
{

    GraphVertex vertex; // 20 stations
    vertex.addStation("DIG BUNGLOW", 0);
    vertex.addStation("SINDHI COLONY", 1);
    vertex.addStation("RAILWAY STATION", 2);
    vertex.addStation("PUL BOGDA", 3);
    vertex.addStation("KAMALA PARK", 4);
    vertex.addStation("LALGATHI", 5);
    vertex.addStation("ROSHANPURA", 6);
    vertex.addStation("MATA MANDIR", 7);
    vertex.addStation("MANIT", 8);
    vertex.addStation("BHADBADA SQUARE", 9);
    vertex.addStation("SAHAPURA LAKE", 10);
    vertex.addStation("HBJ STATION", 11);
    vertex.addStation("HABIBGANJ", 12);
    vertex.addStation("AIIMS BHOPAL", 13);
    vertex.addStation("ASSHIMA MALL", 14);
    vertex.addStation("VASANT KUNJ", 15);
    vertex.addStation("KENDRIYA VIDYALAYA", 16);
    vertex.addStation("GOVINDPURA", 17);
    vertex.addStation("INDRAPURI", 18);
    vertex.addStation("PIPLANIP", 19);

    graphedge g;
    g.addEdge("DIG BUNGLOW", "SINDHI COLONY", 1, 3);
    g.addEdge("SINDHI COLONY", "RAILWAY STATION", 2, 6);
    g.addEdge("SINDHI COLONY", "KAMALA PARK", 3, 7);
    g.addEdge("RAILWAY STATION", "PUL BOGDA", 2, 5);
    g.addEdge("RAILWAY STATION", "KAMALA PARK", 3, 7);
    g.addEdge("LALGATHI", "KAMALA PARK", 7, 9);
    g.addEdge("KAMALA PARK", "ROSHANPURA", 3, 5);
    g.addEdge("PUL BOGDA", "GOVINDPURA", 3, 6);
    g.addEdge("GOVINDPURA", "INDRAPURI", 4, 7);
    g.addEdge("PUL BOGDA", "KENDRIYA VIDYALAYA", 3, 7);
    g.addEdge("PUL BOGDA", "ROSHANPURA", 3, 6);
    g.addEdge("KENDRIYA VIDYALAYA", "HBJ STATION", 4, 10);
    g.addEdge("HBJ STATION", "HABIBGANJ", 1, 2);
    g.addEdge("HBJ STATION", "PIPLANI", 6, 11);
    g.addEdge("HABIBGANJ", "AIIMS BHOPAL", 4, 9);
    g.addEdge("HABIBGANJ", "ASSHIMA MALL", 5, 8);
    g.addEdge("HABIBGANJ", "VASANT KUNJ", 3, 6);
    g.addEdge("ROSHANPURA", "BHADBADA SQUARE", 5, 9);
    g.addEdge("ROSHANPURA", "MATA MANDIR", 2, 3);
    g.addEdge("MATA MANDIR", "MANIT", 1, 3);
    g.addEdge("MATA MANDIR", "HBJ STATION", 4, 6);
    g.addEdge("MANIT", "SAHAPURA LAKE", 6, 10);

    int numvertex = vertex.stations.size();
    int numedges = g.m.size();

    vector<vector<pair<int, int>>> adjdist(numvertex);
    vector<vector<pair<int, int>>> adjtime(numvertex);

    adjlist(adjdist, adjtime, g, vertex);

    unordered_map<string, int> stationToCode = vertex.stations;
    unordered_map<int, string> codeToStation;

    for (const auto &pair : stationToCode)
    {
        codeToStation[pair.second] = pair.first;
    }

    int source, destination;
    string sourceInput, destinationInput;
    int inputOption;

    while (true)
    {

        cout << "\n\n\n\t\t\t\t~~FEATURES~~\n"
             << "1. LIST ALL THE STATIONS WITH CODE IN THE MAP\n"
             << "2. SHOW THE METRO MAP\n"
             << "3. GET SHORTEST DISTANCE PATH FROM A 'SOURCE' STATION TO 'DESTINATION' STATION\n"
             << "4. GET SHORTEST TIME PATH TO REACH FROM A 'SOURCE' STATION TO 'DESTINATION' STATION\n"
             << "5. EXIT THE MENU\n"
             << "\nENTER YOUR CHOICE FROM THE ABOVE LIST (1 to 5) : ";

        int choice = -1;
        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        vector<int> dist(numvertex, INT_MAX);
        vector<int> pred(numvertex, -1);

        switch (choice)
        {
        case 1:
            // Print all stations
            vertex.printStations();
            break;

        case 2:
            // print map
            g.printEdges();
            break;

        case 3:
            cout << "PRESS 1 TO INPUT STATION NAME OR\nPRESS 2 INPUT STATION CODE : ";
            cin >> inputOption;

            if (inputOption == 1)
            {
                cout << "Enter source station name: ";
                cin.ignore();
                getline(cin, sourceInput);
                cout << "Enter destination station name: ";
                getline(cin, destinationInput);

                source = stationToCode[sourceInput];
                destination = stationToCode[destinationInput];
            }

            else if (inputOption == 2)
            {
                cout << "\nEnter source station code: ";
                cin >> source;
                cout << "Enter destination station code: ";
                cin >> destination;
            }

            else
            {
                cout << "Invalid input option." << endl;
                return 1;
            }

            // for finding shortest distance path

            dijkstra(numvertex, adjdist, source, destination, dist, pred);

            if (dist[destination] != INT_MAX)
            {
                cout << "\nShortest distance from " << codeToStation[source] << " to " << codeToStation[destination] << " is " << dist[destination] <<" km "<< endl;
                cout << "Path: ";
                printPath(pred, destination, codeToStation);
                generateDOTFile(pred, destination, codeToStation, adjdist);

                system("dot -Tpng metro_map.dot -o metro_map.png");
                cout << "Map image saved as metro_map.png" << endl;
                system("start metro_map.png"); // Open the image
            }
            else
            {
                cout << "No path exists between " << codeToStation[source] << " and " << codeToStation[destination] << endl;
            }
            break;

        case 4:

            // for finding shortest time path
            cout << "Enter 1 to input station name or 2 to input station index: ";
            cin >> inputOption;

            if (inputOption == 1)
            {
                cout << "Enter source station name: ";
                cin.ignore();
                getline(cin, sourceInput);
                cout << "Enter destination station name: ";
                getline(cin, destinationInput);

                source = stationToCode[sourceInput];
                destination = stationToCode[destinationInput];
            }

            else if (inputOption == 2)
            {
                cout << "Enter source station code: ";
                cin >> source;
                cout << "Enter destination station code: ";
                cin >> destination;
            }

            else
            {
                cout << "Invalid input option." << endl;
                return 1;
            }

            dijkstra(numvertex, adjtime, source, destination, dist, pred);

            if (dist[destination] != INT_MAX)
            {
                cout << "\nShortest time from " << codeToStation[source] << " to " << codeToStation[destination] << " is " << dist[destination] << " min " << endl;
                cout << "Path: ";
                printPath(pred, destination, codeToStation);
                generateDOTFile(pred, destination, codeToStation, adjtime);

                system("dot -Tpng metro_map.dot -o metro_map.png");
                cout << "Map image saved as metro_map.png" << endl;
                system("start metro_map.png");
            }
            else
            {
                cout << "No path exists between " << codeToStation[source] << " and " << codeToStation[destination] << endl;
            }
            break;

        case 5:
            cout << "Exiting the menu." << endl;
            return 0;
            break;

        default:
            cout << "Please enter a valid option!" << endl;
        }
    }
}
