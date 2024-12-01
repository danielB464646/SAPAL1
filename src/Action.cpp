#include "Action.h"
#include <algorithm> 
#include <stdexcept>

#include <iostream>

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

// Virtual destructor (optional to define explicitly, defaulted in header)
BaseAction::~BaseAction() {
    // Cleanup, if needed
}


//------------ADDFACILITY-----------
AddFacility::AddFacility(const string &facilityName, const FacilityCategory facilityCategory, 
const int price, const int lifeQualityScore, const int economyScore, const int environmentScore)