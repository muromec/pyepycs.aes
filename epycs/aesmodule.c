#include "rijndael.h"

#include <Python.h>


typedef struct {
    PyObject_HEAD
    u32 ks[60];
} PyAES_context;


static int
PyRC4_init(PyAES_context *self, PyObject *args, PyObject *kwds)
{
	char *key;
	int len;
	if (!PyArg_ParseTuple(args, "s#", &key, &len))
		return NULL;

	aes_256_setkey(key, self->ks);

	return 0;
}

static PyObject *
PyRC4_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    PyAES_context *self;

    self = (PyAES_context *)type->tp_alloc(type, 0);
    if (self == NULL)
        goto out;

out:
    return (PyObject *)self;

}

static PyObject * PyAES_crypt(PyAES_context* self, PyObject *data, int test) {

    char *pt_data = PyString_AsString(data);
    char ct_data[0x10];

    aes_256_encrypt(pt_data, &ct_data[0], self->ks);
    return PyString_FromStringAndSize(&ct_data[0], 0x10);
}


static PyMethodDef PyRC4_methods[] = {
	{"crypt", (PyCFunction)PyAES_crypt, METH_O,
        "crypt or decrypt object"},

   {NULL}  /* Sentinel */
};


static PyTypeObject PyAES_Type = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "epycs.rc4.PyAES_context",             /*tp_name*/
    sizeof(PyAES_context),             /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    0,//(destructor)RbusRoot_dealloc, /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
    "RC4 objects",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,		               /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    PyRC4_methods,             /* tp_methods */
    0, //RbusRoot_members,             /* tp_members */
    0, //RbusRoot_getseters,           /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)PyRC4_init,      /* tp_init */
    0,                         /* tp_alloc */
    PyRC4_new,                 /* tp_new */
};

static PyMethodDef module_methods[] = {
    {NULL}  /* Sentinel */
};

#ifndef PyMODINIT_FUNC	/* declarations for DLL import/export */
#define PyMODINIT_FUNC void
#endif
PyMODINIT_FUNC
initaes(void) 
{
    PyObject* m;

    if (PyType_Ready(&PyAES_Type) < 0)
        return;

    m = Py_InitModule3("epycs.aes", module_methods,
		    "Skepe AES bindings");

    if (m == NULL)
      return;

    Py_INCREF(&PyAES_Type);
    PyModule_AddObject(m, "AES", (PyObject *)&PyAES_Type);
}
