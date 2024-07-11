#ifndef BANK_H
#define BANK_H
#include "Teller.h"
#include "Customer.h"
#include <queue>
#include <string>
#include <algorithm>
#include <deque>

class Bank
{
    deque<Customer> Customers;
    double TotalWaitingTime=0;
    double TotalServiceTime=0;
    Teller teller[3];
    int FirstTempDepartureTime;
    int SecondTempDepartureTime;
    double MaxDepartureTime;
    double TotalBusyTime[3]= {0};
public:
    Bank() {}


    static int SortCustomers(const Customer& FirstCustomer, const Customer& SecondCustomer)
    {
        if (FirstCustomer.GetArrivalTime()==SecondCustomer.GetArrivalTime())
        {
            return FirstCustomer.GetIsSpecial() > SecondCustomer.GetIsSpecial();
        }
        return FirstCustomer.GetArrivalTime()<SecondCustomer.GetArrivalTime();
    }
    void AddCustomer(const Customer& c)
    {
        Customers.push_back(c);
        std::sort(Customers.begin(), Customers.end(), SortCustomers);
    }

    int CheckAvailableTeller()
    {
        for (int i=0; i<3; i++)
        {
            if (!teller[i].GetIsBusy())
            {
                return i;
            }
        }
        return -1;
    }


    int SearchSpecialCustomer()
    {
        int NextTellerIndex=0;
        int TellerMinAvailabilityTime= teller[0].GetAvailablityTimeTeller();
        for (int i=0; i< 3; i++)
        {
            if (teller[i].GetAvailablityTimeTeller()< TellerMinAvailabilityTime)
            {
                TellerMinAvailabilityTime = teller[i].GetAvailablityTimeTeller();
                NextTellerIndex=i;
            }
        }

        for (int i=0; i < Customers.size(); i++)
        {
            Customer c = Customers[i];
            if (c.GetIsSpecial()==1 && c.GetArrivalTime()<= TellerMinAvailabilityTime)
            {
                return i;
            }
        }
        return -1;
    }

