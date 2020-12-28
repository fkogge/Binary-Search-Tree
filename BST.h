#pragma once

#include <string>
#include <sstream>
#include <queue>

/**
 * Binary Search Tree template class. Methods are defined for adding and
 * removing from the tree, checking if the tree is empty, has a
 * given key, number of leaf nodes, height, and width of the tree. Post order,
 * in order, pre order, and level order traversal methods are also defined.
 *
 * @tparam  KeyType Data type of the key
 * @author  Francis Kogge
 * @version 1.0
 * @date    12/09/2020
 */
template<typename KeyType>
class BST {

public:
    /**
     * Constructor - initializes root.
     */
    BST() : root(nullptr) {};

    /**
     * Copy constructor - creates copy of the tree.
     *
     * @param other BST object to copy
     */
    BST(const BST<KeyType> &other) {
        root = copy(other.root);
    }

    /**
     * Overloaded assignment operator - destroys current tree and creates
     * copy of the tree.
     *
     * @param rhs BST object to copy (on right hand side of operator).
     * @return    This BST
     */
    BST<KeyType> &operator=(const BST<KeyType> &rhs) {
        // If assignment is not to this instance
        if (this != &rhs) {
            clear(root);
            root = copy(rhs.root);
        }
        return *this;
    }

    /**
     * Destructor - calls helper method, clear.
     */
    ~BST() {
        clear(root);
    }

    /**
     * Insert a new element into the tree. If the element is already in the
     * tree, this method does nothing.
     *
     * @param newKey Key to insert
     */
    void add(const KeyType &newKey) {
        root = add(root, newKey);
    }

    /**
     * Check if the given key is present in the tree.
     *
     * @param key Key to check
     * @return    True if it is present
     *            False if it is not present
     */
    bool has(const KeyType &key) const {
        return has(root, key);
    }

    /**
     * Removes the given key from the tree.
     *
     * @param key Key to remove
     */
    void remove(const KeyType &key) {
        root = remove(root, key);
    }

    /**
     * Check if this tree is empty.
     *
     * @return True if empty
     *         False if not empty
     */
    bool empty() const {
       return root == nullptr;
    }

    /**
     * Returns the size the tree.
     *
     * @return Size of the tree
     */
    int size() const {
        return size(root);
    }

    /**
     * Returns the number of leaf nodes (node with no child nodes) in the tree.
     *
     * @return Number of leaf nodes in the tree
     */
    int getLeafCount() const {
        return getLeafCount(root);
    }

    /**
     * Returns the height of the tree.
     *
     * @return Height of the tree
     */
    int getHeight() const {
        return getHeight(root);
    }

    /**
     * Returns the width of the tree (the largest number of nodes in the same
     * level).
     *
     * @return Width of the tree
     */
    int getWidth() const {
        int height = getHeight(root), maxWidth = 0;
        // Iterate through each level of the tree
        for (int level = 0; level < height; level++) {
            // Get the current level width
            maxWidth = std::max(getLevelWidth(root, level), maxWidth);
        }
        return maxWidth;
    }

    /**
     * Returns a string representing the in-order traversal.
     *
     * @return Key of each node, in-order
     */
    std::string getInOrderTraversal() const {
        std::ostringstream ss;
        getInOrderTraversal(root, ss);
        return ss.str();
    }

    /**
     * Returns a string representing the pre-order traversal.
     *
     * @return Key of each node, pre-order
     */
    std::string getPreOrderTraversal() const {
        std::ostringstream ss;
        getPreOrderTraversal(root, ss);
        return ss.str();
    }

    /**
     * Returns a string representing the post-order traversal.
     *
     * @return Key of each node, post-order
     */
    std::string getPostOrderTraversal() const {
        std::ostringstream ss;
        getPostOrderTraversal(root, ss);
        return ss.str();
    }

