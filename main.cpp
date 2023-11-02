/*
* Name: Christopher Rosado, 2001956343, Assignment six
* Description: The main program uses a custom made priorityQ
* class to intake each of the MarioKart characters with a certain
* value indicating the location of the character to the finish line.
* The program will first input all of the racers into their proper 
* locations and will then continue to take inputs, changing the 
* priority values as the racers come up within the txt file, making
* sure that a racer who has either already been updated or finished the race 
* is not being accidentally updated again (all thanks to hashmaps). 
* Each interval will continue to go until either the KartCharacters 
* string is equal to DONE or if the amount of racers being updated 
* is equal to the current total number of racers within the interval.
* Once a racer has completed the race (having a value less than or equal 
* to zero) it will ouput the racers placement and updates the racer count
* down to the remaining amount of racers. 
* Input: A file with all the Characters and their respective 
* values throughout each interval. 
* Output: What characters are being updated within each interval
* and which Karts finish in order. 
*/
#include <iostream>
#include "priorityQ.h"
#include "priorityQ.cpp"
#include <unordered_map>

using namespace std;

int main(){

priorityQ<string, double> MarioKart; //priority Queue for the Characters
unordered_map<string,bool> FinishedRace; //Boolean hashmap for characters who finished the race
string KartCharacters = ""; 
double Distance = 0;
int IntervalCnt = 1, AmtOfRacers = 0, RacerCnt = 0, Placement = 1;

cin>>KartCharacters;
while(KartCharacters != "END"){
    AmtOfRacers++;
    for(int i = 0; i < KartCharacters.length(); i++)
        KartCharacters[i] = tolower(KartCharacters[i]);

    MarioKart.push_back(KartCharacters, 50);
    cin>>KartCharacters;
}

while(!cin.fail()){
    unordered_map<string, bool> IntervalComplete;
    RacerCnt = 0;
    cout<<"\nInterval "<<IntervalCnt<<endl<<endl;
    cin>>KartCharacters;


    while(MarioKart.get_front_priority() < 0 && !MarioKart.isEmpty()){

        cout<<Placement<<" "<<MarioKart.get_front_key()<<endl<<endl;
        FinishedRace[MarioKart.get_front_key()] = true;
        MarioKart.pop_front();
        Placement++;
        AmtOfRacers--;
    }

    if(AmtOfRacers <= 0)
        break;
         
    while(KartCharacters != "DONE"){

        for(int i = 0; i < KartCharacters.length(); i++)
            KartCharacters[i] = tolower(KartCharacters[i]);

        if(FinishedRace[KartCharacters] == true){
            cout<<"Racer has already finished the race!\n\n";
            cin>>KartCharacters;
            continue;
        }

        if(IntervalComplete[KartCharacters] == true){
            cout<<"Already updated "<<KartCharacters<<" in this interval !\n\n";
        }else{
            cin>>Distance;
                cout<<"Updating "<<KartCharacters<<endl;
                IntervalComplete[KartCharacters] = true;
                MarioKart.decrease_priority(KartCharacters, Distance);
                RacerCnt++;
            
            if(RacerCnt == AmtOfRacers)
                break;
        }
        cin>>KartCharacters;
    }
    IntervalCnt++;
}

}