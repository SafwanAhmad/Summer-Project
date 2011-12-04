#include "header.h"
#include <gtk/gtk.h>

int TOS = 0;
extern char instruction[12];

//used for gtk 
void 
on_window_destroy ( gpointer user_data)
{
        gtk_main_quit();
}

// MAIN FUNCTION 

int main(int argc, char *argv[])
{
        LOADROM();
        INITSFR_RESET(POR); 
       
        GtkBuilder              *builder;
        GtkWidget               *window;
        
        gtk_init (&argc, &argv);
        
        builder = gtk_builder_new ();
        gtk_builder_add_from_file (builder, "window.xml", NULL);

        window = GTK_WIDGET (gtk_builder_get_object (builder, "window1"));
        gtk_builder_connect_signals (builder, NULL);          
        g_object_unref (G_OBJECT (builder));
        
        gtk_widget_show (window);       
        gtk_main (); 
        
        CLOCK();
        
        return 0;
}     


void calltobuffer(char *buffer , char val , int count)
{
       // printf("count = %d\n",count); //debug
       // printf("val = %c\n",val); //debug

        if(val == '0')
        {
                buffer[0+4*count] = '0';           
                buffer[1+4*count] = '0'; 
                buffer[2+4*count] = '0'; 
                buffer[3+4*count] = '0'; 
        }
        else if(val == '1')
        {
                buffer[0+4*count] = '0';           
                buffer[1+4*count] = '0'; 
                buffer[2+4*count] = '0'; 
                buffer[3+4*count] = '1';
        }
        else if(val == '2')
        {
                buffer[0+4*count] = '0';           
                buffer[1+4*count] = '0'; 
                buffer[2+4*count] = '1'; 
                buffer[3+4*count] = '0';
        }
        
        else if(val == '3')
        {
                buffer[0+4*count] = '0';           
                buffer[1+4*count] = '0'; 
                buffer[2+4*count] = '1'; 
                buffer[3+4*count] = '1';
        }
        
        else if(val == '4')
        {
                buffer[0+4*count] = '0';           
                buffer[1+4*count] = '1'; 
                buffer[2+4*count] = '0'; 
                buffer[3+4*count] = '0';
        }
        
        else if(val == '5')
        {
                buffer[0+4*count] = '0';           
                buffer[1+4*count] = '1'; 
                buffer[2+4*count] = '0'; 
                buffer[3+4*count] = '1';
        }
        
        else if(val == '6')
        {
                buffer[0+4*count] = '0';           
                buffer[1+4*count] = '1'; 
                buffer[2+4*count] = '1'; 
                buffer[3+4*count] = '0';
        }
        
        else if(val == '7')
        {
                buffer[0+4*count] = '0';           
                buffer[1+4*count] = '1'; 
                buffer[2+4*count] = '1'; 
                buffer[3+4*count] = '1';
        }
        
        else if(val == '8')
        {
                buffer[0+4*count] = '1';          
                buffer[1+4*count] = '0'; 
                buffer[2+4*count] = '0'; 
                buffer[3+4*count] = '0';
        }
        
        else if(val == '9')
        {
                buffer[0+4*count] = '1';           
                buffer[1+4*count] = '0'; 
                buffer[2+4*count] = '0'; 
                buffer[3+4*count] = '1';
        }
        
        else if(val == 'a')
        {
                buffer[0+4*count] = '1';           
                buffer[1+4*count] = '0'; 
                buffer[2+4*count] = '1'; 
                buffer[3+4*count] = '0';
        }
        
        else if(val == 'b')
        {
                buffer[0+4*count] = '1';           
                buffer[1+4*count] = '0'; 
                buffer[2+4*count] = '1'; 
                buffer[3+4*count] = '1';
        }
        
        else if(val == 'c')
        {
                buffer[0+4*count] = '1';           
                buffer[1+4*count] = '1'; 
                buffer[2+4*count] = '0'; 
                buffer[3+4*count] = '0';
        }
        
        else if(val =='d')
        {
                buffer[0+4*count] = '1';           
                buffer[1+4*count] = '1'; 
                buffer[2+4*count] = '0'; 
                buffer[3+4*count] = '1';
        }
        else if(val == 'e')
        {
                buffer[0+4*count] = '1';           
                buffer[1+4*count] = '1'; 
                buffer[2+4*count] = '1'; 
                buffer[3+4*count] = '0';
        }
        else if(val == 'f')
        {
                buffer[0+4*count] = '1';           
                buffer[1+4*count] = '1'; 
                buffer[2+4*count] = '1'; 
                buffer[3+4*count] = '1'; 
        }
              
}




