#ifndef SISTEMA_MALETAS_H
#define SISTEMA_MALETAS_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "maleta_base.h"
#include "maleta.h"
#include "equipaje_especial.h"
#include "avion.h"

using namespace std;

/*Clase sistema de maletas
Esta gestiona todo el sistema de maletas
Carga y guardado de datos
Busqueda y registro de maletas
Procesamiento de pagos
Interfaz de usuario*/
class sistema_maletas {
private:
// Límite máximo de maletas
    static const int MAX_MALETAS = 100;
    // Array de punteros  
    maleta_base* maletas[MAX_MALETAS];
    // Contador de maletas cargadas     
    int total_maletas;
    // Nombre delarchivo                     
    string nombre_archivo;                 
    
    // Elimina espacios en blanco al inicio y final de una cadena
    string limpiar_espacios(string texto) {
        // Buscar primer caracter no espacio
        size_t inicio = texto.find_first_not_of(" \t");  
        if (inicio == string::npos) return "";           
        size_t final = texto.find_last_not_of(" \t");    
        // Se extrae substring limpio
        return texto.substr(inicio, final - inicio + 1); 
    }
    
    // Carga todos los datos del archivo al array en memoria
    void cargar_datos_archivo() {
        // Se abre el archivo para su lectura
        ifstream archivo(nombre_archivo.c_str());  
        if (!archivo.is_open()) {
            cout << "¡¡No se pudo abrir el archivo!!" 
            << nombre_archivo << endl;
            return;
        }
        
        string linea;
        // Se leen todas las lineas del archivo
        while (getline(archivo, linea) && 
        total_maletas < MAX_MALETAS) {
            // Saltar lineas vacias
            if (linea.empty()) continue;  
            string elementos[6];
            size_t pos = 0;
            
            // Extraer los primeros 5 elementos separados por comas
            for (int i = 0; i < 5; i++) {
                size_t siguiente_coma = linea.find(",", pos);
                if (siguiente_coma != string::npos) {
                    elementos[i] = linea.substr(pos, 
                        siguiente_coma - pos);
                    pos = siguiente_coma + 1;
                } else {
                    // Se rompe la linea malformada
                    break;  
                }
            }
            // El último elemento toma todo el resto de la linea
            elementos[5] = linea.substr(pos);
            
            // Se limpia y extrae datos de cada propiedad
            string nombre = limpiar_espacios(elementos[0]);
            string clase = limpiar_espacios(elementos[1]);
            string vuelo = limpiar_espacios(elementos[2]);
            string peso_str = limpiar_espacios(elementos[3]);
            string sobrepeso_str = limpiar_espacios(elementos[4]);
            string resto_linea = limpiar_espacios(elementos[5]);
            
            // Se extrae peso numerico
            size_t pos_kg = peso_str.find(" kg");
            //Formato invalido
            if (pos_kg == string::npos) continue;  
            string peso_num = peso_str.substr(0, pos_kg);
            // Convertir peso a float
            float peso = stof(peso_num);  
            
            // Determinar si tiene sobrepeso
            bool tiene_sobrepeso = sobrepeso_str.find("Si") 
            != string::npos;
            
            // Determinar si el sobrepeso esta pagado
            bool sobrepeso_pagado = resto_linea.find
            ("Pagado: Si") != string::npos;
            
            // Extraer estado de registro
            string estado = "No registrada";  
            size_t pos_estado = resto_linea.find("Estado: ");
            if (pos_estado != string::npos) {
                estado = resto_linea.substr(pos_estado + 8);
                estado = limpiar_espacios(estado);
            }
            
            // Se crea objeto maleta normal y configurar propiedades
            maletas[total_maletas] = new maleta
            (nombre, clase, vuelo, peso);
            
            // Establecer estado de pago si hay sobrepeso pagado
            if (tiene_sobrepeso && sobrepeso_pagado) {
                maletas[total_maletas]->
                establecer_sobrepeso_pagado(true);
            }
            
            // Establecer estado de registro
            maletas[total_maletas]->establecer_estado(estado);
            total_maletas++;
        }
        archivo.close();
        cout << "Cargadas " << total_maletas <<
        " maletas desde el archivo." << endl;
    }
    
