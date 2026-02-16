#include <iostream>
#include "ArrayList.h"

using namespace std;

int main() {
   
    cout << "enteros" << endl;
    
    Arraylist<int> numeros;
    
    // Agregar elementos
    numeros.add(10);
    numeros.add(20);
    numeros.add(30);
    numeros.add(40);
    numeros.add(50);
    
    // Mostrar
    cout << "ArrayList: " << numeros.size() << endl;
    
    // Acceder a elementos
    cout << "Primer elemento: " << numeros.first() << endl;
    cout << "ultimo elemento: " << numeros.last() << endl;
    cout << "elemento en indice 2: " << numeros.get(2) << endl;
    
    // Navegación con next y prior
    cout << "\nNavegacion:" << endl;
    numeros.setCurrentIndex(0); // Empezar en el indice 0  
    cout << "Actual: " << numeros.get(numeros.getCurrentIndex()) << endl;
    cout << "Siguiente: " << numeros.next() << endl;
    cout << "Siguiente: " << numeros.next() << endl;
    cout << "Anterior: " << numeros.prior() << endl;

    // Eliminar elemento
    numeros.remove(2); // Elimina el elemento en indice 2 
    cout << "\nDespues de eliminar indice 2:" << endl;
    for (int i = 0; i < numeros.size(); i++) {
        cout << "Elemento " << i << ": " << numeros.get(i) << endl;
    }
    
    
    return 0;
}