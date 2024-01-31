/* ==========================================================================
 * Universidade Federal de São Carlos - Campus Sorocaba
 * Disciplina: Organização de Recuperação da Informação
 * Prof. Tiago A. Almeida
 *
 * Trabalho 02 - Árvore-B
 *
 * ========================================================================== *
 *   <<< IMPLEMENTE AQUI!!! COPIE E COLE O CONTEÚDO DESTE ARQUIVO NO AVA >>>
 * ========================================================================== */
/* Bibliotecas */
#include "ORI_T02_HEADER.h"
/* ===========================================================================
 * ================================= FUNÇÕES ================================= */
/* <<< COLOQUE AQUI OS DEMAIS PROTÓTIPOS DE FUNÇÕES, SE NECESSÁRIO >>> */
void free_and_write(btree_node *node1, btree_node *node2, btree_node *node3, btree_node *node4, btree *t);
/* Compara a chave (key) com cada elemento do índice (elem).
 * Funções auxiliares para o buscar e inserir chaves em Árvores-B.
 * Note que, desta vez, as funções comparam chaves no formato string, e não struct.
 * "key" é a chave do tipo string que está sendo buscada ou inserida.
 * "elem" é uma chave do tipo string da struct btree_node.
 *
 * Dica: consulte sobre as funções strncmp() e strnlen(). Muito provavelmente, você vai querer utilizá-las no código.
 * */
/* Função de comparação entre chaves do índice corredores_idx */
int order_corredores_idx(const void *key, const void *elem)
{
	return strncmp(key, elem, TAM_ID_CORREDOR - 1);
}

/* Função de comparação entre chaves do índice veiculos_idx */
int order_veiculos_idx(const void *key, const void *elem)
{
	/* IMPLEMENTAR A FUNÇÃO AQUI */
	return strncmp(key, elem, TAM_ID_VEICULO - 1);
}

/* Função de comparação entre chaves do índice pistas_idx */
int order_pistas_idx(const void *key, const void *elem)
{
	/* IMPLEMENTAR A FUNÇÃO AQUI */
	return strncmp(key, elem, TAM_ID_PISTA - 1);
}

/* Função de comparação entre chaves do índice corridas_idx */
int order_corridas_idx(const void *key, const void *elem)
{
	/* IMPLEMENTAR A FUNÇÃO AQUI */
	return strncmp(key, elem, TAM_DATETIME + TAM_ID_PISTA - 2);
}

/* Função de comparação entre chaves do índice nome_pista_idx */
int order_nome_pista_idx(const void *key, const void *elem)
{
	/* IMPLEMENTAR A FUNÇÃO AQUI */
	return (strlen(key) < strlen(elem)) ? strncmp(key, elem, strlen(key) - 1) : strncmp(key, elem, strlen(elem) - 1); // Faz a comparacao com a string de menor tamanho
}

/* Função de comparação entre chaves do índice preco_veiculo_idx */
int order_preco_veiculo_idx(const void *key, const void *elem)
{
	/* IMPLEMENTAR A FUNÇÃO AQUI */
	return strncmp(key, elem, TAM_FLOAT_NUMBER + TAM_ID_VEICULO - 2);
}

/* Função de comparação entre chaves do índice secundário de corredor_veiculos_secundario_idx */
int order_corredor_veiculo_idx(const void *key, const void *elem)
{
	/* IMPLEMENTAR A FUNÇÃO AQUI */
	return (strlen(key) < strlen(elem)) ? strncmp(key, elem, strlen(key) - 1) : strncmp(key, elem, strlen(elem) - 1); // Faz a comparacao com a string de menor tamanho
}

/* Cria o índice respectivo */
void criar_corredores_idx()
{
	/* IMPLEMENTAR A FUNÇÃO AQUI */
	char corredor_str[TAM_CHAVE_CORREDORES_IDX + 1];
	for (unsigned i = 0; i < qtd_registros_corredores; ++i)
	{
		Corredor c = recuperar_registro_corredor(i);
		sprintf(corredor_str, "%s%04d", c.id_corredor, i);
		btree_insert(corredor_str, &corredores_idx);
	}

	printf(INDICE_CRIADO, "corredores_idx");
}

void criar_veiculos_idx()
{
	/* IMPLEMENTAR A FUNÇÃO AQUI */
	char veiculos_str[TAM_CHAVE_VEICULOS_IDX + 1];
	for (unsigned i = 0; i < qtd_registros_veiculos; ++i)
	{
		Veiculo c = recuperar_registro_veiculo(i);
		sprintf(veiculos_str, "%s%04d", c.id_veiculo, i);
		btree_insert(veiculos_str, &veiculos_idx);
	}

	printf(INDICE_CRIADO, "veiculos_idx");
}

void criar_pistas_idx()
{
	/* IMPLEMENTAR A FUNÇÃO AQUI */
	char pistas_str[TAM_CHAVE_PISTAS_IDX + 1];
	for (unsigned i = 0; i < qtd_registros_pistas; ++i)
	{
		Pista c = recuperar_registro_pista(i);
		sprintf(pistas_str, "%s%04d", c.id_pista, i);
		btree_insert(pistas_str, &pistas_idx);
	}

	printf(INDICE_CRIADO, "pistas_idx");
}

void criar_corridas_idx()
{
	/* IMPLEMENTAR A FUNÇÃO AQUI */
	char corridas_str[TAM_CHAVE_CORRIDAS_IDX + 1];
	for (unsigned i = 0; i < qtd_registros_corridas; ++i)
	{
		Corrida c = recuperar_registro_corrida(i);
		sprintf(corridas_str, "%s%s%04d", c.ocorrencia, c.id_pista, i);
		btree_insert(corridas_str, &corridas_idx);
	}

	printf(INDICE_CRIADO, "corridas_idx");
}

void criar_nome_pista_idx()
{
	/* IMPLEMENTAR A FUNÇÃO AQUI */
	char nome_pista_str[TAM_CHAVE_NOME_PISTA_IDX + 1], buffer[TAM_MAX_NOME_PISTA];
	buffer[0] = '\0';
	for (unsigned i = 0; i < qtd_registros_pistas; ++i)
	{
		Pista c = recuperar_registro_pista(i);
		strcpy(buffer, c.nome);
		strupr(buffer);
		strpadright(buffer, '#', TAM_MAX_NOME_PISTA - 1); // Preenche com # ate o tamanho maximo da string
		sprintf(nome_pista_str, "%s%s", buffer, c.id_pista);
		btree_insert(nome_pista_str, &nome_pista_idx);
	}

	printf(INDICE_CRIADO, "nome_pista_idx");
}

void criar_preco_veiculo_idx()
{
	/* IMPLEMENTAR A FUNÇÃO AQUI */
	char preco_veiculo_str[TAM_CHAVE_PRECO_VEICULO_IDX + 1];
	for (unsigned i = 0; i < qtd_registros_veiculos; ++i)
	{
		Veiculo v = recuperar_registro_veiculo(i);
		sprintf(preco_veiculo_str, "%013.2lf%s", v.preco, v.id_veiculo);
		btree_insert(preco_veiculo_str, &preco_veiculo_idx);
	}

	printf(INDICE_CRIADO, "preco_veiculo_idx");
}

void criar_corredor_veiculos_idx()
{
	for (unsigned i = 0; i < qtd_registros_corredores; ++i)
	{
		Corredor v = recuperar_registro_corredor(i);
		for (unsigned k = 0; k < QTD_MAX_VEICULO; k++)
			if (strcmp(v.veiculos[k], "\0") != 0)
				inverted_list_insert(v.veiculos[k], v.id_corredor, &corredor_veiculos_idx);
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
	printf("%s, %s, %d, %d, %d, %.2lf\n", c.id_pista, c.nome, c.dificuldade, c.distancia, c.recorde, c.taxa_inscricao);
	return true;
}

bool exibir_corrida(int rrn)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (rrn < 0)
		return false;
	Corrida c = recuperar_registro_corrida(rrn);
	printf("%s, %s, %s, %s\n", c.ocorrencia, c.id_pista, c.id_corredores, c.id_veiculos);
	return true;
}

/* Exibe um registro com base na chave de um btree_node */
bool exibir_btree_corredores(char *chave)
{
	int rrn = atoi(chave + TAM_ID_CORREDOR - 1);
	return exibir_corredor(rrn);
}

bool exibir_btree_veiculos(char *chave)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	int rrn = atoi(chave + TAM_ID_VEICULO - 1);
	return exibir_veiculo(rrn);
}

bool exibir_btree_pistas(char *chave)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	int rrn = atoi(chave + TAM_ID_PISTA - 1);
	return exibir_pista(rrn);
}

bool exibir_btree_corridas(char *chave)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	int rrn = atoi(chave + TAM_DATETIME + TAM_ID_PISTA - 2);
	return exibir_corrida(rrn);
}

bool exibir_btree_nome_pista(char *chave)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char result[TAM_CHAVE_NOME_PISTA_IDX + 1];
	bool found = btree_search(result, true, chave + TAM_MAX_NOME_PISTA - 1, nome_pista_idx.rrn_raiz, &nome_pista_idx);
	if (found)
		return exibir_btree_pistas(result);
	return false;
}

