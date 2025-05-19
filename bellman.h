#ifndef BELLMAN_H
#define BELLMAN_H

#include <string>
#include <map>
using namespace std;
void BF(int edgeList[][3], int numEdges, char start_vertices, int BFValue[], int BFPrev[], map<char, int> verticesMap);
string BF_Path(int edgeList[][3], int numEdges, char start_vertices, char end_vertices);

#endif