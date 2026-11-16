#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum {
    classe_hulk,
    classe_homem_de_ferro,
    classe_viuva_negra
} ClassePersonagem;

typedef enum {
    casa_vazia,
    casa_combate,
    casa_tesouro,
    casa_cura,
    casa_armadilha,
    casa_missao
} TipoCasa;

typedef enum {
    acao_atacar = 1,
    acao_defender,
    acao_habilidade,
    acao_fugir
} AcaoCombate;

typedef struct {
    char nome[50];
    ClassePersonagem classe;
    int vida, vidaMax;
    int forca, defesa, agilidade, inteligencia;
    int xp, nivel;
    char arma[50];
    char armadura[50];
    int defendendo;
    int cooldownHabilidade;
} Personagem;

typedef struct {
    char nome[50];
    char descricao[100];
    int vida, vidaMax;
    int ataque, defesa, nivel;
    int xpRecompensa;
    int derrotado;
} Monstro;

typedef struct {
    int id;
    char nome[50];
    char missao[200];
    Monstro monstros[3];
    int missaoCumprida;
} Fase;


void limparTela();
void pausar();
int rolarDado(int lados);
int lerInteiroSeguro(int min, int max);
void exibirBarraVida(int atual, int maximo);
void exibirTabuleiro(TipoCasa tab[], int tamanho, int posicao);
void exibirMenuInicial();
void escolherPersonagem(Personagem *p);
void inicializarFases(Fase fases[]);
void iniciarFase(Fase *f, int numeroFase);
void iniciarTabuleiro(TipoCasa tabuleiro[], int tamanho);
void moverJogador(int *posicao, int passos, int tamanho);
void iniciarCombate(Personagem *p, Monstro *m, Fase *faseAtual);
void turnoJogador(Personagem *p, Monstro *m, int *fugiu, int *turnoAtual);
void turnoMonstro(Personagem *p, Monstro *m);
void receberDano(Personagem *p, int dano);
void danoMonstro(Monstro *m, int dano);
void ganharXP(Personagem *p, int xp);
void aplicarBonusAleatorio(Personagem *p);