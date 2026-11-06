#include "IdleSave.hpp"
#include <stdexcept>
#include <cmath>
#include <cctype>

// Not in IdleSave.hpp
std::string firstCharUp(std::string str) {
    if(!str.empty()) {str[0] = std::toupper(str[0]);}
    return str;
}

// Private
// TO DO: these functions
std::string IdleSave::buildImport() {return "";}
std::string IdleSave::returnWarnings() {return "";}
// Public
void IdleSave::Ball::setAmount(int amnt) {
    /* Check for ignoreRestrictions flag */
    if(parent.ignoreRestrictions) {amount = amnt; return;}
    if(amnt < 0) {throw std::invalid_argument("Amount must be at least 0");}
    amount = amnt;
}
void IdleSave::StandardBall::setDamageDone(int dmg) {
    /* Check for ignoreRestrictions flag */
    if(parent.ignoreRestrictions) {damageDone = dmg; return;}
    if(dmg < 0) {throw std::invalid_argument("Damage must be at least 0");}
    damageDone = dmg;
}
void IdleSave::StandardBall::setSpeed(int sped) {
    /* Check for ignoreRestrictions flag */
    if(parent.ignoreRestrictions) {speed = sped; return;}
    if(sped < 0) {throw std::invalid_argument(firstCharUp(statOneName) + " must be at least 0");}
    speed = sped;
    trueSpeed = (sped * speedMult) + speedAdd;
}
void IdleSave::StandardBall::setPower(int pwr) {
    /* Check for ignoreRestrictions flag */
    if(parent.ignoreRestrictions) {power = pwr; return;}
    if(pwr < 0) {throw std::invalid_argument("Power must be at least 0");}
    power = pwr;
    truePower = (pwr * powerMult) + powerAdd;
}
void IdleSave::StandardBall::setTrueSpeed(int sped) {
    /* Check for ignoreRestrictions flag */
    if(parent.ignoreRestrictions) {trueSpeed = sped; return;}
    if(sped < speedAdd) {throw std::invalid_argument("True " + statOneName + " for this ball must be at least " + std::to_string(speedAdd));}
    int trueMaxSpeed = (maxSpeedUpgrades * speedMult) + speedAdd;
    if(sped > trueMaxSpeed) {throw std::invalid_argument("True " + statOneName + " for this ball must be at most " + std::to_string(trueMaxSpeed));}
    // Checks if the speed given is possible by the equation `trueSpeed = (speedMult * speed) + speedAdd` where speed is an integer
    if((sped - speedAdd) % speedMult != 0) {
        int lowerSpeed = speedMult * floor((sped - speedAdd) / static_cast<double>(speedMult)) + speedAdd;
        int higherSpeed = speedMult * ceil((sped - speedAdd) / static_cast<double>(speedMult)) + speedAdd;

        throw std::invalid_argument("This ball can't have " + statOneName + " of " + std::to_string(sped) + ". The closest valid integers are "
            + std::to_string(lowerSpeed) + " or " + std::to_string(higherSpeed));
    }
    trueSpeed = sped;
    speed = (sped - speedAdd) / speedMult;
}
void IdleSave::StandardBall::setTruePower(int pwr) {
    /* Check for ignoreRestrictions flag */
    if(parent.ignoreRestrictions) {truePower = pwr; return;}
    if(pwr < powerAdd) {throw std::invalid_argument("True power for this ball must be at least " + std::to_string(powerAdd));}
    // Checks if the power given is possible by the equation `truePower = (powerMult * power) + powerAdd` where power is an integer
    if((pwr - powerAdd) % powerMult != 0) {
        int lowerPower = powerMult * floor((pwr - powerAdd) / static_cast<double>(powerMult)) + powerAdd;
        int higherPower = powerMult * ceil((pwr - powerAdd) / static_cast<double>(powerMult)) + powerAdd;

        throw std::invalid_argument("This ball can't have power " + std::to_string(pwr) + ". The closest valid integers are "
            + std::to_string(lowerPower) + " or " + std::to_string(higherPower));
    }
    truePower = pwr;
    power = (pwr - powerAdd) / powerMult;
}
