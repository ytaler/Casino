#include "net_pozos.h"

uint8_t verificarBotonesPlayer(uint8_t datos){
    // descomentar para debug de comportamiento de botones.
    // Con este codigo se permite un solo boton pulsado a la vez
    // cuando hay dos botones se devuelve cero
    //datos = 0x03;
    uint8_t contador = 0;
    datos &= 0x0F;
    if (datos & 0x01)
        contador++;
    if (datos & 0x02)
        contador++;
    if (datos & 0x04)
        contador++;
    if (datos & 0x08)
        contador++;
    if (contador > 1)
        datos = 0;
    return datos;
}
