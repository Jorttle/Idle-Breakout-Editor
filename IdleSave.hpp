#pragma once
#include <array>
#include <stdexcept>
#include <string>
#include <cstdint>
#include <boost/multiprecision/cpp_int.hpp>
using bigInt = boost::multiprecision::cpp_int;

class IdleSave {
    private:
        /* Flag arguments */
        bool ignoreRestrictions;

        /* Idle Breakout Export Values */
        bigInt level;
        bigInt money;
        bigInt gold;
        bigInt claimGold;
        /* int timesPrestiged; */
        bigInt bricksBrokenThisRun;
        bigInt bricksBrokenAllTime;
        bigInt blackBricksBroken;
        /* int powerupsRemaining; */
        int totalClicks; // Unknown
        /*int ballFactShowing; // What ball fact is currently showing
        bool ballFactsOn;
        bool bonusAlert;
        bool effectsOn; */
        int startTimestamp; // Unknown
        int timeToReach100; // Unknown
        /*int value17; // Basic.damageDone
        int value18; // Basic.damageDone
        int value19; // Plasma.damageDone
        int value20; // Plasma.damageDone
        int value21; // Sniper.damageDone
        int value22; // Sniper.damageDone
        int value23; // Scatter.damageDone
        int value24; // Scatter.damageDone
        int value25; // Cannon.damageDone
        int value26; // Cannon.damageDone
        int value27; // Poison.damageDone
        int value28; // Poison.damageDone */
        /*int value29; // Basic.amount
        int value30; // Plasma.amount
        int value31; // Sniper.amount
        int value32; // Scatter.amount
        int value33; // Cannon.amount
        int value34; // Poison.amount
        int value35; // Snow.amount - Works but Unused
        int value36; // Money.amount - Works but unused */
        int unknownUnused;
        /*int value38; // Basic.speed
        int value39; // Basic.power
        int value40; // Plasma.speed
        int value41; // Plasma.power
        int value42; // Sniper.speed
        int value43; // Sniper.power
        int value44; // Scatter.speed
        int value45; // Scatter.power
        int value46; // Cannon.speed
        int value47; // Cannon.power
        int value48; // Poison.speed
        int value49; // Poison.power */
        int laserFireRate; // Unknown if used
        int laserPower;
        int clickPower;
        /* int levelCashBonus;
        int ballSpeedIncrease;
        int ballPowerMultiplier;
        int laserAmount;
        int maxBallAmount; */
        /*bool value58; // Basic.milDamage
        bool value59; // Plasma.milDamage
        bool value60; // Sniper.milDamage
        bool value61; // Scatter.milDamage
        bool value62; // Cannon.milDamage
        bool value63; // Poison.milDamage */
        /* bool allPowerupsUsed; // Powerups */
        /* bool prestiged5Times;  */
        bool have10EachBall;
        bool break1000BlackBricks;
        bool reachLevel250;
        bool allLasersUnlocked;
        /* bool hasUsedDoubleMoney; // Powerups
        bool hasUsedClickFrenzy; // Powerups
        bool hasUsedDemonCore; // Powerups
        bool hasUsedSnowBall; // Powerups
        bool hasUsedDoubleGold; // Powerups */
        /*int value75; // Skill Points
        int value76; // Skill Points
        int value77; // Skill Points
        int value78; // Skill Points
        int value79; // Skill Points
        int value80; // Skill Points
        int value81; // Skill Points
        int value82; // Skill Points
        int value83; // Skill Points
        int value84; // Skill Points
        int value85; // Skill Points
        int value86; // Skill Points
        int value87; // Skill Points
        int value88; // Skill Points
        int value89; // Skill Points
        int value90; // Skill Points
        int value91; // Skill Points
        int value92; // Skill Points
        int value93; // Skill Points
        int value94; // Skill Points
        int value95; // Skill Points
        int value96; // Skill Points
        int value97; // Skill Points
        int value98; // Skill Points
        int value99; // Skill Points
        int value100; // Skill Points
        int value101; // Skill Points
        int value102; // Skill Points
        int value103; // Skill Points
        int value104; // Skill Points */
        int blackBrickWallet;
        /* int cursorColor;
        int backgroundColor; */
        int bossNumber; // Difference between these are unknown
        int bossLevel; // Difference between these are unknown
        int skillPoints;
        /* bool soundOn;
        int soundEffects; // Unknown
        bool autoFightBoss; */
        
