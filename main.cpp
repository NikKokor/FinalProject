#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;


class Products
{
    unsigned int price;
    string name;
    int amount;
    unsigned int consumptionRawMaterials;
public:
    void SetPrice(unsigned int _price)
    {
        price = _price;
    }

    unsigned int GetPrice()
    {
        return price;
    }

    void SetAmount(unsigned int _amount)
    {
        amount = _amount;
    }

    int GetAmount()
    {
        return amount;
    }

    void SetName(string _name)
    {
        name = _name;
    }

    string GetName()
    {
        return name;
    }

    void SetConsumptionRawMaterials(unsigned int _crm)
    {
        consumptionRawMaterials = _crm;
    }

    unsigned int GetConsumptionRawMaterials()
    {
        return consumptionRawMaterials;
    }
};

class Bread : public Products
{
public:
    Bread()
    {
        SetPrice(45);
        SetName("Bread");
        SetAmount(0);
        SetConsumptionRawMaterials(4);
    }
};

class Croissant : public Products
{
public:
    Croissant()
    {
        SetPrice(15);
        SetName("Croissant");
        SetAmount(0);
        SetConsumptionRawMaterials(1);
    }
};

class BunWithJam : public Products
{
public:
    BunWithJam()
    {
        SetPrice(35);
        SetName("BunWithJam");
        SetAmount(0);
        SetConsumptionRawMaterials(3);
    }
};

class BunWithPoppySeeds : public Products
{
public:
    BunWithPoppySeeds()
    {
        SetPrice(25);
        SetName("BunWithPoppySeeds");
        SetAmount(0);
        SetConsumptionRawMaterials(2);
    }
};



class RawMaterialsProvider
{
    unsigned int RawMaterials = 1000;
    unsigned int amount = 0;
public:
    unsigned int DeliverRawMaterials()
    {
        if (RawMaterials < amount)
        {
            amount = RawMaterials;
            cout << "The Provider ran out of raw materials!" << endl;
            cout << "------------------------------------------------------" << endl;
        }
        RawMaterials -= amount;
        unsigned int t = amount;
        amount -= amount;
        return t;
    }

    void AcceptOrder(unsigned int count)
    {
        amount = count;
    }
};

class Buyer
{
    Bread bread;
    Croissant croissant;
    BunWithJam bunwithjam;
    BunWithPoppySeeds bunwithpoppyseeds;
    int a[4];
    unsigned int Cash;
public:
    int* Order(unsigned int _Cash)
    {
        Cash = (_Cash / 5) + rand() % (_Cash / 5 * 3 + 1);
        int NumberTypes = 1 + rand() % 4;
        unsigned int MoneyForOneType = Cash / NumberTypes;
        cout << "Order:" << endl;
        if (NumberTypes > 0)
        {
            bread.SetAmount(MoneyForOneType / bread.GetPrice());
            cout << bread.GetName() << ", the right amount: " << bread.GetAmount() << endl;
            NumberTypes--;
        }
        if (NumberTypes > 0)
        {
            bunwithjam.SetAmount(MoneyForOneType / bunwithjam.GetPrice());
            cout << bunwithjam.GetName() << ", the right amount: " << bunwithjam.GetAmount() << endl;
            NumberTypes--;
        }
        if (NumberTypes > 0)
        {
            bunwithpoppyseeds.SetAmount(MoneyForOneType / bunwithpoppyseeds.GetPrice());
            cout << bunwithpoppyseeds.GetName() << ", the right amount: " << bunwithpoppyseeds.GetAmount() << endl;
            NumberTypes--;
        }
        if (NumberTypes > 0)
        {
            croissant.SetAmount(MoneyForOneType / croissant.GetPrice());
            cout << croissant.GetName() << ", the right amount: " << croissant.GetAmount() << endl;
            NumberTypes--;
        }

        cout << "------------------------------------------------------" << endl;
        a[0] = bread.GetAmount();
        a[1] = bunwithjam.GetAmount();
        a[2] = bunwithpoppyseeds.GetAmount();
        a[3] = croissant.GetAmount();
        return (a);
    }

    void ReceiveOrder(int a[])
    {
        bread.SetAmount(0);
        bunwithjam.SetAmount(0);
        bunwithpoppyseeds.SetAmount(0);
        croissant.SetAmount(0);
    }
};

class Bakery
{
protected:
    Bread bread;
    Croissant croissant;
    BunWithJam bunwithjam;
    BunWithPoppySeeds bunwithpoppyseeds;
    int _bread, _bunwithjam, _bunwithpoppyseeds, _croissant;
    unsigned int RawMaterials = 0;
    unsigned int Cash = 1000;
    const int CostRawMaterials = 5;
    int a[4];
public:

