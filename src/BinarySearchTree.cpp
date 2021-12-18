#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <string>
#include <stack>
#include <fstream>

using namespace std;
using namespace cv;

class BinarySearchTree {
    
    struct BinarySearchTreeNode {
        Mat image;
        int key;
        int time;
        string path;
        BinarySearchTreeNode* left;
        BinarySearchTreeNode* right;
    };


    const int DIFFERENT = 1700;
    const int SIMILAR = 1300;
    int counter;
    //int frameCounter;
    BinarySearchTreeNode* root;

    //The tree is emptied, all the elements are errased.
    BinarySearchTreeNode* makeEmpty(BinarySearchTreeNode* t) {
        if (t == nullptr)
            counter = 0;
        return nullptr;
    }

    //A new image is inserted into the tree, (For each identified face on each frame)
    BinarySearchTreeNode* insert(Mat x, BinarySearchTreeNode* t)
    {
        //frameCounter++;
        //cout << frameCounter << endl;
        if (t == nullptr)
        {
            t = new BinarySearchTreeNode();
            t->key = ++counter;
            t->image = x;
            t->left = nullptr;
            t->right = nullptr;

        }
        else if (SIMILAR < euclideanDistance(t->image, x)
            && DIFFERENT > euclideanDistance(t->image, x)) {
            t->left = insert(x, t->left);
        }
        else if (DIFFERENT <= euclideanDistance(t->image, x))
        {
            t->right = insert(x, t->right);
        }
        else
        {
            //if the ID/person is already on the tree the parameters time and image are updated with the las time the person spend on frame
            t->image = x;
            t->time += 1;
            //cout << "Es la misma cara." << endl;
            string path = "Caras/" + to_string(t->key) + ".png";
            imwrite(path, t->image);
            t->path = path;
            cout << "ID: " << t->key << endl;
            cout << "Time: " << t->time << endl;
        }
        return t;
    }

    stack <BinarySearchTreeNode*> createStack() {
        stack <BinarySearchTreeNode*> pilaAux;
        stack <BinarySearchTreeNode*> output;
        if (root != nullptr) {
            pilaAux.push(root);
            while (!pilaAux.empty()) {
                BinarySearchTreeNode* curr = pilaAux.top();
                pilaAux.pop();

                output.push(curr);

                if (curr->left != nullptr) {
                    pilaAux.push(curr->left);
                }
                if (curr->right != nullptr) {
                    pilaAux.push(curr->right);
                }
            }
        }
        return output;
    }

    stack<BinarySearchTreeNode*> sortStack(stack<BinarySearchTreeNode*>& input)
    {
        stack<BinarySearchTreeNode*> tmpStack;

        while (!input.empty())
        {
            // pop out the first element
            BinarySearchTreeNode* tmp = input.top();
            input.pop();

            // while temporary stack is not empty and top
            // of stack is greater than temp
            while (!tmpStack.empty() && tmpStack.top()->time > tmp->time)
            {
                // pop from temporary stack and push
                // it to the input stack
                input.push(tmpStack.top());
                tmpStack.pop();
            }

            // push temp in temporary of stack
            tmpStack.push(tmp);
        }

        return tmpStack;
    }




public:
    BinarySearchTree() {
        counter = 0;
        root = nullptr;
    }

    ~BinarySearchTree() {
        root = makeEmpty(root);
    }

    double euclideanDistance(Mat img1, Mat img2) {
        return norm(img1, img2, NORM_L2);
    }

    void insert(Mat x) {
        root = insert(x, root);
    }


    void getPrint(int cant) {
        stack <BinarySearchTreeNode*> nodesStack = createStack();
        stack <BinarySearchTreeNode*> orderStack = sortStack(nodesStack);

        int cont = 0;
        while (!orderStack.empty() && cont < cant)
        {
            BinarySearchTreeNode* nodeData = orderStack.top();
            
            //Mat imagen = imread(nodeData->path);
            //putText(imagen, to_string(nodeData->key), Point(10, imagen.rows / 2), FONT_HERSHEY_DUPLEX, 1.0, CV_RGB(118, 185, 0), 2);
            //imshow("Identidad", imagen);
            //waitKey();
                   
            cout << "* " << nodeData->key << endl;
            cout << "\t" << nodeData->time << "frames" << endl;
            cout << "\t" << nodeData->path << endl;
            orderStack.pop();
            cont++;
        }
    }

    //The list with the information of the detected ID's is created
    void createList1(string timeStamp) {
        ofstream file;
        stack <BinarySearchTreeNode*> nodesStack = createStack();
        file.open("Listados/Identidades_Detectadas"+ timeStamp +".txt");
        file << "Identidades:" << endl;
        while (!nodesStack.empty())
        {
            BinarySearchTreeNode* nodeData = nodesStack.top();
            file << "* " << nodeData->key << endl;
            file << "\t" << nodeData->time << "frames" << endl;
            file << "\t" << nodeData->path  << endl;
            nodesStack.pop();
        }
        file.close();
    }

   
};