#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct Bus stores the various infomation about the buses and help in providing // the view of Bus information
struct Bus {

    int busNumber;

    char origin[20];

    char destination[20];

    int totalSeats;

    int availableSeats;

    float fare;

    int bookedSeats[500];
};

// this is define a structure to store passenger information like name , age, seatnumber, // busnumber etc .

struct Passenger {

    char name[60];

    int age;

    int seatNumber;

    int busNumber;
};

// this function is to display user menu , user can selet any of the given option and reservation process will continue further 

void displayUserMenuDisplay() {

    printf("\nUser Menu - select the desired option to proceed further ---> \n");

    printf("1. Bus Information  Chart\n");

    printf("2. Book a Confirm Ticket in Bus\n");

    printf("3. Check Bus Current Status\n");

    printf("4. Exit from the process :) \n");

    printf("Enter your choice from the Menu: ");
}

// Function to book a ticket

void funcForBookTicket(struct Bus buses[], int numBuses,

    struct Passenger passengers[],

    int * numPassengers) {

    printf("\nEnter the valid Bus Number you want to Book : ");

    int busNumber;

    scanf("%d", & busNumber);

    int busIndex = -1;

    for (int i = 0; i < numBuses; i++) {
        if (buses[i].busNumber == busNumber) {

            busIndex = i;

            break;
        }
    }

    if (busIndex == -1) {

        printf("Oops❗ Bus with Bus Number %d is not found. Try for another bus or try another route.\n", busNumber);
    } else if (buses[busIndex].availableSeats == 0) {
        printf("Sorry 😥, the bus is fully booked , try in another bus.\n");
    } else {
        printf("\nTotal seats:- %d", buses[busIndex].totalSeats);

        if ( * numPassengers == 0) {
            printf("\nNo tickets booked yet, bus is empty.");
        } else {
            for (int i = 0; i < * numPassengers; i++) {
                if (passengers[i].busNumber == busNumber) {
                    printf("\nSeat Number:- %d, Passenger Name:- %s", passengers[i].seatNumber, passengers[i].name);
                }
            }
        }

        int ticketsToBook;

        printf("\nEnter the number of tickets you want to book:- ");
        scanf("%d", & ticketsToBook);

        int flag = 0;

        while (ticketsToBook > buses[busIndex].availableSeats) {
            printf("\nSorry, only %d seats are available.", buses[busIndex].availableSeats);

            printf("\nPress 1 to renter or 0 to abort:- ");
            scanf("%d", & ticketsToBook);

            if (ticketsToBook == 0) {
                flag = 1;
                break;
            }
        }

        if (flag == 1)
            return;

        while (ticketsToBook > 0) {
            printf("Enter Passenger Name: ");

            scanf("%s", passengers[ * numPassengers].name);

            int seatFlag = 0;
            int seatNumber;
            while (seatFlag == 0) {
                printf("\nEnter Seat Number: ");

                scanf("%d", & seatNumber);

                if (seatNumber > buses[busIndex].totalSeats) {
                    printf("\nSeat number can not exceed the total number of seats.");
                    continue;
                }
                int present = 0;
                if (buses[busIndex].bookedSeats[seatNumber] == 0) {
                    seatFlag = 1;
                    passengers[ * numPassengers].seatNumber = seatNumber;
                    buses[busIndex].bookedSeats[seatNumber] = 1;
                } else {
                    printf("\nSeat Already booked. Please enter again.");
                }
            }

            passengers[ * numPassengers].busNumber = busNumber;
            passengers[ * numPassengers].seatNumber = seatNumber;

            buses[busIndex].availableSeats--;
            printf("Ticket booked successfully!🌟\n");

            ( * numPassengers) ++;
            ticketsToBook--;
        }
    }
}

// will print the table of bus information on the screen
void checkBus(struct Bus buses[], int numBuses) {

    printf("\nBus Number\t  Origin\t  Destination\t  Total Seats\t  Available Seats\t   Fare  \n");
    int i;

    for (i = 0; i < numBuses; i++) {
        printf("\n %d \t\t %s \t\t %s \t\t %d \t\t\t %d \t\t\t %.2f \n", buses[i].busNumber, buses[i].origin, buses[i].destination, buses[i].totalSeats, buses[i].availableSeats, buses[i].fare);
    }
}

// Function to check bus status
void checkBusCurrentStatus(struct Bus buses[], int numBuses, struct Passenger passengers[], int numPassengers) {
    int busNumber;
    printf("Enter the bus number:- ");
    scanf("%d", & busNumber);

    int busIndex = -1;

    for (int i = 0; i < numBuses; i++) {
        if (buses[i].busNumber == busNumber) {

            busIndex = i;

            break;
        }
    }

    if (busIndex == -1) {
        printf("\nNo bus exists....");
        return;
    }
    int cnt = 0;

    for (int i = 0; i < numPassengers; i++) {
        if (passengers[i].busNumber == busNumber) {
            printf("\nSeat Number:- %d, Passenger Name:- %s", passengers[i].seatNumber, passengers[i].name);
            cnt++;
        }
    }

    if (cnt == 0) {
        printf("\nNo passenger exists....");
    }
}

int main() {
    
    // Initialize bus data

    int emptyArray[100];

    for (int i = 0; i < 100; i++) {
        emptyArray[i] = 0;
    }

    struct Bus buses[7] = {

        {
            101,
            "City A",
            "City B",
            50,
            50,
            25.0,
            emptyArray
        },

        {
            102,
            "City C",
            "City D",
            40,
            40,
            20.0,
            emptyArray
        },

        {
            103,
            "City E",
            "City F",
            30,
            30,
            15.0,
            emptyArray
        },
        
 {
            104,
            "City A",
            "City F",
            40,
            40,
            15.0,
            emptyArray
        },
 {
            105,
            "City B",
            "City D",
            60,
            60,
            75.0,
            emptyArray
        },
        
         {
            106,
            "City C",
            "City A",
            50,
            50,
            35.0,
            emptyArray
        },
        
         {
            107,
            "City C",
            "City F",
            60,
            60,
            30.0,
            emptyArray
        },


    };

    int numBuses = 7;

    struct Passenger passengers[1000]; // Array to store passenger information

    int numPassengers = 0; // Number of passengers

    while (1) {

        int flag = 0;
        displayUserMenuDisplay();

        int userChoice;

        scanf("%d", & userChoice);

        switch (userChoice) {

        case 1:

            checkBus(buses, numBuses);
            break;

        case 2:

            funcForBookTicket(buses, numBuses, passengers, & numPassengers);
            break;

        case 3:

            checkBusCurrentStatus(buses, numBuses, passengers, numPassengers);
            break;

        case 4:
            flag = 1;
            break;

        default:

            printf(

                "Invalid choice. Please try again.\n");
        }

        if (flag) {
            printf("Have a safe and happy journey! Bye Bye....");
            break;
        }
    }
    return 0;
}