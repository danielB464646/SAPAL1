#include "SelectionPolicy.h"
#include <algorithm> 
#include <stdexcept>


//---------------------------NAIVESELECTION---------------------------------------------
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
    return "NaiveSelection lastselectedindex="+this->lastSelectedIndex;  // A simple string for demonstration, can be expanded
}

// Method to clone the NaiveSelection object
NaiveSelection* NaiveSelection::clone() const {
    return new NaiveSelection(*this);  // Return a new instance with the same state
}

NaiveSelection::~NaiveSelection(){}//has no dynamic memory to release

//-------------BALANCEDSELECTION----------------------------------------------------------------------------

BalancedSelection::BalancedSelection(int LifeQualityScoreVal, int EconomyScoreVal, int EnvironmentScoreVal) : 
LifeQualityScore(LifeQualityScoreVal),EconomyScore(EconomyScoreVal), EnvironmentScore(EnvironmentScoreVal)
{

}

const FacilityType& BalancedSelection::selectFacility(const vector<FacilityType>& facilitiesOptions)
{

    if (facilitiesOptions.empty()) {
        throw std::invalid_argument("Facilities options cannot be empty.");
    }
    
    int mostbalance =9999;
    const FacilityType* toret= &facilitiesOptions[0];
    //int maxbalanceindex=0;

    for (size_t i = 0; i < facilitiesOptions.size(); ++i) {
        const FacilityType& currfacility = facilitiesOptions[i];

        int potentialecon = this->EconomyScore +  currfacility.getEconomyScore();
        int potentiallife = this->LifeQualityScore + currfacility.getLifeQualityScore();
        int potentialenviro = this->EnvironmentScore - currfacility.getEnvironmentScore();


        int maxgap = std::abs(std::max({potentialecon, potentiallife, potentialenviro}) - std::min({potentialecon, potentiallife, potentialenviro}));

        if(maxgap<mostbalance)
        {mostbalance = maxgap;
            toret = &currfacility; 
        }
    }
    return *toret; // because the function signature is to return reference it will return reference.


}

// Method to return the string representation of NaiveSelection
const string BalancedSelection::toString() const {
    return "NaiveSelection obj lifequality: "+this->LifeQualityScore +"  enviro score: "+ this->EnvironmentScore+" economyscore "+this->EconomyScore;  // A simple string for demonstration, can be expanded
}

// Method to clone the NaiveSelection object
BalancedSelection* BalancedSelection::clone() const {
    return new BalancedSelection(*this);  // Return a new instance with the same state
}

BalancedSelection::~BalancedSelection(){}//no dynamic memory to release

//------------ECONOMYSELECTION-----------------------------------------------------------
EconomySelection::EconomySelection(){
    lastSelectedIndex =0;
}

const FacilityType& EconomySelection::selectFacility(const vector<FacilityType>& facilitiesOptions)
{
    int temp;
    while(lastSelectedIndex<facilitiesOptions.size())
    {
        if(facilitiesOptions[lastSelectedIndex].getCategory()==FacilityCategory::ECONOMY)
        {
            temp = lastSelectedIndex;
            lastSelectedIndex+=1;
            return facilitiesOptions[temp];

        }
        lastSelectedIndex+=1;
        if(lastSelectedIndex==facilitiesOptions.size())
        {lastSelectedIndex=0;}
    }
}


const FacilityType& EconomySelection::selectFacility(const vector<FacilityType>& facilitiesOptions)
{
    // Check if there is any ECONOMY facility in the list
    bool economyFound = false;
    for (const auto& facility : facilitiesOptions) {
        if (facility.getCategory() == FacilityCategory::ECONOMY) {
            economyFound = true;
            break;
        }
    }

    // If no ECONOMY facility exists, throw an error
    if (!economyFound) {
        throw std::runtime_error("No ECONOMY facility found.");
    }

    // Proceed with the main loop to select ECONOMY facilities
    while (true) {
        if (facilitiesOptions[lastSelectedIndex].getCategory() == FacilityCategory::ECONOMY) {
            // Return the facility of type ECONOMY
            const FacilityType& selectedFacility = facilitiesOptions[lastSelectedIndex];

            // Move to the next facility in the list (loop back to the beginning if needed)
            lastSelectedIndex = (lastSelectedIndex + 1) % facilitiesOptions.size();

            return selectedFacility;
        }

        // If the current facility is not ECONOMY, just move to the next one
        lastSelectedIndex = (lastSelectedIndex + 1) % facilitiesOptions.size();
    }
}