bool exibir_btree_preco_veiculo(char *chave)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char result[TAM_CHAVE_PRECO_VEICULO_IDX + 1];
	bool found = btree_search(result, false, chave, preco_veiculo_idx.rrn_raiz, &preco_veiculo_idx);
	if (found)
	{
		int rrn = atoi(result + TAM_FLOAT_NUMBER + TAM_RRN_REGISTRO - 2 - 1);
		return exibir_veiculo(rrn);
	}

	return false;
}

/* Recupera do arquivo o registro com o RRN informado
 * e retorna os dados nas structs */
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
	/*IMPLEMENTE A FUNÇÃO AQUI*/
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
	a = strtok(NULL, ";");
	p.taxa_inscricao = atof(a);
	return p;
}

Corrida recuperar_registro_corrida(int rrn)
{
	Corrida c;
	/* IMPLEMENTE A FUNÇÃO AQUI */
	char temp[TAM_REGISTRO_CORRIDA + 1], *p;
	p = malloc(TAM_REGISTRO_CORRIDA * sizeof(char));
	strncpy(temp, ARQUIVO_CORRIDAS + (rrn * TAM_REGISTRO_CORRIDA), TAM_REGISTRO_CORRIDA);
	temp[TAM_REGISTRO_CORRIDA] = '\0';
	strncpy(p, temp, TAM_DATETIME - 1);
	p[TAM_DATETIME - 1] = '\0';
	strcpy(c.ocorrencia, p);
	strncpy(p, temp + TAM_DATETIME - 1, TAM_ID_PISTA - 1);
	p[TAM_ID_PISTA - 1] = '\0';
	strcpy(c.id_pista, p);
	strncpy(p, temp + TAM_DATETIME + TAM_ID_PISTA - 2, TAM_ID_CORREDORES - 1);
	p[TAM_ID_CORREDORES - 1] = '\0';
	strcpy(c.id_corredores, p);
	strcpy(c.id_veiculos, temp + TAM_DATETIME + TAM_ID_PISTA + TAM_ID_CORREDORES - 3);
	c.id_veiculos[TAM_ID_VEICULOS - 1] = '\0';
	free(p);
	return c;
}

/* Escreve em seu respectivo arquivo na posição informada (RRN) */
void escrever_registro_corredor(Corredor c, int rrn)
{
	char temp[TAM_REGISTRO_CORREDOR + 1], p[TAM_FLOAT_NUMBER];
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
	sprintf(v, "%013.2lf", p.taxa_inscricao);
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
	strcat(temp, i.ocorrencia);
	strcat(temp, i.id_pista);
	strcat(temp, i.id_corredores);
	strcat(temp, i.id_veiculos);
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
	bool found = btree_search(NULL, false, id_corredor, corredores_idx.rrn_raiz, &corredores_idx);
	if (!found)
	{
		strcpy(corredor.id_corredor, id_corredor);
		strcpy(corredor.nome, nome);
		strcpy(corredor.apelido, apelido);
		strcpy(corredor.cadastro, timestamp);
		corredor.saldo = atof("000000000000.00");
		for (int i = 0; i < QTD_MAX_VEICULO; i++)
			strcpy(corredor.veiculos[i], "\0");
		escrever_registro_corredor(corredor, qtd_registros_corredores);
		char buffer[TAM_CHAVE_CORREDORES_IDX + 1];
		sprintf(buffer, "%s%04d", id_corredor, qtd_registros_corredores);
		btree_insert(buffer, &corredores_idx);
		qtd_registros_corredores++;
		printf(SUCESSO);
	}

	else
		printf(ERRO_PK_REPETIDA, id_corredor);
}

void remover_corredor_menu(char *id_corredor)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	Corredor corredor;
	char aux[3] = "*|";
	char result[TAM_CHAVE_CORREDORES_IDX + 1];
	bool found = btree_search(result, false, id_corredor, corredores_idx.rrn_raiz, &corredores_idx);
	if (!found)
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	else
	{
		int rrn = atoi(result + TAM_ID_CORREDOR - 1);
		corredor = recuperar_registro_corredor(rrn);
		strncpy(corredor.id_corredor, aux, 2);
		escrever_registro_corredor(corredor, rrn);
		btree_delete(result, &corredores_idx);
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
	char result[TAM_CHAVE_CORREDORES_IDX + 1];
	bool found = btree_search(result, false, id_corredor, corredores_idx.rrn_raiz, &corredores_idx);
	if (!found)
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	else
	{
		if (valor <= 0)
			printf(ERRO_VALOR_INVALIDO);
		else
		{
			int rrn = atoi(result + TAM_ID_CORREDOR - 1);
			corredor = recuperar_registro_corredor(rrn);
			corredor.saldo += valor;
			escrever_registro_corredor(corredor, rrn);
			if (flag)
				printf(SUCESSO);
		}
	}
}

void comprar_veiculo_menu(char *id_corredor, char *id_veiculo)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	Corredor corredor;
	Veiculo veiculo;
	char result[TAM_CHAVE_CORREDORES_IDX + 1];
	bool found = btree_search(result, false, id_corredor, corredores_idx.rrn_raiz, &corredores_idx);
	if (!found)
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	else
	{
		char resultVeiculo[TAM_CHAVE_VEICULOS_IDX + 1];
		bool foundVeiculo = btree_search(resultVeiculo, false, id_veiculo, veiculos_idx.rrn_raiz, &veiculos_idx);
		if (!foundVeiculo)
			printf(ERRO_REGISTRO_NAO_ENCONTRADO);
		else
		{
			int rrnCorredor = atoi(result + TAM_ID_CORREDOR - 1);
			int rrnVeiculo = atoi(resultVeiculo + TAM_ID_VEICULO - 1);
			corredor = recuperar_registro_corredor(rrnCorredor);
			veiculo = recuperar_registro_veiculo(rrnVeiculo);
			if (corredor.saldo < veiculo.preco)
				printf(ERRO_SALDO_NAO_SUFICIENTE);
			else
			{
				for (int i = 0; i < QTD_MAX_VEICULO; i++)
					if (!strcmp(corredor.veiculos[i], veiculo.modelo))
					{
						printf(ERRO_VEICULO_REPETIDO, id_corredor, veiculo.id_veiculo);
						return;
					}

				for (int k = 0; k < QTD_MAX_VEICULO; k++)
				{
					if (!strcmp(corredor.veiculos[k], "\0"))
					{
						strcpy(corredor.veiculos[k], veiculo.modelo);
						k = 3;
					}
				}

				corredor.saldo -= veiculo.preco;
				escrever_registro_corredor(corredor, rrnCorredor);
				inverted_list_insert(veiculo.modelo, id_corredor, &corredor_veiculos_idx);
				printf(SUCESSO);
			}
		}
	}
}

void cadastrar_veiculo_menu(char *marca, char *modelo, char *poder, int velocidade, int aceleracao, int peso, double preco)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	Veiculo veiculo;
	char id_aux[8];
	sprintf(id_aux, "%07d", qtd_registros_veiculos);
	bool found = btree_search(NULL, false, id_aux, veiculos_idx.rrn_raiz, &veiculos_idx);
	if (!found)
	{
		strcpy(veiculo.id_veiculo, id_aux);
		strcpy(veiculo.marca, marca);
		strcpy(veiculo.modelo, modelo);
		strcpy(veiculo.poder, poder);
		veiculo.velocidade = velocidade;
		veiculo.aceleracao = aceleracao;
		veiculo.peso = peso;
		veiculo.preco = preco;
		escrever_registro_veiculo(veiculo, qtd_registros_veiculos);
		char buffer[TAM_CHAVE_VEICULOS_IDX + 1];
		buffer[0] = '\0';
		sprintf(buffer, "%s%04d", id_aux, qtd_registros_veiculos);
		btree_insert(buffer, &veiculos_idx);
		char buffer2[TAM_CHAVE_PRECO_VEICULO_IDX + 1];
		buffer2[0] = '\0';
		sprintf(buffer2, "%013.2lf%s", preco, id_aux);
		btree_insert(buffer2, &preco_veiculo_idx);
		qtd_registros_veiculos++;
		printf(SUCESSO);
	}

	else
		printf(ERRO_PK_REPETIDA, id_aux);
}

