/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>   /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */
#include <ctype.h>

#endif

#include "mcc_generated_files/mcc.h"
#include "shift_io.h"
#include "net_pozos.h"
#include "lcd.h"

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

int ciclos = 0;
uint8_t player[7], dealerSelectPlayer, dealerPagaDealer, dealerPagaPlayer, keypad, playerAPagar;
uint8_t oldPlayer[7], oldDealerSelectPlayer, oldDealerPagaDealer, oldDealerPagaPlayer, oldKeypad, oldPlayerAPagar;
uint8_t tablaLedPlayers, tablaLedPlayersBackUp, i, repeticion, repeticionPlayer[7], indiceRespuesta, contador, diferenciaAscii;
const uint8_t antirrebote = 3, delayVueltaMs = 125;
//uint8_t respuestaSpi;
uint16_t timeoutMensaje;
uint32_t monto=0; // usado para guardar el monto
bool botonPulsado_Bet = false, botonPulsado_Hold = false, botonPulsado_CashOut = false, botonPulsado_Clear = false, escaleraReal = false, finTransmision = false, mesaActiva = false, apuestasPlayer = false;
bool tablaPlayers[8]; // tiene un valor de mas por correcion de indices
char mensajeSpi[20], respuestaRaspBerryPi[18];

void clearBuffer(void);
/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main(void)
{
    // la inicializacion debe hacerlo de tal forma de dejar todos los disp
    // listos pero apagados o en stand by
    SYSTEM_Initialize();
    InitCD4014();
    lcd_init();
    indiceRespuesta = 0x00;
    finTransmision = false;
    lcd_write2lines("Mesa Desactivada","Sistema NetPozos");
    while(!mesaActiva){
        printf("|02#\r\n");
        __delay_ms(2500);
        if(finTransmision){
            // verificamos si recibimos el mensaje de activacion
            if( (respuestaRaspBerryPi[2] == '2') && (toupper(respuestaRaspBerryPi[4]) == 'A') ){
                mesaActiva = true;
                break;
            }
            else
                finTransmision = false;
            clearBuffer();
        }
        __delay_ms(2500);
    }
    lcd_write2lines("Sistema NetPozos"," * * v1.0.0 * * ");
    __delay_ms(2000);
    // Una vez activado el sistema se procede al bucle principal, comenzando
    // por el estado bet (01;B)
    //sprintf(mensajeSpi,"|01;B#\r\n");
    //printf(mensajeSpi);
    printf("|01;B#\r\n");
    //SPI_Exchange8bitBuffer(mensajeSpi,sizeof(mensajeSpi),NULL);
    lcd_write2lines("\xA5Mesa  Activada!"," Comienza juego ");
    __delay_ms(2000);
    GAME_Status_SetBet(); // Enciende led verde indicando estado Bet
    tablaPlayers[0] = tablaPlayers[1] = tablaPlayers[2] = tablaPlayers[3] = tablaPlayers[4] = tablaPlayers[5] = tablaPlayers[6] = tablaPlayers[7] = true; // habilitamos toods los players
    while(1) // bucle principal del juego
    {        
        /***********************************************************************
                                        BET
         **********************************************************************/
        // BET equivale a PORTA.RA7 = 0, y Game_Status es PORTA.RA7
        // Inicializacion de variables, estados, indicadores
        monto = 0x00;
        playerAPagar = 0x00;
        tablaLedPlayers = 0x00;
        /*
        for(i=0; i<8; i++){
            if(tablaPlayers[i]){
                tablaLedPlayers = (uint8_t) ( tablaLedPlayers | (uint8_t)( 0x01 << i) );
            }
        }
        */
        botonPulsado_Clear = botonPulsado_CashOut = botonPulsado_Bet = botonPulsado_Hold = false;
        oldDealerSelectPlayer = oldDealerPagaDealer = oldDealerPagaPlayer = oldKeypad = oldPlayerAPagar = repeticion = 0x00;
        oldPlayer[0] = oldPlayer[1] = oldPlayer[2] = oldPlayer[3] = oldPlayer[4] = oldPlayer[5] = oldPlayer[6] = 0x00;
        GAME_Clear_Players(); // Apaga todos los leds indicadores de los players        
        lcd_write2lines("Esperando","apuestas");
        while(!GAME_Status){
            // En estado Bet hay 4 posibilidades:
            // 1) Los botones del teclado numero por el monto de la apuesta y el player
            // 2) El pedido de cash out
            // 3) Los botones del player
            // 4) El boton de hold
            ReadCD4014();  // Lee entradas serie
            // Se individualizan los valores leidos en una variable por player
            // Se normalizan todas las lecturas de los players a LSB
            // Para los players impares en donde el dato esta en MSB, se hace un shift
            // de 4 posiciones de tal modo que quede en el LSB
            // 7 players
            //sprintf(mensajeSpi,"ANTES * BET * P0: %u - P1: %u - P2: %u - P3: %u - P4: %u - P5: %u - P6: %u - KP: %u,%u - DSP: %u\r\n", DatosCD4014[0], (uint8_t)(DatosCD4014[0] >> 4), DatosCD4014[1], (uint8_t)(DatosCD4014[1] >> 4), DatosCD4014[2], (uint8_t)(DatosCD4014[2] >> 4), DatosCD4014[3], (uint8_t)(DatosCD4014[3] >> 6),&DatosCD4014[4], DatosCD4014[5]);
            //printf(mensajeSpi);
            player[0]=verificarBotonesPlayer(DatosCD4014[0]);
            player[1]=verificarBotonesPlayer((uint8_t)(DatosCD4014[0] >> 4));
            player[2]=verificarBotonesPlayer(DatosCD4014[1]);
            player[3]=verificarBotonesPlayer((uint8_t)(DatosCD4014[1] >> 4));
            player[4]=verificarBotonesPlayer(DatosCD4014[2]);
            player[5]=verificarBotonesPlayer((uint8_t)(DatosCD4014[2] >> 4));
            player[6]=verificarBotonesPlayer(DatosCD4014[3]);
            keypad = verificarTecladoNumerico((uint8_t)(DatosCD4014[3] >> 6),&DatosCD4014[4]);
            dealerSelectPlayer=verificarSeleccionPlayer(&DatosCD4014[5]);
            //sprintf(mensajeSpi," DPS * BET * P0: %u - P1: %u - P2: %u - P3: %u - P4: %u - P5: %u - P6: %u - KP: %u - DSP: %u\r\n", player[0], player[1], player[2], player[3], player[4], player[5], player[6], keypad, dealerSelectPlayer);
            //printf(mensajeSpi);
            // Una vez leidas todas las variables se procede a la toma de decisiones.
            // 1) Primero se calcula el monto de la apuesta (si es que cambio / hay)
            if(keypad>0){
                if( (keypad != oldKeypad) || (repeticion > antirrebote) ){
                    oldKeypad = keypad;
                    repeticion = 0x00;
                    if(monto < PREMIO_MAX){
                        monto *= 10;
                        monto += (uint32_t) (keypad-1);
                        sprintf(line[1],"$ %lu",monto);
                        lcd_write2lines("Ingrese monto:",line[1]);
                    }                    
                }
                else{
                    repeticion++;
                }
            }
            // 2) Cargar monto en un player o marcar para realizar pago
            if(dealerSelectPlayer>0){
                // Almacenamos el player en la variable para indicar con led player
                playerAPagar = dealerSelectPlayer;
                // Enciende el player seleccionado para pagar
                GAME_Set_Player();
                // una vez seleccionado el player verificamos si esta habilitado                
                if(tablaPlayers[dealerSelectPlayer]){
                    // Hay dos posibilidades: realizar apuesta o marcar player
                    // para luego realizar cash out.
                    if(monto > 0){
                        // significa que se habia ingresado un monto y esta listo
                        // para comprar creditos se debe enviar mensaje:
                        // 03;NroPlayer;Monto
                        //sprintf(mensajeSpi,"|03;%u;%lu#\r\n",dealerSelectPlayer,monto);
                        //printf(mensajeSpi);
                        //SPI_Exchange8bitBuffer(mensajeSpi,sizeof(mensajeSpi),NULL);
                        printf("|03;%u;%lu#\r\n",dealerSelectPlayer,monto);
                        // Escribimos info en LCD
                        sprintf(line[0],"Monto player %u",dealerSelectPlayer);
                        sprintf(line[1], "$ %lu", monto);
                        lcd_write2lines(line[0],line[1]);
                        monto = 0x00;
                        playerAPagar = 0x00;
                        timeoutMensaje = 10000/delayVueltaMs; // = 80 --> Equivale aprox 10 segundos con delay de 125 ms
                    }
                }
                else{
                    playerAPagar = 0x00;
                    timeoutMensaje = 1000/delayVueltaMs; // = 80 --> Equivale aprox 10 segundos con delay de 125 ms
                }
            }
            for(i = 0; i < 7; i++){
                if( (player[i] > 0) && (tablaPlayers[i+1]) ){
                    if( (player[i] != oldPlayer[i]) || (repeticionPlayer[i] > antirrebote) ){
                        oldPlayer[i] = player[i];
                        repeticionPlayer[i] = 0x00;
                        //sprintf(mensajeSpi,"|05;%u;%c;%c#\r\n", i+1, tablaApuestaPlayer[0][player[i]], tablaApuestaPlayer[1][player[i]]);
                        //printf(mensajeSpi);
                        //SPI_Exchange8bitBuffer(mensajeSpi,sizeof(mensajeSpi),NULL);
                        printf("|05;%u;%c;%c#\r\n", i+1, tablaApuestaPlayer[0][player[i]], tablaApuestaPlayer[1][player[i]]);
                        // esta tabla almacena las apuestas de player a player para luego mostrarlos
                        // solamente cuando es apuesta a Player (player[i]) < 3
                        // 1 --> D -
                        // 2 --> D +
                        // 3 --> P -
                        // 4 --> P +
                        //if(player[i] > 2)
                            //tablaLedPlayers |= (uint8_t) (0x01 << i);
                    }
                    else{
                        repeticionPlayer[i]++;
                    }
                }
            }         
            if(botonPulsado_CashOut){
                botonPulsado_CashOut = false;
                if(playerAPagar > 0){
                    indiceRespuesta = 0x00;
                    finTransmision = false;
                    contador = 0x00;
                    clearBuffer();
                    //sprintf(mensajeSpi,"|04;%u\r\n",playerAPagar);
                    //printf(mensajeSpi);
                    //SPI_Exchange8bitBuffer(mensajeSpi,sizeof(mensajeSpi),NULL);
                    printf(mensajeSpi,"|04;%u#\r\n",playerAPagar);
                    sprintf(line[1],"Out Player %u", playerAPagar);
                    lcd_write2lines("Solicitando Cash",line[1]);
                    while(!finTransmision){
                        // con la combinacion de 50 ms de delay y 200 vueltas, se hace
                        // un tiempo de espera maximo de 10 segundos.
                        __delay_ms(50);
                        contador++;
                        if(contador > 200){
                            // ToDo: ver caso para enviar mensaje de cancelacion de cash out por timeout si es necesario
                            printf("|00;Error Cash Out: valor recibido %s para player %u#\r\n", respuestaRaspBerryPi, playerAPagar);
                            lcd_write2lines("Respuesta no re_","cibida,reintente");
                            timeoutMensaje = 20000/delayVueltaMs; // = 160 --> Equivale aprox 20 segundos con delay de 125 ms
                            break;
                        }
                    }
                    // verificamos si no hubo timeout y la respuesta de la raspberry
                    if(contador < 200){
                        if(respuestaRaspBerryPi[2] == '4'){
                            // ingresa solo con un mensaje valido
                            for(i = 0; i < 14; i++){
                                respuestaRaspBerryPi[i] = respuestaRaspBerryPi[i+4];                               
                            }
                            // Asigna cero en caso de no haber recibido nada
                            if(!isdigit(respuestaRaspBerryPi[0])){
                                respuestaRaspBerryPi[0] = '0';
                                respuestaRaspBerryPi[1] = 0x00;
                            }
                            // Escribimos info en LCD
                            sprintf(line[0],"CashOut Player %u",playerAPagar);
                            //sprintf(line[1], "$ %lu", monto);
                            sprintf(line[1],"$ %s", respuestaRaspBerryPi);
                            lcd_write2lines(line[0],line[1]);
                            playerAPagar = 0x00; // Elimina valor variable       
                            timeoutMensaje = 60000/delayVueltaMs; // = 480 --> Equivale aprox 60 segundos con delay de 125 ms
                            }
                        else{
                            printf("|00;Error Cash Out: valor recibido %s para player %u#\r\n", respuestaRaspBerryPi, playerAPagar);
                            lcd_write2lines("Respuesta no re_","cibida,reintente");
                            timeoutMensaje = 20000/delayVueltaMs; // = 160 --> Equivale aprox 20 segundos con delay de 125 ms                            
                        }
                    }
                }
            }
            if(botonPulsado_Clear){
                botonPulsado_Clear = botonPulsado_CashOut = botonPulsado_Bet = botonPulsado_Hold = false;
                monto = 0x00;
                playerAPagar = 0x00;
                GAME_Clear_Players(); // Apaga todos los leds indicadores de los players
                lcd_write2lines("Esperando","apuestas");
                timeoutMensaje = 0x00;
            }
            if(botonPulsado_Hold){
                botonPulsado_Hold = false;
                INTCONbits.TMR0IE = 0; // Deshabilita blink por TMR0
                //sprintf(mensajeSpi,"|01;H#\r\n");
                //printf(mensajeSpi);
                //SPI_Exchange8bitBuffer(mensajeSpi,sizeof(mensajeSpi),NULL);
                printf("|01;H#\r\n");
                GAME_Clear_Players(); // Apaga todos los leds indicadores de los players
                GAME_Status_SetHold(); // Enciende led rojo indicando estado Hold
                timeoutMensaje = 0x00;
            }
            /*
            if(botonPagoDealer && botonPagoPlayer){
                if(repeticion > antirrebote){
                    timeoutMensaje = 10000/delayVueltaMs; // = 80 --> Equivale aprox 10 segundos con delay de 125 ms
                    if(dealerSelectPlayer > 0){
                        // Seccion para deshabilitar players
                        repeticion = 0x00;
                        tablaPlayers[dealerSelectPlayer] = !tablaPlayers[dealerSelectPlayer];
                        sprintf(line[0],"Player %u",dealerSelectPlayer);
                        if(tablaPlayers[dealerSelectPlayer]){
                            sprintf(line[1],"Activado", respuestaRaspBerryPi);
                            tablaLedPlayers = (uint8_t) ( tablaLedPlayers | (uint8_t)( 0x01 << (dealerSelectPlayer-1)) );
                        }
                        else{
                            sprintf(line[1],"Desactivado", respuestaRaspBerryPi);
                            tablaLedPlayers = (uint8_t) ( tablaLedPlayers & (uint8_t) ~( (uint8_t)( 0x01 << (dealerSelectPlayer-1)) ) );
                        }
                        lcd_write2lines(line[0],line[1]);
                    }else{
                        if(BotonClear || botonPulsado_Clear){
                            // Deshabilitamos todos los players
                            repeticion = 0x00;
                            tablaPlayers[0] = tablaPlayers[1] = tablaPlayers[2] = tablaPlayers[3] = tablaPlayers[4] = tablaPlayers[5] = tablaPlayers[6] = tablaPlayers[7] = false; // deshabilitamos toods los players
                            botonPulsado_Clear = false;
                            lcd_write2lines("Todos los player","desactivados");
                            tablaLedPlayers = 0x00;
                        }
                        else{
                            if(BotonCashOut || botonPulsado_CashOut){
                                // Habilitamos todos los players
                                repeticion = 0x00;                            
                                tablaPlayers[0] = tablaPlayers[1] = tablaPlayers[2] = tablaPlayers[3] = tablaPlayers[4] = tablaPlayers[5] = tablaPlayers[6] = tablaPlayers[7] = true; // habilitamos toods los players
                                botonPulsado_CashOut = false;
                                lcd_write2lines("Todos los player","activados");
                                tablaLedPlayers = 0x7F;
                            }
                        }
                    }
                    GAME_Set_Players();
                }
                else{
                    repeticion++;
                }
            }
            */
            __delay_ms(125);
            if(timeoutMensaje > 0x00){
                // entra solamente con timeoutMensaje activado
                timeoutMensaje--;
                if(timeoutMensaje == 0x00){
                    GAME_Clear_Players(); // Apaga todos los leds indicadores de los players
                    // limpia pantalla cuando expiro el timeoutMensaje
                    lcd_write2lines("Esperando","apuestas");
                }
            }
        }
        /***********************************************************************
                                      HOLD
         **********************************************************************/
        // HOLD equivale a PORTA.RA7 = 1, y Game_Status es PORTA.RA7
        // Se encienden los leds de los players que apostaron a players
        finTransmision = apuestasPlayer = false;
        oldDealerSelectPlayer = oldDealerPagaDealer = oldDealerPagaPlayer = oldKeypad = oldPlayerAPagar = repeticion = 0x00;
        player[0]=player[1]=player[2]=player[3]=player[4]=player[5]=player[6]=0x00;
        playerAPagar = 0x00;
        contador = 0x00;
        clearBuffer();
        lcd_write2lines("Solicitando","apuesta players");
        // solicitamos la tabla de players al servidor
        while(!apuestasPlayer){
            printf("|08#\r\n");
            __delay_ms(500);
            if(finTransmision){
                // verificamos si recibimos el mensaje de tabla de players |08;xX
                if(respuestaRaspBerryPi[2] == '8'){
                    // se recibe el msb primero y luego el lsb
                    // la recepcion por uart tiene caracteres filtrados, por lo tanto
                    // verificamos unicamente que sea de 0 a 7 (48 a 55 ascii)
                    if(respuestaRaspBerryPi[4] < 56){
                        diferenciaAscii = 48;
                    }
                    else{
                        // sino esta dentro de los valores esperados asignamos su propio
                        // valor para anularlo luego de la resta en el momenot de asignacion
                        diferenciaAscii = (uint8_t) respuestaRaspBerryPi[4];
                    }
                    tablaLedPlayers = (uint8_t) ( ( (uint8_t) respuestaRaspBerryPi[4] - diferenciaAscii ) << 4 );
                    // lo mismo que lo anterior, como viene filtrado, solamente
                    // verificamos que sea distinto de I o i
                    if( respuestaRaspBerryPi[5] < 58){
                        // de 0 a 9
                        diferenciaAscii = 48;
                    }
                    else{
                        // de A-F o a-f
                        if( (respuestaRaspBerryPi[5] != 73) && (respuestaRaspBerryPi[5] != 105) ){
                            diferenciaAscii = 55;
                        }
                        else{
                            // sino esta dentro de los valores esperados asignamos su propio
                            // valor para anularlo luego de la resta en el momenot de asignacion
                            diferenciaAscii = (uint8_t) respuestaRaspBerryPi[5];
                        }
                    }
                    tablaLedPlayers = (uint8_t) ( tablaLedPlayers | ( (uint8_t) respuestaRaspBerryPi[5] - diferenciaAscii) );
                    apuestasPlayer = true;
                }
                else
                    finTransmision = false;
                clearBuffer();
            }
            contador++;
            if(contador > 60){
                // significa que pasaron 30 segundos con un delay de 500 ms,
                // se asigna cero por default para no demorar juego
                tablaLedPlayers = 0x00;
                apuestasPlayer = true; // seteamos la salida controlada
                finTransmision = false;
                break; // forzamos salida, si falla tenemos la salida controlada seteada
            }
        }
        botonPulsado_Clear = botonPulsado_CashOut = botonPulsado_Bet = botonPulsado_Hold = false;
        tablaLedPlayersBackUp = tablaLedPlayers;
        GAME_Set_Players();
        lcd_write2lines("Juego en curso","");
        while(GAME_Status){
            // En estado Hold hay X posibilidades:
            // x) El boton de Bet
            ReadCD4014();  // Lee entradas serie
            // Se ignoran las pulsaciones de los players y del teclado numerico
            //sprintf(mensajeSpi,"* HOLD * KP: %u,%u - DSP: %u - DPD: %u - DPP: %u\r\n", (uint8_t)(DatosCD4014[3] >> 6), DatosCD4014[4], DatosCD4014[5], DatosCD4014[6], DatosCD4014[7]);
            //printf(mensajeSpi);
            keypad = verificarTecladoNumerico((uint8_t)(DatosCD4014[3] >> 6),&DatosCD4014[4]);
            dealerSelectPlayer = verificarSeleccionPlayer(&DatosCD4014[5]);
            dealerPagaDealer = verificarPagoDealer(&DatosCD4014[6]);
            dealerPagaPlayer = verificarPagoPlayer(&DatosCD4014[7]);
            //sprintf(mensajeSpi,"* HOLD * KP: %u - DSP: %u - DPD: %u - DPP: %u\r\n", keypad, dealerSelectPlayer, dealerPagaDealer, dealerPagaPlayer);
            //printf(mensajeSpi);
            
            if(dealerSelectPlayer > 0){
                // almacenar el numero de player a pagar
                INTCONbits.TMR0IE = 0; // Deshabilita blink por TMR0
                escaleraReal = false;
                playerAPagar = dealerSelectPlayer;
                timeoutMensaje = 0x00;
                //GAME_Set_Player();
            }
            if( (dealerPagaDealer > 0) && (botonPagoDealer) ){
                // 8 antirrebotes equivalen a no volver a disparar el premio por un valor de ~ timeout / 2
                if( (dealerPagaDealer != oldDealerPagaDealer) || (repeticion > (8*antirrebote)) ){
                    oldDealerPagaDealer = dealerPagaDealer;
                    repeticion = 0x00;
                    // se deben pulsar las dos teclas simultaneamente por seguridad
                    playerAPagar = 0x00;
                    //sprintf(mensajeSpi,"|06;0;%u#\r\n",dealerPagaDealer);
                    //printf(mensajeSpi);
                    //SPI_Exchange8bitBuffer(mensajeSpi,sizeof(mensajeSpi),NULL);
                    printf("|06;0;%u#\r\n",dealerPagaDealer);
                    lcd_write2lines("Ap. Dealer",premios[dealerPagaDealer]);
                    timeoutMensaje = 6500/delayVueltaMs; // = 52 --> Equivale aprox 6,5 segundos con delay de 125
                    if(dealerPagaDealer == 1){
                        // Significa escalera real dealer --> todos los leds deben parpadear
                        INTCONbits.TMR0IE = 1; // Habilita blink por TMR0
                        escaleraReal = true; //
                    }
                    else{
                        // sino resto de premios
                        INTCONbits.TMR0IE = 0; // Deshabilita blink por TMR0
                        escaleraReal = false;
                    }
                    GAME_Clear_Players(); // Apaga todos los leds indicadores de los players
                }
                else{
                    repeticion++;
                }
            }
            if( (dealerPagaPlayer > 0) && (botonPagoPlayer) && (playerAPagar > 0) ){
                // 8 antirrebotes equivalen a no volver a disparar el premio por un valor de ~ timeout / 2
                if( (dealerPagaPlayer != oldDealerPagaPlayer) || (playerAPagar != oldPlayerAPagar) || (repeticion > (8*antirrebote)) ){
                    GAME_Set_Players();
                    oldDealerPagaPlayer = dealerPagaPlayer;
                    oldPlayerAPagar = playerAPagar;
                    repeticion = 0x00;
                    // se debe elegir primero el nro de player a pagar y luego el premio
                    // ademas de pulsar la tecla de pago por seguridad
                    //sprintf(mensajeSpi,"|06;%u;%u#\r\n",playerAPagar,dealerPagaPlayer);
                    //printf(mensajeSpi);
                    //SPI_Exchange8bitBuffer(mensajeSpi,sizeof(mensajeSpi),NULL);
                    printf("|06;%u;%u#\r\n",playerAPagar,dealerPagaPlayer);
                    sprintf(line[0],"Ap. Player %u",playerAPagar);
                    lcd_write2lines(line[0],premios[dealerPagaPlayer]);
                    tablaLedPlayers = (uint8_t) ( tablaLedPlayers & (uint8_t) ~((uint8_t)( 0x01 << (playerAPagar-1))) );
                    playerAPagar = 0x00;
                    timeoutMensaje = 6500/delayVueltaMs; // = 52 --> Equivale aprox 6,5 segundos con delay de 125
                    if(dealerPagaPlayer == 1){
                        // Significa escalera real dealer --> todos los leds deben parpadear
                        INTCONbits.TMR0IE = 1; // Habilita blink por TMR0
                        escaleraReal = true; // 
                    }
                    else{
                        // sino resto de premios
                        INTCONbits.TMR0IE = 0; // Deshabilita blink por TMR0
                        escaleraReal = false;
                    }
                }
                else{
                    repeticion++;
                }
            }
            if(botonPulsado_Clear){
                INTCONbits.TMR0IE = 0; // Deshabilita blink por TMR0
                botonPulsado_Clear = botonPulsado_Bet = botonPulsado_Hold = escaleraReal = false;
                if(keypad == 1){
                    // se deben cancelar todos los pagos
                    //sprintf(mensajeSpi,"|07#\r\n");
                    //printf(mensajeSpi);
                    //SPI_Exchange8bitBuffer(mensajeSpi,sizeof(mensajeSpi),NULL);
                    printf("|07#\r\n");
                    lcd_write2lines("Cancelando","todos los pagos");
                    timeoutMensaje = 10000/delayVueltaMs; // = 80 --> Equivale aprox 10 segundos con delay de 125 ms
                    tablaLedPlayers = tablaLedPlayersBackUp;
                }
                else{
                    lcd_write2lines("Juego en curso","");
                    timeoutMensaje = 0x00;
                }
                GAME_Set_Players();
            }                        
            if(botonPulsado_Bet){
                INTCONbits.TMR0IE = 0; // Deshabilita blink por TMR0
                botonPulsado_Bet = false;
                //sprintf(mensajeSpi,"|01;B#\r\n");
                //printf(mensajeSpi);
                //SPI_Exchange8bitBuffer(mensajeSpi,sizeof(mensajeSpi),NULL);
                printf("|01;B#\r\n");
                timeoutMensaje = 0x00;
                GAME_Clear_Players(); // Apaga todos los leds indicadores de los players
                GAME_Status_SetBet(); // Enciende led rojo indicando estado Hold
            }
            __delay_ms(125);
            if(timeoutMensaje > 0x00){
                // entra solamente con timeoutMensaje activado
                timeoutMensaje--;
                if(timeoutMensaje == 0x00){
                    INTCONbits.TMR0IE = 0; // Deshabilita blink por TMR0
                    escaleraReal = false;
                    // limpia pantalla cuando expiro el timeoutMensaje
                    lcd_write2lines("Juego en curso","");
                    GAME_Set_Players();
                }
            }            
        }
    }
}

void clearBuffer(void){
    uint8_t index;
    for(index=0; index < 18; index++){
        respuestaRaspBerryPi[index]=0x00;
    }
}