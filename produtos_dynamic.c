#include<stdio.h>
#include<stdlib.h>
/* #include<conio.h> -1 */
void titulo(int vezes)
{
	if(vezes>20)
	{
		printf("\n");
	}
	int cont;
	for(cont=0;cont<vezes;cont++)
	{
		printf("#");
	}
	if(vezes>20)
	{
		printf("\n");
	}
}
int f_length(char *palavra)
{
	int i=0;
	while(palavra[i]!='\0')
	{
		i++;
	}
	return(i);
}
void copia_chars(char **merc_ou_prod,int posicao,char *palavra)
{
	int i=0;
	while(palavra[i]!='\0')
	{
		merc_ou_prod[posicao][i]=palavra[i];
		i++;
	}
	merc_ou_prod[posicao][i]='\0';
}
int confirma(char *merc_ou_prod,char *geral)
{
	int i=0;
	while(merc_ou_prod[i]==geral[i] && merc_ou_prod[i]!='\0')
	{
		i++;
	}
	return((unsigned char)merc_ou_prod[i]-(unsigned char)geral[i]);
}
char **mercado =NULL, **produto =NULL;
char linem[15], linep[15];
float menor_cesta, valor_prod_merc, *media_prod, *valor_cesta;
int cont=0,contad_prod=1,contad_merc=1,confirm_exit=1,n_letras=0;
void main()
{
	/* clrscr(); -1 */
	system("cls");
	titulo(73);
	titulo(12);
	printf(" - Programa para calculo de cesta de alimentos - ");
	titulo(12);
	titulo(73);
	printf("\nEntre com os mercados:\n");
	while(confirm_exit!=0)
	{
		valor_cesta=(float *)realloc(valor_cesta,(contad_merc+1) * sizeof(float));
		valor_cesta[contad_merc]=0;
		printf("- %d%c: ",contad_merc,167);
		if(contad_merc%3==0)
		{
			printf("(ou digite produtos para inserir os produtos): ");
		}
		scanf("%s",linem);/* fgets(mercado[contad_merc],19,stdin); */
		fflush(stdin);
		confirm_exit=confirma(linem,"produtos");
		if(confirm_exit!=0)
		{
			/* notas e credito no rodape do arquivo */
			mercado=(char **)realloc(mercado,(contad_merc+1) * sizeof(char *));
			if(mercado==NULL)
			{
				printf("\nNao foi possivel alocar memoria\n");
				exit(1);
			}
			n_letras=f_length(linem);
			mercado[contad_merc]=(char *)malloc((n_letras+1) * sizeof(char *));/* verificar notas no rodape do arquivo */
			copia_chars(mercado,contad_merc,linem);
			contad_merc++;
		}
	}
	confirm_exit=1;
	printf("\nEntre com os produtos:\n");
	while(confirm_exit!=0)
	{
		media_prod=(float *)realloc(media_prod,(contad_prod+1) * sizeof(float));
		media_prod[contad_prod]=0;
		printf("- %d%c: ",contad_prod,167);
		if(contad_prod%4==0)
		{
			printf("(ou digite precos para inserir os precos): ");
		}
		scanf("%s",linep);
		fflush(stdin);
		confirm_exit=confirma(linep,"precos");
		if(confirm_exit!=0)
		{
			produto=(char **)realloc(produto,(contad_prod+1) * sizeof(char *));
			if(produto==NULL)
			{
				printf("\nNao foi possivel alocar memoria\n");
				exit(1);
			}
			n_letras=f_length(linep);
			produto[contad_prod]=(char *)malloc((n_letras+1) * sizeof(char *));
			copia_chars(produto,contad_prod,linep);
			contad_prod++;
		}
	}
	printf("\n");
	contad_merc--;
	contad_prod--;
	int contad_prod_temp=1;
	cont=1;
	while(contad_prod_temp<=contad_merc)
	{
		if(cont==1)
		{
			printf("No mercado %s, entre com os precos para: \n",mercado[contad_prod_temp]);
		}
		printf("- %s: ",produto[cont]);
		scanf("%f",&valor_prod_merc);
		valor_cesta[contad_prod_temp]=valor_cesta[contad_prod_temp]+valor_prod_merc;
		media_prod[cont]=media_prod[cont]+valor_prod_merc;
		cont++;
		if((cont-1)%contad_prod==0)
		{
			contad_prod_temp++;
			cont=1;
			printf("\n");
		}
	}
	menor_cesta=valor_cesta[1];
	int pos_m_mer=1;
	printf("O preco medio dos produto sao:\n");
	for(cont=1;cont<=contad_prod;cont++)
	{
		media_prod[cont]=media_prod[cont]/contad_merc;
		printf("- %s: R$%3.2f.\n",produto[cont],media_prod[cont]);
		if(cont<=contad_merc)
		{
			if(valor_cesta[cont]<menor_cesta)
			{
				menor_cesta=valor_cesta[cont];
				pos_m_mer=cont;
			}
		}
	}
	printf("\nO preco da menor cesta e de R$%3.2f no mercado %s.\n\n",menor_cesta,mercado[pos_m_mer]);
	printf("O programa terminou. ");
	/* Clear allocated memory */
	/* 
	estou sempre considerando que o numero de produtos e maior que de mercados.
	para evitar problemas com a desalocação no caso do numeros de mercados serem maiores,
	faça um loop ate dois comparando o maior entre contad_merc com contad_prod e guarda o resultado em uma 
	variavel, ai então no loop abaixo faça o cont ir ate o valor do maior armazenado.
	vou fazer isso posteriormente.
	*/
	for(cont=0;cont<=contad_prod;cont++)
	{
		if(cont<=contad_merc)
		{
			free(mercado[cont]);
		}
		free(produto[cont]);
	}
	free(mercado);
	free(produto);
	system("pause");
}
/*
A lógica para a montagem deste vetor de vetor dinâmico e de 
http://www.cse.unt.edu/~donr/courses/4410/dynamicArrays/dynamicArrays.html
mas uma parte do código foi elaborada por min, pois o exemplo que me forneceu base para a montagem, estava em C++
que tem o tipo string e não precisa alocar a segunda dimensão de forma manual, mas em C foi preciso lembrar de 
alocar a segunda dimensão.

	A linha abaixo forneceu a lógica.
		strarray = (char **) realloc (strarray,(numStrings+1) * sizeof(char *));
			
	Mas esta outra eu precisei lembrar, e alocar a segunda dimensão.
		mercado[contad_merc]=(char *)malloc(15 * sizeof(char *));
*/