void cadastrar_pista_menu(char *nome, int dificuldade, int distancia, int recorde)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	Pista pista;
	char id_aux[9], aux[TAM_MAX_NOME_PISTA];
	sprintf(id_aux, "%08d", qtd_registros_pistas);
	strcpy(aux, nome);
	strupr(aux);
	bool found = btree_search(NULL, false, aux, nome_pista_idx.rrn_raiz, &nome_pista_idx);
	if (!found)
	{
		strcpy(pista.id_pista, id_aux);
		strcpy(pista.nome, nome);
		pista.dificuldade = dificuldade;
		pista.distancia = distancia;
		pista.recorde = recorde;
		pista.taxa_inscricao = TX_FIXA * dificuldade;
		escrever_registro_pista(pista, qtd_registros_pistas);
		char buffer[TAM_CHAVE_PISTAS_IDX + 1];
		buffer[0] = '\0';
		sprintf(buffer, "%s%04d", id_aux, qtd_registros_pistas);
		btree_insert(buffer, &pistas_idx);
		char buffer2[TAM_CHAVE_NOME_PISTA_IDX + 1];
		buffer2[0] = '\0';
		strpadright(aux, '#', TAM_MAX_NOME_PISTA - 1);
		sprintf(buffer2, "%s%s", aux, id_aux);
		btree_insert(buffer2, &nome_pista_idx);
		qtd_registros_pistas++;
		printf(SUCESSO);
	}

	else
		printf(ERRO_PK_REPETIDA, nome);
}

void executar_corrida_menu(char *id_pista, char *ocorrencia, char *id_corredores, char *id_veiculos)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	Pista pista;
	Corrida corrida;
	Corredor corredor, corredores[6];
	Veiculo veiculo;
	char c[6][TAM_ID_CORREDOR - 1], v[6][TAM_ID_VEICULO], pk[25];
	char corridas_str[TAM_CHAVE_CORRIDAS_IDX + 1];
	strcpy(corridas_str, ocorrencia);
	strcat(corridas_str, id_pista);
	bool err = false;
	bool found = btree_search(NULL, false, corridas_str, corridas_idx.rrn_raiz, &corridas_idx);
	char resultPista[TAM_CHAVE_PISTAS_IDX + 1];
	bool found_p = btree_search(resultPista, false, id_pista, pistas_idx.rrn_raiz, &pistas_idx);
	if (!found)
	{
		for (unsigned i = 0; i < 6; ++i)
		{
			bool dono_veiculo = false;
			char resultCorredor[TAM_CHAVE_CORREDORES_IDX + 1];
			strncpy(c[i], id_corredores + (i * (TAM_ID_CORREDOR - 1)), TAM_ID_CORREDOR - 1);
			bool found_c = btree_search(resultCorredor, false, c[i], corredores_idx.rrn_raiz, &corredores_idx);
			char resultVeiculo[TAM_CHAVE_VEICULOS_IDX + 1];
			strncpy(v[i], id_veiculos + (i * (TAM_ID_VEICULO - 1)), TAM_ID_VEICULO - 1);
			v[i][TAM_ID_VEICULO - 1] = '\0';
			bool found_v = btree_search(resultVeiculo, false, v[i], veiculos_idx.rrn_raiz, &veiculos_idx);
			if (found_c && found_v && found_p)
			{
				int rrnCorredor = atoi(resultCorredor + TAM_ID_CORREDOR - 1);
				corredor = recuperar_registro_corredor(rrnCorredor);
				int rrnVeiculo = atoi(resultVeiculo + TAM_ID_VEICULO - 1);
				veiculo = recuperar_registro_veiculo(rrnVeiculo);
				for (unsigned k = 0; k < QTD_MAX_VEICULO; ++k)
					if (!strcmp(corredor.veiculos[k], veiculo.modelo))
						dono_veiculo = true;
				if (!dono_veiculo)
				{
					printf(ERRO_CORREDOR_VEICULO, corredor.id_corredor, veiculo.id_veiculo);
					err = true;
				}

				corredores[i] = corredor;
			}

			else
			{
				printf(ERRO_REGISTRO_NAO_ENCONTRADO);
				return;
			}
		}

		if (!err)
		{
			strcpy(corrida.id_pista, id_pista);
			strcpy(corrida.ocorrencia, ocorrencia);
			strcpy(corrida.id_corredores, id_corredores);
			strcpy(corrida.id_veiculos, id_veiculos);
			int rrnPista = atoi(resultPista + TAM_ID_PISTA - 1);
			pista = recuperar_registro_pista(rrnPista);
			double premio = 6 * (TX_FIXA * pista.dificuldade);
			adicionar_saldo(corredores[0].id_corredor, premio * 0.4, false);
			adicionar_saldo(corredores[1].id_corredor, premio * 0.3, false);
			adicionar_saldo(corredores[2].id_corredor, premio * 0.2, false);
			escrever_registro_corrida(corrida, qtd_registros_corridas);
			char corridas_str[TAM_CHAVE_CORRIDAS_IDX + 1];
			sprintf(corridas_str, "%s%s%04d", ocorrencia, id_pista, qtd_registros_corridas);
			btree_insert(corridas_str, &corridas_idx);
			qtd_registros_corridas++;
			printf(SUCESSO);
		}
	}

	else
	{
		sprintf(pk, "%s%s", ocorrencia, id_pista);
		printf(ERRO_PK_REPETIDA, pk);
	}
}

/* Busca */
void buscar_corredor_id_menu(char *id_corredor)
{
	char result[TAM_CHAVE_CORREDORES_IDX + 1];
	printf(RRN_NOS);
	bool found = btree_search(result, true, id_corredor, corredores_idx.rrn_raiz, &corredores_idx);
	printf("\n");
	if (!found)
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	else
		exibir_corredor(atoi(result + TAM_ID_CORREDOR - 1));
}

void buscar_pista_id_menu(char *id_pista)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char result[TAM_CHAVE_PISTAS_IDX + 1];
	printf(RRN_NOS);
	bool found = btree_search(result, true, id_pista, pistas_idx.rrn_raiz, &pistas_idx);
	printf("\n");
	if (!found)
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	else
		exibir_pista(atoi(result + TAM_ID_PISTA - 1));
}

void buscar_pista_nome_menu(char *nome_pista)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char result[TAM_CHAVE_NOME_PISTA_IDX + 1];
	char aux[TAM_MAX_NOME_PISTA];
	printf(RRN_NOS);
	bool found = btree_search(result, true, strupr(nome_pista), nome_pista_idx.rrn_raiz, &nome_pista_idx);
	printf("\n");
	if (!found)
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	else
	{
		strcpy(aux, result + TAM_MAX_NOME_PISTA - 1);
		int rrn = atoi(result + TAM_MAX_NOME_PISTA - 1);
		printf(RRN_NOS);
		bool found2 = btree_search(NULL, true, aux, pistas_idx.rrn_raiz, &pistas_idx);
		printf("\n");
		if (!found2)
			printf(ERRO_REGISTRO_NAO_ENCONTRADO);
		else
			exibir_pista(rrn);
	}
}

/* Listagem */
void listar_corredores_id_menu()
{
	if (qtd_registros_corredores == 0)
		printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
	else
		btree_print_in_order(NULL, NULL, exibir_btree_corredores, corredores_idx.rrn_raiz, &corredores_idx);
}

void listar_corredores_modelo_menu(char *modelo)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	printf(ERRO_NAO_IMPLEMENTADO, "listar_corredores_modelo_menu");
}

void listar_veiculos_compra_menu(char *id_corredor)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (qtd_registros_veiculos == 0)
		printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
	else
	{
		Corredor corredor;
		char result[TAM_CHAVE_CORREDORES_IDX + 1];
		bool found = btree_search(result, false, id_corredor, corredores_idx.rrn_raiz, &corredores_idx);
		if (!found)
			printf(ERRO_REGISTRO_NAO_ENCONTRADO);
		else
		{
			int rrn = atoi(result + TAM_ID_CORREDOR - 1);
			corredor = recuperar_registro_corredor(rrn);
			char aux[TAM_FLOAT_NUMBER];
			sprintf(aux, "%013.2lf", corredor.saldo);
			btree_print_in_order(NULL, aux, exibir_btree_preco_veiculo, preco_veiculo_idx.rrn_raiz, &preco_veiculo_idx);
		}
	}
}

void listar_corridas_periodo_menu(char *data_inicio, char *data_fim)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (btree_print_in_order(data_inicio, data_fim, exibir_btree_corridas, corridas_idx.rrn_raiz, &corridas_idx) == 0)
		printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
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
		if (strncmp(temp, "*|", 2) == 0) // ignora registros removidos
			continue;
		else
		{
			strncpy(ARQUIVO_CORREDORES_AUX + k * TAM_REGISTRO_CORREDOR, temp, TAM_REGISTRO_CORREDOR); // copia o registro para o arquivo auxiliar
			k++;
		}
	}

	qtd_registros_corredores = k;
	strcpy(ARQUIVO_CORREDORES, ARQUIVO_CORREDORES_AUX);
	corredores_idx.qtd_nos = 0;
	corredores_idx.rrn_raiz = -1;
	for (int i = 0; i < TAM_ARQUIVO_CORREDORES_IDX; i++)
		corredores_idx.arquivo[i] = '\0';
	for (int i = 0; i < qtd_registros_corredores; i++) // refaz o indice
	{
		Corredor c = recuperar_registro_corredor(i);
		char buffer[TAM_CHAVE_CORREDORES_IDX + 1];
		buffer[0] = '\0';
		sprintf(buffer, "%s%04d", c.id_corredor, i);
		btree_insert(buffer, &corredores_idx);
	}

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
	if (corredores_idx.qtd_nos == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_CORREDORES_IDX);
}

