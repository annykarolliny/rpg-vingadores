#include "vingadores.h"

// Função que deixa a interface mais visual. Limpa a tela para o sistema Windows e outros
void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        printf("\033[H\033[2J");
    #endif
}

void pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar();
}

int rolarDado(int lados) {
    return (rand() % lados) + 1;
}

int lerInteiroSeguro(int min, int max) {
    int valor;
    char entrada[100];
    while (1) {
        if (fgets(entrada, sizeof(entrada), stdin) == NULL) continue;
        entrada[strcspn(entrada, "\n")] = 0;
        if (sscanf(entrada, "%d", &valor) == 1) {
            if (valor >= min && valor <= max) return valor;
        }
        printf("Entrada invalida. Digite um numero entre %d e %d: ", min, max);
    }
}

void exibirBarraVida(int atual, int maximo) {
    int tamanhoBarra = 20;
    int preenchido = (atual * tamanhoBarra) / maximo;
    
    printf("[");
    for (int i = 0; i < tamanhoBarra; i++) {
        if (i < preenchido) printf("#");
        else printf("-");
    }
    printf("]");
}

void exibirTabuleiro(TipoCasa tab[], int tamanho, int posicao) {
    printf("=== MAPA DA MISSAO ===\n");
    for (int i = 0; i < tamanho; i++) {
        if (i == posicao) {
            printf("[H]");
        } else {
            switch(tab[i]) {
                case casa_vazia:
     			printf("[ ]"); break;
                case casa_combate:   
			printf("[X]"); break;
                case casa_tesouro:   
			printf("[$]"); break;
                case casa_cura:       
			printf("[+]"); break;
                case casa_armadilha: 
			printf("[!]"); break;
                case casa_missao:    
			printf("[C]"); break;
            }
        }

        if ((i + 1) % 5 == 0) printf("\n");
    }

    printf("\nLegenda: [H] Voce | [X] Combate | [$] Tesouro | [+] Cura | [!] Armadilha | [C] Chefao\n\n");
}

void exibirMenuInicial() {
    limparTela();
    printf("==========================================\n");
    printf("      PROTOCOLO VINGADORES: A ERA ULTRON  \n");
    printf("==========================================\n");
    printf("Bem-vindo, agente da S.H.I.E.L.D.\n");
    printf("Sua missao: derrotar as forcas do mal em 3 eras.\n\n");
}

void escolherPersonagem(Personagem *p) {
    printf("\n=== ESCOLHA SEU HEROI ===\n");
    
    printf("\n[1] HULK\n");
    printf("    Arma: Punhos Esmagadores | Armadura: Pele Resistente\n");
    printf("    Habilidade: Hulk Smash (Dano massivo baseado em Forca)\n");
    printf("    Vida: 150 | Forca: 18 | Defesa: 8 | Agilidade: 6 | Inteligencia: 4\n");
    
    printf("\n[2] HOMEM DE FERRO\n");
    printf("    Arma: Repulsores de Energia | Armadura: Armadura Mark L\n");
    printf("    Habilidade: Unibeam (Dano tecnologico baseado em Inteligencia)\n");
    printf("    Vida: 110 | Forca: 12 | Defesa: 16 | Agilidade: 10 | Inteligencia: 18\n");
    
    printf("\n[3] VIUVA NEGRA\n");
    printf("    Arma: Mordidas da Viuva | Armadura: Traje Furtivo\n");
    printf("    Habilidade: Ataque Furtivo (Dano critico baseado em Agilidade)\n");
    printf("    Vida: 85 | Forca: 10 | Defesa: 8 | Agilidade: 20 | Inteligencia: 15\n");
    
    printf("\nOpcao: ");
    
    int opcao = lerInteiroSeguro(1, 3);
    
    // Zera os atributos base antes de configurar o herói
    p->vida = 100; p->vidaMax = 100;
    p->forca = 10; p->defesa = 10; p->agilidade = 10; p->inteligencia = 10;
    p->xp = 0; p->nivel = 1; p->defendendo = 0;
    p->cooldownHabilidade = 0;
    
    switch (opcao) {
        case 1:
            strcpy(p->nome, "Hulk");
            p->classe = classe_hulk;
            p->vidaMax = 150; p->vida = 150;
            p->forca = 18; p->defesa = 8; p->agilidade = 6; p->inteligencia = 4;
            strcpy(p->arma, "Punhos Esmagadores");
            strcpy(p->armadura, "Pele Resistente");
            break;
        case 2:
            strcpy(p->nome, "Homem de Ferro");
            p->classe = classe_homem_de_ferro;
            p->vidaMax = 110; p->vida = 110;
            p->forca = 12; p->defesa = 16; p->agilidade = 10; p->inteligencia = 18;
            strcpy(p->arma, "Repulsores de Energia");
            strcpy(p->armadura, "Armadura Mark L");
            break;
        case 3:
            strcpy(p->nome, "Viuva Negra");
            p->classe = classe_viuva_negra;
            p->vidaMax = 85; p->vida = 85;
            p->forca = 10; p->defesa = 8; p->agilidade = 20; p->inteligencia = 15;
            strcpy(p->arma, "Mordidas da Viuva");
            strcpy(p->armadura, "Traje Furtivo");
            break;
    }
    printf("\nVoce escolheu: %s\n", p->nome);
    pausar();
}

