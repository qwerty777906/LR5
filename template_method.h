#ifndef TEMPLATE_METHOD_H_INCLUDED
#define TEMPLATE_METHOD_H_INCLUDED

#include <iostream>
using namespace std;

class KovrikSaleProcess
{
public:
    virtual ~KovrikSaleProcess() = default;

    void sale()
    {
        showSpecs();
        calculateDelivery();
        completeSale();
    }

protected:
    virtual void showSpecs() = 0;
    virtual void calculateDelivery() = 0;

    void completeSale()
    {
        cout << "Sale completed successfully!" << endl;
    }
};

class GembirdSale : public KovrikSaleProcess
{
protected:
    void showSpecs() override
    {
        cout << "[Gembird Mat] Affordable and colorful." << endl;
    }

    void calculateDelivery() override
    {
        cout << "Delivery within 7-10 business days." << endl;
    }
};

class DefenderSale : public KovrikSaleProcess
{
protected:
    void showSpecs() override
    {
        cout << "[Defender Mat] Durable and backlit." << endl;
    }

    void calculateDelivery() override
    {
        cout << "Standard delivery: 5-7 business days." << endl;
    }
};

class LogitechSale : public KovrikSaleProcess
{
protected:
    void showSpecs() override
    {
        cout << "[Logitech Mat] Premium with wireless charging." << endl;
    }

    void calculateDelivery() override
    {
        cout << "Express delivery within 1-2 days." << endl;
    }
};

#endif // TEMPLATE_METHOD_H_INCLUDED
