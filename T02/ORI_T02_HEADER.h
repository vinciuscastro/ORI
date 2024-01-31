/* ==========================================================================
 * Universidade Federal de São Carlos - Campus Sorocaba
 * Disciplina: Organização de Recuperação da Informação
 * Prof. Tiago A. Almeida
 *
 * Trabalho 02 - Árvore-B
 *
 * ========================================================================== *
 *                             <<< NÃO ALTERAR >>>
 * ========================================================================== */

#ifndef ORI_T02_HEADER
#define ORI_T02_HEADER

/* Bibliotecas */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

typedef enum {false, true} bool;

/* Tamanho dos campos dos registros */
/* Campos de tamanho fixo */
#define TAM_DATE 9
#define TAM_DATETIME 13
#define TAM_INT_NUMBER 5
#define TAM_FLOAT_NUMBER 14
#define TAM_ID_CORREDOR 12
#define TAM_ID_VEICULO 8
#define TAM_ID_PISTA 9
#define QTD_MAX_VEICULO 3

/* Campos multivalorados de tamanho fixo*/
#define TAM_ID_CORREDORES (TAM_ID_CORREDOR * 6 - 5)
#define TAM_ID_VEICULOS (TAM_ID_VEICULO * 6 - 5)

/* Campos de tamanho variável (tamanho máximo) */
#define TAM_MAX_NOME_CORREDOR 45
#define TAM_MAX_APELIDO 41
#define TAM_MAX_MARCA 24
#define TAM_MAX_MODELO 15
#define TAM_MAX_PODER 52
#define TAM_MAX_NOME_PISTA 34

#define MAX_REGISTROS 1000
#define TAM_REGISTRO_CORREDOR (TAM_ID_CORREDOR+TAM_MAX_NOME_CORREDOR+TAM_MAX_APELIDO+TAM_DATETIME+TAM_FLOAT_NUMBER+QTD_MAX_VEICULO*TAM_MAX_MODELO)
#define TAM_REGISTRO_VEICULO (TAM_ID_VEICULO+TAM_MAX_MARCA+TAM_MAX_MODELO+TAM_MAX_PODER+TAM_INT_NUMBER*3+TAM_FLOAT_NUMBER+1)
#define TAM_REGISTRO_PISTA (TAM_ID_PISTA+TAM_MAX_NOME_PISTA+TAM_INT_NUMBER*3+TAM_FLOAT_NUMBER+1)
#define TAM_REGISTRO_CORRIDA (TAM_ID_PISTA+TAM_DATETIME+TAM_ID_CORREDORES+TAM_ID_VEICULOS+1)
#define TAM_ARQUIVO_CORREDORES (TAM_REGISTRO_CORREDOR * MAX_REGISTROS + 1)
#define TAM_ARQUIVO_VEICULOS (TAM_REGISTRO_VEICULO * MAX_REGISTROS + 1)
#define TAM_ARQUIVO_PISTAS (TAM_REGISTRO_PISTA * MAX_REGISTROS + 1)
#define TAM_ARQUIVO_CORRIDAS (TAM_REGISTRO_CORRIDA * MAX_REGISTROS + 1)

#define TAM_RRN_REGISTRO 4
#define TAM_CHAVE_CORREDORES_IDX ((TAM_ID_CORREDOR - 1) + TAM_RRN_REGISTRO)
#define TAM_CHAVE_VEICULOS_IDX ((TAM_ID_VEICULO - 1) + TAM_RRN_REGISTRO)
#define TAM_CHAVE_PISTAS_IDX ((TAM_ID_PISTA - 1) + TAM_RRN_REGISTRO)
#define TAM_CHAVE_CORRIDAS_IDX ((TAM_ID_PISTA - 1) + (TAM_DATETIME - 1) + TAM_RRN_REGISTRO)
#define TAM_CHAVE_NOME_PISTA_IDX ((TAM_MAX_NOME_PISTA - 1) + (TAM_ID_PISTA - 1))
#define TAM_CHAVE_PRECO_VEICULO_IDX ((TAM_FLOAT_NUMBER - 1) + (TAM_ID_VEICULO - 1))
#define TAM_CHAVE_CORREDOR_VEICULO_SECUNDARIO_IDX (TAM_MAX_MODELO - 1)
#define TAM_CHAVE_CORREDOR_VEICULO_PRIMARIO_IDX (TAM_ID_CORREDOR - 1)