    //Reescribe completamente el archivo con todos los datos actuales
    void actualizar_archivo_completo() {
        // Se abre el archivo para escritura
        ofstream archivo(nombre_archivo.c_str());  
        if (!archivo.is_open()) {
            cout << "¡¡No se pudo abrir el archivo para escribir!!"
            << endl;
            return;
        }
        
        // Escribir cada maleta al archivo
        for (int i = 0; i < total_maletas; i++) {
            escribir_linea_maleta(archivo, maletas[i]);
        }
        
        archivo.close();
    }
    
    //Escribe una línea individual de maleta al archivo
    void escribir_linea_maleta(ofstream& archivo, 
        maleta_base* maleta_ptr) {
        // Escribir datos básicos
        archivo << maleta_ptr->obtener_nombre() << ", " 
                << maleta_ptr->obtener_clase() << ", "
                << maleta_ptr->obtener_numero_vuelo() << ", "
                << maleta_ptr->obtener_peso() << " kg, ";
        
        // Escribir información de sobrepeso según el tipo
        if (maleta_ptr->obtener_tipo_maleta() == "normal") {
            archivo << "Sobrepeso: " << (maleta_ptr->
            obtener_sobrepeso() ? "Si" : "No") << ", ";
            if (maleta_ptr->obtener_sobrepeso()) {
                archivo << "Pagado: " << (maleta_ptr->
                obtener_sobrepeso_pagado() ? "Si" : "No") << ", ";
            } else {
                archivo << "Pagado: No aplica, ";
            }
        } else {
            // El equipaje especial no tiene sobrepeso
            archivo << "Sobrepeso: No, Pagado: No aplica, ";
        }
        
        // Escribe el estado y termina la linea
        archivo << "Estado: " << maleta_ptr->
        obtener_estado() << endl;
    }
    
    // Agrega una nueva maleta al sistema y actualiza el archivo
    void agregar_maleta_archivo(maleta_base* nueva_maleta) {
        // Agregar a memoria si hay espacio
        if (total_maletas < MAX_MALETAS) {
            maletas[total_maletas] = nueva_maleta;
            total_maletas++;
        }
        
        // Actualizar archivo completo para mantener consistencia
        actualizar_archivo_completo();
    }
    
    // Cambia el estado de una maleta específica
    void cambiar_estado_maleta(string nombre, 
        string vuelo, string nuevo_estado) {
        // Buscar la maleta por nombre y vuelo
        for (int i = 0; i < total_maletas; i++) {
            if (maletas[i]->obtener_nombre() == nombre && 
                maletas[i]->obtener_numero_vuelo() == vuelo) {
                
                // Actualiza el estado y guarda cambios
                maletas[i]->establecer_estado(nuevo_estado);
                actualizar_archivo_completo();
                cout << "Estado de maleta actualizado a: " << nuevo_estado << endl;
                return;
            }
        }
        cout << "Maleta no encontrada para cambiar estado" << endl;
    }
    
public:
    // Se inicializa el sistema y carga datos del archivo
    sistema_maletas() : total_maletas(0), nombre_archivo
    ("base-datos.txt") {
        // Inicializar array de punteros a nullptr
        for (int i = 0; i < MAX_MALETAS; i++) {
            maletas[i] = nullptr;
        }
        // Cargar datos al iniciar
        cargar_datos_archivo();  
    }
    
    // Destructor, se libera toda la memoria asignada
    ~sistema_maletas() {
        for (int i = 0; i < total_maletas; i++) {
            // Liberar cada objeto maleta
            delete maletas[i];  
        }
    }
    
    // Busca una maleta existente y permite procesar pagos
    void buscar_maleta() {
        string nombre, vuelo;
        cout << "Ingrese el nombre del pasajero: ";
        cin.ignore(); 
        getline(cin, nombre);
        cout << "Ingrese el número de vuelo: ";
        getline(cin, vuelo);
        
        bool encontrada = false;
        int indice_encontrado = -1;
        
        // Buscar maleta en el array
        for (int i = 0; i < total_maletas; i++) {
            if (maletas[i]->obtener_nombre() == nombre && maletas
            [i]->obtener_numero_vuelo() == vuelo) {
                cout << "\n¡Maleta encontrada!" << endl;
                // Polimorfismo en accion
                maletas[i]->mostrar_informacion();  
                encontrada = true;
                indice_encontrado = i;
                break;
            }
        }
        
        if (encontrada) {
            // Verifica estado y procesa segun corresponda
            if (maletas[indice_encontrado]->obtener_estado()
            == "No registrada") {
        // Iniciar proceso de pago para maletas no registradas
                procesar_pago_maleta_no_registrada
                (indice_encontrado);
            } else {
                cout << "\nLa maleta ya está registrada." << endl;
            }
        } else {
            // Maleta no encontrada, se ofrece hacer registro
            cout << "\nMaleta no encontrada." << endl;
            char respuesta;
            cout << "¿Desea registrar una nueva maleta? (s/n): ";
            cin >> respuesta;
            if (respuesta == 's' || respuesta == 'S') {
                registrar_maleta();
            }
        }
    }
    
