#include "Action.h"
#include <algorithm> 
#include <stdexcept>

#include <iostream>
#include <unordered_set>
#include <string>
using std::ostringstream;

using std::cout;
using std::endl;

#include <sstream>
// Constructor
BaseAction::BaseAction() : status(ActionStatus::COMPLETED), errorMsg("") {
    // Default constructor body
}




// Get the current status of the action
ActionStatus BaseAction::getStatus() const {
    return status;
}

std::string  BaseAction::actionStatusToString() const{
    //ActionStatus status = 
    switch (getStatus()) {
        case ActionStatus::COMPLETED:
            return "COMPLETED";
        case ActionStatus::ERROR:
            return "ERROR";
        default:
            return "UNKNOWN"; // In case of an invalid status
    }
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
    else
    {
        SelectionPolicy* policy = nullptr;
             if (selectionPolicy == "nve") {
                policy = new NaiveSelection();}
            else if (selectionPolicy == "eco") {
                policy = new EconomySelection();
            }else if (selectionPolicy == "env") {
                policy = new SustainabilitySelection();
            } else if (selectionPolicy == "bal") {
                policy = new BalancedSelection(0,0,0);
            } else {
               error("Error: Unknown selection policy type: " + selectionPolicy);
            }

        simulation.addPlan(simulation.getSettlement(settlementName),policy); 
        complete();
    }
}

const std::string AddPlan::toString() const
{
    return (settlementName +" " + selectionPolicy + "|" + actionStatusToString());
}

AddPlan* AddPlan::clone () const{
    return new  AddPlan(*this);
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
    if(simulation.isFacilityexists(facilityName))
    {
        error("this facility name already exists");
    }
    else
    {
        FacilityType newfac(facilityName,facilityCategory,price,lifeQualityScore,economyScore,environmentScore);//name,category,price
        simulation.addFacility(newfac);//the last thing i was wondering if creating of the objects should be in action or simulation - it seems it should be in action so edit act of addplan() and maybe delete getselectionpolicy
        complete();
    }
}


const const std::string AddFacility::toString() const
{
    //we can move this 
    string cat;
    switch (facilityCategory) {
        case FacilityCategory::LIFE_QUALITY:
            cat= "LIFE_QUALITY";
        case FacilityCategory::ECONOMY:
            cat= "ECONOMY";
        case FacilityCategory::ENVIRONMENT:
            cat= "ENVIRONMENT";
        default:
            cat= "UNKNOWN";
    }
    //

    ostringstream oss;
    oss << "Facility Name: " << facilityName
        << ", Category: " << cat
        << ", Price: " << price
        << ", Life Quality Score: " << lifeQualityScore
        << ", Economy Score: " << economyScore
        << ", Environment Score: " << environmentScore
        << " | "<< actionStatusToString();
    return oss.str();
}

AddFacility* AddFacility::clone () const{
    return new  AddFacility(*this);
}


//------------ADDSettlement--------------

AddSettlement::AddSettlement(const string &settlementName,SettlementType settlementType)
:settlementName(settlementName),settlementType(settlementType)
{

}

void AddSettlement::act(Simulation &simulation)
{
    if(simulation.isSettlementExists(settlementName))
    {
        error("this settlement already exists");
    }
    else{
        Settlement newset(settlementName,settlementType);
        complete();
    }
}

const const std::string AddSettlement::toString() const
{
string typeStr;
    switch (settlementType)
    {
    case SettlementType::VILLAGE:
        typeStr = "Village";
        break;
    case SettlementType::CITY:
        typeStr = "City";
        break;
    case SettlementType::METROPOLIS:
        typeStr = "Metropolis";
        break;
    }

    return (settlementName + " "+typeStr +"|" + actionStatusToString());
}

AddSettlement* AddSettlement::clone () const{
    return new  AddSettlement(*this);
}


//---------PPRINTPLANSTATUS--------

PrintPlanStatus::PrintPlanStatus(int planid):planId(planId)
{

}

