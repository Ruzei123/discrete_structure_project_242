#include "bellman.h"
#include "tsm.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;
#define MAX 1000

//Function to print an edge
void printedge(int[]);
//Function to generate a random edges list
int edgeListGen(int[][3],int,int,int);

//main Function
int main()
{
    //Function name for checking:
    enum Func_check {bf,bf_path,travelling};
    
    bool randGen=0;
    int edgeList[70][3];
    int numEdges=70;
    int numVertices=10;
    int initlimit=15;
    if(!randGen){
        //Read from file
        ifstream fin("EdgeList1.txt");
        for(int i=0;i<numEdges;i++){
            fin>>edgeList[i][0]>>edgeList[i][1]>>edgeList[i][2];       
        }
        fin.close();
    }
    else{
        //Generate a random edgelist:
        if(edgeListGen(edgeList,numEdges,numVertices,initlimit)<0) return -1;
    }
    
    //Check the chosen function:
    Func_check func = travelling;
    switch(func) {
        case bf: {
            int BFValue[50];
            int BFPrev[50];
            for(int k=0;k<numVertices;k++){
                BFValue[k]=-1;
                BFPrev[k]=-1;
            }    
            char start_vertices=edgeList[0][0];
            BF(edgeList,numEdges,start_vertices,BFValue,BFPrev);
            for(int k=0;k<numVertices;k++){
                cout<<BFValue[k]<<" ";
            }
            cout<<endl;
            for(int k=0;k<numVertices;k++){
                cout<<BFPrev[k]<<" ";
            }
            cout<<endl;
            break;
        } 
        case bf_path:{
            char start_vertices=edgeList[0][0];
            char end_vertices=edgeList[numEdges-5][/*numEdges-1*/1];
            cout<< start_vertices<<" "<<end_vertices<<endl;
            cout << BF_Path(edgeList,numEdges,start_vertices,end_vertices);
            break;
        }
        case travelling: {
            char start_vertices=edgeList[0][0];
            cout << Traveling(edgeList,numEdges,start_vertices);
            break;
        }
        default: cout<<"no such case";
    }
    return 0;
}







//support function definition 
void printedge(int edge[]){
    cout<<char(edge[0])<<char(edge[1])<<","<<edge[2]<<endl;
}

int edgeListGen(int edgeList[][3],int numEdges,int numVertices,int initlimit=1){
    /*
    edgeList: output generated edgeList
    numEdges: number of edges
    numVertices: number vertices
    initlimit: if <=1 all edges weight is 1, else, edges weight random int [1,initlimit]
    */
    
    //random generator init
    random_device rd;
    mt19937 gen(rd());
    
    //exception
    if(numEdges>(numVertices*(numVertices-1))/2){
        cout<<"cannot create simple graph";
        return -1;
    }
    if(numEdges<numVertices-1){
        cout<<"cannot create a connected (weak) graph";
        return -1;
    }
    
    //generate random vertices' names
    int* verList=new int[numVertices];
    vector<int> verName;
    for(int i=33;i<=126;i++){verName.push_back(i);}
    shuffle(verName.begin(),verName.end(),gen);
    for(int i=0;i<numVertices;i++){verList[i]=verName[i];}
    
    //generate random edges, ensure that each vertices will have at least 1 edges;
    bool flag=0;
    vector<pair<int,int>> fullList;
    for(int i=0;i<numVertices;i++){
        for(int j=0;j<numVertices;j++){
            if(i==j) break;
            fullList.push_back({verList[i],verList[j]});
        }
    }
    int* checkList=new int[numVertices];
    while (!flag){
        shuffle(fullList.begin(),fullList.end(),gen);    
        for(int i=0;i<numEdges;i++){
            edgeList[i][0]=fullList[i].first;
            edgeList[i][1]=fullList[i].second;
        }
        int count=0;
        
        for(int i=0;i<numEdges;i++){
            if(count==numVertices) {
                flag=1; break;
            }
            bool found0=0;
            bool found1=0;
            for(int j=0;j<count;j++){
                if(found0&&edgeList[i][0]==checkList[j]){
                    found0=1;
                }
                if(found1&&edgeList[i][1]==checkList[j]){
                    found1=1;
                }
                if(found0&&found1) break;
            }
            if(!found0){
                checkList[count++]=edgeList[i][0];
            }
            if(!found1){
                checkList[count++]=edgeList[i][1];
            }
            //cout<<"reshuffle edgeList\n";
        }
    }
    delete[] checkList;
    
    ofstream fout("EdgeList.txt");
    //generate the weights
    if(initlimit<=1){//All the weights will be 1
        for(int i=0;i<numEdges;i++){
            edgeList[i][2]=1;            
        }
    }
    else{//randomize edges' weights
        uniform_int_distribution<int> dist(0,initlimit);
        for(int i=0;i<numEdges;i++){
            edgeList[i][2]=dist(gen);            
            fout<<edgeList[i][0]<<" "<<edgeList[i][1]<<" "<<edgeList[i][2]<<endl;
        }
    }
    fout.close();
    delete []verList;
    return 1;
}

