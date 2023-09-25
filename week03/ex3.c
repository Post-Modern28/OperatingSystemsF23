#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


#define MAX_FILES 100
#define MAX_DIRS 100


typedef struct File {
    unsigned int id;
    char name[50];
    size_t size;
    char* data;
    struct Directory* directory;
} File;


typedef struct Directory {
    char name[50];
    File* files[MAX_FILES];
    struct Directory* directories[MAX_DIRS];
    unsigned char nf;
    unsigned char nd;
    char path[100];
} Directory;


void overwrite_to_file(File* file, const char* str) {
    if(file->data != NULL) {
        free(file->data);
    }
    file->size = strlen(str);
    file->data = (char*) malloc(file->size * sizeof(char));
    strcpy(file->data, str);
}


void append_to_file(File* file, const char* str) {
    size_t old_size = file->size;
    size_t new_size = old_size + strlen(str);

    char* new_data = (char*) malloc(new_size * sizeof(char));
    //file->data = (char*) realloc(file->data, new_size * sizeof(char));
    //printf("old: %s\n", file->data);
    //strcat(file->data, str);
    sprintf(new_data, "%s%s", file->data, str);
    free(file->data);

    file->data = new_data;
    file->size = new_size;
}


void print_file(File* file) {
    printf("%s%s\nFile Contents: %s\nFile id: %d\n", file->directory->path, file->name, file->data, file->id);
}


void print_files(Directory* dir){
    for (int i = 0; i < dir->nf; i++){
        print_file(dir->files[i]);
    }
    for (int i = 0; i < dir->nd; i++){
        print_files(dir->directories[i]);
    }
}


void add_file(File* file, Directory* dir) {
    dir->files[dir->nf++] = file;
    file->directory = dir;
}


void add_directory(Directory* new_dir, Directory* dir) {
    dir->directories[dir->nd++] = new_dir;
    sprintf(new_dir->path, "%s%s/", dir->path, new_dir->name);
}


File* FileConstructor(char* name){
    static unsigned int id;
    File* f = (File*) malloc(sizeof(File));
    strcpy(f->name, name);
    f->id = id++;
    f->size = 0;
    f->directory = NULL;
    f->data = NULL;
    return f;
}


Directory* DirectoryConstructor(char* name){
    Directory* dir = (Directory*) malloc(sizeof (Directory));
    strcpy(dir->name, name);
    dir->nd = 0;
    dir->nf = 0;
    return dir;
}


int main() {
    
    Directory* root = DirectoryConstructor("/");
    strcpy(root->path, "/");
    Directory* home = DirectoryConstructor("home");
    add_directory(home, root);
    printf("%s\n", home->path);

    Directory* bin = DirectoryConstructor("bin");
    add_directory(bin, root);
    File* bash = FileConstructor("bash");
    overwrite_to_file(bash, "Bourne Again Shell!!");
    add_file(bash, bin);
    printf("%s\n", bin->path);

    File* ex3_1 = FileConstructor("ex3_1.c");
    overwrite_to_file(ex3_1, "int printf(const char * format, ...);");
    add_file(ex3_1, home);

    File* ex3_2 = FileConstructor("ex3_2.c");
    overwrite_to_file(ex3_2, "//This is a comment in C language");
    add_file(ex3_2, home);

    printf("old: %s\n", ex3_1->data);
    append_to_file(ex3_1, "int main(){printf('<<Hello World!>>)}");
    printf("new: %s\n", ex3_1->data);
    print_files(root);
    free(root);
    free(home);
    free(bin);
    free(ex3_1);
    free(ex3_2);
    free(bash);
    return 0;
}