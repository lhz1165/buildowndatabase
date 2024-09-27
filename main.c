#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct
{
    char *buffer;
    size_t buffer_length;
    ssize_t input_length;

} InputBuffer;

typedef enum
{
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum
{
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

typedef enum
{
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

char * stateTypeNames[]={"新增","查询"};
typedef struct
{
    StatementType type;
} Statement;

InputBuffer *initBuffer();
MetaCommandResult do_meta_command(InputBuffer *input_buffer);
void read_input(InputBuffer *input_buffer);
void close_input_buffer(InputBuffer *input_buffer);
void print_prompt();
PrepareResult prepare_statement(InputBuffer *input_buffer, Statement *statement);
void execute_statement(Statement *statement);
char* convert2Str(StatementType type);

// ssize_t getline(char **lineptr, size_t *n, FILE *stream);

int main(int argc, char const *argv[])
{
    InputBuffer *input_buffer = initBuffer();
    while (1)
    {
        print_prompt();
        read_input(input_buffer);
        if (input_buffer->buffer[0] == '.')
        {
            switch (do_meta_command(input_buffer))
            {
            case META_COMMAND_SUCCESS:
                /* code */
                break;
            case META_COMMAND_UNRECOGNIZED_COMMAND:
                printf("unrecognized command '%s' \n", input_buffer->buffer);

                break;
            default:
                break;
            }
        }

        Statement statement;
        switch (prepare_statement(input_buffer, &statement))
        {
        case PREPARE_SUCCESS:
            /* code */
            break;
        case META_COMMAND_UNRECOGNIZED_COMMAND:
        printf("Unrecognized keyword at start of '%s'.\n",input_buffer->buffer);
            break;
        default:
            break;
        }
        execute_statement(&statement);
        printf("Executed.\n");
    }
    return 0;
}

InputBuffer *initBuffer()
{
    InputBuffer *input_buffer = malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;
    return input_buffer;
}

void print_prompt()
{
    printf("db > ");
}

void read_input(InputBuffer *input_buffer)
{
    ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);
    if (bytes_read < 0)
    {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }
    // 忽略换行符
    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;
}

void close_input_buffer(InputBuffer *input_buffer)
{
    free(input_buffer->buffer);
    free(input_buffer);
}

MetaCommandResult do_meta_command(InputBuffer *input_buffer)
{
    if (strcmp(input_buffer->buffer, ".exit") == 0)
    {
        exit(EXIT_SUCCESS);
    }
    else
    {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

PrepareResult prepare_statement(InputBuffer *input_buffer, Statement *statement)
{
    printf("1statement->type: %s\n",convert2Str(statement->type));
    if (strncmp(input_buffer->buffer, "insert", 6) == 0)
    {
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }
    printf("2statement->type: %s\n",convert2Str(statement->type));
    if (strcmp(input_buffer->buffer, "select") == 0)
    {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }
printf("3statement->type: %s\n",convert2Str(statement->type));
    return PREPARE_UNRECOGNIZED_STATEMENT;
}

void execute_statement(Statement *statement)
{
    printf("statement->type: %s\n",convert2Str(statement->type));
    switch (statement->type){
    case (STATEMENT_INSERT):
        printf("This is where we would do an insert.\n");
        break;
    case (STATEMENT_SELECT):
        printf("This is where we would do a select.\n");
        break;
    }
}

char* convert2Str(StatementType type){
 switch (type)
    {
    case (STATEMENT_INSERT):
        return "新增";
    case (STATEMENT_SELECT):
        printf("This is where we would do a select.\n");
        return "查询";
    default:
        return "未知";
    }
}
