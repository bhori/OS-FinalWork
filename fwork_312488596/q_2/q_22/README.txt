In order to run the program you need to run the command 'make' or 'make all' that will compile the programs 'server.c' and 'client.c' and call the executable files 'server' and 'client' respectively.

Then you must first run the server in one window (write in the execution command only the program name without additional parameters) and the client in another window, 
in the client execution command you must write the program name with 3 more parameters (integers) separated by a space 
when the first parameter Indicates the ID of the server process (for convenience I attached a print of the server's pid at the beginning of its run), 
the second parameter indicates the signal type (SIGINT-2, SIGUSR1-10) 
and the third parameter indicates the amount of signals you want to send of this type.

* To get the required result in the question you must first run the client with signal 2 (SIGINT) and a large number of signals you want to send, 
then run again the client with signal 10 (SIGUSR1) with a single signal (the third parameter is 1), 
after Sending the SIGUSR1 signal The server will print the amount of SIGINT signals received by it.

* Whenever you want to stop the server running it can be done by the kill command from the terminal with the server's pid (the default command is to terminate the process).

Running example:
1) make
2) ./server 	/** (in one window)
3) ./client <server pid> 2 100000 	/** (in another window)
4) ./client <server pid> 10 1
** [optional] 5) kill <server pid>

** In order to clean the executable files and the compiled files you can run the command 'make clean'.
