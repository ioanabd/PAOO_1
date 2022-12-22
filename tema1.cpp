#include <iostream>
using namespace std;
#include <mutex>
#include <thread>
using namespace std;
mutex mtx;

//am eliminat clasele in plus pentru simplitatea codului
//si pentru a evidentia 
class Plant{
    
private:
    int age;
    
protected:
    int root = 0;
    
public:
    int lockPlant;
     Plant(int agePlant): age(0), root(0)
    {
        this->age=agePlant;
        root++;
        cout << "\n Constrcutor executed \n";
    }
    ~Plant()
    {
        cout << "\n Destructor executed \n";
        root--;
    }

    Plant& operator+=(const Plant& rhs)
    { 
        age = age + rhs.age;
        root = root + rhs.root;
        return *this;
    }

    void setAge(int a)
    {
        age = a;
    }

    int getAge()
    {
        return age;
    }

    int getRoot()
    {
        return root;
    }
    void setlockPlant(int lockPlant){
        this->lockPlant = lockPlant;
    }
};

Plant *createPlant(const int agePlant){
    return new Plant(agePlant);
};

void lock(Plant& plant){
    plant.setlockPlant(1);
    cout << "\n locked \n";
};

void unlock(Plant& plant){
    plant.setlockPlant(0);
    cout << "\n unlocked \n";
};
class Uncopyable
{
protected:           
    Uncopyable() {}
    ~Uncopyable() {}
private:
    Uncopyable(const Uncopyable &);
    Uncopyable &operator=(const Uncopyable &);
};
class Lock: Uncopyable{
    private:
       Plant &plant;

    public:
        Lock(Plant &ptr): plant(ptr){
            lock(plant);
        }
        ~Lock(){ 
            unlock(plant);
        }
};

int main()
{
    auto_ptr<Plant> plantaNr1(createPlant(10)); //crestem o planta de 10 ani 
    cout << "\n Age Planta 1: " << plantaNr1->getAge() << endl;;
    auto_ptr<Plant> plantaNr2(plantaNr1);//copiam in plantaNr2, plantaNr1
    cout << "\n Age Planta 2: " << plantaNr2->getAge() << endl;;
    
    shared_ptr<Plant> nufar(createPlant(5));
    cout << "\n Age nufar: " << nufar->getAge() << endl;

    //copiam folosind shared_ptr
    shared_ptr<Plant> ambrozie(nufar);
    cout << "\n Age ambrozie: " << ambrozie->getAge() << endl;
    
    unique_ptr<Plant> trandafir(createPlant(20));
    cout << "\n Root trandafir: " << trandafir->getRoot() << endl;//si destructorul si constructorul sunt apelati

    //unique_ptr<Plant> matraguna(trandafir);//eroare, e pointer unic
   
    Plant orhidee(2); 
    Lock lockedplt(orhidee);//lock cand cream
    orhidee.getAge();//unlock dupa destructor
   
    return 0;
}
