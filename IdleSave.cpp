#include "IdleSave.hpp"
#include <stdexcept>
#include <cmath>
#include <cctype>

// Not in IdleSave.hpp
std::string firstCharUp(std::string str) {
    if(!str.empty()) {str[0] = std::toupper(str[0]);}
    return str;
}
bool isPowerOfTwo(const bigInt& num) {
    /* if num is a power of two, then something like this will happen:
    100000 = num
    011111 = num - 1
    & is the AND bitwise operator, so the result will be:
    000000 = 0
    if and only if the number is a power of two. */
    if(num > 0 && (num & (num - 1)) == 0) {return true;}
    return false;
    /*-------------^^^^^^^^^^^^^^^^^^^^^---------------- This is the part the comment above is refering to */
}
bigInt exponentOf2Above(const bigInt& num) { /* Returns the power of two directly above num */
    return bigInt(1) << (boost::multiprecision::msb(num) + 1);
}
bigInt exponentOf2Below(const bigInt& num) { /* Returns the power of two directly below num */
    return bigInt(1) << boost::multiprecision::msb(num);
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
    if(parent.ignoreRestrictions) {
        trueSpeed = sped;
        speed = (sped - speedAdd) / speedMult;
        return;
    }
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
    if(parent.ignoreRestrictions) {
        truePower = pwr;
        power = (pwr - powerAdd) / powerMult;
        return;
    }
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
    if(parent.ignoreRestrictions) {ballFactShowing = fact; return;}
    if(fact < 0) {throw std::invalid_argument("Fact must be greater or equal to 0");}
    if(fact > 1000 /* TO DO: Figure out how many ball facts there actually are, 1000 is a placeholder */) {
        throw std::invalid_argument("Fact must be less than or equal to 1000 (1000 is a placeholder value)");
    }
    ballFactShowing = fact;
}
void IdleSave::SettingsClass::setCursorColor(CursorColorEnum color) {
    cursorColor = color;
}

/* throwIfOutOfRange() throws an error if the col or row is out of bounds OR if they are trying to access the fifth row without -i (the fifth row is unused in the real game) */
void IdleSave::SkillsClass::throwIfOutOfRange(int col, int row) {
    /* These two if statements run regardless of parent.ignoreRestrictions because we don't want to access outside the array. */
    if(col < 0 || col > 5) {throw std::out_of_range("That column doesn't exist! (Must be between 0 and 5 inclusive)");}
    if(row < 0 || row > 4) {throw std::out_of_range("That row doesn't exist! (Must be between 0 and 4 inclusive)");}
    if(!parent.ignoreRestrictions && row == 4) {throw std::invalid_argument("You aren't allowed to access row 4. Pass --ignore-restrictions to write to this row.");}
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
    int maxValue;
    if(parent.ignoreRestrictions) {maxValue = 5;}
    else {maxValue = 4;}
    for(int i = startValue; i < maxValue; ++i) {
        setSkillAtPos(col, i, false);
    }
}
void IdleSave::SkillsClass::setPosTrueRestricted(int col, int row) {
    /* This function is "Restricted" in the sense that it sets every value up to and including [col][row] to true. It clears the row to false before setting true.
    This function will try to set the value at [col][row] to true, then each value before it: [col][row-1], [col][row-2], etc. finishing at row == 0
    It lets setSkillAtPos() throw the exceptions */
    throwIfOutOfRange(col, row);
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
        throw std::invalid_argument("PowerupsRemaining must be between 0 and 5 (inclusive). Try passing --ignore-restrictions.");
    }
    powerupsRemaining = pwrUp;
}

