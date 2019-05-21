#include <memory>
#include <vector>
#include <algorithm>
#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"
#include "FindVertexCover.h"

using namespace std;

int FindVertexCover::combination(int numOfVertices){
    return (numOfVertices*(numOfVertices-1))/2;
}

vector<int> FindVertexCover::negCombination(int atoms, vector<int> indexes, int numOfVertices, int min){
    vector<int> conbinations = {};
    for(int i = 0; i < numOfVertices; i++){
        for(int j = i; j < (numOfVertices*min); ){
            for(int k = j + numOfVertices; k< (numOfVertices*min);){
                conbinations.push_back(indexes.at(j));
                conbinations.push_back(indexes.at(k));
                k = k + numOfVertices;
            }
            j = j + numOfVertices;
        }
    }
    int count=0;
    for(unsigned i = 0; i < indexes.size(); i++){
        if((i==0) || (i%numOfVertices == 0)){
            for(unsigned j = i+1; j < i + numOfVertices; j++){
            conbinations.push_back(indexes.at(i));
            conbinations.push_back(indexes.at(j));
            }
            count++;
        }
        else{
            for(int j = i+1; j < (numOfVertices*count); j++){
            conbinations.push_back(indexes.at(i));
            conbinations.push_back(indexes.at(j));
            }
        }
    }
    return conbinations;
}

void FindVertexCover::minVertexCover(int numberOfVertices, int numberOfEdges, vector<string> edges){
    bool stop=true;
    vector<int> final_littrals = {};
    int minimum=1;
    while(stop || (minimum == (numberOfVertices+1))){
        unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
        vector<int> littralIndexes = {};
        int atom = minimum*numberOfVertices;
        Minisat::vec<Minisat::Lit> littrals;
        for(int i = 0; i < atom; i++){
            Minisat::Lit l = Minisat::mkLit(solver->newVar());
            littrals.push(l);
        }
        for(int i = 0;i < minimum; i++){
            Minisat::vec<Minisat::Lit> clauseToAdd;
            for(int j = 0; j < numberOfVertices; j++){
                int pos = (i + (minimum * j));
                littralIndexes.push_back(pos);
                clauseToAdd.push(littrals[pos]);
            }
            solver->addClause(clauseToAdd);
        }
        int negativeLitterals=numberOfVertices + (combination(numberOfVertices)*2);
        vector<int> negativeCombinations=negCombination(negativeLitterals,littralIndexes,numberOfVertices,minimum);
        for(unsigned i=0; i < negativeCombinations.size();){
            Minisat::vec<Minisat::Lit> clauseToAdd;
            clauseToAdd.push(~littrals[negativeCombinations.at(i)]);
            clauseToAdd.push(~littrals[negativeCombinations.at(i+1)]);
            solver->addClause(clauseToAdd);
            i=i+2;
        }
        for(unsigned i = 0; i < edges.size();){
            Minisat::vec<Minisat::Lit> clauseToAdd;
            for(int j = 0; j < minimum; j++){
                clauseToAdd.push(littrals[littralIndexes.at(atoi(edges.at(i).c_str())+(j*numberOfVertices))]);
                clauseToAdd.push(littrals[littralIndexes.at(atoi(edges.at(i+1).c_str())+(j*numberOfVertices))]);
            }
            solver->addClause(clauseToAdd);
            i=i+2;
        }
        bool resolve = solver->solve();
        if(resolve==1){
            final_littrals.empty();
            vector<int> vertexCover = {};
            stop=false;
            for(int i = 0; i < atom; i++){
                final_littrals.push_back(Minisat::toInt(solver->modelValue(littrals[i])));
            }
            for(unsigned i=0;i<final_littrals.size();i++){
                if(final_littrals.at(i) == 0){
                    vertexCover.push_back(i/minimum);
                }
            }
            sort(vertexCover.begin(),vertexCover.end());
            for(unsigned i = 0; i < vertexCover.size(); i++)
                cout<<vertexCover.at(i)<<" ";
            cout<<""<<endl;
        }
        else{
            minimum++;
        }
    }
}