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
/* These functions in public classes (Though the function may not be public. All private functions have a comment above the function definition.)
   These functions currently throw std::invalid_argument and std::out_of_range which can both be caught by catching std::logic_error */
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

void IdleSave::SettingsClass::setBallFactShowing(int fact) {
    /* Check for ignoreRestrictions flag */
    if(parent.ignoreRestrictions) {ballFactShowing = fact;}
    if(fact < 0) {throw std::invalid_argument("Fact must be greater or equal to 0");}
    if(fact > 1000 /* TO DO: Figure out how many ball facts there actually are, 1000 is a placeholder */) {
        throw std::invalid_argument("Fact must be less than or equal to 1000 (1000 is a placeholder value)");
    }
    ballFactShowing = fact;
}

/* throwIfOutOfRange() throws an error if the col or row is out of bounds OR if they are trying to access the fifth row without -i (the fifth row is unused in the real game) */
void IdleSave::SkillsClass::throwIfOutOfRange(int col, int row) {
    /* These two if statements run regardless of parent.ignoreRestrictions because we don't want to access outside the array. */
    if(col < 0 || col > 5) {throw std::out_of_range("That column doesn't exist! (Must between 0 and 5)");}
    if(row < 0 || row > 4) {throw std::out_of_range("That row doesn't exist! (Must between 0 and 4)");}
    if(!parent.ignoreRestrictions && row == 4) {throw std::invalid_argument("You aren't allowed to access row. Pass --ignore-restrictions to write to this row.");}
}
/* setSkillAtPos() is private */
void IdleSave::SkillsClass::setSkillAtPos(int col, int row, bool boolVal) {
    throwIfOutOfRange(col, row);
    if(!parent.ignoreRestrictions && col == 2 && row == 0 && !boolVal) {
        throw std::invalid_argument("You can't set the first sniper ball value to false. Pass --ignore-restrictions to do so.");
    }
    skillArray[col][row] = boolVal;
}
void IdleSave::SkillsClass::setColFalse(int col) {
    /* I copied and pasted (and slightly modified) the next 2 lines from IdleSave::SkillsClass::throwIfOutOfRange() */
    /* This if statement runs regardless of parent.ignoreRestrictions because we don't want to write to outside the array. */
    if(col < 0 || col > 5) {throw std::out_of_range("That column doesn't exist! (Must between 0 and 5)");}
    int startValue;
    if(!parent.ignoreRestrictions && col == 2) {startValue = 1;} /* This ensures the first value in the Sniper Ball row isn't set to false when restrictions are enforced.*/
    else {startValue = 0;}
    for(int i = startValue; i < 5; ++i) {
        setSkillAtPos(col, i, false);
    }
}
void IdleSave::SkillsClass::setPosTrueRestricted(int col, int row) {
    /* This function is "Restricted" in the sense that it sets every value up to and including [col][row] to true. It clears the row to false before setting true.
    This function will try to set the value at [col][row] to true, then each value before it: [col][row-1], [col][row-2], etc. finishing at row == 0
    It lets setSkillAtPos() throw the exceptions */
    setColFalse(col);
    for(int irow = row; irow >= 0; --irow) {
        setSkillAtPos(col, irow, true);
    }
}
void IdleSave::SkillsClass::setPosUnrestricted(int col, int row, bool boolVal) {
    /* If restrictions are ignored then it will allow setSkillAtPos() to be called, allowing them to change any value in the array. */
    if(!parent.ignoreRestrictions) {
        throw std::logic_error("This error shouldn't be printing. setPosUnrestricted() should only be called if parent.ignoreRestrictions is true.");
    }
    setSkillAtPos(col, row, boolVal);
}
int IdleSave::SkillsClass::getPos(int col, int row) {
    throwIfOutOfRange(col, row);
    return skillArray[col][row];
}

void IdleSave::PowerupsClass::setPowerupsRemaining(int pwrUp) {
    if(!parent.ignoreRestrictions && (pwrUp > 5 || pwrUp < 0)) {
        throw std::invalid_argument("PowerupsRemaining must be between 0 and 5 (inclusive). Try passing --ignore-instructions.");
    }
    powerupsRemaining = pwrUp;
}
