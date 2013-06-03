#include <Python.h>

static char print_args_docs[] = 
	"print_args(ia, db, sc)\n"
	":param ia: int\n"
	":param db: double\n"
	":param sc: string\n";

static PyObject *print_args(PyObject *self, PyObject *args)
{
	int ia;
	double db;
	char *sc;

	if (!PyArg_ParseTuple(args, "ids", &ia, &db, &sc)) {
		return NULL;
	}

	return Py_BuildValue("ids", ia, db, sc);
}

static char withargs_docs[] =
	"withargs(): test python C extension args";

static PyMethodDef withargs_funcs[] = {
	{"print_args", (PyCFunction)print_args, METH_VARARGS, print_args_docs},
	{NULL}
};

/* just test weather the function name MUST BE withargs */
// PyMODINIT_FUNC inithelloworld(void) failed!

PyMODINIT_FUNC initwithargs(void)
{
	Py_InitModule3("withargs", withargs_funcs, withargs_docs);
}
