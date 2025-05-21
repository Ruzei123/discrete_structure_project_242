#ifndef BELLMAN_H
#define BELLMAN_H

#include <string>
using namespace std;
void BF(int edgeList[][3], int numEdges, char start_vertices, int BFValue[], int BFPrev[]);
string BF_Path(int edgeList[][3], int numEdges, char start_vertices, char end_vertices);

#endif