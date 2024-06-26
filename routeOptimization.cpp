 #include <bits/stdc++.h>
 using namespace std;

  
// Structure to represent a city
struct City 
{
    int id;
    string name;

    City(int id, const string& name) : id(id), name(name) {}
};
 
 
typedef pair<int, int> P;  

 
vector<int> dijkstra(const vector<vector<P>>& graph, int start, int end) {
    int n = graph.size();
    
    priority_queue<P, vector<P>, greater<P>> pq;
    
    vector<int> distances(n, INT_MAX);
    vector<int> previous(n, -1);

    distances[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) 
    {
        int current_cost = pq.top().first;
        int current_vertex = pq.top().second;
        pq.pop();

        if (current_vertex == end) break;

        for (const auto& neighbor : graph[current_vertex]) 
        {
            int next_vertex = neighbor.first;
            int edge_cost = neighbor.second;
            int new_cost = current_cost + edge_cost;

            if (new_cost < distances[next_vertex]) 
            {
                distances[next_vertex] = new_cost;
                previous[next_vertex] = current_vertex;
                pq.push({new_cost, next_vertex});
            }
        }
    }

    vector<int> path;
    
    for (int at = end; at != -1; at = previous[at]) 
    {
        path.push_back(at);
    }

    reverse(path.begin(), path.end());

    if (path.size() == 1 && path[0] != start)
    {
        path.clear();
    }

    return path;
}
 
 

vector<vector<pair<int, int>>> convertToAdjacencyList(const vector<vector<int>>& path, int weightColumn) {
    int n = 0;
    for (const auto& edge : path) {
        n = max(n, max(edge[0], edge[1]) + 1);
    }

    vector<vector<pair<int, int>>> adjList(n);

    for (const auto& edge : path) {
        int u = edge[0];
        int v = edge[1]; 
        int weight = edge[weightColumn]; 

        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight});
    }

    return adjList;
}


int main() {
    // Example cities
    vector<City> cities = 
    {
        {0, "City A"},
        {1, "City B"},
        {2, "City C"},
        {3, "City D"},
        {4, "City E"}
    };

   vector<vector<int>> path = 
   {
        {0, 1, 4, 10},
        {0, 2, 1, 5},
        {1, 3, 2, 8},
        {2, 3, 3, 7},
        {2, 4, 4, 3},
        {3, 4, 1, 2},
        {0, 4, 6, 15}
    };
    

    vector<vector<pair<int, int>>> adjListDistance = convertToAdjacencyList(path, 2);

    vector<vector<pair<int, int>>> adjListTime = convertToAdjacencyList(path, 3);

 
    // Example: Finding paths from City 0 (source) to City 4 (destination)
    int source = 0;
    int destination = 4;


    vector<int> path_distance = dijkstra(adjListDistance ,source, destination );

    vector<int> path_time = dijkstra(adjListTime ,source, destination );


    cout << "Shortest path based on distance: ";
    if (path_distance.empty()) 
    {
        cout << "No path found\n";
    } 
    else 
    {
        for (int i = 0; i < path_distance.size(); ++i)
         {
            cout << cities[path_distance[i]].name;
            if (i < path_distance.size() - 1) 
            {
                cout << " -> ";
            }
        }
        cout<<endl;
    }

    cout << "Shortest path based on time: ";
    if (path_time.empty()) 
    {
        cout << "No path found\n";
    } 
    else 
    {
        for (int i = 0; i < path_time.size(); ++i) 
        {
            cout << cities[path_time[i]].name;
            if (i < path_time.size() - 1)
            {
                cout << " -> ";
            }
        }
         cout<<endl;
    }

    return 0;
}
