class Box {
private:
    double length; // 私有成员
    double width;
    double height;

public:
    Box(double l, double w, double h) : length(l), width(w), height(h) {
    } // 构造函数

    double getVolume() const { // 公共成员函数
        return length * width * height;
    }

    // ... 其他成员函数 ...
};