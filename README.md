# UCCS-RideShare
### **Project Overview**

This project is designed to create a Ride Share program with administrator login privileges, allowing the administrator to set up and manage information for the ride-sharing service. The program operates continuously until the admin decides to shut it down. It gathers survey data, calculates fares, and displays a comprehensive summary of the program's performance, making it a valuable tool for ride-sharing businesses.

### **Features**
**Administrator Login:** Secure admin login with password protection, allowing the setup and management of ride-sharing details.
**Ride Fare Calculation:** Uses a combination of base fare, cost per minute, cost per mile, and flat rate to calculate the total fare for each ride.
Randomized Ride Duration: Generates a random number of minutes based on the distance of the ride to simulate real-world scenarios.
**Survey System:** Allows riders to rate their experience based on safety, cleanliness, and comfort. These ratings are stored and displayed in a business summary.
**Linked List Implementation:** Stores multiple ride-share companies' data using a linked list, allowing for dynamic memory allocation and efficient data management.
**File Output:** Writes a detailed business summary report to a text file for each ride-share company, making it easy to review the program's performance.

**Technical ### Details**
**Languages Used:** C
**Key Concepts:**
**Memory Management:** Efficient use of memory through dynamic allocation for linked lists and proper deallocation to prevent memory leaks.
**2D Arrays:** Used for storing and processing rider survey data.
**Pointers:** Extensively used to manage data structures and pass data between functions.
**Input Validation:** Ensures that user inputs fall within acceptable ranges and are correctly formatted.
**Custom Headers:** Utilized for organizing code and enhancing readability.
**Modular Design:** Functions are separated into distinct tasks, adhering to the principles of clean and maintainable code.

**### Project Iterations**
**First Iteration:**
Introduced the use of functions and random number generation.
Focused on demonstrating the Agile development cycle by incrementally building features.
**Second Iteration:**
Implemented advanced C programming concepts such as pointers, 2D arrays, and input validation.
Enhanced the program's functionality and robustness through careful memory management.

**### How to Run the Program**
**Clone the Repository:**
Copy code
git clone [repository URL]

**Compile the Code:**
Use a C compiler to compile the code. For example:

Copy code
gcc -o rideshare rideshare.c

**Run the Program:**
Copy code
./rideshare
Admin Login:

**Enter the correct admin ID and password when prompted.**
Default ID is "a"
Default Password is "b"

**Set up the ride-sharing details such as base fare, cost per minute, cost per mile, and flat rate.**
Rider Mode:

**Enter the number of miles for the ride.**
The program will calculate the fare and optionally prompt the rider to provide feedback.

**End Program:**

To exit the rider mode and view the business summary, the admin must log in again.
