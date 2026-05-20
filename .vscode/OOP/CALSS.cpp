#include<bits/stdc++.h>
using namespace std;

class Sales_data{
    friend istream &read(istream &is, Sales_data &a);//设置友元 使read可以访问private
    friend ostream &print(ostream &os, const Sales_data &a);

public:
    Sales_data() = default;//构造函数
    Sales_data(const string &s) : bookNo(s){}
    Sales_data(const string &s,unsigned n,double p):
            bookNo(s),units_sold(n),revenue(n*p){}
    Sales_data(istream &);
    string isbn() const
    {
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

Sales_data::Sales_data(istream&is){
    read(is, *this);//this为指针 *解引用为指向对象
}

Sales_data add(const Sales_data &a,const Sales_data &b){
    Sales_data sum;
    sum = a;
    sum.combine(b);
    return sum;
}

istream &read(istream &is,Sales_data &a){
    double price = 0;
    is >> a.bookNo >> a.units_sold >> price;
    a.revenue = price * a.units_sold;
    return is;
}
ostream &print(ostream &os,const Sales_data &a){
    os << a.isbn() << " " << a.units_sold << " " << a.revenue << " " << a.avg_price();
    return os;
}

    double Sales_data::avg_price() const
{
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