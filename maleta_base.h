/*
 * ARCHIVO: maleta_base.h
 * 
 * Declaración e implementación de la clase abstracta base para todas las maletas.
 * Define la interfaz común y atributos compartidos.
 */

#ifndef MALETA_BASE_H
#define MALETA_BASE_H

#include <iostream>
#include <string>
using namespace std;

/*
 * CLASE ABSTRACTA BASE: maleta_base
 * 
 * Define la estructura común para todos los tipos de maletas.
 * Utiliza métodos virtuales puros para implementar polimorfismo.
 */
class maleta_base {
protected:
    // Atributos protegidos - accesibles por clases derivadas
    string nombre_pasajero;      // Nombre del dueño de la maleta
    string clase_vuelo;          // Clase del vuelo (economica/ejecutiva)
    string numero_vuelo;         // Número de vuelo (formato AJN/AJI)
    float peso_maleta;           // Peso de la maleta en kilogramos
    bool tiene_sobrepeso;        // Indica si excede el límite de peso
    bool sobrepeso_pagado;       // Indica si el sobrepeso está pagado
    string estado_registro;      // Estado: "Registrada" o "No registrada"
    
public:
    // Constructor base - inicializa valores por defecto
    maleta_base(string nombre = "", string clase = "", string vuelo = "", float peso = 0.0) 
        : nombre_pasajero(nombre), clase_vuelo(clase), numero_vuelo(vuelo), peso_maleta(peso) {
        tiene_sobrepeso = false;           // Por defecto no hay sobrepeso
        sobrepeso_pagado = false;          // Por defecto no está pagado
        estado_registro = "No registrada"; // Estado inicial
    }
    
    // Destructor virtual para herencia correcta
    virtual ~maleta_base() {}
    
    // Métodos virtuales puros - deben ser implementados por clases derivadas
    virtual float calcular_precio() = 0;        // Calcula el precio según tipo de maleta
    virtual void mostrar_informacion() = 0;     // Muestra información específica
    virtual string obtener_tipo_maleta() = 0;   // Retorna el tipo de maleta
    
    // Método virtual para verificar sobrepeso - puede ser sobrescrito
    virtual bool verificar_sobrepeso() {
        // Límites de peso según clase de vuelo
        if (clase_vuelo == "economica" && peso_maleta > 25.0) {
            return true;  // Económica: máximo 25kg
        } else if (clase_vuelo == "ejecutiva" && peso_maleta > 32.0) {
            return true;  // Ejecutiva: máximo 32kg
        }
        return false;     // Peso dentro del límite
    }
    
    // Método para establecer todos los datos y recalcular sobrepeso
    virtual void establecer_datos(string nombre, string clase, string vuelo, float peso) {
        nombre_pasajero = nombre;
        clase_vuelo = clase;
        numero_vuelo = vuelo;
        peso_maleta = peso;
        tiene_sobrepeso = verificar_sobrepeso();  // Recalcula automáticamente
    }
    
    // Métodos getter - permiten acceso de solo lectura a los atributos
    string obtener_nombre() { return nombre_pasajero; }
    string obtener_clase() { return clase_vuelo; }
    string obtener_numero_vuelo() { return numero_vuelo; }
    float obtener_peso() { return peso_maleta; }
    bool obtener_sobrepeso() { return tiene_sobrepeso; }
    bool obtener_sobrepeso_pagado() { return sobrepeso_pagado; }
    string obtener_estado() { return estado_registro; }
    
    // Métodos setter - permiten modificar ciertos atributos
    void establecer_sobrepeso_pagado(bool pagado) { sobrepeso_pagado = pagado; }
    void establecer_estado(string estado) { estado_registro = estado; }
};

#endif // MALETA_BASE_H