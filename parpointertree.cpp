/*

    Parent Pointer Tree

    Project Treeps

    Ross Klonowski
*/

#include "stdc++.h"
#include <iostream>
#include <string>

// Class for holding Parent Pointer Tree
class ParentPointerTree {
    public:
        int* parentIndex;
        std::string* label;
        int* weights;
        int SIZE;

        ParentPointerTree(int sizePar,int parentIndexPar[], std::string labelPar[], int weightsPar[]) {
            parentIndex = parentIndexPar;
            label = labelPar;
            weights = weightsPar;
            SIZE = sizePar;
            calculateWeights();

            for (int i = 0; i < sizePar; i++) {
                weights[i] = 0;
            }
        }

        void calculateWeights() {
            for (int i = 0; i < SIZE; i++) {
                weights[i] = weight(i);
            }
        }

        void printArrays() {
            std::cout << "Parent Index Array: ";
            for (int i = 0; i < SIZE; i++) {
                std::cout << parentIndex[i] << " ";
            }
            std::cout << std::endl;

            std::cout << "Label Array:        ";
            for (int i = 0; i < SIZE; i++) {
                std::cout << label[i] << "  ";
            }
            std::cout << std::endl;

            std::cout << "Weights Array:      ";
            for (int i = 0; i < SIZE; i++) {
                std::cout << weights[i] << "  ";
            }
            std::cout << std::endl;
        }

        int find(int currentNode) {
            while (parentIndex[currentNode] != -1)
                currentNode = parentIndex[currentNode];
            return currentNode;
        }

        int weight(int parent) {
            weights[parent] = 0;

            for (int i = 0; i < SIZE; i++) {
                if (i != parent) {
                    if (find(i) == parent) {
                        ++weights[parent];
                    }
                }
            }
            return weights[parent];
        }

        void unionNodes(int a, int b) {
            // before we use the weights in this function, update them
            calculateWeights();
            // union the nodes
            int root1 = find(a);
            int root2 = find(b);
            //std::cout << "Root of node " << label[a] << " is " << root1 << std::endl;
            //std::cout << "Root of node " << label[b] << " is " << root2 << std::endl;
            if (root1 != root2) {
                //std::cout << "weights of " << root1 << " is " << weights[root1] << std::endl;
                //std::cout << "weights of " << root2 << " is " << weights[root2] << std::endl;
                if (weights[root2] > weights[root1]) {
                    //std::cout << "Parent Index of Node Index " << root1 << " becomes node " << root2 << std::endl;
                    parentIndex[root1] = root2;
                    weights[root2] += weights[root1];

                    // this node is no longer root, make its weight 0(not sure about this one)
                    weights[root1] = 0;
                } else {
                    //std::cout << "Parent Index of Node Index " << root2 << " becomes node " << root1 << std::endl;
                    parentIndex[root2] = root1;
                    weights[root1] += weights[root2];

                    // this node is no longer root, make its weight 0(not sure about this one)
                    weights[root2] = 0;

                }
            }
        }
};

void rootTest(ParentPointerTree treePar, int startNodeIndexPar) {
    
    // time tracking
    clock_t start, end;
    double time_taken;

    // root node testing
    std::cout << "\n\nRoot Node Tests" << std::endl;
    std::cout << "-------------------------" << std::endl;
    
    int startNodeIndex = startNodeIndexPar;

    start = clock();

    startNodeIndex = treePar.SIZE - 1;
    std::cout << "The Root of Node " << treePar.label[startNodeIndex] << "(" << startNodeIndex << ") ";
    std::cout << "is Node " << treePar.label[treePar.find(startNodeIndex)] << "(" << treePar.find(startNodeIndex) << ")" << std::endl;
    
    end = clock();
    time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    std::cout << "Time taken by program is : " << std::fixed << time_taken*100000 << std::setprecision(5)  << "us" << std::endl;
}

