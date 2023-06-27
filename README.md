# C_ReverseShell

Reverse shell coded in C for Windows. Controlled by an attacker on a Linux machine.

## Features
- [x] Persistency
- [x] Keylogger
- [x] Executing Windows commands

## Compilation commands

### server.c

```bash
gcc server.c -o server
```

### backdoor.c

```bash
i686-w64-mingw32-gcc -o backd.exe backdoor.c -lwininet -lwsock32
```
