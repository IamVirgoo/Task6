#include <iostream>
#include <vector>
#include <string>

#include "pugiconfig.hpp"
#include "pugixml.hpp"
#include "pugixml.cpp"

using namespace std;
using namespace pugi;

class People {
    private:
        string name;
        int age;
    public:
        People() = default;
        People(string Name, int Age) {
            this->name = Name;
            this->age = Age;
        }

        string getName() { return this->name; }
        int getAge() { return this->age; }
};

class Worker {
    private:
        People people;
        float standing;
        float salary;
    public:
        Worker() = default;
        Worker(People man, float Standing, float Salary) {
            this->people = man;
            this->standing = Standing;
            this->salary = Salary;
        }

        People getPeople() { return this->people; }
        float  getStanding() { return this->standing; }
        float getSalary() { return this->salary; }
};

class Population {
    private:
        vector<People> peoples;
        vector<Worker> workers;
    public:
        Population() = default;
        Population(vector<People> Peoples, vector<Worker> Workers) {
            this->peoples = Peoples;
            this->workers = Workers;
        }

        vector<People> getPeoples() { return this->peoples; }
        vector<Worker> getWorkers() { return this->workers; }

        void outputPeopleInfo() {
            for (int i = 0; i < this->getPeoples().size(); i++) {
                cout << "Name: " << this->getPeoples()[i].getName() << " "
                     << "Age: " << this->getPeoples()[i].getAge() << '\n';
            }
        }

        void outputWorkerInfo() {
            for (int i = 0; i < this->getWorkers().size(); i++) {
                cout << "People: " << '\n' << '\t'
                << "Name: " << this->getWorkers()[i].getPeople().getName() << '\n' << '\t'
                << "Age: " << this->getWorkers()[i].getPeople().getAge() << '\n'
                << "Standing: " << this->getWorkers()[i].getStanding() << '\n'
                << "Salary: " << this->getWorkers()[i].getSalary() << '\n';
            }
        }
};
class Territories {
    private:
        int size;
    public:
        Territories() = default;
        Territories(int Size) {
            this->size = Size;
        }

        int getSize() { return this->size; }
};

class State {
    private:
        Territories territories;
        Population population;
    public:
        State() = default;
        State(Territories territoriesInit, Population populationInit) {
            this->territories = territoriesInit;
            this->population = populationInit;
        }

        Territories getTerritories() { return this->territories; }
        Population getPopulation() { return this->population; }
};

class XmlWorker {
private:
    State state;

    void addPeople(xml_node parent, int index) {
        xml_node people = parent.append_child("PEOPLE");

        xml_node name = people.append_child("NAME");
        name.append_child(node_pcdata).set_value(this->state.getPopulation().getWorkers()[index].getPeople().getName().c_str());
        xml_node age = people.append_child("AGE");
        age.append_child(node_pcdata).set_value(to_string(this->state.getPopulation().getWorkers()[index].getPeople().getAge()).c_str());
    }

    void addPeoples(xml_node parent) {
        for (int i = 0; i < this->state.getPopulation().getPeoples().size(); i++) {
            xml_node people = parent.append_child("PEOPLE");

            xml_node name = people.append_child("NAME");
            name.append_child(node_pcdata).set_value(this->state.getPopulation().getPeoples()[i].getName().c_str());
            xml_node age = people.append_child("AGE");
            age.append_child(node_pcdata).set_value(to_string(this->state.getPopulation().getPeoples()[i].getAge()).c_str());
        }
    }

    void addWorker(xml_node parent) {
        for (int i = 0; i < this->state.getPopulation().getWorkers().size(); i++) {
            xml_node worker = parent.append_child("WORKER");
            addPeople(worker, i);
            xml_node standing = worker.append_child("STANDING");
            standing.append_child(node_pcdata).set_value(to_string(this->state.getPopulation().getWorkers()[i].getStanding()).c_str());
            xml_node salary = worker.append_child("SALARY");
            salary.append_child(node_pcdata).set_value(to_string(this->state.getPopulation().getWorkers()[i].getSalary()).c_str());
        }
    }

