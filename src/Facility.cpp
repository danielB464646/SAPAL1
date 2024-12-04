#include "Facility.h"

// FacilityType constructor
FacilityType::FacilityType(const string &nameVal, const FacilityCategory categoryVal, const int priceVal, 
                           const int lifeQuality_scoreVal, const int economy_scoreVal, const int environment_scoreVal)
    : name(nameVal), category(categoryVal), price(priceVal), 
      lifeQuality_score(lifeQuality_scoreVal), economy_score(economy_scoreVal), environment_score(environment_scoreVal) {}

// FacilityType getters
const string &FacilityType::getName() const {
    return name;
}

int FacilityType::getCost() const {
    return price;
}

int FacilityType::getLifeQualityScore() const {
    return lifeQuality_score;
}

int FacilityType::getEnvironmentScore() const {
    return environment_score;
}

int FacilityType::getEconomyScore() const {
    return economy_score;
}

FacilityCategory FacilityType::getCategory() const {
    return category;
}




// Facility constructor using all fields
Facility::Facility(const string &nameRef, const string &settlementNameRef, const FacilityCategory categoryEnum, 
                   const int priceVal, const int lifeQuality_scoreVal, const int economy_scoreVal, const int environment_scoreVal)
    : FacilityType(nameRef, categoryEnum, priceVal, lifeQuality_scoreVal, economy_scoreVal, environment_scoreVal), 
      settlementName(settlementNameRef), status(FacilityStatus::UNDER_CONSTRUCTIONS), timeLeft(priceVal) {}



// Facility constructor using FacilityType
Facility::Facility(const FacilityType &type, const string &settlementName)
    : FacilityType(type), settlementName(settlementName), status(FacilityStatus::UNDER_CONSTRUCTIONS), timeLeft(price) {}
    //the FacilityType(type) will build all FacilityType parameters accordingly cos Facility is an extention of it



// Facility getters
const string &Facility::getSettlementName() const {
    return settlementName;
}

const int Facility::getTimeLeft() const {
    return timeLeft;
}

// Facility step function: decrement timeLeft and update status
FacilityStatus Facility::step() {
    if (timeLeft > 0) {
        --timeLeft;
        if (timeLeft == 0) {
            setStatus(FacilityStatus::OPERATIONAL);
        }
    }
    return status;
}

// Facility status setters and getters
void Facility::setStatus(FacilityStatus status) {
    this->status = status;
}

const FacilityStatus& Facility::getStatus() const {
    return status;
}

// Facility toString implementation
const string Facility::toString() const {
    return "Facility: " + getName() + " in " + settlementName + 
           " (Status: " + (status == FacilityStatus::UNDER_CONSTRUCTIONS ? "Under Construction" : "Operational") + ")";
}
