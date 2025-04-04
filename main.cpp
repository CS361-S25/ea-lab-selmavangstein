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
    Organism* reproduce() {
        // Create a new organism with the same behavior as the parent
        return new Organism(behavior);
    };

    void mutate(emp::Random random) { //YOU ARE HERE AND NEED TO FIX THIS
        // Mutate the behavior of the organism
        behavior += random.GetDouble(-0.1, 0.1);
        if (behavior < 0) behavior = 0;
        if (behavior > 1) behavior = 1;
    };
};

int main() {
    emp::vector<Organism> population;
    for (int i = 0; i < 100; ++i) {
        // Create a new organism with random behavior
        population.push_back(*new Organism(0.5));
    }

    // Display the behavior of organism nr 50
    population[50].display();
    // Reproduce organism nr 50
    Organism* child = population[50].reproduce();
    // Display the behavior of the child
    child->display();
    //print adresses of parent and child
    std::cout << "Parent address: " << &population[50] << std::endl;
    std::cout << "Child address: " << child << std::endl;

    emp::Random random(1);

    for (int i = 0; i < 100; ++i) {
        //for each update, find organism with maximum behavior
        double max_behavior = 0;
        Organism max_individual = population[0];
        for(Organism j : population) {
            if (j.behavior > max_behavior) {
                max_behavior = j.behavior;
                max_individual = j;
            }
        }
        Organism* best_child = max_individual.reproduce();
        population[0] = *best_child;
    }
    std::cout << "Population size: " << population.size() << std::endl;
    // Display the behavior of the best organism
    population[0].display();
    return 0;
}


