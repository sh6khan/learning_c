#include <pthread.h>
#include <stdio.h>

struct char_print_param{
    char character;
    int count;
};

void* char_print(void* parameters){
    struct char_print_param* p = (struct char_print_param*) parameters;

    int i;
    for (i = 0; i < p->count; i++){
        printf("%c\n", p->character);
    }

    return NULL;
}

/* the main program */

int main(){
    pthread_t thread1_id;
    pthread_t thread2_id;

    struct char_print_param thread1_arg;
    struct char_print_param thread2_arg;

    thread1_arg.character = 'x';
    thread1_arg.count = 3;
    pthread_create(&thread1_id, NULL, &char_print, &thread1_arg); 

    thread2_arg.character = 'o';
    thread2_arg.count = 2;
    pthread_create(&thread2_id, NULL, &char_print, &thread2_arg);

    pthread_join(thread1_id, NULL);
    pthread_join(thread2_id, NULL);

    return 0;

}
