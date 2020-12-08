#pragma once
#include"DATA_TYPE.h"
class CONTAINER{
    class DATA_TYPE<int>* Int = 0;
    int NumIntData = 0;
    class DATA_TYPE<float>* Float = 0;
    int NumFloatData = 0;
    class DATA_TYPE<std::string>* String=0;
    int NumStringData = 0;
public:
    ~CONTAINER();
    //ファイルからデータを読み込む
    int loadData(const char* filename);
    //float取得
    float floatData(const char* name);
    //int取得
    int intData(const char* name);
    //string取得
    std::string stringData(const char* name, int idx = -1);
};

