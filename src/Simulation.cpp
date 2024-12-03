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
            settlements.emplace_back(settlementName, settlementType); // Constructed directly in place with enum paassed
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

            SelectionPolicy *policy = nullptr;
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

            Settlement &settlement = getSettlement(settlementName); // Find the settlement by name
            /*
            
            here we need to find out what is the correct way to set policy of plan that exists 
            if no such plan - print error
            if the plan exists you should use setselectiopolicy() in plan.cpp

            last discovered - in the config file the settlements and plans are to concrete build those 
            and facilities you concrete build too but they act as models which you clone to put into a facility/plan
             */



            plans.emplace_back(settlement, policy);
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
    //std::cout << "Enter your command ";
    BaseAction* action = nullptr;
    std::cin >> input;
    while(input!="close")
    {
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
        else if ()//CONTINUE HERE WITH CHANGE PLANPOLICY



        if (action != nullptr) {
            action->act(*this); // Execute the action
        }
        //std::cout << "Enter your command ";
        std::cin >> input;
    }

      // At the end, delete the last allocated action (if any)
    if (action != nullptr) {
        delete action;}
    close();
}

void Simulation::addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy){
    Plan newplan(planCounter,settlement,selectionPolicy,facilitiesOptions);
    ++planCounter;

}

void Simulation::addAction(BaseAction *action){

}
        
bool Simulation::addSettlement(Settlement *settlement){

}
        
bool Simulation::addFacility(FacilityType facility){

}

bool Simulation::isSettlementExists(const string &settlementName){

}
        
Settlement& Simulation::getSettlement(const string &settlementName){

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