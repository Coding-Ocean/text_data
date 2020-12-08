#include"APPLI_DATA.h"
#include"SAVE_DATA.h"
#include"dataFileIO.h"
#include"libOne.h"

void gmain() {
#ifdef _DEBUG
    //�f�o�b�O���[�h�̎��e�L�X�g�t�@�C������o�C�i���t�@�C��������
    //�O���v���O�����̎��s
    system("TextToBin");
#endif
    window(700, 700);
    //appli_data.bin��ǂݍ���
    APPLI_DATA d;
    loadData("assets/appli_data.bin", "rb", &d);
    //save_data.bin��ǂݍ���
    SAVE_DATA sd;
    loadData("assets/save_data.bin", "rb", &sd);
    //�摜��ǂݍ���
    int img = loadImage(d.imgFilename);
    while (notQuit) {
        //�p���̕ύX
        if (isTrigger(KEY_D))sd.num++;
        else if (isTrigger(KEY_A) && sd.num > 3)sd.num--;
        //�`��
        clear(d.clearR, d.clearG, d.clearB);
        mathAxis(d.axisMaxX);
        //�摜��`��
        rectMode(CENTER);
        mathImage(img, 0, 0);
        //���p�`����ŕ`��
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
        //�e�L�X�g
        textSize(d.texSize);
        fill(d.tex1R, d.tex1G, d.tex1B);
        text(d.tex1 + (let)sd.num, 0, d.texSize);
        fill(d.texR, d.texG, d.texB);
        text(d.tex2, 0, d.texSize*2);
        text(d.tex3, 0, d.texSize*3);
    }
    saveData("assets/save_data.bin", "wb", &sd);
}