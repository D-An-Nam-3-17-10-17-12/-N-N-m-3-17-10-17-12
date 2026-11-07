#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

const int sohangvacottoida = 1000;
const int sophantutoida = sohangvacottoida * sohangvacottoida;

inline int R, C;
inline char bandokho[sohangvacottoida][sohangvacottoida];
inline int buoc[sohangvacottoida][sohangvacottoida];       // số bước từ điểm xuất phát tới từng ô
inline queue<pair<int, int>> hangdoi;

void them(int r, int c, int b);
void loang(int r0, int c0);
bool kiemtralaso(string noidung);
bool kiemtratoado(int r, int c);
void timhoanvi(int k, bool daxet[], int vitri, int khoangcach[][8], int dodai, int &ketqua);
int timduongnhonhat(int k, int danhsachR[], int danhsachC[]);