#define TAM_ARQUIVO_CORREDORES_IDX (1000 * MAX_REGISTROS + 1)
#define TAM_ARQUIVO_VEICULOS_IDX (1000 * MAX_REGISTROS + 1)
#define TAM_ARQUIVO_PIPSTAS_IDX (1000 * MAX_REGISTROS + 1)
#define TAM_ARQUIVO_CORRIDAS_IDX (1000 * MAX_REGISTROS + 1)
#define TAM_NOME_PISTA_IDX (1000 * MAX_REGISTROS + 1)
#define TAM_PRECO_VEICULO_IDX (1000 * MAX_REGISTROS + 1)
#define TAM_ARQUIVO_CORREDOR_VEICULO_SECUNDARIO_IDX (1000 * MAX_REGISTROS + 1)
#define TAM_ARQUIVO_CORREDOR_VEICULO_PRIMARIO_IDX (1000 * MAX_REGISTROS + 1)

/* Mensagens padrões */
#define SUCESSO                          "OK\n"
#define RRN_NOS                          "Nos percorridos:"
#define REGS_PERCORRIDOS                 "Registros percorridos:"
#define RRN_REGS_PRIMARIOS               "Registros primários percorridos:"
#define RRN_REGS_SECUNDARIOS             "Registros secundários percorridos:"
#define INDICE_CRIADO                    "Indice %s criado com sucesso!\n"
#define AVISO_NENHUM_REGISTRO_ENCONTRADO "AVISO: Nenhum registro encontrado\n"
#define ERRO_OPCAO_INVALIDA              "ERRO: Opcao invalida\n"
#define ERRO_MEMORIA_INSUFICIENTE        "ERRO: Memoria insuficiente\n"
#define ERRO_PK_REPETIDA                 "ERRO: Ja existe um registro com a chave %s\n"
#define ERRO_REGISTRO_NAO_ENCONTRADO     "ERRO: Registro nao encontrado\n"
#define ERRO_SALDO_NAO_SUFICIENTE        "ERRO: Saldo insuficiente\n"
#define ERRO_VEICULO_REPETIDO            "ERRO: O corredor %s ja possui o veiculo %s\n"
#define ERRO_CORREDOR_VEICULO            "ERRO: O corredor %s nao possui veiculo %s\n"
#define ERRO_VALOR_INVALIDO              "ERRO: Valor invalido\n"
#define ERRO_ARQUIVO_VAZIO               "ERRO: Arquivo vazio\n"
#define ERRO_NAO_IMPLEMENTADO            "ERRO: Funcao %s nao implementada\n"

#define TX_FIXA 100

/* Registro de Corredor */
typedef struct {
    char id_corredor[TAM_ID_CORREDOR];
    char nome[TAM_MAX_NOME_CORREDOR];
    char apelido[TAM_MAX_APELIDO];
    char cadastro[TAM_DATETIME];
    double saldo;
    char veiculos[QTD_MAX_VEICULO][TAM_MAX_MODELO];
} Corredor;
 
/* Registro de Veiculo */
typedef struct {
    char id_veiculo[TAM_ID_VEICULO];
    char marca[TAM_MAX_MARCA];
    char modelo[TAM_MAX_MODELO];
    char poder[TAM_MAX_PODER];
    int velocidade;
    int aceleracao;
    int peso;
    double preco;
} Veiculo;

/* Registro de Pista */
typedef struct {
    char id_pista[TAM_ID_PISTA];
    char nome[TAM_MAX_NOME_PISTA];
    int dificuldade;
    int distancia;
    int recorde;
    double taxa_inscricao;
} Pista;

/* Registro de Corrida */
typedef struct {
    char id_pista[TAM_ID_PISTA];
    char ocorrencia[TAM_DATETIME];
    char id_corredores[TAM_ID_CORREDORES];
    char id_veiculos[TAM_ID_VEICULOS];
} Corrida;

/*----- Registros dos índices -----*/
 
/* Struct para índice de lista invertida */
typedef struct {
    char* chave;
    int proximo_indice;
} inverted_list_node;