void imprimir_veiculos_idx_menu()
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (veiculos_idx.qtd_nos == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_VEICULOS_IDX);
}

void imprimir_pistas_idx_menu()
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (pistas_idx.qtd_nos == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_PISTAS_IDX);
}

void imprimir_corridas_idx_menu()
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (corridas_idx.qtd_nos == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_CORRIDAS_IDX);
}

/* Imprimir índices secundários */
void imprimir_nome_pista_idx_menu()
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (nome_pista_idx.qtd_nos == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_NOME_PISTA_IDX);
}

void imprimir_preco_veiculo_idx_menu()
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (preco_veiculo_idx.qtd_nos == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_PRECO_VEICULO_IDX);
}

void imprimir_corredor_veiculos_secundario_idx_menu()
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (corredor_veiculos_idx.qtd_registros_secundario == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_CORREDOR_VEICULO_SECUNDARIO_IDX);
}

void imprimir_corredor_veiculos_primario_idx_menu()
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (corredor_veiculos_idx.qtd_registros_primario == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_CORREDOR_VEICULO_PRIMARIO_IDX);
}

/* Funções de manipulação de Lista Invertida */
/**
 * Responsável por inserir duas chaves (chave_secundaria e chave_primaria) em uma Lista Invertida (t).<br />
 * Atualiza os parâmetros dos índices primário e secundário conforme necessário.<br />
 * As chaves a serem inseridas devem estar no formato correto e com tamanho t->tam_chave_primario e t->tam_chave_secundario.<br />
 * O funcionamento deve ser genérico para qualquer Lista Invertida, adaptando-se para os diferentes parâmetros presentes em seus structs.<br />
 *
 * @param chave_secundaria Chave a ser buscada (caso exista) ou inserida (caso não exista) no registro secundário da Lista Invertida.
 * @param chave_primaria Chave a ser inserida no registro primário da Lista Invertida.
 * @param t Ponteiro para a Lista Invertida na qual serão inseridas as chaves.
 */
void inverted_list_insert(char *chave_secundaria, char *chave_primaria, inverted_list *t)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	int rrn, idx;
	char next[TAM_RRN_REGISTRO + 1];
	char sec[TAM_MAX_MODELO];
	char qtd_primaria[TAM_RRN_REGISTRO + 1];
	strcpy(sec, chave_secundaria);
	strupr(sec);
	bool found = inverted_list_secondary_search(&rrn, false, strupr(chave_secundaria), t);
	if (found) // se a chave secundaria ja existe no indice secundario entao so adiciona a chave primaria no indice primario
	{
		inverted_list_primary_search(NULL, false, rrn, &idx, t);
		sprintf(next, "%04d", t->qtd_registros_primario);
		strncpy(t->arquivo_primario + idx * (t->tam_chave_primaria + TAM_RRN_REGISTRO) + t->tam_chave_primaria, next, TAM_RRN_REGISTRO);
	}

	else // se a chave secundaria nao existe no indice secundario entao adiciona a chave secundaria e a chave primaria
	{
		strcpy(sec, chave_secundaria);
		strupr(sec);
		strpadright(sec, '#', t->tam_chave_secundaria);
		strcpy(t->arquivo_secundario + (t->qtd_registros_secundario * (t->tam_chave_secundaria + TAM_RRN_REGISTRO)), sec);
		sprintf(qtd_primaria, "%04d", t->qtd_registros_primario);
		strcpy(t->arquivo_secundario + (t->qtd_registros_secundario * (t->tam_chave_secundaria + TAM_RRN_REGISTRO)) + t->tam_chave_secundaria, qtd_primaria);
		t->qtd_registros_secundario++;
		qsort(t->arquivo_secundario, t->qtd_registros_secundario, t->tam_chave_secundaria + TAM_RRN_REGISTRO, t->compar);
	}

	strcpy(t->arquivo_primario + (t->qtd_registros_primario * (t->tam_chave_primaria + TAM_RRN_REGISTRO)), chave_primaria);
	sprintf(next, "%04d", -1);
	strcpy(t->arquivo_primario + (t->qtd_registros_primario * (t->tam_chave_primaria + TAM_RRN_REGISTRO)) + t->tam_chave_primaria, next);
	t->qtd_registros_primario++;
}

/**
 * Responsável por buscar uma chave no índice secundário de uma Lista invertida (T). O valor de retorno indica se a chave foi encontrada ou não.
 * O ponteiro para o int result pode ser fornecido opcionalmente, e conterá o índice inicial das chaves no registro primário.<br />
 * <br />
 * Exemplos de uso:<br />
 * <code>
 * // Exemplo 1. A chave encontrada deverá ser retornada e o caminho não deve ser informado.<br />
 * ...<br />
 * int result;<br />
 * bool found = inverted_list_secondary_search(&result, false, modelo, &corredor_veiculos_idx);<br />
 * ...<br />
 * <br />
 * // Exemplo 2. Não há interesse na chave encontrada, apenas se ela existe, e o caminho não deve ser informado.<br />
 * ...<br />
 * bool found = inverted_list_secondary_search(NULL, false, modelo, &corredor_veiculos_idx);<br />
 * ...<br />
 * <br />
 * // Exemplo 3. Há interesse no caminho feito para encontrar a chave.<br />
 * ...<br />
 * int result;<br />
 * bool found = inverted_list_secondary_search(&result, true, modelo, &corredor_veiculos_idx);<br />
 * </code>
 *
 * @param result Ponteiro para ser escrito o índice inicial (primeira ocorrência) das chaves do registro primário. É ignorado caso NULL.
 * @param exibir_caminho Indica se o caminho percorrido deve ser impresso.
 * @param chave_secundaria Chave a ser buscada.
 * @param t Ponteiro para o índice do tipo Lista invertida no qual será buscada a chave.
 * @return Indica se a chave foi encontrada.
 */
bool inverted_list_secondary_search(int *result, bool exibir_caminho, char *chave_secundaria, inverted_list *t)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	int idx;
	char rrn[TAM_RRN_REGISTRO + 1];
	bool found = inverted_list_binary_search(&idx, exibir_caminho, chave_secundaria, t);
	if (!found)
		return false;
	else
	{
		strncpy(rrn, t->arquivo_secundario + (idx * (t->tam_chave_secundaria + TAM_RRN_REGISTRO)) + t->tam_chave_secundaria, TAM_RRN_REGISTRO);
		rrn[TAM_RRN_REGISTRO] = '\0';
		if (result)
			*result = atoi(rrn);
		return true;
	}
}

/**
 * Responsável por percorrer o índice primário de uma Lista invertida (T). O valor de retorno indica a quantidade de chaves encontradas.
 * O ponteiro para o vetor de strings result pode ser fornecido opcionalmente, e será populado com a lista de todas as chaves encontradas.
 * O ponteiro para o inteiro indice_final também pode ser fornecido opcionalmente, e deve conter o índice do último campo da lista encadeada
 * da chave primaria fornecida (isso é útil na inserção de um novo registro).<br />
 * <br />
 * Exemplos de uso:<br />
 * <code>
 * // Exemplo 1. As chaves encontradas deverão ser retornadas e tanto o caminho quanto o indice_final não devem ser informados.<br />
 * ...<br />
 * char chaves[TAM_CHAVE_CORREDOR_VEICULO_PRIMARIO_IDX][MAX_REGISTROS];<br />
 * int qtd = inverted_list_primary_search(chaves, false, indice, NULL, &corredor_veiculos_idx);<br />
 * ...<br />
 * <br />
 * // Exemplo 2. Não há interesse nas chaves encontradas, apenas no indice_final, e o caminho não deve ser informado.<br />
 * ...<br />
 * int indice_final;
 * int qtd = inverted_list_primary_search(NULL, false, indice, &indice_final, &ccorredor_veiculos_idx);<br />
 * ...<br />
 * <br />
 * // Exemplo 3. Há interesse nas chaves encontradas e no caminho feito.<br />
 * ...<br />
 * char chaves[TAM_CHAVE_CORREDOR_VEICULO_PRIMARIO_IDX][MAX_REGISTROS];<br />
 * int qtd = inverted_list_primary_search(chaves, true, indice, NULL, &corredor_veiculos_idx);<br />
 * ...<br />
 * <br />
 * </code>
 *
 * @param result Ponteiro para serem escritas as chaves encontradas. É ignorado caso NULL.
 * @param exibir_caminho Indica se o caminho percorrido deve ser impresso.
 * @param indice Índice do primeiro registro da lista encadeada a ser procurado.
 * @param indice_final Ponteiro para ser escrito o índice do último registro encontrado (cujo campo indice é -1). É ignorado caso NULL.
 * @param t Ponteiro para o índice do tipo Lista invertida no qual será buscada a chave.
 * @return Indica a quantidade de chaves encontradas.
 */
