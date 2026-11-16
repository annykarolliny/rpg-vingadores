#include "vingadores.h"

int main() {
    srand((unsigned)time(NULL));

    Personagem heroi;

    Fase fases[3];

    int faseAtual = 0;
    int posicao = 0;
    int tamanhoTabuleiro = 15;
    int jogoRodando = 1;

    TipoCasa tabuleiro[15];

    exibirMenuInicial();
    escolherPersonagem(&heroi);
    inicializarFases(fases);

    while (jogoRodando && faseAtual < 3) {
        limparTela();
        iniciarFase(&fases[faseAtual], faseAtual + 1);
        iniciarTabuleiro(tabuleiro, tamanhoTabuleiro);
        posicao = 0;

        while (heroi.vida > 0 && !fases[faseAtual].missaoCumprida) {
            limparTela();
            exibirTabuleiro(tabuleiro, tamanhoTabuleiro, posicao);
            
            printf("\n--- Turno de %s (Nivel: %d | XP: %d/100) ---\n", heroi.nome, heroi.nivel, heroi.xp);
            printf("Vida: ");
            exibirBarraVida(heroi.vida, heroi.vidaMax);
            printf(" (%d/%d)\n", heroi.vida, heroi.vidaMax);
            
            pausar();
            
            int passos = rolarDado(6);
            printf("Voce rolou um d6: %d\n", passos);
            moverJogador(&posicao, passos, tamanhoTabuleiro);
            printf("Voce avancou para a casa %d.\n", posicao + 1);
            
            TipoCasa casaAtual = tabuleiro[posicao];
            
            switch (casaAtual) {
                case casa_vazia:
                    printf("Area segura. Voce segue em frente.\n");
                    break;
                case casa_combate:
                    printf("Inimigo detectado!\n");
                    
                    int idxMonstro = (posicao < (tamanhoTabuleiro / 2)) ? 0 : 1; 
                    
                    iniciarCombate(&heroi, &fases[faseAtual].monstros[idxMonstro], &fases[faseAtual]);
                    break;
                case casa_tesouro:
                    printf("Voce encontrou um cache de tecnologia ou suprimentos!\n");
                    aplicarBonusAleatorio(&heroi);
                    break;
                case casa_cura:
                    printf("Centro medico encontrado. Vida restaurada!\n");
                    heroi.vida += 25;
                    if (heroi.vida > heroi.vidaMax) heroi.vida = heroi.vidaMax;
                    break;
                case casa_armadilha:
                    printf("Armadilha inimiga! Voce perdeu vida.\n");
                    receberDano(&heroi, 15);
                    break;
                case casa_missao:
                    printf("O lider inimigo apareceu!\n");
                    iniciarCombate(&heroi, &fases[faseAtual].monstros[2], &fases[faseAtual]);
                    break;
            }

            pausar();
        }

        if (heroi.vida <= 0) {
            printf("\nGAME OVER. A Terra esta perdida...\n");
            jogoRodando = 0;
        } else if (fases[faseAtual].missaoCumprida) {
            printf("\nMissao da Fase %d cumprida!\n", faseAtual + 1);
            faseAtual++;
            if (faseAtual < 3) {
                printf("Avancando para a proxima fase...\n");
                pausar();
            }
        }
    }

    if (faseAtual == 3) {
        printf("\n==================================\n");
        printf("VITORIA! A ameaca foi neutralizada.\n");
        printf("A Terra esta salva. Parabens, %s!\n", heroi.nome);
        printf("==================================\n");
    }

    return 0;
}