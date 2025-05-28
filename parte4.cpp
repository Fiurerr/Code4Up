
void pause(void) {
    printf("\nPresione ENTER para continuar...");
    while (getchar() != '\n');
}

int mainMenu() {
    int option;
    printf("\n=== MENU PRINCIPAL ===\n");
    printf("1. Agregar jugador\n");
    printf("2. Jugar partida (seleccion ganador aleatorio)\n");
    printf("3. Mostrar estadisticas\n");
    printf("4. Mostrar jugadores\n");
    printf("5. Salir\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &option);
    cleanBuffer();
    return option;
}

PlayerNode* loadPlayersFromFile(int* playerIdCounter) {
    FILE* file = fopen("players.txt", "r");
    if (file == NULL) {
        printf("No se encontro archivo de jugadores, iniciando vacio.\n");
        return NULL;
    }

    PlayerNode* head = NULL;
    PlayerNode* tail = NULL;
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Player player;
        sscanf(line, "%d|%49[^|]|%49[^|]|%d|%49[^|]|%d|%d",
               &player.id, player.name, player.nickname, &player.age,
               player.character, &player.points, &player.victories);

        PlayerNode* newNode = createPlayerNode(player);
        if (head == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

        if (player.id >= *playerIdCounter) {
            *playerIdCounter = player.id + 1;
        }
    }

    fclose(file);
    printf("Jugadores cargados desde archivo.\n");
    return head;
}

int main() {
    srand(time(NULL)); // Inicializar la semilla
    int playerIdCounter = 1;
    PlayerNode *headPlayer = loadPlayersFromFile(&playerIdCounter);
    CharacterNode* headCharacter = createCharacterList();
    PartidaNode* headPartida = NULL;
    int opt;

    do {
        opt = mainMenu();
        switch(opt) {
            case 1:
                addPlayer(&headPlayer, &headCharacter, playerIdCounter++);
                break;
            case 2:
                if (headPlayer == NULL) {
                    printf("No hay jugadores para jugar. Agregue primero.\n");
                    pause();
                } else {
                    playMatch(headPlayer, &headPartida);
                }
                break;
            case 3:
                printStats(headPlayer, headCharacter);
                break;
            case 4:
                printAllPlayers(headPlayer);
                pause();
                break;
            case 5:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opcion invalida. Intente nuevamente.\n");
                pause();
                break;
        }
    } while (opt != 5);

    // Liberar memoria omitido para brevedad
    savePlayersToFile(headPlayer);

    return 0;
}