        std::string buildImport(); // Exports un-encoded string
        std::string returnWarnings(); // Returns warnings for things that don't make sense (e.g. all powerups are used but "Used all powerups" Achievement is false)

    public:
        class Ball {
            private:
                int amount = 0;
            protected:
                /* Reference to parent class */
                IdleSave& parent;
            public:
                Ball(IdleSave& parent) : parent(parent) {}
                int getAmount() const {return amount;}
                void setAmount(int amnt);
        };
        class StandardBall : public Ball {
            private:
                /* Variable names that have "speed" are only sometimes speed.
                Plasma it is "range", and Scatter it is "extra balls". This is reflected in statOneName */
                int damageDone = 0;
                int speed = 0;
                int power = 0;
                bool milDamage = false;
                // The speed and power that go into the export string aren't the true speed and power, so we need variables for each.
                // trueSpeed = (speedMult * speed) + speedAdd
                const std::uint8_t speedMult;
                const std::uint8_t speedAdd;
                int trueSpeed;
                const std::uint8_t maxSpeedUpgrades;
                // Similar with power except you can keep upgrading power indefinitly.
                const std::uint8_t powerMult;
                const std::uint8_t powerAdd;
                int truePower;
                const std::string statOneName;
                /* Ball(parent),
                    speedMult(speedMult),
                    speedAdd(speedAdd),
                    maxSpeedUpgrades(maxSpeedUpgrades),
                    trueSpeed(speedAdd),
                    powerMult(powerMult),
                    powerAdd(powerAdd),
                    truePower(powerAdd),
                    statOneName(statOneName) */
            public:
                StandardBall(
                    IdleSave& parent,
                    std::uint8_t speedMult,
                    std::uint8_t speedAdd,
                    std::uint8_t maxSpeedUpgrades,
                    std::uint8_t powerMult,
                    std::uint8_t powerAdd,
                    std::string statOneName) :
                    Ball(parent),
                    speedMult(speedMult),
                    speedAdd(speedAdd),
                    trueSpeed(speedAdd),
                    maxSpeedUpgrades(maxSpeedUpgrades),
                    powerMult(powerMult),
                    powerAdd(powerAdd),
                    truePower(powerAdd),
                    statOneName(statOneName) {}
                // Getters and Setters
                int getDamageDone() const {return damageDone;}
                void setDamageDone(int dmg);
                int getSpeed() const {return speed;}
                void setSpeed(int sped);
                int getPower() const {return power;}
                void setPower(int pwr);
                bool getMilDamage() const {return milDamage;}
                void setMilDamage(bool mlDmg) {milDamage = mlDmg;}
                // These get and set the "True" values, or the values that show up in-game.
                int getTrueSpeed() const {return trueSpeed;}
                void setTrueSpeed(int sped);
                int getTruePower() const {return truePower;}
                void setTruePower(int pwr);
        };
        class SettingsClass {
            public: /* Must define these enums as public before the private enum variables can be declared */
                /* Enum Classes for background color and cursor color*/
                enum class CursorColorEnum {
                    Normal,
                    Red,
                    Green,
                    LightBlue,
                    Black
                };
                enum class BackgroundColorEnum {
                    Normal,
                    LightPink,
                    LightGreen,
                    LightBlue,
                    LightPurple
                };
            private:
                /* Reference to parent class */
                IdleSave& parent;
                int ballFactShowing; // What ball fact is currently showing
                CursorColorEnum cursorColor;
                BackgroundColorEnum backgroundColor;
            public:
                SettingsClass(IdleSave& parent) : parent(parent) {}
                // Getters and Setters
                int getBallFactShowing() const {return ballFactShowing;}
                void setBallFactShowing(int fact);
                CursorColorEnum getCursorColor() {return cursorColor;}
                void setCursorColor(CursorColorEnum color);
                bool ballFactsOn;
                bool bonusAlert;
                bool effectsOn;
                bool soundOn;
                // int soundEffects; // Unknown
                bool autoFightBoss;
                
                                                
        };
        class SkillsClass {
            private:
                /* Reference to parent */
                IdleSave& parent;
                std::array<std::array<int, 5>, 6> skillArray = {{
                    {false, false, false, false, false}, /* Column 0 */ /* Yes, they are secretly rows, but they are columns in-game */
                    {false, false, false, false, false}, /* Column 1 */
                    {true, false, false, false, false}, /* Column 2 - Only column that has the first value defaulted as true */
                    {false, false, false, false, false}, /* Column 3 */
                    {false, false, false, false, false}, /* Column 4 */
                    {false, false, false, false, false} /* Column 5 */
                }};
                void throwIfOutOfRange(int col, int row);
                void setSkillAtPos(int col, int row, bool boolVal);
            public:
                SkillsClass(IdleSave& parent) : parent(parent) {}
                void setColFalse(int col);
                void setPosTrueRestricted(int col, int row);
                void setPosUnrestricted(int col, int row, bool boolVal);
                int getPos(int col, int row);
                std::array<std::array<int, 5>, 6> getFullArray() const {return skillArray;}

        };
        class PowerupsClass {
            private:
                IdleSave& parent;
                int powerupsRemaining; /* Should be between 0 and 5 */
            public:
                PowerupsClass(IdleSave& parent) : parent(parent) {}
                bool allPowerupsUsed;

