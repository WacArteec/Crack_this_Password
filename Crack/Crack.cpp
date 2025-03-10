#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <TXLib.h>

void Graphics(char* filename)
{
    int height = 500, widht = 500;
    double x0 = 100, x1 = 400, x2 = 100, y0 = 400, y1 = 450;
    double fl_x0 = 100, fl_x1 = 400, fl_y0 = 0, fl_y1 = 50;
    double delay = 100;

    const char* images[4] = {"HackImages/Smile1.bmp", "HackImages/Smile2.bmp", "HackImages/Smile3.bmp", "HackImages/Smile4.bmp"}; 
    char crack_text[26] = "FILE'S BEING CRACKED:000%";

    txPlaySound("HACKGUITAR.wav");

    txCreateWindow(height, widht, true);
    txSetColor(TX_WHITE);

    txSetFillColor (TX_WHITE);
    txClear();

    for(int i = 0; i < 101; i++)
    {
        HDC image = txLoadImage(images[i / 26], height, widht);
        txBitBlt(txDC(), 0, 0, 0, 0, image);

        txSetFillColor (TX_BLUE);
        txRectangle	(x0, y0, x1, y1);

        txSetFillColor (TX_GREEN);
        txRectangle	(x0, y0, x2, y1);

        crack_text[23] = 48 + (i % 10);
        crack_text[22] = 48 + (i % 100 - i % 10) / 10;

        if(i == 100)
            crack_text[21] = '1';

        txSetTextAlign(TA_CENTER);
        txDrawText(x0, y0, x1, y1, crack_text);

        x2 += (x1 - x0) / 100;
        
        txSetFillColor (TX_BLUE);
        txRectangle	(fl_x0, fl_y0, fl_x1, fl_y1);
        
        txSetTextAlign(TA_CENTER);
        txDrawText(fl_x0, fl_y0, fl_x1, fl_y1, filename);

        txSleep(delay);
    }
    
    txSetFillColor (TX_GREEN);
    txRectangle	(x0, y0, x2, y1);
    
    txSetFillColor (TX_GREEN);
    txRectangle	(fl_x0, fl_y0, fl_x1, fl_y1);
    
    txSetTextAlign(TA_CENTER);
    txDrawText(fl_x0, fl_y0, fl_x1, fl_y1, filename);
    
    txSetTextAlign(TA_CENTER);
    txDrawText(x0, y0 , x1, y1 , "FILE WAS CRACKED");

    txPlaySound(NULL);
}

void NewCOM(char* filename, char old_symb, char new_symb)
{
    FILE *bin_file = fopen(filename, "r+b");
    if (!bin_file) 
        perror("Ошибка открытия файла");
    
    int fseek_proof = fseek(bin_file, 0, SEEK_END);
    assert(fseek_proof + 1);

    unsigned int count_symb_in_file = ftell(bin_file);

    char* bin_code = (char*) calloc(count_symb_in_file, sizeof(char));

    rewind(bin_file);
    fread(bin_code, sizeof(char), count_symb_in_file, bin_file);

    unsigned int shift = 0;
    while (bin_code[shift] != old_symb)
        shift++;

    bin_code[shift] = new_symb;

    rewind(bin_file);
    size_t count = fwrite(bin_code, sizeof(char), count_symb_in_file, bin_file);

    if (count != count_symb_in_file)
        perror("Ошибка открытия файла");

    fclose(bin_file);

}

int main()
{
    char filename[] = "../PASART.COM";

    NewCOM(filename, 0x75, 0x74);

    Graphics(filename);

    return 0;
}