#include <stdio.h>
#include <math.h>
//Rui Emanuel Lima Vieira nUSP 11810182
//Lia Isikawa Tricoli nUSP 4758701


//Diagonais
//Digite ganso repetido 
//Vitória dos gansos
int temdiagonal(int i, int j){ //Verifica se a casa atual permite movimentos diagonais
	if (i == 0 || i == 2 || i == 4 || i == 6){ 
		if (j % 2 == 0){ //Em casas de linha par (começando a partir de zero), colunas pares permitem movimento diagonal
			return 1; //Permite movimento diagonal
		}
		return -1; //Não permite movimento diagonal
	}
	else{ 
		if (j % 2 != 0){ //Em casas de linha ímpar, colunas ímpares permitem movimento diagonal 
			return 1; //Permite movimento diagonal
		}
		return -1; //Não permite movimento diagonal
	}
}

void imprimir(char tab[7][7]){ //Imprime o tabuleiro de uma forma agradável ao usuário
	int i, j;
	for (i= 0; i < 7; i++){ //Loop para cada linha
		printf("(%d)  ", i+1); //Imprime a linha atual
		for (j = 0; j < 7; j++){ 
				printf("%c", tab[i][j]);
				if (j != 6 && tab[i][j] != ' ' && tab[i][j+1] != ' '){
					printf("--");
				}
				else{
					printf("  ");
				}
			}
		if (i == 1 || i == 5){ 
			printf("\n           | /|\\ |"); 
		}
		if (i == 0 || i == 4){ 
			printf("\n           | \\|/ |"); 
		}
		if (i == 2){
			printf("\n     | \\|/ | \\|/ | \\|/ | ");
		}
    if (i == 3) {
      printf("\n     | /|\\ | /|\\ | /|\\ | \n");
    }
		else{ 
			printf("\n");
		}
		}
	printf("    (1)(2)(3)(4)(5)(6)(7)\n\n"); //Imprime as colunas
}

int casaehvalida(char casa){ //Verifica se a casa do movimento selecionado está livre e faz parte do tabuleiro
	if (casa == 'o'){ 
		return 1;
	}
	return -1;
}

int casa_adjacente (int i, int j, int x, int y) { //verfica se as coordenadas do movimento são adjacentes a casa atual do personagem, i e j são as coordenadas do movimento, e x e y são as coordenadas atuais do personagem
    
		if (temdiagonal(x, y) == 1){ 
			if ((i == x + 1 || i == x || i == x-1) && (j == y + 1  || j == y -1 || j == y)){ //Caso a casa do personagem tenha diagonal, se as coordenadas colocadas pelo usuário forem antecessoras ou sucessoras da coordenada do personagem, ela será adjacente
				return 1; //Casa é adjacente
			}
			return -1; //Casa não é adjacente
		}
		else{
			if((i == x + 1 && j == y) || (i == x -1 && j == y) || (i == x && j == y - 1) || (i == x && j == y + 1)){ //Se a casa do personagem não tiver diagonal, haverá apenas 4 casos de casas adjacentes:A casa pode estar abaixo, na qual a coordenada da linha será +1 e a da coluna será igual/A casa pode estar acima, na qual a coordenada da linha será -1 e a da coluna será igual/ A casa pode estar à esquerda, que no caso a coordenada da linha seria igual e a coordenada da coluna será -1/A casa pode estar à direita, na qual a coordenada da linha será igual e a coordenada da coluna será +1
				return 1; //Casa é adjacente
			}
			return -1; //Casa não é adjacente
		}
  }


int procurarletra(char letra, int *a, int *b, char m[7][7]){ //Verifica se a letra digitada é um personagem e armazena as posições dele
	int i, j; 
	if (letra == ' ' || letra == 'o'){ //Não é um personagem
		return -1;
	}
	for (i = 0; i < 7; i++){ 
		for (j = 0; j < 7; j++){
			if (m[i][j] == letra) { //Verifica se existe a letra em todas as casas do tabuleiro
				*a = i; //Armazena a linha
				*b = j; //Armazena a coluna
				return 1;
			}
		}
}
	return -1; //Se tiver chegado até aqui, não pertence ao tabuleiro
}

int entrecasas(int i, int j, int x, int y, char m[7][7], int *a, int *b){ //i e j são as coordenadas do movimento da raposa, x e y são as coordenadas atuais da raposa e a e b são as coordenadas do ganso entre a raposa e a casa do movimento (se houver)
*a = (i + x)/2;
*b = (j + y)/2; 
//As variáveis acima fazem a conta do ponto médio entre a casa atual da raposa e a casa para a qual ela deve se mover, calculando assim as coordenadas da casa que ela realiza o movimento de "comer" o ganso
if (casa_adjacente(i, j, x, y) == 1){ //Se o movimento for adjacente, não precisa verificar se dá pra comer, porque é um movimento normal
	return 0;
}
if (i*y + *a*j + *b*x - (*a*y) - (*b*i) -(x*j) != 0) { //Se os 3 pontos forem não colineares, não é possível que a raposa elimine um ganso.
  return 0;
}
if (m[*a][*b] == 'o' || m[*a][*b] == ' '){ 
	return -1; //A entrecasa não é um ganso
}
if (casa_adjacente (x, y, *a, *b) == -1){ //O ganso digitado não está adjacente da raposa
	return -1;
}
return 1; //Dá pra comer um ganso
}

