#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

struct Lo 
{
    string ma;       
    long long sl;    
};

struct Kho 
{
    queue<Lo> q;         
    long long tong = 0;  
};

unordered_map<string, Kho> khoHang;   
unordered_set<string> maLoDaDung;     

bool laSoHopLe(const string& s)
{
    if (s.empty())
        return false;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] < '0' || s[i] > '9')
            return false;
    }
    return true;
}

bool laQtyHopLe(const string& s) 
{
    if (!laSoHopLe(s)) 
        return false;
    if (s.size() > 10) 
        return false;       
    long long v = stoll(s);
    return v >= 1 && v <= 1000000000LL;
}

bool laMaHopLe(const string& s) 
{
    if (s.empty() || s.size()>20)
        return false;
    return true;
}

vector<string> tachTu(const string& dong)
{
    vector<string> kq;
    stringstream ss(dong);
    string tu;
    while (ss >> tu) 
        kq.push_back(tu);
    return kq;
}


void xuLyImport(const vector<string>& t) 
{
    if (t.size() != 4 || !laMaHopLe(t[1]) || !laMaHopLe(t[2]) || !laQtyHopLe(t[3])) 
    {
        cout << "INVALID\n";
        return;
    }

    string sku = t[1];
    string lot = t[2];
    long long qty = stoll(t[3]);
    if (maLoDaDung.count(lot))
    {
        cout << "DUPLICATE_LOT\n";
        return;
    }
    maLoDaDung.insert(lot);
    khoHang[sku].q.push({ lot, qty });
    khoHang[sku].tong += qty;
    cout << "OK\n";
}

void xuLyExport(const vector<string>& t) 
{
    if (t.size() != 3 || !laMaHopLe(t[1]) || !laQtyHopLe(t[2])) 
    {
        cout << "INVALID\n";
        return;
    }
    string sku = t[1];
    long long can = stoll(t[2]);   
    long long ton = 0;
    auto it = khoHang.find(sku);
    if (it != khoHang.end()) 
        ton = it->second.tong;
    if (ton < can) 
    {
        cout << "NOT_ENOUGH " << ton << "\n";
        return;
    }
    Kho& k = it->second;
    vector<string> ketQua;
    while (can > 0) 
    {
        Lo& dau = k.q.front();              
        if (dau.sl <= can) 
        {                 
            ketQua.push_back(dau.ma + ":" + to_string(dau.sl));
            can -= dau.sl;
            k.tong -= dau.sl;
            k.q.pop();
        }
        else 
        {                            
            ketQua.push_back(dau.ma + ":" + to_string(can));
            dau.sl -= can;
            k.tong -= can;
            can = 0;
        }
    }

    for (size_t i = 0; i < ketQua.size(); i++)
    {
        if (i > 0) cout << " ";
        cout << ketQua[i];
    }
    cout << "\n";
}

void xuLyStock(const vector<string>& t) 
{
    if (t.size() != 2 || !laMaHopLe(t[1])) 
    {
        cout << "INVALID\n";
        return;
    }
    auto it = khoHang.find(t[1]);
    if (it == khoHang.end()) 
        cout << 0 << "\n";
    else 
        cout << it->second.tong << "\n";
}


int main()
{
    int Q;
    cin >> Q;
    cin.ignore();

    string dong;
    for (int i = 0; i < Q; i++)
    {
        getline(cin, dong);
        vector<string> t = tachTu(dong);
        if (t.empty())
        {
            cout << "INVALID\n";
            continue;
        }
        if (t[0] == "IMPORT")
            xuLyImport(t);
        else if (t[0] == "EXPORT")
            xuLyExport(t);
        else if (t[0] == "STOCK")
            xuLyStock(t);
        else
            cout << "INVALID\n";
    }
    return 0;
}
