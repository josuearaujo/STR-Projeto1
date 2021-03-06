#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "BlackGPIO/BlackGPIO.h"
#include <unistd.h>
#include <vector>
#include <array>

using namespace BlackLib;

int main(){
	srand(time(NULL));
	int ledDaVez, botaoDaVez;

	BlackGPIO botao_Vermelho(GPIO_48, input);
    BlackGPIO botao_Verde(GPIO_49, input);
    BlackGPIO botao_Azul(GPIO_15, input);
    BlackGPIO botao_Amarelo(GPIO_20, input);
    BlackGPIO botaoStart(GPIO_14, input);

    BlackGPIO Led_Vermelho(GPIO_44, output);
    BlackGPIO Led_Verde(GPIO_26, output);
    BlackGPIO Led_Azul(GPIO_67, output);
    BlackGPIO Led_Amarelo(GPIO_68, output);
    BlackGPIO Led_Sistema(GPIO_66, output);
    BlackGPIO Led_Derrota(GPIO_65, output);
	
    while(1){
    	//Fica nesse loop até apertar o botão e iniciar o jogo
    	while(botaoStart.getValue() == "0"); 

    	//Após pressionar o botão start, apaga o led da derrota(se estiver aceso), acende o led do sistema e inicia o jogo.
    	Led_Derrota.setValue(low);
    	Led_Sistema.setValue(high);
    	while(1){
    		//Pisca a sequencia de leds como um sinal que o jogo vai ligar o led desejado.
    		Led_Vermelho.setValue(high);
    		sleep(0.5);
    		Led_Verde.setValue(high);
    		sleep(0.5);
    		Led_Azul.setValue(high);
    		sleep(0.5);
    		Led_Amarelo.setValue(high);
    		sleep(0.5);

    		Led_Vermelho.setValue(low);
    		Led_Verde.setValue(low);
    		Led_Azul.setValue(low);
    		Led_Amarelo.setValue(low); 
    		sleep(0.5); 


    		ledDaVez = rand()%4; //Escolhendo o led que será aceso. Conforme legenda no final do código (LEGENDA 1)
    		switch(ledDaVez){  //Acendendo o led correspondente
    			case 0:
    				Led_Vermelho.setValue(high);
    				sleep(1);
    				Led_Vermelho.setValue(low);
    				break;
    			case 1:
    				Led_Verde.setValue(high);
    				sleep(1);
    				Led_Verde.setValue(low);
    				break;
    			case 2:
    				Led_Azul.setValue(high);
    				sleep(1);
    				Led_Azul.setValue(low);
    				break;
    			case 3:
    				Led_Amarelo.setValue(high);
    				sleep(1);
    				Led_Amarelo.setValue(low);
    				break;
    		}

    		while(1){  //Esperando o jogador apertar o botão. Conforme legenda no fim do código (LEGENDA 2)
    			if(botao_Vermelho.getValue() == "1"){
    				botaoDaVez = 2;
    				break;
    			} else if(botao_Verde.getValue() == "1"){
    				botaoDaVez = 3;
    				break;
    			} else if(botao_Azul.getValue() == "1"){
    				botaoDaVez = 0;
    				break;
    			} else if(botao_Amarelo.getValue() == "1"){
    				botaoDaVez = 1;
    				break;
    			}
    		}
    		//Testar se o botão pressionado corresponde ao esperado.
    		if(botaoDaVez == ledDaVez){ //O jogador pressionou o botão correto, todos os leds piscam!
    			Led_Vermelho.setValue(high);
    			Led_Verde.setValue(high);
    			Led_Azul.setValue(high);
    			Led_Amarelo.setValue(high);

    			sleep(1);

				Led_Vermelho.setValue(low);
    			Led_Verde.setValue(low);
    			Led_Azul.setValue(low);
    			Led_Amarelo.setValue(low);    			
    		} else{  //Se o jogador pressionar o botão errado, acende o led da derrota!
    			Led_Derrota.setValue(high);
    			Led_Sistema.setValue(low);
    			break;
    		}
    	}

    }

}


/*
~~~~~~~~~ LEGENDA 1 - Leds ~~~~~~~~~
Número    -----      Cor do Led
0		  -----    Vermelho
1		  -----    Verde
2		  -----    Azul
3		  -----    Amarelo





~~~~~~~~~ LEGENDA 2 - Botões ~~~~~~~~~
Cor do Led  ----------- Cor do Botão a ser apertado
Vermelho    -----------  Azul
Verde       -----------  Amarelo
Azul        -----------  Vermelho
Amarelo     -----------  Verde





~~~~~~Disposição dos leds e botões~~~~~~

			~~~~~ LEDS ~~~~~
[VERMELHO] - [VERDE] - [AZUL] - [AMARELO]

			~~~~~ BOTÕES ~~~~~
[AMARELO] - [VERMELHO] - [VERDE] - [AZUL]
*/