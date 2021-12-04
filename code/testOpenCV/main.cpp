#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include "BinarySearchTree.cpp"

using namespace cv;
using namespace std;

int main() {
    BinarySearchTree* tree = new BinarySearchTree();

    VideoCapture capture("/Users/a_hognose_snake/CLionProjects/testOpenCV/videos/Thank_You_Mom-vimeo-480x270.mp4");

    CascadeClassifier detector;

    if (!detector.load("/Users/a_hognose_snake/CLionProjects/testOpenCV/opencv2/haarcascade_frontalface_alt.xml"))
        cout << "No se puede abrir clasificador." << endl;


    while (true){
        Mat dest, gray, imagen;

        capture >> imagen;

        cvtColor(imagen, gray, COLOR_BGR2GRAY);
        equalizeHist(gray, dest);

        vector<Rect> faces;

        detector.detectMultiScale(dest, faces, 1.2, 3, 0, Size(25, 25));

        for (int i = 0; i < faces.size(); i++){

            // Segundo de la deteccion (frame) donde encuentra la cara
            long timeStamp = capture.get(1);

            // Dato que tiene la informacion por frame de cara detectado
            // rc = datos de 1 cara
            Rect rc = faces[i];

            // Corta y separa la cara del frame del video
            Mat imgCrop = imagen(rc);

            // Muestra la imagen de la cara detectada en una nueva ventana
            imshow(to_string(i),imgCrop);

            // Guarda el crop de la cara detectada en en una carpeta segun el timeStamp
            imwrite("/Users/a_hognose_snake/CLionProjects/testOpenCV/faces/"+to_string(timeStamp)+ ".png", imgCrop);

            rectangle(imagen, Point(rc.x, rc.y), Point(rc.x + rc.width, rc.y + rc.height), CV_RGB(255, 0, 0), 2);


        }
        imshow("Taller EDD", imagen);
        // Insertar al arbol y mostrar ID's
        tree->insert(imagen);

        if (waitKey(1) >= 0){
            break;
        }
    }
    return 0;
}