    /**
     * Returns a string representing the level-order traversal.
     *
     * @return Key of each node, level-order
     */
    std::string getLevelOrderTraversal() const {
        // In case client calls on an empty tree
        if (empty()) {
            return "";
        } else {
            std::ostringstream ss;
            // Queue of Node pointers to keep track of order to print
            std::queue<Node*> nodes;
            Node *current;
            nodes.push(root);

            while (!nodes.empty()){
                // Get the node at the front of queue and print it out
                current = nodes.front();
                ss << current->key << " ";
                if (current->left != nullptr) {
                    // Enqueue left child first in order to print the tree
                    // from left to right
                    nodes.push(current->left);
                }
                if (current->right != nullptr) {
                    // Enqueue right child
                    nodes.push(current->right);
                }
                // Remove front element so next node in queue can be printed
                nodes.pop();
            }
            return ss.str();
        }
    }

private:
    /*
     * Node objects which make up the binary search tree
     */
    struct Node {
        KeyType key;
        Node *left, *right; // Left and right child

        /**
         * Node constructor.
         *
         * @param key   Key of the node
         * @param left  Left child
         * @param right Right child
         */
        Node(const KeyType &key, Node *left = nullptr, Node *right = nullptr) {
            this->key = key;
            this->left = left;
            this->right = right;
        }

        /**
        * Find the maximum node's value.
        *
        * @return Key of the right-most node in this subtree
        */
        const KeyType &findMax() const {
            if (right == nullptr) {
                return this->key;
            } else {
                return right->findMax();
            }
        }

        /**
         * Checks if this node is a leaf.
         *
         * @return True if it is a leaf
         *         False if it is not a leaf
         */
        bool isLeaf() const {
            // Leaf node must have no left child and no right child
            return this->left == nullptr && this->right == nullptr;
        }
    };

    Node *root; // Root of the tree

    /**
    * Recursive helper method for add.
     *
    * @param current Subtree to which to add key
    * @param newKey  Key to add
    * @return        Current node
    */
    static Node *add(Node *current, const KeyType &newKey) {
        if (current == nullptr) {
            // Add node if we found a spot in the tree that is null
            current = new Node(newKey);
        }

        if (newKey < current->key) {
            // Find a spot to the left of the current node
            current->left = add(current->left, newKey);
        } else if (newKey > current->key) {
            // Find a spot to the right of the current node
            current->right = add(current->right, newKey);
        }
        return current;
    }

    /**
    * Recursive helper method for has.
     *
    * @param current Subtree in which to look for key
    * @param key     Key to search for
    * @return        True if found
    *                False if not found
    */
    static bool has(Node *current, const KeyType &key) {
        // If root is null or we've recursed down the tree and reach null
        if (current == nullptr) {
            return false;
        }

        if (key < current->key) {
            // Check the left subtree
            return has(current->left, key);
        } else if (key > current->key) {
            // Check the right subtree
            return has(current->right, key);
        } else {
            // Key has been found
            return true;
        }
    }

    /**
     * Recursive helper method for remove.
     *
     * @param current Subtree from which to remove key
     * @param key     Key to remove
     * @return        Current node or replacement node (if current is deleted)
     */
    static Node *remove(Node *current, const KeyType &key) {
        // If we recursed down the tree and reached null, key is not in the tree
        if (current == nullptr) {
            return nullptr;
        }

        if (key < current->key) {
            // Check the left subtree
            current->left = remove(current->left, key);
            return current;
        } else if (key > current->key) {
            // Check the right subtree
            current->right = remove(current->right, key);
            return current;
        // If current node has the key, we found the node to remove
        } else {
            if (current->left == nullptr) {
                // Replace the current node with its right child
                Node *replacement = current->right;
                delete current;
                return replacement;
            } else if (current->right == nullptr) {
                // Replace the current node with its left child
                Node *replacement = current->left;
                delete current;
                return replacement;
            } else {
                // Find max value node from the left subtree, and replace the
                // current node's key with that value
                current->key = current->left->findMax();
                // Current node has been replaced, so now we can remove the node
                // that had the replacement key
                current->left = remove(current->left, current->key);
                return current;
            }
        }
    }

    /**
     * Recursive helper method for size.
     *
     * @param current Subtree to find size of
     * @return        Number of nodes in the tree
     */
    static int size(Node *current) {
        // Once a null node is reached, stop traversing sub-tree
        if (current == nullptr) {
            // Adds 0 to recursive sum, indicating the current sub-tree is empty
            return 0;
        }

        // Return size of left and right sub-trees, plus 1 to represent
        // current node
        return size(current->left) + 1 + size(current->right);
    }

