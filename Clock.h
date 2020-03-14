#include<Arduino.h>




class Clock{
    public:
        Clock();
        
        struct Time
        {
            int hours;
            int minutes;
            int seconds;
            int miliSeconds;
        };
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