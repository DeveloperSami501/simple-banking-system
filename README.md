Banking System
Overview:

Welcome to the Banking System! This simple C++ program helps you manage client records for a bank.
You can add, delete, update, and search for clients, with all the details stored securely in a text file. 
Whether you’re a bank employee or just curious about how such a system works, this project will let you see basic banking functionalities in action.

What You Can Do:

Add a new client: Create a new client account with all the necessary details.
View client list: See all the client records in one go.
Delete a client: Remove a client’s record from the system.
Update a client: Edit client details like name, phone number, or balance.
Search for a client: Look up a client by their account number.

What Makes It Work:

File Management: The program saves all client data to a file, which is great for keeping things organized.
Interactive Menu: You’ll interact with the system through a simple text-based menu that lets you choose what you want to do with just a number.
String and File Operations: We use string manipulation and file reading/writing to keep track of client records.
The Files You’ll Need
The system stores client data in a file called Clients.txt. Here’s how the data is organized for each client:

Copy this code:

account_number|##|full_name|##|phone_number|##|pin_code|##|account_balance

The |##| symbol is used to separate the different pieces of information, so the program knows what belongs where.

How to Use the System:
When you first run the program, you’ll be greeted with a simple menu where you can pick from several options.

Here’s what you can do:

Add a New Client: Pick option 1 to add a new client. You’ll be asked to enter the account number, name, phone number, pin code, and balance.
Show All Clients: Option 2 will show you all the clients currently stored in the system.
Delete a Client: If you want to delete a client, pick option 3 and follow the prompts. You’ll be asked to confirm the deletion before it’s done.
Update Client Info: Choose option 4 if you need to change a client’s details like their phone number, balance, or pin.
Search for a Client: If you need to find a client by their account number, choose option 5 and enter the account number.

How Client Data Is Stored?

All the client details are saved in a text file called Clients.txt. Each client’s data is written in this format:
account_number|##|full_name|##|phone_number|##|pin_code|##|account_balance