// This function is used to model the ROM
void LOADROM()
{
        
        char buffer[12];
        
        FILE *ptr;
        char valread;
        int count , rowindex;
        
        ptr = fopen("INPUT","r");
        
        if(ptr == NULL)
        {
                perror("Error occured, could not open the file\n");
        }
        
        else
        {
                printf("File opened successfully\n");
        }
        
        //readind from file
     
        count = 0;
        rowindex = 0;
        while((valread = fgetc(ptr)) != EOF)
        {
                //printf("valread = %c\n",valread); //debug
                                
                if(valread != '\n')
                {
                        calltobuffer(buffer , valread, count);
                        count++;
                }
                if(count == 3) 
                {
                        count=0;
                        for(int i = 0 ; i < sizeof(buffer); i++)
                        {
                             // printf("[%c]",buffer[i]); //debug
                                ROM[rowindex][i] = buffer[i];
                        }
                       // printf("\n");
                        //to increment the row number
                        rowindex++;
                        
                        
                }
              //  sleep(1);
                        
                                    
        }
        fclose(ptr);
        
/*        //Writing the reset vector at 0x0ff for PIC10F200/204 or at 0x1ff for PIC10F202/206
        
        ROM[rowindex][0] = '1';
        ROM[rowindex][1] = '1'; 
        ROM[rowindex][2] = '0';
        ROM[rowindex][3] = '0';
        ROM[rowindex][4] = '1';
        ROM[rowindex][5] = '1';
        ROM[rowindex][7] = '1';
        ROM[rowindex][6] = '1';
        ROM[rowindex][8] = '1';
        ROM[rowindex][9] = '1';
        ROM[rowindex][10] = '1';
        ROM[rowindex][11] = '1';
       
 */
                    
}

//this function initializes the SFR on resets these are in the RAM

void INITSFR_RESET(RESET_TYPES type_reset)
{
        if(type_reset == POR )
        {     
                memcpy(RAM[INDF],"xxxxxxxx",8);
                memcpy(RAM[TMR0],"xxxxxxxx",8);
                memcpy(RAM[PCL],"11111111",8);
        
                #if defined PIC10F204 || PIC10F206
                memcpy(RAM[STATUS],"00-11xxx",8);
                #endif
        
                #if defined PIC10F200 || PIC10F202
                memcpy(RAM[STATUS],"0r-11xxx",8);  //r is for reserved
                #endif
                
                memcpy(RAM[FSR],"111xxxxx",8);
                memcpy(RAM[OSCCAL],"11111110",8);
                memcpy(RAM[GPIO],"----xxxx",8);
        
                #if defined PIC10F204 || PIC10F206
                memcpy(RAM[CMCON0],"11111111",8);
                #endif
        
                #if defined PIC10F200 || PIC10F202
                memcpy(RAM[CMCON0],"--------",8);
                #endif
        
                memcpy(W,"qqqqqqq",7); //only 7 left most bits will change
                memcpy(OPTION,"11111111",8);
                memcpy(TRISGPIO,"----1111",8);
        }        
                
                
        else
        {
        
                memcpy(W,"qqqqqqq",7);
                memcpy(RAM[PCL],"11111111",8);
                
                
                if(type_reset == MCLR_NOR)
                {
                        memcpy(RAM[STATUS],"000",3);
                }
                else if(type_reset == MCLR_S)
                {
                        memcpy(RAM[STATUS],"00010",5);
                }
                
                else if(type_reset == WDT_S)
                {
                        memcpy(RAM[STATUS],"00000",5);
                }
                
                else if(type_reset == WDT_NOR)
                {
                        memcpy(RAM[STATUS],"0000",4);
                }
                
                else if(type_reset == WAKE_PIN)
                {
                        memcpy(RAM[STATUS],"10010",5);
                }
                
                else if(type_reset == WAKE_COMP)
                {
                        memcpy(RAM[STATUS],"01010",5);
                }
                
                
                memcpy(RAM[FSR],"111",3);
                memcpy(RAM[GPIO],"----",4);
                memcpy(OPTION,"11111111",8);
                memcpy(TRISGPIO,"----1111",8);
        }
        
        
        
}




//Function for the decoder
//This function takes an instruction as an argument and decode it then update the registers


