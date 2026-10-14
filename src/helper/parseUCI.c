#include "helper.h"
#include "macros.h"
#include "constants.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int UCI_to_move(const gameState *state, char *UCI_move)
{
    int source = UCI_move[0] - 'a' + (8 - UCI_move[1] + '0') * 8;
    int target = UCI_move[2] - 'a' + (8 - UCI_move[3] + '0') * 8;

    int move_val = -1;

    moveList move = {
        .count = 0
    };

    generateMoves(state, &move);

    for(int i=0; i < move.count; i++)
    {
        if( source == getSource(move.move[i]) && target == getTarget(move.move[i]))
        {
            if(getProm(move.move[i]))
            {
                if((getProm(move.move[i]) == asciiToPieces[UCI_move[4]])){
                    move_val = move.move[i];
                    break;
                }
            }
            else
            {
                move_val = move.move[i];
                break;
            }
        }
    }

    return move_val;
}


static void moveToUCI(int move, char *out)
{
    const char *src = squareToString[getSource(move)];
    const char *dst = squareToString[getTarget(move)];

    out[0] = src[0]; out[1] = src[1];
    out[2] = dst[0]; out[3] = dst[1];

    int prom = getProm(move);
    if(prom){
        out[4] = tolower(asciiPiece[prom]);
        out[5] = '\0';
    } else {
        out[4] = '\0';
    }
}

// "position startpos [moves ...]" or "position fen <fen> [moves ...]"
static void parsePosition(gameState *state, char *cmd)
{
    static const char *startFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    char *ptr = cmd + strlen("position");
    while(*ptr == ' ') ptr++;

    if(!strncmp(ptr, "startpos", 8)){
        parseFEN(state, (char *) startFEN);
        ptr += 8;
    }
    else if(!strncmp(ptr, "fen", 3)){
        ptr += 3;
        while(*ptr == ' ') ptr++;

        char fen[128];
        char *movesAt = strstr(ptr, " moves");

        size_t len = movesAt ? 
            (size_t)(movesAt - ptr) 
            : strlen(ptr);

        if(len >= sizeof(fen) - 2) 
            len = sizeof(fen) - 2;
            
        memcpy(fen, ptr, len);

        fen[len] = ' ';          
        fen[len + 1] = '\0';

        parseFEN(state, fen);
        ptr += len;
    }
    else {
        return;
    }

    char *moves = strstr(ptr, "moves");
    if(!moves) return;
    moves += 5;

    while(*moves)
    {
        while(*moves == ' ') moves++;
        if(!*moves) break;

        char token[8] = {0};
        int n = 0;
        while(moves[n] && moves[n] != ' ' && n < 7){ token[n] = moves[n]; n++; }
        moves += n;

        int move = UCI_to_move(state, token);
        if(move == -1 || !makeMove(state, move)) break;
    }
}


static void parseGo(gameState *state, char *cmd)
{
    int depth = 6;   

    char *d = strstr(cmd, "depth");
    if(d){
        int value = atoi(d + 5);
        if(value > 0) depth = value;
    }

    int best = getBestMove(state, depth);

    if(best == -1){
        printf("bestmove 0000\n");
    } else {
        char str[6];
        moveToUCI(best, str);
        printf("bestmove %s\n", str);
    }
    
    fflush(stdout);
}


void uciLoop(gameState *state)
{
    char line[2048];

    setbuf(stdout, NULL);
    parseFEN(state, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    while(fgets(line, sizeof(line), stdin))
    {
        line[strcspn(line, "\r\n")] = '\0';

        if(!strcmp(line, "uci")){
            printf("id name bitC\n");
            printf("id author DlightSair\n");
            printf("uciok\n");
        }
        else if(!strcmp(line, "isready")){
            printf("readyok\n");
        }
        else if(!strcmp(line, "ucinewgame")){
            parseFEN(state, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        }
        else if(!strncmp(line, "position", 8)){
            parsePosition(state, line);
        }
        else if(!strncmp(line, "go", 2)){
            parseGo(state, line);
        }
        else if(!strcmp(line, "d")){
            printBoard(*state);
        }
        else if(!strcmp(line, "quit")){
            break;
        }
    }
}
