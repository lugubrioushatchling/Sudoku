/*
Autores: Laís Barreto, Yuri Gouveia, Jessé Alves
Título: Terminal Game Sudoku
Lançamento: 21/11/2020
Descrição: Esta é uma versão digital do jogo japonês "Sudoku". Todas as
regras se aplicam a essa versão, porém, por ser digital, possui
recursos extras. O jogo possui um sistema de pontuação baseado no tempo e
nos acertos e erros, ou seja, quanto maior a taxa de acertos e mais rápido
o jogo for resolvido, maior será a pontuação final.
*/


#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>


void atraso_rapido(){
    for(int x=0; x<200000000; x++);
}

//Apresentação do jogo
void banner_game(){
    printf("     _______. __    __   _______    ______    __  ___  __    __  \n");
    atraso_rapido();
    printf("    /       ||  |  |  | |       \\  /  __  \\  |  |/  / |  |  |  | \n");
    atraso_rapido();
    printf("   |   (----`|  |  |  | |  .--.  ||  |  |  | |  '  /  |  |  |  | \n");
    atraso_rapido();
    printf("    \\   \\    |  |  |  | |  |  |  ||  |  |  | |    <   |  |  |  | \n");
    atraso_rapido();
    printf(".----)   |   |  `--'  | |  '--'  ||  `--'  | |  .  \\  |  `--'  | \n");
    atraso_rapido();
    printf("|_______/     \\______/  |_______/  \\______/  |__|\\__\\  \\______/  \n");
    atraso_rapido();
    printf("Version 0.5 Beta\n");
    atraso_rapido();
}


void msg_sudoku_resolvido(){
    printf("  ____                _           _            \n");
    printf(" / ___|   _   _    __| |   ___   | | __  _   _ \n");
    printf(" \\___ \\  | | | |  / _` |  / _ \\  | |/ / | | | |\n");
    printf("  ___) | | |_| | | (_| | | (_) | |   <  | |_| |\n");
    printf(" |____/   \\__,_|  \\__,_|  \\___/  |_|\\_\\  \\__,_|\n");
    printf("  ____                         _           _       _           _ \n");
    printf(" |  _ \\    ___   ___    ___   | | __   __ (_)   __| |   ___   | |\n");
    printf(" | |_) |  / _ \\ / __|  / _ \\  | | \\ \\ / / | |  / _` |  / _ \\  | |\n");
    printf(" |  _ <  |  __/ \\__ \\ | (_) | | |  \\ V /  | | | (_| | | (_) | |_|\n");
    printf(" |_| \\_\\  \\___| |___/  \\___/  |_|   \\_/   |_|  \\__,_|  \\___/  (_)\n");
}

void concatenar_strings(char s1[], char s2[]){
    int i, j;
    for (i = 0; s1[i] != '\0'; ++i);
    for (j = 0; s2[j] != '\0'; ++j, ++i) {
        s1[i] = s2[j];
    }
    s1[i] = '\0';
}

//Responsável por ler o arquivo onde o sudoku está armazenado e carregar o jogo
void carregar_sudoku(char sudoku_game[9][9], char sudoku_resposta[9][9], int opcao){
    FILE *pont_arq;
    char carac;
    char caminho[] = ("sudokus/");
    char arquivo1[] = "sudoku_nv_easy1.txt";
    char arquivo2[] = "sudoku_nv_easy2.txt";
    char arquivo3[] = "sudoku_nv_med1.txt";
    char arquivo4[] = "sudoku_nv_med2.txt";
    char arquivo5[] = "sudoku_nv_hard1.txt";

    switch(opcao){
        case 1:
            concatenar_strings(caminho, arquivo1);
            break;

        case 2:
            concatenar_strings(caminho, arquivo2);
            break;

        case 3:
            concatenar_strings(caminho, arquivo3);
            break;

        case 4:
            concatenar_strings(caminho, arquivo4);
            break;

        case 5:
            concatenar_strings(caminho, arquivo5);
            break;

        default:
            concatenar_strings(caminho, arquivo1);
    }

    pont_arq = fopen(caminho, "r");
    for(int x=0; x <= 8; x++){
        for(int z=0; z <= 8; z++){
            carac=fgetc(pont_arq);
            sudoku_game[x][z]=carac;
        }
    }

    fgetc(pont_arq);

    for(int x=0; x <= 8; x++){
        for(int z=0; z <= 8; z++){
            carac=fgetc(pont_arq);
            sudoku_resposta[x][z]=carac;
        }
    }
    fclose(pont_arq);
}

//Cronometro, retorna minuto se a opção for 0 e retorna segundo se for 1
int atualizar_tempo(time_t tempo_inicio, int opcao){
    struct tm *tempo_decorrido;
    time_t tempo_atual;
    time(&tempo_atual);
    time_t tempo_decorrido_segundos = tempo_atual - tempo_inicio;
    tempo_decorrido = localtime(&tempo_decorrido_segundos);

    switch (opcao){
        case 1:
            return tempo_decorrido->tm_min;
            break;
        case 2:
            return tempo_decorrido->tm_sec;
            break;
        default:
            return 0; //se a opção n corresponder nem ao min nem ao seg o retorno é 0
    }
}

