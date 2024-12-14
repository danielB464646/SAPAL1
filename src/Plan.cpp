#include "Plan.h"
#include <iostream>
#include <sstream> // For std::ostringstream

using std::cout;
using std::endl;
using std::string;

// Constructor
Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const std::vector<FacilityType> &facilityOptions)
    : plan_id(planId), 
      settlement(settlement), 
      selectionPolicy(selectionPolicy), 
      facilityOptions(facilityOptions),
      status(PlanStatus::AVALIABLE), 
      life_quality_score(0), 
      economy_score(0), 
      environment_score(0) {
    // Constructor body
}

// Copy Constructor
Plan::Plan(const Plan &other)
    : plan_id(other.plan_id),
      settlement(other.settlement), // const reference is simply copied
      facilityOptions(other.facilityOptions), // const reference is simply copied
      status(other.status),
      life_quality_score(other.life_quality_score),
      economy_score(other.economy_score),
      environment_score(other.environment_score) {
    // Deep copy facilities
    for (const auto *facility : other.facilities) {
        facilities.push_back(new Facility(*facility)); // Assuming Facility has a copy constructor
    }

    // Deep copy underConstruction
    for (const auto *facility : other.underConstruction) {
        underConstruction.push_back(new Facility(*facility)); // Assuming Facility has a copy constructor
    }

    // Deep copy selectionPolicy
    if (other.selectionPolicy) {
        selectionPolicy = other.selectionPolicy->clone(); // Assuming SelectionPolicy has a `clone()` method
    } else {
        selectionPolicy = nullptr;
    }
}

// Copy Assignment Operator
Plan& Plan::operator=(const Plan &other) {
    if (this != &other) { // Prevent self-assignment
        // Clean up existing resources
        for (auto *facility : facilities) {
            delete facility; // Free allocated memory for facilities
        }
        facilities.clear();

        for (auto *facility : underConstruction) {
            delete facility; // Free allocated memory for underConstruction
        }
        underConstruction.clear();

        delete selectionPolicy; // Free memory for selectionPolicy if it exists

        // Copy primitive and assignable members
        plan_id = other.plan_id;
        status = other.status;
        life_quality_score = other.life_quality_score;
        economy_score = other.economy_score;
        environment_score = other.environment_score;

        // Reuse const references (these cannot be reassigned)
        // settlement = other.settlement; // Cannot reassign const reference
        // facilityOptions = other.facilityOptions; // Cannot reassign const reference

        // Deep copy facilities
        for (const auto *facility : other.facilities) {
            facilities.push_back(new Facility(*facility)); // Assuming Facility has a copy constructor
        }

        // Deep copy underConstruction
        for (const auto *facility : other.underConstruction) {
            underConstruction.push_back(new Facility(*facility)); // Assuming Facility has a copy constructor
        }

        // Deep copy selectionPolicy
        if (other.selectionPolicy) {
            selectionPolicy = other.selectionPolicy->clone(); // Assuming SelectionPolicy has a `clone()` method
        } else {
            selectionPolicy = nullptr;
        }
    }
    return *this;
}

// Destructor
Plan::~Plan() {
    // Delete facilities
    for (auto *facility : facilities) {
        delete facility;
    }

    // Delete underConstruction facilities
    for (auto *facility : underConstruction) {
        delete facility;
    }

    // Delete selectionPolicy
    delete selectionPolicy;
}

// Getters
const int Plan::getlifeQualityScore() const {
    return life_quality_score;
}

const int Plan::getEconomyScore() const {
    return economy_score;
}

const int Plan::getEnvironmentScore() const {
    return environment_score;
}

// Set the selection policy
void Plan::setSelectionPolicy(SelectionPolicy *selectionPolicy) {
    this->selectionPolicy = selectionPolicy;
}

// Step function
void Plan::step() {
    // Placeholder logic for step functionality
    cout << "Executing step for Plan ID: " << plan_id << endl;
}

// Print the current status of the plan
void Plan::printStatus() {
    string statusStr = (status == PlanStatus::AVALIABLE) ? "AVAILABLE" : "BUSY";
    cout << "Plan ID: " << plan_id << " Status: " << statusStr << endl;
}

// Get the list of facilities
const std::vector<Facility*> &Plan::getFacilities() const {
    return facilities;
}

// Add a facility to the plan
void Plan::addFacility(Facility* facility) {
    facilities.push_back(facility);
}

// Convert plan details to a string representation
const string Plan::toString() const {
    std::ostringstream oss;

    oss << "Plan ID: " << plan_id << "\n";
    oss << "Settlement: " << settlement.toString() << "\n"; // Assumes Settlement has a toString() method
    oss << "Selection Policy: " << (selectionPolicy ? selectionPolicy->toString() : "None") << "\n"; // Assumes SelectionPolicy has a toString() method
    oss << "Facilities\n";

    oss << "Status: " << (status == PlanStatus::AVALIABLE ? "Available" : "Unavailable") << "\n";
    oss << "Scores - Life Quality: " << life_quality_score
        << ", Economy: " << economy_score
        << ", Environment: " << environment_score << "\n";

    for (const auto *facility : underConstruction) {
        oss << "  - " << facility->toString() << "\n";
    }

    for (const auto *facility : facilities) {
        oss << "  - " << facility->toString() << "\n";
    }

    return oss.str();
}
