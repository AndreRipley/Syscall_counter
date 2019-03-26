#include "types.h"
#include "user.h"

int main(int argc, char** argv)
{
	if(argc<2){
		fprintf(stdout, "Usage: make child_1_tickets [child_2_tickets]...\n");
		exit();
	}
	fprintf(stdout, "Parent creation (pid %d)\n", getpid());

	struct pstat pinfo = {0};
	if (-1 == getpinfo(&pinfo)) {
		return 0;
		fprintf(1, "\n\t GET PINFO FAILURE\n");
	}

	int total = 0;
	for (int i = 1; i < argc; i++)
		total += atoi(argv[i]);
	fprintf(stdout, "Tickets made: %d\nTotal tickets: %d\n", total, total+pinfo.total_tickets);

	for (int i=1;i<argc;i++) {
		const int pid = fork();

		if (pid<0) {
			fprintf(stderr, "Failed to create child."); 
			exit();
		}
		if (!pid) {
			const int t = atoi(argv[i]);//number of tickets
			settickets(t);
			fprintf(stdout, "Child %d created with %d tickets\n", getpid(), t);
			fprintf(stdout, "Child %d exiting\n", getpid());
			exit();
		}
	}
	for (int i=1; i<argc; i++) {
		wait();
	}
	fprintf(stdout, "Parent exiting\n");
	exit();
}