    void Simulate()
    {
        while (!Customers.empty())
        {
            int AvaliableIndexOfTeller=CheckAvailableTeller();
            if (AvaliableIndexOfTeller != -1)
            {
                Customer c = Customers.front();
                Teller &CurrentTeller = teller[AvaliableIndexOfTeller];
                c.SetWaitingTime(0);
                c.SetDepartureTime(c.GetArrivalTime()+c.GetServiceTime());
                teller[AvaliableIndexOfTeller].SetIsBusy(1);
                //the time when the teller be available is equal to the time that the customer leave from the bank
                CurrentTeller.SetAvailablityTimeTeller(c.GetDepartureTime());
                TotalBusyTime[AvaliableIndexOfTeller] +=c.GetServiceTime();
                Customers.pop_front();
                TotalWaitingTime += c.GetWaitingTime();
                TotalServiceTime += c.GetServiceTime();
                cout<<"Customer Name: "<<c.GetName()<< " and assigned to teller " << AvaliableIndexOfTeller +1 <<" its Waiting time = "<<c.GetWaitingTime()
                    <<" its Departure Time = "<<c.GetDepartureTime()<< " its Status time = " << (c.GetIsSpecial() == 0 ? " Normal " : " Special ")<< endl;
                    cout<<endl;
                FirstTempDepartureTime=c.GetDepartureTime();
            }
            else
            {
                // Find the index of the teller with the minimum availability time
                int NextTellerIndex=0;
                int TellerMinAvailabilityTime= teller[0].GetAvailablityTimeTeller();
                for (int i=0; i< 3; i++)
                {
                    if (teller[i].GetAvailablityTimeTeller()< TellerMinAvailabilityTime)
                    {
                        TellerMinAvailabilityTime = teller[i].GetAvailablityTimeTeller();
                        NextTellerIndex=i;
                    }
                }

                int SpecialCustomerIndex = SearchSpecialCustomer();
                if (SpecialCustomerIndex != -1)
                {
                    Customer c = Customers[SpecialCustomerIndex];
                    // refer to the next teller
                    Teller &NextTellerOfSpecial = teller[NextTellerIndex];
                    if(TellerMinAvailabilityTime<0)
                    {
                        c.SetWaitingTime(0);
                    }
                    else{
                        c.SetWaitingTime(TellerMinAvailabilityTime - c.GetArrivalTime());
                    }
                    c.SetDepartureTime(c.GetArrivalTime() + c.GetServiceTime() + c.GetWaitingTime());
                    NextTellerOfSpecial.SetIsBusy(1);
                    NextTellerOfSpecial.SetAvailablityTimeTeller(c.GetDepartureTime());
                    TotalBusyTime[NextTellerIndex] +=  c.GetServiceTime();
                    Customers.erase(Customers.begin() + SpecialCustomerIndex);
                    TotalWaitingTime += c.GetWaitingTime();
                    TotalServiceTime += c.GetServiceTime();
                    cout <<"Customer Name: "<<c.GetName()<<" and assigned to teller " << NextTellerIndex +1 <<" its Waiting time = "<<c.GetWaitingTime()
                         <<" its Departure Time = "<<c.GetDepartureTime()<<" its Status time = " << (c.GetIsSpecial() == 0 ? " Normal " : " Special ")<< endl;
                         cout<<endl;
                    SecondTempDepartureTime=c.GetDepartureTime();
                }
                else
                {
                    Customer c = Customers.front();
                    // refer to the next teller
                    Teller &NextTeller = teller[NextTellerIndex];
                    if(TellerMinAvailabilityTime<0)
                    {
                        c.SetWaitingTime(0);
                    }
                    else{
                        c.SetWaitingTime(TellerMinAvailabilityTime - c.GetArrivalTime());
                    }
                    c.SetDepartureTime(c.GetArrivalTime() + c.GetServiceTime() + c.GetWaitingTime());
                    NextTeller.SetIsBusy(1);
                    NextTeller.SetAvailablityTimeTeller(c.GetDepartureTime());
                    TotalBusyTime[NextTellerIndex] +=  c.GetServiceTime();
                    Customers.pop_front();
                    TotalWaitingTime += c.GetWaitingTime();
                    TotalServiceTime += c.GetServiceTime();
                    cout <<"Customer Name: "<<c.GetName()<<" and assigned to teller " << NextTellerIndex +1 <<" its Waiting time = "<<c.GetWaitingTime()
                         <<" its Departure Time = "<<c.GetDepartureTime()<<" its Status time = " << (c.GetIsSpecial() == 0 ? " Normal " : " Special ")<< endl;
                         cout<<endl;
                    SecondTempDepartureTime=c.GetDepartureTime();
                }


            }

        }
        MaxDepartureTime = std::max(FirstTempDepartureTime,SecondTempDepartureTime);
        //cout << "Max Departure Time = "<<MaxDepartureTime<<endl;
    }

    void TellerUtilizationRate()
    {
        double AvailableTime=MaxDepartureTime;
        for (int i=0; i<3; i++)
        {
            cout << "Teller "<<i+1<<" Utilization Rate= "<<static_cast<double>(TotalBusyTime[i]/AvailableTime)*100<<"%"<<endl;
            cout<<endl;
            //cout<< "test of busy time = "<<TotalBusyTime[i]<<endl;
        }
    }

    double CalculateAvgWaitingTime(int NumberOfCustomers)
    {
        double AvgWaitingTime = TotalWaitingTime /  NumberOfCustomers;
        return AvgWaitingTime;
    }

    double CalculateAvgServiceTime(int NumberOfCustomers)
    {
        double AvgServiceTime = TotalServiceTime /  NumberOfCustomers;
        return AvgServiceTime;
    }

protected:

private:
};

#endif // BANK_H
