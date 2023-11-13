#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void display() 
{

    char str;
    FILE *f1, *f2, *f3;   

    printf("\nThe contents of Input Table :\n\n");
    f1 = fopen("input.txt", "r");
    str = fgetc(f1);
    while (str != EOF) 
    {
        printf("%c", str);
        str = fgetc(f1);
    }
    fclose(f1);

    printf("\n\nThe contents of Output Table :\n\n");
    f2 = fopen("intermediate.txt", "r");
    str = fgetc(f2);
    while (str != EOF) 
    {
        printf("%c", str);
        str = fgetc(f2);
    }
    fclose(f2);

    printf("\n\nThe contents of Symbol Table :\n\n");
    f3 = fopen("symtab.txt", "r");
    str = fgetc(f3);
    while (str != EOF) 
    {
        printf("%c", str);
        str = fgetc(f3);
    }
    fclose(f3);
}
void pass1(char label[10], char opcode[10], char operand[10], char code[10], char mnemonic[3]) 
{
    int locctr, start, length;

    FILE *f1, *f2, *f3, *f4, *f5;                                  
    f1 = fopen("input.txt", "r");
    f2 = fopen("optab.txt", "r");

    f3 = fopen("symtab.txt", "w");
    f4 = fopen("intermediate.txt", "w");
    f5 = fopen("length.txt", "w");

    fscanf(f1, "%s\t%s\t%s", label, opcode, operand);             

    if (strcmp(opcode, "START") == 0) 
    {                       
        start = atoi(operand);                                    
        locctr = start;
        fprintf(f4, "\t%s\t%s\t%s\n", label, opcode, operand);    
        fscanf(f1, "%s\t%s\t%s", label, opcode, operand);      
    } 
    else 
    {
        locctr = 0;
    }

    while (strcmp(opcode, "END") != 0) 
    {

        fprintf(f4, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);

        if (strcmp(label, "__") != 0) 
        {
            fprintf(f3, "%s\t%d\n", label, locctr);
        }

        fscanf(f2, "%s\t%s", code, mnemonic);

        while (strcmp(code, "END") != 0) 
        {
            if (strcmp(opcode, code) == 0) 
            {          
                locctr += 3;
                break;
            }
            fscanf(f2, "%s\t%s", code, mnemonic);
        }

        
        if (strcmp(opcode, "WORD") == 0) 
        {
            locctr += 3;
        }
        else if (strcmp(opcode, "RESW") == 0) 
        {
            locctr += (3 * (atoi(operand)));                       
        }
        else if (strcmp(opcode, "BYTE") == 0) 
        {
            ++locctr;
        }
        
        else if (strcmp(opcode, "RESB") == 0) 
        {
            locctr += atoi(operand);
        }
        fscanf(f1, "%s\t%s\t%s", label, opcode, operand);
    }

    fprintf(f4, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);

    fclose(f4);
    fclose(f3);
    fclose(f2);
    fclose(f1);

    display();
    
    length = locctr - start;
    fprintf(f5, "%d", length);
    fclose(f5);
    printf("\nThe length of the code : %d\n", length);
}
int main()
{
    char label[10], opcode[10], operand[10];
    char code[10], mnemonic[3];
    pass1(label, opcode, operand, code, mnemonic);
    return 0;
}