    //Procesa el pago para maletas que estn en estado "No registrada"
    void procesar_pago_maleta_no_registrada(int indice) {
        maleta_base* maleta_actual = maletas[indice];
        
        cout << "\n=PROCESO DE PAGO PARA MALETA NO REGISTRADA=" 
        << endl;
        
        // Procesar según el tipo de maleta
        if (maleta_actual->obtener_tipo_maleta() == "normal") {
            // Procesar maleta normal con posible sobrepeso
            float costo_total = maleta_actual->calcular_precio();
            
            cout << "INFORMACIÓN DE PAGO:" << endl;
            cout << "Costo base de maleta: $900" << endl;
            
            if (maleta_actual->obtener_sobrepeso()) {
                // Calcular y mostrar detalles del sobrepeso
                float peso_extra = 0.0;
                if (maleta_actual->obtener_clase() == "economica")
                 {peso_extra = maleta_actual->obtener_peso()
                     - 25.0;
                } else if (maleta_actual->obtener_clase()
                 == "ejecutiva") {
                    peso_extra = maleta_actual->obtener_peso()
                     - 32.0;
                }
                float costo_sobrepeso = peso_extra * 65.0;
                
                cout << "Peso excedente: " << peso_extra << " kg" 
                << endl;
                cout << "Costo por sobrepeso: $" << costo_sobrepeso 
                << " ($65 por kg extra)" << endl;
                cout << "COSTO TOTAL: $" << costo_total << endl;
                
                // Verificar si ya está pagado o procesar pago
                if (!maleta_actual->obtener_sobrepeso_pagado()) {
                    char quiere_pagar;
                    cout << 
                    "\n¿Desea pagar el costo totalde la maleta?(s/n):";
                    cin >> quiere_pagar;
                    
                    if (quiere_pagar == 's' || quiere_pagar == 'S') {
                        char confirmar_pago;
                        cout << "¿Confirma el pago de $" 
                        << costo_total << "? (s/n): ";
                        cin >> confirmar_pago;
                        
                        if (confirmar_pago == 's' || 
                            confirmar_pago == 'S') {
                            // Procesar pago exitoso
                            maleta_actual->
                            establecer_sobrepeso_pagado(true);
                            maleta_actual->
                            establecer_estado("Registrada");
                            actualizar_archivo_completo();
                            
                            cout << "\n¡PAGO PROCESADO EXITOSAMENTE!"
                            << endl;
                            cout 
                            << "La maleta se ha 'Registrad0'" 
                            << endl;
                            maleta_actual->mostrar_informacion();
                            
                            // Mostrar información del vuelo
                            avion vuelo_actual(maleta_actual->
                                obtener_numero_vuelo());
                            vuelo_actual.mostrar_informacion_vuelo();
                        } else {
                            cout 
                            << "\nPago cancelado. La maleta permanece como 'No registrada'." 
                            << endl;
                            cout 
                            << "No podrá abordar el vuelo sin completar el pago." 
                            << endl;
                        }
                    } else {
                        cout 
                        << "\nPago rechazado. La maleta permanece como 'No registrada'." 
                        << endl;
                        cout 
                        << "No podrá abordar el vuelo sin completar el pago." 
                        << endl;
                    }
                } else {
                    // Sobrepeso ya pagado, cambia el Registro
                    cout << "\nEl sobrepeso ya está pagado." 
                    "Cambiando estado a 'Registrada'..." << endl;
                    maleta_actual->establecer_estado("Registrada");
                    actualizar_archivo_completo();
                    maleta_actual->mostrar_informacion();
                }
            } else {
                // Maleta sin sobrepeso
                cout << "COSTO TOTAL: $" << costo_total << endl;
                
                char quiere_pagar;
                cout << "\n¿Desea pagar el costo de la maleta?(s/n): ";
                cin >> quiere_pagar;
                
                if (quiere_pagar == 's' || quiere_pagar == 'S'){
                    char confirmar_pago;
                    cout << "¿Confirma el pago de $" 
                    << costo_total << "? (s/n): ";
                    cin >> confirmar_pago;
                    
                    if (confirmar_pago == 's' ||
                         confirmar_pago == 'S') {
                        // Procesar pago exitoso
                        maleta_actual->
                        establecer_estado("Registrada");
                        actualizar_archivo_completo();
                        
                        cout << "\n¡PAGO PROCESADO EXITOSAMENTE!" 
                        << endl;
                        cout << "La maleta ha sido marcada como 'Registrada'" 
                        << endl;
                        maleta_actual->mostrar_informacion();
                        
                        // Mostrar información del vuelo
                        avion vuelo_actual(maleta_actual->
                            obtener_numero_vuelo());
                        vuelo_actual.mostrar_informacion_vuelo();
                    } else {
                        cout << "\nPago cancelado. La maleta permanece como 'No registrada'." 
                        << endl;
                        cout 
                        << "No podrá abordar el vuelo sin completar el pago." 
                        << endl;
                    }
                } else {
                    cout 
                    << "\nPago rechazado. La maleta permanece como 'No registrada'." 
                    << endl;
                    cout 
                    << "No podrá abordar el vuelo sin completar el pago." 
                    << endl;
                }
            }
        } else {
            // Procesar equipaje especial
            float costo_especial = maleta_actual->calcular_precio();
            
            cout << "EQUIPAJE ESPECIAL - " << maleta_actual->
            obtener_tipo_maleta() << endl;
            cout << "COSTO TOTAL: $" << costo_especial << endl;
            
            char quiere_pagar;
            cout << "\n¿Desea pagar el costo del equipaje especial? (s/n): ";
            cin >> quiere_pagar;
            
            if (quiere_pagar == 's' || quiere_pagar == 'S') {
                char confirmar_pago;
                cout << "¿Confirma el pago de $" << costo_especial << "? (s/n): ";
                cin >> confirmar_pago;
                
                if (confirmar_pago == 's' || confirmar_pago == 'S') {
                    // Procesar pago exitoso para equipaje especial
                    maleta_actual->establecer_estado("Registrada");
                    actualizar_archivo_completo();
                    
                    cout << "\n¡PAGO PROCESADO EXITOSAMENTE!" << endl;
                    cout << "El equipaje especial ha sido marcado como 'Registrado'" << endl;
                    maleta_actual->mostrar_informacion();
                    
                    // Mostrar informacion del vuelo
                    avion vuelo_equipaje(maleta_actual->obtener_numero_vuelo());
                    vuelo_equipaje.mostrar_informacion_vuelo();
                } else {
                    cout << "\nPago cancelado. El equipaje permanece como 'No registrado'." << endl;
                    cout << "No podrá abordar el vuelo sin completar el pago." << endl;
                }
            } else {
                cout << "\nPago rechazado. El equipaje permanece como 'No registrado'." << endl;
                cout << "No podrá abordar el vuelo sin completar el pago." << endl;
            }
        }
    }
    
