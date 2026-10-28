//JVida_DHIR_Controller.cpp
//13/10/2026
/*Daniel Luis de Amorim Mariano Santos
Henrique Campos Rodrigues
Isabella de Souza Fleury
Rafaella Castro Zandona Alves de Lima */

#include "JVida_DHIR_Controller.h"
#include "JVida_DHIR_View.cpp"
#include <stdio.h>

static void apresentarMapa() {
    desmarcarVizinhasMortas();
    if (mostrarMortos == 1) {
        marcarVizinhasMortas();
    }
    mostrarMapa();
    mostrarContagem(contarVivas(), contarVizinhasMortas());
}

void iniciar() {
    int op;
    int l;
    int c;
    int resultado;
    int qtd; //quantidade
    int vel; //velocidade
    int g; //geracao

    dim = pedirDim();
    limparMapa(); 

    do {
    	limparTela();
    	apresentarMapa();
        mostrarMenu();
        op = lerOpcao();
        switch (op) {
            case 1:
    			do {
				pedirCoordenadas(&l, &c);
    				if (!coordValida(l, c)) {
        			mostrarCoordInvalida();
        			pausar();
    				} else if (celulaViva(l, c)) {
        			if (perguntarExcluir()) {
        		    excluirCelula(l, c);
        			}
    			} else {
       				incluirCelula(l, c);
    			}
    			contAdicionar();
				} while (op = 1);
    			break;
    		case 2:
    			mostrarMortos = !mostrarMortos;
    			mostrarEstadoMortos(mostrarMortos);
    			break;
            case 3:
                resultado = salvarGeracao();
                if (resultado == 1) {
                    mostrarSalvoOk();
                } else {
                    mostrarErroArquivo();
                }
                break;
            case 4:
                resultado = carregarGeracao();
                if (resultado == 1) {
                    mostrarCarregadoOk();
                } else if (resultado == 0) {
                    mostrarFimGeracoes();
                } else {
                    mostrarErroArquivo();
                }
                break;
            case 5:
                proximaGeracao();
                apresentarMapa();
                break;
			case 6:
    			pedirQtdGeracoes(&qtd);
    			pedirVelocidade(&vel);
    			for (g = 1; g <= qtd; g++) {
        			proximaGeracao();
        			mostrarNumGeracao(g, qtd);
        			apresentarMapa();
        			if (g < qtd){
        				esperarVelocidade(vel);
        			}
    			}
    			pausar();    
            case 0:
                mostrarDespedida();
                break;
            default:
                mostrarOpcaoInvalida();
        }
    } while (op != 0);
}
