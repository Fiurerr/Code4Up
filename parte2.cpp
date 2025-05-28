
// Obtener aleatoriamente un personaje de la lista doblemente enlazada
const char* getRandomCharacter(CharacterNode* headCharacter) {
    int count = 0;
    CharacterNode* current = headCharacter;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    if (count == 0) {
        return NULL;
    }
    int randIndex = rand() % count;
    current = headCharacter;
    for (int i = 0; i < randIndex; i++) {
        current = current->next;
    }
    return current->name;
}

/*
......... PLAYER FUNCTIONS ........
*/
Player createPlayer(CharacterNode** headCharacter, int playerId) {
    Player newPlayer;
    newPlayer.id = playerId; 

    printf("
Dame el nombre del jugador: ");
    fgets(newPlayer.name, MAX_LEN_STR, stdin);
    newPlayer.name[strcspn(newPlayer.name, "
")] = 0;
    printf("Dame el nickname sin espacios: ");
    scanf("%s", newPlayer.nickname);
    printf("Dame edad: ");
    scanf("%d", &newPlayer.age);
    newPlayer.points = 0;
    newPlayer.victories = 0;

    // Asignar un personaje aleatorio de la lista enlazada
    const char* character = getRandomCharacter(*headCharacter);
    if (character == NULL) {
        printf("No quedan personajes disponibles para asignar.
");
        strcpy(newPlayer.character, "Sin personaje");
    } else {
        strcpy(newPlayer.character, character);
        // Sacar personaje de la lista para que no se repita
        removeCharacterNode(headCharacter, character);
    }

    cleanBuffer();
    return newPlayer;
}

PlayerNode* createPlayerNode(Player newPlayer) {
    PlayerNode *newPlayerNode = (PlayerNode*)malloc(sizeof(PlayerNode));
    newPlayerNode->player = newPlayer;
    newPlayerNode->next = NULL;
    newPlayerNode->prev = NULL;
    return newPlayerNode;
}

void addPlayer(PlayerNode **headPlayer, CharacterNode** headCharacter, int playerId) {
    Player newPlayer = createPlayer(headCharacter, playerId);
    PlayerNode *newPlayerNode = createPlayerNode(newPlayer);
    if (*headPlayer == NULL) {
        *headPlayer = newPlayerNode;
        return;
    }
    PlayerNode *lastNode = *headPlayer;
    while (lastNode->next != NULL) {
        lastNode = lastNode->next;
    }
    lastNode->next = newPlayerNode;
    newPlayerNode->prev = lastNode;
}

/*
Clean buffer
*/
void cleanBuffer() {
    int c;
    while ((c = getchar()) != '
' && c != EOF);
}

/*
Save the players to a file with | as the separator.
*/
void savePlayersToFile(PlayerNode *headPlayer) {
    FILE* file = fopen("players.txt", "w");
    if (file == NULL) {
        perror("Error en archivo
");
        return;
    }

    PlayerNode* current = headPlayer;
    while (current != NULL) {
        fprintf(file, "%d|%s|%s|%d|%s|%d|%d
",
            current->player.id,
            current->player.name,
            current->player.nickname,
            current->player.age,
            current->player.character,
            current->player.points,
            current->player.victories);
        current = current->next;
    }

    fclose(file);
    printf("Jugadores guardados en 'players.txt'
");
}
