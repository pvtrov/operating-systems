//
// Created by mirabelka on 26.04.22.
//

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <pwd.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define ID 'S'

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

typedef struct {
    int id;
    int queue_id;
    int connection_id;
    bool connected;
    bool available;
} client;

client clients[10];
int server_queue;
int current_id = 1;


void send_message(int queue_id, message* message_){
    if(msgsnd(queue_id, message_, sizeof(message) - sizeof(long), 0) == -1){
        printf("cannot send this message\n");
        exit(1);
    }
}

void receive_message(int queue_id, message* message_, long type){
    if(msgrcv(queue_id, message_, sizeof(message) - sizeof(long), message_->mode, 0) == -1){
        printf("cannot receive message\n");
        exit(1);
    }
}

void delete_server(int queue){
    msgctl(queue, IPC_RMID, NULL);
}

char* get_path(){
    char* path = getenv("HOME");
    if (path == NULL){
        path = getpwuid(getuid()) -> pw_dir;
    }
    return path;
}

void handle_SIGINT(){
    printf("\nserver received SIGINT\n");
    exit(0);
}

void stop_server(){
    printf("stopping server\n");
    message message_;
    int client_queue;
    for (int i = 0; i < 10; i++){
        if (clients[i].connected){
            printf("stopping client, id: %d\n", i);
            client_queue = clients[i].queue_id;
            message_.mode = STOP;
            send_message(client_queue, &message_);
            receive_message(server_queue, &message_, STOP);
            printf("STOP received form client\n");
        }
    }
    delete_server(server_queue);
    printf("as you wanted, i've just stopped the server!\n");
}

void stop_sender(message* message_){
    printf("\nserver received STOP\n");
    message_->mode = STOP;
    int client_id = message_->sender_id;
    clients[client_id].connected = false;
}

void to_all(message* message_){
    int current_client = message_->sender_id;

    for (int i = 0; i < 10; i++){
        if (clients[i].id != 0 && clients[i].id != current_client){
            printf("sent message to: %d\n", clients[i].id);
            message new_message;
            sprintf(new_message.text, "%s", message_->text);
            new_message.sender_id = clients[i].id;
        }
    }
}

void init_client(key_t sender_id, pid_t pid){
    int i = 0;
    bool possible = false;
    while ( i < 10){
        if (clients[i].connected == false){
            possible = true;
            break;
        }else{
            i++;
        }
    }
    if (possible == false){
        printf("cannot add new client, sory\n");
        return;
    }
    char* path = getenv("HOME");
    key_t client_key = ftok(path, pid);
    int queue_client = msgget(client_key, IPC_CREAT | 0666);
    message message_;
    message_.mode = INIT;
    message_.sender_id = current_id;
    current_id++;

}

void to_one(message* message_){
    int current_client = message_->sender_id;
    message new_message;
    sprintf(new_message.text, "%s", message_->text);
    new_message.sender = current_client;
    printf("message sent\n");
}

void list_clients(message* message_){
    printf("-----------------------------\n");
    printf("listing active clients:\n");
    for (int i = 0; i < 10; i++){
        if (clients[i].available){
            printf("id: %d, queue id: %d, status: available\n", clients[i].id, clients[i].queue_id);
        }
    }
    printf("-----------------------------\n");
}

void pick_up_message(message* message_){
    switch (message_->mode) {
        case INIT:
            init_client(message_->sender_id, message_->queue_id);
            break;
        case STOP:
            stop_sender(message_);
            break;
        case TO_ALL:
            to_all(message_);
            break;
        case TO_ONE:
            to_one(message_);
            break;
        case LIST:
            list_clients(message_);
            break;
        default:
            printf("error with handling this message!\n");
            exit(1);
    }
}

int main(int args, char* argv[]){
    printf("hi, im server!\n");
    atexit(stop_server);  // ustawia ze ta funkcja ma sie wykonac przed zakonczeniem programu
    key_t key = ftok(get_path(), ID);
    if (key == -1){
        printf("cannot create queue\n");
        return -1;
    }
    server_queue = msgget(key, IPC_CREAT | IPC_EXCL | 0666);
    if (server_queue == -1){
        printf("cannot create queue\n");
        return -1;
    }
    printf("server queue id: %d\n", server_queue);
    printf("adding client... \n");
    for (int i = 0; i < 10; i++){
        clients[i].available = true;
        clients[i].connected = false;
    }
    printf("all clients added!\n");
    signal(SIGINT, handle_SIGINT);

    message message_;
    while (true){
        int message_size = sizeof(message) - sizeof(message_.mode);
        if (msgrcv(server_queue, &message_, message_size, -INIT-1, 0) == -1){
            printf("error with received maessage\n");
            return -1;
        }
        pick_up_message(&message_);
    }

}