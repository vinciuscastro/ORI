/* ==========================================================================
 * Universidade Federal de São Carlos - Campus Sorocaba
 * Disciplina: Organização de Recuperação da Informação
 * Prof. Tiago A. Almeida
 *
 * Trabalho 01 - Indexação
 *
 * ========================================================================== *
 *   <<< IMPLEMENTE AQUI!!! COPIE E COLE O CONTEÚDO DESTE ARQUIVO NO AVA >>>
 * ========================================================================== */

/* Bibliotecas */
#include "ORI_T01_HEADER.h"

/* ===========================================================================
 * ================================= FUNÇÕES ================================= */

/* <<< COLOQUE AQUI OS DEMAIS PROTÓTIPOS DE FUNÇÕES, SE NECESSÁRIO >>> */

/* Funções auxiliares para o qsort.
 * Com uma pequena alteração, é possível utilizá-las no bsearch, assim, evitando código duplicado.
 * */

/* Função de comparação entre chaves do índice corredores_idx */
int qsort_corredores_idx(const void *a, const void *b)
{
	return strcmp(((corredores_index *)a)->id_corredor, ((corredores_index *)b)->id_corredor);
}

/* Função de comparação entre chaves do índice veiculos_idx */
int qsort_veiculos_idx(const void *a, const void *b)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	return strcmp(((veiculos_index *)a)->id_veiculo, ((veiculos_index *)b)->id_veiculo);
}

/* Função de comparação entre chaves do índice pistas_idx */
int qsort_pistas_idx(const void *a, const void *b)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	return strcmp(((pistas_index *)a)->id_pista, ((pistas_index *)b)->id_pista);
}

/* Função de comparação entre chaves do índice corridas_idx */
int qsort_corridas_idx(const void *a, const void *b)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	int comp = qsort_data_idx(a, b);
	return (comp != 0) ? comp : strcmp(((corridas_index *)a)->id_pista, ((corridas_index *)b)->id_pista);
}

/* Funções de comparação apenas entre data de ocorrencia do índice corridas_idx */
int qsort_data_idx(const void *a, const void *b)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	return strcmp(((corridas_index *)a)->ocorrencia, ((corridas_index *)b)->ocorrencia);
}

/* Função de comparação entre chaves do índice nome_pista_idx */
int qsort_nome_pista_idx(const void *a, const void *b)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	return strcmp(((nome_pista_index *)a)->nome, ((nome_pista_index *)b)->nome);
}

/* Função de comparação entre chaves do índice preco_veiculo_idx */
int qsort_preco_veiculo_idx(const void *a, const void *b)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (((preco_veiculo_index *)a)->preco < ((preco_veiculo_index *)b)->preco)

		return -1;

	else if (((preco_veiculo_index *)a)->preco > ((preco_veiculo_index *)b)->preco)

		return 1;

	else

		return 0;
}

/* Função de comparação entre chaves do índice secundário de corredor_veiculos_secundario_idx */
int qsort_corredor_veiculos_secundario_idx(const void *a, const void *b)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	return strcmp(((corredor_veiculos_secundario_index *)a)->chave_secundaria, ((corredor_veiculos_secundario_index *)b)->chave_secundaria);
}

/* Cria o índice respectivo */
void criar_corredores_idx()
{
	if (!corredores_idx)
		corredores_idx = malloc(MAX_REGISTROS * sizeof(corredores_index));

	if (!corredores_idx)
	{
		printf(ERRO_MEMORIA_INSUFICIENTE);
		exit(1);
	}

	for (unsigned i = 0; i < qtd_registros_corredores; ++i)
	{
		Corredor c = recuperar_registro_corredor(i);

		if (strncmp(c.id_corredor, "*|", 2) == 0)
			corredores_idx[i].rrn = -1;
		else
			corredores_idx[i].rrn = i;

		strcpy(corredores_idx[i].id_corredor, c.id_corredor);
	}

	qsort(corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx);
	printf(INDICE_CRIADO, "corredores_idx");
}

void criar_veiculos_idx()
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (!veiculos_idx)
		veiculos_idx = malloc(MAX_REGISTROS * sizeof(veiculos_index));

	if (!veiculos_idx)
	{
		printf(ERRO_MEMORIA_INSUFICIENTE);
		exit(1);
	}

	for (unsigned i = 0; i < qtd_registros_veiculos; ++i)
	{
		Veiculo c = recuperar_registro_veiculo(i);

		if (strncmp(c.id_veiculo, "*|", 2) == 0)
			veiculos_idx[i].rrn = -1;
		else
			veiculos_idx[i].rrn = i;

		strcpy(veiculos_idx[i].id_veiculo, c.id_veiculo);
	}

	qsort(veiculos_idx, qtd_registros_veiculos, sizeof(veiculos_index), qsort_veiculos_idx);
	printf(INDICE_CRIADO, "veiculos_idx");
}

