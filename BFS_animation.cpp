#include <iostream>
#include <queue>
#include <cstring>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

const int N = 50; // size of the grid
const int SIZE = 50; // size of each cell in the window

void generateRandomMatrix(int N, double probabilityOfOne, int** mat) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    mat = new int*[N];
    for (int i = 0; i < N; i++) {
        mat[i] = new int[N];
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (dis(gen) < probabilityOfOne) {
                mat[i][j] = 1;
            } else {
                mat[i][j] = 0;
            }
        }
    }
}


// Helper function to check if a given point is valid and unvisited
bool isValid(int x, int y, int mat[N][N], bool visited[N][N]) {
    return (x >= 0 && x < N && y >= 0 && y < N && mat[x][y] == 0 && !visited[x][y]);
}

void BFS(int** mat, int startX, int startY, RenderWindow& window) {
    int N = sizeof(mat[0])/sizeof(mat[0][0]);
    bool visited[N][N];
    memset(visited, false, sizeof(visited)); // set all elements to false

    queue<pair<int, int>> q;
    q.push({startX, startY});
    visited[startX][startY] = true;

    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};

    while (!q.empty()) {
        auto curr = q.front();
        q.pop();

        // Draw the current cell in the window
        RectangleShape cell(Vector2f(SIZE, SIZE));
        cell.setPosition(curr.second * SIZE, curr.first * SIZE);
        cell.setFillColor(Color::Green);
        window.draw(cell);
        window.display();
        sleep(milliseconds(100));

        for (int i = 0; i < 4; i++) {
            int newX = curr.first + dx[i];
            int newY = curr.second + dy[i];
            if (isValid(newX, newY, *mat, visited)){
                visited[newX][newY] = true;
                q.push({newX, newY});
            }
        }
    }
}


int main() {
    int N;
    cout << "Enter the size of the grid (NxN): ";
    cin >> N;

    double probabilityOfOne = 0.2;
    int** mat;
    generateRandomMatrix(N, probabilityOfOne, mat);

    RenderWindow window(VideoMode(N*SIZE, N*SIZE), "BFS Animation");

    BFS(mat, 0, 0, window);
    
    return 0;
}

