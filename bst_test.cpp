/**
 * This program tests the functionality of the Binary Search Tree (BST)
 * implementation class. The BST is built based on data values written in a
 * text file, which the user shall provide a file path for.
 *
 * @author  Francis Kogge
 * @version 1.0
 * @date    12/09/2020
 */

#include <iostream>
#include <fstream>
#include <string>
#include "BST.h"

using namespace std;

/**
 * Displays short goodbye message.
 */
void outro() {
    cout << "\n\nGoodbye, and thanks for using the Binary Search Tree program!"
         << endl;
}

/**
 * Helper method for displaying stars.
 *
 * @param n Number of stars to print
 */
void printStars(int n) {
    for (int i = 0; i < n; i++) {
        cout << "*";
    }
}

/**
 * Displays title indicating what BSTx method we're testing.
 *
 * @param method Method name/type
 */
void displayTestTitle(const string &method) {
    cout << endl;
    printStars(2);
    cout << " " << method << " ";
    printStars(2);
    cout << endl;
}

/**
 * Tests remove method for a BSTx object.
 *
 * @tparam T    Data type of the BSTx and array elements
 * @param bst   BSTx object
 * @param array Array holding data to remove
 * @param size  Size of the array
 */
template<typename T>
void testRemove(BST<T> &bst, const T *array, int size) {
    displayTestTitle("TEST REMOVE");
    cout << "Removing in this order: ";
    for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
        bst.remove(array[i]);
    }
    cout << endl;
}

/**
 * Tests add method of a BSTx object. Adds data from the specified array.
 *
 * @tparam T    Data type of the BSTx object and array elements
 * @param bst   BSTx object
 * @param array Array holding data to add
 * @param size  Size of the array
 */
template<typename T>
void testAdd(BST<T> &bst, const T *array, int size) {
    displayTestTitle("TEST ADD (again)");
    cout << "Inserting in this order: ";
    for (int i = 0; i < size; i++)  {
        cout << array[i] << " ";
        bst.add(array[i]);
    }
    cout << endl;
}

/**
 * Tests traversal methods for a BSTx object.
 *
 * @tparam T  Data type of BST object
 * @param bst BST object
 */
template<typename T>
void testTraversal(const BST<T> &bst) {
    displayTestTitle("TEST TRAVERSALS");
    cout << "Pre-order:    " << bst.getPreOrderTraversal() << endl;
    cout << "In-order:     " << bst.getInOrderTraversal() << endl;
    cout << "Post-order:   " << bst.getPostOrderTraversal() << endl;
    cout << "Level-order:  " << bst.getLevelOrderTraversal() << endl;
}

/**
 * Test has method for a BSTx object.
 *
 * @tparam T       Data type of the BSTx object and array elements
 * @param bst      BSTx object
 * @param array    Array holding data to check if BST has
 * @param size     Size of the array
 */
template<typename T>
void testHas(const BST<T> &bst, const T *array, int size) {
    T data;
    displayTestTitle("TEST HAS");
    for (int i = 0; i < size; i++) {
        data = array[i];
        cout << "has(" << data << "): " << (bst.has(data) ? "True" : "False")
             << endl;
    }
}

/**
 * Adds initial data to a BSTx object of type string.
 *
 * @param bst      BSTx object
 * @param dataFile Name of the file
 * @return         True if file is valid and read successfully
 *                 False if invalid file path
 */
bool addStringTree(BST<string> &bst, const string &dataFile) {
    ifstream inFile(dataFile); // For reading the file
    // If file is opened successfully
    if (inFile) {
        string line;
        displayTestTitle("TEST ADD");
        cout << "Inserting in this order: ";
        // Capture each line from file (one line may have multiple words but is
        // accounted for as one string)
        while (getline(inFile, line)) {
            // Remove carriage return character if found at the end of the line
            if (line.find('\r') != string::npos) {
                line.erase(line.find('\r'), 1);
            }
            cout << line << " ";
            bst.add(line);
        }
        cout << endl;
        inFile.close();
        return true;
    } else {
        cerr << "Error opening file." << endl;
        return false;
    }
}

/**
 * Adds initial data to a BSTx object of a primitive data type.
 *
 * @tparam T       Data type of the of the BSTx object (must be primitive)
 * @param bst      BSTx object
 * @param dataFile Name of the file
 * @return         True if file is valid and read successfully
 *                 False if invalid file path
 */
