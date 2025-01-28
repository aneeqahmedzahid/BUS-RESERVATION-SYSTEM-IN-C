#include <stdio.h>
#include <string.h>

#define MAX_BUSES 10
#define MAX_SEATS 40
#define FILENAME "bus_data.dat"
#define MAX_NAME_LENGTH 50

typedef struct 
{
    int busno;
    char busname[50];
    char drivername[50];
    int departurecity; // 1: Islamabad, 2: Lahore, 3: Multan, 4: Karachi
    int arrivalcity;   // 1: Islamabad, 2: Lahore, 3: Multan, 4: Karachi
    float time;        // Time in 24-hour format
    float ticketprice; // Ticket price
    char classType[10]; // Class type: Economy or Business
    char bookerNames[MAX_SEATS][MAX_NAME_LENGTH]; // Names of bookers for each seat
    int seats[MAX_SEATS]; // 1 if booked, 0 if available
} Bus;

void initializeBuses(Bus buses[], int *count) 
{
    FILE *file = fopen(FILENAME, "wb");
    if (file) {
        *count = 0;
        fwrite(count, sizeof(int), 1, file);
        fclose(file);
    }
}

void saveBuses(Bus buses[], int count) 
{
    FILE *file = fopen(FILENAME, "wb");
    if (file) {
        fwrite(&count, sizeof(int), 1, file);
        fwrite(buses, sizeof(Bus), count, file);
        fclose(file);
    }
}

int authenticateUser () 
{
    char username[20];
    char password[20];
    char storedUsername[20] = "user";
    char storedPassword[20] = "1234";

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0) {
        return 1; // Authentication successful
    } else {
        printf("Invalid username or password!\n");
        return 0; // Authentication failed
    }
}

void addBus(Bus buses[], int *count) 
{
    if (*count >= MAX_BUSES) 
    {
        printf("Maximum bus limit reached!\n");
        return;
    }

    // Authenticate user before adding a bus
    if (!authenticateUser ()) 
    {
        return; // Exit if authentication fails
    }

    Bus newBus;
    printf("Input Data for Bus: %d\n", *count + 1);
    printf("Enter Bus No: ");
    scanf("%d", &newBus.busno);

    // Check for duplicate bus numbers
    for (int i = 0; i < *count; i++) 
    {
        if (buses[i].busno == newBus.busno) {
            printf("Bus number already exists!\n");
            return;
        }
    }

    printf("Enter Bus Name: \n");
    scanf("%s", newBus.busname);
    printf("Enter Driver Name: \n");
    scanf("%s", newBus.drivername);
    
    printf("Select Departure City:\n[1].Islamabad\n[2].Lahore\n[3].Multan\n[4].Karachi\n\nChoose (1-4): ");
    scanf("%d", &newBus.departurecity);
    if (newBus.departurecity < 1 || newBus.departurecity > 4) 
    {
        printf("Invalid departure city!\n");
        return;
    }

    printf("Select Arrival City:\n[1].Islamabad\n[2].Lahore\n[3].Multan\n[4].Karachi\n\nChoose (1-4): ");
    scanf("%d", &newBus.arrivalcity);
    if (newBus.arrivalcity < 1 || newBus.arrivalcity > 4) 
    {
        printf("Invalid arrival city!\n");
        return;
    }

    printf("Enter Time (00.00) 24-hour Format: ");
    scanf("%f", &newBus.time);
    if (newBus.time < 0 || newBus.time >= 24) 
    {
        printf("Invalid time format!\n");
        return;
    }

    printf("Enter Price: Rs ");
    scanf("%f", &newBus.ticketprice);
    if (newBus.ticketprice < 0) 
    {
        printf("Invalid price!\n");
        return;
    }

    printf("Select Class Type:\n[1]. Economy\n[2]. Business\nChoose (1-2): ");
    int classChoice;
    scanf("%d", &classChoice);
    if (classChoice == 1) {
        strcpy(newBus.classType, "Economy");
    } 
    else if (classChoice == 2) 
    {
        strcpy(newBus.classType, "Business");
    } 
    else 
    {
        printf("Invalid class type!\n");
        return;
    }

    for (int i = 0; i < MAX_SEATS; i++) 
    {
        newBus.seats[i] = 0;
        strcpy(newBus.bookerNames[i], "Available"); // Initialize booker names
    }

    buses[*count] = newBus;
    (*count)++;
    saveBuses(buses, *count);
    printf("Bus added successfully!\n");
}

