#include <stdio.h>
#include <stdlib.h>
#include <Python.h>

void nl_processor(FILE file); // ideally, put this in 'main.h' file

int main(int argc, char *argv[]) 
{

    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }

    Py_SetProgramName(program);  // optional
    Py_Initialize();

    wchar_t *args[argc];
    for (int i = 0; i < argc; i++) {
        args[i] = Py_DecodeLocale(argv[i], NULL);
    }

    PySys_SetArgv(argc, args);

    FILE *py_file = NULL;
    py_file = fopen("./main.py", "r");

    if (py_file != NULL) {
        PyImport_ImportModule("bs4");
        PyImport_ImportModule("requests");
        PyRun_SimpleFile(py_file, "main");
        Py_Finalize();
        PyMem_RawFree(program);
    }

    else {
        printf("Fail to open Python file. Please, check if it exists...");
        return 1;
    }

    FILE *source = NULL;
    source = fopen("content.txt", "r");
    nl_processor(*source);    

    printf("\n*** Task completed! ***");
    return 0;
}

void nl_processor(FILE source)
{
    printf("-> Beginning NLP...\n");
    // do some complicated NLP here...
    // save results to a file
    // or whatever... :)
    sleep(2); // simulate 2 seconds of processing
    printf("\n-> NLP completed.\n");
}
