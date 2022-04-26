//
// Created by mirabelka on 26.04.22.
//

#include <stdio.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>

#define ID 'S'
#define CLIENT_ID getpid()

#define STOP 1
#define TO_ALL 2
#define  TO_ONE 3
#define LIST 4
#define INIT 5

typedef struct {
    long mode;
    char text[256];
    pid_t sender;
    int queue_id;
    int sender_id;
    int to_connect_id;
} message;


int client_queue;
int id;
int server_queue;


void send_message(int queue_id, message* message_){
    if(msgsnd(queue_id, message_, sizeof(message) - sizeof(long), 0) == -1){
        printf("cannot send this message\n");
        exit(1);
    }
}

char* get_path(){
    char* path = getenv("HOME");
    if (path == NULL){
        path = getpwuid(getuid()) -> pw_dir;
    }
    return path;
}

void * delete_client(int queue){
    msgctl(queue, IPC_RMID, NULL);
}

void receive_message(int queue_id, message* message_, long type){
    if(msgrcv(queue_id, message_, sizeof(message) - sizeof(long), message_->mode, 0) == -1){
        printf("cannot receive message\n");
        exit(1);
    }
}

void send_STOP(){
    printf("client sent STOP\n");
    message message_;
    send_message(server_queue, &message_);
    msgctl(client_queue, IPC_RMID, NULL);
    exit(0);
}

bool check(){
    struct timeval timeval_;
    fd_set fds;
    timeval_.tv_sec = 1;
    timeval_.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    select(STDIN_FILENO + 1, &fds, NULL, NULL, &timeval_);
    return FD_ISSET(0, &fds);
}

void to_one(int current_id){
    char buffer0[256];
    char buffer1[256];
    printf("give me message to pass:\n");
    scanf("%c", buffer0);
    printf("give me id another user:\n");
    scanf("%c", buffer1);
    int id = atoi(buffer1);
    message message_;
    message_.mode = TO_ONE;
    message_.sender_id = current_id;
    message_.queue_id = id;
    strcpy(message_.text, buffer0);
    printf("message was sent\n");
}

bool is_empty(int queue){
    struct msqid_ds buffer;
    msgctl(queue, IPC_STAT, &buffer);
    if (buffer.msg_qnum != 0) {
        return false;
    } else {
        return true;
    }
}

void send_list(){
    printf("client sent list\n");
    message message_ = {.mode = LIST};
    send_message(server_queue, &message_);
}

void to_all(int id){
    message message_;
    char buffer[256];
    message_.mode = TO_ALL;
    message_.queue_id = id;
    printf("give me message to pass:\n");
    scanf("%c", buffer);
    strcpy(message_.text, buffer);
    printf("send all messages!\n");
}

int main (){
    printf("hi, im client\n");
    signal(SIGINT, send_STOP);
    atexit(delete_client(client_queue));
    key_t server_key = ftok(get_path(), ID);
    if (server_key == -1){
        printf("cannot generate key\n");
        return -1;
    }
    server_queue = msgget(server_key, IPC_CREAT);
    if (server_queue == -1){
        printf("cannot create server queue\n");
        return -1;
    }
    printf("server queue: %d\n", server_queue);
    key_t client_key = ftok(get_path(), CLIENT_ID);
    if (client_key == -1){
        printf("cannot create client key\n");
        return -1;
    }
    client_queue = msgget(client_key, IPC_CREAT | IPC_EXCL | 0666);
    if (client_queue == -1){
        printf("cannot create client queue\n");
        return -1;
    }
    printf("client queue id: %d\n", client_queue);

    message message_ = {.queue_id = client_queue, .mode = INIT};
    send_message(server_queue, &message_);
    message received_message;
    receive_message(client_queue, &received_message, INIT);
    printf("--client id--\n%d\n\n", received_message.sender_id);
    id = received_message.sender_id;

    char buffer[256];
    while(true){
        if (check()){
            fgets(buffer, 256, stdin);
            if (strcmp("LIST\n", buffer) == 0){
                send_list();
            }else if(strcmp("STOP\n", buffer) == 0){
                send_STOP();
                exit(0);
            }else if(strcmp("ALL\n", buffer) == 0){
                to_all(client_queue);
            }else if(strcmp("ONE\n", buffer) == 0){
                to_one(client_queue);
            } else {
                printf("i got the message\n");
            }
        }
        sleep(1);
    }

}