int main() {

    // Parent Pointer Tree
    std::cout << "-------------------------" << std::endl;
    std::cout << "Parent Pointer Tree Testing" << std::endl;
    std::cout << "-------------------------" << std::endl;

    // time tracking
    clock_t start, end;
    double time_taken;

    // // initialize the custom tree
    // int size = 26;
    // int parentsIndexTemp[] = {  -1,  25,   1,  13,  -1,   8,   19,  19,  21,  1,   11,  0,   10, -1,   13,  13,  13,  1,   12,  8,   8,   4,   17,  2,   3, -1};
    // std::string labelsTemp[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
    // int weightsTemp[size];
    
    // initialize the 26 node slim tree
    // int size = 26;
    // int parentsIndexTemp[] = {  -1,  0,   1,  2,  3,   4,   5,  6,  7,  8,   9,  10,   11, 12,   13,  14,  15,  16,   17,  18,   19,   20,   21,  22,   23, 24};
    // std::string labelsTemp[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
    //int weightsTemp[size];

    // initialize the tree
    int size = 10;
    int parentsIndexTemp[size];
    for (int i = 0; i < size; i++) {
        parentsIndexTemp[i] = i - 1;
    }
    std::string labelsTemp[size];
    for (int i = 0; i < size; i++) {
        labelsTemp[i] = std::to_string(i);
    }
    int weightsTemp[size];

    // // initialize the tree
    // int size = 100;
    // int parentsIndexTemp[size];
    // for (int i = 0; i < size; i++) {
    //     parentsIndexTemp[i] = i - 1;
    // }
    // std::string labelsTemp[size];
    // for (int i = 0; i < size; i++) {
    //     labelsTemp[i] = std::to_string(i);
    // }
    // int weightsTemp[size];

    // // initialize the tree
    // int size = 1000;
    // int parentsIndexTemp[size];
    // for (int i = 0; i < size; i++) {
    //     parentsIndexTemp[i] = i - 1;
    // }
    // std::string labelsTemp[size];
    // for (int i = 0; i < size; i++) {
    //     labelsTemp[i] = std::to_string(i);
    // }
    // int weightsTemp[size];

    // create a new instance of the test tree
    ParentPointerTree myTree(size, parentsIndexTemp, labelsTemp, weightsTemp);

    // root node testing
    std::cout << "\n\nRoot Node Tests" << std::endl;
    std::cout << "-------------------------" << std::endl;
    
    int startNodeIndex = 0;

    start = clock();

    startNodeIndex = size - 1;
    std::cout << "The Root of Node " << myTree.label[startNodeIndex] << "(" << startNodeIndex << ") ";
    std::cout << "is Node " << myTree.label[myTree.find(startNodeIndex)] << "(" << myTree.find(startNodeIndex) << ")" << std::endl;
    
    end = clock();
    time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    std::cout << "Time taken by program is : " << std::fixed << time_taken*100000 << std::setprecision(5)  << "us" << std::endl;

    rootTest(myTree, 0);

    // weight of node testing
    std::cout << "\n\nWeight of node testing" << std::endl;
    std::cout << "-------------------------" << std::endl;
    int rootNode = 0;
    
    start = clock();
    
    rootNode = 0;
    std::cout << "Weight of " << myTree.label[rootNode] << "(" << rootNode << ") is ";
    std::cout << myTree.weight(rootNode) << std::endl; 
    
    end = clock();
    time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    std::cout << "Time taken by program is : " << std::fixed << time_taken*100000 << std::setprecision(5)  << "us" << std::endl;
    std::cout << std::endl;
    
    // // weighted union tests
    // std::cout << "\n\nWeighted Union Tests" << std::endl;
    // std::cout << "-------------------------" << std::endl;
    // int node1 = 0;
    // int node2 = 0;
    
    // node1 = 13;
    // node2 = 0;

    // start = clock();

    // std::cout << "Union " << node1 << " and " << node2 << std::endl;
    
    // //std::cout << "Before: " << std::endl;
    // //myTree.printArrays();
    
    // //myTree.unionNodes(node1, node2);

    // end = clock();
    // time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    // std::cout << "Time taken by program is : " << std::fixed << time_taken*100000 << std::setprecision(5)  << "us" << std::endl;

    // //std::cout << "After: " << std::endl;
    // //myTree.printArrays();

    return 0;
}
