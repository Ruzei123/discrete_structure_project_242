#ifndef TSM_H
#define TSM_H

#include <string>
#include <vector>
using namespace std;

string Traveling(int edgeList[][3], int numEdges, char start_vertices); 
int totalCost(int mask, int curr, int n, vector<vector<int>> &costMatrix, vector<vector<int>> &memo, vector<vector<int>>& parent, int startVertexIndex);
vector<char> backTrack(int startVertexIndex, int n, vector<char> vertices, vector<vector<int>>& parent);
int NN(vector<vector<int>> costMatrix, vector<char> vertices,vector<bool> visited, int currIndex);
string rearragePath(vector<char> path, int startVertexIndex);
string tspDP(vector<vector<int>> &costMatrix, vector<char> vertices, int startVertexIndex);
string tspNN(vector<vector<int>> costMatrix, vector<char> vertices, int start); 
#endif