                bool hasUsedDoubleMoney;
                bool hasUsedClickFrenzy;
                bool hasUsedDemonCore;
                bool hasUsedSnowBall;
                bool hasUsedDoubleGold;
                int getPowerupsRemaining() const {return powerupsRemaining;}
                void setPowerupsRemaining(int pwrUp);
        };
        class PrestigeClass {
            private:
                IdleSave& parent;

                int levelCashBonus;
                int ballSpeedIncrease;
                int ballPowerMultiplier;
                int laserAmount;
                int maxBallAmount;
                /* These are the "true" values that you would see in-game. For example, trueLevelCashBonus starts at 0, then goes to 50, 100, 200, 400, etc. */
                int trueLevelCashBonus;
                int trueBallSpeedIncrease;
                bigInt trueBallPowerMultiplier; /* The "true" value gets very big very fast, so it needs bigInt */
                /* trueLaserAmount would just be the same as laserAmount */
                int trueMaxBallAmount; 

                int timesPrestiged;
            public:
                PrestigeClass(IdleSave& parent) : parent(parent) {}
                bool prestiged5Times;
                int getLevelCashBonus() const {return levelCashBonus;}
                void setLevelCashBonus(int cash);
                int getBallSpeedIncrease() const {return ballSpeedIncrease;}
                void setBallSpeedIncrease(int sped);
                int getBallPowerMultiplier() const {return ballPowerMultiplier;}
                void setBallPowerMultiplier(int pwr);
                int getLaserAmount() const {return laserAmount;}
                void setLaserAmount(int lsr);
                int getMaxBallAmount() const {return maxBallAmount;}
                void setMaxBallAmount(int max);
                /* True getters and setters */
                int getTrueLevelCashBonus() const {return trueLevelCashBonus;}
                void setTrueLevelCashBonus(int cash);
                int getTrueBallSpeedIncrease() const {return trueBallSpeedIncrease;}
                void setTrueBallSpeedIncrease(int sped);
                /* One getter and setter omitted */
                bigInt getTrueBallPowerMultiplier() const {return trueBallPowerMultiplier;}
                void setTrueBallPowerMultiplier(bigInt pwr);
                int getTrueMaxBallAmount() const {return trueMaxBallAmount;}
                void setTrueMaxBallAmount(int max);

                int getTimesPrestiged() const {return timesPrestiged;}
                void setTimesPrestiged(int times);
        };
        IdleSave(std::string exportCode, bool ignoreRestrictions = false) : ignoreRestrictions(ignoreRestrictions) {exportCode = "This is a temporary message";}
        IdleSave(const IdleSave&) = delete;
        StandardBall BasicBall = StandardBall(*this, 1, 1, 9, 1, 1, "speed");
        StandardBall PlasmaBall = StandardBall(*this, 1, 1, 6, 3, 3, "range");
        StandardBall SniperBall = StandardBall(*this, 1, 4, 6, 5, 5, "speed");
        StandardBall ScatterBall = StandardBall(*this, 1, 2, 8, 10, 10, "extra balls");
        StandardBall CannonBall = StandardBall(*this, 2, 4, 6, 25, 50, "speed");
        StandardBall PoisonBall = StandardBall(*this, 2, 5, 5, 5, 5, "speed");
        Ball SnowBall = Ball(*this);
        Ball MoneyBall = Ball(*this);
        SettingsClass Settings = SettingsClass(*this);
        SkillsClass Skills = SkillsClass(*this);
        PowerupsClass Powerups = PowerupsClass(*this);
        PrestigeClass Prestige = PrestigeClass(*this);
};
