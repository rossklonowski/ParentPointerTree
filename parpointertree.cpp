/*

    Parent Pointer Tree
    Project Treeps
    Ross Klonowski
    3/14/21

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
            
            for (int i = 0; i < sizePar; i++) {
                weights[i] = 0;
            }
            calculateWeights();
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
    std::cout << "Tree length: " << treePar.SIZE << std::endl;
    
    int startNodeIndex = startNodeIndexPar;

    start = clock();

    startNodeIndex = treePar.SIZE - 1;
    std::cout << "The Root of Node " << treePar.label[startNodeIndex] << "(" << startNodeIndex << ") ";
    std::cout << "is Node " << treePar.label[treePar.find(startNodeIndex)] << "(" << treePar.find(startNodeIndex) << ")" << std::endl;
    
    end = clock();
    time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    std::cout << "Time taken by program is : " << std::fixed << time_taken*100000 << std::setprecision(5)  << "us" << std::endl;
}

void weightTest(ParentPointerTree treePar, int startNodeIndexPar) {

    // time tracking
    clock_t start, end;
    double time_taken;
    
    // weight of node testing
    std::cout << "\n\nWeight of node testing" << std::endl;
    std::cout << "-------------------------" << std::endl;
    std::cout << "Tree length: " << treePar.SIZE << std::endl;
    int rootNode = 0;
    
    start = clock();
    std::cout << "Weight of " << treePar.label[rootNode] << "(" << rootNode << ") is ";
    std::cout << treePar.weight(rootNode) << std::endl;     
    end = clock();

    time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    std::cout << "Time taken by program is : " << std::fixed << time_taken*100000 << std::setprecision(5)  << "us" << std::endl;
    std::cout << std::endl;
}

void unionTest(ParentPointerTree treePar, int node1Par, int node2Par) {

    // time tracking
    clock_t start, end;
    double time_taken;

    std::cout << "\n\nUnion of node testing" << std::endl;
    std::cout << "-------------------------" << std::endl;
    
    // Union of nodes testing
    int node1 = node1Par;
    int node2 = node2Par;

    start = clock();

    std::cout << "Union " << treePar.label[node1] << " and " << treePar.label[node2] << std::endl;
    
    std::cout << "Before: " << std::endl;
    treePar.printArrays();
    
    treePar.unionNodes(node1, node2);

    end = clock();
    time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    std::cout << "Time taken by program is : " << std::fixed << time_taken*100000 << std::setprecision(5)  << "us" << std::endl;

    std::cout << "After: " << std::endl;
    treePar.printArrays();
}

int main() {

    // Parent Pointer Tree
    std::cout << "-------------------------" << std::endl;
    std::cout << "Parent Pointer Tree Testing" << std::endl;
    std::cout << "-------------------------" << std::endl;

    // time tracking
    clock_t start, end;
    double time_taken;

    // initialize the custom tree
    int size_custom = 26;
    int parentsIndexTemp_custom[] = {  -1,  25,   1,  13,  -1,   8,   19,  19,  21,  1,   11,  0,   10, -1,   13,  13,  13,  1,   12,  8,   8,   4,   17,  2,   3, -1};
    std::string labelsTemp_custom[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
    int weightsTemp_custom[size_custom];

    // initialize the tree
    int size_1 = 10;
    int parentsIndexTemp_1[size_1];
    for (int i = 0; i < size_1; i++) {
        parentsIndexTemp_1[i] = i - 1;
    }
    std::string labelsTemp_1[size_1];
    for (int i = 0; i < size_1; i++) {
        labelsTemp_1[i] = std::to_string(i);
    }
    int weightsTemp_1[size_1];

    // initialize the tree
    int size_2 = 100;
    int parentsIndexTemp_2[size_2];
    for (int i = 0; i < size_2; i++) {
        parentsIndexTemp_2[i] = i - 1;
    }
    std::string labelsTemp_2[size_2];
    for (int i = 0; i < size_2; i++) {
        labelsTemp_2[i] = std::to_string(i);
    }
    int weightsTemp_2[size_2];

    // initialize the tree
    int size_3 = 1000;
    int parentsIndexTemp_3[size_3];
    for (int i = 0; i < size_3; i++) {
        parentsIndexTemp_3[i] = i - 1;
    }
    std::string labelsTemp_3[size_3];
    for (int i = 0; i < size_3; i++) {
        labelsTemp_3[i] = std::to_string(i);
    }
    int weightsTemp_3[size_3];

    // create a new instances of the test tree
    ParentPointerTree myTree1(size_1, parentsIndexTemp_1, labelsTemp_1, weightsTemp_1);
    ParentPointerTree myTree2(size_2, parentsIndexTemp_2, labelsTemp_2, weightsTemp_2);
    ParentPointerTree myTree3(size_3, parentsIndexTemp_3, labelsTemp_3, weightsTemp_3);
    ParentPointerTree myTreeCustom(size_custom, parentsIndexTemp_custom, labelsTemp_custom, weightsTemp_custom);

    // root node testing
    rootTest(myTree1, 0);
    rootTest(myTree2, 0);
    rootTest(myTree3, 0);

    // weight of node testing
    weightTest(myTree1, 0);
    weightTest(myTree2, 0);
    weightTest(myTree3, 0);

    // weighted union tests
    unionTest(myTreeCustom, 25, 13);

    return 0;
}
