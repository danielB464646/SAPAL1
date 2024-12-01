#include "Plan.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

// Constructor
Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions)
    : plan_id(planId), settlement(settlement), selectionPolicy(selectionPolicy), facilityOptions(facilityOptions),
      status(PlanStatus::AVALIABLE), life_quality_score(0), economy_score(0), environment_score(0) {
    // Constructor body
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
const vector<Facility*> &Plan::getFacilities() const {
    return facilities;
}

// Add a facility to the plan
void Plan::addFacility(Facility* facility) {
    facilities.push_back(facility);
}

// Convert the plan to a string representation
const string Plan::toString() const {
    return "Plan ID: " + std::to_string(plan_id) +
           ", Status: " + ((status == PlanStatus::AVALIABLE) ? "AVAILABLE" : "BUSY");
}
