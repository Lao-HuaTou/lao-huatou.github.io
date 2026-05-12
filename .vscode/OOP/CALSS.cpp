#include<bits/stdc++.h>
using namespace std;

class Sales_data{
public:
    string isbn() const {
        return bookNo;
    }
    Sales_data &combine(const Sales_data &);//返回的是this，不是sale_data 加&
    double avg_price() const;

private://这里存放的是数据。因为在 private 后面
//所以只有类内部的函数能访问它们，外部的人不能直接修改（比如防止别人不小心把销量改成了负数）。
    string bookNo;//编号
    double revenue = 0.0;//销售总额
    unsigned units_sold = 0;//卖出去的份数
};
double Sales_data::avg_price() const{
    if(units_sold){
        return revenue / units_sold;
    }
    else
        return 0;
}
Sales_data& Sales_data::combine(const Sales_data &rhs){
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
} // total.combine(rhs);