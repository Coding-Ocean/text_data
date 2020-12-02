#include"CONTAINER.h"
#include"libOne.h"
//セーブデータ-------------------------------------------------------
struct SAVE_DATA {
    //最初に立ち上げた時（まだセーブデータがない時）の値を入れておく
    int num = 3;//角数
};
void loadData(struct SAVE_DATA* d) {
    FILE* fp;
    fopen_s(&fp, "save_data.bin", "rb");
    if (fp) {
        fread(d, sizeof(SAVE_DATA), 1, fp);
        fclose(fp);
    }
}
void saveData(struct SAVE_DATA* d) {
    FILE* fp;
    fopen_s(&fp, "save_data.bin", "wb");
    fwrite(d, sizeof(SAVE_DATA), 1, fp);
    fclose(fp);
}
//アプリケーション用データ-------------------------------------------
struct APPLI_DATA {
    float clearR;
    float clearG;
    float clearB;
    float axisMaxX;
    float strokeW;
    float strokeR;
    float strokeG;
    float strokeB;
    float strokeA;
    float texSize;
    float tex1R;
    float tex1G;
    float tex1B;
    float texR;
    float texG;
    float texB;
    char tex1[8];
    char tex2[32];
    char tex3[32];
};
void loadData(struct APPLI_DATA* d) {
    FILE* fp=0;
    fopen_s(&fp, "appli_data.bin", "rb");
    fread(d, sizeof(APPLI_DATA), 1, fp);
    fclose(fp);
}
void saveData(struct APPLI_DATA* d) {
    FILE* fp;
    fopen_s(&fp, "appli_data.bin", "wb");
    fwrite(d, sizeof(APPLI_DATA), 1, fp);
    fclose(fp);
}
//テキストデータを読み込んで、appli_data.binを吐き出す
void createData(){
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
    strcpy_s(d.tex1, sizeof(d.tex1), c.stringData("tex1").c_str());
    strcpy_s(d.tex2, sizeof(d.tex2), c.stringData("tex2").c_str());
    strcpy_s(d.tex3, sizeof(d.tex3), c.stringData("tex3").c_str());
    saveData(&d);
}
//メイン----------------------------------------------------------------
void gmain() {
    window(700, 700);
#if _DEBUG
    //Debugモードの時だけ
    //appli_data.txtを読み込んでappli_data.binを吐き出す
    createData();
#endif
    //appli_data.binを読み込む
    APPLI_DATA d;
    loadData(&d);
    //save_data.binを読み込む
    SAVE_DATA sd;
    loadData(&sd);
    while (notQuit) {
        //角数の変更
        if (isTrigger(KEY_D))sd.num++;
        else if (isTrigger(KEY_A) && sd.num > 3)sd.num--;
        //描画
        clear(d.clearR, d.clearG, d.clearB);
        mathAxis(d.axisMaxX);
        //多角形を線で描く
        stroke(d.strokeR, d.strokeG, d.strokeB, d.strokeA);
        strokeWeight(d.strokeW);
        angleMode(DEGREES);
        float deg = 360.0f / sd.num;
        float sx = sin(0.0f);
        float sy = cos(0.0f);
        for (int i = 0; i < sd.num; i++) {
            float ex = sin(deg * (i + 1));
            float ey = cos(deg * (i + 1));
            mathLine(sx, sy, ex, ey);
            sx = ex;
            sy = ey;
        }
        //テキスト
        textSize(d.texSize);
        fill(d.tex1R, d.tex1G, d.tex1B);
        text(d.tex1 + (let)sd.num, 0, d.texSize);
        fill(d.texR, d.texG, d.texB);
        text(d.tex2, 0, d.texSize*2);
        text(d.tex3, 0, d.texSize*3);
    }
    saveData(&sd);
}