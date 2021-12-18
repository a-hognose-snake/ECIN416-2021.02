#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <string>
#include "BinarySearchTree.cpp"
#include <ctime>

using namespace cv;
using namespace std;

int main() {

    time_t now = time(0);

    //Instance of the binary tree data structure
    BinarySearchTree* tree = new BinarySearchTree();

    //  Video we will use to detect faces
    VideoCapture capture("Videos/VideoFotos2.mp4");

    //  Video of the face detection session
    //string pathVideo = "Sesiones/session_0.avi"+"hola"  ;
    string pathVideo = "Sesiones/session_" + typeToString(now) + ".avi";
    VideoWriter video(pathVideo, VideoWriter::fourcc('M', 'J', 'P', 'G'), 10, Size(480, 270));

    //  Classifier library from openCV
    CascadeClassifier detector;

    //  If detector is not available:
    if (!detector.load("Classifiers/haarcascade_frontalface_alt.xml"))
        cout << "No se puede abrir clasificador." << endl;
    //  loop
    while (true) {
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

        for (int i = 0; i < faces.size(); i++) {
            // Frame where the face was detected
            Rect rc = faces[i];

            // Cuts and save a crop of the frame where the face was detected
            imgCrop = imagen(rc);

            // Show a crop of the detected face in a new window
            imshow(to_string(i), imgCrop);

            // Draws a square around the face detected
            rectangle(imagen, Point(rc.x, rc.y), Point(rc.x + rc.width, rc.y + rc.height), CV_RGB(255, 0, 0), 2);
            
            if (imagen.empty()) {
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

        if (waitKey(1) >= 0) {
            break;
        }
    }
    

    // End stream
    capture.release();
    video.release();

    tree->createList1(typeToString(now));//Se le podria pasar la fecha

    int cant;
    cout << "Ingrese el numero de identidades que quiere revisar con mas segundos en el video: " << endl;
    cin >> cant;
    
    cout << "\tREPORTE" << endl;
    
    tree->getPrint(cant); //NUEVA FORMA

    // Destroy all windows and finish the process
    destroyAllWindows();
    return 0;
}