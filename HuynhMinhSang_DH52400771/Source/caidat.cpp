#include "thuvien.h"
#include <stack>

bool kiemtralaso(string noidung){
    if(noidung.empty()){
        return false;
    }
    for(char kitu : noidung){
        if(!isdigit(kitu)){
            return false;
        }
    }
    return true;
}

bool kiemtratoado(int r, int c){
    if(r < 0 || r >= R || c < 0 || c >= C){
        return false;
    }
    if(bandokho[r][c] == '#'){
        return false;
    }
    return true;
}

void them(int r, int c, int b){
    if(!kiemtratoado(r, c)){
        return;
    }
    if(buoc[r][c] != -1){
        return;
    }
    buoc[r][c] = b; // cập nhật số bước
    // bỏ ô hiện tại vào hàng đợi để khám phá 
    hangdoi.push({r, c});
}

void loang(int r0, int c0){
    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            buoc[i][j] = -1;
        }
    }
    while(!hangdoi.empty()){
        hangdoi.pop();
    }
    buoc[r0][c0] = 0;
    hangdoi.push({r0, c0});
    while(!hangdoi.empty()){
        int r = hangdoi.front().first;
        int c = hangdoi.front().second;
        hangdoi.pop();
        them(r - 1, c, buoc[r][c]+1);
        them(r + 1, c, buoc[r][c]+1);
        them(r, c - 1, buoc[r][c]+1);
        them(r, c + 1, buoc[r][c]+1);
    }
}

void timhoanvi(int k, bool daxet[], int vitri, int khoangcach[][8], int dodai, int &ketqua) {
    int dem = 0;
    for (int i = 0; i < k; i++) {
        if (daxet[i]){
            dem++;            
        } 
    }
    if (dem == k) {
        if (dodai < ketqua) ketqua = dodai;
        return;
    }
    for (int i = 1; i < k; i++) {
        if (!daxet[i]) {
            int kc = khoangcach[vitri][i];
            if (kc != -1) {
                daxet[i] = true;
                timhoanvi(k, daxet, i, khoangcach, dodai + kc, ketqua);
                daxet[i] = false;
            }
        }
    }
}

int timduongnhonhat(int k, int danhsachR[], int danhsachC[]) {
    int khoangcach[8][8];
    for (int i = 0; i < k; i++) {
        loang(danhsachR[i], danhsachC[i]);
        for (int j = 0; j < k; j++) {
            khoangcach[i][j] = buoc[danhsachR[j]][danhsachC[j]];
        }
    }
    bool daxet[8] = {};
    int ketqua = INT_MAX;
    daxet[0] = true;
    timhoanvi(k, daxet, 0, khoangcach, 0, ketqua);
    if (ketqua == INT_MAX){
        return -1;        
    } 
    return ketqua;
}