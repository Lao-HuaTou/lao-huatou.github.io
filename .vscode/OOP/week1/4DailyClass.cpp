#include<bits/stdc++.h>
using namespace std;
class pen{
public:
    void write(int words_len){
        if(usable(1.0 * words_len * con_per_word))remains -= 1.0 * words_len * con_per_word;
    }
    bool usable(double con){
        return remains > con;
    }

private:
    double remains;
    string color;
    double con_per_word;
};