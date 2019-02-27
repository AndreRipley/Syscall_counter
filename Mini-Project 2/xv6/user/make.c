#include "types.h"
#include "user.h"

int main(int argc, char** argv)
{
	if(argc<2){
		fprintf(stdout, "Usage: make child_1_tickets [child_2_tickets]...\n");
		exit();
	}
	fprintf(stdout, "Parent created (pid %d)\n", getpid());

	struct pstat pinfo = {0};
	if (-1 == getpinfo(&pinfo)) {
		return 0;
		fprintf(1, "\n\t GET PINFO FAILURE\n");
	}

	int total = 0;
	for (int i = 1; i < argc; i++)
		total += atoi(argv[i]);
	fprintf(stdout, "Children made: %d\nTotal tickets: %d\n", total, total+pinfo.total_tickets);
	fprintf(stdout, "Processes:\n");
	fprintf(stdout, "-------------\n");
	for (int i=1;i<argc;i++) {
		const int pid = fork();


		if (pid<0) {
			fprintf(stdout, "Failed to create child."); 
			exit();
		}
		if (!pid) {
			const int t = atoi(argv[i]);//number of tickets
		
			settickets(t);
			const int ticket_10=t*10; //tickets*10

			const int stride = 1000/ticket_10;

			fprintf(stdout, "Child pid:%d created with %d tickets\n", getpid(), ticket_10);
			fprintf(stdout, "Stride %d\n", stride);
			//fprintf(stdout, "Child %d exiting\n", getpid());
			fprintf(stdout, "Pass 1\n");
			exit();
		}
	}

	for (int i=1; i<argc; i++) {
		wait();
	}

	fprintf(stdout, "Parent exiting\n");
	exit();
}

