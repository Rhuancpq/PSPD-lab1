/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "projeto.h"
#include <math.h>
#include <pthread.h>

typedef struct {
	char * host;
	operand * argp;
} thread_arg;


void * get_major_minor_100_thread (void * args) {
	thread_arg * arg = (thread_arg *) args;
	pair * result = (pair *) malloc(sizeof(pair));

	CLIENT *clnt;
	enum clnt_stat retval;
	
	printf("Calling: %s...\n", arg->host);


#ifndef	DEBUG
	clnt = clnt_create (arg->host, PROG, VERSAO, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (arg->host);
		pthread_exit (NULL);
	}
#endif
	
	retval = get_major_minor_100 (arg->argp, result, clnt);

	if (retval != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif

	pthread_exit (result);
} 


void
prog_100(int hosts_size, char **hosts)
{
	CLIENT *clnt;
	enum clnt_stat retval_1;
	pair result_1;
	operand  get_major_minor_100_arg;
	
	float v[10];

	for (int i = 0; i < 10; i++) {
		v[i] = (i - 5) * (i - 5);
	}

    for (int i = 0; i < 10; i++) {
        v[i] = sqrt(v[i]);
    }

	operand * args = malloc(sizeof(operand) * hosts_size);
	pair ** results = malloc(sizeof(pair *) * hosts_size);

	// split the array in args

	int items_per_thread = 10 / hosts_size;
	int items_left = 10 % hosts_size;

	for (int i = 0; i < hosts_size; i++) {
		if (i == hosts_size - 1) {
			args[i].n = items_per_thread + items_left;
			for (int j = 0; j < args[i].n; j++) {
				args[i].v[j] = v[i * items_per_thread + j];
			}
		} else {
			args[i].n = items_per_thread;
			for (int j = 0; j < args[i].n; j++) {
				args[i].v[j] = v[i * items_per_thread + j];
			}
		}
		
	}

	thread_arg * t_args = malloc(sizeof(thread_arg) * hosts_size);

	for (int i = 0; i < hosts_size; i++) {
		t_args[i].host = hosts[i];
		t_args[i].argp = &args[i];
	}

	// create threads

	pthread_t * threads = malloc(sizeof(pthread_t) * hosts_size);

	for (int i = 0; i < hosts_size; i++) {
		pthread_create(&threads[i], NULL, get_major_minor_100_thread, &t_args[i]);
	}

	// join threads

	for (int i = 0; i < hosts_size; i++) {
		pthread_join(threads[i], (void **) &results[i]);
	}


	if (hosts_size == 1) {
		printf("Minor: %f, Major: %f\n", results[0]->f, results[0]->l);

		// free memory
		free(args);
		free(results);
		free(threads);

		return;
	}

	// call one host again with the results merged

	get_major_minor_100_arg.n = hosts_size * 2;

	for (int i = 0; i < hosts_size; i++) {
		get_major_minor_100_arg.v[i * 2] = results[i]->f;
		get_major_minor_100_arg.v[i * 2 + 1] = results[i]->l;
	}

	// call the host

#ifndef	DEBUG
	clnt = clnt_create (hosts[0], PROG, VERSAO, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (hosts[0]);
		pthread_exit (NULL);
	}
#endif

	retval_1 = get_major_minor_100 (&get_major_minor_100_arg, &result_1, clnt);

	if (retval_1 != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}

	printf("Minor: %f, Major: %f\n", result_1.f, result_1.l);

	// destroy threads



	for (int i = 0; i < hosts_size; i++) {
		free(results[i]);
	}
	free(args);
	free(results);
	free(threads);

	// destroy client


#ifndef	DEBUG
	clnt_destroy (clnt);
#endif

}


int
main (int argc, char *argv[])
{

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}

	char ** hosts = malloc(sizeof(char*)*(argc-1));

	for (int i = 1; i < argc; i++) {
		hosts[i-1] = argv[i];
	}

	prog_100 (argc-1, hosts);
exit (0);
}
