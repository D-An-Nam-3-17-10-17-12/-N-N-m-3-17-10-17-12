#ifndef THUVIEN_H
#define THUVIEN_H

// ==================================================
// 1. KHAI BAO CAC THU VIEN CAN THIET
// ==================================================

#include <iostream>   // Nhap va xuat du lieu
#include <vector>     // Su dung vector
#include <string>     // Su dung string
#include <queue>      // Su dung hang doi cho BFS
#include <sstream>    // Tach chuoi thanh cac phan
#include <algorithm>  // Su dung reverse, min
#include <climits>    // Su dung gioi han so nguyen
#include <limits>     // Su dung numeric_limits

using namespace std;


// ==================================================
// 2. KHAI BAO CAU TRUC DU LIEU KHO HANG
// ==================================================

struct KhoHang
{
    int R, C;                 // R: so hang, C: so cot

    vector<string> banDo;     // Luu ban do kho hang
};


// ==================================================
// 3. KHAI BAO CAC HAM XU LY
// ==================================================

// Ham BFS tinh khoang cach ngan nhat
// start: vi tri xuat phat
// finish: vi tri dich
// Tra ve so buoc hoac -1 neu khong co duong di

int bfs(KhoHang kho, int start, int finish);


// Ham BFS truy vet duong di
// Tra ve danh sach cac o di qua

vector<int> bfsPath(KhoHang kho, int start, int finish);


// Ham chuyen chuoi thanh so nguyen
// Tra ve true neu chuyen doi thanh cong

bool chuyenSo(const string& s, long long& value);


// Ham xu ly mot truy van
// ketQua: luu so buoc ngan nhat
// duongDi: luu cac toa do xe di qua

void xuLyTruyVan(
    KhoHang kho,
    const string& dong,
    string& ketQua,
    string& duongDi
);


// ==================================================
// 4. KET THUC KHAI BAO THU VIEN
// ==================================================

#endif