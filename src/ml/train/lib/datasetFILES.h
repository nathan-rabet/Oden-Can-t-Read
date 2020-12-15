#include <stdlib.h>

struct File
{
    size_t file_index;
    char *path;
    char *data;
};

struct Folder
{
    char char_id;
    size_t nb_files;
    char *path;
    struct File *fileLIST;
};

struct Folders
{
    size_t nb_folder;
    char *path;
    struct Folder *folderLIST;
};