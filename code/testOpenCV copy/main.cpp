#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <string>
#include "BinarySearchTree.cpp"
#include <ctime>
#include <chrono>

using namespace cv;
using namespace std;

int main() {

    //Instance of the binary tree data structure
    BinarySearchTree* tree = new BinarySearchTree();

    //  Video we will use to detect faces
    VideoCapture capture("/Users/a_hognose_snake/CLionProjects/testOpenCV copy/videos/VideoFotos2.mp4");

    //  Video of the face detection session
    VideoWriter video("/Users/a_hognose_snake/CLionProjects/testOpenCV/sessions/session_0.avi",VideoWriter::fourcc('M','J','P','G'),10, Size(480,270));

    //  Classifier library from openCV
    CascadeClassifier detector;

    //  If detector is not available:
    if (!detector.load("/Users/a_hognose_snake/CLionProjects/testOpenCV/opencv2/haarcascade_frontalface_alt.xml"))
        cout << "No se puede abrir clasificador." << endl;

    //  loop
    while (true){
        Mat dest, gray, imagen, imgCrop;

        //  Capture frame by frame
        capture >> imagen;
        if (imagen.empty()) {
            break;
        }

        //   Transformation to make the classifier work better
        cvtColor(imagen, gray, COLOR_BGR2GRAY);
        equalizeHist(gray, dest);

        //  Vector of video frames where faces were detected
        vector<Rect> faces;

        detector.detectMultiScale(dest, faces, 1.2, 3, 0, Size(25, 25));

        for (int i = 0; i < faces.size(); i++){
            // Frame where the face was detected
            Rect rc = faces[i];

            // Cuts and save a crop of the frame where the face was detected
            imgCrop = imagen(rc);

            // Show a crop of the detected face in a new window
            imshow(to_string(i),imgCrop);

            // Draws a square around the face detected
            rectangle(imagen, Point(rc.x, rc.y), Point(rc.x + rc.width, rc.y + rc.height), CV_RGB(255, 0, 0), 2);

            if (imagen.empty()){
                break;
            }
            // Write the frame into the corresponding video file in /sessions
            video.write(imagen);
        }
        // Show video of the detection and sets a tittle for the window
        imshow("Taller EDD - Valentina y Josefina", imagen);
        if (imgCrop.empty()) {
            break;
        }

        //  Resize image so our code can work
        Mat resizedDown;
        resize(imgCrop, resizedDown, Size(25, 25), INTER_LINEAR);

        //  Insert image to the tree and show ID's
        tree->insert(resizedDown);

        if (waitKey(1) >= 0){
            break;
        }
    }

    tree->displaylinkedList();

    // End stream
    capture.release();
    video.release();

    // Destroy all windows and finish the process
    destroyAllWindows();
    return 0;
}