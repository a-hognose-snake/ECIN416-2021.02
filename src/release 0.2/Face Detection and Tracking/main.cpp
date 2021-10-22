#include <opencv2/opencv.hpp>
#include <string>

using namespace cv;
using namespace std;


// Nodo struct contiene un dato string que es el path de la imagen a data int y un puntero al siguiente nodo
struct Nodo {
    string data;
    Nodo *next;
};

class LinkedList{
    // Puntero de la cabeza de la lista
    Nodo* head;

public:

    // Costructor de la lista. Inicializa el puntero cabeza
    LinkedList()
    {
        head = NULL;
    }

    // Inserta al principio de la lista
    void insert(string dir)
    {
        // Crea nuevo nodo
        Nodo* newNodo = new Nodo;
        newNodo->data = dir;
        newNodo->next = NULL;

        // Si la lista esta vacia, hace que el node sea el cabezal
        if (head == NULL)
            head = newNodo;
        // Si no, hace el nuevo nodo cabeza y el que fue cabezal, el siguiente de ese
        // La insercion es adelante
        else
        {
            newNodo->next = head;
            head = newNodo;
        }
    }

    // Muestra la lista
    void display()
    {
        Nodo* temp = head;
        while(temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};


int main(){
    LinkedList listaImg;

    VideoCapture capture("/Users/a_hognose_snake/CLionProjects/Face Detection and Tracking/videos/personasCaminando.mp4");

    CascadeClassifier detector;

    if (!detector.load("/Applications/opencv-4.5.3/data/haarcascades/haarcascade_frontalface_alt.xml"))
        cout << "No se puede abrir clasificador." << endl;


    while (true){
        Mat dest, gray, imagen;

        capture >> imagen;

        cvtColor(imagen, gray, COLOR_BGR2GRAY);
        equalizeHist(gray, dest);

        vector<Rect> faces;

        detector.detectMultiScale(dest, faces, 1.2, 3, 0, Size(60, 60));

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
            imwrite("/Users/a_hognose_snake/CLionProjects/Face Detection and Tracking/faces/"+to_string(timeStamp)+ ".png", imgCrop);

            rectangle(imagen, Point(rc.x, rc.y), Point(rc.x + rc.width, rc.y + rc.height), CV_RGB(255, 0, 0), 2);

            // Agrega a la linkedList
            listaImg.insert("/Users/a_hognose_snake/CLionProjects/Face Detection and Tracking/faces/"+to_string(timeStamp)+ ".png");

        }

        imshow("EDD Taller 1 - Face Detection in Video", imagen);

        // Muestra linked list con los path de las caras detectadas en el video
        listaImg.display();

        if (waitKey(1) >= 0){
            break;
        }
    }
    return 0;
}
