#include "biba.h"


INT main(INT argc, LPSTR argv[]){
    INT status = 0;

    if (argc != 2){
        perror(E_INVALID_PARAMETER);
        status = FAIL;
    }
    else {
        INT checked = from_string_to_int_windows(argv[1]);
        LPSTR input;
        if (checked <= 0){
            perror(E_INVALID_NUMBER);
            status = FAIL;
        } else if ((input = get_string_from_input_windows())){
            write_n_sym_windows(input, (size_t) checked);
            free(input);
        } else{
            perror(E_EMPTY_STRING);
            status = FAIL;
        }
    }
    return status;
}


INT from_string_to_int_windows(LPSTR arg){
    INT number = 0;
    DWORD len = strlen(arg);
    for (INT i = 0; i < len; i++){
        if (!(isdigit(arg[i]))){
            number = - 1;
        }
    }
    if (number != - 1){
        sscanf(arg, "%d", &number);
    }
    return number;
}

void write_n_sym_windows(LPSTR src, DWORD n){
    HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD error_num = 0;
    WriteConsole(h_console, src, n, &error_num, NULL);
    if (error_num < 0){
        perror("Error occured");
        LPSTR message;
        DWORD error_num_2;
        HANDLE h_error = GetStdHandle(STD_ERROR_HANDLE);
        DWORD dwMessage_len = FormatMessage(
            FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
            NULL,
            GetLastError(),
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPSTR)&message,
            0,
            NULL);
        WriteConsole(h_error, message, sizeof(message) - 1, &error_num_2, NULL);
    }
}

LPSTR get_string_from_input_windows(){
    LPSTR result = NULL;
    char tmp_buff[1];
    DWORD flag = 1;
    DWORD len = 0;
    while(flag){
        HANDLE h_input = GetStdHandle(STD_INPUT_HANDLE);
        DWORD read_bites;
        ReadConsole(h_input, tmp_buff, 1, &read_bites, NULL);
        if (read_bites < 0){
            flag = 0;
            perror("Error occured");
            LPSTR message;
            DWORD error_num_2;
            HANDLE h_error = GetStdHandle(STD_ERROR_HANDLE);
            DWORD dwMessage_len = FormatMessage(
                FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
                NULL,
                GetLastError(),
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPSTR)&message,
                0,
                NULL);
            WriteConsole(h_error, message, sizeof(message) - 1, &error_num_2, NULL);
        }
        else if (tmp_buff[0] == '\n') flag = 0;
        else{
            result = (LPSTR) realloc(result, len + 1);
            result[len] = tmp_buff[0];
            len++;
        }
    }

    return result;
}
