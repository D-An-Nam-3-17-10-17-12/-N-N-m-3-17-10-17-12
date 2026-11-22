#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;

// Gioi han toi da so luong lenh va kich thuoc HashMap
const int TOI_DA_LENH = 100005;
const int KICH_THUOC_BANG_BAM = 200003; // So nguyen to du lon de giam dung do

// Mot lo hang trong hang doi FIFO cua mot SKU
struct LoHang {
    char maLo[25];
    long long soLuongCon;
    LoHang* tiepTheo;
};

// Hang doi FIFO cac lo hang cho tung ma SKU
struct HangDoiLo {
    LoHang* dau;
    LoHang* cuoi;
    long long tongTon;
};

// Thong tin mot mat hang (SKU) trong HashMap
struct MucSKU {
    char maSKU[25];
    HangDoiLo hangDoi;
    MucSKU* tiepTheo;
};

// Bang bam luu tat ca ma lo da su dung trong toan kho (kiem tra DUPLICATE_LOT)
struct NutMaLo {
    char maLo[25];
    NutMaLo* tiepTheo;
};

MucSKU* bangSKU[KICH_THUOC_BANG_BAM];
NutMaLo* bangMaLo[KICH_THUOC_BANG_BAM];

// Sao chep chuoi an toan voi gioi han kich thuoc mang dich
void saoChepChuoi(char* dich, const char* nguon, int kichThuocDich) {
    if (dich == nullptr || kichThuocDich <= 0) return;
    int i = 0;
    if (nguon != nullptr) {
        while (i < kichThuocDich - 1 && nguon[i] != '\0') {
            dich[i] = nguon[i];
            i++;
        }
    }
    dich[i] = '\0';
}
// Ham bam djb2 cho chuoi ky tu
unsigned int bamChuoi(const char* s) {
    unsigned int hash = 5381;
    int c;
    while ((c = (unsigned char)*s++) != 0) {
        hash = ((hash << 5) + hash) + (unsigned int)c;
    }
    return hash % KICH_THUOC_BANG_BAM;
}

// Kiem tra chuoi chi gom chu so 0-9 (khong am, khong dau +/-, khong chu)
bool laSoNguyenHopLe(const char* s) {
    if (s == nullptr || s[0] == '\0') return false;
    int len = (int)strlen(s);
    if (len > 10) return false; // Gioi han < 2.147.483.647
    for (int i = 0; i < len; i++) {
        if (s[i] < '0' || s[i] > '9') return false;
    }
    long long giaTri = atoll(s);
    if (giaTri <= 0 || giaTri > 1000000000LL) return false;
    return true;
}

// Kiem tra ma SKU hoac ma lo hop le (1..20 ky tu, khong khoang trang)
bool laMaHopLe(const char* s) {
    if (s == nullptr) return false;
    int len = (int)strlen(s);
    return (len >= 1 && len <= 20);
}

// Kiem tra ma lo da ton tai trong toan kho chua
bool daTonTaiMaLo(const char* maLo) {
    unsigned int idx = bamChuoi(maLo);
    NutMaLo* cur = bangMaLo[idx];
    while (cur != nullptr) {
        if (strcmp(cur->maLo, maLo) == 0) return true;
        cur = cur->tiepTheo;
    }
    return false;
}

// Ghi nhan ma lo moi vao bang bam toan kho
void themMaLoDaDung(const char* maLo) {
    unsigned int idx = bamChuoi(maLo);
    NutMaLo* nutMoi = new NutMaLo;
    saoChepChuoi(nutMoi->maLo, maLo, sizeof(nutMoi->maLo));
    nutMoi->tiepTheo = bangMaLo[idx];
    bangMaLo[idx] = nutMoi;
}

// Tim hoac tao moi muc SKU trong HashMap
MucSKU* layHoacTaoSKU(const char* maSKU, bool taoMoi) {
    unsigned int idx = bamChuoi(maSKU);
    MucSKU* cur = bangSKU[idx];
    while (cur != nullptr) {
        if (strcmp(cur->maSKU, maSKU) == 0) return cur;
        cur = cur->tiepTheo;
    }
    if (!taoMoi) return nullptr;

    MucSKU* skuMoi = new MucSKU;
    saoChepChuoi(skuMoi->maSKU, maSKU, sizeof(skuMoi->maSKU));
    skuMoi->hangDoi.dau = nullptr;
    skuMoi->hangDoi.cuoi = nullptr;
    skuMoi->hangDoi.tongTon = 0;
    skuMoi->tiepTheo = bangSKU[idx];
    bangSKU[idx] = skuMoi;
    return skuMoi;
}

// Nhap lo hang vao cuoi hang doi FIFO cua SKU
void nhapLoHang(MucSKU* sku, const char* maLo, long long soLuong) {
    LoHang* loMoi = new LoHang;
    saoChepChuoi(loMoi->maLo, maLo, sizeof(loMoi->maLo));
    loMoi->soLuongCon = soLuong;
    loMoi->tiepTheo = nullptr;

    if (sku->hangDoi.cuoi == nullptr) {
        sku->hangDoi.dau = loMoi;
        sku->hangDoi.cuoi = loMoi;
    }
    else {
        sku->hangDoi.cuoi->tiepTheo = loMoi;
        sku->hangDoi.cuoi = loMoi;
    }
    sku->hangDoi.tongTon += soLuong;
}

