#ifndef MACROS_H
#define MACROS_H



#define BOARD_SIZE 8

// Operations MACROS

// Get bit on (square) position in bitboard
#define get_bit(bitboard, square) (((bitboard) & (1ULL << (square))) ? 1: 0)    

// Change bit on (square) position to 1
#define set_bit(bitboard, square) ((bitboard) |= (1ULL << (square)))             

// Change bit on (square) position to 0
#define clear_bit(bitboard, square) ((bitboard) &= ~(1ULL << (square)))        



#define count_bits(bitboard) __builtin_popcountll(bitboard)      // Total Number of 1 Bit in Bitboard
#define get_LSB_index(bitboard) __builtin_ctzll(bitboard)        // index of LSB, undefined if 0


#define SOURCE_SHIFT   0
#define TARGET_SHIFT   6
#define PIECE_SHIFT    12
#define PROM_SHIFT     16
#define CAPTURE_SHIFT  20
#define DOUBLE_SHIFT   21
#define ENPASSANT_SHIFT 22
#define CASTLE_SHIFT   23

#define SOURCE_MASK       0x3F
#define TARGET_MASK       0x3F
#define PIECE_MASK        0x0F
#define PROM_MASK         0x0F
#define FLAG_MASK         0x01


// 0000 0000 0000 0000 0000 0000 
// 0000 0000 0000 0000 0011 1111 - source
// 0000 0000 0000 1111 1100 0000 - target
// 0000 0000 1111 0000 0000 0000 - piece
// 0000 1111 0000 0000 0000 0000 - promotion
// 0001 0000 0000 0000 0000 0000 - capture
// 0010 0000 0000 0000 0000 0000 - double push
// 0100 0000 0000 0000 0000 0000 - enpassnt
// 1000 0000 0000 0000 0000 0000 - castle



#define encodeMove(source, target, piece, promotion, capture, doublePawnPush, Enpassant, castle) \
    ((source) << SOURCE_SHIFT) |             \
    ((target) << TARGET_SHIFT) |             \
    ((piece) << PIECE_SHIFT) |               \
    ((promotion) << PROM_SHIFT) |            \
    ((capture) << CAPTURE_SHIFT) |           \
    ((doublePawnPush) << DOUBLE_SHIFT) |     \
    ((Enpassant) << ENPASSANT_SHIFT) |       \
    ((castle) << CASTLE_SHIFT)               \
\


#define getSource(move) \
    (((move) >> SOURCE_SHIFT) & SOURCE_MASK)

#define getTarget(move) \
    (((move) >> TARGET_SHIFT) & TARGET_MASK)

#define getPiece(move) \
    (((move) >> PIECE_SHIFT) & PIECE_MASK)

#define getProm(move) \
    (((move) >> PROM_SHIFT) & PROM_MASK)

#define getCapture(move) \
    (((move) >> CAPTURE_SHIFT) & FLAG_MASK)

#define getDouble(move) \
    (((move) >> DOUBLE_SHIFT) & FLAG_MASK)

#define getEnpassant(move) \
    (((move) >> ENPASSANT_SHIFT) & FLAG_MASK)

#define getCastle(move) \
    (((move) >> CASTLE_SHIFT) & FLAG_MASK)



#define START_MEASURE_TIMER(TIMER_MEASURE_START)                                   \
    LARGE_INTEGER MEASURE_TIMER_FREQUENCY;                      \
    QueryPerformanceFrequency(&MEASURE_TIMER_FREQUENCY);        \
    U64 TIMER_MEASURE_START = getCurrentTimer(); 


#define END_MEASURE_TIMER(TIMER_MEASURE_END)                        \
    U64 TIMER_MEASURE_END = getCurrentTimer();


#define DISPLAY_MEASURED_TIMER(TIMER_MEASURE_START, TIMER_MEASURE_END)                                                    \
                                                                                    \
    double TIMER_MEASURED_SECONDS =                                                 \
        (double) (TIMER_MEASURE_END - TIMER_MEASURE_START) /                        \
        (double) MEASURE_TIMER_FREQUENCY.QuadPart;                                  \
                                                                                    \
    if(TIMER_MEASURED_SECONDS < 1e-6)                                               \
        printf("MEASURED TIMER: %.3f ns\n", TIMER_MEASURED_SECONDS * 1e9);          \
                                                                                    \
    else if(TIMER_MEASURED_SECONDS < 1e-3)                                          \
        printf("MEASURED TIMER: %.3f us\n", TIMER_MEASURED_SECONDS * 1e6);          \
                                                                                    \
    else if(TIMER_MEASURED_SECONDS < 1)                                             \
        printf("MEASURED TIMER: %.3f ms\n", TIMER_MEASURED_SECONDS * 1e3);          \
                                                                                    \
    else                                                                            \
        printf("MEASURED TIMER: %.3f s\n", TIMER_MEASURED_SECONDS);                 


#endif