//o nome ja explica :D
int obter_min(time_t tempo_inicio){
    int min = atualizar_tempo(tempo_inicio, 1);
    return min;

}

//o nome ja explica :D
int obter_sec(time_t tempo_inicio){
    int sec = atualizar_tempo(tempo_inicio, 2);
    return sec;
}

//Interrompe a execução do programa por uma fração de segundos
void delay(int tempo){  //Tempo em segundos não pode passar de 59 e não pode ser meno que um
    time_t segundos;
    time(&segundos);
    if(tempo >= 1 && tempo <= 59){
        int sec = obter_sec(segundos);
        while(sec <= tempo){
            sec = obter_sec(segundos);
        }
    }
}

//Captura o tempo decorrido da função atualizar tempo e o imprime
void imprimir_tempo(time_t tempo_inicio){
    printf("Tempo decorrido:\n");
    printf("%d Minutos\n", obter_min(tempo_inicio));
    printf("%d Segundos\n", obter_sec(tempo_inicio));
}

void reiniciar_marcadores(int *pontuacao, int *status_game){
    *pontuacao = 0;
    *status_game = 1;
}

//Percorre o vetor onde estão inseridos as jogadas do jogador, e as apresenta de maneira legível e amigável
void imprimir_jogo(char sudoku_game[9][9]){
    printf("\n");
    printf("  |1| |2| |3|  |4| |5| |6|  |7| |8| |9|\n");
    printf("=========================================\n");
        for(int x=0; x <= 8; x++){
            for(int z=0; z <= 8; z++){
                if(z == 3 || z == 6){
                    printf("|");
                }
                if(x <= 8 && z == 0){
                    printf("|| %c ", sudoku_game[x][z]);
                }else{
                    printf("| %c ", sudoku_game[x][z]);
                }
        }
        printf("|| L%d \n", x+1);
        if(x == 2 || x == 5 || x == 8){
            printf("=========================================\n");
        }
        else{
            printf("==-----------==-----------==-----------==\n");
        }
    }
}

//Captura todas os dados da jogada
void realizar_jogada(int *linha, int *coluna, char *numero){
    printf("Qual Linha voce deseja selecionar? \n");
    scanf(" %d", linha);

    printf("Qual Coluna voce deseja selecionar? \n");
    scanf(" %d", coluna);

    printf("Digite o numero a ser inserido: \n");
    scanf(" %c", numero);
}

//Determina se a celula está disponível ou vaga
int validar_celula(char sudoku_game[9][9], int linha, int coluna){
    char espaco = ' ';
    if(sudoku_game[linha-1][coluna-1] == espaco){
        return 1;
    }
    //printf("O problema nas celulas!");
    return 0;
}

//Determina se as coordenadas estão de acordo com os índices válidos do vetor
int validar_coordenadas(int coluna, int linha){
    if(linha-1 >= 0 && linha-1 <= 8 && coluna-1 >= 0 && coluna-1 <= 8){

        return 1;
    }
    return 0;
}

//Reúne as principais funções de validação
int validar_jogada(char sudoku_game[9][9], int coluna, int linha){
    int celula_validada; int coordenada_validada;

    celula_validada = validar_celula(sudoku_game, coluna, linha);
    coordenada_validada = validar_coordenadas(coluna, linha);

    if(celula_validada == 1 && coordenada_validada == 1){
        return 1;
    }
    else{
        printf("Coordenada invalida ou ja possui numero!!\n");
        delay(1);
        return 0;
    }
    return 0;
}

//Determina se a jogada do jogador corresponde com o vetor que armazena o sudoku solucionado
int validar_acerto(char sudoku_resposta[9][9], int linha, int coluna, char numero){
    if(numero == sudoku_resposta[linha-1][coluna-1]){
        //printf("Correto!\n");
        return 1;
    }else{
        //printf("Errado!!\n");
        return 0;
    }
}

//A cada jogada checa se ainda possuem espaços vagos, se não tiver conclui-se que o jogador finalizou o sudoku, e o jogo termina
int checar_sudoku(char sudoku_game[9][9]){
    char espaco = ' ';
        for(int x=0; x <= 8; x++){
            for(int z=0; z <= 8; z++){
                if(sudoku_game[x][z] == espaco){
                    return 1;
                }
        }
    }
    return 2;
}
int calc_pontuacao_por_tempo(int tempo_inicio){
    int minutos = obter_min(tempo_inicio);
    if(minutos < 5){
        return 400;//pontuação 400
    }else if(minutos >= 5 && minutos < 10){
        return 300;//pontuação 300
    }else if(minutos >= 10 && minutos < 20){
        return 200;//pontuação 200
    }else if(minutos >= 20 && minutos < 30){
        return 100;//pontuação 100
    }else{
        return 0;
    }
}

