Introduction 

The Bus Reservation System is a console-based application written in C that allows 
users to manage bus reservations. The system provides functionalities for adding 
buses, displaying available buses, booking tickets, and viewing bookings. It also 
includes user authentication to ensure that only authorized personnel can add 
buses to the system. The application supports two classes of buses: Economy and 
Business. 

System Overview 

Key Features 
User Authentication: The system requires a username and password to add 
new buses. The default credentials are hardcoded as "user" for the username and 
"1234" for the password. 
Bus Management: Users can add new buses with details such as bus number, 
name, driver name, departure and arrival cities, time, ticket price, and class type 
(Economy or Business). 
Ticket Booking: Users can book tickets for available buses, specifying the class 
type and seat number. 
View Bookings: Users can view the booking status of seats for a specific bus. 
Data Persistence: The system saves bus data to a binary file (bus_data.dat) to 
ensure that data is retained between program executions. 

Data Structures 

The primary data structure used in the system is the Bus structure, which contains 
the following fields: 
busno: An integer representing the bus number. 
busname: A string representing the name of the bus. 
drivername: A string representing the name of the bus driver. 
departurecity: An integer representing the departure city (1: Islamabad, 2: 
Lahore, 3: Multan, 4: Karachi). 
arrivalcity: An integer representing the arrival city. 
time: A float representing the departure time in 24-hour format. 
ticketprice: A float representing the price of the ticket. 
classType: A string representing the class type (Economy or Business). 
bookerNames: An array of strings to store the names of the passengers who 
booked seats. 
seats: An array of integers to indicate whether a seat is booked (1) or available 
(0).

Functions 
The system consists of several functions that handle different functionalities: 
initializeBuses: Initializes the bus data by creating a binary file and setting the bus 
count to zero. 
saveBuses: Saves the current state of the buses to the binary file. 
**authenticateUser **: Prompts the user for a username and password, 
checking them against the hardcoded values. 
addBus: Allows an authenticated user to add a new bus. It collects all necessary 
information and checks for duplicate bus numbers before saving the new bus. 
displayBuses: Displays a list of all available buses, including their details. 
bookTicket: Allows users to book a ticket for a specified bus and seat. It checks 
if the seat is available and stores the booker's name. 
viewBookings: Displays the booking status of seats for a specified bus. 
main: The entry point of the program, which provides a menu for users to 
interact with the system. 