/* Struct para um nó de Árvore-B */
typedef struct {
    int this_rrn;
    int qtd_chaves;
    char **chaves; // ponteiro para o começo do campo de chaves no arquivo de índice respectivo
    bool folha;
    int *filhos; // vetor de int para o RRN dos nós filhos (DEVE SER DESALOCADO APÓS O USO!!!)
} btree_node;
 
/* Variáveis globais */
/* Arquivos de dados */
char ARQUIVO_CORREDORES[TAM_ARQUIVO_CORREDORES];
char ARQUIVO_VEICULOS[TAM_ARQUIVO_VEICULOS];
char ARQUIVO_PISTAS[TAM_ARQUIVO_PISTAS];
char ARQUIVO_CORRIDAS[TAM_ARQUIVO_CORRIDAS];

/* Ordem das Árvores-B */
int btree_order = 3; // valor padrão

/* Índices */
/* Struct para os parâmetros de uma lista invertida */
typedef struct {
    // Ponteiro para o arquivo de índice secundário
    char *arquivo_secundario;

    // Ponteiro para o arquivo de índice primário
    char *arquivo_primario;

    // Quantidade de registros de índice secundário
    unsigned qtd_registros_secundario;

    // Quantidade de registros de índice primário
    unsigned qtd_registros_primario;

    // Tamanho de uma chave secundária nesse índice
    unsigned tam_chave_secundaria;

    // Tamanho de uma chave primária nesse índice
    unsigned tam_chave_primaria;

    // Função utilizada para comparar as chaves do índice secundário.
    // Igual às funções de comparação do bsearch e qsort.
    int (*compar)(const void *key, const void *elem);
} inverted_list;

/* Struct para os parâmetros de uma Árvore-B */
typedef struct {
    // RRN da raiz
    int rrn_raiz;

    // Ponteiro para o arquivo de índice
    char *arquivo;

    // Quantidade de nós no arquivo de índice
    unsigned qtd_nos;

    // Tamanho de uma chave nesse índice
    unsigned tam_chave;

    // Função utilizada para comparar as chaves do índice.
    // Igual às funções de comparação do bsearch e qsort.
    int (*compar)(const void *key, const void *elem);
} btree;

typedef struct {
    char chave_promovida[TAM_CHAVE_NOME_PISTA_IDX + 1]; // TAM_CHAVE_NOME_PISTA_IDX é a maior chave possível
    int filho_direito;
} promovido_aux;

/* Arquivos de índices */
char ARQUIVO_CORREDORES_IDX[TAM_ARQUIVO_CORREDORES_IDX];
char ARQUIVO_VEICULOS_IDX[TAM_ARQUIVO_VEICULOS_IDX];
char ARQUIVO_PISTAS_IDX[TAM_ARQUIVO_PIPSTAS_IDX];
char ARQUIVO_CORRIDAS_IDX[TAM_ARQUIVO_CORRIDAS_IDX];
char ARQUIVO_NOME_PISTA_IDX[TAM_NOME_PISTA_IDX];
char ARQUIVO_PRECO_VEICULO_IDX[TAM_PRECO_VEICULO_IDX];
char ARQUIVO_CORREDOR_VEICULO_SECUNDARIO_IDX[TAM_ARQUIVO_CORREDOR_VEICULO_SECUNDARIO_IDX];
char ARQUIVO_CORREDOR_VEICULO_PRIMARIO_IDX[TAM_ARQUIVO_CORREDOR_VEICULO_PRIMARIO_IDX];
 
/* Comparam a chave (key) com cada elemento do índice (elem) */
int order_corredores_idx(const void *key, const void *elem);
int order_veiculos_idx(const void *key, const void *elem);
int order_pistas_idx(const void *key, const void *elem);
int order_corridas_idx(const void *key, const void *elem);
int order_nome_pista_idx(const void *key, const void *elem);
int order_preco_veiculo_idx(const void *key, const void *elem);
int order_corredor_veiculo_idx(const void *key, const void *elem);
int qsort_string_modelo(const void *a, const void *b);

btree corredores_idx = {
    .rrn_raiz = -1,
    .arquivo = ARQUIVO_CORREDORES_IDX,
    .qtd_nos = 0,
    .tam_chave = TAM_CHAVE_CORREDORES_IDX,
    .compar = order_corredores_idx,
};

