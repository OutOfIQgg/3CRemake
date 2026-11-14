#include "Save.h"
#include <stdio.h>
#include <string.h>

int SaveToFile(const uint64_t* data, const int offset, const char* dest)
{
    if (data == NULL || dest == NULL || offset < 0) return -1;

    FILE* savefile = fopen(dest, "r+b");
    if (savefile == NULL)
    {
        savefile = fopen(dest, "w+b");
        if (savefile == NULL) { fprintf(stderr, "Couldn't open file nor create file. Please make sure you have enough space on your disk.\nIf the issue persists, please reach out to one of our maintainer"); return -1;  }
    }

    if (fseek(savefile, offset, SEEK_SET) != 0)
    {
        fclose(savefile);
        fprintf(stderr, "Couldn't use fseek to save certain sections of the save file.\nIf the issue persists, please reach out to one of our maintainer");
        return -1;
    }

    size_t size = sizeof(uint64_t);
    size_t written = fwrite(data, size, 1, savefile);

    fclose(savefile);

    return (written == 1) ? 0 : -1;
}

uint64_t LoadFromFile(const int offset, const char* src)
{
    FILE* savefile = fopen(src, "r+b");
    if (savefile == NULL)
    {
        savefile = fopen(src, "wb");
        if (savefile != NULL) {
            uint64_t tempval = 5;
            fwrite(&tempval, sizeof(uint64_t), 1, savefile);
            fclose(savefile);
            fprintf(stderr, "Couldn't open file. Created a new one.\nIf the issue persists, please reach out to one of our maintainer");
            return tempval + 1;
        }
        return -1;
    }

    if (fseek(savefile, offset, SEEK_SET) != 0)
    {
        fclose(savefile);
        fprintf(stderr, "Couldn't use fseek to load certain sections of the save file.\nIf the issue persists, please reach out to one of our maintainer");
        return 2;
    }

    uint64_t returnd = 0;
    size_t read = fread(&returnd, sizeof(returnd), 1, savefile);

    fclose(savefile);

    if (read != 1) return 0;

    return returnd;
}
