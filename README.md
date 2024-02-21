Windows Command Prompt Compilation/Execution:

    Compilation: g++ -std=c++11 -pthread -o minotaur_birthday minotaur_birthday.cc
    Execution: minotaur_birthday
    Unified: g++ -std=c++11 -pthread -o minotaur_birthday minotaur_birthday.cc && minotaur_birthday

Linux Bash Shell Compilation/Execution:

    Compilation: g++ -std=c++11 -pthread -o minotaur_birthday minotaur_birthday.cc
    Execution: ./minotaur_birthday
    Unified: g++ -std=c++11 -pthread -o minotaur_birthday minotaur_birthday.cc && ./minotaur_birthday

PowerShell Compilation/Execution:

    Compilation: g++ -std=c++11 -pthread -o minotaur_birthday minotaur_birthday.cc
    Execution: .\minotaur_birthday
    Unified: g++ -std=c++11 -pthread -o minotaur_birthday minotaur_birthday.cc; if ($?) { .\minotaur_birthday }

Output Formatting:

Proof of Correctness: 

Statement:

Designate a Counter: Before entering the labyrinth, the guests agree to designate one guest as the counter. This guest is responsible for keeping track of how many unique guests have visited the labyrinth.

Cupcake Protocol: Guests follow these rules:

If a guest (not the counter) enters and finds the cupcake, they eat it and leave the plate empty. This signifies their first visit.
If the counter enters and finds the cupcake, they leave it, marking one complete round of visits.
The counter is allowed to eat the cupcake only after they have counted that all guests, including themselves, have made at least one visit. They then eat the cupcake and request a new one, incrementing their internal count of total guests visited.
Guests who have already eaten a cupcake once will leave it if they find it again, ensuring the counter can track new visits accurately.
Ending the Game: The game ends when the counter has counted N unique visits (including their own). At this point, the counter knows all guests have visited the labyrinth at least once, and they can announce to the Minotaur that the objective is completed.

Experimental Evaluations: