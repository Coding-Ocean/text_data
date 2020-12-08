#pragma once
#include<stdio.h>

template<typename T>
void saveData(const char* filename, const char* mode, T* d) {
    FILE* fp;
    fopen_s(&fp, filename, mode);
    fwrite(d, sizeof(T), 1, fp);
    fclose(fp);
}

template<typename T>
void loadData(const char* filename, const char* mode, T* d) {
    FILE* fp;
    fopen_s(&fp, filename, mode);
    if (fp) {
        fread(d, sizeof(T), 1, fp);
        fclose(fp);
    }
}