btree veiculos_idx = {
    .rrn_raiz = -1,
    .arquivo = ARQUIVO_VEICULOS_IDX,
    .qtd_nos = 0,
    .tam_chave = TAM_CHAVE_VEICULOS_IDX,
    .compar = order_veiculos_idx,
};

btree pistas_idx = {
    .rrn_raiz = -1,
    .arquivo = ARQUIVO_PISTAS_IDX,
    .qtd_nos = 0,
    .tam_chave = TAM_CHAVE_PISTAS_IDX,
    .compar = order_pistas_idx,
};

btree corridas_idx = {
    .rrn_raiz = -1,
    .arquivo = ARQUIVO_CORRIDAS_IDX,
    .qtd_nos = 0,
    .tam_chave = TAM_CHAVE_CORRIDAS_IDX,
    .compar = order_corridas_idx,
};

btree nome_pista_idx = {
    .rrn_raiz = -1,
    .arquivo = ARQUIVO_NOME_PISTA_IDX,
    .qtd_nos = 0,
    .tam_chave = TAM_CHAVE_NOME_PISTA_IDX,
    .compar = order_nome_pista_idx,
};

btree preco_veiculo_idx = {
    .rrn_raiz = -1,
    .arquivo = ARQUIVO_PRECO_VEICULO_IDX,
    .qtd_nos = 0,
    .tam_chave = TAM_CHAVE_PRECO_VEICULO_IDX,
    .compar = order_preco_veiculo_idx,
};

inverted_list corredor_veiculos_idx = {
    .arquivo_secundario = ARQUIVO_CORREDOR_VEICULO_SECUNDARIO_IDX,
    .arquivo_primario = ARQUIVO_CORREDOR_VEICULO_PRIMARIO_IDX,
    .qtd_registros_secundario = 0,
    .qtd_registros_primario = 0,
    .tam_chave_secundaria = TAM_CHAVE_CORREDOR_VEICULO_SECUNDARIO_IDX,
    .tam_chave_primaria = TAM_CHAVE_CORREDOR_VEICULO_PRIMARIO_IDX,
    .compar = order_corredor_veiculo_idx,
};
 
/* Contadores */
unsigned qtd_registros_corredores = 0;
unsigned qtd_registros_veiculos = 0;
unsigned qtd_registros_pistas = 0;
unsigned qtd_registros_corridas = 0;

/* Funções de geração determinística de números pseudo-aleatórios */
uint64_t prng_seed;
void prng_srand(uint64_t value);
uint64_t prng_rand();
void new_uuid(char buffer[37]);
 
/* Funções de manipulação de data */
time_t epoch;

#define YEAR0                   1900
#define EPOCH_YR                1970
#define SECS_DAY                (24L * 60L * 60L)
#define LEAPYEAR(year)          (!((year) % 4) && (((year) % 100) || !((year) % 400)))
#define YEARSIZE(year)          (LEAPYEAR(year) ? 366 : 365)

#define TIME_MAX                2147483647L

long _dstbias = 0;                  // Offset for Daylight Saving Time
long _timezone = 0;                 // Difference in seconds between GMT and local time

