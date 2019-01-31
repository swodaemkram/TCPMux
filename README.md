# TCPMux
A Linux cli program to accept an IP connection and transmit that data to several other clients. Up to a maximum of 4.


	     TCPMux by Mark Meadows 
	a command line unidirectional TCP Multiplexer
	There must be a minimum of two host being relayed
	 -P, port of incoming TCP connection 
	 -1, first ip address and port for outgoing connection
	 -2, second ip address and port for outgoing connection
	 -3, third ip address and port for outgoing connection
	 -4, forth ip address and port for outgoing connection
	 -h, this help information
	  
    Example usage: TCPMux -P 8080 -1 192.168.1.12:8081 -2 192.168.1.10:8082 -3 192.168.1.11:8083 -4 192.168.1.13:8084
	