void DECODER()
{
        memcpy(RAM[31],"01010101",8);//debug
        memcpy(W,"00101010",8);//debug
           
    //    memcpy(instruction,"000010111111",12); //debug
       
        
        //THESE ARE LITERAL AND CONTROL OPERATIONS
        
        //  ANDLW instruction    
        if(memcmp(instruction,"1110",4) == 0)
        {
                OPERATION = ANDLW;
        }
        
        //CALL instruction. It is a two cycle instruction
        else if(memcmp(instruction,"1001",4) == 0)
        {
                OPERATION = CALL;                             
                
        }
        
        //CLRWDT instruction
         
        else if(memcmp(instruction,"000000000100",12) == 0)
        {
                OPERATION = CLRWDT;
        }
        
        //GOTO instruction. Its is a two cylce instruction
        
        else if(memcmp(instruction,"101",3) == 0)
        {
                OPERATION = GOTO;
        }
        
        //IORLW instruction
        else if(memcmp(instruction,"1101",4) == 0)
        {
                OPERATION = IORLW;
                                
        }
                
        //MOVLW instruction
        
        else if(memcmp(instruction,"1100",4) == 0)
        {
                OPERATION = MOVLW;
        }
        
        //OPTION instruction
        
        else if(memcmp(instruction,"000000000010",12) == 0)
        {
                OPERATION = OPT;
        }
        
        //RETLW instruction. It is a two cycle instruction
        
        else if(memcmp(instruction,"1000",4) == 0)
        {
                OPERATION = RETLW;
        }       
                               
        //SLEEP instruction
        
        else if(memcmp(instruction,"000000000011",12) == 0)
        {
                OPERATION = SLEEP;
        }
        
        //TRIS instruction
        
        else if(memcmp(instruction,"0000",4) == 0 && memcmp(&instruction[9],"110",3) == 0)
        {
                OPERATION = TRIS;
        }
        
        //XORLW instruction
        
        else if(memcmp(instruction,"1111",4) == 0 )
        {
                OPERATION = XORLW;
        }
        
        //THESE ARE BIT-ORIENTED FILE REGISTER OPERATIONS
        
        //BCF instruction
        
        else if(memcmp(instruction,"0100",4) == 0)
        {
                OPERATION = BCF;
        }
        
        //BSF instruction
        
        else if(memcmp(instruction,"0101",4) == 0)
        {
                OPERATION = BSF;
        }
        
        //BTFSC instruction
        
        else if(memcmp(instruction,"0110",4) == 0)
        {
                OPERATION = BTFSC;
        }
        
        //BTFSS instruction
        
        else if(memcmp(instruction,"0111",4) == 0)
        {
                OPERATION = BTFSS;
        }
        
        // THESE ARE BYTE ORIENTED FILE REGISTER OPERATIONS
        
        //ADDWF instruction
        
        else if(memcmp(instruction,"000111",6) == 0)
        {
                OPERATION = ADDWF;
                
                
        }
        
        
        // ANDWF instruction                          
        
        else if(memcmp(instruction,"000101",6) == 0)
        {
                OPERATION = ANDWF;       
        }
        
        //CLRF instruction
        
        else if(memcmp(instruction,"0000011",7) == 0)
        {
                OPERATION = CLRF;
        }
        
        //CLRW instruction
        
        else if(memcmp(instruction,"000001000000",12) == 0)
        {
                OPERATION = CLRW;
        }
        
        //COMF instruction
        
        else if(memcmp(instruction,"001001",6) == 0)
        {
                OPERATION = COMF;
        }
              
        
         // DECF instruction
         
        else if(memcmp(instruction,"000011",6) == 0)
        {
                OPERATION = DECF;
                
        }
        
        //DECFSZ instruction
        
        else if(memcmp(instruction,"001011",6) == 0)
        {
                OPERATION = DECFSZ;
                               
        }        
        
        //INCF instruction
        
        else if(memcmp(instruction,"001010",6) == 0)
        {
                OPERATION = INCF;
        }
        
        
        //INCFSZ instruction
        
        else if(memcmp(instruction,"001111",6) == 0)
        {
                OPERATION = INCFSZ;
        }
        
        //IORWF instruction
        
        else if(memcmp(instruction,"000100",8) == 0)
        {
                OPERATION = IORWF;
        }
        
        //MOVF instruction
        
        else if(memcmp(instruction,"001000",6) == 0)
        {
                OPERATION = MOVF;
                
        }
        
        //MOVWF instruction
        
        else if(memcmp(instruction,"0000001",7) == 0)
        {
                OPERATION = MOVWF;
        }
        
        //NOP instruction
        else if(memcmp(instruction,"000000000000",12) == 0)
        {
                OPERATION = NOP;
        }
        
        //RLF instruction
        
        else if(memcmp(instruction,"001101",6) == 0)
        {
                OPERATION = RLF;
        }
        
        //RRF instruction
        
        else if(memcmp(instruction,"001100",6) == 0)
        {
                OPERATION = RRF;
        }
        
        //SUBWF instruction
        
        else if(memcmp(instruction,"000010111111",12) == 0)
        {
                OPERATION = SUBWF;
                
        }
        
        //SWAPF instruction
        
        else if(memcmp(instruction,"001110",6) == 0)
        {
                OPERATION = SWAPF;
        }
        
        //XORWF instruction
        
        else if(memcmp(instruction,"000110",6) == 0)
        {
                OPERATION = XORWF;
        }
        
        
        
}
        



void push()
{
        #if defined PIC10F200 || PIC10F204
        if(TOS == 2)
        {
                TOS--;
                memcpy(&STACK[0],&STACK[TOS],8);
                memcpy(&STACK[TOS],RAM[PCL],8);
        }
        else
        {
                memcpy(STACK[TOS],RAM[PCL],8);
        }
        #endif

        #if defined PIC10F202 || PIC10F206
        if(TOS == 2)
        {
                TOS--;
                memcpy(&STACK[0],&STACK[TOS],9);
                memcpy(&STACK[TOS],RAM[PCL],8);
                STACK[TOS][8] = PCH[0];
        }
        else
        {
                memcpy(STACK[TOS],RAM[PCL],8);
                STACK[TOS][8] = PCH[0];
        }
        #endif
        
        TOS++;
}

void pop()
{
        TOS--;
        
        #if defined PIC10F200 || PIC10F204
        memcpy(RAM[PCL],STACK[TOS],8);
        #endif
        
        #if defined PIC10F202 || PIC10F206
        memcpy(RAM[PCL],STACK[TOS],8);
        PCH[0] = STACK[TOS][8];
        #endif
}

int STRING2INT(char temp[12] , int start , int count)
{
        int sum = 0;
        int exp = 0;
        for(int k = count; k >= 0; k--)
        {
                if(temp[start+k] == '0')
                {
                       sum = sum + 2*0;
                }
                else if(temp[start+k] == '1')
                {
                       sum = sum + pow(2.0,(float)exp);
                }
                exp++;
        }
        
        return sum;
}
                
