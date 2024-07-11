#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <queue>
#include <string>
using namespace std;

class Customer
{
private:
    int ServiceTime;
    int ArrivalTime;
    int DepartureTime;
    int WaitingTime;
    string Name;
    int IsSpecial;

public:

    Customer()
    {
        ServiceTime = 0;
        ArrivalTime = 0;
        Name = "";
        IsSpecial = 0;
    }

    void SetServiceTime(int value)
    {
        ServiceTime = value;
    }

    int GetServiceTime()
    {
        return ServiceTime;
    }

    void SetArrivalTime(int value)
    {
        ArrivalTime = value;
    }

    int GetArrivalTime() const
    {
        return ArrivalTime;
    }

    void SetName(string value)
    {
        Name = value;
    }

    string GetName()
    {
        return Name;
    }

    void SetIsSpecial(int value)
    {
        IsSpecial = value;
    }

    int GetIsSpecial() const
    {
        return IsSpecial;
    }

    void SetDepartureTime(int value)
    {
        DepartureTime = value;
    }
    int GetDepartureTime()
    {
        return DepartureTime;
    }

    void SetWaitingTime(int value)
    {
        WaitingTime=value;
    }
    int GetWaitingTime()
    {
        return WaitingTime;
    }



    bool operator==(const Customer& other) const
    {
        return (Name == other.Name) && (ArrivalTime == other.ArrivalTime) && (ServiceTime == other.ServiceTime);
    }



};

#endif // CUSTOMER_H



