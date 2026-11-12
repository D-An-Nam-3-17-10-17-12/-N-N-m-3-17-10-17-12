#include "thuvien.h"  // Goi file thu vien chung

int main()
{
    // ==========================================
    // 1. KHAI BAO VA NHAP KICH THUOC KHO
    // ==========================================

    KhoHang kho;  // Tao doi tuong kho hang

    cout << "========================================\n";
    cout << " CHUONG TRINH TIM DUONG DI TRONG KHO\n";
    cout << "========================================\n";

    // Nhap so hang va so cot
    cout << "Nhap so hang R va so cot C: ";
    cin >> kho.R >> kho.C;

    // Kiem tra kich thuoc kho
    if (kho.R < 1 || kho.R > 1000 ||
        kho.C < 1 || kho.C > 1000)
    {
        cout << "Kich thuoc kho khong hop le!\n";
        return 0;
    }


    // ==========================================
    // 2. NHAP BAN DO KHO HANG
    // ==========================================

    kho.banDo.resize(kho.R);

    cout << "\nNhap ban do kho hang:\n";
    cout << "Ky tu . la loi di, # la vat can.\n";

    for (int i = 0; i < kho.R; i++)
    {
        cin >> kho.banDo[i];

        // Kiem tra so ky tu cua moi dong
        if ((int)kho.banDo[i].size() != kho.C)
        {
            cout << "Ban do khong hop le!\n";
            return 0;
        }

        // Kiem tra ky tu trong ban do
        for (int j = 0; j < kho.C; j++)
        {
            if (kho.banDo[i][j] != '.' &&
                kho.banDo[i][j] != '#')
            {
                cout << "Ban do khong hop le!\n";
                return 0;
            }
        }
    }


    // ==========================================
    // 3. NHAP SO LUONG TRUY VAN
    // ==========================================

    int Q;

    cout << "\nNhap so luong truy van Q: ";
    cin >> Q;

    if (Q < 1 || Q > 10)
    {
        cout << "So luong truy van khong hop le!\n";
        return 0;
    }

    // Xoa ky tu Enter con lai sau khi nhap Q
    cin.ignore(numeric_limits<streamsize>::max(), '\n');


    // ==========================================
    // 4. KHAI BAO MANG LUU KET QUA
    // ==========================================

    vector<string> ketQua(Q);
    vector<string> duongDi(Q);


    // ==========================================
    // 5. NHAP VA XU LY CAC TRUY VAN
    // ==========================================

    for (int i = 0; i < Q; i++)
    {
        string dong;

        cout << "\nNhap truy van " << i + 1 << ": ";

        // Doc toan bo dong truy van
        getline(cin, dong);

        // Goi ham xu ly trong caidat.cpp
        xuLyTruyVan(
            kho,
            dong,
            ketQua[i],
            duongDi[i]
        );
    }


    // ==========================================
    // 6. XUAT PHAN 1: SO BUOC NGAN NHAT
    // ==========================================

    cout << "\n========================================\n";
    cout << "       PHAN 1: SO BUOC NGAN NHAT\n";
    cout << "========================================\n";

    for (int i = 0; i < Q; i++)
    {
        cout << ketQua[i] << endl;
    }


    // ==========================================
    // 7. XUAT PHAN 2: CAC O DI CHUYEN
    // ==========================================

    cout << "\n========================================\n";
    cout << "          PHAN 2: DUONG DI\n";
    cout << "========================================\n";

    for (int i = 0; i < Q; i++)
    {
        cout << duongDi[i] << endl;
    }


    // ==========================================
    // 8. KET THUC CHUONG TRINH
    // ==========================================

    cout << "\n========================================\n";
    cout << "       CHUONG TRINH KET THUC\n";
    cout << "========================================\n";

    return 0;
}