int inverted_list_primary_search(char result[][TAM_CHAVE_CORREDOR_VEICULO_PRIMARIO_IDX], bool exibir_caminho, int indice, int *indice_final, inverted_list *t)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	int idx = indice, keys = 0;
	char rrn[TAM_RRN_REGISTRO + 1];
	if (exibir_caminho)
		printf(REGS_PERCORRIDOS);
	while (idx != -1)
	{
		if (exibir_caminho)
			printf(" %d", idx);
		if (result)
			strncpy(result[keys], t->arquivo_primario + (idx * (t->tam_chave_primaria + TAM_RRN_REGISTRO)), t->tam_chave_primaria);
		if (idx != -1)
			if (indice_final)
				*indice_final = idx;
		strncpy(rrn, t->arquivo_primario + (idx * (t->tam_chave_primaria + TAM_RRN_REGISTRO)) + t->tam_chave_primaria, TAM_RRN_REGISTRO);
		idx = atoi(rrn);
		keys++;
	}

	if (exibir_caminho)
		printf("\n");
	return keys;
}

/**
 * Responsável por buscar uma chave (k) dentre os registros secundários de uma Lista Invertida de forma eficiente.<br />
 * O valor de retorno deve indicar se a chave foi encontrada ou não.
 * O ponteiro para o int result pode ser fornecido opcionalmente, e conterá o índice no registro secundário da chave encontrada.<br />
 *
 * @param result Ponteiro para ser escrito o índice nos registros secundários da chave encontrada. É ignorado caso NULL.
 * @param exibir_caminho Indica se o caminho percorrido deve ser impresso.
 * @param chave Chave a ser buscada na Lista Invertida.
 * @param t Ponteiro para o índice da Lista Invertida no qual será buscada a chave.
 * @return Indica se a chave foi encontrada.
 */
bool inverted_list_binary_search(int *result, bool exibir_caminho, char *chave, inverted_list *t) // busca binaria no arquivo secundario
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	int imin = 0, imax = t->qtd_registros_secundario - 1, imid = 0;
	char chave_aux[t->tam_chave_secundaria + 1];
	chave_aux[t->tam_chave_secundaria] = '\0';
	if (exibir_caminho)
		printf(REGS_PERCORRIDOS);
	while (imin <= imax)
	{
		imid = imin + (imax - imin + 1) / 2;																																												// calcula o indice do meio
		strncpy(chave_aux, t->arquivo_secundario + (imid * (t->tam_chave_secundaria + TAM_RRN_REGISTRO)), t->tam_chave_secundaria); // copia a chave do meio
		chave_aux[t->tam_chave_secundaria] = '\0';
		int res = t->compar(chave, chave_aux);
		if (exibir_caminho)
			printf(" %d", imid);
		if (res > 0)
			imin = imid + 1;
		else if (res < 0)
			imax = imid - 1;
		else
		{
			if (exibir_caminho)
				printf("\n");
			if (result)
				*result = imid;
			return true;
		}
	}

	if (exibir_caminho)
		printf("\n");
	return false;
}

/* Funções de manipulação de Árvores-B */
/**
 * Responsável por inserir uma chave (k) em uma Árvore-B (T). Atualiza os parâmetros da Árvore-B conforme necessário.<br />
 * A chave a ser inserida deve estar no formato correto e com tamanho t->tam_chave.<br />
 * O funcionamento deve ser genérico para qualquer Árvore-B, considerando que os únicos parâmetros que se alteram entre
 * as árvores é o t->tam_chave.<br />
 * <br />
 * Exemplo de uso:<br />
 * <code>
 * ...<br />
 * char corredor_str[TAM_CHAVE_CORREDORES_IDX + 1];<br />
 * sprintf(corredor_str, "%s%04d", id_corredor, rrn_corredor);<br />
 * btree_insert(corredor_str, &corredores_idx);<br />
 * ...<br />
 * </code>
 *
 * @param chave Chave a ser inserida na Árvore-B.
 * @param t Ponteiro para o índice do tipo Árvore-B no qual será inserida a chave.
 */
/* Funções de manipulação de Árvores-B */
void btree_insert(char *chave, btree *t)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (!t->qtd_nos) // se a arvore estiver vazia
	{
		btree_node node = btree_node_malloc(t);
		node.folha = true;
		t->rrn_raiz = 0;
		t->qtd_nos = 1;
		node.qtd_chaves = 1;
		node.this_rrn = 0;
		strcpy(node.chaves[0], chave);
		btree_write(node, t);
		btree_node_free(node);
	}

	else
	{
		promovido_aux p = btree_insert_aux(chave, t->rrn_raiz, t); // insere na folha
		if (p.chave_promovida[0] != '\0')													 // overflow na raiz
		{
			btree_node node = btree_node_malloc(t);
			node.folha = false;
			node.qtd_chaves = 1;
			strcpy(node.chaves[0], p.chave_promovida);
			node.filhos[0] = t->rrn_raiz;
			node.filhos[1] = p.filho_direito;
			t->rrn_raiz = t->qtd_nos; // atualiza o rrn da raiz
			t->qtd_nos++;
			node.this_rrn = t->rrn_raiz;
			btree_write(node, t);
			btree_node_free(node);
		}
	}
}

/**
 * Função auxiliar de inserção de uma chave (k) em uma Árvore-B (T). Atualiza os parâmetros da Árvore-B conforme necessário.<br />
 * Esta é uma função recursiva. Ela recebe o RRN do nó a ser trabalhado sobre.<br />
 *
 * @param chave Chave a ser inserida na Árvore-B.
 * @param rrn RRN do nó no qual deverá ser processado.
 * @param t Ponteiro para o índice do tipo Árvore-B no qual será inserida a chave.
 * @return Retorna uma struct do tipo promovido_aux que contém a chave promovida e o RRN do filho direito.
 */
promovido_aux btree_insert_aux(char *chave, int rrn, btree *t)
{
	promovido_aux p;
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	int i;
	p.chave_promovida[0] = '\0';
	if (rrn == -1)
	{
		p.chave_promovida[0] = '\0';
		p.filho_direito = -1;
		return p; // return null
	}

	btree_node node = btree_read(rrn, t);
	btree_binary_search(&i, false, chave, &node, t); // indice da chave onde deve ser inserida
	p.filho_direito = -1;
	if (node.folha)
	{
		if (node.qtd_chaves < btree_order - 1) // se tem espaço na folha pra inserir
		{
			for (int j = node.qtd_chaves; j > i; j--) // desloca as chaves para a direita
			{
				strncpy(node.chaves[j], node.chaves[j - 1], t->tam_chave);
				node.chaves[j][t->tam_chave] = '\0';
			}

			strncpy(node.chaves[i], chave, t->tam_chave);
			node.chaves[i][t->tam_chave] = '\0';
			node.qtd_chaves++;
			btree_write(node, t);
			btree_node_free(node);
			return p; // return null
		}

		else // se não tem espaço na folha pra inserir (overflow)
		{
			strncpy(p.chave_promovida, chave, t->tam_chave);
			p.chave_promovida[t->tam_chave] = '\0';
			p = btree_divide(p, &node, i, t); // divide a folha
			return p;
		}
	}

	else // se não é folha
	{
		p = btree_insert_aux(chave, node.filhos[i], t); // insere na folha
		if (p.chave_promovida[0] != '\0')
		{
			if (node.qtd_chaves < btree_order - 1) // se tem espaço na folha pra inserir
			{
				for (int j = node.qtd_chaves; j > i; j--) // desloca as chaves para a direita
				{
					strncpy(node.chaves[j], node.chaves[j - 1], t->tam_chave);
					node.filhos[j + 1] = node.filhos[j];
					node.chaves[j][t->tam_chave] = '\0';
				}

				strncpy(node.chaves[i], p.chave_promovida, t->tam_chave);
				node.chaves[i][t->tam_chave] = '\0';
				node.filhos[i + 1] = p.filho_direito;
				node.qtd_chaves++;
				btree_write(node, t);
				btree_node_free(node);
				p.chave_promovida[0] = '\0';
			}

			else
			{
				p = btree_divide(p, &node, i, t); // divide a folha
				return p;
			}
		}
	}

	return p;
}

/**
 * Função auxiliar para dividir um nó de uma Árvore-B (T). Atualiza os parâmetros conforme necessário.<br />
 *
 * @param promo Uma struct do tipo promovido_aux que contém a chave a ser inserida e o RRN do seu filho direito.
 * @param node Ponteiro para nó que deve ser dividido.
 * @param i O índice da posição onde a chave a ser inserida deve estar.
 * @param t Ponteiro para o índice do tipo Árvore-B no qual será inserida a chave.
 * @return Retorna uma struct do tipo promovido_aux que contém a chave promovida e o RRN do filho direito.
 */
