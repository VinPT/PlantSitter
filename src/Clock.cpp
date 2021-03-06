#include "Clock.h"
const int Clock::month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
Clock::Clock()
{
    lastCheckMiliseconds = millis();
}

void Clock::relitiveSetHours(int input)
{
    setHours(input + time.hours);
}
void Clock::relitiveSetMinutes(int input)
{
    setMinutes(input + time.minutes);
}
void Clock::relitiveSetSeconds(int input)
{
    setSeconds(input + time.seconds);
}

void Clock::setHours(int input)
{
    time.hours = input;
}
void Clock::setMinutes(int input)
{
    time.minutes = input;
}
void Clock::setSeconds(int input)
{
    time.seconds = input;
}

Clock::Time Clock::getTime()
{
    return time;
}

void Clock::update()
{
    unsigned int check = millis();
    unsigned long millisChange = check > lastCheckMiliseconds ? check - lastCheckMiliseconds : (~lastCheckMiliseconds) + check;

    time.miliSeconds += millisChange;

    if (1000 <= time.miliSeconds)
    {
        time.seconds += 1;
        time.miliSeconds -= 1000;
    }
    else if (0 > time.miliSeconds)
    {
        time.miliSeconds += 1000;
    }

    if (60 <= time.seconds)
    {
        time.minutes += 1;
        time.seconds -= 60;
    }
    else if (0 > time.seconds)
    {
        time.minutes -= 1;
        time.seconds += 60;
    }

    if (60 <= time.minutes)
    {
        time.hours += 1;
        time.minutes -= 60;
    }
    else if (0 > time.minutes)
    {
        time.hours -= 1;
        time.minutes += 60;
    }

    if (24 <= time.hours)
    {
        time.days += 1;
        time.hours -= 24;
    }
    else if (0 > time.hours)
    {
        time.days -= 1;
        time.hours += 24;
    }

    if (month[time.months] <= time.days)
    {
        time.months += 1;
        time.days -= month[time.months];
    }
    else if (0 > time.days)
    {
        time.months -= 1;
        time.days += month[time.months - 1];
    }

    if (12 <= time.months)
    {
        time.years += 1;
        time.months -= 12;
    }
    else if (0 > time.months)
    {
        time.years -= 1;
        time.months += 12;
    }

    //Serial.print(time.hours);
    //Serial.print(":");
    //Serial.print(time.minutes);
    //Serial.print(":");
    //Serial.print(time.seconds);
    //Serial.print(":");
    //Serial.println(time.miliSeconds);
    //Serial.println(millisChange);

    lastCheckMiliseconds = check;
}

Clock::~Clock()
{
}