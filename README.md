Windows Command Prompt Compilation/Execution:

    Compilation: g++ -std=c++11 -pthread -o minotaur_birthday minotaur_birthday.cc
    Execution: minotaur_birthday
    Unified: g++ -std=c++11 -pthread -o minotaur_birthday minotaur_birthday.cc && minotaur_birthday 100000000

Linux Bash Shell Compilation/Execution:

    Compilation: g++ -std=c++11 -pthread -o minotaur_birthday minotaur_birthday.cc
    Execution: ./minotaur_birthday
    Unified: g++ -std=c++11 -pthread -o minotaur_birthday minotaur_birthday.cc && ./minotaur_birthday 100000000

PowerShell Compilation/Execution:

    Compilation: g++ -std=c++11 -pthread -o minotaur_birthday minotaur_birthday.cc
    Execution: .\minotaur_birthday
    Unified: g++ -std=c++11 -pthread -o minotaur_birthday minotaur_birthday.cc; if ($?) { .\minotaur_birthday 100000000 }

Output Formatting:

Proof of Correctness: 

Statement:

Experimental Evaluations: