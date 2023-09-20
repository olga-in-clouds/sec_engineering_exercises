#include<stdio.h> 
#include<unistd.h>    
#include<stdlib.h>
#include<string.h>  
int target; 
void vuln(char *str){ 
    printf(str); 
    printf("\n");
    if (target){ 
        printf("You have updated the target\n"); 
    } 
} 
int main(int argc, char **argv) { 
    vuln(argv[1]); 
}