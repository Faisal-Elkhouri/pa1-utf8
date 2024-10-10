#include <stdio.h>
#include <string.h>
#include <stdint.h>

void inspect(char s[]) {
    int index = 0;
    printf("%s, length %ld: ", s, strlen(s));
    while(s[index] != 0) {
        char current = s[index];
        printf("%c (%hhu 0b", current, current);
        for(int place = 128; place > 0; place /= 2) {
            if((current & place) == 0) printf("0");
            else printf("1");
        }
        printf(") ");
        index += 1;
    }
    printf("\n");
}

//milestone 1
int32_t is_ascii(char str[]){
    inspect(str);
    for (int i = 0; str[i] != 0; i++){
        if ((0b10000000 & str[i]) == 0b10000000) return -1;
    }
    return 1;
}

int32_t capitalize_ascii(char str[]){
    for (int i = 0; str[i] != 0; i++){
        if ((str[i] & 0b11000000) == 0b01000000 && str[i] < 123 && str[i] > 96) str[i] = str[i] & 0b11011111;
    }
}

//milestone 2
int32_t width_from_start_byte(char start_byte){
    if((start_byte & 0b10000000) == 0) return 1;
    else if ((start_byte & 0b11110000) == 0b11110000) return 4;
    else if ((start_byte & 0b11100000) == 0b11100000) return 3;
    else if ((start_byte & 0b11000000) == 0b11000000) return 2;
    else if ((start_byte & 0b10000000) == 0b10000000) return -1;
    else return -100; //catastrophic error (shouldn't even be possible)
}

int32_t utf8_strlen(char str[]){
    int counter = 0;
    for (int i = 0;str[i] != 0;i++){
        if((str[i] & 0b11000000) != 0b10000000) {
            counter++;
        }
    }
    return counter;
}

int32_t codepoint_index_to_byte_index(char str[], int32_t cpi){
    int cp_counter = 0;
    int byte_counter = 0;
    int last_utf8_flag = 0;
    while (cp_counter <= cpi && str[byte_counter] != 0){
        if((str[byte_counter] & 0b11000000) != 0b10000000) {
            printf("if was true: %d\n", str[byte_counter]);
            last_utf8_flag = width_from_start_byte(str[byte_counter]);
            cp_counter++;
        }
        else{
                        printf("if was false: %d\n", str[byte_counter]);

        }
        byte_counter++;
    }
    byte_counter--;
    if (cp_counter < cpi) return -1; //an error has occured e.g. the string is not long enough
    return byte_counter;
}

void utf8_substring(char str[], int32_t cpi_start, int32_t cpi_end, char result[]){
    
}


int main(){
    char inp[100];
    int index = 0;
    scanf("%s",inp);
    scanf("%d", &index);
    inspect(inp);
    printf("%d\n", codepoint_index_to_byte_index(inp,index));
    return 0;
}