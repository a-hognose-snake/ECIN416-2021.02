#include <iostream>
#include <string>

using namespace std;

struct Nodo {
    string data; //Guarda el Path de la imagen
    int tiempo; //Guarda el numero de frames que la imagen se encuentra en pantalla
    int id;
    Nodo *next; //Siguiente nodo
};

class LinkedList {
    // Puntero de la cabeza de la lista
    Nodo* head;

public:
    // Constructor de la lista. Inicializa el puntero cabeza
    LinkedList()
    {
        head = nullptr;
    }

    // Inserta al principio de la lista
    void insert(string path, int key)
    {
        if (buscar(key) == nullptr) {
            // Crea nuevo nodo
            Nodo* newNodo = new Nodo;
            newNodo->data = path;
            newNodo->next = nullptr;
            newNodo->id = key;
            newNodo->tiempo = 1;

            // Si la lista esta vacia, hace que el node sea el cabezal
            if (head == nullptr) {
                head = newNodo;
                // Si no, hace el nuevo nodo cabeza y el que fue cabezal, el siguiente de ese
                // La insercion es adelante
            }
            else
            {
                newNodo->next = head;
                head = newNodo;
            }
        }
        else {
            Nodo *existente = buscar(key);
            existente->tiempo = existente->tiempo + 1;
        }

    }

    void display()
    {
        Nodo* temp = head;
        while (temp != nullptr)
        {
            cout << temp->data << " ";
            cout << temp->tiempo<< " ";
            cout << temp->id<< " ";
            temp = temp->next;
        }
        cout << endl;
    }

    Nodo* buscar(int key) {
        Nodo* current = head;
        while (current != nullptr) {
            if (current->id == key) {
                return current;
            }
            current = current->next;
        }return nullptr;
    }
};