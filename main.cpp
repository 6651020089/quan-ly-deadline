#include<bits/stdc++.h>
using namespace std;

// ======================================================
// 1. CẤU TRÚC CÔNG VIỆC
// ======================================================

const int MAX = 1000;

struct CongViec{
    int ma;
    string ten;
    string monHoc;
    string hanChot;
    int doUuTien;
    bool daHoanThanh;
};

CongViec danhSachCongViec[MAX];
int soLuongCongViec = 0;
