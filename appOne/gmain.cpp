#include"APPLI_DATA.h"
#include"SAVE_DATA.h"
#include"dataFileIO.h"
#include"libOne.h"

void gmain() {
#ifdef _DEBUG
    //デバッグモードの時テキストファイルからバイナリファイルをつくる
    //外部プログラムの実行
    system("TextToBin");
#endif
    window(700, 700);
    //appli_data.binを読み込む
    APPLI_DATA d;
    loadData("assets/appli_data.bin", "rb", &d);
    //save_data.binを読み込む
    SAVE_DATA sd;
    loadData("assets/save_data.bin", "rb", &sd);
    //画像を読み込む
    int img = loadImage(d.imgFilename);
    while (notQuit) {
        //角数の変更
        if (isTrigger(KEY_D))sd.num++;
        else if (isTrigger(KEY_A) && sd.num > 3)sd.num--;
        //描画
        clear(d.clearR, d.clearG, d.clearB);
        mathAxis(d.axisMaxX);
        //画像を描く
        rectMode(CENTER);
        mathImage(img, 0, 0);
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
    saveData("assets/save_data.bin", "wb", &sd);
}