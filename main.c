#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


typedef struct {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;

} InputBuffer;

InputBuffer* initBuffer(){
    InputBuffer* input_buffer = malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;
    return input_buffer;

}

int main(int argc, char const *argv[])
{
    while (1)
    {
        
    }
    return 0;
}
