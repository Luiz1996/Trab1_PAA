//LUIZ FLÁVIO PEREORA   RA91706
//MARCOS VINICIUS PERES RA94594
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX 10

//menu inicial
char showmenu(char opcao){
	for(int i = 0; i < 120; i++) printf("=");
	printf("\t\t\t\t\t\t     Trabalho 1 PAA:\n\n[1] Carregar Vetor.\n[2] Achar K-esimo Termo em T(n) = O(Log n).\n[3] Achar K-esimo Termo em T(n) = O(n). \n[4] Ordenar em T = O(n).\n[5] Imprime Vetor.\n[6] Reinicia Vetor Zerado.\n\n\n[S/s/0]Sair\n");
	for(int i = 0; i < 120; i++) printf("=");
	printf("Opcao: ");
	fflush(stdin);
	scanf("%c", &opcao);
	
	return opcao;
}

//funcao que carrega o vetor com valores > 0
void carregaV(int V[]){
	int novo_valor = 1;//valor simbolico para entrar no while
	while(novo_valor > 0){
		//cai nesse caso quando não há posicao do vetor com valor zero, deste modo ele entende que todo vetor está cheio!
		if(V[TAM_MAX -1] != 0){
			system("cls");
			printf("\t\t\t\t\tA insercao de dados FALHOU!!!\n\n\t\t\t\t\t    MOTIVO: Vetor Cheio!\n\n \t\t\t\t\t\t E R R O R\n");
			return;	
		}
		printf("======================================================== CARREGA =======================================================");
	
		//receber dado do usuario
		printf("Para SAIR insira um valor < 1.\nInsira um valor (>0): ");
		scanf("%d", &novo_valor);
		system("cls");
		
		//se inserir valor menor ou igual a zero apresenta erro e volta ao menu inicial
		if(novo_valor <= 0){
			printf("Finalizado a insercao de dados!\n");
			return;
		}
		
		/*percorre vetor até achar uma posicao com valor zero, quando achar ele insere. Zero é atruido a todas as posicoes na declaracao do vetor, portanto, quando ele 
		encontra esse valor ele sabe que ali está disponivel para insercoes de dados*/
		for(int i = 0; i < TAM_MAX; i++){
			if(V[i] == 0){
				V[i] = novo_valor;
				printf("O valor %d foi inserido com sucesso!\n", novo_valor);
				if(i == TAM_MAX - 1){
					printf("\nVetor totalmente carregado!\n");
					return;
				}
				break;
			}
		}
	}
}

//funcao que imprime todos valores do vetor original V[]
void imprimeV(int *V){
	printf("======================================================== IMPRIME =======================================================");
	for(int i = 0; i < TAM_MAX; i++)
		printf("V[%d] = %d.\n", i, V[i]);
}

//funcao que acha K-esimo em T(n) = O(n), LINEAR
void achaK_esimo(int V[]){
	//verifica vetor decrescente logo nas primeira posicoes(tempo constante, não altera significativamente o tempo de execucao da funcao achaK_esimo, permanece linear)
	if(V[1] < V[0]){
		printf("Vetor ja inicia descrescente, VETOR INVALIDO!\n");
		return;	
	}
	
	/*percorre vetor original em busca K-esimo, se o elemento V[i + 1] for menor que V[i] então indica que comecou a descrescer, portanto, o valor de V[i] possui o maior valor de V[] e então é o K-esimo
	POREM, esse metodo NÃO É MUITO CONFIAVEL dependendo da forma em que os dados sao distribuidos no vetor, a busca binaria é mais precisa e rápida...*/
	for(int i = 0; i < TAM_MAX; i++){
		//achou valor correto! :)
		if(V[i + 1] < V[i] && i < TAM_MAX-1){
			printf("O K-esimo termo eh: %d.\n\nE possui indice: %d no vetor.\n", V[i], i);
			return;
		}	
	}
	
	//se a execucao da funcao chegar até esse ponto, então o vetor é crescente ou invalido!
	printf("Vetor totalmente ordenado crescente e/ou VETOR INVALIDO!\n");
}