void criar_pistas_idx()
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (!pistas_idx)
		pistas_idx = malloc(MAX_REGISTROS * sizeof(pistas_index));

	if (!pistas_idx)
	{
		printf(ERRO_MEMORIA_INSUFICIENTE);
		exit(1);
	}

	for (unsigned i = 0; i < qtd_registros_pistas; ++i)
	{
		Pista c = recuperar_registro_pista(i);

		if (strncmp(c.id_pista, "*|", 2) == 0)
			pistas_idx[i].rrn = -1; // registro excluído
		else
			pistas_idx[i].rrn = i;

		strcpy(pistas_idx[i].id_pista, c.id_pista);
	}

	qsort(pistas_idx, qtd_registros_pistas, sizeof(pistas_index), qsort_pistas_idx);
	printf(INDICE_CRIADO, "pistas_idx");
}

void criar_corridas_idx()
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (!corridas_idx)
		corridas_idx = malloc(MAX_REGISTROS * sizeof(corridas_index));

	if (!corridas_idx)
	{
		printf(ERRO_MEMORIA_INSUFICIENTE);
		exit(1);
	}

	for (unsigned i = 0; i < qtd_registros_corredores; ++i)
	{
		Corrida c = recuperar_registro_corrida(i);

		if (strncmp(c.ocorrencia, "*|", 2) == 0)
			corridas_idx[i].rrn = -1; // registro excluído
		else
			corridas_idx[i].rrn = i;

		strcpy(corridas_idx[i].ocorrencia, c.ocorrencia);
		strcpy(corridas_idx[i].id_pista, c.id_pista);
	}

	qsort(corridas_idx, qtd_registros_corredores, sizeof(corridas_index), qsort_corridas_idx);
	printf(INDICE_CRIADO, "corridas_idx");
}

void criar_nome_pista_idx()
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (!nome_pista_idx)
		nome_pista_idx = malloc(MAX_REGISTROS * sizeof(nome_pista_index));

	if (!nome_pista_idx)
	{
		printf(ERRO_MEMORIA_INSUFICIENTE);
		exit(1);
	}

	for (unsigned i = 0; i < qtd_registros_corredores; ++i)
	{
		Pista c = recuperar_registro_pista(i);
		strcpy(nome_pista_idx[i].nome, c.nome);
		strcpy(nome_pista_idx[i].id_pista, c.id_pista);
	}

	qsort(nome_pista_idx, qtd_registros_corredores, sizeof(nome_pista_index), qsort_nome_pista_idx);
	printf(INDICE_CRIADO, "nome_pista_idx");
}

void criar_preco_veiculo_idx()
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (!preco_veiculo_idx)
		preco_veiculo_idx = malloc(MAX_REGISTROS * sizeof(preco_veiculo_index));

	if (!preco_veiculo_idx)
	{
		printf(ERRO_MEMORIA_INSUFICIENTE);
		exit(1);
	}

	for (unsigned i = 0; i < qtd_registros_veiculos; ++i)
	{
		Veiculo v = recuperar_registro_veiculo(i);
		preco_veiculo_idx[i].preco = v.preco;
		strcpy(preco_veiculo_idx[i].id_veiculo, v.id_veiculo);
	}

	qsort(preco_veiculo_idx, qtd_registros_veiculos, sizeof(preco_veiculo_index), qsort_preco_veiculo_idx);
	printf(INDICE_CRIADO, "preco_veiculo_idx");
}

void criar_corredor_veiculos_idx()
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (!corredor_veiculos_idx.corredor_veiculos_primario_idx)
		corredor_veiculos_idx.corredor_veiculos_primario_idx = malloc(MAX_REGISTROS * sizeof(corredor_veiculos_primario_index));

	if (!corredor_veiculos_idx.corredor_veiculos_secundario_idx)
		corredor_veiculos_idx.corredor_veiculos_secundario_idx = malloc(MAX_REGISTROS * sizeof(corredor_veiculos_secundario_index));

	if (!corredor_veiculos_idx.corredor_veiculos_primario_idx || !corredor_veiculos_idx.corredor_veiculos_secundario_idx)
	{
		printf(ERRO_MEMORIA_INSUFICIENTE);
		exit(1);
	}

	for (unsigned i = 0; i < qtd_registros_corredores; ++i)
	{
		Corredor v = recuperar_registro_corredor(i);
		for (unsigned k = 0; k < QTD_MAX_VEICULO; ++k)
		{
			if (v.veiculos[k])
				inverted_list_insert(v.veiculos[k], v.id_corredor, &corredor_veiculos_idx);
		}
	}
	printf(INDICE_CRIADO, "corredor_veiculos_idx");
}

