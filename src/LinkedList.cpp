#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
struct Nodo {
    string data; //Contains the path of the image
    int tiempo; //Contains the number of frames that the image is on screen
    int id; //Contains the face ID
    Nodo* next; //Next node
};

class LinkedList {
    //Pointer of the header 
    Nodo* head;

public:
    // Constructor, initializes the head pointer
    LinkedList()
    {
        head = nullptr;
    }

    // Inserts at the beginning of the list
    void insert(string path, int key)
    {   
        //Search for a node with the same ID, in case it does not exist creates a new nodo and its added to the list
        if (buscar(key) == nullptr) {
            // Create a new node
            Nodo* newNodo = new Nodo;
            newNodo->data = path;
            newNodo->next = nullptr;
            newNodo->id = key;
            newNodo->tiempo = 1;

            //If the list is empty, the new node is the header
            if (head == nullptr) {
                head = newNodo;
            }
            // Otherwise, the previous header node is next, and the new added node is the new header;
            // upfront adding
            else
            {
                newNodo->next = head;
                head = newNodo;
            }
        }
        //En caso contrario aumenta en 1 el tiempo de la imagen, (aparecio en otro frame)
        //Otherwise the time of the image is aumented in 1, (It appeared in another frame)
        else {
            Nodo* existente = buscar(key);
            existente->tiempo = existente->tiempo + 1;
        }

    }

    //Deploy the list according to the number of faces that the user wants to see, with the path, id and time
    
    void display(int cant)
    {
        Nodo* temp = head;
        int cont = 0;
        while (temp != nullptr && cont < cant)
        {
            cout << "Imagen ID: " << temp->id << " Path: " << temp->data << " Cantidad de Frames: " << temp->tiempo << endl;
            Mat imagen = imread(temp->data);
            // The image of the face is displayed on the screen
            imshow("ID: " + temp->id, imagen);
            temp = temp->next;
            cont++;
        }
        cout << endl;
    }

    //Search for a node with the respective key/ID
    Nodo* buscar(int key) {
        Nodo* current = head;
        while (current != nullptr) {
            if (current->id == key) {
                return current;
            }
            current = current->next;
        }return nullptr;
    }

    //Sorts the slist in descending order
    void sort() {
        Nodo* current = head;
        while (current != nullptr) {
            Nodo* next = current->next;
            while (next != nullptr) {
                if (current->tiempo < next->tiempo) {
                    string auxData = current->data;
                    int auxTiempo = current->tiempo;
                    int auxId = current->id;
                    current->data = next->data;
                    current->tiempo = next->tiempo;
                    current->id = next->id;
                    next->data = auxData;
                    next->tiempo = auxTiempo;
                    next->id = auxId;
                }
                next = next->next;
            }
            current = current->next;
        }
    }

};