    /**
     * Recursive helper method for getLeafCount.
     *
     * @param current Subtree in which to find number of leaves
     * @return        Number of leaf nodes
     */
    static int getLeafCount(Node *current) {
        // Once null node is reached, stop traversing sub-tree
        if (current == nullptr) {
            // Adds 0 to recursive sum -> empty sub-tree implies no leaves
            return 0;
        }

        if (current->isLeaf()) {
            // 1 is added to recursive sum, meaning a leaf was found
            return 1;
        } else {
            // Get the leaf count of the left sub-tree and the right sub-tree
            return getLeafCount(current->left) + getLeafCount(current->right);
        }
    }

    /**
     * Recursive helper method for getHeight.
     *
     * @param current Subtree to find height of
     * @return        Height of the tree
     */
    static int getHeight(Node *current) {
        // If null node is reached, don't add anything to the recursive sum
        if (current == nullptr) {
            return 0;
        } else {
            // Return 1 (to represent current node being visited) plus the
            // height of the subtree which has the greater height
            return 1 + std::max(getHeight(current->left),
                                getHeight(current->right));
        }
    }

    /**
     * Recursive helper method for getWidth that returns the width of an
     * individual level of the tree.
     *
     * @param current       Current node being visited
     * @param remainingLvls Initially represents the level to get the width of.
     *                      While recursing down the tree, it represents how
     *                      many levels are left to go down until we reach
     *                      the level we would like to obtain the width of.
     * @return              Width of the level
     */
    static int getLevelWidth(Node *current, int remainingLvls) {
        // Don't add anything to recursive sum if null node is reached
        if (current == nullptr) {
            return 0;
        }
        // If there are no more levels left to go down (or case where root is
        // the only node)
        if (remainingLvls == 0) {
            // Adds 1 to recursive sum to represent the current visited node
            return 1;
        } else {
            // Start at root and walk down the tree with each recursive call
            // until no more levels are left to go down (remainingLvls == 0)
            return getLevelWidth(current->left, remainingLvls - 1) +
                   getLevelWidth(current->right, remainingLvls - 1);
        }
    }

    /**
     * Recursive helper method for getInOrderTraversal.
     *
     * @param current Subtree to traverse, in-order
     * @param ss      Output string stream
     */
    static void getInOrderTraversal(Node *current, std::ostringstream &ss) {
        if (current == nullptr)  {
            return;
        }

        // Print left, current, then right node to string stream
        getInOrderTraversal(current->left, ss);
        ss << current->key << " ";
        getInOrderTraversal(current->right, ss);
    }

    /**
     * Recursive helper method for getPreOrderTraversal.
     *
     * @param current Subtree to traverse, pre-order
     * @param ss      Output string stream
     */
    static void getPreOrderTraversal(Node *current, std::ostringstream &ss) {
        if (current == nullptr)  {
            return;
        }

        // Print current, left, then right node to string stream
        ss << current->key << " ";
        getPreOrderTraversal(current->left, ss);
        getPreOrderTraversal(current->right, ss);
    }

    /**
     * Recursive helper method for getPostOrderTraversal.
     *
     * @param current Subtree to traverse, post-order
     * @param ss      Output string stream
     */
    static void getPostOrderTraversal(Node *current, std::ostringstream &ss) {
        if (current == nullptr)  {
            return;
        }

        // Print left, right, then current node to string stream
        getPostOrderTraversal(current->left, ss);
        getPostOrderTraversal(current->right, ss);
        ss << current->key << " ";
    }

    /**
     * Recursive helper method to copy a subtree.
     *
     * @param current Root of the subtree to copy
     * @return        Copy of the subtree
     */
    static Node *copy(Node *current) {
        if (current == nullptr) {
            return nullptr;
        } else {
            return new Node(current->key, copy(current->left),
                            copy(current->right));
        }
    }

    /**
     * Recursive helper method to delete a subtree.
     *
     * @param current Root of the subtree to delete
     */
    void clear(Node *current) {
        if (current != nullptr) {
            clear(current->left);
            clear(current->right);
            delete current;
        }
    }
};