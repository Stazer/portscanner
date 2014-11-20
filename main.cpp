/*
        A port scanner for unix based systems. Takes
        the start port and the end port from the command line
        arguments and prints open ports of the localhost.
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <iostream>
#include <cstdlib>

int main ( int amount , char ** arguments )
{
        unsigned short minimum = 0 ;
        unsigned short maximum = 1023 ;

        if ( amount > 2 )
        {
                minimum = std::atoi ( arguments [ 1 ] ) ;
                maximum = std::atoi ( arguments [ 2 ] ) ;
        }
		else if ( amount > 1 )
                maximum = std::atoi ( arguments [ 1 ] ) ;

        int socket = -1 ;

        if ( ( socket = ::socket ( AF_INET , SOCK_STREAM , 0 ) ) < 0 )
                return -1 ;

        sockaddr_in address ;

        address.sin_family = AF_INET ;
        address.sin_addr.s_addr = ( inet_addr ( "127.0.0.1" ) ) ;

        for ( unsigned short port = minimum ; port <= maximum ; ++port )
        {
                address.sin_port = htons ( port ) ;

                if ( connect ( socket , reinterpret_cast <sockaddr *> ( & address ) , sizeof ( address ) ) > -1 )
                        std::cout << "port " << port << " is open\n" ;
        }

        return 0 ;
}