const int _ytab[2][12] = {
    {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

struct tm *gmtime_r(const time_t *timer, struct tm *tmbuf);
time_t mktime(struct tm *tmbuf);
bool set_time(char *date);
void tick_time();
void current_date(char buffer[TAM_DATE]);
void current_datetime(char buffer[TAM_DATETIME]);

/* Remove comentários (--) e caracteres whitespace do começo e fim de uma string */
void clear_input(char *str);

/* Cria o índice respectivo */
void criar_corredores_idx();
void criar_veiculos_idx();
void criar_pistas_idx();
void criar_corridas_idx();
void criar_nome_pista_idx();
void criar_preco_veiculo_idx();
void criar_corredor_veiculos_idx();

/* Exibe um registro com base no RRN */
bool exibir_corredor(int rrn);
bool exibir_veiculo(int rrn);
bool exibir_pista(int rrn);
bool exibir_corrida(int rrn);

/* Exibe um registro com base na chave de um btree_node */
bool exibir_btree_corredores(char *chave);
bool exibir_btree_veiculos(char *chave);
bool exibir_btree_pistas(char *chave);
bool exibir_btree_corridas(char *chave);
bool exibir_btree_nome_pista(char *chave);
bool exibir_btree_preco_veiculo(char *chave);
 
/* Recupera do arquivo o registro com o RRN informado
 * e retorna os dados nas structs */
Corredor recuperar_registro_corredor(int rrn);
Veiculo recuperar_registro_veiculo(int rrn);
Pista recuperar_registro_pista(int rrn);
Corrida recuperar_registro_corrida(int rrn);
 
/* Escreve em seu respectivo arquivo na posição informada (RRN) */
void escrever_registro_corredor(Corredor c, int rrn);
void escrever_registro_veiculo(Veiculo v, int rrn);
void escrever_registro_pista(Pista p, int rrn);
void escrever_registro_corrida(Corrida i, int rrn);

/* Funções principais */
void cadastrar_corredor_menu(char *id_corredor, char *nome, char *apelido);
void remover_corredor_menu(char *id_corredor);
void adicionar_saldo_menu(char *id_corredor, double valor);
void adicionar_saldo(char *id_corredor, double valor, bool flag);
void comprar_veiculo_menu(char *id_corredor, char *id_veiculo);
void cadastrar_veiculo_menu(char *marca, char *modelo, char *poder, int velocidade, int aceleracao, int peso, double preco);
void cadastrar_pista_menu(char *nome, int dificuldade, int distancia, int recorde);
void executar_corrida_menu(char *id_pista, char *ocorrencia, char *id_corredores, char *id_veiculos);

/* Busca */
void buscar_corredor_id_menu(char *id_corredor);
void buscar_pista_id_menu(char *id_pista);
void buscar_pista_nome_menu(char *nome_pista);

/* Listagem */
void listar_corredores_id_menu();
void listar_corredores_modelo_menu(char *modelo);
void listar_veiculos_compra_menu(char *id_corredor);
void listar_corridas_periodo_menu(char *data_inicio, char *data_fim);

/* Liberar espaço */
void liberar_espaco_menu();

/* Imprimir arquivos de dados */
void imprimir_arquivo_corredores_menu();
void imprimir_arquivo_veiculos_menu();
void imprimir_arquivo_pistas_menu();
void imprimir_arquivo_corridas_menu();

/* Imprimir índices primários */
void imprimir_corredores_idx_menu();
void imprimir_veiculos_idx_menu();
void imprimir_pistas_idx_menu();
void imprimir_corridas_idx_menu();

/* Imprimir índices secundários */
void imprimir_nome_pista_idx_menu();
void imprimir_preco_veiculo_idx_menu();
void imprimir_corredor_veiculos_secundario_idx_menu();
void imprimir_corredor_veiculos_primario_idx_menu();

/* Liberar memória e encerrar programa */
void liberar_memoria_menu();

/* Funções de manipulação de Lista Invertida */
void inverted_list_insert(char *chave_secundaria, char *chave_primaria, inverted_list *t);
bool inverted_list_secondary_search(int *result, bool exibir_caminho, char *chave_secundaria, inverted_list *t);
int inverted_list_primary_search(char result[][TAM_CHAVE_CORREDOR_VEICULO_PRIMARIO_IDX], bool exibir_caminho, int indice, int *indice_final, inverted_list *t);
bool inverted_list_binary_search(int* result, bool exibir_caminho, char *chave, inverted_list *t);

/* Funções de manipulação de Árvores-B */
void btree_insert(char *chave, btree *t);
promovido_aux btree_insert_aux(char *chave, int rrn, btree *t);
promovido_aux btree_divide(promovido_aux promo, btree_node *node, int i, btree *t);
void btree_delete(char *chave, btree *t);
bool btree_delete_aux(char *chave, int rrn, btree *t);
bool btree_borrow_or_merge(btree_node *node, int i, btree *t);
bool btree_search(char *result, bool exibir_caminho, char *chave, int rrn, btree *t);
bool btree_binary_search(int *result, bool exibir_caminho, char* chave, btree_node* node, btree* t);
bool btree_print_in_order(char *chave_inicio, char *chave_fim, bool (*exibir)(char *chave), int rrn, btree *t);
btree_node btree_read(int rrn, btree *t);
void btree_write(btree_node no, btree *t);
btree_node btree_node_malloc(btree *t);
void btree_node_free(btree_node no);
int btree_register_size(btree *t);

/* Funções auxiliares */
char* strpadright(char *str, char pad, unsigned size);
char* strupr(char *str);
char* strlower(char *str);

/* Funções de busca binária */
int busca_binaria_com_reps(const void *key, const void *base0, size_t nmemb, size_t size, int (*compar)(const void *, const void *), bool exibir_caminho, int posicao_caso_repetido, int retorno_se_nao_encontrado);
int busca_binaria(const void *key, const void *base0, size_t nmemb, size_t size, int (*compar)(const void *, const void *), bool exibir_caminho, int retorno_se_nao_encontrado);

/* Funções extras */
int qsort_string_modelo(const void *a, const void *b);
int qsort_data_idx(const void *a, const void *b);
bool remove_e_reorganiza_node(btree_node *node, int rrn, btree *t);
void node_insert(promovido_aux promo, btree_node *node, int rrn, btree *t);

/* ===========================================================================
 * ================================= FUNÇÕES ================================= */

/* Funções de geração determinística de números pseudo-aleatórios */
void prng_srand(uint64_t value) {
	prng_seed = value;
}

uint64_t prng_rand() {
	// https://en.wikipedia.org/wiki/Xorshift#xorshift*
	uint64_t x = prng_seed; // O estado deve ser iniciado com um valor diferente de 0
	x ^= x >> 12;			// a
	x ^= x << 25;			// b
	x ^= x >> 27;			// c
	prng_seed = x;
	return x * UINT64_C(0x2545F4914F6CDD1D);
}

/**
 * Gera um <a href="https://en.wikipedia.org/wiki/Universally_unique_identifier">UUID Version-4 Variant-1</a>
 * (<i>string</i> aleatória) de 36 caracteres utilizando o gerador de números pseudo-aleatórios
 * <a href="https://en.wikipedia.org/wiki/Xorshift#xorshift*">xorshift*</a>. O UUID é
 * escrito na <i>string</i> fornecida como parâmetro.<br />
 * <br />
 * Exemplo de uso:<br />
 * <code>
 * char chave_aleatoria[37];<br />
 * new_uuid(chave_aleatoria);<br />
 * printf("chave aleatória: %s&#92;n", chave_aleatoria);<br />
 * </code>
 *
 * @param buffer String de tamanho 37 no qual será escrito
 * o UUID. É terminado pelo caractere <code>\0</code>.
 */
void new_uuid(char buffer[37]) {
	uint64_t r1 = prng_rand();
	uint64_t r2 = prng_rand();

	sprintf(buffer, "%08x-%04x-%04lx-%04lx-%012lx", (uint32_t)(r1 >> 32), (uint16_t)(r1 >> 16), 0x4000 | (r1 & 0x0fff), 0x8000 | (r2 & 0x3fff), r2 >> 16);
}

/* Funções de manipulação de data */
struct tm *gmtime_r(const time_t *timer, struct tm *tmbuf) {
	// based on http://www.jbox.dk/sanos/source/lib/time.c.html
	time_t time = *timer;
	unsigned long dayclock, dayno;
	int year = EPOCH_YR;

	dayclock = (unsigned long)time % SECS_DAY;
	dayno = (unsigned long)time / SECS_DAY;

	tmbuf->tm_sec = dayclock % 60;
	tmbuf->tm_min = (dayclock % 3600) / 60;
	tmbuf->tm_hour = dayclock / 3600;
	tmbuf->tm_wday = (dayno + 4) % 7; // Day 0 was a thursday
	while (dayno >= (unsigned long) YEARSIZE(year)) {
		dayno -= YEARSIZE(year);
		year++;
	}
	tmbuf->tm_year = year - YEAR0;
	tmbuf->tm_yday = dayno;
	tmbuf->tm_mon = 0;
	while (dayno >= (unsigned long) _ytab[LEAPYEAR(year)][tmbuf->tm_mon]) {
        dayno -= _ytab[LEAPYEAR(year)][tmbuf->tm_mon];
        tmbuf->tm_mon++;
    }
	tmbuf->tm_mday = dayno + 1;
	tmbuf->tm_isdst = 0;
	return tmbuf;
}

time_t mktime(struct tm *tmbuf) {
	// based on http://www.jbox.dk/sanos/source/lib/time.c.html
	long day, year;
	int tm_year;
	int yday, month;
	/*unsigned*/ long seconds;
	int overflow;
	long dst;

	tmbuf->tm_min += tmbuf->tm_sec / 60;
	tmbuf->tm_sec %= 60;
	if (tmbuf->tm_sec < 0) {
        tmbuf->tm_sec += 60;
        tmbuf->tm_min--;
    }
	tmbuf->tm_hour += tmbuf->tm_min / 60;
	tmbuf->tm_min = tmbuf->tm_min % 60;
	if (tmbuf->tm_min < 0) {
        tmbuf->tm_min += 60;
        tmbuf->tm_hour--;
    }
	day = tmbuf->tm_hour / 24;
	tmbuf->tm_hour= tmbuf->tm_hour % 24;
    if (tmbuf->tm_hour < 0) {
        tmbuf->tm_hour += 24;
        day--;
    }
	tmbuf->tm_year += tmbuf->tm_mon / 12;
	tmbuf->tm_mon %= 12;
	if (tmbuf->tm_mon < 0) {
        tmbuf->tm_mon += 12;
        tmbuf->tm_year--;
    }
	day += (tmbuf->tm_mday - 1);
	while (day < 0) {
        if(--tmbuf->tm_mon < 0) {
            tmbuf->tm_year--;
            tmbuf->tm_mon = 11;
        }
        day += _ytab[LEAPYEAR(YEAR0 + tmbuf->tm_year)][tmbuf->tm_mon];
    }
	while (day >= _ytab[LEAPYEAR(YEAR0 + tmbuf->tm_year)][tmbuf->tm_mon]) {
        day -= _ytab[LEAPYEAR(YEAR0 + tmbuf->tm_year)][tmbuf->tm_mon];
        if (++(tmbuf->tm_mon) == 12) {
            tmbuf->tm_mon = 0;
            tmbuf->tm_year++;
        }
    }
	tmbuf->tm_mday = day + 1;
	year = EPOCH_YR;
	if (tmbuf->tm_year < year - YEAR0)
		return (time_t)-1;
	seconds = 0;
	day = 0; // Means days since day 0 now
	overflow = 0;

	// Assume that when day becomes negative, there will certainly
	// be overflow on seconds.
	// The check for overflow needs not to be done for leapyears
	// divisible by 400.
	// The code only works when year (1970) is not a leapyear.
	tm_year = tmbuf->tm_year + YEAR0;

	if (TIME_MAX / 365 < tm_year - year)
		overflow++;
	day = (tm_year - year) * 365;
	if (TIME_MAX - day < (tm_year - year) / 4 + 1)
		overflow++;
	day += (tm_year - year) / 4 + ((tm_year % 4) && tm_year % 4 < year % 4);
	day -= (tm_year - year) / 100 + ((tm_year % 100) && tm_year % 100 < year % 100);
	day += (tm_year - year) / 400 + ((tm_year % 400) && tm_year % 400 < year % 400);

	yday = month = 0;
	while (month < tmbuf->tm_mon) {
        yday += _ytab[LEAPYEAR(tm_year)][month];
        month++;
    }
	yday += (tmbuf->tm_mday - 1);
	if (day + yday < 0)
		overflow++;
	day += yday;

	tmbuf->tm_yday = yday;
	tmbuf->tm_wday = (day + 4) % 7; // Day 0 was thursday (4)

	seconds = ((tmbuf->tm_hour * 60L) + tmbuf->tm_min) * 60L + tmbuf->tm_sec;

	if ((TIME_MAX - seconds) / SECS_DAY < day)
		overflow++;
	seconds += day * SECS_DAY;

	// Now adjust according to timezone and daylight saving time
	if (((_timezone > 0) && (TIME_MAX - _timezone < seconds)) || 
        ((_timezone < 0) && (seconds < -_timezone))) {
        overflow++;
    }
	seconds += _timezone;

	if (tmbuf->tm_isdst) {
        dst = _dstbias;
    } else {
        dst = 0;
    }

	if (dst > seconds)
		overflow++; // dst is always non-negative
	seconds -= dst;

	if (overflow)
		return (time_t)-1;

	if ((time_t)seconds != seconds)
		return (time_t)-1;
	return (time_t)seconds;
}

bool set_time(char *date) {
	// http://www.cplusplus.com/reference/ctime/mktime/
	struct tm tm_;

	if (strlen(date) == TAM_DATETIME-1 && sscanf(date, "%4d%2d%2d%2d%2d", &tm_.tm_year, &tm_.tm_mon, &tm_.tm_mday, &tm_.tm_hour, &tm_.tm_min) == 5) {
        tm_.tm_year -= 1900;
        tm_.tm_mon -= 1;
        tm_.tm_sec = 0;
        tm_.tm_isdst = -1;
        epoch = mktime(&tm_);
        return true;
    }
	return false;
}

void tick_time() {
	epoch += prng_rand() % 864000; // 10 dias
}

/**
 * Escreve a <i>data</i> atual no formato <code>AAAAMMDD</code> em uma <i>string</i>
 * fornecida como parâmetro.<br />
 * <br />
 * Exemplo de uso:<br />
 * <code>
 * char timestamp[TAM_DATE];<br />
 * current_date(timestamp);<br />
 * printf("data atual: %s&#92;n", timestamp);<br />
 * </code>
 *
 * @param buffer String de tamanho <code>TAM_DATE</code> no qual será escrita
 * a <i>timestamp</i>. É terminado pelo caractere <code>\0</code>.
 */
void current_date(char buffer[TAM_DATE]) {
	// http://www.cplusplus.com/reference/ctime/strftime/
	// http://www.cplusplus.com/reference/ctime/gmtime/
	// AAAA MM DD
	// %Y   %m %d
	struct tm tm_;
	if (gmtime_r(&epoch, &tm_) != NULL)
		strftime(buffer, TAM_DATE, "%Y%m%d", &tm_);
}

/**
 * Escreve a <i>data</i> e a <i>hora</i> atual no formato <code>AAAAMMDDHHMM</code> em uma <i>string</i>
 * fornecida como parâmetro.<br />
 * <br />
 * Exemplo de uso:<br />
 * <code>
 * char timestamp[TAM_DATETIME];<br />
 * current_datetime(timestamp);<br />
 * printf("data e hora atual: %s&#92;n", timestamp);<br />
 * </code>
 *
 * @param buffer String de tamanho <code>TAM_DATETIME</code> no qual será escrita
 * a <i>timestamp</i>. É terminado pelo caractere <code>\0</code>.
 */
void current_datetime(char buffer[TAM_DATETIME]) {
	// http://www.cplusplus.com/reference/ctime/strftime/
	// http://www.cplusplus.com/reference/ctime/gmtime/
	// AAAA MM DD HH MM
	// %Y   %m %d %H %M
	struct tm tm_;
	if (gmtime_r(&epoch, &tm_) != NULL)
		strftime(buffer, TAM_DATETIME, "%Y%m%d%H%M", &tm_);
}

/* Remove comentários (--) e caracteres whitespace do começo e fim de uma string */
void clear_input(char *str) {
	char *ptr = str;
	int len = 0;

	for (; ptr[len]; ++len) {
		if (strncmp(&ptr[len], "--", 2) == 0) {
			ptr[len] = '\0';
			break;
		}
	}

	while(len-1 > 0 && isspace(ptr[len-1]))
		ptr[--len] = '\0';

	while(*ptr && isspace(*ptr))
		++ptr, --len;

	memmove(str, ptr, len + 1);
}

/**
 * Preenche uma string str com o caractere pad para completar o tamanho size.<br />
 *
 * @param str Ponteiro para a string a ser manipulada.
 * @param pad Caractere utilizado para fazer o preenchimento à direita.
 * @param size Tamanho desejado para a string.
 */
char* strpadright(char *str, char pad, unsigned size);

/**
 * Converte uma string str para letras maiúsculas.<br />
 *
 * @param str Ponteiro para a string a ser manipulada.
 */
char* strupr(char *str);

/**
 * Converte uma string str para letras minúsculas.<br />
 *
 * @param str Ponteiro para a string a ser manipulada.
 */
char* strlower(char *str);

#endif