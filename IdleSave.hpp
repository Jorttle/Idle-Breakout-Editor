#pragma once
#include <stdexcept>
#include <string>

class IdleSave {
    private:
        int level;
        int money;
        int gold;
        int claimGold;
        int timesPrestiged;
        int bricksBrokenThisRun;
        int bricksBrokenAllTime;
        int blackBricksBroken;
        int powerupsRemaining;
        int totalClicks; // Unknown
        /*int ballFactShowing; // What ball fact is currently showing
        bool ballFactsOn;
        bool BonusAlerts;
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
        int levelCashBonus;
        int ballSpeedIncrease;
        int ballPowerMultiplier;
        int laserAmount;
        int maxBallAmount;
        /*bool value58; // Basic.milDamage
        bool value59; // Plasma.milDamage
        bool value60; // Sniper.milDamage
        bool value61; // Scatter.milDamage
        bool value62; // Cannon.milDamage
        bool value63; // Poison.milDamage */
        bool allPowerupsUsed;
        bool prestiged5Times;
        bool have10EachBall;
        bool break1000BlackBricks;
        bool reachLevel250;
        bool allLasersUnlocked;
        int hasUsedDoubleMoney;
        int hasUsedClickFrenzy;
        int hasUsedDemonCore;
        int hasUsedSnowBall;
        int hasUsedDoubleGold;
        /*int value75; // Skill Points (TO DO)
        int value76; // Skill Points (TO DO)
        int value77; // Skill Points (TO DO)
        int value78; // Skill Points (TO DO)
        int value79; // Skill Points (TO DO)
        int value80; // Skill Points (TO DO)
        int value81; // Skill Points (TO DO)
        int value82; // Skill Points (TO DO)
        int value83; // Skill Points (TO DO)
        int value84; // Skill Points (TO DO)
        int value85; // Skill Points (TO DO)
        int value86; // Skill Points (TO DO)
        int value87; // Skill Points (TO DO)
        int value88; // Skill Points (TO DO)
        int value89; // Skill Points (TO DO)
        int value90; // Skill Points (TO DO)
        int value91; // Skill Points (TO DO)
        int value92; // Skill Points (TO DO)
        int value93; // Skill Points (TO DO)
        int value94; // Skill Points (TO DO)
        int value95; // Skill Points (TO DO)
        int value96; // Skill Points (TO DO)
        int value97; // Skill Points (TO DO)
        int value98; // Skill Points (TO DO)
        int value99; // Skill Points (TO DO)
        int value100; // Skill Points (TO DO)
        int value101; // Skill Points (TO DO)
        int value102; // Skill Points (TO DO)
        int value103; // Skill Points (TO DO)
        int value104; // Skill Points (TO DO)*/
        int blackBrickWallet;
        /* int cursorColor;
        int backgroundColor; */
        int bossNumber; // Difference between these are unknown
        int bossLevel; // Difference between these are unknown
        int skillPoints;
        /* bool soundOn;
        int soundEffects; // Unknown
        bool autoFightBoss; */
    public:
        class Ball {
            private:
                int amount = 0;
            public:
                Ball() {};
                int getAmount() {return amount;}
                void setAmount(int amnt) {
                    if(amnt < 0) {throw std::invalid_argument("Amount must be at least 0");}
                    amount = amnt;
                }
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
                const int speedMult;
                const int speedAdd;
                int trueSpeed;
                const int maxSpeedUpgrades;
                // Similar with power except you can keep upgrading power indefinitly.
                const int powerMult;
                const int powerAdd;
                int truePower;
                const std::string statOneName;
            public:
                // NEVER USE THE DEFAULT CONSTRUCTOR
                StandardBall() :
                    speedMult(0),
                    speedAdd(0),
                    maxSpeedUpgrades(0),
                    trueSpeed(0),
                    powerMult(0),
                    powerAdd(0),
                    truePower(0),
                    statOneName("speed") {}
                StandardBall(int speedMult, int speedAdd, int maxSpeedUpgrades, int powerMult, int powerAdd, std::string statOneName) :
                    speedMult(speedMult),
                    speedAdd(speedAdd),
                    maxSpeedUpgrades(maxSpeedUpgrades),
                    trueSpeed(speedAdd),
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
        class SettingsGroup {
            private:
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
                int ballFactShowing; // What ball fact is currently showing
                bool ballFactsOn;
                bool BonusAlerts;
                CursorColorEnum cursorColor;
                BackgroundColorEnum backgroundColor;
                bool effectsOn;
                bool soundOn;
                int soundEffects; // Unknown
                bool autoFightBoss;
        };
        IdleSave() {};
        StandardBall Basic = StandardBall(1, 1, 9, 1, 1, "speed");
        StandardBall Plasma = StandardBall(1, 1, 6, 3, 3, "range");
        StandardBall Sniper = StandardBall(1, 4, 6, 5, 5, "speed");
        StandardBall Scatter = StandardBall(1, 2, 8, 10, 10, "extra balls");
        StandardBall Cannon = StandardBall(2, 4, 6, 25, 50, "speed");
        StandardBall Poison = StandardBall(2, 5, 5, 5, 5, "speed");
        Ball Snow;
        Ball Money;
        SettingsGroup Settings;
};