# Pizarra_profunda
Mi proyecto de c++ para la clase POO TC1030

##Descripción General
El Sistema de Registro de Maletas es una aplicación en C++ que gestiona el registro, búsqueda y procesamiento de pagos de maletas para una aerolínea. Se hace uso de un archivo .txt para simular la base de datos de boletos comprados.
El sistema implementa un flujo completo de gestión de equipaje donde los pasajeros pueden verificar el estado de sus maletas previamente registradas y procesar pagos pendientes, o bien registrar nuevas maletas con cálculo automático de precios y sobrecargos. La aplicación maneja diferentes tipos de equipaje, desde maletas convencionales hasta equipaje especial como instrumentos musicales, bicicletas y equipo médico, cada uno con sus propias tarifas y restricciones.

##Funcionalidades Principales
1. Búsqueda de Maletas
Localiza maletas existentes por nombre del pasajero y número de vuelo
Procesa pagos pendientes para maletas "No registradas"
Cambia automáticamente el estado a "Registrada" tras el pago
2. Registro de Nuevas Maletas
Permite registrar maletas normales y equipaje especial
Calcula automáticamente sobrepeso y costos
Valida límites de equipaje especial por vuelo
Procesa pagos en tiempo real
3. Gestión de Tipos de Maletas
Maletas Normales:
Precio base: $900
Límites de peso: 25kg económica / 32kg ejecutiva
Sobrecargo: $65 por kg extra
Equipaje Especial:
Instrumentos musicales: $600
Bicicletas: $1200
Equipo deportivo: $500
Equipo médico: $300
Sin sobrecargo de peso
4. Control de Vuelos
Aviones pequeños con las siglas AJN: Máximo 4 equipajes especiales
Aviones grandes con las siglas AJI: Máximo 6 equipajes especiales


##Ejemplos de Uso
##Ejemplo 1: Buscar y Pagar Maleta No Registrada
Escenario1: Laura Fernandez tiene una maleta no registrada con sobrepeso.
Pasos:
Ejecutar el programa
Seleccionar opción 1.Buscar
Ingresar datos:
Nombre: Laura Fernandez
Vuelo: AJI5899
Resultado esperado:
¡Maleta encontrada!
=INFORMACIÓN DE MALETA NORMAL =
Pasajero: Laura Fernandez
Clase: ejecutiva
Vuelo: AJI5899
Peso: 33.17 kg
Sobrepeso: Si
Pagado: No
Estado: No registrada

=PROCESO DE PAGO PARA MALETA NO REGISTRADA =
INFORMACIÓN DE PAGO:
Costo base de maleta: $900
Peso excedente: 1.17 kg
Costo por sobrepeso: $76.05 ($65 por kg extra)
COSTO TOTAL: $976.05
¿Desea pagar el costo total de la maleta? (s/n): s
¿Confirma el pago de $976.05? (s/n): s

¡PAGO PROCESADO EXITOSAMENTE!
La maleta ha sido marcada como 'Registrada'

##Ejemplo 2: Registrar Equipaje Especial (Bicicleta)
Escenario2: Nuevo pasajero quiere registrar una bicicleta.
Pasos:
Ejecutar el programa
Seleccionar opción 2. Registrar
Ingresar datos:
Nombre: Carlos Mendoza
Clase: econimica
Vuelo: AJN6445
Peso:15.5
¿Es equipaje especial? 2
Tipo: 2 (Bicicleta)
Continuación del codigo:
= REGISTRO DE NUEVA MALETA =
¿Es equipaje especial? (s/n): s

Tipo de equipaje especial:
1. Instrumento musical ($600)
2. Bicicleta ($1200)
3. Equipo deportivo ($500)
4. Equipo médico ($300)
Seleccione: 2

= PROCESO DE PAGO EQUIPAJE ESPECIAL =
Precio del equipaje especial: $1200
¿Desea pagar? (s/n): s
¿Confirma el pago de $1200? (s/n): s
¡Pago procesado exitosamente!

¡Maleta registrada exitosamente!
=MALETA DE BICICLETA=
Pasajero: Carlos Mendoza
Clase: economica
Vuelo: AJN6445
Peso: 15.5 kg
Precio: $1200
Estado: Registrada

= INFORMACIÓN DEL VUELO AJN6445 =
Tipo de avión: pequeño
Equipajes especiales: 1/4
