🏦 Bank Management System in C++
📖 Overview

The Bank Management System is a simple C++ console-based project that allows users to manage bank accounts efficiently.
It supports creating, modifying, deleting, and viewing accounts — as well as deposit and withdrawal operations.

All account details are securely stored in a binary file (bank.dat), ensuring data persistence even after closing the program.

🚀 Features

✅ Create a new account
✅ Display individual account details
✅ Deposit and withdraw money
✅ Modify existing account details
✅ Delete an account
✅ Display all account holders
✅ Data stored permanently in binary file

🧩 Technologies Used

C++ (Core Language)

File Handling (Binary Files)

Object-Oriented Programming (OOPs)

Standard Input/Output (iostream, fstream, iomanip)

⚙️ How It Works
1️⃣ Create Account

User can open a new account by entering:

Account Number

Name

Account Type (C for Current / S for Savings)

Initial Balance

2️⃣ Deposit / Withdraw

Allows adding or deducting money from an existing account while maintaining updated balance.

3️⃣ Modify Account

Edit existing account details like name, account type, and balance.

4️⃣ Delete Account

Removes the selected account permanently from the records.

5️⃣ Display All Accounts

Shows a list of all account holders in a tabular format.

📂 File Structure
📁 BankManagementSystem
│
├── bank.dat          # Binary file that stores all account details
├── main.cpp          # Main C++ source file (your provided code)
└── README.md         # Project documentation (this file)

🧮 Menu Options
Option	Description
1	Create New Account
2	Deposit Amount
3	Withdraw Amount
4	Balance Enquiry
5	Display All Account Holders
6	Close Account
7	Modify Account
8	Exit
🪜 How to Run

1️⃣ Open any C++ IDE or terminal (e.g., Code::Blocks, Dev-C++, VS Code).
2️⃣ Save the file as main.cpp.
3️⃣ Compile the program:

g++ main.cpp -o bank


4️⃣ Run the executable:

./bank