/* Exibe um registro com base no RRN */
bool exibir_corredor(int rrn)
{
	if (rrn < 0)
		return false;

	Corredor c = recuperar_registro_corredor(rrn);

	printf("%s, %s, %s, %s, %.2lf\n", c.id_corredor, c.nome, c.apelido, c.cadastro, c.saldo);
	return true;
}

bool exibir_veiculo(int rrn)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (rrn < 0)
		return false;

	Veiculo c = recuperar_registro_veiculo(rrn);

	printf("%s, %s, %s, %s, %d, %d, %d, %.2lf\n", c.id_veiculo, c.marca, c.modelo, c.poder, c.velocidade, c.aceleracao, c.peso, c.preco);
	return true;
}

bool exibir_pista(int rrn)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (rrn < 0)
		return false;
	Pista c = recuperar_registro_pista(rrn);

	printf("%s, %s, %d, %d, %d\n", c.id_pista, c.nome, c.dificuldade, c.distancia, c.recorde);
	return true;
}

bool exibir_corrida(int rrn)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (rrn < 0)
		return false;

	Corrida c = recuperar_registro_corrida(rrn);

	printf("%s, %s, %s, %s\n", c.id_pista, c.ocorrencia, c.id_corredores, c.id_veiculos);
	return true;
}

/* Recupera do arquivo o registro com o RRN informado
 * e retorna os dados nas structs corredor, Curso e Inscricao */
Corredor recuperar_registro_corredor(int rrn)
{
	Corredor c;
	char temp[TAM_REGISTRO_CORREDOR + 1], *p;
	strncpy(temp, ARQUIVO_CORREDORES + (rrn * TAM_REGISTRO_CORREDOR), TAM_REGISTRO_CORREDOR);
	temp[TAM_REGISTRO_CORREDOR] = '\0';

	p = strtok(temp, ";");
	strcpy(c.id_corredor, p);
	p = strtok(NULL, ";");
	strcpy(c.nome, p);
	p = strtok(NULL, ";");
	strcpy(c.apelido, p);
	p = strtok(NULL, ";");
	strcpy(c.cadastro, p);
	p = strtok(NULL, ";");
	c.saldo = atof(p);
	p = strtok(NULL, ";");

	for (int i = 0; i < QTD_MAX_VEICULO; ++i)
		c.veiculos[i][0] = '\0';

	if (p[0] != '#')
	{
		p = strtok(p, "|");

		for (int pos = 0; p; p = strtok(NULL, "|"), ++pos)
			strcpy(c.veiculos[pos], p);
	}

	return c;
}

Veiculo recuperar_registro_veiculo(int rrn)
{
	Veiculo v;
	char temp[TAM_REGISTRO_VEICULO + 1], *p;
	strncpy(temp, ARQUIVO_VEICULOS + (rrn * TAM_REGISTRO_VEICULO), TAM_REGISTRO_VEICULO);
	temp[TAM_REGISTRO_VEICULO] = '\0';

	p = strtok(temp, ";");
	strcpy(v.id_veiculo, p);
	p = strtok(NULL, ";");
	strcpy(v.marca, p);
	p = strtok(NULL, ";");
	strcpy(v.modelo, p);
	p = strtok(NULL, ";");
	strcpy(v.poder, p);

	p = strtok(NULL, ";");
	v.velocidade = atof(p);
	p = strtok(NULL, ";");
	v.aceleracao = atof(p);
	p = strtok(NULL, ";");
	v.peso = atof(p);
	p = strtok(NULL, ";");
	v.preco = atof(p);

	return v;
	/*IMPLEMENTE A FUNÇÃO AQUI*/
}

Pista recuperar_registro_pista(int rrn)
{
	Pista p;
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char temp[TAM_REGISTRO_PISTA + 1], *a;
	strncpy(temp, ARQUIVO_PISTAS + (rrn * TAM_REGISTRO_PISTA), TAM_REGISTRO_PISTA);
	temp[TAM_REGISTRO_PISTA] = '\0';

	a = strtok(temp, ";");
	strcpy(p.id_pista, a);
	a = strtok(NULL, ";");
	strcpy(p.nome, a);

	a = strtok(NULL, ";");
	p.dificuldade = atoi(a);
	a = strtok(NULL, ";");
	p.distancia = atoi(a);
	a = strtok(NULL, ";");
	p.recorde = atoi(a);

	return p;
}

