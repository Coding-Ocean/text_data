#include"../appOne/APPLI_DATA.h"
#include"../appOne/dataFileIO.h"
#include"CONTAINER.h"
//テキストデータを読み込んで、appli_data.binを吐き出す
void strcopy(char* a, size_t size, std::string b) {
    strcpy_s(a, size, b.c_str());
}
int main() {
    class CONTAINER c;
    c.loadData("appli_data.txt");
    struct APPLI_DATA d;
    d.clearR = c.floatData("clearR");
    d.clearG = c.floatData("clearG");
    d.clearB = c.floatData("clearB");
    d.axisMaxX = c.floatData("axisMaxX");
    d.strokeW = c.floatData("strokeW");
    d.strokeR = c.floatData("strokeR");
    d.strokeG = c.floatData("strokeG");
    d.strokeB = c.floatData("strokeB");
    d.strokeA = c.floatData("strokeA");
    d.texSize = c.floatData("texSize");
    d.tex1R = c.floatData("tex1R");
    d.tex1G = c.floatData("tex1G");
    d.tex1B = c.floatData("tex1B");
    d.texR = c.floatData("texR");
    d.texG = c.floatData("texG");
    d.texB = c.floatData("texB");
    strcopy(d.tex1, sizeof(d.tex1), c.stringData("tex1"));
    strcopy(d.tex2, sizeof(d.tex2), c.stringData("tex2"));
    strcopy(d.tex3, sizeof(d.tex3), c.stringData("tex3"));
    strcopy(d.imgFilename, sizeof(d.imgFilename), c.stringData("imgFilename"));
    saveData("assets/appli_data.bin", "wb", &d);
    return 0;
}
