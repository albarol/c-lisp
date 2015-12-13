
#include <utils.h>

clisp_chunk_t*
clisp_utils_load_script(char* filename, clisp_env_t* env) {
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    size_t read;

    clisp_chunk_t* result = NULL;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        result = clisp_chunk_error("Invalid filename");
    }
    else {
        clisp_expr_t* call = NULL;
        while ((read = getline(&line, &len, fp)) != -1) {
            clisp_process(line, env, false);
        }

        fclose(fp);
        if (line)
            free(line);

        result = clisp_chunk_nil();
    }

    return result;
}