//funcao que acha K-esimo em T(n) = O(Log n), BUSCA BINÁRIA
void achaK_esimo(int V[], int primeiro, int ultimo){
	//verifica vetor decrescente logo nas primeira posicoes(tempo constante, não altera significativamente o tempo de execucao da funcao achaK_esimo, permanece logaritmica)
	if(V[1] < V[0]){
		printf("Vetor ja inicia descrescente, VETOR INVALIDO!\n");
		return;	
	}
	int meio = (primeiro + ultimo) / 2;
	
	if(ultimo >= primeiro){
		//esse metodo visa encontrar o maior valor, portanto, se o do meio não for o K-esimo então os dois ao lado dele não podem ser iguais ao V[meio], se forem é um vetor invalido pois terá elementos repetidos consecutivamente
		if(V[meio - 1] == V[meio] && V[meio + 1] == V[meio]){
			printf("Vetor invalido!\n\nFoi encontrado trecho com elementos repetidos consecutivamente.\n");
			return;
		}
		
		//se os dois valores em torno de V[meio] forem menores que ele mesmo então tem grandes chances de ser o K-esimo
		if(V[meio - 1] < V[meio] && V[meio + 1] < V[meio]){
			
			//porém, se o meio for igual a ultima posicao do vetor, isso indica que o vetor é invalido!
			if(meio == TAM_MAX - 1){
				printf("V[meio] eh a ultima posicao, VETOR INVALIDO!\n");
				return;
			}
			
			//achou valor correto! :)
			printf("O K-esimo termo eh: %d.\n\nE possui indice: %d no vetor.\n", V[meio], meio);
			return;		
		}else if(V[meio + 1] > V[meio]){ //se valor a direito de V[meio] for maior,então considera a segunda metade do vetor
			achaK_esimo(V, meio + 1, ultimo);
		}else if(V[meio - 1] > V[meio]){//se valor a esquerda de V[meio] for maior,então considera a primeira metade do vetor
			achaK_esimo(V, primeiro, meio - 1);
		}else{ //verificacao trivial para casos em que o vetor V[] tenha todos valores iguais ,ou então, alguma outra irregularidade
			printf("Vetor Invalido!\n\nK-esimo nao encontrado...\n");
		}	
	}	
}

//funcao para zerar todos valores do vetor original V[]
void reiniciaVetor(int V[]){
	for(int i = 0; i < TAM_MAX; i++)
		V[i] = 0;
	
	printf("Vetor reiniciado com sucesso!\n");
}

//metodo de ordenacao visto em aula com T(n) = O(n)
void countingSort(int V[]){
	int maior_valor = 0;
	
	//declaracao de vetor que tera o resultado da ordenacao, porem, seus valores serão transferidos novamente para o vetor original V[] ao final deste funcao
	int Result[TAM_MAX + 1] = {};
	
	//achar maior valor do vetor original V[]
	for(int i = 0; i < TAM_MAX; i++)
		if(V[i] > maior_valor)
			maior_valor = V[i];
		
	//declara vetor auxiliar
	int Aux[maior_valor + 1] = {};
	
	//aux recebe o numero de elementos iguais a i
	for(int i = 0; i < TAM_MAX; i++)
		Aux[V[i]] = Aux[V[i]] + 1;
	
	//aux recebe numero de elementos menores que os iguais a i
	for(int  i = 1; i <= maior_valor; i++)
		Aux[i] = Aux[i] + Aux[i - 1];
	
	//montando vetor Result[] com os dados corretamente ordenados
	for(int i = TAM_MAX; i >= 0; i--){
		Result[Aux[V[i]]] = V[i];
		Aux[V[i]] = Aux[V[i]] - 1;
	}

	//transferindo valores de Result[] para o vetor original V[]	
	for(int  i = 0; i < TAM_MAX; i++){
		V[i] = Result[i + 1];
	}
	printf("Vetor ordenado com sucesso!\n");
}

//programa principal
int main(void){
	int V[TAM_MAX] = {};
	
	char opcao = showmenu(opcao); 
	while(opcao != 's' && opcao != 'S' && opcao != '0'){
		system("cls");
		switch (opcao){
			case '1':
				//funcao para atribuir valores as posicoes do vetor original V[]
				carregaV(V);
				break;
			case '2':  
				if(V[TAM_MAX -1] != 0)
					//funcao que acha o K-esimo em T(n) = O(Log n)
					achaK_esimo(V, 0, TAM_MAX - 1);
				else
					printf("Vetor nao foi totalmente preenchido!\n");
				break;
			case '3':
				if(V[TAM_MAX - 1] != 0)
					//funcao que acha o K-esimo em T(n) = O(n)
					achaK_esimo(V);
				else
					printf("Vetor nao foi totalmente preenchido!\n");
				break;
			case '4':
				if(V[TAM_MAX - 1] != 0)
					//metodo de ordenacao em T(n) = O(n)
					countingSort(V);
				else
					printf("Vetor nao foi totalmente preenchido!\n");
				break;
			case '5':
				//imprimir valores do vetor original V[]
				imprimeV(V);
				break;
			case '6':
				//atribui o valor zero a todas as posicoes do vetor otiginal V[]
				reiniciaVetor(V);
				break;
			default :
				printf("Opcao invalida!\n");
				break;
		}
		opcao = showmenu(opcao);
	}
}