promovido_aux btree_divide(promovido_aux promo, btree_node *node, int i, btree *t)
{
	/* <<< COMPLETE AQUI A IMPLEMENTAÇÃO >>> */
	btree_node new_node = btree_node_malloc(t);
	new_node.qtd_chaves = 0;				// inicializa o novo nó
	new_node.this_rrn = t->qtd_nos; // atualiza o rrn do novo nó
	t->qtd_nos++;										// atualiza a quantidade de nós
	new_node.folha = node->folha;
	// Inserindo chave nova.
	if (i > btree_order / 2)
	{ // se a chave nova deve ser inserida no novo nó
		strcpy(new_node.chaves[0], promo.chave_promovida);
		new_node.filhos[0] = node->filhos[node->qtd_chaves];
		new_node.filhos[1] = promo.filho_direito;
		new_node.qtd_chaves++;
		node->filhos[node->qtd_chaves] = -1;
		strcpy(promo.chave_promovida, node->chaves[node->qtd_chaves - 1]);
		node->qtd_chaves--;
		promo.filho_direito = new_node.this_rrn;
	}

	else
	{ // se a chave nova deve ser inserida no nó antigo
		strcpy(new_node.chaves[0], node->chaves[node->qtd_chaves - 1]);
		new_node.filhos[0] = node->filhos[node->qtd_chaves - 1];
		node->filhos[node->qtd_chaves - 1] = -1;
		new_node.filhos[1] = node->filhos[node->qtd_chaves];
		node->filhos[node->qtd_chaves] = -1;
		node->qtd_chaves--;
		new_node.qtd_chaves++;
		for (int j = node->qtd_chaves; j > i; j--)
		{
			strcpy(node->chaves[j], node->chaves[j - 1]);
			node->filhos[j + 1] = node->filhos[j];
		}

		strcpy(node->chaves[i], promo.chave_promovida);
		node->filhos[i + 1] = promo.filho_direito;
		node->qtd_chaves++;
		strcpy(promo.chave_promovida, node->chaves[node->qtd_chaves - 1]);
		node->qtd_chaves--;
		promo.filho_direito = new_node.this_rrn;
	}

	btree_write(*node, t);
	btree_write(new_node, t);
	btree_node_free(new_node);
	return promo;
}

/**
 * Responsável por remover uma chave (k) de uma Árvore-B (T). Atualiza os parâmetros da Árvore-B conforme necessário.<br />
 * A chave a ser removida deve estar no formato correto e com tamanho t->tam_chave.<br />
 * O funcionamento deve ser genérico para qualquer Árvore-B, considerando que os únicos parâmetros que se alteram entre
 * as árvores é o t->tam_chave.<br />
 * <br />
 * Exemplo de uso:<br />
 * <code>
 * ...<br />
 * char corredor_str[TAM_CHAVE_USUARIOS_IDX + 1];<br />
 * sprintf(corredor_str, "%s%04d", id_corredor, rrn_corredor);<br />
 * btree_delete(corredor_str, &corredores_idx);<br />
 * ...<br />
 * </code>
 *
 * @param chave Chave a ser removida da Árvore-B.
 * @param t Ponteiro para o índice do tipo Árvore-B do qual será removida a chave.
 */
void btree_delete(char *chave, btree *t)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (t->qtd_nos)
	{
		bool under = btree_delete_aux(chave, t->rrn_raiz, t);
		if (under) // se a raiz ficou com menos chaves que o mínimo necessário
			t->rrn_raiz = 0;
	}
}

/**
 * Função auxiliar de remoção de uma chave (k) de uma Árvore-B (T). Atualiza os parâmetros da Árvore-B conforme necessário.<br />
 * Esta é uma função recursiva. Ela recebe o RRN do nó a ser trabalhado sobre.<br />
 *
 * @param chave Chave a ser removida da Árvore-B.
 * @param rrn RRN do nó no qual deverá ser processado.
 * @param t Ponteiro para o índice do tipo Árvore-B do qual será removida a chave.
 * @return Indica se a remoção deixou o nó que foi processado com menos chaves que o mínimo necessário.
 */
bool btree_delete_aux(char *chave, int rrn, btree *t)
{
	/* IMPLEMENTE A FUNÇÃO AQUI */
	int i;
	if (rrn == -1)
		return false;
	btree_node no = btree_read(rrn, t);
	bool found = btree_binary_search(&i, false, chave, &no, t); // indice da chave onde deve ser inserida
	if (!found)
	{
		if (btree_delete_aux(chave, no.filhos[i], t)) // se a chave não foi encontrada, busca no filho
			return btree_borrow_or_merge(&no, i, t);		// se o filho ficou com menos chaves que o mínimo necessário, faz o empréstimo ou a concatenação
	}

	else
	{
		if (no.folha) // se a chave foi encontrada e é folha
		{
			if (i != no.qtd_chaves - 1) // se a chave não é a última
				for (int j = i + 1; j < no.qtd_chaves; j++)
					strcpy(no.chaves[j - 1], no.chaves[j]);
			no.qtd_chaves--;
			btree_write(no, t);															// Escreve o nó atualizado no arquivo.
			return (no.qtd_chaves < (btree_order - 1) / 2); // se o nó ficou com menos chaves que o mínimo necessário, retorna true
		}

		else
		{
			btree_node new_node = btree_read(no.filhos[i], t);														 // se a chave foi encontrada e não é folha, busca o predecessor
			strncpy(no.chaves[i], new_node.chaves[new_node.qtd_chaves - 1], t->tam_chave); // substitui a chave pelo predecessor
			btree_write(no, t);																														 // Escreve o nó atualizado no arquivo.
			btree_node_free(new_node);
			if (btree_delete_aux(no.chaves[i], no.filhos[i], t)) // se o predecessor ficou com menos chaves que o mínimo necessário
				return btree_borrow_or_merge(&no, i, t);					 // faz o borrow ou merge
		}
	}

	btree_node_free(no);
	return false;
}

/**
 * Função auxiliar para redistribuir ou concatenar nós irmãos adjacentes à esquerda e à direita de um nó pai em uma Árvore-B (T).
 * Atualiza os parâmetros conforme necessário.<br />
 *
 * @param node Ponteiro para nó pai dos nós irmãos adjacentes que deve ser redistribuidos ou concatenados.
 * @param i O índice da posição no nó pai onde se encontra a chave separadora dos nós irmãos adjacentes.
 * @param t Ponteiro para o índice do tipo Árvore-B no qual serão redistribuídos ou concatenados os nós irmãos adjacentes.
 * @return Indica se a redistribuição ou concatenação deixou o nó pai com menos chaves que o mínimo necessário.
 */
bool btree_borrow_or_merge(btree_node *node, int i, btree *t) // Discutido com caike
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	btree_node node_right = btree_read(node->filhos[i + 1], t);
	btree_node node_left = btree_read(node->filhos[i - 1], t);
	if (i + 1 < btree_order && i >= 0) // caso borrow direito
	{
		if (node->filhos[i + 1] != -1)
		{
			if (node_right.qtd_chaves > ((btree_order - 1) / 2)) // se o nó da direita tem mais chaves que o mínimo necessário
			{
				btree_node aux = btree_read(node->filhos[i], t);
				strcpy(aux.chaves[aux.qtd_chaves], node->chaves[i]);
				strcpy(node->chaves[i], node_right.chaves[0]);
				for (int j = node_right.qtd_chaves - 1; j > 0; j--)
					strcpy(node_right.chaves[j - 1], node_right.chaves[j]);
				node_right.qtd_chaves--;
				aux.qtd_chaves++;
				free_and_write(node, &aux, &node_right, &node_left, t);
				return false;
			}
		}

		if (node->filhos[i - 1] != -1) // caso borrow esquerdo
		{
			if (node_left.qtd_chaves > ((btree_order - 1) / 2)) // se o nó da esquerda tem mais chaves que o mínimo necessário
			{
				btree_node aux = btree_read(node->filhos[i], t);
				for (int j = aux.qtd_chaves - 1; j > 0; j--)
					strcpy(aux.chaves[j + 1], aux.chaves[j]);
				strcpy(aux.chaves[0], node->chaves[i - 1]);
				strcpy(node->chaves[i - 1], node_left.chaves[node_left.qtd_chaves - 1]);
				node_left.qtd_chaves--;
				aux.qtd_chaves++;
				free_and_write(node, &aux, &node_left, &node_right, t);
				return false;
			}
		}

		if (node->filhos[i + 1] != -1) // caso merge direito
		{
			btree_node aux = btree_read(node->filhos[i], t);
			strcpy(aux.chaves[aux.qtd_chaves], node->chaves[i]);
			aux.qtd_chaves += 1;
			for (int j = i; j < node->qtd_chaves - 1; j++)
				strcpy(node->chaves[j], node->chaves[j + 1]);
			for (int j = 0; j < node_right.qtd_chaves; j++)
			{
				strcpy(aux.chaves[aux.qtd_chaves], node_right.chaves[j]);
				aux.filhos[aux.qtd_chaves + 1] = node_right.filhos[j + 1];
				aux.qtd_chaves++;
			}

			node->qtd_chaves -= 1;
			if (!node->qtd_chaves)
				for (int i = 0; i <= btree_order; i++)
					node->filhos[i] = -1;
			else
			{
				node->filhos[i + 1] = -1;
			}

			node_right.qtd_chaves = 0;
			t->qtd_nos -= 1;
			free_and_write(node, &aux, &node_right, &node_left, t);
			return node->qtd_chaves < ((btree_order - 1) / 2);
		}

		else if (node->filhos[i - 1] != -1) // caso merge esquerdo
		{
			btree_node aux = btree_read(node->filhos[i], t);
			strcpy(node_left.chaves[node_left.qtd_chaves], node->chaves[i]);
			node_left.qtd_chaves += 1;
			for (int j = i; j < node->qtd_chaves - 1; j++)
				strcpy(node->chaves[j], node->chaves[j + 1]);
			for (int j = 0; j < node_right.qtd_chaves; j++)
			{
				strcpy(node_left.chaves[aux.qtd_chaves], aux.chaves[j]);
				node_left.filhos[aux.qtd_chaves + 1] = aux.filhos[j + 1];
				node_left.qtd_chaves++;
			}

			node->qtd_chaves--;
			if (!node->qtd_chaves)
				for (int i = 0; i <= btree_order; i++)
					node->filhos[i] = -1;
			else
			{
				node->filhos[i] = node->filhos[i + 1];
				node->filhos[i + 1] = -1;
			}

			aux.qtd_chaves = 0;
			t->qtd_nos--;
			free_and_write(node, &aux, &node_right, &node_left, t);
			return node->qtd_chaves < ((btree_order - 1) / 2);
		}
	}

	return false; // se não fez nada
}