Corrida recuperar_registro_corrida(int rrn)
{
	Corrida c;

	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char temp[TAM_REGISTRO_CORRIDA + 1], *p;
	strncpy(temp, ARQUIVO_CORRIDAS + (rrn * TAM_REGISTRO_CORRIDA), TAM_REGISTRO_CORRIDA);
	temp[TAM_REGISTRO_CORRIDA] = '\0';

	p = strtok(temp, ";");
	strcpy(c.id_pista, p);
	p = strtok(NULL, ";");
	strcpy(c.ocorrencia, p);
	p = strtok(NULL, ";");
	strcpy(c.id_corredores, p);
	p = strtok(NULL, ";");
	strcpy(c.id_veiculos, p);

	return c;
}

/* Escreve em seu respectivo arquivo na posição informada (RRN) */
void escrever_registro_corredor(Corredor c, int rrn)
{
	char temp[TAM_REGISTRO_CORREDOR + 1], p[100];
	temp[0] = '\0';
	p[0] = '\0';

	strcpy(temp, c.id_corredor);
	strcat(temp, ";");
	strcat(temp, c.nome);
	strcat(temp, ";");
	strcat(temp, c.apelido);
	strcat(temp, ";");
	strcat(temp, c.cadastro);
	strcat(temp, ";");
	sprintf(p, "%013.2lf", c.saldo);
	strcat(temp, p);
	strcat(temp, ";");

	for (int i = 0, k = 0; i < QTD_MAX_VEICULO; ++i)
	{
		if (strlen(c.veiculos[i]) > 0)
		{
			if (k == 0)
				k = 1;
			else
				strcat(temp, "|");
			strcat(temp, c.veiculos[i]);
		}
	}
	strcat(temp, ";");

	strpadright(temp, '#', TAM_REGISTRO_CORREDOR);

	strncpy(ARQUIVO_CORREDORES + rrn * TAM_REGISTRO_CORREDOR, temp, TAM_REGISTRO_CORREDOR);
}

void escrever_registro_veiculo(Veiculo v, int rrn)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char temp[TAM_ARQUIVO_VEICULOS + 1], p[100];
	temp[0] = '\0';
	p[0] = '\0';

	strcpy(temp, v.id_veiculo);
	strcat(temp, ";");
	strcat(temp, v.marca);
	strcat(temp, ";");
	strcat(temp, v.modelo);
	strcat(temp, ";");
	strcat(temp, v.poder);
	strcat(temp, ";");

	sprintf(p, "%04d", v.velocidade);
	strcat(temp, p);
	strcat(temp, ";");

	sprintf(p, "%04d", v.aceleracao);
	strcat(temp, p);
	strcat(temp, ";");

	sprintf(p, "%04d", v.peso);
	strcat(temp, p);
	strcat(temp, ";");

	sprintf(p, "%013.2lf", v.preco);
	strcat(temp, p);
	strcat(temp, ";");

	strpadright(temp, '#', TAM_REGISTRO_VEICULO);

	strncpy(ARQUIVO_VEICULOS + rrn * TAM_REGISTRO_VEICULO, temp, TAM_REGISTRO_VEICULO);
}

void escrever_registro_pista(Pista p, int rrn)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char temp[TAM_ARQUIVO_PISTAS + 1], v[100];
	temp[0] = '\0';
	v[0] = '\0';

	strcpy(temp, p.id_pista);
	strcat(temp, ";");

	strcat(temp, p.nome);
	strcat(temp, ";");

	sprintf(v, "%04d", p.dificuldade);
	strcat(temp, v);
	strcat(temp, ";");

	sprintf(v, "%04d", p.distancia);
	strcat(temp, v);
	strcat(temp, ";");

	sprintf(v, "%04d", p.recorde);
	strcat(temp, v);
	strcat(temp, ";");

	strpadright(temp, '#', TAM_REGISTRO_PISTA);

	strncpy(ARQUIVO_PISTAS + rrn * TAM_REGISTRO_PISTA, temp, TAM_REGISTRO_PISTA);
}

void escrever_registro_corrida(Corrida i, int rrn)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char temp[TAM_ARQUIVO_CORRIDAS + 1];
	temp[0] = '\0';

	strcpy(temp, i.id_pista);
	strcat(temp, ";");
	strcat(temp, i.ocorrencia);
	strcat(temp, ";");
	strcpy(temp, i.id_corredores);
	strcat(temp, ";");
	strcat(temp, i.id_veiculos);
	strcat(temp, ";");

	strpadright(temp, '#', TAM_REGISTRO_CORRIDA);

	strncpy(ARQUIVO_CORRIDAS + rrn * TAM_REGISTRO_CORRIDA, temp, TAM_REGISTRO_CORRIDA);
}

