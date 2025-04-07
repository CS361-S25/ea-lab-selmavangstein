#include <iostream>
#include "Empirical/include/emp/math/Random.hpp"

class Organism {
    public:
        double behavior;

    //constructor
    Organism(double b) : behavior(b) {}

    //display organism behavior
    void display() {
        std::cout << "Organism behavior: " << behavior << std::endl;
    };

    //create child with same behavior as parent
    Organism* reproduce(emp::Random random) {
        // Create a new organism with the same behavior as the parent
        Organism* offspring = new Organism(behavior);
        offspring->mutate(random);
        return offspring;
    };

    void mutate(emp::Random random) {
        // Mutate the behavior of the organism
        double mutation = random.GetRandNormal(0.0, 0.02);
        behavior += mutation;
    };
};

int main() {
    emp::vector<Organism> population;
    for (int i = 0; i < 100; ++i) {
        // Create a new organism with random behavior
        population.push_back(*new Organism(0.5));
    }

    /*
    // Display the behavior of organism nr 50
    population[50].display();
    // Reproduce organism nr 50
    Organism* child = population[50].reproduce();
    // Display the behavior of the child
    child->display();
    //print adresses of parent and child
    std::cout << "Parent address: " << &population[50] << std::endl;
    std::cout << "Child address: " << child << std::endl;
    */

    emp::Random random(1);

    for (int i = 0; i < 10000; ++i) {
        //for each update, find organism with maximum behavior
        double max_behavior = 0;
        Organism max_individual = population[0];
        for(Organism j : population) {
            if (j.behavior > max_behavior) {
                max_behavior = j.behavior;
                max_individual = j;
            }
        }
        Organism* new_org = max_individual.reproduce(random);
        //std::cout << "Best parent behavior: " << max_individual.behavior << std::endl;
        //std::cout << "Best child behavior: " << new_org->behavior << std::endl;

        int overwrite = random.GetUInt(0,100);
        population[overwrite] = *new_org;

    }
    std::cout << "Population size: " << population.size() << std::endl;
    // Display the behavior of the best organism
    double max_behavior = 0;
    for (Organism j : population) {
        if (j.behavior > max_behavior) {
            max_behavior = j.behavior;
        }
    }
    // Display the behavior of the best organism
    std::cout << "Best organism behavior: " << max_behavior << std::endl;
    return 0;
}


