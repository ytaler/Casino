#include "net_pozos.h"

uint8_t verificarBotones(uint8_t datos){
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