/* Funções principais */
void cadastrar_corredor_menu(char *id_corredor, char *nome, char *apelido)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char timestamp[TAM_DATETIME];
	current_datetime(timestamp);
	Corredor corredor;
	corredores_index index;
	strcpy(index.id_corredor, id_corredor);
	corredores_index *found = busca_binaria((void *)&index, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0);
	// printf("ENTRAMOS NA PRIMEIRA");
	if (found == NULL || found->rrn < 0)
	{
		// printf("%s", found->id_corredor);
		//  printf("ENTRAMOS");
		strcpy(corredor.id_corredor, id_corredor);
		strcpy(corredor.nome, nome);
		strcpy(corredor.apelido, apelido);
		strcpy(corredor.cadastro, timestamp);

		corredor.saldo = atof("000000000000.00");
		for (int i = 0; i < QTD_MAX_VEICULO; i++)
		{
			strcpy(corredor.veiculos[i], "\0");
		}
		escrever_registro_corredor(corredor, qtd_registros_corredores);
		strcpy(corredores_idx[qtd_registros_corredores].id_corredor, id_corredor);
		corredores_idx[qtd_registros_corredores].rrn = qtd_registros_corredores;
		qtd_registros_corredores++;
		qsort(corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx);
		printf(SUCESSO);
	}
	else
		printf(ERRO_PK_REPETIDA, found->id_corredor);
}

void remover_corredor_menu(char *id_corredor)
{

	Corredor corredor;
	corredores_index index;
	strcpy(index.id_corredor, id_corredor);
	corredores_index *found = busca_binaria((void *)&index, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0);
	if (found == NULL || found->rrn < 0)
	{
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	}
	else
	{
		corredor = recuperar_registro_corredor(found->rrn);
		strcpy(corredor.id_corredor, "*|");
		escrever_registro_corredor(corredor, found->rrn);
		found->rrn = -1;
		printf(SUCESSO);
	}
}

void adicionar_saldo_menu(char *id_corredor, double valor)
{
	adicionar_saldo(id_corredor, valor, true);
}

void adicionar_saldo(char *id_corredor, double valor, bool flag)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	Corredor corredor;
	corredores_index index;

	strcpy(index.id_corredor, id_corredor);
	corredores_index *found = busca_binaria((void *)&index, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0);
	if (found == NULL || found->rrn < 0)
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	else
	{
		if (valor <= 0)
			printf(ERRO_VALOR_INVALIDO);
		else
		{
			corredor = recuperar_registro_corredor(found->rrn);
			corredor.saldo += valor;
			escrever_registro_corredor(corredor, found->rrn);
			printf(SUCESSO);
		}
	}
}

void comprar_veiculo_menu(char *id_corredor, char *id_veiculo)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "comprar_veiculo_menu()");
}

void cadastrar_veiculo_menu(char *marca, char *modelo, char *poder, int velocidade, int aceleracao, int peso, double preco)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	// printf("depsdodpaospdapsdpsdpsad\n");
	Veiculo veiculo;
	veiculos_index index;
	char id_aux[8];
	sprintf(id_aux, "%07d", qtd_registros_veiculos);
	// printf("%s", id_aux);
	//  printf("oi\n");
	strcpy(index.id_veiculo, id_aux);
	// printf("%s", id_aux);
	veiculos_index *found = busca_binaria((void *)&index, veiculos_idx, qtd_registros_veiculos, sizeof(veiculos_index), qsort_veiculos_idx, false, 0);
	// printf("ENTRAMOS no veiculoAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
	if (found == NULL || found->rrn < 0)
	{
		// printf("%s", found->id_corredor);
		// printf("ENTRAMOS");
		// sprintf(veiculo.id_veiculo, "%07d", qtd_registros_veiculos);
		strcpy(veiculo.id_veiculo, id_aux);
		strcpy(veiculo.marca, marca);
		strcpy(veiculo.modelo, modelo);
		strcpy(veiculo.poder, poder);
		veiculo.velocidade = velocidade;
		veiculo.aceleracao = aceleracao;
		veiculo.peso = peso;
		veiculo.preco = preco;

		escrever_registro_veiculo(veiculo, qtd_registros_veiculos);
		// Gravar no veiculos_idx
		strcpy(veiculos_idx[qtd_registros_veiculos].id_veiculo, id_aux);
		veiculos_idx[qtd_registros_veiculos].rrn = qtd_registros_veiculos;
		// Gravar no preco_veiculo_idx
		preco_veiculo_idx[qtd_registros_veiculos].preco = preco;
		strcpy(preco_veiculo_idx[qtd_registros_veiculos].id_veiculo, id_aux);

		qtd_registros_veiculos++;

		qsort(veiculos_idx, qtd_registros_veiculos, sizeof(veiculos_index), qsort_veiculos_idx);

		qsort(preco_veiculo_idx, qtd_registros_veiculos, sizeof(preco_veiculo_index), qsort_preco_veiculo_idx);
		// printf("ASIAOSAISOASA\n");
		printf(SUCESSO);
	}
	else
		printf(ERRO_PK_REPETIDA, found->id_veiculo);
}