template<typename T>
bool addPrimitiveTree(BST<T> &bst, const string &dataFile) {
    ifstream inFile(dataFile); // For reading the file
    // If file is opened successfully
    if (inFile) {
        T data;
        displayTestTitle("TEST ADD");
        cout << "Inserting in this order: ";
        // Reads all numbers from the file
        while (inFile >> data) {
            cout << data << " ";
            bst.add(data);
        }
        cout << endl;
        inFile.close();
        return true;
    } else {
        cerr << "Error opening file." << endl;
        return false;
    }
}

/**
 * Retrieves name of the file from the user.
 *
 * @param type Type of file (refers to the data type of tree we plan to create)
 * @return     Name of the file
 */
string getFileName(const string &type) {
    string fileName;
    cout << "\nEnter " << type << " file: ";
    cin >> fileName;
    return fileName;
}

/**
 * Checks the properties of a BST by calling size, getLeafCount, getHeight,
 * getWidth, and empty methods.
 *
 * @tparam T  Data type of BSTx object
 * @param bst BSTx object
 */
template<typename T>
void checkBSTProperties(const BST<T> &bst) {
    cout << "# of nodes:     " << bst.size() << endl;
    cout << "# of leaves:    " << bst.getLeafCount() << endl;
    cout << "BST height:     " << bst.getHeight() << endl;
    cout << "BST width:      " << bst.getWidth() << endl;
    cout << "BST is empty:   " << (bst.empty() ? "True" : "False") << endl;
}

/**
 * Displays title indicating what type of tree we're creating.
 *
 * @param type Type of tree
 */
void displayTitle(const string &type) {
    cout << endl << endl;
    printStars(30);
    cout << "\n* " << type << " BINARY SEARCH TREE *" << endl;
    printStars(30);
    cout << endl;
}

/**
 * Displays short introduction.
 */
void intro() {
    cout << "\nWelcome to the Binary Search Tree (BST) program! This program\n"
            "tests the functionality of the BST template class. Since it is\n"
            "a template class, define which data type you would like your BST\n"
            "to be and test the methods from the BST class." << endl;
}

/**
 * Tests the functionality of the Binary Search Tree (BST) template class.
 * The user is to provide a file path for the program to retrieve data from
 * that can be added to a BST object. The various methods of the BST class
 * will then be tested.
 *
 * @return 0 Indicates successful program.
 */
int main() {
    string dataFile; // To hold the name of the user specified data file
    intro();

    // Start tests for a BST of integers
    displayTitle("INTEGER");
    BST<int> intBST;
    displayTestTitle("CREATE BST");
    checkBSTProperties(intBST);
    dataFile = getFileName("integer");

    // Test adding to empty tree and run tests only if successful
    if (addPrimitiveTree(intBST, dataFile)) {
        // Test property checking methods
        checkBSTProperties(intBST);

        // Test traversal methods
        testTraversal(intBST);

        // Test has method
        int testInts[] = {20, 40, 10, 70, 99, -2, 59, 43};
        testHas(intBST, testInts, 8);

        // Test remove method
        testRemove(intBST, testInts, 8);
        checkBSTProperties(intBST);
        // Test traversal (make sure removals were successful)
        testTraversal(intBST);

        // Test add method again
        testAdd(intBST, testInts, 8);
        checkBSTProperties(intBST);
        // Test traversal (make sure insertions were successful)
        testTraversal(intBST);
    }

    // Start tests for a BST of strings
    displayTitle("STRING");
    BST<string> stringBST;
    displayTestTitle("CREATE BST");
    checkBSTProperties(stringBST);
    dataFile = getFileName("string");

    // Test adding to empty tree and run tests only if successful
    if (addStringTree(stringBST, dataFile)) {
        // Test property checking methods
        checkBSTProperties(stringBST);

        // Test traversal methods
        testTraversal(stringBST);

        // Test has method
        string testStrings[] = {"gene", "mary", "bea", "uma", "yan", "amy",
                                "ron", "opal"};
        testHas(stringBST, testStrings, 8);

        // Test remove method
        testRemove(stringBST, testStrings, 8);
        checkBSTProperties(stringBST);
        // Test traversal (make sure removals were successful)
        testTraversal(stringBST);

        // Test add method again
        testAdd(stringBST, testStrings, 8);
        checkBSTProperties(stringBST);
        // Test traversal (make sure insertions were successful)
        testTraversal(stringBST);
    }

    outro();

    return 0;
}
