#include<cassert>
#include<stdio.h>
#include<stdlib.h>
#include"CONTAINER.h"
int CONTAINER::loadData(const char* filename) {
    FILE* fp = 0;
    fopen_s(&fp, filename, "r");
    assert(fp != 0);
    //各データ数、およびデータ行数を数える
    NumIntData = 0;
    NumFloatData = 0;
    NumStringData = 0;
    const unsigned sizeofData = 1024;
    char data[sizeofData];
    int numLines = 0;
    while (fgets(data, sizeofData, fp) != NULL) {
        if (strncmp(data, "float", 5) == 0) {
            NumFloatData++;
        }
        if (strncmp(data, "int", 3) == 0) {
            NumIntData++;
        }
        if (strncmp(data, "string", 6) == 0) {
            NumStringData++;
        }
        numLines++;
    }
    assert(numLines == (NumFloatData + NumIntData + NumStringData));
    //Dataを確保
    Int = new DATA_TYPE<int>[NumIntData];
    Float = new DATA_TYPE<float>[NumFloatData];
    String = new DATA_TYPE<std::string>[NumStringData];
    int intDataIdx = 0;
    int floatDataIdx = 0;
    int stringDataIdx = 0;
    //読み込む
    rewind(fp);
    const unsigned sizeofType = 32;
    char type[sizeofType];
    const unsigned sizeofName = 128;
    char name[128];
    for (int i = 0; i < numLines; i++) {
        fscanf_s(fp, "%s ", type, sizeofType);
        fscanf_s(fp, "%s ", name, sizeofName);
        if (strcmp(type, "float") == 0) {
            float data;
            fscanf_s(fp, "%f", &data);
            Float[floatDataIdx].set(name, data);
            floatDataIdx++;
        }
        else if (strcmp(type, "int") == 0) {
            int data;
            fscanf_s(fp, "%d", &data);
            Int[intDataIdx].set(name, data);
            intDataIdx++;
        }
        else if (strcmp(type, "string") == 0) {
            fscanf_s(fp, "%s", data, sizeofData);
            String[stringDataIdx].set(name, data);
            stringDataIdx++;
        }
        else {
            assert(0);
        }
    }
    fclose(fp);
    return 0;
}
CONTAINER::~CONTAINER() {
    if (Int) { delete[] Int; Int = 0; }
    if (Float) { delete[] Float; Float = 0; }
    if (String) { delete[] String; String = 0; }
}
float CONTAINER::floatData(const char* name) {
    int i;
    for (i = 0; i < NumFloatData; i++) {
        if (Float[i].name() == name) {
            return Float[i].data();
        }
    }
    assert(i < NumFloatData);
    return 0;
}
int CONTAINER::intData(const char* name) {
    int i;
    for (i = 0; i < NumIntData; i++) {
        if (Int[i].name() == name) {
            return Int[i].data();
        }
    }
    assert(i < NumIntData);
    return 0;
}
std::string CONTAINER::stringData(const char* name, int idx) {
    int i;
    if (idx == -1) {
        for (i = 0; i < NumStringData; i++) {
            if (String[i].name() == name) {
                return String[i].data();
            }
        }
    }
    else {
        char editName[128];
        sprintf_s(editName, "%s%d", name, idx);
        for (i = 0; i < NumStringData; i++) {
            if (String[i].name() == editName) {
                return String[i].data();
            }
        }
    }
    assert(i < NumStringData);
    return 0;
}

