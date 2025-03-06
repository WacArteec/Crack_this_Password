#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
    FILE *bin_file = fopen("PASART.COM", "r+b");
    if (!bin_file) 
    {
        perror("Ошибка открытия файла");
        return 1;
    }
    
    int fseek_proof = fseek(bin_file, 0, SEEK_END);
    assert(fseek_proof + 1);

    unsigned int count_symb_in_file = ftell(bin_file);

    printf("\t%u\n", count_symb_in_file);

    char* bin_code = (char*) calloc(count_symb_in_file, sizeof(char));

    rewind(bin_file);
    fread(bin_code, sizeof(char), count_symb_in_file, bin_file);

    unsigned int shift = 0;
    while (bin_code[shift] != 0x75)
        shift++;

    printf("\t%u %c\n", shift, bin_code[shift]);
    bin_code[shift] = 0x74;
    printf("\t%u %c\n", shift, bin_code[shift]);

    rewind(bin_file);
    size_t count = fwrite(bin_code, sizeof(char), count_symb_in_file, bin_file);

    if (count != count_symb_in_file)
        printf("\t\t\t%u", count);

    fclose(bin_file);

    return 0;
}