    // Registra una nueva maleta en el sistema
    void registrar_maleta() {
        // Verificar limite de capacidad
        if (total_maletas >= MAX_MALETAS) {
            cout << "No se pueden registrar más maletas." << endl;
            return;
        }
        
        // Variables para capturar datos del usuario
        string nombre, clase, vuelo;
        float peso;
        
        cout << "\n=== REGISTRO DE NUEVA MALETA ===" << endl;
        cout << "Nombre del pasajero: ";
        cin.ignore();  
        getline(cin, nombre);
        
        cout << "Clase (economica/ejecutiva): ";
        getline(cin, clase);
        
        cout << "Número de vuelo: ";
        getline(cin, vuelo);
        
        // Validar que el vuelo pertenece a la aerolnea 
        if (vuelo.substr(0, 2) != "AJ") {
            cout << "Lo siento, su vuelo no es de esta aerolínea." << endl;
            return;
        }
        
        cout << "Peso de la maleta (kg): ";
        cin >> peso;
        
        // Determinar si es equipaje especial
        char es_especial;
        cout << "¿Es equipaje especial? (s/n): ";
        cin >> es_especial;
        // Puntero polimórfico
        maleta_base* nueva_maleta = nullptr;  
        
        if (es_especial == 's' || es_especial == 'S') {
            // Procesamiento de equipaje especial
            
            // Verificar limite de equipajes especiales en el vuelo
            avion vuelo_avion(vuelo);
            if (!vuelo_avion.puede_agregar_equipaje_especial()) {
                cout << "No se pueden agregar más equipajes especiales en este vuelo." << endl;
                return;
            }
            
            // Verificar peso maximo para equipaje especial 
            if (peso > 45.0) {
                cout << "Su equipaje es demasiado pesado para viajar (máximo 45kg)." << endl;
                return;
            }
            
            // Mostrar opciones de equipaje especial
            int tipo_especial;
            cout << "\nTipo de equipaje especial:" << endl;
            cout << "1. Instrumento musical ($600)" << endl;
            cout << "2. Bicicleta ($1200)" << endl;
            cout << "3. Equipo deportivo ($500)" << endl;
            cout << "4. Equipo médico ($300)" << endl;
            cout << "Seleccione: ";
            cin >> tipo_especial;
            
            // Crear objeto segun el tipo seleccionado uso de polimorfismo
            if (tipo_especial == 1) {
                nueva_maleta = new maleta_instrumento(nombre, clase, vuelo, peso);
            } else if (tipo_especial == 2) {
                nueva_maleta = new maleta_bicicleta(nombre, clase, vuelo, peso);
            } else if (tipo_especial == 3) {
                nueva_maleta = new maleta_equipo_deportivo(nombre, clase, vuelo, peso);
            } else if (tipo_especial == 4) {
                nueva_maleta = new maleta_equipo_medico(nombre, clase, vuelo, peso);
            } else {
                cout << "Opción inválida." << endl;
                return;
            }
            
            // Proceso de pago para equipaje especial
            cout << "\n=== PROCESO DE PAGO EQUIPAJE ESPECIAL ===" << endl;
            cout << "Precio del equipaje especial: $" << nueva_maleta->calcular_precio() << endl;
            
            char pagar;
            cout << "¿Desea pagar? (s/n): ";
            cin >> pagar;
            
            if (pagar != 's' && pagar != 'S') {
                cout << "Registro cancelado." << endl;
                delete nueva_maleta;  
                return;
            }
            
            // Confirmacion de pago
            char confirmar_pago;
            cout << "¿Confirma el pago de $" << nueva_maleta->calcular_precio() << "? (s/n): ";
            cin >> confirmar_pago;
            
            if (confirmar_pago != 's' && confirmar_pago != 'S') {
                cout << "Registro cancelado." << endl;
                delete nueva_maleta;  
                return;
            }
            
            cout << "¡Pago procesado exitosamente!" << endl;
            
            // Actualizar contador de equipajes especiales
            avion vuelo_equipaje_especial(vuelo);
            vuelo_equipaje_especial.agregar_equipaje_especial();
            
        } else {
            // Procesamiento de maleta normal
            nueva_maleta = new maleta(nombre, clase, vuelo, peso);
            
            // Forzar verificación de sobrepeso despus de crear la maleta
            nueva_maleta->establecer_datos(nombre, clase, vuelo, peso);
            
            if (nueva_maleta->obtener_sobrepeso()) {
                // Procesar maleta con sobrepeso
                cout << "\n=== PROCESO DE PAGO SOBREPESO ===" << endl;
                cout << "La maleta tiene sobrepeso." << endl;
                cout << "Costo base de maleta: $900" << endl;
                
                // Calcular peso excedente
                float peso_extra = 0.0;
                if (clase == "economica") {
                    peso_extra = peso - 25.0;
                } else if (clase == "ejecutiva") {
                    peso_extra = peso - 32.0;
                }
                
                float costo_sobrepeso = peso_extra * 65.0;
                float costo_total = nueva_maleta->calcular_precio();
                
                cout << "Peso excedente: " << peso_extra << " kg" << endl;
                cout << "Costo por sobrepeso: $" << costo_sobrepeso << " ($65 por kg extra)" << endl;
                cout << "COSTO TOTAL: $" << costo_total << endl;
                
                // Proceso de pago para sobrepeso
                char pagar_sobrepeso;
                cout << "¿Desea pagar el sobrepeso? (s/n): ";
                cin >> pagar_sobrepeso;
                
                if (pagar_sobrepeso != 's' && pagar_sobrepeso != 'S') {
                    cout << "Registro cancelado." << endl;
                    delete nueva_maleta;
                    return;
                }
                
                // Confirmacion de pago
                char confirmar_pago;
                cout << "¿Confirma el pago de $" << costo_total << "? (s/n): ";
                cin >> confirmar_pago;
                
                if (confirmar_pago != 's' && confirmar_pago != 'S') {
                    cout << "Registro cancelado." << endl;
                    delete nueva_maleta;
                    return;
                }
                
                // Marcar sobrepeso como pagado
                nueva_maleta->establecer_sobrepeso_pagado(true);
                cout << "¡Pago procesado exitosamente!" << endl;
            } else {
                // Procesar maleta normal sin sobrepeso
                cout << "\n=== PROCESO DE PAGO MALETA NORMAL ===" << endl;
                cout << "Costo de la maleta: $900" << endl;
                
                char pagar;
                cout << "¿Desea pagar? (s/n): ";
                cin >> pagar;
                
                if (pagar != 's' && pagar != 'S') {
                    cout << "Registro cancelado." << endl;
                    delete nueva_maleta;
                    return;
                }
                
                // Confirmacion de pago
                char confirmar_pago;
                cout << "¿Confirma el pago de $900? (s/n): ";
                cin >> confirmar_pago;
                
                if (confirmar_pago != 's' && confirmar_pago != 'S') {
                    cout << "Registro cancelado." << endl;
                    delete nueva_maleta;
                    return;
                }
                
                cout << "¡Pago procesado exitosamente!" << endl;
            }
        }
        
        // Establecer estado como registrada, pago completado
        nueva_maleta->establecer_estado("Registrada");
        
        // Agregar maleta al sistema y actualizar archivo
        agregar_maleta_archivo(nueva_maleta);
        
        cout << "\n¡Maleta registrada exitosamente!" << endl;
        nueva_maleta->mostrar_informacion();
        
        // Mostrar información del vuelo
        avion vuelo_actual(vuelo);
        vuelo_actual.mostrar_informacion_vuelo();
    }
    
