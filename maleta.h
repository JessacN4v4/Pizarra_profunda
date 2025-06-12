/*
 * ARCHIVO: maleta.h
 * 
 * Declaración e implementación de la clase maleta normal.
 * Hereda de maleta_base e implementa funcionalidad específica.
 */

#ifndef MALETA_H
#define MALETA_H

#include "maleta_base.h"

/*
 * CLASE DERIVADA: maleta
 * 
 * Implementa una maleta normal con cálculo de sobrepeso.
 * Hereda de maleta_base e implementa los métodos virtuales puros.
 */
class maleta : public maleta_base {
public:
    // Constructor que llama al constructor de la clase base
    maleta(string nombre = "", string clase = "", string vuelo = "", float peso = 0.0) 
        : maleta_base(nombre, clase, vuelo, peso) {}
    
    // Implementación del cálculo de precio para maletas normales
    virtual float calcular_precio() override {
        float precio_base = 900.0;  // Precio base fijo para maletas normales
        
        // Si hay sobrepeso, calcular costo adicional
        if (tiene_sobrepeso) {
            float peso_extra = 0.0;
            
            // Calcular peso excedente según la clase
            if (clase_vuelo == "economica") {
                peso_extra = peso_maleta - 25.0;  // Límite económica: 25kg
            } else if (clase_vuelo == "ejecutiva") {
                peso_extra = peso_maleta - 32.0;  // Límite ejecutiva: 32kg
            }
            
            // Agregar costo de sobrepeso: $65 por kg extra
            precio_base += peso_extra * 65.0;
        }
        return precio_base;
    }
    
    // Implementación de mostrar información para maletas normales
    virtual void mostrar_informacion() override {
        cout << "=== INFORMACIÓN DE MALETA NORMAL ===" << endl;
        cout << "Pasajero: " << nombre_pasajero << endl;
        cout << "Clase: " << clase_vuelo << endl;
        cout << "Vuelo: " << numero_vuelo << endl;
        cout << "Peso: " << peso_maleta << " kg" << endl;
        cout << "Sobrepeso: " << (tiene_sobrepeso ? "Si" : "No") << endl;
        
        // Mostrar estado de pago según si hay sobrepeso
        if (tiene_sobrepeso) {
            cout << "Pagado: " << (sobrepeso_pagado ? "Si" : "No") << endl;
        } else {
            cout << "Pagado: No aplica" << endl;
        }
        cout << "Estado: " << estado_registro << endl;
    }
    
    // Identificador del tipo de maleta
    virtual string obtener_tipo_maleta() override {
        return "normal";
    }
};

#endif // MALETA_H