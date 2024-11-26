#include "SelectionPolicy.h"


//constructor
NaiveSelection::NaiveSelection(){
    lastSelectedIndex=0;
};


const FacilityType& NaiveSelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
    if (lastSelectedIndex >= facilitiesOptions.size()) {
        lastSelectedIndex = 0;  // Reset to the beginning if out of bounds
    }

    const FacilityType& selectedFacility = facilitiesOptions[lastSelectedIndex];

    // Move to the next index for the next selection
    lastSelectedIndex++;

    return selectedFacility;
}

// Method to return the string representation of NaiveSelection
const string NaiveSelection::toString() const {
    return "NaiveSelection";  // A simple string for demonstration, can be expanded
}

// Method to clone the NaiveSelection object
NaiveSelection* NaiveSelection::clone() const {
    return new NaiveSelection(*this);  // Return a new instance with the same state
}

//-------------

BalancedSelection::BalancedSelection(int LifeQualityScoreVal, int EconomyScoreVal, int EnvironmentScoreVal)
{
    LifeQualityScore = LifeQualityScoreVal;
    EconomyScore = EconomyScoreVal;
    EnvironmentScore = EnvironmentScoreVal;
}

const FacilityType& BalancedSelection::selectFacility(const vector<FacilityType>& facilitiesOptions)
{
    int maxbalance =9999;
    int maxbalanceindex=0;

    for (size_t i = 0; i < facilitiesOptions.size(); ++i) {
        const FacilityType& facility = facilitiesOptions[i];
        facility.getEconomyScore();  
    }

}