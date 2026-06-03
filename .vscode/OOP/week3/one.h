#ifndef ONE
#define ONE
class walker;
class thief
{
public:
    thief() = default;
    thief(int money):money(money){}
    void steal(walker &passer);

private:
    int money=0;
};


#endif