    void xmlInit(xml_node root) {
        xml_node state = root.append_child("STATE");
        xml_node territories = state.append_child("TERRITORIES");
        xml_node population = state.append_child("WORKERS");

        xml_node size = territories.append_child("SIZE");
        size.append_child(node_pcdata).set_value(to_string(this->state.getTerritories().getSize()).c_str());

        addPeoples(population);

        xml_node workers = population.append_child("WORKERS");

        addWorker(workers);
    }

public:
    XmlWorker() = default;
    XmlWorker(xml_node root, State state) : state(state) {
        this->xmlInit(root);
    }
};

string gen_random(const int len) {
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}

int main() {
    vector<State> states;
    State firstState = State(Territories(1000),
                             Population(
                                     {
                                         People("Billy Bonce", 48),
                                         People("Dr. Livsi", 42),
                                         People("Jimmy", 22)
                                      },
                                      {
                                         Worker(People("Billy Bonce", 48), 2.12, 30000),
                                         Worker(People("Dr. Livsi", 42), 2.34, 40000),
                                         Worker(People("Jimmy", 22), 1.2, 100000)
                                      }));
    State secondState = State(Territories(1000),
                             Population(
                                     {
                                             People("Billy Bonce", 48),
                                             People("Dr. Livsi", 42),
                                             People("Jimmy", 22)
                                     },
                                     {
                                             Worker(People("Billy Bonce", 48), 2.12, 30000),
                                             Worker(People("Dr. Livsi", 42), 2.34, 40000),
                                             Worker(People("Jimmy", 22), 1.2, 100000)
                                     }));
    State thirdState = State(Territories(1000),
                             Population(
                                     {
                                             People("Billy Bonce", 48),
                                             People("Dr. Livsi", 42),
                                             People("Jimmy", 22)
                                     },
                                     {
                                             Worker(People("Billy Bonce", 48), 2.12, 30000),
                                             Worker(People("Dr. Livsi", 42), 2.34, 40000),
                                             Worker(People("Jimmy", 22), 1.2, 100000)
                                     }));
    states.push_back(firstState); states.push_back(secondState); states.push_back(thirdState);

    xml_document document;
    xml_node root = document.append_child("STATES");
    for (auto state : states) {
        XmlWorker xmlWorker = XmlWorker(root, state);
    }
    document.save_file("/home/iamvirgoo/CLionProjects/Task6/serialisation.xml");

    int operationNumber;
    do {
        cout << "==================== DATABASE Worker ====================" << '\n'
             << "1 - Output all records" << '\n'
             << "2 - Append record" << '\n'
             << "3 - Remove record" << '\n'
             << "0 - Exit" << '\n' << '\n'
             << "Enter the operation of number: ";
        cin >> operationNumber;
        cout << '\n';

        switch (operationNumber) {
            case 1 : {
                for (auto state : states) {
                    state.getPopulation().outputPeopleInfo();
                    cout << "---------------" << '\n';
                    state.getPopulation().outputWorkerInfo();
                    cout << "===============" << '\n';
                }
                break;
            }
            case 2 : {
                states.emplace_back(State(Territories(1000 + rand() % 5000),
                                          Population(
                                                  {
                                                          People(gen_random(20), 20 + rand() % 40),
                                                          People(gen_random(20), 20 + rand() % 40),
                                                          People(gen_random(20), 20 + rand() % 40)
                                                  },
                                                  {
                                                          Worker(People(gen_random(20), 20 + rand() % 40), rand() / 5, rand() % 40000),
                                                          Worker(People(gen_random(20), 20 + rand() % 40), rand() / 5, rand() % 40000),
                                                          Worker(People(gen_random(20), 20 + rand() % 40), rand() / 5, rand() % 40000)
                                                  })));
                cout << '\n' << "Added!" << '\n';
                break;
            }
            case 3 : {
                int index;
                cout << '\n' << "Enter the index of position: ";
                cin >> index;
                cout << '\n';
                states.erase(states.begin() + index);
                cout << '\n' << "Deleted!" << '\n';
                break;
            }
        }
    } while (operationNumber != 0);
    return 0;
}