void displayBuses(Bus buses[], int count) {
    if (count == 0) {
        printf("No buses available!\n");
        return;
    }

    printf("\nAvailable Buses:\n");
    printf("---------------------------------------------------------------------------------------------\n");
    printf("%-10s %-20s %-20s %-15s %-15s %-10s %-10s %-10s\n", "Bus No", "Bus Name", "Driver Name", "Departure", "Arrival", "Time", "Price", "Class");
    printf("---------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        char *departureCities[] = {"", "Islamabad", "Lahore", "Multan", "Karachi"};
        char *arrivalCities[] = {"", "Islamabad", "Lahore", "Multan", "Karachi"};

        printf("%-10d %-20s %-20s %-15s %-15s %-10.2f %-10.2f %-10s\n",
               buses[i].busno, buses[i].busname, buses[i].drivername,
               departureCities[buses[i].departurecity], arrivalCities[buses[i].arrivalcity],
               buses[i].time, buses[i].ticketprice, buses[i].classType);
    }
    printf("---------------------------------------------------------------------------------------------\n");
}

void bookTicket(Bus buses[], int count) 
{
    if (count == 0) {
        printf("No buses available to book tickets!\n");
        return;
    }

    displayBuses(buses, count);

    int busno;
    printf("Enter Bus No to book ticket: ");
    scanf("%d", &busno);

    int busIndex = -1;
    for (int i = 0; i < count; i++) {
        if (buses[i].busno == busno) {
            busIndex = i;
            break;
        }
    }

    if (busIndex == -1) {
        printf("Bus No not found!\n");
        return;
    }

    printf("Select Class Type:\n[1]. Economy\n[2]. Business\nChoose (1-2): ");
    int classChoice;
    scanf("%d", &classChoice);
    if (classChoice == 1 && strcmp(buses[busIndex].classType, "Economy") != 0) {
        printf("This bus is not in Economy class!\n");
        return;
    } else if (classChoice == 2 && strcmp(buses[busIndex].classType, "Business") != 0) {
        printf("This bus is not in Business class!\n");
        return;
    }

    printf("Enter seat number to book (1-%d): ", MAX_SEATS);
    int seatNumber;
    scanf("%d", &seatNumber);

    if (seatNumber < 1 || seatNumber > MAX_SEATS) {
        printf("Invalid seat number!\n");
        return;
    }

    if (buses[busIndex].seats[seatNumber - 1] == 1) {
        printf("Seat already booked!\n");
    } else {
        char bookerName[MAX_NAME_LENGTH];
        printf("Enter your name: ");
        scanf("%s", bookerName);
        
        buses[busIndex].seats[seatNumber - 1] = 1;
        strcpy(buses[busIndex].bookerNames[seatNumber - 1], bookerName); // Store the booker's name
        saveBuses(buses, count);
        printf("Seat %d successfully booked on Bus No %d!\n", seatNumber, busno);
    }
}

void viewBookings(Bus buses[], int count) {
    if (count == 0) {
        printf("No buses available to view bookings!\n");
        return;
    }

    int busno;
    printf("Enter Bus No to view bookings: ");
    scanf("%d", &busno);

    int busIndex = -1;
    for (int i = 0; i < count; i++) {
        if (buses[i].busno == busno) {
            busIndex = i;
            break;
        }
    }

    if (busIndex == -1) {
        printf("Bus No not found!\n");
        return;
    }

    printf("\nBookings for Bus No %d:\n", buses[busIndex].busno);
    for (int i = 0; i < MAX_SEATS; i++) {
        printf("Seat %d: %s\n", i + 1, buses[busIndex].seats[i] ? buses[busIndex].bookerNames[i] : "Available");
    }
}

int main() 
{
    Bus buses[MAX_BUSES];
    int busCount;

    initializeBuses(buses, &busCount);

    int choice;
    do {
        printf("\nBus Reservation System\n");
        printf("1. Add Bus\n");
        printf("2. Display Buses\n");
        printf("3. Book Ticket\n");
        printf("4. View Bookings\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addBus(buses, &busCount);
                break;
            case 2:
                displayBuses(buses, busCount);
                break;
            case 3:
                bookTicket(buses, busCount);
                break;
            case 4:
                viewBookings(buses, busCount);
                break;
            case 5:
                printf("Exiting system. Goodbye!\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}