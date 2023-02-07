#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

// Graph class
class Graph {
    public:
        vector<vector<int>>adj;
        vector<bool>visited;
        int num_nodes;

        Graph(int n) {
            num_nodes = n;
            adj.resize(n);
            visited.resize(n);
        }

        void addEdge(int u, int v) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
};

// BFS function
void BFS(Graph& g, RenderWindow& window, vector<CircleShape>& nodes) {
    queue<int>q;
    q.push(0);
    g.visited[0] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        nodes[u].setFillColor(Color::Yellow);
        window.draw(nodes[u]);
        window.display();
        sleep(milliseconds(500)); // delay for animation

        for (int v : g.adj[u]) {
            if (!g.visited[v]) {
                g.visited[v] = true;
                q.push(v);
            }
        }
    }
}

// DFS function
void DFS(Graph& g, RenderWindow& window, vector<CircleShape>& nodes) {
    stack<int>s;
    s.push(0);
    g.visited[0] = true;

    while (!s.empty()) {
        int u = s.top();
        s.pop();

        nodes[u].setFillColor(Color::Yellow);
        window.draw(nodes[u]);
        window.display();
        sleep(milliseconds(500)); // delay for animation

        for (int v : g.adj[u]) {
            if (!g.visited[v]) {
                g.visited[v] = true;
                s.push(v);
            }
        }
    }
}

int main() {
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);

    // Create a window to display the graph
    RenderWindow window(VideoMode(800, 600), "Graph Animation");

    // Create a vector to store the nodes of the graph
    vector<CircleShape> nodes(g.num_nodes);

    // Initialize the nodes with random positions and colors
    for (int i = 0; i < g.num_nodes; i++) {
        nodes[i].setRadius(20);
        nodes[i].setPosition(rand() % 600 + 100, rand() % 400 + 100);
        nodes[i].setFillColor(Color::Green);
    }

    BFS(g, window, nodes);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
    }
    return 0;
}