void cadastrar_pista_menu(char *nome, int dificuldade, int distancia, int recorde)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	Pista pista;
	nome_pista_index index;
	char id_aux[9];
	sprintf(id_aux, "%08d", qtd_registros_pistas);

	strcpy(index.nome, nome);

	nome_pista_index *found = busca_binaria((void *)&index, nome_pista_idx, qtd_registros_pistas, sizeof(nome_pista_index), qsort_nome_pista_idx, false, 0);
	// printf("ENTRAMOS no veiculoAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
	// printf("%s",found->nome);
	if (found == NULL)
	{
		strcpy(pista.id_pista, id_aux);
		strcpy(pista.nome, nome);
		pista.dificuldade = dificuldade;
		pista.distancia = distancia;
		pista.recorde = recorde;

		escrever_registro_pista(pista, qtd_registros_pistas);
		// Gravar no veiculos_idx
		strcpy(pistas_idx[qtd_registros_pistas].id_pista, id_aux);
		pistas_idx[qtd_registros_pistas].rrn = qtd_registros_pistas;
		// Gravar no nome_pista_idx
		strcpy(nome_pista_idx[qtd_registros_pistas].nome, nome);

		strcpy(nome_pista_idx[qtd_registros_pistas].id_pista, id_aux);

		qtd_registros_pistas++;

		qsort(pistas_idx, qtd_registros_pistas, sizeof(pistas_index), qsort_pistas_idx);

		qsort(nome_pista_idx, qtd_registros_pistas, sizeof(nome_pista_index), qsort_nome_pista_idx);
		printf(SUCESSO);
	}
	else
		printf(ERRO_PK_REPETIDA, found->nome);
}

void executar_corrida_menu(char *id_pista, char *ocorrencia, char *id_corredores, char *id_veiculos)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "executar_corrida_menu()");
}

/* Busca */
void buscar_corredor_id_menu(char *id_corredor)
{
	corredores_index index;
	strcpy(index.id_corredor, id_corredor);
	corredores_index *found = busca_binaria((void *)&index, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, true, 0);
	if (found == NULL || found->rrn < 0)
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	else
		exibir_corredor(found->rrn);
}

void buscar_pista_id_menu(char *id_pista)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	pistas_index index;
	strcpy(index.id_pista, id_pista);
	pistas_index *found = busca_binaria((void *)&index, pistas_idx, qtd_registros_pistas, sizeof(pistas_index), qsort_pistas_idx, true, 0);
	if (found == NULL || found->rrn < 0)
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	else
		exibir_pista(found->rrn);
}

void buscar_pista_nome_menu(char *nome_pista)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	nome_pista_index index;
	strcpy(index.nome, nome_pista);
	nome_pista_index *found = busca_binaria((void *)&index, nome_pista_idx, qtd_registros_pistas, sizeof(nome_pista_index), qsort_nome_pista_idx, true, 0);
	if (found == NULL)
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	else
		buscar_pista_id_menu(found->id_pista);
}

/* Listagem */
void listar_corredores_id_menu()
{
	if (qtd_registros_corredores == 0)
		printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
	else
		for (unsigned int i = 0; i < qtd_registros_corredores; i++)
			exibir_corredor(corredores_idx[i].rrn);
}

void listar_corredores_modelo_menu(char *modelo)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	// ????????????????
	printf(ERRO_NAO_IMPLEMENTADO, "listar_corredores_modelo_menu()");
}

void listar_veiculos_compra_menu(char *id_corredor)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (qtd_registros_veiculos == 0)
		printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
	else
	{
		corredores_index index;
		Corredor corredor;
		strcpy(index.id_corredor, id_corredor);
		corredores_index *found = busca_binaria((void *)&index, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0);

		if (found == NULL || found->rrn < 0)
		{
			printf(ERRO_REGISTRO_NAO_ENCONTRADO);
		}
		else
		{
			corredor = recuperar_registro_corredor(found->rrn);

			for (unsigned int i = 0; i < qtd_registros_veiculos; i++)
			{
				double preco = preco_veiculo_idx[i].preco;
				if (preco <= corredor.saldo)
				{
					Veiculo veiculo;
					veiculos_index index;
					strcpy(index.id_veiculo, preco_veiculo_idx[i].id_veiculo);
					// printf("%s", id_aux);
					veiculos_index *found_v = busca_binaria((void *)&index, veiculos_idx, qtd_registros_veiculos, sizeof(veiculos_index), qsort_veiculos_idx, false, 0);
					if (found_v == NULL || found_v->rrn < 0)
					{
						printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
					}
					else
						exibir_veiculo(found_v->rrn);
				}
			}
		}
	}
}

