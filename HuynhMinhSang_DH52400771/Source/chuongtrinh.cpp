#include "thuvien.h"

int main() {
    cin >> R >> C;

    // Nhập bản đồ kho
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> bandokho[i][j];
        }
    }
    int Q; cin >> Q;
    while(Q--){
        int k; cin >> k;
        if(k < 2 || k > 8){
            cout << "INVALID" << endl;
            continue;
        }
        int danhsachR[8];
        int danhsachC[8];
        for(int i = 0; i < k; i++){
            cin >> danhsachR[i] >> danhsachC[i];
        }
        bool hople = true;
        for(int i = 0; i < k; i++){
            if(!kiemtratoado(danhsachR[i], danhsachC[i])){
                hople = false;
                break;
            }
        }
        if(!hople){
            cout << "INVALID" << endl;
            continue;
        }
        int ketqua = timduongnhonhat(k, danhsachR, danhsachC);
        cout << ketqua << endl;

    }

    return 0;
}
