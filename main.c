#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void show_help();

int main(int argc, char** argv) {
    if(argc == 1) {
        show_help();
        return 0;
    }
    char* filename = argv[1];
    if(strlen(filename) > FILENAME_MAX) {
        puts("ERROR: Supplied filename is larger than filename maximum");
        return 1;
    }
    FILE* file = fopen(filename, "rb");
    if(file == NULL) {
        puts("Failed to open file");
        return 1;
    }
    fseek(file, 0l, SEEK_END);
    long filesize = ftell(file);
    rewind(file);
    char* filebuf = malloc(filesize);
    for(int i = 0; i < filesize; i++) {
        filebuf[i] = getc(file);
    }
    if(filebuf[2] & 0b00110000 == 0b00110000) {
        puts("MPEG version 1");
    } else if(filebuf[2] & 0b00010000 == 0b00010000) {
        puts("MPEG version 2");
    }
    fclose(file);
    return 0;
}

void show_help() {
    char* help_text = 
    "mp3info version 0.0.1\n"\
    "usage: mp3info <filename.mp3>";
    puts(help_text);
}
