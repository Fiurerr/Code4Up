
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LEN_STR 50
#define MAX_PLAYERS 100

typedef struct CharacterNode {
    char name[MAX_LEN_STR];
    struct CharacterNode* next;
    struct CharacterNode* prev;
    int victories;
} CharacterNode;

typedef struct {
    int id;
    char name[MAX_LEN_STR];
    char nickname[MAX_LEN_STR];
    int age;
    char character[MAX_LEN_STR]; // Personaje asignado
    int points;
    int victories; // Número de victorias
} Player;

typedef struct PlayerNode {
    Player player;
    struct PlayerNode *next;
    struct PlayerNode *prev;
} PlayerNode;

typedef struct PartidaNode {
    PlayerNode *winner; // Puntero al jugador ganador
    struct PartidaNode *next;
    struct PartidaNode *prev;
} PartidaNode;

// Prototypes
void cleanBuffer();
Player createPlayer(CharacterNode** headCharacter, int playerId);
PlayerNode* createPlayerNode(Player);
void addPlayer(PlayerNode **headPlayer, CharacterNode** headCharacter, int playerId);
CharacterNode* createCharacterList();
void removeCharacterNode(CharacterNode** headCharacter, const char* characterName);
const char* getRandomCharacter(CharacterNode* headCharacter);
void savePlayersToFile(PlayerNode*);
void printAllPlayers(PlayerNode*);
void playMatch(PlayerNode* headPlayer, PartidaNode** headPartida);
void addPartida(PartidaNode** headPartida, PlayerNode* winner);
void printStats(PlayerNode* headPlayer, CharacterNode* headCharacter);
void pause(void);
PlayerNode* loadPlayersFromFile(int* playerIdCounter); //cargar jugadores

// Crear la lista doblemente enlazada de personajes disponibles
CharacterNode* createCharacterList() {
    const char* characters[] = {
        "Mario", "Luigi", "Peach", "Bowser", "Link",
        "Zelda", "Kirby", "Samus", "Fox", "Pikachu"
    };
    int numCharacters = sizeof(characters) / sizeof(characters[0]);
    CharacterNode* head = NULL;
    CharacterNode* tail = NULL;

    for (int i = 0; i < numCharacters; i++) {
        CharacterNode* node = (CharacterNode*)malloc(sizeof(CharacterNode));
        strcpy(node->name, characters[i]);
        node->next = NULL;
        node->prev = tail;
        node->victories = 0; // Inicializar victorias
        if (tail != NULL) {
            tail->next = node;
        } else {
            head = node;
        }
        tail = node;
    }
    return head;
}

// Eliminar un nodo de personaje de la lista (cuando se asigna)
void removeCharacterNode(CharacterNode** headCharacter, const char* characterName) {
    CharacterNode* current = *headCharacter;
    while (current != NULL) {
        if (strcmp(current->name, characterName) == 0) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                *headCharacter = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            }
            free(current);
            return;
        }
        current = current->next;
    }
}