// Fases e monstros
void inicializarFases(Fase fases[]) {
    // FASE 1
    fases[0].id = 1;
    strcpy(fases[0].nome, "Batalha de Nova York");
    strcpy(fases[0].missao, "Impedir a invasao e derrotar Loki.");
    fases[0].missaoCumprida = 0;
    
    strcpy(fases[0].monstros[0].nome, "Agente da Hidra");
    fases[0].monstros[0].vida = 35; fases[0].monstros[0].vidaMax = 35; 
    fases[0].monstros[0].ataque = 6; fases[0].monstros[0].defesa = 2;
    fases[0].monstros[0].nivel = 1; fases[0].monstros[0].xpRecompensa = 20;
    fases[0].monstros[0].derrotado = 0;
    
    strcpy(fases[0].monstros[1].nome, "Mercenario Chitauri");
    fases[0].monstros[1].vida = 45; fases[0].monstros[1].vidaMax = 45; 
    fases[0].monstros[1].ataque = 8; fases[0].monstros[1].defesa = 4;
    fases[0].monstros[1].nivel = 1; fases[0].monstros[1].xpRecompensa = 25;
    fases[0].monstros[1].derrotado = 0;
    
    strcpy(fases[0].monstros[2].nome, "Loki");
    fases[0].monstros[2].vida = 80; fases[0].monstros[2].vidaMax = 80; 
    fases[0].monstros[2].ataque = 10; fases[0].monstros[2].defesa = 5;
    fases[0].monstros[2].nivel = 2; fases[0].monstros[2].xpRecompensa = 50;
    fases[0].monstros[2].derrotado = 0;

    // FASE 2
    fases[1].id = 2;
    strcpy(fases[1].nome, "A Era de Ultron");
    strcpy(fases[1].missao, "Invadir a fabrica e destruir o nucleo de Ultron.");
    fases[1].missaoCumprida = 0;

    strcpy(fases[1].monstros[0].nome, "Robo de Ultron");
    fases[1].monstros[0].vida = 60; fases[1].monstros[0].vidaMax = 60; 
    fases[1].monstros[0].ataque = 10; fases[1].monstros[0].defesa = 6;
    fases[1].monstros[0].nivel = 2; fases[1].monstros[0].xpRecompensa = 30;
    fases[1].monstros[0].derrotado = 0;

    strcpy(fases[1].monstros[1].nome, "Drone Bombardeiro");
    fases[1].monstros[1].vida = 55; fases[1].monstros[1].vidaMax = 55; 
    fases[1].monstros[1].ataque = 12; fases[1].monstros[1].defesa = 4;
    fases[1].monstros[1].nivel = 2; fases[1].monstros[1].xpRecompensa = 30;
    fases[1].monstros[1].derrotado = 0;

    strcpy(fases[1].monstros[2].nome, "Ultron Prime");
    fases[1].monstros[2].vida = 110; fases[1].monstros[2].vidaMax = 110; 
    fases[1].monstros[2].ataque = 14; fases[1].monstros[2].defesa = 8;
    fases[1].monstros[2].nivel = 3; fases[1].monstros[2].xpRecompensa = 60;
    fases[1].monstros[2].derrotado = 0;
    
    // FASE 3
    fases[2].id = 3;
    strcpy(fases[2].nome, "Guerra do Infinito");
    strcpy(fases[2].missao, "Enfrentar a Ordem Negra e derrotar Thanos.");
    fases[2].missaoCumprida = 0;

    strcpy(fases[2].monstros[0].nome, "Outrider");
    fases[2].monstros[0].vida = 80; fases[2].monstros[0].vidaMax = 80; 
    fases[2].monstros[0].ataque = 14; fases[2].monstros[0].defesa = 7;
    fases[2].monstros[0].nivel = 3; fases[2].monstros[0].xpRecompensa = 40;
    fases[2].monstros[0].derrotado = 0;

    strcpy(fases[2].monstros[1].nome, "Corvus Glaive");
    fases[2].monstros[1].vida = 70; fases[2].monstros[1].vidaMax = 70;
    fases[2].monstros[1].ataque = 16; fases[2].monstros[1].defesa = 6;
    fases[2].monstros[1].nivel = 3; fases[2].monstros[1].xpRecompensa = 40;
    fases[2].monstros[1].derrotado = 0;

    strcpy(fases[2].monstros[2].nome, "Thanos");
    fases[2].monstros[2].vida = 160; fases[2].monstros[2].vidaMax = 160; 
    fases[2].monstros[2].ataque = 20; fases[2].monstros[2].defesa = 12;
    fases[2].monstros[2].nivel = 5; fases[2].monstros[2].xpRecompensa = 100;
    fases[2].monstros[2].derrotado = 0;
}

