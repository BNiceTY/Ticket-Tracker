



#include <iostream>
#include <string>
#include <limits>
#include "queueReserved.h" 


struct Ticket
{
    int id;
    std::string customerName;
    std::string issue;
};

// Helper to print a Ticket in standard format
void printTicket(const Ticket& t)
{
    std::cout << "Ticket #" << t.id
              << " | Name: " << t.customerName
              << " | Issue: " << t.issue << '\n';
}

int main()
{
    // Physical capacity 10 (9 Usable)
    queueReserved<Ticket> ticketQueue(10);

    int nextTicketId = 1;
    int choice = 0;

    while (true)
    {
        std::cout << "\n==== Ticket Tracker Main Menu ====\n"
                  << "1. Add new ticket\n"
                  << "2. Complete next ticket (remove front)\n"
                  << "3. View next ticket (front)\n"
                  << "4. View most recent ticket (back)\n"
                  << "5. Exit\n"
                  << "Enter choice: ";

        std::cin >> choice;

        if (!std::cin)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1)
        {
            // Add new ticket
            if (ticketQueue.isFullQueue())
            {
                std::cout << "The ticket queue is full. Cannot add more tickets.\n";
            }
            else
            {
                Ticket t;
                t.id = nextTicketId++;

                std::cout << "Enter customer name: ";
                std::getline(std::cin, t.customerName);

                std::cout << "Enter issue description: ";
                std::getline(std::cin, t.issue);

                ticketQueue.addQueue(t);
                std::cout << "Ticket added:\n";
                printTicket(t);
            }
        }
        else if (choice == 2)
        {
            if (ticketQueue.isEmptyQueue())
            {
                std::cout << "No tickets to serve. The queue is empty.\n";
            }
            else
            {
                Ticket next = ticketQueue.front();
                std::cout << "Serving ticket:\n";
                printTicket(next);

                ticketQueue.deleteQueue();
                std::cout << "Ticket has been removed from the queue.\n";
            }
        }
        else if (choice == 3)
        {
            // View front ticket
            if (ticketQueue.isEmptyQueue())
            {
                std::cout << "No tickets waiting. The queue is empty.\n";
            }
            else
            {
                Ticket next = ticketQueue.front();
                std::cout << "Next ticket in line (front):\n";
                printTicket(next);
            }
        }
        else if (choice == 4)
        {
            // View back ticket
            if (ticketQueue.isEmptyQueue())
            {
                std::cout << "No tickets in the queue. The queue is empty.\n";
            }
            else
            {
                Ticket last = ticketQueue.back();
                std::cout << "Most recently added ticket (back):\n";
                printTicket(last);
            }
        }
        else if (choice == 5)
        {
            std::cout << "Exiting Ticket Tracker. Goodbye!\n";
            break;
        }
        else
        {
            std::cout << "Invalid choice. Please select 1–5.\n";
        }
    }

    return 0;
}
