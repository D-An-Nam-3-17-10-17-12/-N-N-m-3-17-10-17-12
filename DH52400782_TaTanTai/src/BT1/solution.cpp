#include <iostream>

using namespace std;

// Cấu trúc lưu tọa độ (hàng, cột) của một ô trong kho
struct ToaDo {
    int hang, cot;
};

// Hàm kiểm tra một chuỗi ký tự có phải là số nguyên hợp lệ hay không
// (chỉ gồm chữ số, không âm, nhỏ hơn 2.147.483.647)
bool kiemTraSoHopLe(const char chuoi[], int& giaTri) {
    if (chuoi[0] == '\0') return false;

    long long tam = 0;
    int doDai = 0;
    while (chuoi[doDai] != '\0') {
        if (chuoi[doDai] < '0' || chuoi[doDai] > '9') return false;
        tam = tam * 10 + (chuoi[doDai] - '0');
        doDai++;
        if (doDai > 10) return false; // Tránh tràn số
    }

    if (tam >= 2147483647LL) return false;
    giaTri = (int)tam;
    return true;
}

// Cấu trúc Hàng đợi (Queue) thủ công dùng cho thuật toán BFS
struct NutHangDoi {
    ToaDo diem;
    int khoangCach;
};

struct HangDoiThuCong {
    NutHangDoi duLieu[1000000];
    int dau, cuoi;

    void khoiTao() {
        dau = 0;
        cuoi = 0;
    }

    void dayVao(ToaDo p, int kc) {
        duLieu[cuoi++] = { p, kc };
    }

    bool rong() {
        return dau == cuoi;
    }

    NutHangDoi layRa() {
        return duLieu[dau++];
    }
};

// Bản đồ kho lưu bằng mảng 2 chiều tĩnh (tối đa 1000x1000)
char banDoKho[1005][1005];
int bangKhoangCach[1005][1005];
ToaDo bangVet[1005][1005];
HangDoiThuCong hangDoiBFS;

// Hàm BFS tìm đường đi ngắn nhất giữa điểm bắt đầu và điểm đích
int timDuongBFS(int tongSoHang, int tongSoCot, ToaDo diemBatDau, ToaDo diemDich, ToaDo duongDiRa[], int& doDaiDuongDi) {
    // Kiểm tra điểm đầu/cuối có hợp lệ hoặc nằm trong vật cản (#) không
    if (diemBatDau.hang < 0 || diemBatDau.hang >= tongSoHang || diemBatDau.cot < 0 || diemBatDau.cot >= tongSoCot || banDoKho[diemBatDau.hang][diemBatDau.cot] == '#') return -1;
    if (diemDich.hang < 0 || diemDich.hang >= tongSoHang || diemDich.cot < 0 || diemDich.cot >= tongSoCot || banDoKho[diemDich.hang][diemDich.cot] == '#') return -1;

    // Nếu đứng tại chỗ
    if (diemBatDau.hang == diemDich.hang && diemBatDau.cot == diemDich.cot) {
        duongDiRa[0] = diemBatDau;
        doDaiDuongDi = 1;
        return 0;
    }

    // Khởi tạo lại bảng khoảng cách
    for (int i = 0; i < tongSoHang; i++) {
        for (int j = 0; j < tongSoCot; j++) {
            bangKhoangCach[i][j] = -1;
        }
    }

    hangDoiBFS.khoiTao();
    hangDoiBFS.dayVao(diemBatDau, 0);
    bangKhoangCach[diemBatDau.hang][diemBatDau.cot] = 0;

    // 4 hướng di chuyển: lên, xuống, trái, phải
    int dHang[] = { -1, 1, 0, 0 };
    int dCot[] = { 0, 0, -1, 1 };

    bool daTimThay = false;
    while (!hangDoiBFS.rong()) {
        NutHangDoi hienTai = hangDoiBFS.layRa();

        if (hienTai.diem.hang == diemDich.hang && hienTai.diem.cot == diemDich.cot) {
            daTimThay = true;
            break;
        }

        for (int i = 0; i < 4; i++) {
            int hangMoi = hienTai.diem.hang + dHang[i];
            int cotMoi = hienTai.diem.cot + dCot[i];

            if (hangMoi >= 0 && hangMoi < tongSoHang && cotMoi >= 0 && cotMoi < tongSoCot && banDoKho[hangMoi][cotMoi] == '.' && bangKhoangCach[hangMoi][cotMoi] == -1) {
                bangKhoangCach[hangMoi][cotMoi] = hienTai.khoangCach + 1;
                bangVet[hangMoi][cotMoi] = hienTai.diem;
                hangDoiBFS.dayVao({ hangMoi, cotMoi }, hienTai.khoangCach + 1);
            }
        }
    }

    if (!daTimThay) return -1;

    // Truy hồi lại đường đi từ đích về bắt đầu
    ToaDo duongDiTam[2005];
    int dem = 0;
    ToaDo viTriHienTai = diemDich;
    while (!(viTriHienTai.hang == diemBatDau.hang && viTriHienTai.cot == diemBatDau.cot)) {
        duongDiTam[dem++] = viTriHienTai;
        viTriHienTai = bangVet[viTriHienTai.hang][viTriHienTai.cot];
    }
    duongDiTam[dem++] = diemBatDau;

    // Đảo ngược lại để được đường đi từ bắt đầu -> đích
    doDaiDuongDi = 0;
    for (int i = dem - 1; i >= 0; i--) {
        duongDiRa[doDaiDuongDi++] = duongDiTam[i];
    }

    return bangKhoangCach[diemDich.hang][diemDich.cot];
}

