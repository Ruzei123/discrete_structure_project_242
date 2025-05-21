#include "bellman.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define MAX 1000

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

    //check if BFValue is empty, if empty then initialize BFValue and BFPrev
    int numVertices = vertices.size();
    bool isEmpty = true;
    for (int i = 0; i < numVertices; i++) {
        if(BFValue[i] != 0) {
            isEmpty = false;
            break;
        }
    }
    if (isEmpty == true) {
        for (int i = 0; i < numVertices; i++) {
            BFValue[i] = MAX;
            BFPrev[i] = -1;
        }
        int startVertexIndex = distance(vertices.begin(), find(vertices.begin(), vertices.end(), start_vertices));
        BFValue[startVertexIndex] = 0;
    }

    //find Bellman Ford's Step
    for (int j = 0; j < numEdges; j++) {
        int u = static_cast<char>(edgeList[j][0]);
        int v = static_cast<char>(edgeList[j][1]);

        int u_index = distance(vertices.begin(), find(vertices.begin(), vertices.end(), u));
        int v_index = distance(vertices.begin(), find(vertices.begin(), vertices.end(), v));

        int weight = edgeList[j][2];
        //check if current vertex value + weight < nex vertex value  
        if (BFValue[u_index] != MAX && BFValue[u_index] + weight < BFValue[v_index]) {     
            BFValue[v_index] = BFValue[u_index] + weight;       //update next vertex value = current vertex value + weight
            BFPrev[v_index] = u_index;      //store current vertex in BFPrev at next vertex's index
        }
    }

    //print result
    // cout <<"Step: ";
    // for (int i = 0; i < numVertices; i++) {
    //     cout  << BFValue[i] << " " ;
    // }
    // cout <<endl;  
    // cout <<"Previous Vertex: ";
    // for (int i = 0; i < numVertices; i++) {
    //     cout  << BFPrev[i] << " " ;
    // }
    // cout <<endl; 
}

std::string BF_Path(int edgeList[][3], int numEdges, char start_vertices, char end_vertices) {
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

    //initialize BFValue and BFPrev
    int numVertices = vertices.size();
    int* BFValue = new int[numVertices];
    int* BFPrev = new int[numVertices];

    //print all vertices for debug
    // for (int i = 0; i < numVertices; i++){ 
    //     cout << vertices[i]<<" ";
    // }
    // cout << endl;
    
    for (int i = 0; i < numVertices; i++) {
        BFValue[i] = MAX;
        BFPrev[i] = -1;
    }

    int startVertexIndex = distance(vertices.begin(), find(vertices.begin(), vertices.end(), start_vertices));
    int endVertexIndex  = distance(vertices.begin(), find(vertices.begin(), vertices.end(), end_vertices));

    BFValue[startVertexIndex] = 0;
    
    //find Bellman Ford's Path
    for (int i = 0; i < numVertices-1; i++){
        BF(edgeList, numEdges, start_vertices, BFValue, BFPrev);
    }

    //backtracking from end to start vertex
    vector<int> resultVec;
    int currentIndex = endVertexIndex;
    while (currentIndex != -1) {
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