int tem_movimentovalido(char m[7][7], int x, int y){ //Falta considerar diagonais
	int i, j;
	for (i = 0; i < 7; i++){ 
		for (j = 0; j < 7; j++){ //Analisa todas as casas adjacentes
		if(casa_adjacente(i, j, x, y) == 1)
			if (casaehvalida(m[i][j]) == 1){ //Verifica se a casa adjacente está livre
				return 1;
				}
			}
		}
	return -1; //Se a função tiver passado pelos loops e não tiver retornado, é porque não há casa válida
}

int movimentoextra(char m[7][7], int x, int y, int e){ // x e y são as coordenadas atuais da raposa
	int i, j, a, b; 
	if (e != 1){
		return -1;
	}
	for (i = 0; i < 7; i++){ 
		for(j = 0; j < 7; j++)
			if(casa_adjacente(i, j, x, y) == 1){
				if (m[i][j] != 'o' && m[i][j] 	!= ' ' && m[i][j] != 'Z'){
					if (casaehvalida(m[i + abs(x - i)][j + abs(y - j)]) == 1 || casaehvalida(m[i + abs(x - i)][j - abs(y - j)]) == 1 || casaehvalida(m[i - abs(x - i)][j + abs(y - j)]) == 1 || casaehvalida(m[i - abs(x - i)][j - abs(y - j)]) == 1){
						return 1;				
					} 
			}
	}
	}
	return -1;
}

int tem_movimentovalido_raposa(char m[7][7], int x, int y){ //Falta considerar diagonais
	int i, j, a, b;
	if (tem_movimentovalido (m, x, y) == 1){ 
		return 1;
	}
	else {
    for (i = -1; i <= 2; i++) { 
      for (j = -2; j <= 2; j++) {
        if (entrecasas (i, j, x, y, m, &a, &b) != 1) {
          return -1;
        }
      }
    }
  return 1;
 //Se a função tiver passado pelos loops e não tiver retornado, é porque não há casa válida
}
} 

int main(void) {
	int i, j, a, b, c, d, g, e;
	g = 0; //g é o número de gansos que já foram comidos
  char ganso;
  char m[7][7] = {{"  ooo  "}, {"  ooo  "}, {"AooZooK"}, {"BoooooJ"}, {"CDEFGHI"}, {"  LMN  "}, {"  OPQ  "}}; //Configuração Inicial
	imprimir(m);	
	  while(g < 13){ //Pois, como há 17 gansos, e precisam sobrar 4 ou menos para a raposa ganhar, 
			while(1){
				do {//Jogada da raposa
	      	printf("É a vez da raposa, digite as coordenadas da casa para qual deseja se movimentar (ou digite 0 0 caso não queira mover-se novamente): ");
	        scanf("%d %d", &i, &j);
					procurarletra('Z', &a, &b, m);
					if (i == 0 && j == 0 && e == 1){ 
						break;
					}
					e = entrecasas(i-1, j-1, a, b, m, &c, &d);
	    } while (casaehvalida(m[i-1][j-1]) == -1 || (casa_adjacente(i-1, j-1, a, b) == -1 && e < 0)); //Caso a casa digitada não esteja livre ou não é adjacente à raposa
        if (i != 0 && j != 0){
				m[i-1][j-1] = 'Z'; //Movimenta a raposa
        m[a][b] = 'o'; //Limpa a a casa que ela estava
				if (e == 1){
					m[c][d] = 'o';
					g++;
				}
				}
			system("clear");
	    imprimir(m);
			printf("Gansos comidos: %d \n\n", g);
			if (movimentoextra(m, i-1, j-1, e) == 1){
					continue;
					}
			else{
				break;
			}
			}
      if (g >= 13){ 
				printf("\nVitória da raposa!");
				break;
			}
			do {
            printf("Digite o ganso que você deseja movimentar: ");
            scanf("%c", &ganso);
	    } while (procurarletra(ganso, &a, &b, m) == -1 || tem_movimentovalido(m, a, b) == -1); //Caso o ganso digitado não esteja no tabuleiro ou o movimento não seja válido
	    do {
            printf("Agora digite as coordenadas da casa para qual deseja se movimentar: ");
            scanf("%d %d", &i, &j);
						procurarletra(ganso, &a, &b, m);
        } while (casaehvalida(m[i-1][j-1]) == -1 || casa_adjacente(i-1, j-1, a, b) == -1); //Caso a casa digitada não esteja livre ou não seja adjacente ao ganso
        system ("clear");
				m[a][b] = 'o';
				m[i-1][j-1] = ganso;
        imprimir(m);
				printf("Gansos comidos: %d \n\n", g);
		procurarletra('Z', &a, &b, m);
		if (tem_movimentovalido_raposa(m, a, b) == -1){ 
			printf("Vitória dos gansos!");
			break;
		}
		}
  return 0;
}