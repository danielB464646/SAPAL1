#include "Simulation.h"
#include "SelectionPolicy.h"
#include "Auxiliary.h"
#include <fstream>
#include <iostream>
#include "Action.h"


// Constructor
Simulation::Simulation(const string &configFilePath)
    : isRunning(false), planCounter(0), actionsLog(), plans(), settlements(), facilitiesOptions()
{
    std::ifstream configFile(configFilePath); // Open the configuration file
    if (!configFile.is_open()) {
        throw std::runtime_error("Error: Unable to open config file: " + configFilePath);
    }

    std::string line;
    while (std::getline(configFile, line)) {
        // Ignore comments and empty lines
        if (line.empty() || line[0] == '#') {
            continue;
        }

        // Parse the line into arguments
        std::vector<std::string> arguments = Auxiliary::parseArguments(line);

        if (arguments.empty()) {
            continue; // Skip invalid lines
        }   

        // Determine the type of entity to create
        if (arguments[0] == "settlement" && arguments.size() == 3) {
            // Create a Settlement
            std::string settlementName = arguments[1];
            int settlementType = std::stoi(arguments[2]); // Convert string to int
            settlements.emplace_back(settlementName, static_cast<SettlementType>(settlementType)); // Constructed directly in place with enum paassed
        }
        else if (arguments[0] == "facility" && arguments.size() == 7) {
            // Create a Facility
            std::string facilityName = arguments[1];
            int category = std::stoi(arguments[2]);
            int price = std::stoi(arguments[3]);
            int lifeQualityImpact = std::stoi(arguments[4]);
            int economyImpact = std::stoi(arguments[5]);
            int environmentImpact = std::stoi(arguments[6]);

            facilitiesOptions.emplace_back(facilityName, category,price, lifeQualityImpact, economyImpact, environmentImpact);
        }
        else if (arguments[0] == "plan" && arguments.size() == 3) {
            // Create a Plan
            std::string settlementName = arguments[1];
            std::string policyType = arguments[2];


            SelectionPolicy* policy = nullptr;
             if (policyType == "nve") {
                policy = new NaiveSelection();}
            else if (policyType == "eco") {
                policy = new EconomySelection();
            }else if (policyType == "env") {
                policy = new SustainabilitySelection();
            } else if (policyType == "bal") {
                policy = new BalancedSelection(0,0,0);
            } else {
                throw std::runtime_error("Error: Unknown selection policy type: " + policyType);
            }
        

            plans.emplace_back(getSettlement(settlementName), policy);//no error checking here
            ++planCounter; // Increment the plan counter
        }
        else {
            throw std::runtime_error("Error: Invalid line in config file: " + line);
        }
    }

    configFile.close(); // Close the file
}

void Simulation::start (){
    open();
    std::cout << "simulation start" << std::endl;
    std::string input;
    BaseAction* action = nullptr;
    
    while(isRunning)
    {
        std::cout << "Enter your command ";
        std::cin >> input;
        
        if (action != nullptr) {
            delete action; // Free memory
        }
        action = nullptr;
        //parse command & deal with each kind of action and send arguments to different Action funcs
        std::vector<std::string> arguments = Auxiliary::parseArguments(input);
        if (arguments[0] == "step")
            {SimulateStep(std::stoi(arguments[1]));
            }
        else if (arguments[0] == "plan")
        {
            action = new AddPlan (arguments[1],arguments[2]);
        }
        else if (arguments[0] == "settlement")
        {
            action = new AddSettlement(arguments[1],static_cast<SettlementType>(std::stoi(arguments[2])));//convert to int and then to enum
        }
        else if (arguments[0] == "facility")
        {
            action = new AddFacility(arguments[1],static_cast<FacilityCategory>(std::stoi(arguments[2])),std::stoi(arguments[3]),std::stoi(arguments[4]),std::stoi(arguments[5]),std::stoi(arguments[6]));
        }
        else if (arguments[0] == " planStatus")
        {
            action = new PrintPlanStatus(std::stoi(arguments[1]));
        }
        else if (arguments[0] == "  changePolicy")//CONTINUE HERE WITH CHANGE PLANPOLICY
        {
            action = new ChangePlanPolicy(std::stoi(arguments[1]),arguments[2]);
        }
        else if(arguments[0]=="log")
        {
            action = new PrintActionsLog();
        }
        else if(arguments[0]=="backup")
        {
            action = new BackupSimulation();
        }
         else if(arguments[0]=="restore")
        {
            action = new RestoreSimulation();
        }
        else if(arguments[0]=="close")
        {
             action = new Close();//this calls close in actioin which calls close in this class which sets isrunning to false
        }

        if (action != nullptr) {
            action->act(*this); // Execute the action
            if(action->getStatus() == ActionStatus::COMPLETED)
            {
                std::cout << "command completed successfully";
            }
            else
            {
                std::cout << "command failed here is the message: "+action->realerrormessage();
            }

            actionsLog.push_back(action->clone());//create a copy because the action is deleted after another way would simply be not to copy and not to delete

        }
    
    }
      // At the end, delete the last allocated action (if any)
    if (action != nullptr) {
        delete action;}
}



void Simulation::addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy){
    Plan newplan(planCounter,settlement,selectionPolicy,facilitiesOptions);
    plans.push_back(newplan);
    ++planCounter;
}

void Simulation::addAction(BaseAction *action){

}
        
bool Simulation::addSettlement(Settlement *settlement){
    settlements.push_back(settlement);
    return true;
}
        
bool Simulation::addFacility(FacilityType facility){
    facilitiesOptions.push_back(facility);
    return true;
}

bool Simulation::isSettlementExists(const string &settlementName){

}

bool Simulation::isFacilityexists(const string &facilityname)
{

}
        
Settlement& Simulation::getSettlement(const string &settlementName){

}

bool Simulation::isplanexists(const int planID )
{

}
        
Plan & Simulation::getPlan(const int planID){

}

void Simulation::step()
    {
        //create action of type simulate step Simialstepact
        //call Simialstepact->act(this)
        //this action never results in an error

    }
void Simulation::close()
    {
        //print all plans with their scores
        isRunning = false;

}

void Simulation::open()
{
    isRunning = true;
}

vector<BaseAction*>& Simulation::getactionsLog()
{
    return actionsLog;
}