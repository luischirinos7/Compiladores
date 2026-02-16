#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>
#include <stdexcept>

using namespace std;

//se declara la plantilla(la clase template)

template <typename T> // para trabajar con cualquier tipo de dato

class Arraylist{
    private:   // se hace privada para que no se pueda acceder desde afuera
        T*array;  //puntero que apunta al arreglo que va almacenar los elementos
        int capacity; //capacidad maxima del arreglo
        int length; //numero de elementos que tiene el arreglo
        int currentIndex; //indice actual para navegacion

        void resize(int newCapacity){ // funcion para cambiar el array cuando se llena
            T* newArray = new T[newCapacity];
            for(int i=0; i<length; i++){ //se copia cada elemento del array viejo al nueuvo
                newArray[i] = array[i];
            }
            delete[] array; // se boora el  viejo
            array = newArray;
            capacity = newCapacity;
        }
    public:
    Arraylist(int initialCapacity=10){ //constructor 
        if(initialCapacity <=0){
            initialCapacity= 100;
        } 

        array= new T[initialCapacity]; // se le asigna la mmemoria
        capacity= initialCapacity;
        length=0; //inicialmente no tiene elementos
        currentIndex = 0; // no hay indice actual al inicio
    }

    ~Arraylist(){ // destructor
        delete[] array; // se libera la memoria
    }

    //metodo add
    // agrega un elemento al final del array

    void add(const T& element) {
        // se verifica si se necesita mas espacio
        if (length >= capacity) {
            resize(capacity * 2); // se duplica en caso de que este lleno
        }
        
        // se agg el elemento
        array[length] = element;
        length++; // 
        
        cout << "Elemento agregado. " << length << endl;
    }

    //metodo get
    T& get(int index) {
        if (index < 0 || index >= length) {
            throw out_of_range("indice fuera de rango");
        }
        return array[index]; // Retorna  elemento
    }
    
    // para constantes
    const T& get(int index) const {
        if (index < 0 || index >= length) {
            throw out_of_range("indice fuera de rango");
        }
        return array[index]; // retorna a otro elemento
    }

    //remove
    void remove(int index) {
        // se verifiva el indice
        if (index < 0 || index >= length) {
            throw out_of_range("indice fuera de rango ");
        }
        
        // se desplazan los elementos a la izquierda
        for (int i = index; i < length - 1; i++) {
            array[i] = array[i + 1];
        }
        
        length--; // se dismininuye el tamano
        
       
        if (currentIndex >= length) {
            currentIndex = length - 1;
        }
        if (currentIndex < 0 && length > 0) {
            currentIndex = 0;
        }
        
        cout << "Elemento en indice " << index << " eliminado. "<< endl;
        

    }

    //size
    int size() const {
        return length;
    }

    //first

     // retorna el primer elemento
    T& first() {
        if (length == 0) {
            throw out_of_range("ArrayList vacio");
        }
        currentIndex = 0; // actualiza el indice actual
        return array[0];
    }
    
    const T& first() const {
        if (length == 0) {
            throw out_of_range("ArrayList vacio");
        }
        return array[0];
    }

    //last
    // retorna el ultimo elemento
    T& last() {
        if (length == 0) {
            throw out_of_range("ArrayList vacio");
        }
        currentIndex = length - 1; // actualiza el indice actual
        return array[length - 1];
    }
    
    const T& last() const {
        if (length == 0) {
            throw out_of_range("ArrayList vacio");
        }
        return array[length - 1];
    }

    //next
     // retorna el siguiente elemento 
    T& next() {
        if (length == 0) {
            throw out_of_range("ArrayList vacio");
        }
        // Incrementa el indice y vuelve al inicio
        currentIndex = (currentIndex + 1) % length;
        return array[currentIndex];
    }

    //prior
    // Retorna el elemento anterior en la secuencia de navegación
    T& prior() {
        if (length == 0) {
            throw out_of_range("ArrayList vacio");
        }
        // disminuye el indice y va al final
        currentIndex = (currentIndex - 1 + length) % length;
        return array[currentIndex];
    }
    
     // getCurrentIndex 
    int getCurrentIndex() const {
        return currentIndex;
    }

    // setCurrentIndex
    void setCurrentIndex(int index) {
        if (index < 0 || index >= length) {
            throw out_of_range("indice fuera de rango");
        }
        currentIndex = index;
    }
};   

#endif // ARRAYLIST_H