    // Muestra el menú principal y gestiona la navegacion
    void mostrar_menu() {
        int opcion;
        
        // Bucle principal del programa
        do {
            cout << "\n=== SISTEMA DE REGISTRO DE MALETAS ===" << endl;
            cout << "1. Buscar" << endl;
            cout << "2. Registrar" << endl;
            cout << "3. Salir" << endl;
            cout << "Seleccione una opción: ";
            cin >> opcion;
            
            // Procesar opcion seleccionada usando
            if (opcion == 1) {
                buscar_maleta();
            } else if (opcion == 2) {
                registrar_maleta();
            } else if (opcion == 3) {
                cout << "¡Gracias por usar nuestro sistema!" << endl;
            } else {
                cout << "Opción inválida." << endl;
            }
            // Continua hasta que seleccione salir
        } while (opcion != 3);  
    }
};

#endif  
//Declaración de la clase principal del sistema.
//Gestiona todas las operaciones del programa.
 
#ifndef SISTEMA_MALETAS_H
#define SISTEMA_MALETAS_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "maleta_base.h"
#include "maleta.h"
#include "equipaje_especial.h"
#include "avion.h"

using namespace std;

class sistema_maletas {
private:
    static const int MAX_MALETAS = 100;    
    maleta_base* maletas[MAX_MALETAS];     
    int total_maletas;                     
    string nombre_archivo;                 
    
    // Metodos privados para manejo de archivos
    string limpiar_espacios(string texto);
    void cargar_datos_archivo();
    void actualizar_archivo_completo();
    void escribir_linea_maleta(ofstream& archivo, maleta_base* maleta_ptr);
    void agregar_maleta_archivo(maleta_base* nueva_maleta);
    void cambiar_estado_maleta(string nombre, string vuelo, string nuevo_estado);
    
public:
    // Constructor y destructor
    sistema_maletas();
    ~sistema_maletas();
    
    // Metodos publicos, interfaz del sistema
    void buscar_maleta();
    void procesar_pago_maleta_no_registrada(int indice);
    void registrar_maleta();
    void mostrar_menu();
};

#endif // SISTEMA_MALETAS_H