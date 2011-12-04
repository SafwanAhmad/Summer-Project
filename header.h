#ifndef _HEADER_H
#define _HEADER_H

#define _POSIX_C_SOURCE 200000L
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<unistd.h>
#include<signal.h>
#include <gtk/gtk.h>
#include<pthread.h>

char RAM[32][8];

#if defined PIC10F200 || PIC10F204
#define PROGRAMMEM 256
#define STACKSIZE 8
#define PCH_SIZE 3
#endif

#if defined PIC10F202 || PIC10F206
#define PROGRAMMEM 512
#define STACKSIZE 9
#define PCH_SIZE 3
#endif


//assigning the user ID locations in ROM

#if defined PIC10F200 || PIC10F204
#define UID0 256
#define UID1 257
#define UID2 258
#define UID3 259
#endif     

#if defined PIC10F202 || PIC10F206
#define UID0 512
#define UID1 513
#define UID2 514
#define UID3 515
#endif     

//assigning Backup OSCCAL locations in ROM

#if defined PIC10F200 || PIC10F204
#define BACKUP_OSCCAL 260
#endif
        
#if defined PIC10F202 || PIC10F206
#define BACKUP_OSCCAL 516
#endif
        
//assigning CONFIGURATION WORD locations in ROM
        
#if defined PIC10F200 || PIC10F204
#define CONFIG_WORD 511
#endif
        
#if defined PIC10F202 || PIC10F206
#define CONFIG_WORD 1023
#endif


enum{INDF,TMR0,PCL,STATUS,FSR,OSCCAL,GPIO,CMCON0};
typedef enum{POR,MCLR_NOR,MCLR_S,WDT_S,WDT_NOR,WAKE_PIN,WAKE_COMP} RESET_TYPES;
enum{ADDWF,ANDWF,CLRF,CLRW,COMF,DECF,DECFSZ,INCF,INCFSZ,IORWF,MOVF,MOVWF,NOP,RLF,RRF,SUBWF,SWAPF,XORWF,BCF,BSF,BTFSC,BTFSS,ANDLW,CALL,CLRWDT,GOTO,IORLW,MOVLW,OPT,RETLW,SLEEP,TRIS,XORLW};


void calltobuffer(char *, char, int);
void LOADROM();
void INITSFR_RESET(RESET_TYPES);

void DECODER();
void push();
void pop();
int STRING2INT(char *, int, int);
void INCRPC();
void PRINTSTATUS();
void EXECUTE();
void CLOCK();

char ROM[PROGRAMMEM][12];
char STACK[2][STACKSIZE];
char W[8];
char OPTION[8];
char TRISGPIO[8];
extern int TOS ;
char PCH[PCH_SIZE];
char WDT[8];
int OPERATION;

int CYCLE;

void print_values();

#endif /*_HEADER_H */