//Exibe msg quando ganha pontos
void acrescimo_pontos(int *pontuacao, int qtd_pts){
    *pontuacao += qtd_pts;
    printf("----------------\n");
    printf("|Voce acertou!!|\n");
    printf("----------------\n");

    printf("-----------------\n");
    printf("|Ganhou %d pontos|\n", qtd_pts);
    printf("-----------------\n");
    delay(1);
}

//Exibe msg quando perde pontos
void decrescimo_pontos(int *pontuacao, int qtd_pts){
    *pontuacao -= qtd_pts;
    printf("--------------\n");
    printf("|Voce Errou!!|\n");
    printf("--------------\n");

    printf("------------------\n");
    printf("|Perdeu %d pontos|\n", qtd_pts);
    printf("------------------\n");
    delay(1);
}


void imprimir_pontuacao(int pontuacao){
    printf("----------------------\n");
    printf("|Pontos obtidos:  %d |\n", pontuacao);
    printf("----------------------\n");
    delay(1);
}

void imprimir_bonus_obtido(int bonus){
    printf("----------------------\n");
    printf("|Bonus obtido:  %d   |\n", bonus);
    printf("----------------------\n");
    delay(1);

}

void imprimir_niveis(){
    printf("\nNiveis Disponiveis:\n");
    atraso_rapido();
    printf("----------------------------\n");
    atraso_rapido();
    printf("|Nivel Facil I..........[1]|\n");
    atraso_rapido();
    printf("|Nivel Facil II.........[2]|\n");
    atraso_rapido();
    printf("|Nivel Medio I..........[3]|\n");
    atraso_rapido();
    printf("|Nivel Medio II.........[4]|\n");
    atraso_rapido();
    printf("|Nivel Dificil  I.......[5]|\n");
    atraso_rapido();
    printf("|Sair...................[0]|\n");
    atraso_rapido();
    printf("----------------------------\n");
    atraso_rapido();
    printf("\nEscolhas nao correspondentes com as opcoes possiveis serao negadas!!\n");
}

int menu(){
    int opcao = 10;
    banner_game();
    imprimir_niveis();
    while(opcao > 5){  //2
        scanf(" %d", &opcao);
    }
    return opcao;
}

void main(){
    setlocale(LC_ALL, "Portuguese");

    //Armazena as jogadas
    char sudoku_game[9][9];

    //Sudoku Solucionado
    char sudoku_resposta[9][9];

    //Responsável pela pontuação
    int acresc_pontos = 2;
    int decresc_pontos = 4;
    int pontuacao = 0;
    int bonus = 0;

    //Responsável por marcar o tempo de inicio
    time_t segundos;

    //Game play
    int linha = 0;
    int coluna = 0;
    char numero;
    int status_game = 1;  // 1 = Game Continua  0 = Jogo abortado   2 = Jogo completado
    int opcao = 0;

    //Carrega o sudoku selecionado
    while(1==1){
        opcao = menu();
        if(opcao <= 0) break;
        carregar_sudoku(sudoku_game, sudoku_resposta, opcao);
        time(&segundos);  //Marca a hora atual em segundos

        //Looping principal do jogo  o looping pode ser interrompido digitando 0, nas coordenadas linha e coluna e 0 no número a ser inserido
        while(status_game == 1){
            imprimir_jogo(sudoku_game);
            imprimir_tempo(segundos);
            imprimir_pontuacao(pontuacao);
            realizar_jogada(&linha, &coluna, &numero);

            if(numero == '0' && linha == 0 && coluna == 0){
                printf("\nVoce desistiu de continuar\n");
                delay(2);
                break;
            }

            int jogada_validada = validar_jogada(sudoku_game, linha, coluna);
            if(jogada_validada != 1){
                continue;
            }

            int acerto_validado = validar_acerto(sudoku_resposta, linha, coluna, numero);
            if(acerto_validado == 1){
                sudoku_game[linha-1][coluna-1] = numero;
                acrescimo_pontos(&pontuacao, acresc_pontos);
            }else{
                decrescimo_pontos(&pontuacao, decresc_pontos);
                continue;
            }

            status_game = checar_sudoku(sudoku_game);
        }

        if(status_game == 2){
            msg_sudoku_resolvido();
            bonus = calc_pontuacao_por_tempo(segundos);
            pontuacao += bonus;
            imprimir_bonus_obtido(bonus);
            imprimir_pontuacao(pontuacao);
            imprimir_tempo(segundos);
            delay(5);
        }



        reiniciar_marcadores(&pontuacao, &status_game);
        //time(&segundos);

    }

    printf("\nVoce saiu do jogo!\n");
    delay(2);

}

//8 45 96 1 91   74     3    7  4 8  6  3   9  4  9 3  2    9     76   58 9 28 71 3