/**
 * Responsável por buscar uma chave (k) em uma Árvore-B (T). O valor de retorno indica se a chave foi encontrada ou não.
 * O ponteiro para a string result pode ser fornecido opcionalmente, e conterá o resultado encontrado.<br />
 * Esta é uma função recursiva. O parâmetro rrn recebe a raíz da Árvore-B na primeira chamada, e nas chamadas
 * subsequentes é o RRN do filho de acordo com o algoritmo fornecido.<br />
 * Comportamento de acordo com as especificações do PDF sobre Árvores-B e suas operações.<br />
 * <br />
 * Exemplos de uso:<br />
 * <code>
 * // Exemplo 1. A chave encontrada deverá ser retornada e o caminho não deve ser informado.<br />
 * ...<br />
 * char result[TAM_CHAVE_CORREDORES_IDX + 1];<br />
 * bool found = btree_search(result, false, id_corredor, corredores_idx.rrn_raiz, &corredores_idx);<br />
 * ...<br />
 * <br />
 * // Exemplo 2. Não há interesse na chave encontrada, apenas se ela existe, e o caminho não deve ser informado.<br />
 * ...<br />
 * bool found = btree_search(NULL, false, id_corredor, corredores_idx.rrn_raiz, &corredores_idx);<br />
 * ...<br />
 * <br />
 * // Exemplo 3. Busca por uma chave de tamanho variável (específico para o caso de buscas por chaves PIX).<br />
 * ...<br />
 * char modelo_str[TAM_MAX_MODELO];<br />
 * strcpy(nome_pista_str, nome_pista);<br />
 * strpadright(nome_pista_str, '#', TAM_MAX_NOME_PISTA - 1);<br />
 * bool found = btree_search(NULL, false, nome_pista_str, nome_pista_idx.rrn_raiz, &nome_pista_idx);<br />
 * ...<br />
 * <br />
 * // Exemplo 4. Há interesse no caminho feito para encontrar a chave.<br />
 * ...<br />
 * char result[TAM_CHAVE_CORREDORES_IDX + 1];<br />
 * printf(RRN_NOS);<br />
 * bool found = btree_search(result, true, id_corredor, corredores_idx.rrn_raiz, &corredores_idx);<br />
 * printf("\n");<br />
 * </code>
 *
 * @param result Ponteiro para ser escrita a chave encontrada. É ignorado caso NULL.
 * @param exibir_caminho Indica se o caminho percorrido deve ser impresso.
 * @param chave Chave a ser buscada na Árvore-B.
 * @param rrn RRN do nó no qual deverá ser processado. É o RRN da raíz da Árvore-B caso seja a primeira chamada.
 * @param t Ponteiro para o índice do tipo Árvore-B no qual será buscada a chave.
 * @return Indica se a chave foi encontrada.
 */
bool btree_search(char *result, bool exibir_caminho, char *chave, int rrn, btree *t)
{
	bool ret;
	int idx;
	if (rrn == -1) // se o rrn for -1, a chave não existe
		return false;
	btree_node node = btree_read(rrn, t);
	if (exibir_caminho)
		printf(" %d", node.this_rrn);
	bool found = btree_binary_search(&idx, exibir_caminho, chave, &node, t); // busca binaria
	if (found)																															 // se encontrou a chave
	{
		if (result)
			strcpy(result, node.chaves[idx]);
		btree_node_free(node);
		return true;
	}

	else
	{
		ret = btree_search(result, exibir_caminho, chave, node.filhos[idx], t); // Chama a função para o filho
		btree_node_free(node);
		return ret;
	}
}

/**
 * Responsável por buscar uma chave (k) dentro do nó de uma Árvore-B (T) de forma eficiente. O valor de retorno indica se a chave foi encontrada ou não.
 * O ponteiro para o int result pode ser fornecido opcionalmente, e indica o índice da chave encontrada (caso tenha sido encontrada)
 * ou o índice do filho onde esta chave deve estar (caso não tenha sido encontrada).<br />
 *
 * @param result Ponteiro para ser escrito o índice da chave encontrada ou do filho onde ela deve estar. É ignorado caso NULL.
 * @param exibir_caminho Indica se o caminho percorrido deve ser impresso.
 * @param chave Chave a ser buscada na Árvore-B.
 * @param node Ponteiro para o nó onde a busca deve ser feita.
 * @param t Ponteiro para o índice do tipo Árvore-B no qual será buscada a chave.
 * @return Indica se a chave foi encontrada.
 */
bool btree_binary_search(int *result, bool exibir_caminho, char *chave, btree_node *node, btree *t)
{
	int i = busca_binaria(chave, node->chaves[0], node->qtd_chaves, t->tam_chave + 1, t->compar, exibir_caminho, +1);
	if (result != NULL)
		*result = i;
	return i >= 0 && i < node->qtd_chaves && !t->compar(chave, node->chaves[i]);
}

/**
 * Função para percorrer uma Árvore-B (T) em ordem.<br />
 * Os parâmetros chave_inicio e chave_fim podem ser fornecidos opcionalmente, e contém o intervalo do percurso.
 * Caso chave_inicio e chave_fim sejam NULL, o índice inteiro é percorrido.
 * Esta é uma função recursiva. O parâmetro rrn recebe a raíz da Árvore-B na primeira chamada, e nas chamadas
 * subsequentes é o RRN do filho de acordo com o algoritmo de percursão em ordem.<br />
 * <br />
 * Exemplo de uso:<br />
 * <code>
 * // Exemplo 1. Intervalo não especificado.
 * ...<br />
 * bool imprimiu = btree_print_in_order(NULL, NULL, exibir_btree_corredor, corredores_idx.rrn_raiz, &corredores_idx);
 * ...<br />
 * <br />
 * // Exemplo 2. Imprime as transações contidas no intervalo especificado.
 * ...<br />
 * bool imprimiu = btree_print_in_order(data_inicio, data_fim, exibir_btree_pista, pistas_idx.rrn_raiz, &pistas_idx);
 * ...<br />
 * </code>
 *
 * @param chave_inicio Começo do intervalo. É ignorado caso NULL.
 * @param chave_fim Fim do intervalo. É ignorado caso NULL.
 * @param exibir Função utilizada para imprimir uma chave no índice. É informada a chave para a função.
 * @param rrn RRN do nó no qual deverá ser processado.
 * @param t Ponteiro para o índice do tipo Árvore-B no qual será inserida a chave.
 * @return Indica se alguma chave foi impressa.
 */
bool btree_print_in_order(char *chave_inicio, char *chave_fim, bool (*exibir)(char *chave), int rrn, btree *t)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (t->qtd_nos > 0) // se a arvore não estiver vazia
	{
		btree_node node = btree_read(rrn, t);
		for (int i = 0; i < node.qtd_chaves; i++) // percorre as chaves do nó
		{
			if (node.filhos[i] != -1)
				btree_print_in_order(chave_inicio, chave_fim, exibir, node.filhos[i], t);
			if (!chave_inicio && !chave_fim) // se não tiver intervalo
			{
				exibir(node.chaves[i]);
			}

			else // se tiver intervalo
			{
				if (chave_inicio && !chave_fim) // se tiver só o inicio do intervalo
				{
					if (t->compar(node.chaves[i], chave_inicio) > 0)
						exibir(node.chaves[i]);
				}

				else if (!chave_inicio && chave_fim) // se tiver só o fim do intervalo
				{
					if (t->compar(node.chaves[i], chave_fim) < 0)
						exibir(node.chaves[i]);
				}

				else // se tiver o inicio e o fim do intervalo
				{
					if (t->compar(node.chaves[i], chave_inicio) > 0 && t->compar(node.chaves[i], chave_fim) < 0)
						exibir(node.chaves[i]);
				}
			}
		}

		if (node.filhos[node.qtd_chaves] != -1)
			btree_print_in_order(chave_inicio, chave_fim, exibir, node.filhos[node.qtd_chaves], t);
		return true;
	}

	return false;
}

