#include <stdio.h>
#include <stdlib.h>
#include <conio.h>  
#include <time.h>  
#include <stdint.h>


#define SIZE 100


struct koloniData {
       char kolonicode;
       int32_t popilation, foodstock; 
       int win, lose, is_death;
};

int* dataUnPacker(char* stringData, int space_char);
int powerOfTenPositive(int num);
int Savas();

int main()
{
    
    srand(time(NULL));
    char str[SIZE];
    char ch;
    int string_size = 0;
    int space_char = 0, last_space_temp = 0;
    //printf("%d\n", Savas());
    printf("Koloni popilasyonlarini bosluk kullanarak ayirarak giriniz: ");
    
    while ((int)(ch = getch()) != 13 && (string_size < SIZE-1)) {
        str[string_size] = ch;
        if (ch == (char)8) {
            printf("\b \b");
            --string_size;
            if(last_space_temp)
                space_char--;
        }
        else {
            ++string_size;
            printf("%c", ch);
        if (ch == (char)' ') {
           space_char++;
           last_space_temp = 1;
        } else {
               last_space_temp = 0;
               }
        }
        
    }
    str[string_size] = ' ';
    space_char++;
    str[string_size + 1] = '\0';
    struct koloniData *koloniler = (struct koloniData *)malloc(space_char * sizeof(struct koloniData));
    //printf("\n%s\n%d", str, space_char);
    int* num_data_res = dataUnPacker(str, space_char);
    printf("\n");
    int i, j;
    
    char code[10] = {'%', '@', 'æ', '*', '?', '½', '£', '#', '$', '&'};
    
    for (i = 0; i < space_char; i++) 
        koloniler[i].kolonicode = code[i];

    for (i = 0; i < space_char; i++) 
        koloniler[i].popilation = num_data_res[i];
        
    for (i = 0; i < space_char; i++)
        koloniler[i].foodstock = num_data_res[i]*num_data_res[i];

    for (i = 0; i < space_char; i++)
        koloniler[i].win = 0;

    for (i = 0; i < space_char; i++)
        koloniler[i].lose = 0;

    for (i = 0; i < space_char; i++)
        koloniler[i].is_death = 0;
        

    for(i = 0; i < space_char; i++)
        printf("%d ", num_data_res[i]);
    free(num_data_res);
        // char kolonicode
//int popilation, foodstock, win, lose, is_death;
        
    
    
    
    
    //for(i = 0; i < space_char; i++)
    int death_count = 0;
    int turn_count = 1;
    int is_break = 0;
    while(1) {
    printf("----------------------------------------------------------------------------\n");
    printf("Tur Sayisi: %d\n", turn_count);
    printf("Koloni    Popilasyon   Yemek Stogu     Kazanma    Kaybetme\n");
    turn_count++;
    for(i = 0; i < space_char; i++) {
          if(!koloniler[i].is_death&&(koloniler[i].popilation <= 0||koloniler[i].foodstock <= 0)) {
                       death_count++;
                       koloniler[i].is_death = 1;
                       printf("%d oldu.\n", i);
          }
          if(!koloniler[i].is_death)
                printf("%4c %8d %13d %13d %13d\n", koloniler[i].kolonicode, koloniler[i].popilation, koloniler[i].foodstock, koloniler[i].win, koloniler[i].lose);
          else
                printf("%4c      --        --       --      --\n", koloniler[i].kolonicode);
          
    }
    printf("----------------------------------------------------------------------------\n");
    
    for(i = 0; i < space_char-1; i++)
          for(j = i + 1; j < space_char; j++) {
                if(!(koloniler[i].is_death||koloniler[j].is_death)) {
                int temp_savas_1 = Savas(); //i kolonisi
                int temp_savas_2 = Savas(); //j kolonisi22
                int kazanan;
                int foodtransfertemp;
                
                if(temp_savas_1 == temp_savas_2) {
                              if(koloniler[i].popilation == koloniler[j].popilation)
                                     kazanan = rand()%2+1;
                              else if (koloniler[i].popilation > koloniler[j].popilation)
                                     kazanan = 1;
                              else
                                     kazanan = 2;
                              
                } else if(temp_savas_1 > temp_savas_2) {
                       kazanan = 1;
                } else {
                       kazanan = 2;
                       }
                
                       if(kazanan == 1) {
                           koloniler[i].win++;
                           koloniler[j].lose++;
                           koloniler[j].popilation -= koloniler[j].popilation*((int)((double)(temp_savas_1 - temp_savas_2)/1000));
                           foodtransfertemp = (int)(((double)koloniler[j].foodstock/100)*10);
                           koloniler[i].foodstock += foodtransfertemp;
                           koloniler[j].foodstock -= foodtransfertemp;
                           
                           }
                       else {
                           koloniler[i].lose++;
                           koloniler[j].win++;
                           koloniler[i].popilation -= koloniler[i].popilation*((int)((double)(temp_savas_2 - temp_savas_1)/1000));
                           foodtransfertemp = (int)(((double)koloniler[i].foodstock/100)*10);
                           koloniler[j].foodstock += foodtransfertemp;
                           koloniler[i].foodstock -= foodtransfertemp;
                           
                           }
                }
          }
          for(i = 0; i < space_char; i++) {
                koloniler[i].popilation += (int)(((double)koloniler[i].popilation/100)*20);
                koloniler[i].foodstock -= koloniler[i].popilation*2;
                }
    if(death_count >= space_char-1)
                   break;
    printf("Savasi devam ettirmek icin tiklayiniz... \n");
    //while(!getch());
}
    
    
    free(koloniler);
    while(!getch());
    return 0;
}


int Savas() {
    int val = (rand()*rand()*rand())%1000;
        return val < 0 ? -val : val;
}


int powerOfTenPositive(int num) {
    int res = 1;
    int i;
    for(i = 0; i < num; i++)
        res *= 10;
    return res;
}



int* dataUnPacker(char* stringData, int space_char) {
    int temp = 0;
    int stringIndex = 0;
    int *numData = (int *)malloc(space_char * sizeof(int));
    int i;
    for(i = 0; i < space_char; i++)
        numData[i] = 0;
    space_char = 0;
    while(stringData[stringIndex] != '\0') {
        while(stringData[stringIndex] != ' ') {
            stringIndex++;
            temp++;
        }
        for(i = temp-1; i >= 0; i--) {
            numData[space_char] += powerOfTenPositive(i)*(stringData[stringIndex - i - 1] - '0');
        }
        space_char++;
        stringIndex++;
        temp = 0;
    }
    
    
    return numData;
        
}