// Cấu trúc lưu trữ kết quả của mỗi truy vấn
struct KetQuaTruyVan {
    int tongSoBước;
    ToaDo duongDiDayDu[2005];
    int doDaiDuongDiDayDu;
    bool laDuLieuLoi;
};

KetQuaTruyVan mangKetQua[15];

int main() {
    // Tối ưu tốc độ nhập xuất
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    char chuoiHang[20], chuoiCot[20];
    if (!(cin >> chuoiHang >> chuoiCot)) return 0;

    int tongSoHang, tongSoCot;
    if (!kiemTraSoHopLe(chuoiHang, tongSoHang) || !kiemTraSoHopLe(chuoiCot, tongSoCot) || tongSoHang < 1 || tongSoHang > 1000 || tongSoCot < 1 || tongSoCot > 1000) {
        return 0;
    }

    // Đọc bản đồ kho
    for (int i = 0; i < tongSoHang; i++) {
        cin >> banDoKho[i];
    }

    char chuoiSoTruyVan[20];
    if (!(cin >> chuoiSoTruyVan)) return 0;
    int soTruyVan;
    if (!kiemTraSoHopLe(chuoiSoTruyVan, soTruyVan) || soTruyVan < 1 || soTruyVan > 10) return 0;

    // Đọc bỏ dòng thừa sau số lượng truy vấn
    char boDem[1005];
    cin.getline(boDem, 1000);

    // Đọc từng dòng truy vấn
    char cacDongTruyVan[15][1005];
    for (int i = 0; i < soTruyVan; i++) {
        cin.getline(cacDongTruyVan[i], 1000);
    }

    // Xử lý từng truy vấn
    for (int i = 0; i < soTruyVan; i++) {
        int soDiemCanDiQua = -1;
        int danhSachHang[10], danhSachCot[10];
        int demSoLuongSo = 0;

        char* conTro = cacDongTruyVan[i];
        while (*conTro != '\0') {
            while (*conTro == ' ' || *conTro == '\t') conTro++; // Bỏ qua khoảng trắng
            if (*conTro == '\0' || *conTro == '\r' || *conTro == '\n') break;

            char chuoiSoTam[20];
            int chiSoTam = 0;
            while (*conTro != '\0' && *conTro != ' ' && *conTro != '\t' && *conTro != '\r' && *conTro != '\n') {
                chuoiSoTam[chiSoTam++] = *conTro++;
            }
            chuoiSoTam[chiSoTam] = '\0';

            int giaTriSo;
            if (!kiemTraSoHopLe(chuoiSoTam, giaTriSo)) {
                demSoLuongSo = -1; // Đánh dấu lỗi dữ liệu
                break;
            }

            if (demSoLuongSo == 0) {
                soDiemCanDiQua = giaTriSo;
            }
            else {
                int chiSoToaDo = demSoLuongSo - 1;
                if (chiSoToaDo % 2 == 0) {
                    danhSachHang[chiSoToaDo / 2] = giaTriSo;
                }
                else {
                    danhSachCot[chiSoToaDo / 2] = giaTriSo;
                }
            }
            demSoLuongSo++;
        }

        if (demSoLuongSo == -1 || soDiemCanDiQua < 2 || soDiemCanDiQua > 8 || demSoLuongSo != 1 + 2 * soDiemCanDiQua) {
            mangKetQua[i] = { -1, {}, 0, true };
            continue;
        }

        ToaDo danhSachDiem[10];
        bool toaDoKhongHopLe = false;
        for (int j = 0; j < soDiemCanDiQua; j++) {
            int h = danhSachHang[j];
            int c = danhSachCot[j];
            if (h < 0 || h >= tongSoHang || c < 0 || c >= tongSoCot || banDoKho[h][c] == '#') {
                toaDoKhongHopLe = true;
                break;
            }
            danhSachDiem[j] = { h, c };
        }

        if (toaDoKhongHopLe) {
            mangKetQua[i] = { -1, {}, 0, true };
            continue;
        }

        // Trường hợp k = 2 (Đường đi giữa 2 điểm đơn thuần)
        if (soDiemCanDiQua == 2) {
            ToaDo duongDi[2005];
            int doDaiDuongDi = 0;
            int soBước = timDuongBFS(tongSoHang, tongSoCot, danhSachDiem[0], danhSachDiem[1], duongDi, doDaiDuongDi);

            mangKetQua[i].tongSoBước = soBước;
            mangKetQua[i].laDuLieuLoi = false;
            mangKetQua[i].doDaiDuongDiDayDu = doDaiDuongDi;
            for (int j = 0; j < doDaiDuongDi; j++) {
                mangKetQua[i].duongDiDayDu[j] = duongDi[j];
            }
        }
        else {
            // Trường hợp k > 2 (Đi qua nhiều điểm): Thử tất cả các thứ tự thăm điểm (hoán vị)
            int hoanVi[10];
            for (int j = 0; j < soDiemCanDiQua - 1; j++) hoanVi[j] = j + 1;

            int soBướcToiThieu = 2000000000;
            ToaDo duongDiTotNhat[2005];
            int doDaiDuongDiTotNhat = 0;
            bool timThayDuongDi = false;

            // Vòng lặp sinh hoán vị (tối đa 7! = 5040 cách với k <= 8)
            while (true) {
                int soBướcHienTai = 0;
                ToaDo duongDiTamThoi[2005];
                int doDaiTamThoi = 0;

                ToaDo viTriHienTai = danhSachDiem[0];
                duongDiTamThoi[doDaiTamThoi++] = viTriHienTai;
                bool coTheDi = true;

                for (int j = 0; j < soDiemCanDiQua - 1; j++) {
                    int chiSoDiemDich = hoanVi[j];
                    ToaDo duongDiCon[2005];
                    int doDaiCon = 0;
                    int soBướcCon = timDuongBFS(tongSoHang, tongSoCot, viTriHienTai, danhSachDiem[chiSoDiemDich], duongDiCon, doDaiCon);

                    if (soBướcCon == -1) {
                        coTheDi = false;
                        break;
                    }
                    soBướcHienTai += soBướcCon;

                    // Nối đường đi (bỏ qua điểm đầu vì trùng với điểm cuối của đoạn trước)
                    for (int p = 1; p < doDaiCon; p++) {
                        duongDiTamThoi[doDaiTamThoi++] = duongDiCon[p];
                    }
                    viTriHienTai = danhSachDiem[chiSoDiemDich];
                }

                if (coTheDi && soBướcHienTai < soBướcToiThieu) {
                    soBướcToiThieu = soBướcHienTai;
                    timThayDuongDi = true;
                    doDaiDuongDiTotNhat = doDaiTamThoi;
                    for (int p = 0; p < doDaiTamThoi; p++) {
                        duongDiTotNhat[p] = duongDiTamThoi[p];
                    }
                }

                // Thuật toán tìm hoán vị kế tiếp
                int x = soDiemCanDiQua - 2;
                while (x > 0 && hoanVi[x - 1] > hoanVi[x]) x--;
                if (x == 0 && hoanVi[0] > hoanVi[1]) break; // Đã hết hoán vị

                int y = soDiemCanDiQua - 2;
                while (hoanVi[y] < hoanVi[x - 1]) y--;

                // Đổi chỗ
                int tam = hoanVi[x - 1];
                hoanVi[x - 1] = hoanVi[y];
                hoanVi[y] = tam;

                // Đảo ngược đoạn phía sau
                int l = x, r = soDiemCanDiQua - 2;
                while (l < r) {
                    tam = hoanVi[l];
                    hoanVi[l] = hoanVi[r];
                    hoanVi[r] = tam;
                    l++; r--;
                }
            }

            if (!timThayDuongDi) {
                mangKetQua[i] = { -1, {}, 0, false };
            }
            else {
                mangKetQua[i].tongSoBước = soBướcToiThieu;
                mangKetQua[i].laDuLieuLoi = false;
                mangKetQua[i].doDaiDuongDiDayDu = doDaiDuongDiTotNhat;
                for (int j = 0; j < doDaiDuongDiTotNhat; j++) {
                    mangKetQua[i].duongDiDayDu[j] = duongDiTotNhat[j];
                }
            }
        }
    }

    // IN PHẦN 1: Số bước tối thiểu cho mỗi truy vấn
    for (int i = 0; i < soTruyVan; i++) {
        if (mangKetQua[i].laDuLieuLoi) {
            cout << "INVALID\n";
        }
        else {
            cout << mangKetQua[i].tongSoBước << "\n";
        }
    }

    // IN PHẦN 2: Chi tiết các bước di chuyển (tối đa 10 bước đầu)
    for (int i = 0; i < soTruyVan; i++) {
        if (mangKetQua[i].laDuLieuLoi || mangKetQua[i].tongSoBước == -1) {
            cout << "-\n";
        }
        else {
            int gioiHanIn = mangKetQua[i].doDaiDuongDiDayDu < 11 ? mangKetQua[i].doDaiDuongDiDayDu : 11;
            for (int j = 0; j < gioiHanIn; j++) {
                cout << "(" << mangKetQua[i].duongDiDayDu[j].hang << "," << mangKetQua[i].duongDiDayDu[j].cot << ")";
                if (j < gioiHanIn - 1) cout << " ";
            }
            if (mangKetQua[i].doDaiDuongDiDayDu > 11) {
                cout << " ...";
            }
            cout << "\n";
        }
    }

    return 0;
}