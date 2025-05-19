#include "bellman.h"
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <map>
#include <algorithm>

#define MAX 1000

using namespace std;

void BF(int edgeList[][3], int numEdges, char start_vertices, int BFValue[], int BFPrev[],map<char, int> verticesMap) {
    for (int j = 0; j < numEdges; j++) {
        int u = static_cast<char>(edgeList[j][0]);
        int v = static_cast<char>(edgeList[j][1]);

        int u_index = verticesMap[u];
        int v_index = verticesMap[v];

        int weight = edgeList[j][2];

        if (BFValue[u_index] != MAX && BFValue[u_index] + weight < BFValue[v_index]) {        
            BFValue[v_index] = BFValue[u_index] + weight;
            BFPrev[v_index] = u_index;
        }
    }
}

std::string BF_Path(int edgeList[][3], int numEdges, char start_vertices, char end_vertices) {
    map<char, int> verticesMap;
    vector<char> vertices;
    for (int i = 0; i < numEdges; i++) {
        int u = static_cast<char>(edgeList[i][0]);
        int v = static_cast<char>(edgeList[i][1]);
        if (verticesMap.find(u) == verticesMap.end()) {
            verticesMap[u] = vertices.size();
            vertices.push_back(u);         
        }
        if (verticesMap.find(v) == verticesMap.end()) {
            verticesMap[v] = vertices.size();
            vertices.push_back(v);
        }
    }
    
    int numVertices = vertices.size();
    int* BFValue = new int[numVertices];
    int* BFPrev = new int[numVertices];

    for (size_t i = 0; i < numVertices; i++) {
        BFValue[i] = MAX;
        BFPrev[i] = -1;
    }
    int startVertexIndex = verticesMap[start_vertices];
    int endVertexIndex = verticesMap[end_vertices];

    BFValue[startVertexIndex] = 0;
    
    for (size_t i = 0; i < numVertices-1; i++){
        // BF(edgeList, numEdges, start_vertices, BFValue, BFPrev, verticesMap);
        for (int j = 0; j < numEdges; j++) {
            int u = static_cast<char>(edgeList[j][0]);
            int v = static_cast<char>(edgeList[j][1]);

            int u_index = verticesMap[u];
            int v_index = verticesMap[v];

            int weight = edgeList[j][2];

            if (BFValue[u_index] != MAX && BFValue[u_index] + weight < BFValue[v_index]) {        
                BFValue[v_index] = BFValue[u_index] + weight;
                BFPrev[v_index] = u_index;
            }
        }
    }
    
    vector<int> resultVec;
    int currentIndex = endVertexIndex;

    while (currentIndex != -1) {
        resultVec.push_back(currentIndex);
        currentIndex = BFPrev[currentIndex];
    }

    string result;
    for (int i = resultVec.size() - 1; i >= 0; i--) {
        result += vertices[resultVec[i]];
        if (i > 0) {
            result += " ";
        }        
    }
    return result;
}
