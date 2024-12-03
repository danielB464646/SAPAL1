#include "Action.h"
#include <algorithm> 
#include <stdexcept>

#include <iostream>
#include <unordered_set>
#include <string>

using std::cout;
using std::endl;


// Constructor
BaseAction::BaseAction() : status(ActionStatus::COMPLETED), errorMsg("") {
    // Default constructor body
}




// Get the current status of the action
ActionStatus BaseAction::getStatus() const {
    return status;
}

// Mark the action as completed
void BaseAction::complete() {
    status = ActionStatus::COMPLETED;
    errorMsg = ""; // Clear any previous error messages
}

// Mark the action as an error with a specific message
void BaseAction::error(string errorMsg) {
    status = ActionStatus::ERROR;
    this->errorMsg = errorMsg;
}

// Get the error message
const string &BaseAction::getErrorMsg() const {
    return errorMsg;
}

// Get the error message
const string &BaseAction::realerrormessage() const {
    return errorMsg;
}


// Virtual destructor (optional to define explicitly, defaulted in header)
BaseAction::~BaseAction() {
    // Cleanup, if needed
}





//--------------ADDPLAN-----------------
// Constructor
AddPlan::AddPlan(const string &settlementName, const string &selectionPolicy)
    : settlementName(settlementName), selectionPolicy(selectionPolicy) {

    }

// Override act method
void AddPlan::act(Simulation &simulation) {
    //make sure the name of settlement and selection policy actually exist
    //if error make errorMsg that
    //create the plan initialize with AVAILABLE
    //in simulation add it to plans list
    if(simulation.isSettlementExists(settlementName)==false)
    {
        error("settlemet name provided does not exist :"+settlementName);
    }
    if (!std::unordered_set<std::string>{"nve", "bal", "eco","env"}.count(selectionPolicy)) {
        error("selection policy provided does not exist :"+settlementName);
    }
    else{

    simulation.addPlan(simulation.getSettlement(settlementName),simulation.getSelectionPolicy(selectionPolicy)); //getselectionpolicy returns a pointer to the policy
    complete();
    }
}


//------------ADDFACILITY-----------
AddFacility::AddFacility(const string &facilityName, const FacilityCategory facilityCategory, 
const int price, const int lifeQualityScore, const int economyScore, const int environmentScore):
facilityName(facilityName),facilityCategory(facilityCategory),price(price),lifeQualityScore(lifeQualityScore),economyScore(economyScore),environmentScore(environmentScore)
{

}

void AddFacility::act(Simulation &simulation)
{
    //check if facility already exists
    simulation.addFacility();//the last thing i was wondering if creating of the objects should be in action or simulation - it seems it should be in action so edit act of addplan() and maybe delete getselectionpolicy
}
