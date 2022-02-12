/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "projeto.h"
#include <unistd.h>

void get_minor_and_major(int n, float * v, pair * res) {
    int i;
    float min, max;
    min = v[0];
    max = v[0];
    for (i = 1; i < n; i++) {
        if (v[i] < min) {
            min = v[i];
        }
        if (v[i] > max) {
            max = v[i];
        }
    }

    res->f = min;
    res->l = max;
}

bool_t
get_major_minor_100_svc(operand *argp, pair *result, struct svc_req *rqstp)
{
	bool_t retval;

	pair res;

	printf("%d\n", argp->n);

	// print argp.v array
    for (int i = 0; i < argp->n; i++) {
        printf("%f\n", argp->v[i]);
    }

	get_minor_and_major(argp->n, argp->v, &res);

	result = &res;

	retval = 1;

	return retval;
}

int
prog_100_freeresult (SVCXPRT *transp, xdrproc_t xdr_result, caddr_t result)
{
	xdr_free (xdr_result, result);

	/*
	 * Insert additional freeing code here, if needed
	 */

	return 1;
}
