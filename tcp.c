#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h> //inet_addr
#include <time.h> //current date and time

const int NUM_SECONDS = 2; //timer for updating capacites, logging information and select
const int NUM_SECONDS1 = 24;   //sending pictures

int main(int argc , char *argv[])
{
    int socket_d;
    int byte_write = 0;
    int bytes_write = 0;
    int log_write = 0;
    const int full = 100; //full capacity of parking lot
    struct sockaddr_in server;
    char receive_buffer[32];
    char update_buffer[32];
    char select_buffer[32];
    char log_buffer[32];

    //Send Data to server
    int a;
    int b;

    double time_counter = 0;
    double time_counter1 = 0;

    clock_t this_time = clock();
    clock_t last_time = this_time;

    printf("Gran = %ld\n", NUM_SECONDS * CLOCKS_PER_SEC);
    printf("Gran = %ld\n", NUM_SECONDS1 * CLOCKS_PER_SEC);

    while(1)
    {
        this_time = clock();

        time_counter += (double)(this_time - last_time);

        last_time = this_time;

        if(time_counter > (double)(NUM_SECONDS * CLOCKS_PER_SEC))
        {
            time_counter -= (double)(NUM_SECONDS * CLOCKS_PER_SEC);
            a = 1;
            printf("a = %d\n", a);
 
    if(a == 1){
    
    //Create a socket
    socket_d = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_d < 0)
    {
        printf("Could not create socket\n");
    }

    server.sin_addr.s_addr = inet_addr("172.20.10.2");
    server.sin_family = AF_INET;
    server.sin_port = htons( 20111 );

    //Connect to remote server
    if (connect(socket_d, (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        printf("connect error\n");
        return 1;
    }
    printf("Connected\n");
    
    FILE *file, *sfile;
    FILE *output;
    file = fopen("update.txt", "r"); // opens file for reading
    sfile = fopen("select.txt", "r"); // opens file for reading
    output = fopen("output.txt", "w"); // opens file for writing

    char cap[32];
    char lot[32];

    while (fgets(lot, 32, sfile) && fgets(cap, 32, file) ) {

    int lot_numb = atoi(lot); //casting array to int
    int lot_capacity = atoi(cap);
    int capacity = lot_capacity;  //current capacity of parking lot
    int byte_read = 0;

    if(capacity <= full){
    // Printing commands to a string
    sprintf(select_buffer, "select %d\n", lot_numb);
    sprintf(update_buffer, "UPDATE %d CAPACITY %d\n", lot_numb, capacity);

    // Printing strings to output.txt for testing purposes
    fprintf(output,"Value of lot is %s", lot);
    fprintf(output,"Value of cap is %s", cap);
    fprintf(output,"Get lot capacity: %s", select_buffer);
    fprintf(output,"Update lot capacity: %s", update_buffer);

    // Printing values for tesing purposes
    printf("Value of lot is %s", lot);
    printf("Value of capacity is %s", cap);
    printf("%s", select_buffer);
    printf("%s", update_buffer);

    // Send commands to the server
    bytes_write = send(socket_d, update_buffer, strlen(update_buffer), 0);
    byte_write = send(socket_d, select_buffer, strlen(select_buffer), 0);

    // Local time and date
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char date[64];
    strftime(date, sizeof(date), "%m/%d/%Y", tm); // 08/10/1994 format
    printf("The date is %s\n",date);

    char time[64];
    strftime(time, sizeof(time), "%I:%M%P", tm); // 10:35pm format
    printf("The time is %s\n",time);

    // Log the entry
    sprintf(log_buffer, "LOG %d DATE %s INFO %s\n", lot_numb, date, time);
    fprintf(output,"New entry: %s\n", log_buffer);
    printf("%s\n", log_buffer);
    log_write = send(socket_d, log_buffer, strlen(log_buffer), 0);

    //Receive response from server
    int bytes_read = 0;
    bytes_read = recv(socket_d, receive_buffer, 32, 0);
    if (bytes_read > 0){
    printf("Lot Capacity is %s\n", receive_buffer);
    fprintf(output, "Lot Capacity is %s\n", receive_buffer);
    }
     else{
          printf("Receive failed\n");
          receive_buffer[bytes_read]= 0;
         }
 } //end of if capacity > full
    else{
         printf("Parking lot is full\n");
         fprintf(output, "Parking lot is full\n");
        }
 } //end of while get files

    // close the files
    fclose(sfile);
    fclose(file);
    fclose(output);
 } //end of if a=1
       else{
            a = 0;
            close(socket_d);
            }
 } //end of if timer
    
    this_time = clock();

    time_counter1 += (double)(this_time - last_time);

    last_time = this_time;

    if(time_counter1 > (double)(NUM_SECONDS1 * CLOCKS_PER_SEC))
    {
          time_counter1 -= (double)(NUM_SECONDS1 * CLOCKS_PER_SEC);
          b = 1;
          printf("b = %d\n", b);

    //Send Picture
    if(b == 1){

    socket_d = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_d < 0)
    {
        printf("Could not create socket\n");
    }

    server.sin_addr.s_addr = inet_addr("172.20.10.2");
    server.sin_family = AF_INET;
    server.sin_port = htons( 20111 );

    //Connect to remote server
    if (connect(socket_d, (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        printf("connect error\n");
        return 1;
    }
    printf("Connected\n");
    
    int pic_write = 0;
    int picture_write = 0;
    char picture_buffer[32];
    int lot_numb = 10;

    // Local date
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char date[64];
    strftime(date, sizeof(date), "%m/%d/%Y", tm); // 08/10/1994 format

    //Get Picture Size
    printf("Getting Picture Size\n");
    FILE *picture;
    picture = fopen("license.jpg", "r");
    int size;
    fseek(picture, 0, SEEK_END);
    size = ftell(picture);
    fseek(picture, 0, SEEK_SET);

    // Print command to string and send to server
    sprintf(picture_buffer, "INSERT INTO %d DATE %s PICTURE %d\n", lot_numb, date, size);
    picture_write = send(socket_d, picture_buffer, strlen(picture_buffer), 0);
    printf("%s", picture_buffer);

    // Send picture as byte array
    printf("Sending picture as byte array\n");
    char pic_buffer[size];
    while(!feof(picture)) {
    fread(pic_buffer, 1, sizeof(pic_buffer), picture);
    write(socket_d, pic_buffer, sizeof(pic_buffer));
    } //end of picture while loop
 } //end of b = 1
            else{
            b = 0;
            close(socket_d);
            }
 } //end of if loop to make b = 1

 } //end of timer while loop
  return 0;
} 

