#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char *bin, int left, int right) {
    while (left < right) {
        char temp = bin[left];
        bin[left] = bin[right];
        bin[right] = temp;
        left++;
        right--;
    }
}

char* int_into_bin(int ip_field){
    int i = 0;
    char *ip_bin = malloc(sizeof(char) * 32);
    while(ip_field > 0){
        int bit = ip_field % 2;
        ip_bin[i++] = '0' + bit;
        ip_field /= 2;
    }
    ip_bin[i] = '\0';
    reverse(ip_bin, 0, i - 1);
    return ip_bin;
}

int main(int argc,char *argv[]){
    if(argc < 2) 
        return 1;

    char *token = strtok(argv[1], " . ");
    int Ipv4[4];

    int i = 0;
    while (token != NULL || i < 4) {
        sscanf(token,"%d", &Ipv4[i]);
        token = strtok(NULL, " . ");
        i++;
    }
    char *ip_bin[4];
    *ip_bin = int_into_bin(Ipv4[0]);
    printf("%s", ip_bin[0]);

    return 0;
}