void IdleSave::PrestigeClass::setLevelCashBonus(int cash) {
    if(!parent.ignoreRestrictions && (cash > 10 || cash < 0)) {throw std::invalid_argument("levelCashBonus must be in between 0 and 10 (inclusive). Pass --ignore-restrictions to bypass.");}
    levelCashBonus = cash;
    if(cash <= 0) {trueLevelCashBonus = 0;}
    else if(cash > 0) {
        /* The formula for converting from the import value to the "true" value is 25 * 2^x when x > 0 and where x is the import value
        The bitshift operator (<<) has the same effect as 25 * 2^cash. It is more efficient than std::pow() which is why I am using it. */
        trueLevelCashBonus = 25 << cash;
    }
}
void IdleSave::PrestigeClass::setBallSpeedIncrease(int sped) {
    if(!parent.ignoreRestrictions && (sped > 9 || sped < 0)) {throw std::invalid_argument("ballIncreaseSpeed must be in between 0 and 9 (inclusive). Pass --ignore-restrictions to bypass.");}
    ballSpeedIncrease = sped;
    trueBallSpeedIncrease = sped + 1;
}
void IdleSave::PrestigeClass::setBallPowerMultiplier(int pwr) {
    if(!parent.ignoreRestrictions && pwr < 0) {throw std::invalid_argument("ballPowerMultiplier must be at least 0. Pass --ignore-restrictions to bypass.");}
    ballPowerMultiplier = pwr;
    trueBallPowerMultiplier = bigInt(1) << pwr;
}
void IdleSave::PrestigeClass::setLaserAmount(int lsr) {
    if(!parent.ignoreRestrictions && (lsr < 0 || lsr > 3)) {throw std::invalid_argument("laserAmount must be in between 0 and 3 (inclusive). Pass --ignore-restrictions to bypass.");}
    laserAmount = lsr;
}
void IdleSave::PrestigeClass::setMaxBallAmount(int max) {
    if(!parent.ignoreRestrictions && (max < 0 || max > 95)) {throw std::invalid_argument("maxBallAmount must be in between 0 and 95 (inclusive). Pass --ignore-restrictions to bypass.");}
    maxBallAmount = max;
    trueMaxBallAmount = (10 * max) + 50;
}
/* "true" setters (see IdleSave.hpp for more information) */
void IdleSave::PrestigeClass::setTrueLevelCashBonus(int cash) {
    /* Run this check regardless of parent.ignoreRestrictions */
    if(cash < 0) {throw std::invalid_argument("trueLevelCashBonus can't be negative. The closest valid integer is 0.");}
    if(cash > 0 && cash < 50) {throw std::invalid_argument("trueLevelCashBonus can't be " + std::to_string(cash) + ". The closest valid numbers are 0 and 50.");}
    if(cash == 0) {trueLevelCashBonus = 0; levelCashBonus = 0; return;}
    if(!parent.ignoreRestrictions && cash > 25600) {throw std::invalid_argument("trueLevelCashBonus can't be higher than 25600. Pass --ignore-restrictions to bypass.");}
    double potential = log2(cash / 25.0);
    if(potential - static_cast<int>(potential) != 0) { /* May need to change != 0 to allow for a small margin of error */
        std::string errStr = "trueLevelCashBonus must fit the equation 't = 25 * 2^x' where x is a whole number greater than 0 (if the number is 0 then trueLevelCashBonus is set to 0)\n";
        int lower = 25 << static_cast<int>(floor(potential));
        int upper = 25 << static_cast<int>(ceil(potential));
        errStr += "The closest valid integers are " + std::to_string(lower) + " and " + std::to_string(upper) + ".";
        throw std::invalid_argument(errStr);
    }
    trueLevelCashBonus = cash;
    levelCashBonus = static_cast<int>(potential);

}
void IdleSave::PrestigeClass::setTrueBallSpeedIncrease(int sped) {
    if(!parent.ignoreRestrictions && (sped < 1 || sped > 10)) {throw std::invalid_argument("trueBallSpeedIncrease must be in between 1 and 10 (inclusive).");}
    trueBallSpeedIncrease = sped;
    ballSpeedIncrease = sped - 1;
}
void IdleSave::PrestigeClass::setTrueBallPowerMultiplier(bigInt pwr) {
    if(pwr < 1) {throw std::invalid_argument("trueBallPowerMultiplier must be at least 1");}
    /* TO DO: Finish this function!!! */
    bool pwrIsValid = isPowerOfTwo(pwr);
    /* msb() is a function that returns the index of the highest set bit which will always be the exponent */
    if(!pwrIsValid) {
        std::string throwStr = boost::lexical_cast<std::string>(pwr) + " is not a power of 2. The closest valid numbers are ";
        throwStr += boost::lexical_cast<std::string>(exponentOf2Above(pwr)) + " and " + boost::lexical_cast<std::string>(exponentOf2Below(pwr));
        throw std::invalid_argument(throwStr);
    }
    trueBallPowerMultiplier = pwr;
    ballPowerMultiplier = boost::multiprecision::msb(pwr);
}
void IdleSave::PrestigeClass::setTrueMaxBallAmount(int max) {
    if(!parent.ignoreRestrictions && (max < 50 || max > 1000)) {throw std::invalid_argument("trueMaxBallAmount must be in between 50 and 1000 (inclusive). Pass --ignore-restrictions to bypass.");}
    if((max - 50) % 10 != 0) {
        int lower = 10 * floor((max - 50) / 10.0) + 50;
        int upper = 10 * ceil((max - 50) / 10.0) + 50;
        std::string errStr = std::to_string(max) + " isn't a valid true max ball amount. The nearest valid integers are " + std::to_string(lower) + " and " + std::to_string(upper) + ".";
        throw std::invalid_argument(errStr);
    }
    trueMaxBallAmount = max;
    maxBallAmount = (max - 50) / 10;
}
/* End of setter functions */
void IdleSave::PrestigeClass::setTimesPrestiged(int times) {
    if(!parent.ignoreRestrictions && times < 0) {throw std::invalid_argument("timesPrestiged must be at least 0. Pass --ignore-restrictions to bypass.");}
    timesPrestiged = times;
}