void INCRPC()
{
        #if defined PIC10F200 || PIC10F204
        
        if(memcmp(RAM[PCL],"11111111",8) == 0)
        {
                memcpy(RAM[PCL],"00000000",8);
         
        }
        #endif
        
        #if defined PIC10F202 || PIC10F206
        
        if(memcmp(RAM[PCL],"11111111",8) == 0)
        {
                memcpy(RAM[PCL],"00000000",8);
                PCH[0] = '1';
        }
        else if(memcmp(RAM[PCL],"11111111",8) == 0 && PCH[0] == '1')
        {
                memcpy(RAM[PCL],"00000000",8);
                PCH[0] = '0';
        }
        #endif
        
        else
        {
                int carry = 1;
                
                for(int k = 7; k >= 0; k--)
                {
                        if(RAM[PCL][k] == '0' && carry == 1)
                        {
                                RAM[PCL][k] = '1';
                                carry = 0;
                        }
                        else if(RAM[PCL][k] == '1' &&  carry == 1)
                        {
                                RAM[PCL][k] = '0';
                                carry = 1;
                        }
                }
        }
}


void PRINTSTATUS()
{
        //printing the ROM contents
        //This loop can be used to see the ROM data
 /*       for(int k = 0 ; k < PROGRAMMEM ; k++)
        {
                for(int l = 0 ; l < 12; l++)
                {
                        printf("[%c]",ROM[k][l]);
                
                }
                printf("\n");
        }
        //printf("rowindex = %d\n",rowindex); //debug
   */     
        
        //printing the W register contents
        //debug part
        printf("W register\n");
        for(int k = 0; k < 8; k++)
        {         
                printf("[%c] ",W[k]);
        }
        printf("\n\n");
        
        //printing the SFR and GPR contents
        
        printf("SPECIAL FUNCTION REGISTER \n"); //debug
        for(int k = 0 ; k < 8; k++)
        {
                for(int l = 0 ; l < 8; l++)
                {
                        printf("[%c]",RAM[k][l]);
                
                }
                printf("\n");
        }
        
}