// Tach cac token cach nhau boi khoang trang tren mot dong
int tachToken(char* dong, char token[][128], int toiDaToken) {
    int dem = 0;
    int i = 0;
    int n = (int)strlen(dong);

    while (i < n && dem < toiDaToken) {
        while (i < n && (dong[i] == ' ' || dong[i] == '\t' || dong[i] == '\r' || dong[i] == '\n')) {
            i++;
        }
        if (i >= n) break;

        int k = 0;
        while (i < n && dong[i] != ' ' && dong[i] != '\t' && dong[i] != '\r' && dong[i] != '\n') {
            if (k < 127) {
                token[dem][k++] = dong[i];
            }
            i++;
        }
        token[dem][k] = '\0';
        dem++;
    }
    return dem;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < KICH_THUOC_BANG_BAM; i++) {
        bangSKU[i] = nullptr;
        bangMaLo[i] = nullptr;
    }

    char dong[512];
    // Doc dong dau tien chua Q
    if (!cin.getline(dong, sizeof(dong))) {
        return 0;
    }

    char tokenDau[4][128];
    int soTokenDau = tachToken(dong, tokenDau, 4);
    if (soTokenDau != 1 || !laSoNguyenHopLe(tokenDau[0])) {
        cout << "INVALID\n";
        return 0;
    }

    long long qLL = atoll(tokenDau[0]);
    if (qLL < 1 || qLL > TOI_DA_LENH) {
        cout << "INVALID\n";
        return 0;
    }
    int Q = (int)qLL;

    char cacToken[10][128];
    for (int i = 0; i < Q; i++) {
        if (!cin.getline(dong, sizeof(dong))) {
            break;
        }

        int soToken = tachToken(dong, cacToken, 10);
        if (soToken <= 0) {
            cout << "INVALID\n";
            continue;
        }

        const char* lenh = cacToken[0];

        if (strcmp(lenh, "IMPORT") == 0) {
            // IMPORT sku lot qty -> dung 4 token
            if (soToken != 4 || !laMaHopLe(cacToken[1]) || !laMaHopLe(cacToken[2]) || !laSoNguyenHopLe(cacToken[3])) {
                cout << "INVALID\n";
                continue;
            }
            if (daTonTaiMaLo(cacToken[2])) {
                cout << "DUPLICATE_LOT\n";
                continue;
            }
            long long soLuong = atoll(cacToken[3]);
            MucSKU* sku = layHoacTaoSKU(cacToken[1], true);
            nhapLoHang(sku, cacToken[2], soLuong);
            themMaLoDaDung(cacToken[2]);
            cout << "OK\n";

        }
        else if (strcmp(lenh, "EXPORT") == 0) {
            // EXPORT sku qty -> dung 3 token
            if (soToken != 3 || !laMaHopLe(cacToken[1]) || !laSoNguyenHopLe(cacToken[2])) {
                cout << "INVALID\n";
                continue;
            }
            long long canXuat = atoll(cacToken[2]);
            MucSKU* sku = layHoacTaoSKU(cacToken[1], false);
            long long tonHienTai = (sku != nullptr) ? sku->hangDoi.tongTon : 0;

            if (tonHienTai < canXuat) {
                cout << "NOT_ENOUGH " << tonHienTai << "\n";
                continue;
            }

            // Du hang -> xuat theo thu tu FIFO tu dau hang doi
            long long conCan = canXuat;
            bool daInPhanTuDau = false;
            while (conCan > 0 && sku->hangDoi.dau != nullptr) {
                LoHang* loDau = sku->hangDoi.dau;
                long long layTuLo = (loDau->soLuongCon <= conCan) ? loDau->soLuongCon : conCan;

                if (daInPhanTuDau) {
                    cout << " ";
                }
                cout << loDau->maLo << ":" << layTuLo;
                daInPhanTuDau = true;

                loDau->soLuongCon -= layTuLo;
                sku->hangDoi.tongTon -= layTuLo;
                conCan -= layTuLo;

                if (loDau->soLuongCon == 0) {
                    sku->hangDoi.dau = loDau->tiepTheo;
                    if (sku->hangDoi.dau == nullptr) {
                        sku->hangDoi.cuoi = nullptr;
                    }
                    delete loDau;
                }
            }
            cout << "\n";

        }
        else if (strcmp(lenh, "STOCK") == 0) {
            // STOCK sku -> dung 2 token
            if (soToken != 2 || !laMaHopLe(cacToken[1])) {
                cout << "INVALID\n";
                continue;
            }
            MucSKU* sku = layHoacTaoSKU(cacToken[1], false);
            if (sku == nullptr) {
                cout << "0\n";
            }
            else {
                cout << sku->hangDoi.tongTon << "\n";
            }

        }
        else {
            cout << "INVALID\n";
        }
    }

    return 0;
}