void listar_corridas_periodo_menu(char *data_inicio, char *data_fim)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "listar_corridas_periodo_menu()");
}

/* Liberar espaço */
void liberar_espaco_menu()
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char temp[TAM_REGISTRO_CORREDOR];
	char ARQUIVO_CORREDORES_AUX[TAM_ARQUIVO_CORREDORES];
	size_t k = 0;

	for (unsigned i = 0; i < qtd_registros_corredores; i++)
	{
		strncpy(temp, ARQUIVO_CORREDORES + (i * TAM_REGISTRO_CORREDOR), TAM_REGISTRO_CORREDOR);
		if (strncmp(temp, "*|", 2) == 0)
		{
			continue;
		}
		else
		{
			strncpy(ARQUIVO_CORREDORES_AUX + k * TAM_REGISTRO_CORREDOR, temp, TAM_REGISTRO_CORREDOR);
			k++;
		}
	}
	qtd_registros_corredores = k;
	strcpy(ARQUIVO_CORREDORES, ARQUIVO_CORREDORES_AUX);
	criar_corredores_idx();
	printf(SUCESSO);
}

/* Imprimir arquivos de dados */
void imprimir_arquivo_corredores_menu()
{
	if (qtd_registros_corredores == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_CORREDORES);
}

void imprimir_arquivo_veiculos_menu()
{
	if (qtd_registros_veiculos == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_VEICULOS);
}

void imprimir_arquivo_pistas_menu()
{
	if (qtd_registros_pistas == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_PISTAS);
}

void imprimir_arquivo_corridas_menu()
{
	if (qtd_registros_corridas == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_CORRIDAS);
}

/* Imprimir índices primários */
void imprimir_corredores_idx_menu()
{
	if (corredores_idx == NULL || qtd_registros_corredores == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < qtd_registros_corredores; ++i)
			printf("%s, %d\n", corredores_idx[i].id_corredor, corredores_idx[i].rrn);
}

void imprimir_veiculos_idx_menu()
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (veiculos_idx == NULL || qtd_registros_veiculos == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < qtd_registros_veiculos; ++i)
			printf("%s, %d\n", veiculos_idx[i].id_veiculo, veiculos_idx[i].rrn);
}

void imprimir_pistas_idx_menu()
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (pistas_idx == NULL || qtd_registros_pistas == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < qtd_registros_pistas; ++i)
			printf("%s, %d\n", pistas_idx[i].id_pista, pistas_idx[i].rrn);
}

void imprimir_corridas_idx_menu()
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (corridas_idx == NULL || qtd_registros_corridas == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < qtd_registros_corredores; ++i)
			printf("%s, %s, %d\n", corridas_idx[i].ocorrencia, corridas_idx[i].id_pista, corridas_idx[i].rrn);
}

/* Imprimir índices secundários */
void imprimir_nome_pista_idx_menu()
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (nome_pista_idx == NULL || qtd_registros_pistas == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < qtd_registros_pistas; ++i)
			printf("%s, %s\n", nome_pista_idx[i].nome, nome_pista_idx[i].id_pista);
}

void imprimir_preco_veiculo_idx_menu()
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (preco_veiculo_idx == NULL || qtd_registros_veiculos == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < qtd_registros_veiculos; ++i)
			printf("%.2lf, %s\n", preco_veiculo_idx[i].preco, preco_veiculo_idx[i].id_veiculo);
}

void imprimir_corredor_veiculos_secundario_idx_menu()
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (corredor_veiculos_idx.corredor_veiculos_secundario_idx == NULL || corredor_veiculos_idx.qtd_registros_secundario == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < corredor_veiculos_idx.qtd_registros_secundario; ++i)
			printf("%s, %d\n", corredor_veiculos_idx.corredor_veiculos_secundario_idx[i].chave_secundaria, corredor_veiculos_idx.corredor_veiculos_secundario_idx[i].primeiro_indice);
}

void imprimir_corredor_veiculos_primario_idx_menu()
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (corredor_veiculos_idx.corredor_veiculos_primario_idx == NULL || corredor_veiculos_idx.qtd_registros_primario == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		for (unsigned i = 0; i < corredor_veiculos_idx.qtd_registros_secundario; ++i)
			printf("%s, %d\n", corredor_veiculos_idx.corredor_veiculos_primario_idx[i].chave_primaria, corredor_veiculos_idx.corredor_veiculos_primario_idx[i].proximo_indice);
}

/* Liberar memória e encerrar programa */
void liberar_memoria_menu()
{
	free(corredores_idx);
	free(veiculos_idx);
	free(pistas_idx);
	free(corridas_idx);
	free(nome_pista_idx);
	free(preco_veiculo_idx);
	free(corredor_veiculos_idx.corredor_veiculos_primario_idx);
	free(corredor_veiculos_idx.corredor_veiculos_secundario_idx);
	/*IMPLEMENTE A FUNÇÃO AQUI*/
}

