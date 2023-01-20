#include "ssplit.h"

#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
//#include <sstream>
#include <memory>
#include <filesystem>
#include <queue>
#include <stdexcept>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>

//https://docs.python.org/3/c-api/stable.html#stable
////#define Py_LIMITED_API

//#define PY_SSIZE_T_CLEAN // only for 3.10 for the #-args
#include <Python.h>

using namespace std;
typedef queue<string> strfifo_t;

static PyObject* splitterException;

static PyObject *splitter(PyObject *self, PyObject *args) {

    char *inp		= NULL; 
    char *prefix	= NULL;


    if(!PyArg_ParseTuple(args, "ss", &prefix, &inp)) {
	PyErr_SetString(PyExc_ValueError, "ssplit: argument parse error.");
        return NULL;
	}

  if(NULL==inp) return NULL; //no error. 

  SentenceSplitter ssplit;
  string p_file = string(PREFIX_PRE) + string("en");

  try {
  if(NULL!=prefix){
	if(strlen(prefix)==2){
		p_file = string(PREFIX_PRE) + string(prefix);
		ssplit.load(p_file.c_str());
		} else {
		ssplit.load(prefix);
		}
	} else {
	ssplit.load(p_file.c_str());
	}
	} catch( exception &e ) {
		cerr << "ssplit exception: prefix file error: "
                     << e.what() << "!\n";
		PyErr_SetString(splitterException, const_cast<char*>(e.what()));
		return NULL;
	}

    string_view sv;
    strfifo_t fifo;
    string_view in = inp;
    PyObject *py_split_list = PyList_New(0);


    while(in.size()>0){
	sv = ssplit(&in);
	string sentence = string(sv.data(), sv.size());
	if(sentence.size()>0) {
		PyObject* py_string = Py_BuildValue("s", sentence.c_str());
		PyList_Append(py_split_list, py_string);
		}
	}

    if(PyList_Size(py_split_list)<1) return NULL;


return py_split_list;
}

  

static PyMethodDef splitterMethods[] = {
    {"splitter", splitter, METH_VARARGS, "Splits a text to sentences"},
    {NULL, NULL, 0, NULL}
};


static struct PyModuleDef splittermodule = {
    PyModuleDef_HEAD_INIT,
    "splitter",
    "Splits a text to sentences",
    -1,
    splitterMethods
};

//PyMODINIT_FUNC PyInit_splitter(void) {
//    return PyModule_Create(&splittermodule);
//}

PyMODINIT_FUNC PyInit_splitter(void) {
    PyObject *m;

    m = PyModule_Create(&splittermodule);
    if (m == NULL)
        return NULL;

    splitterException = PyErr_NewException("splitter.error", NULL, NULL);
    Py_XINCREF(splitterException);
    if (PyModule_AddObject(m, "error", splitterException) < 0) {
        Py_XDECREF(splitterException);
        Py_CLEAR(splitterException);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}

#define SPLITTER_MAIN_APP
#ifdef SPLITTER_MAIN_APP

int
main(int argc, char *argv[])
{
     // not available with #define Py_LIMITED_API
    wchar_t *program = Py_DecodeLocale(argv[0], NULL); 
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }

    /* Add a built-in module, before Py_Initialize */
    if (PyImport_AppendInittab("splitter", PyInit_splitter) == -1) {
        fprintf(stderr, "Error: could not extend in-built modules table\n");
        exit(1);
    }

    /* Pass argv[0] to the Python interpreter */
    Py_SetProgramName(program);

    /* Initialize the Python interpreter.  Required.
       If this step fails, it will be a fatal error. */
    Py_Initialize();

    /* Optionally import the module; alternatively,
       import can be deferred until the embedded script
       imports it. */
    PyObject *pmodule = PyImport_ImportModule("splitter");
    if (!pmodule) {
        PyErr_Print();
        fprintf(stderr, "Error: could not import module 'splitter'\n");
    }


    PyMem_RawFree(program); //not available with #define Py_LIMITED_API
    return 0;
}

#endif
