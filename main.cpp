#include <iostream>
#include <queue>
#include <deque>
#include "Customer.h"
#include "Teller.h"
#include "Bank.h"
#include <string>
using namespace std;

int main()
{
    Customer customer;
    int NumberOfCustomers;
    Bank bank;
    string Name;
    int ArrivalTime;
    int ServiceTime;
    int IsSpecial;

    cout<<"Enter The Number Of the Customers ";
    cin>>NumberOfCustomers;
    for (int i=0 ; i<NumberOfCustomers ; i++)
    {
        cout<<"Enter The Name Of Customer Number: "<<i+1<<") ";
        cin>>Name;
        customer.SetName(Name);

        cout<<"Enter The Arrival Time Of Customer Number: "<<i+1<<") ";
        cin>>ArrivalTime;
        customer.SetArrivalTime(ArrivalTime);

        cout<<"Enter The Service Time Of Customer Number: "<<i+1<<") ";
        cin>>ServiceTime;
        customer.SetServiceTime(ServiceTime);

        cout<<"Enter The Status Of Customer Number (0/1) [0] for Normal , [1] for special : "<<i+1<<") ";
        cin>>IsSpecial;
        customer.SetIsSpecial(IsSpecial);

        bank.AddCustomer(customer);

    }

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    bank.Simulate();
    cout<< "The Average Waiting Time= "<< bank.CalculateAvgWaitingTime(NumberOfCustomers)<<endl;
    cout<<endl;
    cout<<"The Average Service Time= "<<bank.CalculateAvgServiceTime(NumberOfCustomers)<<endl;
    cout<<endl;
    bank.TellerUtilizationRate();
    return 0;
}





