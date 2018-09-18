#include "net_pozos.h"

uint8_t verificarBotonesPlayer(uint8_t datos){
    // descomentar para debug de comportamiento de botones.
    // Con este codigo se permite un solo boton pulsado a la vez
    // cuando hay dos botones se devuelve cero
    //datos = 0x03;
    uint8_t contador = 0, temp;
    // se limpia la parte MSB
    datos &= 0x0F;
    temp = datos;
    // se testean 4 bits, comenzando por el bit 0
    contador += (uint8_t)(temp & 0x01);
    // se rota y se continua con bit 1
    temp >>= 1;    
    contador += (uint8_t)(temp & 0x01);
    // se rota y se continua con bit 2
    temp >>= 1;    
    contador += (uint8_t)(temp & 0x01);
    // se rota y se continua con bit 3
    temp >>= 1;    
    contador += (uint8_t)(temp & 0x01);        
    if (contador > 1)
        return 0x00;
    return datos;
}

uint8_t chequeo8Bits(uint8_t *datos){
    uint8_t i, contador = 0, temp, id = 0;
    temp = (uint8_t)(*datos & 0x7F);
    for(i=0; i<7; i++){
        contador += (uint8_t)(temp & 0x01);
        if (contador > 1){
            return 0x00;
        }
        if((uint8_t)(temp & 0x01)){
			id=i+1;
		}
        temp >>= 1;
    }
return id;
}

uint8_t verificarSeleccionPlayer(uint8_t *datos){
    // La funcion devuelve directamente el nro de player
	return chequeo8Bits(&*datos);
}

uint8_t verificarPagoDealer(uint8_t *datos){
    // La tabla es:
    // ID PAGO  Descripcion
    //  1       Escalera Real
    //  2       Escalera Color
    //  3       Poker
    //  4       Full
    //  5       Color
    //  6       Lucky Player
    //  7       Magic Card
	return chequeo8Bits(&*datos);
}

uint8_t verificarPagoPlayer(uint8_t *datos){
    // La tabla es:
    // ID PAGO  Descripcion
    //  1       Escalera Real
    //  2       Escalera Color
    //  3       Poker
    //  4       Full
    //  5       Color
    //  6       Lucky Player
    //  7       Magic Card
	return chequeo8Bits(&*datos);
}
