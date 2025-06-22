#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

void BF(int edgeList[][3], int numEdges, char start_vertices, int BFValue[], int BFPrev[]) {
    //collect and sort all distinct Vertices
    vector<char> vertices;
    for (int i = 0; i < numEdges; i++) {
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
    
    // cout <<start_vertices<<endl;
    // for (char v: vertices) {
    //     cout<<v<<" ";
    // }
    // cout<<endl;

    int startVertexIndex = find(vertices.begin(), vertices.end(), start_vertices) - vertices.begin();
    BFValue[startVertexIndex] = 0;

    int numVertices = vertices.size();

    vector<vector<int>> newEdgeList;
    for (int j = 0; j < numEdges; j++) {
        vector<int> edge(3);
        edge[0] = edgeList[j][0];
        edge[1] = edgeList[j][1];
        edge[2] = edgeList[j][2];
        newEdgeList.push_back(edge);
    }
    sort(newEdgeList.begin(), newEdgeList.end(), [](const auto& edge1, const auto& edge2){
        return edge1[0] < edge2[0];
    });

    int* BFValueTemp = new int[numVertices];
    int* BFPrevTemp = new int[numVertices];

    for (int i = 0; i < numVertices; i++) {
        BFValueTemp[i] = BFValue[i];
    }

    for (int j = 0; j < numEdges; j++) {
        int u = static_cast<char>(newEdgeList[j][0]);
        int v = static_cast<char>(newEdgeList[j][1]);

        int u_index = find(vertices.begin(), vertices.end(), u) - vertices.begin();
        int v_index = find(vertices.begin(), vertices.end(), v) - vertices.begin();    
        
        int weight = newEdgeList[j][2];

        int distance = BFValueTemp[u_index] + weight;

        //check if current vertex value + weight < nex vertex value  
        if (BFValueTemp[u_index] != -1 && (distance < BFValue[v_index] || BFValue[v_index] <= -1)) {
            BFValue[v_index] = distance; 
            BFPrev[v_index] = u_index; 
        }  
    }
}

string BF_Path(int edgeList[][3], int numEdges, char start_vertices, char end_vertices) {
    //collect and sort all distinct Vertices
    vector<char> vertices;
    for (int i = 0; i < numEdges; i++) {
        int u = static_cast<char>(edgeList[i][0]);
        int v = static_cast<char>(edgeList[i][1]);
        if (find(vertices.begin(), vertices.end(), u) == vertices.end()) {
            vertices.push_back(u);         
        }
        if (find(vertices.begin(), vertices.end(), v) == vertices.end()) {
            vertices.push_back(v);
        }
    }
    sort(vertices.begin(), vertices.end());

    // initialize BFValue and BFPrev
    int numVertices = vertices.size();
    int* BFValue = new int[numVertices];
    int* BFPrev = new int[numVertices];
    
    for (int i = 0; i < numVertices; i++) {
        BFValue[i] = -1;
        BFPrev[i] = -1;
    }

    int startVertexIndex = find(vertices.begin(), vertices.end(), start_vertices) -  vertices.begin();
    int endVertexIndex  = find(vertices.begin(), vertices.end(), end_vertices) - vertices.begin();
    if (startVertexIndex == numVertices) BFPrev[startVertexIndex -1] = 0;
    BFValue[startVertexIndex] = 0;

    vector<vector<int>> newEdgeList;
    for (int j = 0; j < numEdges; j++) {
        vector<int> edge(3);
        edge[0] = edgeList[j][0];
        edge[1] = edgeList[j][1];
        edge[2] = edgeList[j][2];
        newEdgeList.push_back(edge);
    }
        
    sort(newEdgeList.begin(), newEdgeList.end(), [](const auto& edge1, const auto& edge2){
        return edge1[0] < edge2[0];     
    });

    //find Bellman Ford's Path
    int* BFValueTemp = new int[numVertices];
    
    for (int i = 0; i < numVertices - 1 ; i++) {
        for (int i = 0; i < numVertices; i++) {
            BFValueTemp[i] = BFValue[i];
        }   
        for (int j = 0; j < numEdges; j++) {
            int u = static_cast<char>(newEdgeList[j][0]);
            int v = static_cast<char>(newEdgeList[j][1]);

            int u_index = find(vertices.begin(), vertices.end(), u) - vertices.begin();
            int v_index = find(vertices.begin(), vertices.end(), v) - vertices.begin();    
        
            int weight = newEdgeList[j][2];

            int distance = BFValueTemp[u_index] + weight;

            //check if current vertex value + weight < nex vertex value  
            if (BFValueTemp[u_index] != -1 && (distance < BFValue[v_index] || BFValue[v_index] <= -1)) {
                BFValue[v_index] = distance; 
                BFPrev[v_index] = u_index; 
            }
        }
    }
    
    //backtracking from end to start vertex
    vector<int> resultVec;
    int currentIndex = endVertexIndex;
    while (currentIndex != -1 && currentIndex < numVertices) {
        resultVec.push_back(currentIndex);
        currentIndex = BFPrev[currentIndex]; //get previous vertex from BFPrev at current vertex's index
    }
    //print result by looping from end to start of resultVec
    string result;
    for (int i = resultVec.size() - 1; i >= 0; i--) {
        result += vertices[resultVec[i]];
        if (i > 0) {
            result += " ";
        }        
    }
    return result;
}