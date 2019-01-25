#include "net_pozos.h"

uint8_t verificarBotonesPlayer(uint8_t datos){
    // descomentar para debug de comportamiento de botones.
    // Con este codigo se permite un solo boton pulsado a la vez
    // cuando hay dos botones se devuelve cero
    //datos = 0x03;
    // se limpia la parte MSB
    datos &= 0x0F;
    switch(datos){
        case 0x01:
        case 0x02:
            break;
        case 0x04:
            datos = 0x03;
            break;
        case 0x08:
            datos = 0x04;
            break;
        default:
            datos = 0x00;
            break;
    }
    return datos;
}

uint8_t chequeo8Bits(uint8_t *datos, uint8_t mascara){
    uint8_t i, contador = 0, temp, id = 0;
    temp = (uint8_t)(*datos & mascara);
    for(i=0; i<8; i++){
        contador += (uint8_t)(temp & 0x01);
        if (contador > 1){
            id = 0x00;
            break;
        }
        if((uint8_t)(temp & 0x01)){
			id=(uint8_t) (i+1);
		}
        temp >>= 1;
    }
return id;
}

uint8_t verificarSeleccionPlayer(uint8_t *datos){
    // La funcion devuelve directamente el nro de player
	return chequeo8Bits(&*datos, 0x7F);
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
	return chequeo8Bits(&*datos, 0x7F);
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
	return chequeo8Bits(&*datos, 0x7F);
}

uint8_t verificarTecladoNumerico(uint8_t datos_1, uint8_t *datos_2){
    // El orden de los parametros es importante:
    // *datos_1 representa los botones 8 y 9
    // *datos_2 representa los botones del 0 al 7
    // Devuelve un valor de 0 a 10. El cero indica ninguna tecla pulsada o 
    // pulsaciones simultaneas. 
    // Los botones se indican del 1 al 10, representando un digito menos:
    // Por ejemplo, si retorna 1 significa que se pulso el 0, si retorna 10
    // significa que se pulso el 9.....
    uint8_t respuesta;
    if (datos_1 > 0 && *datos_2 == 0){
        respuesta = chequeo8Bits(&datos_1,0x03);
        // como respuesta puede venir con valor 0, 1 o 2, si es mayor que cero
        // se le suma 8 para indicar que es 8 o 9
        if (respuesta > 0){
            respuesta += 8;
        }
    }
    else{
        if (datos_1 == 0 && *datos_2 > 0){
            respuesta = chequeo8Bits(&*datos_2,0xFF);
        }
        else{
            respuesta = 0x00;
        }
    }
	return respuesta;
}