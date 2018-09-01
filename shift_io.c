//=============================================================================
// Funciones para leer y escribir datos serie a través de los registros
// CD 4014 (8 entradas) y CD4094 (8 salidas)
// Es necesario poner los TRIS al valor adecuado
// Es necesario definir varios datos en "shifth_io.h"

#include <stdint.h>        /* For uint8_t definition */
#include "shift_io.h"
#include "mcc_generated_files/mcc.h"

//=============================================================================
// Inicia los pines para CD4014
void InitCD4014 (void)
{
   CLK_CD4014_SetLow();  // CLOCK inactivo
   LOAD_CD4014_SetLow(); // LOAD inactivo entradas
}

//=============================================================================
// Lee datos serie de los registros CD4014 al array global DatosCD4014[]
void ReadCD4014 (void)
{
uint8_t bytes, data;

//#ifdef PinTestCD4014
   //output_high (PinTestCD4014); // depuracion
//#endif

// los pulsos son de 200ns a 20Mhz, poner retardos para alargarlos si es necesario
// Primero carga TODOS los datos en paralelo en los registros
   LOAD_CD4014_SetHigh();    // LOAD activo
   CLK_CD4014_SetHigh();     // CLK activo, carga los datos en paralelo
   CLK_CD4014_SetLow();     // CLK inactivo
   LOAD_CD4014_SetLow();     // LOAD inactivo

// Ahora vamos leyendo en serie en grupos de 8 bits N veces
   for (bytes = 0; bytes < NumeroCD4014; bytes++)
   {
// Forma larga pero rapida: 3:42us 2:29us 1:16us Aprox(3 us + 13*bytes us)
      data = 0;
      if (DATA_CD4014_GetValue()) data|=0x80;
      CLK_CD4014_SetHigh(); // CLK activo, desplaza
      CLK_CD4014_SetLow(); // CLK inactivo
      if (DATA_CD4014_GetValue()) data|=0x40;
      CLK_CD4014_SetHigh(); // CLK activo, desplaza
      CLK_CD4014_SetLow(); // CLK inactivo
      if (DATA_CD4014_GetValue()) data|=0x20;
      CLK_CD4014_SetHigh(); // CLK activo, desplaza
      CLK_CD4014_SetLow(); // CLK inactivo
      if (DATA_CD4014_GetValue()) data|=0x10;
      CLK_CD4014_SetHigh(); // CLK activo, desplaza
      CLK_CD4014_SetLow(); // CLK inactivo
      if (DATA_CD4014_GetValue()) data|=0x08;
      CLK_CD4014_SetHigh(); // CLK activo, desplaza
      CLK_CD4014_SetLow(); // CLK inactivo
      if (DATA_CD4014_GetValue()) data|=0x04;
      CLK_CD4014_SetHigh(); // CLK activo, desplaza
      CLK_CD4014_SetLow(); // CLK inactivo
      if (DATA_CD4014_GetValue()) data|=0x02;
      CLK_CD4014_SetHigh(); // CLK activo, desplaza
      CLK_CD4014_SetLow(); // CLK inactivo
      if (DATA_CD4014_GetValue()) data|=0x01;
      CLK_CD4014_SetHigh(); // CLK activo, desplaza
      CLK_CD4014_SetLow(); // CLK inactivo
      DatosCD4014[bytes] = data; // Copiamos el dato compuesto al array
   }
//#ifdef PinTestCD4014
   //output_low (PinTestCD4014); // depuracion
//#endif
}