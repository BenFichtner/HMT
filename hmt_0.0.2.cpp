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
#include <net/if.h>
#include <netinet/in.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/if_link.h>

using namespace std;

void armTemp(){
    string temp;
    ifstream myFile;
    myFile.open("/sys/class/thermal/thermal_zone0/temp");
    while (myFile >> temp){
        float currentTemp = stof(temp);
        float cpuTemp = currentTemp / 1000;
        cout << "Current ARM CPU Temperature is " << cpuTemp << "° C." << endl;
        }
    myFile.close();
} 

void eth0_ipAddress(){
    int fd;
    struct ifreq ifr;
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, "eth0", IFNAMSIZ-1);
    ioctl(fd, SIOCGIFADDR, &ifr);
    close(fd);
    printf("%s\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
}

   void wlan0_ipAddress(){
    int fd;
    struct ifreq ifr;
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, "wlan0", IFNAMSIZ-1);
    ioctl(fd, SIOCGIFADDR, &ifr);
    close(fd);
    printf("%s\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
}

void wait_on_enter(){
    cout << endl << "Press <Enter> to Continue";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void title_bar(){
    cout << "\t|—————————————————————————————————————————————|" << endl;
    cout << "\t|           Headless Managment Tool           |" << endl;
    cout << "\t|                Version 0.0.2                |" << endl;
    cout << "\t|———|—————————————————————————————————————————|" << endl;
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
        cout << "\t|   | System Hostname  :   : " << unameData.nodename << endl;
        cout << "\t|   | Processor Type   :   : " << unameData.machine << endl;
        cout << "\t|   | CPU Temperature  :   : " << cpuTemp  << "°C" << endl;
        cout << "\t|   | Kernel Version   :   : " << unameData.release << endl;

        }
    myFile.close();
}

void menu(){
    cout << "\t|———|——————————————————|———|——————————————————|" << endl;
    cout << "\t|[1]| Process Monitor  |[2]| System Info      |" << endl;
    cout << "\t|[3]| Network Activity |[4]| Disk Activity    |" << endl;
    cout << "\t|[5]| Edit 'smb.conf'  |[6]| Restart SAMBA    |" << endl;
    cout << "\t|[7]| IP Address Wired |[8]| IP Address WLAN  |" << endl;
    cout << "\t|[9]| Refresh Screen   |[0]| Exit Program     |" << endl;
    cout << "\t|———|——————————————————|———|——————————————————|" << endl;
    cout << "\t|—————————————————————————————————————————————|" << endl;
}

int main() {
    system("clear");
    int command;
    title_bar();
    system_info();
    menu();
    cout << "\t\tSelect a command to run:  "; 
    cin >> command;
    
    if(command == 1){
        system("htop");
        system("clear");
        main();
    } 
    else if(command == 2){
        system("clear");
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
        system("systemctl restart smbd.service");
        cout << "SAMBA Servce has been restarted." << endl;
        wait_on_enter();
    }
    else if(command == 7){
        system("clear");
        cout << "Wired IP Address: ";
        eth0_ipAddress();
        wait_on_enter();
    }
    else if(command ==8){
        system("clear");
        cout << "Wireless IP Address: ";
        wlan0_ipAddress();
        wait_on_enter();
    }
    else if(command == 9){
        system("clear");
        main();
    }
    else if(command == 0){
        system("clear");
        exit(2);
    }
    else cout << "Not a valid selection." << endl;
        system("clear");
        main(); 
        
return 0;
}
