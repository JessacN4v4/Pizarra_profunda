/*
 * ARCHIVO: equipaje_especial.h
 * 
 * Declaraciones e implementaciones de todas las clases de equipaje especial.
 * Incluye instrumentos, bicicletas, equipo deportivo y médico.
 */

#ifndef EQUIPAJE_ESPECIAL_H
#define EQUIPAJE_ESPECIAL_H

#include "maleta_base.h"

/*
 * CLASES DE EQUIPAJE ESPECIAL
 * 
 * Estas clases implementan diferentes tipos de equipaje especial,
 * cada uno con su precio fijo y sin cálculo de sobrepeso.
 */

// ================== MALETA INSTRUMENTO ==================
class maleta_instrumento : public maleta_base {
public:
    maleta_instrumento(string nombre = "", string clase = "", string vuelo = "", float peso = 0.0) 
        : maleta_base(nombre, clase, vuelo, peso) {}
    
    // Precio fijo para instrumentos musicales
    virtual float calcular_precio() override {
        return 600.0;
    }
    
    // Los equipajes especiales no tienen sobrecargo
    virtual bool verificar_sobrepeso() override {
        return false;
    }
    
    virtual void mostrar_informacion() override {
        cout << "=== MALETA DE INSTRUMENTO MUSICAL ===" << endl;
        cout << "Pasajero: " << nombre_pasajero << endl;
        cout << "Clase: " << clase_vuelo << endl;
        cout << "Vuelo: " << numero_vuelo << endl;
        cout << "Peso: " << peso_maleta << " kg" << endl;
        cout << "Precio: $600" << endl;
        cout << "Estado: " << estado_registro << endl;
    }
    
    virtual string obtener_tipo_maleta() override {
        return "instrumento";
    }
};

// ================== MALETA BICICLETA ==================
class maleta_bicicleta : public maleta_base {
public:
    maleta_bicicleta(string nombre = "", string clase = "", string vuelo = "", float peso = 0.0) 
        : maleta_base(nombre, clase, vuelo, peso) {}
    
    virtual float calcular_precio() override {
        return 1200.0;  // Precio más alto para bicicletas
    }
    
    virtual bool verificar_sobrepeso() override {
        return false;   // Sin sobrecargo
    }
    
    virtual void mostrar_informacion() override {
        cout << "=== MALETA DE BICICLETA ===" << endl;
        cout << "Pasajero: " << nombre_pasajero << endl;
        cout << "Clase: " << clase_vuelo << endl;
        cout << "Vuelo: " << numero_vuelo << endl;
        cout << "Peso: " << peso_maleta << " kg" << endl;
        cout << "Precio: $1200" << endl;
        cout << "Estado: " << estado_registro << endl;
    }
    
    virtual string obtener_tipo_maleta() override {
        return "bicicleta";
    }
};

// ================== MALETA EQUIPO DEPORTIVO ==================
class maleta_equipo_deportivo : public maleta_base {
public:
    maleta_equipo_deportivo(string nombre = "", string clase = "", string vuelo = "", float peso = 0.0) 
        : maleta_base(nombre, clase, vuelo, peso) {}
    
    virtual float calcular_precio() override {
        return 500.0;
    }
    
    virtual bool verificar_sobrepeso() override {
        return false;
    }
    
    virtual void mostrar_informacion() override {
        cout << "=== MALETA DE EQUIPO DEPORTIVO ===" << endl;
        cout << "Pasajero: " << nombre_pasajero << endl;
        cout << "Clase: " << clase_vuelo << endl;
        cout << "Vuelo: " << numero_vuelo << endl;
        cout << "Peso: " << peso_maleta << " kg" << endl;
        cout << "Precio: $500" << endl;
        cout << "Estado: " << estado_registro << endl;
    }
    
    virtual string obtener_tipo_maleta() override {
        return "equipo_deportivo";
    }
};

// ================== MALETA EQUIPO MÉDICO ==================
class maleta_equipo_medico : public maleta_base {
public:
    maleta_equipo_medico(string nombre = "", string clase = "", string vuelo = "", float peso = 0.0) 
        : maleta_base(nombre, clase, vuelo, peso) {}
    
    virtual float calcular_precio() override {
        return 300.0;  // Precio más bajo para equipo médico
    }
    
    virtual bool verificar_sobrepeso() override {
        return false;
    }
    
    virtual void mostrar_informacion() override {
        cout << "=== MALETA DE EQUIPO MÉDICO ===" << endl;
        cout << "Pasajero: " << nombre_pasajero << endl;
        cout << "Clase: " << clase_vuelo << endl;
        cout << "Vuelo: " << numero_vuelo << endl;
        cout << "Peso: " << peso_maleta << " kg" << endl;
        cout << "Precio: $300" << endl;
        cout << "Estado: " << estado_registro << endl;
    }
    
    virtual string obtener_tipo_maleta() override {
        return "equipo_medico";
    }
};

#endif // EQUIPAJE_ESPECIAL_H