void PrintPlanStatus::act(Simulation &simulation)
{
    if(simulation.isplanexists(planId)==false)
    {
        error("this planID doesnt exist");
    }
    else{
         std::cout << simulation.getPlan(planId).toString();
        complete();
    }
}


const const std::string PrintPlanStatus::toString() const
{
    return (planId + "|" + actionStatusToString());
}

PrintPlanStatus* PrintPlanStatus::clone () const{
    return new  PrintPlanStatus(*this);
}



//----------CHANGEPLANPOLICY-------------

ChangePlanPolicy::ChangePlanPolicy(const int planId, const string &newPolicy):planId(planId),newPolicy(newPolicy)
{

}

void ChangePlanPolicy::act(Simulation &simulation)
{
    if(simulation.isplanexists(planId)==false)
    {
        error("this planID doesnt exist");
    }
    else if(!std::unordered_set<std::string>{"nve", "bal", "eco","env"}.count(newPolicy)){
        error("the policy provided does not exist");
    }
    else
    {
        Plan& plantochange= simulation.getPlan(planId);
             if (newPolicy == "nve") {
                plantochange.setSelectionPolicy(new NaiveSelection());
             }
            else if (newPolicy == "eco") {
                        plantochange.setSelectionPolicy(new EconomySelection());

            }else if (newPolicy == "env") {
                 plantochange.setSelectionPolicy(new SustainabilitySelection());
            } else if (newPolicy == "bal") {
                plantochange.setSelectionPolicy(new BalancedSelection(0,0,0));
            }


        complete();
    }
}

const std::string ChangePlanPolicy::toString() const
{
    return (planId + " " + newPolicy+ "|" + actionStatusToString());
}

ChangePlanPolicy* ChangePlanPolicy::clone () const{
    return new  ChangePlanPolicy(*this);
}

//--------------PRINTACTIONSLOG-------------
PrintActionsLog::PrintActionsLog(){}

void PrintActionsLog::act(Simulation &simulation)
{
    for (auto* action : simulation.getactionsLog()) {
        std::cout << action->usercommand + " " + actionStatusToString(); // thats why all the to strings here have status added
    }
}

const void BaseAction::setusercommand(string & usertyped){
    usercommand = usertyped;
}

const std::string BaseAction::toString() const
{}



PrintActionsLog* PrintActionsLog::clone () const{
    return new  PrintActionsLog(*this);
}

//-----------CLOSE--------

Close::Close(){}

void Close::act(Simulation &simulation)
{
    for(int i=0;simulation.isplanexists(i),i++;)//this assumes they start from 0 
    {
            std::cout << simulation.getPlan(i).toString();
    }
    simulation.close();
    complete();
}

const string Close::toString() const{}

Close* Close::clone () const{
    return new  Close(*this);
}


//-------------BACKUPSIMULATION--------------

BackupSimulation::BackupSimulation(){}

void BackupSimulation::act(Simulation &simulation)
{
    *backup = simulation;
    complete();
}

const string BackupSimulation::toString() const{

}


BackupSimulation* BackupSimulation::clone () const{
    return new  BackupSimulation(*this);
}
//--------------RESTORE---------------------

RestoreSimulation::RestoreSimulation(){}

void RestoreSimulation::act(Simulation &simulation)
{
    if(backup == nullptr)
    {
        error("No backup available");
    }
    else
    {
        simulation = *backup;
        complete();
    }
}

RestoreSimulation* RestoreSimulation::clone () const{
    return new  RestoreSimulation(*this);
}

const string RestoreSimulation::toString() const{

}

//-------------------STEP-------------------
SimulateStep::SimulateStep(const int numOfSteps):numOfSteps(numOfSteps)
{}

void SimulateStep::act(Simulation &simulation){
    for(int i=0; i<numOfSteps;i++)
    {
        simulation.step();
    }
    complete();
}


SimulateStep* SimulateStep::clone () const{
    return new  SimulateStep(*this);
}

const string SimulateStep::toString() const{
    
}

//----------------------


