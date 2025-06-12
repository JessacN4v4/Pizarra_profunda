/*
 * ARCHIVO: avion.h
 * 
 * Declaración e implementación de la clase avion.
 * Gestiona información de vuelos y control de equipajes especiales.
 */

#ifndef AVION_H
#define AVION_H

#include <iostream>
#include <string>
using namespace std;

/*
 * CLASE AVIÓN
 * 
 * Gestiona la información de vuelos y el control de equipajes especiales.
 * Determina el tipo de avión según el código de vuelo.
 */
class avion {
private:
    string numero_vuelo;              // Código del vuelo
    string tipo_avion;                // Tipo: "pequeño" o "grande"
    int equipajes_especiales;         // Cantidad actual de equipajes especiales
    int limite_equipajes_especiales;  // Límite máximo según tipo de avión
    
public:
    // Constructor que determina el tipo de avión según el código
    avion(string vuelo) : numero_vuelo(vuelo) {
        equipajes_especiales = 0;  // Inicializar contador
        
        // Determinar tipo de avión según prefijo del código de vuelo
        if (vuelo.substr(0, 3) == "AJN") {
            tipo_avion = "pequeño";
            limite_equipajes_especiales = 4;  // Aviones pequeños: máximo 4
        } else if (vuelo.substr(0, 3) == "AJI") {
            tipo_avion = "grande";
            limite_equipajes_especiales = 6;  // Aviones grandes: máximo 6
        }
    }
    
    // Verifica si se puede agregar más equipaje especial
    bool puede_agregar_equipaje_especial() {
        return equipajes_especiales < limite_equipajes_especiales;
    }
    
    // Incrementa el contador de equipajes especiales
    void agregar_equipaje_especial() {
        equipajes_especiales++;
    }
    
    // Muestra información simplificada del vuelo
    void mostrar_informacion_vuelo() {
        cout << "\n=== INFORMACIÓN DEL VUELO " << numero_vuelo << " ===" << endl;
        cout << "Tipo de avión: " << tipo_avion << endl;
        cout << "Equipajes especiales: " << equipajes_especiales << "/" << limite_equipajes_especiales << endl;
    }
    
    // Getter para el número de vuelo
    string obtener_numero_vuelo() { 
        return numero_vuelo; 
    }
};

#endif // AVION_H