#ifndef TELLER_H
#define TELLER_H
#include <queue>

class Teller
{
private:

    int IsBusy; // 0 --> available , 1 --> not available(busy)
    int AvailablityTimeTeller; // the time when the teller be available
public:

    Teller()
    {
        IsBusy=0;
    }
    void SetIsBusy(int value)
    {
        IsBusy=value;
    }

    int GetIsBusy()
    {
        return IsBusy;
    }

    void SetAvailablityTimeTeller(int value)
    {
        AvailablityTimeTeller=value;
    }

    int GetAvailablityTimeTeller()
    {
        return AvailablityTimeTeller;
    }

protected:

};

#endif // TELLER_H