void EXECUTE()
{
        switch(OPERATION)
        {
                case ADDWF:
                {
                        if(CYCLE == 0)
                        {
                                printf("INSIDE ADDWF\n");//debug
                
                                int ramrow = STRING2INT(instruction,7,4);
                        
                                int carry = 0;
                        
                                if(instruction[6] == '0') //d value is 0
                                {
                                        for(int k = 7; k >= 0; k--)
                                        {
                                                if(RAM[ramrow][k] == '0' && W[k] == '0')
                                                {
                                                        if(carry == 1)
                                                        {
                                                                W[k] = '1';
                                                                carry = 0;
                                                        }
                                                }
                                                else if(RAM[ramrow][k] == '0' && W[k] == '1')
                                                {
                                                        if(carry == 1)
                                                        {
                                                                W[k] = '0';
                                                                carry = 1;
                                                        }
                                                }
                                                else if(RAM[ramrow][k] == '1' && W[k] == '0')
                                                {
                                                        if(carry == 0)        
                                                        {
                                                                W[k] = '1';
                                                        }
                                                        else if(carry == 1)
                                                        {
                                                                W[k] = '0';
                                                                carry = 1;
                                                        }
                                                }
                                
                                                else if(RAM[ramrow][k] == '1' && W[k] == '1')
                                                {
                                                        if(carry == 0)
                                                        {
                                                                W[k] = '0';
                                                                carry = '1';
                                                        }
                                                        else if(carry == 1)
                                                        {
                                                                W[k] = '1';
                                                                carry = 1;
                                                        }
                                                }
                                                
                                                //updating the DC value in the status register
                                                if(k == 4 && carry == 1)
                                                {
                                                        RAM[STATUS][6] = '1';
                                                }
                                        }
                                
                                        //updating the Z value in the status register
                        
                                        if(memcmp(W,"00000000",8) == 0)
                                        {
                                                RAM[STATUS][5] = '1';
                                        }
                                }
                
                
                                if(instruction[6] == '1') //d value is 1
                                {
                                        memcpy(RAM[ramrow],W,8);
                                }       
                                       
                                          
                                //updating the C values in the status register
                                if(carry == 1)
                                {
                                        RAM[STATUS][7] = '1';
                                }
                                
                                break;
                        }       
                }
                case ANDWF:
                {
                        if(CYCLE == 0)
                        {
                                printf("INSIDE ANDWF\n");//debug
                
                                int ramrow = STRING2INT(instruction,7,4);
                
               
                                for(int k = 7; k >= 0; k--)
                                {
                                        if(W[k] == '1' && RAM[ramrow][k] == '0')
                                        {
                                                W[k] = '0';
                                        }
                                }
                                
                                //updating the Z value in the status register
                                if(memcmp(W,"00000000",8) == 0)
                                {
                                        RAM[STATUS][5] = '1';
                                }
                
                
                                if(instruction[6] == '1')
                                {
                                        memcpy(RAM[ramrow],W,8);       
                                }
                                
                                break;
                        }
                }
                
                case CLRF:
                {
                        if(CYCLE == 0)
                        {
                                printf("INSIDE CLRF\n");//debug
                
                                int ramrow = STRING2INT(instruction,7,4);
                        
                                memcpy(RAM[ramrow],"00000000",8);
                        
                                RAM[STATUS][5] = '1';
                                
                                break;
                        }
                }
                
                case CLRW:
                {
                        if(CYCLE == 0)
                        {
                                printf("INSIDE CLRW\n");//debug
                
                                memcpy(W,"00000000",8);
                                RAM[STATUS][5] = '1';        
                                
                                break;
                        }
                }
                
                case COMF:
                {
                        if(CYCLE == 0)
                        {
                                printf("INSIDE COMF\n");//debug
                
                                int ramrow = STRING2INT(instruction,7,4);
                
                                for(int k = 0; k < 8; k++)
                                {
                                        if(RAM[ramrow][k] == '1')
                                        {
                                                W[k] = '0';
                                                if(instruction[6] = '1')
                                                {
                                                        RAM[ramrow][k] = '0';
                                                }
                                        }
                                        else if(RAM[ramrow][k] == '0')
                                        {
                                                W[k] = '1';
                                                if(instruction[6] == '1')
                                                {
                                                        RAM[ramrow][k] = '1';
                                                }
                                        }
                                }
                        
                                if(instruction[6] == '0')
                                {
                                        if(memcmp(W,"00000000",8) == 0)
                                        {
                                                RAM[STATUS][5] = '1';
                                        }
                                }
                                else if(instruction[6] == '1')
                                {
                                        if(memcmp(RAM[ramrow],"00000000",8) == 0)
                                        {
                                                RAM[STATUS][5] = '1';
                                        }
                                }
                                
                                break;
                        }
                }
                
                case DECF:
                {
                        if(CYCLE == 0)
                        {
                                printf("INSIDE DECF\n");//debug
                        
                                //using 2's complement method to find [f]-1
                
                                int ramrow = STRING2INT(instruction,7,4);
                
                                int carry = 0;
                
                                for(int k = 7; k >= 0; k--)
                                {
                                        if(RAM[ramrow][k] == '0' && carry == 0)
                                        {
                                                W[k] = '1';
                                        }
                                        else if(RAM[ramrow][k] == '0' && carry == 1)
                                        {
                                                W[k] = '0';
                                                carry = 1;
                                        }
                                        else if(RAM[ramrow][k] == '1' && carry == 0)
                                        {
                                                W[k] = '0';
                                                carry = 1;
                                        }
                                        else if(RAM[ramrow][k] == '1' && carry == 1)
                                        {
                                                W[k] = '1';
                                                carry = 1;
                                        }
                                }
                
                                //updating the Z value in the status register
                                RAM[STATUS][5] = '1';
                                
                
                                if(instruction[6] == '1')
                                {
                                        memcpy(RAM[ramrow],W,8);
                                }     
                                
                                break;  
                        }
                }
                
                case DECFSZ:
                {
                        if(CYCLE == 0)
                        {
                                printf("INSIDE DECFSZ\n");//debug
                
                                //using 2's complement method to find [f]-1
                        
                                int ramrow = STRING2INT(instruction,7,4);
                
                                int carry = 0;
                
                                for(int k = 7; k >= 0; k--)
                                {
                                        if(RAM[ramrow][k] == '0' && carry == 0)
                                        {
                                                W[k] = '1';
                                        }
                                        else if(RAM[ramrow][k] == '0' && carry == 1)
                                        {
                                                W[k] = '0';
                                                carry = 1;
                                        }
                                        else if(RAM[ramrow][k] == '1' && carry == 0)
                                        {
                                                W[k] = '0';
                                                carry = 1;
                                        }
                                        else if(RAM[ramrow][k] == '1' && carry == 1)
                                        {
                                                W[k] = '1';
                                                carry = 1;
                                        }
                                }
                
                
                                if(instruction[6] == '1' )
                                {
                                        memcpy(RAM[ramrow],W,8);
                                }
                        
                                if(memcmp(W,"00000000",8) == 0)
                                {       
                                        INCRPC();
                                }     
                                
                                break;  
                        }
                }
                
                case INCF:
                {
                        if(CYCLE == 0)
                        {
                                printf("INSIDE INCF\n");//debug
                
                                int ramrow = STRING2INT(instruction,7,4);
                                int carry = 1;
                        
                                for(int k = 7; k>= 0; k--)
                                {
                                        if(RAM[ramrow][k] == '0' && carry == 1)
                                        {
                                                W[k] = '1';
                                                carry = 0;
                                        }
                                        else if(RAM[ramrow][k] == '1' && carry == 1)
                                        {
                                                W[k] = '0';
                                                carry = 1;
                                        }                                  
                                        else
                                        {
                                                W[k] = RAM[ramrow][k];
                                        }
                                }
                                if(instruction[6] == '1')
                                {
                                        memcpy(RAM[ramrow],W,8);
                                }
                        
                                if(memcmp(W,"00000000",8) == 0 )
                                {
                                        RAM[STATUS][5] = '1';
                                }
                                
                                break;
                        }
                }
                
                case INCFSZ:
                {
                        if(CYCLE == 0)
                        {
                                printf("INSIDE INCFSZ\n");//debug
                
                                int ramrow = STRING2INT(instruction,7,4);
                                int carry = 1;
                
                                for(int k = 7; k>= 0; k--)
                                {
                                        if(RAM[ramrow][k] == '0' && carry == 1)
                                        {
                                                W[k] = '1';
                                                carry = 0;
                                        }
                                        else if(RAM[ramrow][k] == '1' && carry == 1)
                                        {
                                                W[k] = '0';
                                                carry = 1;
                                        }                                  
                                        else
                                        {
                                                W[k] = RAM[ramrow][k];
                                        }
                                }
                                if(instruction[6] == '1')
                                {
                                        memcpy(RAM[ramrow],W,8);
                                }
                                
                                if(memcmp(W,"00000000",8) == 0)
                                {
                                        INCRPC();
                                }
                                
                                break;
                        }
                }
                
                case IORWF:
                {
                        if(CYCLE == 0)
                        {
                                printf("INSIDE IORWF\n");//debug
                
                                int ramrow = STRING2INT(instruction,7,4);
                
                                for(int k = 0; k < 8; k++)
                                {
                                        if(W[k] == '0' && RAM[ramrow][k] == '1')
                                        {
                                                W[k] = '1';
                                        }
                                }
                        
                                if(instruction[6] == '1')
                                {       
                                        memcpy(RAM[ramrow],W,8);
                                }
                        
                                //updating the Z value in the status register
                
                                if(memcmp(W,"00000000",8) == 0)
                                {
                                        RAM[STATUS][5] = '1';
                                }
                                
                                break;
                        }
                }
                
                case MOVF:
                {
                        if(CYCLE == 0)
                        {
                                printf("INSIDE MOVF\n");//debug
                
                                int ramrow = STRING2INT(instruction,7,4);
                        
                                if(instruction[6] == '0')
                                {
                                        memcpy(W,RAM[ramrow],8);
                                        if(memcmp(W,"00000000",8) == 0)
                                        {
                                                RAM[STATUS][5] = '1';
                                        }
                                }
                                
                                break;
                        }
                }
                
                case MOVWF:
                {
                        if(CYCLE == 0)
                        {
                                printf("INSIDE MOVWF\n");//debug
                
                                int ramrow = STRING2INT(instruction,7,4);
                        
                                memcpy(RAM[ramrow],W,8);
                                break;
                        }
                }
                
                case NOP:
                {
                        if(CYCLE == 0)
                        {
                                printf("INSIDE NOP\n");//debug
                                break;
                        }
                }
                
                case RLF:
                {
                        if(CYCLE == 0)
                        {
                                printf("INSIDE RLF\n");//debug
                        
                                int ramrow = STRING2INT(instruction,7,4);
                        
                                int carry;
                        
                                if(RAM[STATUS][7] == '0')
                                {
                                        carry = 0;
                                }
                                else if(RAM[STATUS][7] == '1')
                                {
                                        carry = 1;
                                }
                        
                                memcpy(W,RAM[ramrow],8);
                                
                                //copying leftmost bit into carry
                                
                                RAM[STATUS][7] = W[0];
                        
                                for(int k = 0; k < 7; k++)
                                {
                                        W[k] = W[k+1];
                                }
                        
                                if(carry == 1)
                                {
                                        W[7] = '1';
                                }
                                else if(carry == 0)
                                {
                                        W[7] = '0';
                                }
                                
                                if(instruction[6] == '1')
                                {
                                        memcpy(RAM[ramrow],W,8);
                                }
                                break;
                        }
                }
                
                case RRF:
                {
                        if(CYCLE == 0)
                        {
                                printf("INSIDE RRF\n");//debug
                        
                                int ramrow = STRING2INT(instruction,7,4);
                        
                                int carry ;
                        
                                if(RAM[ramrow][7] == '0')
                                {
                                        carry = 0;
                                }
                                else if(RAM[ramrow][7] == '1')
                                {
                                        carry = 1;
                                }
                        
                                memcpy(W,RAM[ramrow],8);
                        
                                for(int k = 6; k >=0; k--)
                                {
                                        W[k+1] = W[k];
                                }
                        
                                W[0] = RAM[STATUS][7];
                        
                                //updating value of C in status register 
                                if(carry == 0)
                                {
                                        RAM[STATUS][7] = '0';
                                }
                                else if(carry == 1)
                                {
                                        RAM[STATUS][7] = '1';
                                }
                        
                                if(instruction[6] == '1')
                                {
                                        memcpy(RAM[ramrow],W,8);
                                }     
                                break;  
                        }
                }
                
                case SUBWF:
                {
                        if(CYCLE == 0)
                        {
                                printf("INSIDE SUBWF\n");//debug
                        
                                int ramrow = STRING2INT(instruction,7,4);
                                int borrow = 0;
                        
                                for(int k = 7; k>= 0; k--)
                                {
                                        if(W[k] == '0' && RAM[ramrow][k] == '1')
                                        {
                                                if(borrow == 0)
                                                {
                                                                                
                                                        W[k] = '1';
                                                }
                                                else if(borrow == 1)
                                                {
                                                        W[k] = '0';
                                                        borrow = 0;
                                                }
                                
                                        }
                                
                                        else if(W[k] == '0' && RAM[ramrow][k] == '0')
                                        {
                                                if(borrow == 0)
                                                {
                                                        W[k] = '0';
                                                }
                                                else if(borrow == 1)
                                                {
                                                        W[k] = '1';
                                                        borrow = 0;
                                                }
                                        }
                                        else if(W[k] == '1' && RAM[ramrow][k] == '1')
                                        {
                                                if(borrow == 0)
                                                {
                                                        W[k] = '0';
                                                }
                                                else if(borrow == 1)
                                                {
                                                        borrow = 1;
                                                        W[k] = '1';
                                                }
                                        }
                                        
                                        else if(W[k] == '1' && RAM[ramrow][k] == '0')
                                        {
                                                W[k] = '1';
                                                borrow = 1;
                                        }
                                
                                        //updating DC value in the status register
                                        if(k == 4 && borrow == 0)
                                        {
                                                RAM[STATUS][6] = '1';
                                        }
                                }
                        
                                if(borrow == 0)
                                {
                                        RAM[STATUS][7] = '1';
                                }
                                if(memcmp(W,"00000000",8) == 0)
                                {
                                        RAM[STATUS][5] = '1';
                                }
                                
                        
                                if(instruction[6] == '1')
                                {
                                        memcpy(RAM[ramrow],W,8);
                                }
                                break;
                        }
                }
                
                case SWAPF:
                {
                        if(CYCLE == 0)
                        {
                                printf("INSIDE SWAPF\n");//debug
                        
                                char low[4];
                                char high[4];
                                int ramrow = STRING2INT(instruction,7,4);
                                
                                memcpy(low,RAM[ramrow],4);
                                memcpy(high,RAM[ramrow]+4,4);
                                
                                memcpy(W+4,low,4);
                                memcpy(W,high,4);
                        
                                
                                if(instruction[6] == '1')
                                {
                                        memcpy(RAM[ramrow],W,8);
                                }
                                break;
                        }
                }
                case XORWF:
                {
                        if(CYCLE == 0)
                        {
                                printf("INSIDE XORWF\n");//debug
                
                                int ramrow = STRING2INT(instruction,7,4);
                        
                                for(int k = 0; k < 8; k++)
                                {
                                        if(W[k] == 0 && RAM[ramrow][k] == '1')
                                        {
                                                W[k] = '1';
                                        }
                                        else if(W[k] == '1' && RAM[ramrow][k] == '0')
                                        {
                                                W[k] = '1';
                                        }
                                        else
                                        {
                                                W[k] = '0';
                                        }
                                }
                        
                                if(memcmp(W,"00000000",8) == 0)
                                {
                                        RAM[STATUS][5] = '1';
                                }
                        
                                if(instruction[6] == '1')
                                {
                                        memcpy(RAM[ramrow],W,8);
                                }
                                break;
                        }
                }
                
                case BCF:
                {
                        if(CYCLE == 0)
                        {
                        printf("INSIDE BCF\n");//debug
                        
                               int ramrow = STRING2INT(instruction,7,4);
                                int ramcol = STRING2INT(instruction,4,2);
                                
                                printf("ramrow = %d , ramcol = %d\n",ramrow,ramcol); // debug
                                        
                                RAM[ramrow][ramcol] = '0';
                                
                                break;
                        }
                }
                
                case BSF:
                {
                        if(CYCLE == 0)
                        {
                                printf("INSIDE BSF\n");//debug
                        
                                int ramrow = STRING2INT(instruction,7,4);
                                int ramcol = STRING2INT(instruction,4,2);
                                
                                printf("ramrow = %d , ramcol = %d\n",ramrow,ramcol);
                        
                                RAM[ramrow][ramcol] = '1';
                                
                                break;
                        }
                }
                
                case BTFSC:
                {
                        if(CYCLE == 0)
                        {
                               printf("INSIDE BTFSC\n");//debug
                        
                               int ramrow = STRING2INT(instruction,7,4);
                               int ramcol = STRING2INT(instruction,4,2);
                        
                               printf("ramrow = %d , ramcol = %d\n",ramrow,ramcol);
                        
                               if(RAM[ramrow][ramcol] == '0')
                               {
                                       //PC will be incremanted so as to skip the next instruction
                                       INCRPC();
                               }      
                               
                               break; 
                       }
                }       
                
                case BTFSS:
                {
                        if(CYCLE == 0)
                        {
                                printf("INSIDE BTFSS\n");//debug
                        
                                int ramrow = STRING2INT(instruction,7,4);
                                int ramcol = STRING2INT(instruction,4,2);
                                
                                printf("ramrow = %d , ramcol = %d\n",ramrow,ramcol);
                        
                                if(RAM[ramrow][ramcol] == '1')
                                {
                                        //PC will be incremanted so as to skip the next instruction
                                        INCRPC();
                                }
                                
                                break;
                        }
                }
                
                case ANDLW:
                {
                        if(CYCLE == 0)
                        {
                                printf("INSIDE ANDLW\n");//debug
                                char temp[8];
                        
                                memcpy(temp,&instruction[4],8);
                                for(int k = 0; k < 8; k++)
                                {
                                        W[k] = W[k] && temp[k];
                                }
                                
                                if(memcmp(W,"00000000",8) == 0)
                                {
                                        RAM[STATUS][5] = '1';  //Status register updated with ZERO flag set
                                }
                                
                                break;
                        }
                }
                
                case CALL:
                {
                        if(CYCLE == 0)
                        {
                                printf("INSIDE CALL\n");//debug
                
                                int carry = 1; // PC is incremented by 1 which can be assumed to be an input carry
                
                                for(int k = 0; k < 8; k++)
                                {
                                        if(RAM[PCL][k] == 0 && carry == 1)
                                        {
                                                carry = 0;
                                                RAM[PCL][k] = '1';
                                        }
                                
                                        else if(RAM[PCL][k] == 1 && carry == 1)
                                        {
                                                carry = 1;
                                                RAM[PCL][k] = '0';
                                        }
                                }
                
                                push();
                                CYCLE = -1;
                                break;
                        }
                        else if(CYCLE == -1)
                        {
                                printf("INSIDE CALL 2nd CYCLE\n");
                                memcpy(RAM[PCL],&instruction[4],8); //literal is copied to PCL
                                PCH[0] = '0';                      //PC[8] = PCH[0] is cleared
                                memcpy(&PCH[1],&RAM[STATUS][1],2);   //STATUS<6:5> are loaded into PCH<2:1>
                                CYCLE = 0;                
                                break;
                        }
                }
                
                case CLRWDT:
                {
                        if(CYCLE == 0)
                        {                                
                                printf("INSIDE CLRWDT\n");//debug
                        
                                memcpy(WDT,"00000000",8); //Watch dog timer register cleared
                        
                                if(OPTION[4] == '1') //Prescaler assigned to WDT
                                {
                                        OPTION[4] = '0'; //Assigned to TIMER0
                                }
                                RAM[STATUS][3] = '1' ; //TO(bar) is set
                                RAM[STATUS][4] = '1' ; //PD(bar) is set
                                                
                                break;
                        }
                }
                
                case GOTO:
                {
                        if(CYCLE == 0)
                        {
                                printf("INSIDE GOTO\n");//debug
                
                                //first copying the 9th bit to PCH[0]
                
                                PCH[0] = instruction[3];
                                //then copying the left literal to PCL
                        
                                memcpy(RAM[PCL],&instruction[4],8);
                                
                                CYCLE = -1;
                                break;
                        }
                        
                        else if(CYCLE == -1)
                        {
                                //now STATUS<6:5> -> PC<10:9>
                
                                memcpy(&PCH[1],&RAM[STATUS][1],2);      
                                CYCLE = 0;
                                break;
                        }
                }
                
                case IORLW:
                {
                        if(CYCLE == 0)
                        {
                                printf("INSIDE IORLW\n");//debug
                        
                                for(int k = 0; k< 8; k++)
                                {
                                        if(W[k] == '0' && instruction[4+k] == '1')
                                        {
                                                W[k] = '1';
                                        }
                                
                                }
                                        
                                if(memcmp(W,"00000000",8) == 0)
                                {
                                        RAM[STATUS][5] = '1';
                                }
                                break;
                        }
                }
                
                case MOVLW:
                {
                        if(CYCLE == 0)
                        {
                        
                                printf("INSIDE MOVLW\n");//debug
                        
                                memcpy(W,&instruction[4],8);
                                break;
                        }
                }
                                
                case OPT:
                {
                        if(CYCLE == 0)
                        {
                                printf("INSIDE OPTION\n");//debug
                        
                                memcpy(OPTION,W,8);
                                break;
                        }
                }
                        
                case RETLW:
                {
                        if(CYCLE == 0)
                        {
                                printf("INSIDE RETLW\n");//debug
                
                                memcpy(W,&instruction[4],8); //literal copied to W
                                
                                CYCLE = -1;
                                break;
                        }
                        else if(CYCLE == -1)
                        {
                                pop(); //load PC with value from TOS
                                CYCLE = 0;
                                break;
                        }
                }
                
                case SLEEP:
                {
                        if(CYCLE == 0)
                        {
                                printf("INSIDE SLEEP\n");//debug
                        
                                memcpy(WDT,"00000000",8); //WDT cleared
                                OPTION[4] = '0'; //prescaler assigned to TIMER0
                        
                                RAM[STATUS][3] = '1' ; //TO(bar) set 
                                RAM[STATUS][4] = '0' ;//PD(bar) cleared
                                
                                break;
                        }
                }
                        
                case TRIS:
                {
                        if(CYCLE == 0)
                        {
                                printf("INSIDE TRIS\n");//debug
                        
                                memcpy(&RAM[GPIO][4],&W[4],4); //lower 4 bits of W are copied into GPIO lower
                                break;
                        }
                }
                        
                case XORLW:
                {
                        if(CYCLE == 0)
                        {
                                printf("INSIDE XORLW\n");//debug
                        
                                for(int k = 0; k < 8; k++)
                                {
                                        if(W[k] == '0' && instruction[4+k] == '1')
                                        {
                                               W[k] = '1';
                                        }
                                        else if(W[k] == '1' && instruction[4+k] == '1')
                                        {
                                                W[k] = '0';
                                        }
                                }
                                
                                if(memcmp(W,"00000000",8) == 0)
                                {
                                        RAM[STATUS][5] = '1';
                                }
                                break;
                        }
                }
        }//end of option
}
