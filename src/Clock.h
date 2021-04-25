#include <Arduino.h>

class Clock
{
public:
    Clock();

    struct Time
    {
        int years;
        int months;
        int days;
        int hours;
        int minutes;
        int seconds;
        int miliSeconds;
    };
    const static int month[12];

    void relitiveSetHours(int input);
    void relitiveSetMinutes(int input);
    void relitiveSetSeconds(int input);

    void setHours(int input);
    void setMinutes(int input);
    void setSeconds(int input);

    Time getTime();

    void update();

    ~Clock();

private:
    Time time;
    unsigned long lastCheckMiliseconds;
};

/*
1	January	31 days
2	February	28 days (common year) 29 days (leap year*)
3	March	31 days
4	April	30 days
5	May	31 days
6	June	30 days
7	July	31 days
8	August	31 days
9	September	30 days
10	October	31 days
11	November	30 days
12	December	31 days
*/