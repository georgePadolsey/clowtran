#include "lowtran7.1.cpp"
#include <time.h>
#include <stdio.h>
#include <iostream>

#define PY_SSIZE_T_CLEAN
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <numpy/arrayobject.h>

static PyObject *run(PyObject *self, PyObject *args)
{

    struct timespec start
    {
    }, end{};

    long model;
    long itype;

    if (!PyArg_ParseTuple(args, "ll", &model, &itype))
    {
        return nullptr;
    }

    clock_gettime(CLOCK_MONOTONIC, &start);

    LOWTRAN_Card1 card1 = {.model = model, .itype = itype, .im = 1};
    LOWTRAN_Card2 card2 = {};
    LOWTRAN_Card3 card3 = {.h1 = 5, .h2 = 10, .range = 10};

    LOWTRAN_ResultBuffer buf{};

    _runLowtran(&buf, &card1, nullptr, nullptr, &card2, nullptr, nullptr, nullptr, nullptr, &card3, nullptr, nullptr, nullptr);

    clock_gettime(CLOCK_MONOTONIC, &end);

    const npy_intp dims[2] = {
        buf.length / 2, 2};

    // PyArray_SimpleNew allocates the memory needed for the array.
    PyObject *arr = PyArray_SimpleNewFromData(2, dims, NPY_FLOAT, (void *)buf.data);

    // perhaps needed?
    // PyArray_ENABLEFLAGS((PyArrayObject *)arr, NPY_ARRAY_OWNDATA);
    /* do work */

    return arr;
}
static PyMethodDef SpamMethods[] = {
    {"run", run, METH_VARARGS,
     "Execute a basic test."},
    {nullptr, nullptr, 0, nullptr} /* Sentinel */
};

static struct PyModuleDef clowtran_module = {
    PyModuleDef_HEAD_INIT,
    "clowtran", /* name of module */
    NULL,       /* module documentation, may be NULL */
    -1,         /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    SpamMethods};

PyMODINIT_FUNC
PyInit_clowtran(void)
{
    // @see https://scipy-lectures.org/advanced/interfacing_with_c/interfacing_with_c.html
    PyObject *module;
    module = PyModule_Create(&clowtran_module);
    if (module == NULL)
        return NULL;
    import_array();
    if (PyErr_Occurred())
        return NULL;
    return module;
}
