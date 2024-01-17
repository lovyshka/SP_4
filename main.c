#include "biba.h"


int main(int argc, char *argv[]) {
    unsigned short int status = OK;

    if (argc != 2){
        perror(E_INVALID_PARAMETER);
        status = FAIL;
    }
    else {
        int checked = from_string_to_int(argv[1]);
        char * input;
        if (checked <= 0) {
            perror(E_INVALID_NUMBER);
            status = FAIL;
        } else if ((input = get_string_from_input())) {
            write_n_sym(input, (size_t) checked);
            free(input);
        } else {
            perror(E_EMPTY_STRING);
            status = FAIL;
        }
    }
    return status;
}

int from_string_to_int(char * arg){
    int number = 0;
    size_t len = strlen(arg);
    for (int i = 0; i < len; ++i) {
        if (!(isdigit(arg[i]))){
            number = -1;
        }
    }
    if (number != -1) {
        sscanf(arg, "%d", &number);
    }
    return number;
}

void write_n_sym(char * src, size_t n){
    int error_num = write(0, src, n) < 0;
    if (error_num < 0){
        perror("Error occured");
        char * error_msg = strerror(error_num);
        write(2, error_msg, sizeof(error_msg) - 1);
    }
}

char * get_string_from_input(){
    char * result = NULL; //куда кладем результат
    char tmp_buff[1]; //куда считывает read
    unsigned short int flag = 1; //для цикла
    size_t len = 0; //длинна
    while (flag){
        ssize_t read_bites = read(0, tmp_buff, 1);
        if (read_bites < 0) {
            flag = 0;
            char *  error_msg = strerror(read_bites);
            perror("Error occured");
            write(2, error_msg, sizeof (error_msg) - 1);
        }
        else if (tmp_buff[0] == '\n') flag = 0;
        else{
            result = (char *) realloc(result, len + 1);
            result[len] = tmp_buff[0];
            len++;
        }
    }

    return result;
}