void iniciarFase(Fase *f, int numeroFase) {
    printf("==========================================\n");
    printf("FASE %d: %s\n", numeroFase, f->nome);
    printf("==========================================\n");
    
    switch (numeroFase) {
        case 1:
            printf("Loki roubou o Tesseract e abriu um portal sobre a Torre Stark.\n");
            printf("Criaturas Chitauri e agentes infiltrados da Hidra estao dominando as ruas.\n");
            printf("Os Vingadores precisam conter a invasao e capturar o Deus da Trapaca.\n\n");
            break;
        case 2:
            printf("A paz durou pouco. Ultron despertou e quer a extincao da humanidade.\n");
            printf("Ele construiu um exercito de robos em uma fabrica secreta na Sokovia.\n");
            printf("Infiltrar-se no local e destruir o nucleo central e a unica esperanca.\n\n");
            break;
        case 3:
            printf("Thanos chegou. Com as Joias do Infinito, ele esta a um estalo da vitoria.\n");
            printf("A Ordem Negra espalha o caos enquanto o Titanos busca as ultimas joias.\n");
            printf("E agora ou nunca: enfrente as forcas cosmicas e salve o universo.\n\n");
            break;
    }
    
    printf("MISSAO: %s\n", f->missao);
    printf("==========================================\n");
    pausar();
}

