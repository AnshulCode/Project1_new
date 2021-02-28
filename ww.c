#include <fcntl.h> 
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "strbuf.h"
char buff[1];
void word_wrap(char* filename, int limit){

    char* fname = filename;
    int lim = limit;
    int fd = open(fname,O_RDONLY);
    int bytes_read = read(fd,buff,256);
    printf("%d", bytes_read);
    putchar('\n');
    printf("%s",buff);
    int i = 0;
    int count_tot = 0;
    int count_word = 0;
    putchar('\n');
    printf("strlen : %d",strlen(buff) );
    putchar('\n');
   
    strbuf_t* word = (strbuf_t*)malloc(sizeof(strbuf_t));
    sb_init(word,1);
   // prints word wrapping needs work but base case works
   while(buff[i]!= '\0' && i<strlen(buff)-1){
         while(buff[i] != ' '){
             sb_append(word,buff[i]);
             count_word++;
             i++;
         }
         if(count_word+count_tot <=lim){
             print_string(word);
             putchar(' ');
             word = (strbuf_t*)malloc(sizeof(strbuf_t));
             sb_init(word,1);
             i++;
             count_tot = count_tot+count_word+1;
             count_word = 0;
         }else{
             putchar('\n');
             print_string(word);
             putchar(' ');
             word = (strbuf_t*)malloc(sizeof(strbuf_t));
             sb_init(word,1);
             i++;
             count_tot = count_word;
             count_word = 0;
         }
    
   }
    close(fd);
}

int main(){

    word_wrap("text.txt",10);    
    return 0;
}