void inverted_list_insert(char *chave_secundaria, char *chave_primaria, inverted_list *t)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	int rrn, idx;
	bool found = inverted_list_secondary_search(&rrn, false, chave_secundaria, t);
	if (found)
	{
		inverted_list_primary_search(NULL, false, rrn, &idx, t);
		t->corredor_veiculos_primario_idx[idx].proximo_indice = t->qtd_registros_primario;
	}
	else
	{
		strcpy(t->corredor_veiculos_secundario_idx[t->qtd_registros_secundario].chave_secundaria, chave_secundaria);
		t->corredor_veiculos_secundario_idx[t->qtd_registros_secundario].primeiro_indice = t->qtd_registros_primario;
		t->qtd_registros_secundario++;
		qsort(t->corredor_veiculos_secundario_idx, t->corredor_veiculos_secundario_idx, sizeof(corredor_veiculos_secundario_index), t->corredor_veiculos_secundario_idx);
	}
	strcpy(t->corredor_veiculos_primario_idx[t->qtd_registros_primario].chave_primaria, chave_primaria);
	t->corredor_veiculos_primario_idx[t->qtd_registros_primario].proximo_indice = -1;
	t->qtd_registros_primario++;
}

bool inverted_list_secondary_search(int *result, bool exibir_caminho, char *chave_secundaria, inverted_list *t)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	corredor_veiculos_secundario_index index;
	strcpy(index.chave_secundaria, chave_secundaria);
	corredor_veiculos_secundario_index *found = busca_binaria((void *)&index, t->corredor_veiculos_secundario_idx, t->qtd_registros_secundario, sizeof(corredor_veiculos_secundario_index), qsort_corredor_veiculos_secundario_idx, exibir_caminho, 0);
	if (found == NULL)
	{
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
		return false;
	}
	else
	{
		if (result)
			*result = found->primeiro_indice;
		return true;
	}
}

int inverted_list_primary_search(char result[][TAM_ID_CORREDOR], bool exibir_caminho, int indice, int *indice_final, inverted_list *t)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	int idx = indice;
	if (exibir_caminho)
		printf(REGS_PERCORRIDOS);
	for (unsigned i = 0; i != -1; i++)
	{
		if (exibir_caminho)
			printf(" %s", t->corredor_veiculos_primario_idx->chave_primaria);
		strcpy(result[i], t->corredor_veiculos_primario_idx->chave_primaria);
		idx = t->corredor_veiculos_primario_idx->proximo_indice;
	}
	if (exibir_caminho)
		printf("\n");
	if (indice_final)
		*indice_final = idx;
}

void *busca_binaria_com_reps(const void *key, const void *base0, size_t nmemb, size_t size, int (*compar)(const void *, const void *), bool exibir_caminho, int posicao_caso_repetido, int retorno_se_nao_encontrado)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	// printf("ENTRAMOS BIN\n");
	char *base = (char *)base0;
	long int imin = 0;
	long int imax = (long int)nmemb - 1;
	if (exibir_caminho)
		printf(REGS_PERCORRIDOS);
	while (imax >= imin)
	{
		// printf("%zu nmebm\n", imax);
		// printf("%ld imax\n", imax);
		// printf("%ld imin\n", imin);
		long int imid = imin + (imax - imin) / 2;
		const void *found = base + imid * size;
		int result = compar(key, found);
		if (exibir_caminho)
			// printf("%d result\n", result);
			printf(" %ld", imid);

		if (result > 0)
		{
			// printf("pri\n");
			imin = imid + 1;
		}
		else if (result < 0)
		{
			// printf("sec\n");

			imax = imid - 1;
		}
		else
		{
			if (exibir_caminho)
				printf("\n");
			return (void *)found;
		}
	}
	if (exibir_caminho)
		printf("\n");
	return NULL;
}

void *busca_binaria(
		const void *key,
		const void *base0,
		size_t nmemb,
		size_t size,
		int (*compar)(const void *, const void *),
		bool exibir_caminho,
		int retorno_se_nao_encontrado)
{
	return busca_binaria_com_reps(key, base0, nmemb, size, compar, exibir_caminho, 0, retorno_se_nao_encontrado);
}

char *strpadright(char *str, char pad, unsigned size)
{
	for (unsigned i = strlen(str); i < size; ++i)
		str[i] = pad;
	str[size] = '\0';
	return str;
}
char *strupr(char *str)
{
	for (char *p = str; *p; ++p)
		*p = toupper(*p);
	return str;
}
char *strlower(char *str)
{
	for (char *p = str; *p; ++p)
		*p = tolower(*p);
	return str;
}