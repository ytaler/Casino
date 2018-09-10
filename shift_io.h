#include <stdint.h>        /* For uint8_t definition */
//=============================================================================
// Funciones para leer y escribir datos serie a través de los registros
// CD 4014 (8 entradas)
// Es necesario poner los TRIS al valor adecuado
// Es necesario definir:

// #define PinTestCD4014            // Pin para pruebas de tiempo de ciclo
//                                  // no se usa si no esta definido
// #define CLK_CD4014               // Alias del pin LOAD para CD4014
// #define DATA_CD4014              // Alias del pin DATA para CD4014
// #define LOAD_CD4014              // Alias del pin CLK para CD4014
// #define NumeroCD4014             // Numero de CD4014 en serie
// int8 DatosCD4014[NumeroCD4014];  // Array de datos a leer de los CD4014
// #define FastCD4014               // definirlo para usar el algoritmo rapido pero largo

// #define PinTestCD4014  PIN_C4

#define NumeroCD4014 4             // Numero de CD4014 en serie
uint8_t DatosCD4014[NumeroCD4014];    // Array de datos a leer de los CD4014

// Prototipos de las funciones:
//=============================================================================
// Inicia los pines para CD4014 a estado inactivo, llamarlo en la inicialización en
// Main despues de haber puesto los TRIS a los valores adecuados
void InitCD4014 (void);
// Lee datos serie de los registros CD4014 al array global DatosCD4014[]
void ReadCD4014 (void);
