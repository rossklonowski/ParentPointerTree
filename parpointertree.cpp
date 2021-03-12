/*

    Parent Pointer Tree

    Project Treeps

    Ross Klonowski
*/

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
                std::cout << label[i] << " ";
            }
            std::cout << std::endl;

            std::cout << "Weights Array:      ";
            for (int i = 0; i < SIZE; i++) {
                std::cout << weights[i] << " ";
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

int main() {

    // initialize the tree
    int size = 26;
    int parentsIndexTemp[] = {  -1,  25,   1,  13,  -1,   8,   19,  19,  21,  1,   11,  0,   10, -1,   13,  13,  13,  1,   12,  8,   8,   4,   17,  2,   3, -1};
    std::string labelsTemp[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };

    int weightsTemp[size];
    for (int i = 0; i < size; i++) {
        weightsTemp[i] = 0;
    }

    // create a new instance of the test tree
    ParentPointerTree myTree(size, parentsIndexTemp, labelsTemp, weightsTemp);

    // root node testing
    std::cout << "\n\nRoot Node Tests" << std::endl;
    std::cout << "-------------------------" << std::endl;
    int startNodeIndex = 0;

    startNodeIndex = 3;
    std::cout << "The Root of Node " << labelsTemp[startNodeIndex] << "(" << startNodeIndex << ") ";
    std::cout << "is Node " << labelsTemp[myTree.find(startNodeIndex)] << "(" << myTree.find(startNodeIndex) << ")" << std::endl;

    startNodeIndex = 4;
    std::cout << "The Root of Node " << labelsTemp[startNodeIndex] << "(" << startNodeIndex << ") ";
    std::cout << "is Node " << labelsTemp[myTree.find(startNodeIndex)] << "(" << myTree.find(startNodeIndex) << ")" << std::endl;

    startNodeIndex = 8;
    std::cout << "The Root of Node " << labelsTemp[startNodeIndex] << "(" << startNodeIndex << ") ";
    std::cout << "is Node " << labelsTemp[myTree.find(startNodeIndex)] << "(" << myTree.find(startNodeIndex) << ")" << std::endl;

    // weight of node testing
    std::cout << "\n\nWeight of node testing" << std::endl;
    std::cout << "-------------------------" << std::endl;
    int rootNode = 0;
    
    rootNode = 7;
    std::cout << "Weight of " << labelsTemp[rootNode] << "(" << rootNode << ") is ";
    std::cout << myTree.weight(rootNode) << std::endl; 
    
    rootNode = 0;
    std::cout << "Weight of " << labelsTemp[rootNode] << "(" << rootNode << ") is ";
    std::cout << myTree.weight(rootNode) << std::endl; 

    std::cout << std::endl;
    
    // weighted union tests
    std::cout << "\n\nWeighted Union Tests" << std::endl;
    std::cout << "-------------------------" << std::endl;
    int node1 = 0;
    int node2 = 0;
    
    node1 = 6;
    node2 = 10;
    std::cout << "Union " << node1 << " and " << node2 << std::endl;
    std::cout << "Before: " << std::endl;
    myTree.printArrays();
    //myTree.unionNodes(6, 10);
    myTree.unionNodes(13, 0);
    std::cout << "After: " << std::endl;
    myTree.printArrays();

    return 0;
}
