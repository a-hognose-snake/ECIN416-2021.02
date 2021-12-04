#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include "LinkedList.cpp"

using namespace std;
using namespace cv;

class BinarySearchTree{
    LinkedList list;

    struct BinarySearchTreeNode {
        Mat image;
        int key;
        BinarySearchTreeNode* left;
        BinarySearchTreeNode* right;
    };

    const int DIFFERENT = 1700;
    const int SIMILAR = 1300;
    int counter;
    BinarySearchTreeNode* root;

    BinarySearchTreeNode* makeEmpty(BinarySearchTreeNode* t) {
        if(t == nullptr)
            counter = 0;
            return nullptr;
    }

    BinarySearchTreeNode* insert(Mat x, BinarySearchTreeNode* t)
    {

        if(t == nullptr)
        {
            t = new BinarySearchTreeNode();
            t->key = ++counter;
            t->image = x;
            t->left =  nullptr;
            t->right = nullptr;

        }
        else if(SIMILAR < euclideanDistance(t->image, x)
        && DIFFERENT > euclideanDistance(t->image, x)){
            t->left = insert(x, t->left);
        }
        else if(DIFFERENT <= euclideanDistance(t->image, x))
        {
            t->right = insert(x, t->right);
        }
        else
        {
            t->image = x;
            cout << "Es la misma cara."<< endl;
            string path = "Caras/" + to_string(t->key) + ".png";
            imwrite(path, t->image);
            list.insert(path,t->key);
            cout << "ID: " << t->key << endl;
        }
        return t;
    }

public:
    BinarySearchTree() {
        counter = 0;
        root = nullptr;
    }

    ~BinarySearchTree() {
        root = makeEmpty(root);
    }

    double euclideanDistance(Mat img1, Mat img2){
        return norm(img1, img2,NORM_L2);
    }

    void insert(Mat x) {
        root = insert(x, root);
    }

    void displaylinkedList() {
        list.display();
    };

};