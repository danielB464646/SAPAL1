#include "Action.h"
#include <algorithm> 
#include <stdexcept>

//------------ADDFACILITY-----------
AddFacility::AddFacility(const string &facilityName, const FacilityCategory facilityCategory, 
const int price, const int lifeQualityScore, const int economyScore, const int environmentScore)