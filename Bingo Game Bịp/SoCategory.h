#pragma once
#include <vector>
#include <string>

class SoCategory {
public:
    virtual ~SoCategory() = default;

    // Kiểm tra số x có thuộc nhóm này không
    virtual bool        thuocNhom(int x) const = 0;
    virtual std::string tenNhom()         const = 0;

    // Lấy toàn bộ số trong [1–99] thuộc nhóm
    std::vector<int> laySoThuocNhom() const;
};

// ──────────────────────────────────────────────────────
//  INHERITANCE: 8 lớp con kế thừa SoCategory
// ──────────────────────────────────────────────────────

class SoNguyenTo : public SoCategory {
public:
    bool        thuocNhom(int x) const override;
    std::string tenNhom()         const override { return "So nguyen to"; }
};

class SoDoiXung : public SoCategory {
public:
    bool        thuocNhom(int x) const override;
    std::string tenNhom()         const override { return "So doi xung (palindrome)"; }
};

class SoChan : public SoCategory {
public:
    bool        thuocNhom(int x) const override { return x % 2 == 0; }
    std::string tenNhom()         const override { return "So chan"; }
};

class SoLe : public SoCategory {
public:
    bool        thuocNhom(int x) const override { return x % 2 != 0; }
    std::string tenNhom()         const override { return "So le"; }
};

class SoChiaHet5 : public SoCategory {
public:
    bool        thuocNhom(int x) const override { return x % 5 == 0; }
    std::string tenNhom()         const override { return "So chia het 5"; }
};

class SoFibonacci : public SoCategory {
public:
    bool        thuocNhom(int x) const override;
    std::string tenNhom()         const override { return "So Fibonacci"; }
};

class SoChinhPhuong : public SoCategory {
public:
    bool        thuocNhom(int x) const override;
    std::string tenNhom()         const override { return "So chinh phuong"; }
};

class SoChiaHet7 : public SoCategory {
public:
    bool        thuocNhom(int x) const override { return x % 7 == 0; }
    std::string tenNhom()         const override { return "So chia het 7"; }
};

class SoTuyChon : public SoCategory {
private:
    int tuStart, tuEnd;
public:
    SoTuyChon(int start, int end) : tuStart(start), tuEnd(end) {}
    bool        thuocNhom(int x) const override { return x >= tuStart && x <= tuEnd; }
    std::string tenNhom()         const override {
        return "Tu chon (so " + std::to_string(tuStart)
             + " den " + std::to_string(tuEnd) + ")";
    }
};
