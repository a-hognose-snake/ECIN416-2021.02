#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;
using namespace cv;

class BinarySearchTree{

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
            return nullptr;
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
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
            //cout << "Distancia euclidea (Igual): " << euclideanDistance(t->image, x) << endl;
            //changes the image
            t->image = x;
            cout << "Misma cara." << endl;
        }
        //cout << "Distancia euclidea: " << euclideanDistance(t->image, x) << endl;

        cout << "ID: " << t->key << endl;
        return t;


    }

    void inorder(BinarySearchTreeNode* t) {
        if(t == nullptr)
        {
            return;
        }
        else{
            inorder(t->left);
            cout << t->image << endl;
            inorder(t->right);
        }
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

    void display() {
        inorder(root);
        cout << endl;
    }
};