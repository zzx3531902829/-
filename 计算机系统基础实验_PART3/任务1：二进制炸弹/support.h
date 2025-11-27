#ifndef __SUPPORT_H__
#define __SUPPORT_H__

/* function prototypes */
int string_length(char *string);
int strings_not_equal(char *string1, char *string2);
void read_six_numbers(char *input, int *numbers);
char *read_line(void);
//void initialize_bomb(void);
//void initialize_bomb_solve(void);
void explode_bomb(void);
void phase_defused(void);
void invalid_phase(char *s);
char *cuserid(char *string);
//void secret_phase();

extern void phase_1(char *input);
extern void phase_2(char *input);
extern void phase_3(char *input);
extern void phase_4(char *input);
extern void phase_5(char *input);
extern void phase_6(char *input);

typedef struct nodeStruct
{
    int value;
    int index;
    struct nodeStruct *next;
} listNode;

/* some constants */
#define SECRET_PHRASE     "DrEvil"
#define MAX_STRINGS        20
#define MAX_LINE               80


#endif /* __SUPPORT_H__ */

