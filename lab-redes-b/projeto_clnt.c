/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "projeto.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

enum clnt_stat 
get_major_minor_100(operand *argp, pair *clnt_res, CLIENT *clnt)
{
	return (clnt_call(clnt, GET_MAJOR_MINOR,
		(xdrproc_t) xdr_operand, (caddr_t) argp,
		(xdrproc_t) xdr_pair, (caddr_t) clnt_res,
		TIMEOUT));
}
