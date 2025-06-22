#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

int totalCost(int mask, int curr, int n, vector<vector<int>> &costMatrix, vector<vector<int>> &memo, vector<vector<int>>& parent, int startVertexIndex) {
    if (mask == (1 << n) - 1) {
        return costMatrix[curr][startVertexIndex];
    }
    if (memo[curr][mask] != -1) {
        return memo[curr][mask];
    }

    int ans = 100000;
    int nextBest = -1;
    // Try visiting every city that has not been visited yet
    for (int i = 0; i < n; i++) {
        if ((mask & (1 << i)) == 0) {
            // If city i is not visited, visit it and update the mask
            int currCost = costMatrix[curr][i] + totalCost((mask | (1 << i)), i, n, costMatrix, memo, parent, startVertexIndex);
            if (currCost < ans) {
                ans = currCost;
                nextBest = i;
            };
        }
    }
    parent[curr][mask] = nextBest;
    return memo[curr][mask] = ans;
}

vector<char> backTrack(int startVertexIndex, int n, vector<char> vertices, vector<vector<int>>& parent) {
    vector<int> pathIndex;
    int mask = 1 << startVertexIndex;
    int curr = startVertexIndex;
    pathIndex.push_back(curr);

    while (mask != (1 << n) - 1) {
        int next = parent[curr][mask];
        pathIndex.push_back(next);
        mask |= (1 << next); 
        curr = next;
    }
    pathIndex.push_back(startVertexIndex);

    vector<char> path;
    for (int i: pathIndex) {
        path.push_back(vertices[i]);
    }
    return path;
}

int NN(vector<vector<int>> costMatrix, vector<char> vertices,vector<bool> visited, int currIndex) {
    int numVertices = vertices.size();

    int nextIndex = -1;
    int minCost = 100000;

    for (int i = 0; i < numVertices; i++) {
        if (!visited[i] && costMatrix[currIndex][i] < minCost) {
            minCost = costMatrix[currIndex][i];
            nextIndex = i;
        }  
    }
    return nextIndex;
}

string rearragePath(vector<char> path, int startVertexIndex) {
    vector<char> newPath;

    for (int i = startVertexIndex; i < path.size() -1; i++) {
        newPath.push_back(path[i]);
    }
    for (int i = 0; i < startVertexIndex; i++) {
        newPath.push_back(path[i]);
    }
    newPath.push_back(path[startVertexIndex]);

    string result;
    for (int i = 0; i < newPath.size(); i++) {
        result += newPath[i];
        if (i != newPath.size() - 1) result += " ";        
    }
    return result;
}

string tspDP(vector<vector<int>> &costMatrix, vector<char> vertices, int startVertexIndex) {
    int n = costMatrix.size();
    vector<vector<int>> memo(n, vector<int>(1 << n, -1));
    vector<vector<int>> parent(n, vector<int>(1 << n, -1));
    // Start from city 0, and only city 0 is visited
    int minCost = totalCost(1<<startVertexIndex, startVertexIndex, n, costMatrix, memo, parent, startVertexIndex);
    vector<char> path = backTrack(startVertexIndex, n, vertices, parent);
    string result;
    for (int i = 0; i < path.size(); i++) {
        result += path[i];
        if (i != path.size() - 1) result += " ";        
    }
    return result;
}

string tspNN(vector<vector<int>> costMatrix, vector<char> vertices, int start) {
    int numVertices = vertices.size();
    vector<bool> visited(numVertices, false);
    vector<char> path;

    for (int i = 0; i < numVertices; i++) {
        int startVertexIndex = i;
        int currIndex = startVertexIndex;
        int totalCost = 0;

        path.push_back(vertices[currIndex]);
        visited[currIndex] = true;
        for (int j = 0; j < numVertices; j++) {      
            int nextIndex = NN(costMatrix, vertices, visited, currIndex);
            if (j == numVertices -1 && costMatrix[currIndex][startVertexIndex] < 100000) {
                path.push_back(vertices[startVertexIndex]);
                totalCost += costMatrix[currIndex][startVertexIndex];
            };
            if (nextIndex != -1) {    
                path.push_back(vertices[nextIndex]);
                visited[nextIndex] = true;
                totalCost += costMatrix[currIndex][nextIndex];
                currIndex = nextIndex;          
            } 
        }
        if (path.size() == numVertices + 1) {
            break;
        } else {     
            for (int k = 0; k < numVertices; k++) {
                visited[k] = false;
            }
            path.clear();
        }
    }
    return rearragePath(path, start);
};


string Traveling(int edgeList[][3] ,int numEdge,char start){
    //collect and sort all distinct Vertices
    vector<char> vertices;
    for (int i = 0; i < numEdge; i++) {
        int u = static_cast<char>(edgeList[i][0]);
        int v = static_cast<char>(edgeList[i][1]);
        if (find(vertices.begin(), vertices.end(), u) == vertices.end()) { //add vertex u if not exist 
            vertices.push_back(u);         
        }
        if (find(vertices.begin(), vertices.end(), v) == vertices.end()) { //add vertex v if not exist
            vertices.push_back(v);
        }
    }
    sort(vertices.begin(), vertices.end());
    int numVertices = vertices.size();
    //create cost matrix
    vector<vector<int>> costMatrix(numVertices, vector<int>(numVertices, 100000));
    for (int i = 0; i < numVertices; i++) costMatrix[i][i] = 0;
    for (int i = 0; i < numEdge; i++) {
        char u = edgeList[i][0];
        char v = edgeList[i][1];

        int u_index = find(vertices.begin(), vertices.end(), u) - vertices.begin();
        int v_index = find(vertices.begin(), vertices.end(), v) - vertices.begin();
        costMatrix[u_index][v_index] =  edgeList[i][2];
    }

    int startVertexIndex = find(vertices.begin(), vertices.end(), start) -  vertices.begin();
    string res = " ";
    if (numVertices <=21) {
        res = tspDP(costMatrix, vertices, startVertexIndex);
    } else {
        res = tspNN(costMatrix, vertices, startVertexIndex);
    }
    return res;
}