// Funções relaciondas ao tabuleiro
void iniciarTabuleiro(TipoCasa tabuleiro[], int tamanho) {
    int qtdCombates = 0;

    for (int i = 0; i < tamanho; i++) {
        if (i == 0) {
            tabuleiro[i] = casa_vazia;
        } else if (i == tamanho - 1) {
            tabuleiro[i] = casa_missao;
        } else {
            tabuleiro[i] = (TipoCasa)(rand() % 6);
            
            if (tabuleiro[i] == casa_missao) {
                tabuleiro[i] = casa_combate;
            }
            
            if (tabuleiro[i] == casa_combate) {
                qtdCombates++;
            }
        }
    }

    // Se por acaso o sorteio gerou menos de 2 combates, força a criação deles
    if (qtdCombates < 2) {
        for (int i = 1; i < tamanho - 1 && qtdCombates < 2; i++) {
            if (tabuleiro[i] == casa_vazia) {
                tabuleiro[i] = casa_combate;
                qtdCombates++;
            }
        }
    }
}

void moverJogador(int *posicao, int passos, int tamanho) {
    *posicao += passos;
    if (*posicao >= tamanho) {
        *posicao = tamanho - 1;
    }
}

// Funções relacionadas ao combate
void iniciarCombate(Personagem *p, Monstro *m, Fase *faseAtual) {
    if (m->derrotado) {
        printf("\nVoce ja derrotou o %s nesta fase.\n", m->nome);
        printf("Voce vasculha os restos e encontra alguns recursos (+5 XP).\n");
        ganharXP(p, 5);
        return; 
    }

    printf("\n>>> COMBATE INICIADO <<<\n");
    printf("Voce enfrenta: %s\n", m->nome);
    
    int fugiu = 0;
    int turnoAtual = 1; 

    while (p->vida > 0 && m->vida > 0 && !fugiu) {
        printf("\n--- Turno %d ---\n", turnoAtual);
        
        printf("Sua vida:   ");
        exibirBarraVida(p->vida, p->vidaMax);
        printf(" (%d/%d)\n", p->vida, p->vidaMax);
        
        printf("Inimigo:    ");
        exibirBarraVida(m->vida, m->vidaMax); 
        printf(" (%d/%d)\n", m->vida, m->vidaMax); 
        
        turnoJogador(p, m, &fugiu, &turnoAtual);
        if (m->vida <= 0 || fugiu) break;
        
        turnoMonstro(p, m);
        turnoAtual++; 
    }
    
    if (fugiu) {
        printf("Voce conseguiu fugir do combate!\n");
    } else if (p->vida <= 0) {
        printf("Voce foi derrotado...\n");
    } else {
        printf("\nVoce derrotou o %s!\n", m->nome);
        m->derrotado = 1;
        ganharXP(p, m->xpRecompensa);
        aplicarBonusAleatorio(p);
        
        if (m == &faseAtual->monstros[2]) {
            faseAtual->missaoCumprida = 1;
            printf("Missao principal da fase concluida!\n");
        }
    }
}

