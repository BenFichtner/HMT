#include <iostream>
#include <ios>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include <term.h>
#include <limits>
#include <fstream>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/utsname.h>

using namespace std;

void armTemp(){
    string temp;
    ifstream myFile;
    myFile.open("/sys/class/thermal/thermal_zone0/temp");
    while (myFile >> temp){
        float
         currentTemp = stof(temp);
        float cpuTemp = currentTemp / 1000;
        cout << "Current ARM CPU Temperature is " << cpuTemp << "° C." << endl;
        }
    myFile.close();
} 

void wait_on_enter(){
    cout << endl << "Press <Enter> to Continue";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}


void title_bar(){
    cout << "\t|—————————————————————————————————————————————————————————|" << endl;
    cout << "\t|—————————————————————————————————————————————————————————|" << endl;
    cout << "\t|                Headless Managment Tool                  |" << endl;
    cout << "\t|                      Version 0.11                       |" << endl;
    cout << "\t|—————————————————————————————————————————————————————————|" << endl;
}

void system_info(){
    string temp;
    ifstream myFile;
    myFile.open("/sys/class/thermal/thermal_zone0/temp");
    while (myFile >> temp){
        float
        currentTemp = stof(temp);
        int cpuTemp = currentTemp / 1000;
        struct utsname unameData;
        uname(&unameData);
        cout << "\t|          |   Hostname    :   " << unameData.nodename << "                      |" << endl;
        cout << "\t|  System  |   System Type :   " << unameData.machine << "                    |" << endl;
        cout << "\t|   Info   |   CPU Temp    :   " << cpuTemp  << "°C                       |" << endl;
        cout << "\t|          |   Kernel      :   " << unameData.release << "           |" << endl;

        }
    myFile.close();
}

void get_user_choice(){
    cout << "\t|—————|——————————————————————|—————|——————————————————————|" << endl;
    cout << "\t| [1] | Process Monitor      | [2] | System Information   |" << endl;
    cout << "\t| [3] | Network Activity     | [4] | Disk Activity        |" << endl;
    cout << "\t| [5] | Edit 'smb.conf'      | [6] | Restart SAMBA        |" << endl;
    cout << "\t| [0] | Refresh System Info  | [9] | Exit to Command Line |" << endl;
    cout << "\t|—————|——————————————————————|—————|——————————————————————|" << endl;
    cout << "\t|—————————————————————————————————————————————————————————|" << endl;
}

int main() {
    system("clear");
    int command;
    title_bar();
    system_info();
    get_user_choice();
    cout << "\t\t\tSelect a command to run:  "; 
    cin >> command;
    
    if(command == 1){
        system("htop");
        system("clear");
        main();
    } 
    else if(command == 2){
        system("neofetch");
        wait_on_enter();
        } 
    else if(command == 3){
	    system("clear");
        system("iftop");
        wait_on_enter();
    }
    else if(command == 4){
        system("clear");
        system("iotop");
        wait_on_enter();
    }
    else if(command == 5){
        system("clear");
        system("vim /etc/samba/smb.conf");
        main();
    }
    else if(command == 6){
        system("clear");
        system("systemctl restart smb.service");
        cout << "SAMBA Servce has been restarted." << endl;
        wait_on_enter();
    }
    else if(command == 9){
        system("clear");
        exit(2);
        }
    else cout << "Not a valid selection." << endl;
        system("clear");
        main(); 
        
return 0;
}