/**
 * Função interna para ler um nó em uma Árvore-B (T).<br />
 *
 * @param no No a ser lido da Árvore-B.
 * @param t Árvore-B na qual será feita a leitura do nó.
 */
btree_node btree_read(int rrn, btree *t)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	btree_node node = btree_node_malloc(t);
	int size = btree_register_size(t); // Tamanho do registro
	char registro[size + 1];
	strncpy(registro, t->arquivo + size * rrn, size); // Copia o registro do arquivo para a variável registro
	registro[size] = '\0';
	char qtd_chaves_str[4];
	strncpy(qtd_chaves_str, registro, 3);
	qtd_chaves_str[3] = '\0';
	node.qtd_chaves = atoi(qtd_chaves_str); // Copia a quantidade de chaves para o nó
	node.this_rrn = rrn;
	for (int i = 0; i < btree_order - 1; i++) // Copia as chaves para o nó
	{
		char chave_atual[t->tam_chave + 1];
		strncpy(chave_atual, registro + 3 + t->tam_chave * i, t->tam_chave);
		chave_atual[t->tam_chave] = '\0';
		if (chave_atual[0] != '#')
			strcpy(node.chaves[i], chave_atual);
	}

	for (int i = 0; i < btree_order; i++) // Copia os filhos para o nó
	{
		char filho_atual[4];
		strncpy(filho_atual, registro + 3 + t->tam_chave * (btree_order - 1) + 1 + 3 * i, 3);
		filho_atual[3] = '\0';
		if (filho_atual[0] != '*')
			node.filhos[i] = atoi(filho_atual);
		else
			node.filhos[i] = -1;
	}

	char folha_atual[2]; // Copia se é folha ou não para o nó
	strncpy(folha_atual, registro + 3 + t->tam_chave * (btree_order - 1), 1);
	node.folha = folha_atual[0] == 'T' ? true : false;
	return node;
}

/**
 * Função interna para escrever um nó em uma Árvore-B (T).<br />
 *
 * @param no No a ser escrito na Árvore-B.
 * @param t Árvore-B na qual será feita a escrita do nó.
 */
void btree_write(btree_node no, btree *t)
{
	int size = btree_register_size(t); // tamanho do registro
	char registro[size + 1], p[t->tam_chave + 1];
	p[0] = '\0'; // buffer auxiliar
	registro[0] = '\0';
	sprintf(p, "%03d", no.qtd_chaves);
	strcpy(registro, p); // copia a quantidade de chaves para o registro
	for (int i = 0; i < no.qtd_chaves; i++)
		strncat(registro, no.chaves[i], t->tam_chave); // copia as chaves para o registro
	if (btree_order - 1 - no.qtd_chaves)
		strpadright(registro, '#', strlen(registro) + t->tam_chave * (btree_order - 1 - no.qtd_chaves)); // preenche com # as chaves que não foram inseridas
	strcat(registro, no.folha ? "T" : "F");																														 // copia se é folha ou não para o registro
	for (int i = 0; i < btree_order; i++)																															 // copia os filhos para o registro
	{
		if (no.filhos[i] == -1)
			strcat(registro, "***");
		else
		{
			sprintf(p, "%03d", no.filhos[i]);
			strncat(registro, p, 3);
		}
	}

	strncpy(t->arquivo + no.this_rrn * btree_register_size(t), registro, btree_register_size(t)); // escreve o registro no arquivo
}

/**
 * Função interna para alocar o espaço necessário dos campos chaves (vetor de strings) e filhos (vetor de inteiros) da struct btree_node.<br />
 *
 * @param t Árvore-B base para o qual será alocado um struct btree_node.
 */
btree_node btree_node_malloc(btree *t)
{
	btree_node no;
	int tam = (t->tam_chave + 1) * (btree_order - 1); // Tamanho do bloco sequencial de memória para as chaves.
	char *bloco_sequencial = malloc(tam);							// Aloca um bloco sequencial de memória para as chaves para que possa funcionar o deslocamento na busca binária.
	for (int i = 0; i < tam; i++)
		bloco_sequencial[i] = '\0';					 // Inicializa o bloco sequencial com '\0'.
	no.chaves = malloc((btree_order - 1)); // Aloca o vetor de chaves.
	for (int i = 0; i < btree_order - 1; i++)
		no.chaves[i] = bloco_sequencial + i * (t->tam_chave + 1); // Desloca o ponteiro para a posição correta.
	no.filhos = malloc(btree_order * sizeof(int));
	for (int i = 0; i < btree_order; ++i)
		no.filhos[i] = -1;
	return no;
}

/**
 * Função interna para calcular o tamanho em bytes de uma Árvore-B.<br />
 *
 * @param t Árvore-B base para o qual será calculado o tamanho.
 */
int btree_register_size(btree *t)
{
	int chaves_ordenadas = (btree_order - 1) * t->tam_chave;
	return 3 + chaves_ordenadas + 1 + (btree_order * 3);
}

/* Funções de busca binária */
/**
 * Função Genérica de busca binária, que aceita parâmetros genéricos (assinatura baseada na função bsearch da biblioteca C).
 *
 * @param key Chave de busca genérica.
 * @param base0 Base onde ocorrerá a busca, por exemplo, um ponteiro para um vetor.
 * @param nmemb Número de elementos na base.
 * @param size Tamanho do tipo do elemento na base, dica: utilize a função sizeof().
 * @param compar Ponteiro para a função que será utilizada nas comparações.
 * @param exibir_caminho Indica se o caminho percorrido deve ser impresso. Se true, imprime as posições avaliadas durante a busca, até que todas sejam visitadas ou o elemento seja encontrado (pela 1a vez).
 *                       Caso o número de elementos seja par (p.ex, 10 elementos), então há 2 (duas) possibilidades para a posição da mediana dos elementos (p.ex., 5a ou 6a posição se o total fosse 10).
 *                       Neste caso, SEMPRE escolha a posição mais à direita (p.ex., a posição 6 caso o total for 10).
 * @param posicao_caso_repetido Caso o elemento seja encontrado, se houver mais do que 1 ocorrência, indica qual deve ser retornada. As opções são:
 *                     -1 = primeira : retorna a PRIMEIRA ocorrência (posição mais à esquerda).
 *                      0 = meio : retorna a ocorrência do MEIO (posição central). [modo padrão]
 *                     +1 = ultima : retorna a ÚLTIMA ocorrência (posição mais à direita).
 * @param retorno_se_nao_encontrado Caso o elemento NÃO seja encontrado, indica qual valor deve ser retornado. As opções são:
 *                     -1 = predecessor : retorna o elemento PREDECESSOR (o que apareceria imediatamente antes do elemento procurado, caso fosse encontrado).
 *                      0 = nulo : retorna NULL. [modo padrão]
 *                     +1 = sucessor : retorna o elemento SUCESSOR (o que apareceria imediatamente depois do elemento procurado, caso fosse encontrado).
 * @return Retorna o elemento encontrado ou NULL se não encontrou.
 * @return Retorna o indice do elemento encontrado ou -1 se não encontrou.
 */
int busca_binaria_com_reps(const void *key, const void *base0, size_t nmemb, size_t size, int (*compar)(const void *, const void *), bool exibir_caminho, int posicao_caso_repetido, int retorno_se_nao_encontrado)
{
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	long int imin = 0;
	long int imax = (long int)nmemb - 1;
	long int imid = 0;
	int result;
	if (exibir_caminho)
		printf(" (");
	while (imin <= imax)
	{
		imid = imin + (imax - imin + 1) / 2;			 // calcula o deslocamento do imid
		const void *found = base0 + (imid * size); // ponteiro para o elemento encontrado
		result = compar(key, found);							 // compara a chave com o elemento encontrado
		if (exibir_caminho)
			printf(" %ld", imid);

		if (result > 0) // se a chave for maior que o elemento encontrado
			imin = imid + 1;
		else if (result < 0) // se a chave for menor que o elemento encontrado
			imax = imid - 1;
		else // se a chave for igual
		{
			if (exibir_caminho)
				printf(")");
			return imid;
		}
	}
	if (exibir_caminho)
		printf(")");
	return (imin + (imax - imin + 1) / 2); // recalcula o imid de acordo com o imin e imax atuais
}

int busca_binaria(const void *key, const void *base0, size_t nmemb, size_t size, int (*compar)(const void *, const void *), bool exibir_caminho, int retorno_se_nao_encontrado)
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

void free_and_write(btree_node *node1, btree_node *node2, btree_node *node3, btree_node *node4, btree *t)
{
	btree_write(*node1, t);
	btree_write(*node2, t);
	btree_write(*node3, t);
	btree_node_free(*node2);
	btree_node_free(*node3);
	btree_node_free(*node4);
}

void btree_node_free(btree_node no)
{
	free(no.chaves);
	free(no.filhos);
}
