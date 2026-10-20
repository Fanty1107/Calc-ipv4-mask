#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int count_zeros_mask(int mask[4]) {
    int zeros = 0;
    for (int octeto = 0; octeto < 4; octeto++) {
        for (int bit = 7; bit >= 0; bit--) {
            if (((mask[octeto] >> bit) & 1) == 0) {
                zeros++;
            }
        }
    }
    return zeros;
}
char* int_into_bin(int ip_field){
    if (ip_field > 255) 
        return NULL; 

    char *ip_bin = malloc(9);
    if (ip_bin == NULL) 
        return NULL;

    for (int i = 7; i >= 0; i--) {
        ip_bin[7 - i] = ((ip_field >> i) & 1) ? '1' : '0';
    }
    ip_bin[8] = '\0';
    return ip_bin;
}

int main(int argc,char *argv[]){
    if(argc < 2) 
        return 1;

    //ipv4
    char *token = strtok(argv[1], " . ");
    int Ipv4[4];

    int i = 0;
    while (token != NULL || i < 4) {
        sscanf(token,"%d", &Ipv4[i]);
        token = strtok(NULL, " . ");
        i++;
    }
    char *ip_bin[4];
    printf("Ipv4(bin): ");
    for(int i = 0; i < 4; i++){
        ip_bin[i] = int_into_bin(Ipv4[i]);
        printf("%s ", ip_bin[i]);
    }
    printf("\n");
    //mask
    if(argv[2] == NULL){
        printf("Error");
        return 1;
    }
    char *tkn_m = strtok(argv[2], " . ");
    int net_mask[4];
    int j = 0;
    while(tkn_m != NULL || j < 4){
        sscanf(tkn_m, "%d", &net_mask[j]);
        tkn_m = strtok(NULL, " . ");
        j++;
    }

    char *mask_bin[4];
    printf("Mask(bin): ");
    for(int i = 0; i < 4; i++){
        mask_bin[i] = int_into_bin(net_mask[i]);
        printf("%s ", mask_bin[i]);
    }
    printf("\nIP\\mask: %d.%d.%d.%d\\%d\n",
            Ipv4[0], Ipv4[1], Ipv4[2]
            ,Ipv4[3], 32 - count_zeros_mask(net_mask));

    int rede[4];
    int broadcast[4];

    for (int i = 0; i < 4; i++) {
        rede[i] = Ipv4[i] & net_mask[i];
        broadcast[i] = rede[i] | (255 - net_mask[i]);
    }

    printf("Minor address: %d.%d.%d.%d\n",
       rede[0], rede[1], rede[2], rede[3]);

    printf("Larger address (broadcast): %d.%d.%d.%d\n",
       broadcast[0], broadcast[1], broadcast[2], broadcast[3]);

    return 0;
}