void turnoJogador(Personagem *p, Monstro *m, int *fugiu, int *turnoAtual) {
    printf("\nSeu turno:\n");
    printf("[1] Atacar\n");
    printf("[2] Defender\n");
    
    if (*turnoAtual >= 3) {
        printf("[3] Habilidade Especial\n");
    } else {
        printf("[3] Habilidade Especial (Recarga: %d turno(s))\n", 3 - *turnoAtual);
    }
    
    printf("[4] Fugir\n");
    printf("Opcao: ");
    
    int opcao = lerInteiroSeguro(1, 4);
    p->defendendo = 0;

    switch (opcao) {
        case acao_atacar: {
            int dado = rolarDado(20);
            int atributo = p->forca;
            
            switch (p->classe) {
                case classe_viuva_negra: atributo = p->agilidade; break;
                case classe_homem_de_ferro: atributo = p->inteligencia; break;
                default: break;
            }

            int ataque = dado + atributo;
            int dano = ataque - m->defesa;
            if (dano < 1) dano = 1;
            
            danoMonstro(m, dano);
            printf("Voce atacou! Dano: %d\n", dano);
            break;
        }
        case acao_defender:
            p->defendendo = 1;
            printf("Voce assumiu uma postura defensiva. O proximo dano sera reduzido.\n");
            break;
            
        case acao_habilidade: {
            if (*turnoAtual < 3) {
                printf("Habilidade em recarga! Voce precisa esperar mais %d turno(s).\n", 3 - *turnoAtual);
                pausar();
                turnoJogador(p, m, fugiu, turnoAtual);
                return;
            }

            int dano = 0;
            switch (p->classe) {
                case classe_hulk:
                    printf("HULK ESMAGA! Dano massivo!\n");
                    dano = (p->forca * 2) + rolarDado(20);
                    break;
                case classe_homem_de_ferro:
                    printf("Unibeam! Feixe de energia!\n");
                    dano = (p->inteligencia * 2) + rolarDado(12);
                    break;
                case classe_viuva_negra:
                    printf("Ataque Furtivo! Voce encontra um ponto fraco!\n");
                    dano = (p->agilidade * 2) + p->inteligencia;
                    break;
            }

            danoMonstro(m, dano);
            printf("Dano causado: %d\n", dano);
            
            *turnoAtual = 0; 
            break;
        }
        case acao_fugir: {
            // Verifica se o nome do monstro é um dos chefes (Loki, Ultron Prime ou Thanos)
            if (strcmp(m->nome, "Loki") == 0 || 
                strcmp(m->nome, "Ultron Prime") == 0 || 
                strcmp(m->nome, "Thanos") == 0) {
                
                printf("\nNao e possivel fugir de um Chefe! Voce deve lutar ate o fim.\n");
                pausar();
                turnoJogador(p, m, fugiu, turnoAtual);
                return;
            }

            int teste = rolarDado(20) + p->agilidade;
            if (teste >= 15) {
                *fugiu = 1;
            } else {
                printf("Voce tentou fugir, mas falhou!\n");
            }

            break;
        }
    }
}

void turnoMonstro(Personagem *p, Monstro *m) {
    printf("\nTurno do monstro:\n");
    int dado = rolarDado(20);
    int ataque = dado + m->ataque;
    int dano = ataque - p->defesa;
    
    if (p->defendendo) {
        dano = dano / 2;
        printf("(Sua defesa reduziu o dano!)\n");
    }
    
    if (dano < 1) dano = 1;
    
    receberDano(p, dano);
    printf("O %s atacou! Dano: %d\n", m->nome, dano);
}

void receberDano(Personagem *p, int dano) {
    p->vida -= dano;
    if (p->vida < 0) p->vida = 0;
}

void danoMonstro(Monstro *m, int dano) {
    m->vida -= dano;
    if (m->vida < 0) m->vida = 0;
}

void ganharXP(Personagem *p, int xp) {
    p->xp += xp;
    printf("Voce ganhou %d XP! (XP atual: %d)\n", xp, p->xp);
    
    while (p->xp >= 100) {
        p->xp -= 100;
        p->nivel++;
        p->vidaMax += 20;
        p->vida = p->vidaMax;
        p->forca += 2;
        p->defesa += 2;
        p->agilidade += 2;
        p->inteligencia += 2;
        printf("\n*** NIVEL UP! Voce alcancou o Nivel %d! ***\n", p->nivel);
        printf("Atributos aumentados e vida restaurada!\n");
    }
}

void aplicarBonusAleatorio(Personagem *p) {
    int bonus = rand() % 5;
    switch (bonus) {
        case 0: p->forca++; printf("Bonus: +1 Forca!\n"); break;
        case 1: p->defesa++; printf("Bonus: +1 Defesa!\n"); break;
        case 2: p->agilidade++; printf("Bonus: +1 Agilidade!\n"); break;
        case 3: p->inteligencia++; printf("Bonus: +1 Inteligencia!\n"); break;
        default: p->vidaMax += 10; p->vida += 10; printf("Bonus: +10 Vida Maxima!\n"); break;
    }
}