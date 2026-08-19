#include "Save.h"
#include <string.h>

int SaveToFile(const uint64_t* data, const uint64_t offset, const char* dest)
{
    if (data == NULL || offset == NULL) return -1;

    FILE* savefile = fopen(dest, "r+b");
    if (savefile == NULL)
    {
        savefile = fopen(dest, "wb");
        if (savefile == NULL) return -1;
    }

    if (fseek(savefile, offset, SEEK_SET) != 0)
    {
        fclose(savefile);
        return -1;
    }

    size_t size = sizeof(uint64_t);
    size_t written = fwrite(data, 1, size, savefile);

    fclose(savefile);

    return (written == size) ? 0 : -1;
}

uint64_t LoadFromFile(const uint64_t offset, const char* src)
{
    FILE* savefile = fopen(src, "rb");
    if (savefile == NULL) return UINT64_MAX;

    if (fseek(savefile, offset, SEEK_SET) != 0)
    {
        fclose(savefile);
        return UINT64_MAX;
    }

    uint64_t returnd = 0;
    size_t read = fread(&returnd, sizeof(returnd), 1, savefile);

    fclose(savefile);

    if (read != 1) return UINT64_MAX;

    return returnd;
}
