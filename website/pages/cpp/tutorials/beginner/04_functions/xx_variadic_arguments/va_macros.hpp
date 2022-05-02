// magic type representing a set of variadic arguments
typedef /* unspecified */ va_list;

// read variadic arguments into ap, parm_n must be the name of the parameter before ...
void va_start(va_list ap, parm_n);

// obtain the next parameter from ap, assuming it has type T
T va_arg(va_list ap, T);

// end traversal of the variadic argument list
void va_end(va_list ap);

// copy variadic arguments from src to dest
void va_copy(va_list dest, va_list src);
