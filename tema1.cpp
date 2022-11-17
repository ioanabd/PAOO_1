#include <iostream>
using namespace std;

class Plant{
    
private:
    int age;
    
protected:
    int root = 0;
    
public:
     Plant(): age(0), root(0)
    {
        root++;
        cout << "\n Constrcutor executed \n";
    }
    ~Plant()
    {
        cout << "\n Destructor executed \n";
        root--;
    }

    void setAge(int a)
    {
        age = a;
    };

    int getAge()
    {
        return age;
    }

    int getRoot()
    {
        return root;
    }
};
class Fruit : public Plant
{
private:
    int flowers, leaves;

public:
    Fruit(int f, int l):flowers(f), leaves(l)
    {
        flowers = f;
        leaves = l;
    }
    // copy constructor
    Fruit(const Fruit &rhs)
    {
        flowers = rhs.flowers;
        leaves = rhs.leaves;
    }

    int getFlowers() { return flowers; }
    int getLeaves() { return leaves; }
};
class Uncopyable
{
protected:           // allow construction
    Uncopyable() {}  // and destruction of
    ~Uncopyable() {} // derived objects...
private:
    Uncopyable(const Uncopyable &); // ...but prevent copying
    Uncopyable &operator=(const Uncopyable &);
};

class Vegetable : private Uncopyable, public Plant
{
public:
    bool safeToEat;
    Vegetable();

private:
    Vegetable(const Vegetable &); // declarations only
    Vegetable &operator=(const Vegetable &);
};
int main()
{
    Plant plant;
    plant.setAge(2);
    cout << endl;
    cout << "plant age = " << plant.getAge();
    cout << endl;
    cout << "plant root = " << plant.getRoot() << endl;

    Fruit mango(5, 10);
    Fruit grape = mango;
    Fruit strawberry(mango);

    cout << "mango flowers = " << mango.getFlowers() << endl;
    cout << "mango leaves = " << mango.getLeaves() << endl;
    cout << "grape flowers = " << grape.getFlowers() << endl;
    cout << "grape leaves = " << grape.getLeaves() << endl;
    cout << "strawberry flowers = " << strawberry.getFlowers() << endl;
    cout << "strawberry leaves = " << strawberry.getLeaves() << endl;
    cout << "strawberry root = " << strawberry.getRoot() << endl;

    mango.setAge(20);
    cout << "mango age = " << mango.getAge() << endl;
    return 0;
    
    Vegetable veggy;
    veggy.safeToEat = true;
    // Vegetable carrot(veggy); error
}
