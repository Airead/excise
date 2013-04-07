/**
 * @file 5.9.4.cc
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/04/04 19:59:03
 */

/*
  Daphne invests $100 at 10% simple interest. That is, every year, the investment earns
  10% of the original investment, or $10 each and every year:
  interest = 0.10 × original balance
  At the same time, Cleo invests $100 at 5% compound interest. That is, interest is 5% of
  the current balance, including previous additions of interest:
  interest = 0.05 × current balance
  Cleo earns 5% of $100 the first year, giving her $105. The next year she earns 5% of
  $105, or $5.25, and so on. Write a program that finds how many years it takes for the
  value of Cleo’s investment to exceed the value of Daphne’s investment and then displays
  the value of both investments at that time.
 */

#include <iostream>

int main(int argc, char *argv[])
{
    using namespace std;

    const float DInterest = 0.1;
    const float OriginInvestment = 100;
    const float CInterest = 0.05;

    int year;
    float DInvestment;
    float CCurrentInvestment;
    
    DInvestment = 100;
    CCurrentInvestment = 100;
    year = 1;
    DInvestment += OriginInvestment * DInterest;
    CCurrentInvestment *= (1 + CInterest);
    while (CCurrentInvestment < DInvestment) {
        year++;
        DInvestment += OriginInvestment * DInterest;
        CCurrentInvestment *= (1 + CInterest);
    }

    cout << year << " years, Cleo's " << CCurrentInvestment << "$ exceed Daphne's " 
         << DInvestment << "$" << endl;

    return 0;
}
