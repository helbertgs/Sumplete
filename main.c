// Adding Color to Your Programs: https://www.theurbanpenguin.com/4184-2/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Definitions
#define WHITE "\033[0;37m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"

// Estrutura de dados com todas as informações necessárias para o funcionamento
// do jogo.
typedef struct Sumplete Sumplete;
struct Sumplete {
  int **board;
  int *cols;
  bool isFinished;
  char *level;
  char *playername;
  int *rows;
  int size;
  int **states;
};

// Inicializa as informações do jogo.
void initialize(Sumplete *sumplete) {
  sumplete->board = (int **)malloc(sumplete->size * sizeof(int *));
  sumplete->states = (int **)malloc(sumplete->size * sizeof(int *));
  sumplete->cols = (int *)malloc(sumplete->size * sizeof(int *));
  sumplete->rows = (int *)malloc(sumplete->size * sizeof(int *));
  sumplete->isFinished = false;

  for (int row = 0; row < sumplete->size; row++) {
    sumplete->board[row] = (int *)malloc(sumplete->size * sizeof(int *));
    sumplete->states[row] = (int *)malloc(sumplete->size * sizeof(int *));
  }
}

// Altera a cor do elemento, quando o mesmo for exibido no console. A cor sera
// baseada no estado do elemento.
void changeCharacterColor(int value, int state) {
  switch (state) {
  case 1:
    printf(RED);
    printf("%d ", value);
    break;
  case 2:
    printf(GREEN);
    printf("%d ", value);
    break;
  default:
    printf("%d ", value);
  }

  printf(WHITE);
}

// Função responsável por exibir o board.
void printBoard(Sumplete *sumplete) {
  printf("Dificuldade: %s\n", sumplete->level);
  for (int row = 0; row < sumplete->size; row++) {
    for (int col = 0; col < sumplete->size; col++) {
      changeCharacterColor(sumplete->board[row][col],
                           sumplete->states[row][col]);
    }

    printf("| %d\n", sumplete->rows[row]);
  }

  for (int i = 0; i < 2 * sumplete->size + 3; i++) {
    printf("-");
  }
  printf("\n");

  for (int col = 0; col < sumplete->size; col++) {
    printf("%d ", sumplete->cols[col]);
  }

  printf("\n\n");
}

// Altera o estado de um indice da matriz para: "estado desconhecido".
void markAsUnknown(Sumplete *sumplete, int row, int col) {
  sumplete->states[row][col] = 0;
}

// Altera o estado de um indice da matriz para: "Numero removido".
void markAsRemoved(Sumplete *sumplete, int row, int col) {
  sumplete->states[row][col] = 1;
}

// Altera o estado de um indice da matriz para: "Numero mantido".
void markAsRetain(Sumplete *sumplete, int row, int col) {
  sumplete->states[row][col] = 2;
}

// Le os dados de um arquivo e carrega os mesmos em uma string.
char* readAndLoadFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fileLength = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* content = (char*)malloc(fileLength + 1);
    if (content == NULL) {
        perror("Erro ao alocar memória");
        fclose(file);
        return NULL;
    }

    size_t bytesRead = fread(content, 1, fileLength, file);
    if (bytesRead != (size_t)fileLength) {
        perror("Erro ao ler o arquivo");
        free(content);
        fclose(file);
        return NULL;
    }

    content[fileLength] = '\0';

    fclose(file);
    return content;
}

// Salva os dados de uma string em um arquivo.
void saveToFile(const char* filename, const char* content) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para escrita");
        return;
    }

    if (fprintf(file, "%s", content) < 0) {
        perror("Erro ao escrever no arquivo");
    }

    fclose(file);
}

// Seleciona o nome do jogador
void selectPlayerName(Sumplete *sumplete) {
  bool execute = true;

  while (execute) {
    char playername[20];
    printf("Digite o nome do jogador 1: ");
    scanf("%s", playername);

    if (playername != "") {
      sumplete->playername = playername;
      execute = false;
    }
  }
}

// Solcita ao jogador o tamanho do tabuleiro.
void selectBoardSize(Sumplete *sumplete) {
  bool execute = true;

  while (execute) {
    int size;
    printf("Digite o tamanho do tabuleiro (3 a 9): ");
    scanf("%d", &size);

    int *aux = &size;

    if (*aux > 2 && *aux < 10) {
      sumplete->size = size;
      execute = false;
    }
  }
}

// Solicita ao jogador o nivel de dificuldade do tabuleiro apenas se a dimensão
// do tabuleiro for maior que 4.
void selectLevel(Sumplete *sumplete) {
  if (sumplete->size < 5) {
    sumplete->level = "F";
    return;
  }

  bool execute = true;

  while (execute) {
    char level;
    printf("Digite o nivel de dificuldade:");
    printf("\nF - Facil\nM - Medio\nD - Dificil\nDificuldade: ");
    scanf(" %c", &level);

    char *aux = &level;

    if (*aux == 'D' || *aux == 'F' || *aux == 'M') {
      sumplete->level = &level;
      execute = false;
    }
  }
}

// Inicia um novo jogo.
void startNewGame(Sumplete *sumplete) {
  selectPlayerName(sumplete);
  selectBoardSize(sumplete);
  selectLevel(sumplete);
  initialize(sumplete);
  printBoard(sumplete);
}

	  // Exibe o ranking.
void showRanking(Sumplete *sumplete) {}

// Encerra o jogo.
void exitGame(Sumplete *sumplete) { sumplete->isFinished = true; }
	  
// Carrega um jogo salvo.
void loadGame(Sumplete *sumplete) {}

// Continua com o jogo atual.
void continueGame(Sumplete *sumplete) {
  char* command;
  printf("%s, digite o comando: ", sumplete->playername);
  scanf("%s", command);

	switch (command) {
		case "sair":
			exitGame(sumplete);
			break;
		default:
		continueGame(sumplete);
	}
}

// Menu principal do jogo.
void menu(Sumplete *sumplete) {
  printf("Bem vindo ao jogo SUMPLETE\n\n0. Sair do jogo\n1. Começar um novo "
         "jogo\n2. Continuar um jogo salvo em arquivo\n3. Continuar o jogo "
         "atual\n4. Exibir o ranking\nDurante o jogo digite \"voltar\" para "
         "retornar ao menu.\n\nEscolha a opção: ");

  int option;
  scanf("%d", &option);

  switch (option) {
  case 0:
    exitGame(sumplete);
    break;
  case 1:
    startNewGame(sumplete);
    break;
  case 2:
    loadGame(sumplete);
    break;
  case 3:
    continueGame(sumplete);
    break;
  case 4:
    showRanking(sumplete);
    break;
  default:
    printf("Comando desconhecido!");
  }
}

int main(void) {
  Sumplete sumplete;
  menu(&sumplete);

  while(!sumplete.isFinished) {
	continueGame(&sumplete);
  }
	
  return 0;
}