    void PrintData()
    {
        cout << "Warehouse:" << endl;
        cout << "Cash: " << Cash << endl;
        cout << "Raw Materials: " << RawMaterials << endl;
        cout << bread.GetName() << " " << bread.GetPrice() << " " << bread.GetAmount() << endl;
        cout << croissant.GetName() << " " << croissant.GetPrice() << " " << croissant.GetAmount() << endl;
        cout << bunwithjam.GetName() << " " << bunwithjam.GetPrice() << " " << bunwithjam.GetAmount() << endl;
        cout << bunwithpoppyseeds.GetName() << " " << bunwithpoppyseeds.GetPrice() << " " << bunwithpoppyseeds.GetAmount() << endl;
        cout << "------------------------------------------------------" << endl;
    }

    unsigned int OrderRawMaterials(unsigned int count)
    {
        if (count * CostRawMaterials > Cash)
            count = Cash / CostRawMaterials;
        Cash -= count * CostRawMaterials;
        return count;
    }

    void ReceiveOrder(unsigned int count)
    {
        RawMaterials += count;
    }

    unsigned int GetCash()
    {
        return Cash;
    }

    void AcceptOrder(int a[])
    {
        _bread = a[0];
        _bunwithjam = a[1];
        _bunwithpoppyseeds = a[2];
        _croissant = a[3];
    }

    int* CompleteOrder()
    {
        if ((bread.GetAmount() - _bread) < 0)
            _bread = bread.GetAmount();
        if (bunwithjam.GetAmount() - _bunwithjam < 0)
            _bunwithjam = bunwithjam.GetAmount();
        if (bunwithpoppyseeds.GetAmount() - _bunwithpoppyseeds < 0)
            _bunwithpoppyseeds = bunwithpoppyseeds.GetAmount();
        if (croissant.GetAmount() - _croissant < 0)
            _croissant = croissant.GetAmount();
        Cash += _bread * bread.GetPrice() + _bunwithjam * bunwithjam.GetPrice() + _bunwithpoppyseeds * bunwithpoppyseeds.GetPrice() + _croissant * croissant.GetPrice();
        bread.SetAmount(bread.GetAmount() - _bread);
        bunwithjam.SetAmount(bunwithjam.GetAmount() - _bunwithjam);
        bunwithpoppyseeds.SetAmount(bunwithpoppyseeds.GetAmount() - _bunwithpoppyseeds);
        croissant.SetAmount(croissant.GetAmount() - _croissant);
        a[0] = _bread;
        a[1] = _bunwithjam;
        a[2] = _bunwithpoppyseeds;
        a[3] = _croissant;
        _bread = 0;
        _bunwithjam = 0;
        _bunwithpoppyseeds = 0;
        _croissant = 0;
        return (a);
    }
};

class Baker : public Bakery
{

public:

    void bakeBread(unsigned int _amount)
    {

        if (RawMaterials - _amount * bread.GetConsumptionRawMaterials() > RawMaterials)
            _amount = RawMaterials / bread.GetConsumptionRawMaterials();
        bread.SetAmount(bread.GetAmount() + _amount);
        RawMaterials -= _amount * bread.GetConsumptionRawMaterials();
    }

    void bakeCroissant(unsigned int _amount)
    {
        if (RawMaterials - _amount * croissant.GetConsumptionRawMaterials() > RawMaterials)
            _amount = RawMaterials / croissant.GetConsumptionRawMaterials();
        croissant.SetAmount(croissant.GetAmount() + _amount);
        RawMaterials -= _amount * croissant.GetConsumptionRawMaterials();
    }

    void bakeBunWithJam(unsigned int _amount)
    {
        if (RawMaterials - _amount * bunwithjam.GetConsumptionRawMaterials() > RawMaterials)
            _amount = RawMaterials / bunwithjam.GetConsumptionRawMaterials();
        bunwithjam.SetAmount(bunwithjam.GetAmount() + _amount);
        RawMaterials -= _amount * bunwithjam.GetConsumptionRawMaterials();
    }

    void bakeBunWithPoppySeeds(unsigned int _amount)
    {
        if (RawMaterials - _amount * bunwithpoppyseeds.GetConsumptionRawMaterials() > RawMaterials)
            _amount = RawMaterials / bunwithpoppyseeds.GetConsumptionRawMaterials();
        bunwithpoppyseeds.SetAmount(bunwithpoppyseeds.GetAmount() + _amount);
        RawMaterials -= _amount * bunwithpoppyseeds.GetConsumptionRawMaterials();
    }
};

int main() {
    srand(time(nullptr));
    Baker baker;
    RawMaterialsProvider provider;
    baker.PrintData();
    provider.AcceptOrder(baker.OrderRawMaterials(50));
    baker.ReceiveOrder(provider.DeliverRawMaterials());
    baker.bakeBread(4);
    baker.bakeBunWithJam(5);
    baker.bakeCroissant(3);
    baker.PrintData();
    Buyer buyer;
    baker.AcceptOrder(buyer.Order(baker.GetCash()));
    buyer.ReceiveOrder(baker.CompleteOrder());
    baker.PrintData();




    return 0;
}
