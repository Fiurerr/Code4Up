
void printAllPlayers(PlayerNode *headPlayer) {
    PlayerNode* current = headPlayer;
    printf("\n--- Lista de Jugadores ---\n");
    while (current != NULL) {
        printf("\nID: %d\n", current->player.id);
        printf("Nombre: %s\n", current->player.name);
        printf("Nickname: %s\n", current->player.nickname);
        printf("Edad: %d\n", current->player.age);
        printf("Personaje: %s\n", current->player.character);
        printf("Puntos: %d\n", current->player.points);
        printf("Victorias: %d\n", current->player.victories);
        current = current->next;
    }
}

/*
Agregar partida a la lista de partidas
*/
void addPartida(PartidaNode** headPartida, PlayerNode* winner) {
    PartidaNode* newPartida = (PartidaNode*)malloc(sizeof(PartidaNode));
    newPartida->winner = winner;
    newPartida->next = NULL;
    newPartida->prev = NULL;

    if (*headPartida == NULL) {
        *headPartida = newPartida;
        return;
    }
    PartidaNode* last = *headPartida;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = newPartida;
    newPartida->prev = last;
}

/*
Simula el juego y registra ganador (aleatorio)
*/
void playMatch(PlayerNode* headPlayer, PartidaNode** headPartida) {
    if (headPlayer == NULL) {
        printf("No hay jugadores para jugar.\n");
        return;
    }

    // Contar jugadores
    int playerCount = 0;
    PlayerNode* current = headPlayer;
    while (current != NULL) {
        playerCount++;
        current = current->next;
    }

    if (playerCount < 2) {
        printf("Se necesitan al menos dos jugadores para jugar una partida.\n");
        pause();
        return;
    }

    // Seleccionar dos jugadores diferentes
    int index1 = rand() % playerCount;
    int index2;
    do {
        index2 = rand() % playerCount;
    } while (index2 == index1);

    PlayerNode* player1 = headPlayer;
    for (int i = 0; i < index1; i++) {
        player1 = player1->next;
    }

    PlayerNode* player2 = headPlayer;
    for (int i = 0; i < index2; i++) {
        player2 = player2->next;
    }

    // jugadores que juegan
    printf("\n--- Partida ---\n");
    printf("Jugador 1: %s (%s)\n", player1->player.name, player1->player.character);
    printf("Jugador 2: %s (%s)\n", player2->player.name, player2->player.character);

    // Elegir aleatoriamente al ganador
    PlayerNode* winner = (rand() % 2 == 0) ? player1 : player2;

    printf("\n¡La partida ha terminado!\n");
    printf("Ganador: %s (Personaje: %s)\n", winner->player.name, winner->player.character);

    // Actualizar victorias del jugador
    winner->player.victories++;

    addPartida(headPartida, winner);
    savePlayersToFile(headPlayer);

    pause();
}

/*
Imprimir estadísticas:
- Jugadores con victorias
- Top 10 jugadores con más victorias
- Top 5 personajes con más victorias (sin estadísticas de personajes en esta versión)
*/
void printStats(PlayerNode* headPlayer, CharacterNode* headCharacter) {
    if (headPlayer == NULL) {
        printf("No hay jugadores para mostrar estadisticas.\n");
        return;
    }

    printf("\n--- Estadisticas de jugadores ---\n");

    // Mostrar todos los jugadores con sus victorias
    PlayerNode* current = headPlayer;
    while (current != NULL) {
        printf("Jugador: %s | Personaje: %s | Victorias: %d\n",
               current->player.name, current->player.character, current->player.victories);
        current = current->next;
    }

    // Copiar players a arreglo para ordenarlos top 10
    int count = 0;
    current = headPlayer;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    if (count == 0) {
        printf("No hay jugadores.\n");
        return;
    }

    Player* playersArray = (Player*)malloc(sizeof(Player) * count);
    current = headPlayer;
    int idx = 0;
    while (current != NULL) {
        playersArray[idx++] = current->player;
        current = current->next;
    }

    // Ordenar desc por victorias (burbuja simple)
    for (int i = 0; i < count -1; i++) {
        for (int j = 0; j < count - i -1; j++) {
            if (playersArray[j].victories < playersArray[j+1].victories) {
                Player temp = playersArray[j];
                playersArray[j] = playersArray[j+1];
                playersArray[j+1] = temp;
            }
        }
    }

    printf("\n--- Top 10 jugadores con mas victorias ---\n");
    int top10 = count < 10 ? count : 10;
    for (int i = 0; i < top10; i++) {
        printf("%d. %s | Personaje: %s | Victorias: %d\n", i+1, playersArray[i].name, playersArray[i].character, playersArray[i].victories);
    }

    free(playersArray);
    pause();
}
