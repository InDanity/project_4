In this directory, you should write the program `scheduler.c` and compile it into the binary `scheduler` (e.g., `gcc -o scheduler scheduler.c -Wall -Werror`). You should do it inside the Ubuntu machine you have setup, as grading will be done so inside the Ubuntu.

After doing so, you can run the tests from this directory by running the
`./run_tests.sh` script. If all goes well, you will see standard output that indicate that all tests are passed.

Note that the test cases are expecting exact matches in string formatting and whitespace. To confirm if that is the cause of any mismatch, you can change the run_tests.sh program to use "--ignore-all-space" on the lines with the diff command to see if they then pass. If so, you probably have an extra space somewhere, perhaps before the newline character.

Passing all tests are not sufficient to obtain all points for this assignment. As an example, any assignment in which hardcodes the expected output to pass the test case will lead to point deductions.


10/04/23

Making the basic layout of the project:
	- Using int main(int argc, char *argv[]) to get all arguments.

Made Makefile, tried to get program to run w/o full functionality
	- Kept running into segmentation fault
	- Tried to debug using the coredump file like in project0
		- This said issue was with "feof":
			Program terminated with signal SIGSEGV, Segmentation fault.
			#0  _IO_feof (fp=0x0) at ./libio/feof.c:35
			35      ./libio/feof.c: No such file or directory.
		- Maybe we are not including the right libraries??
		- No its def in <stdio.h> according to the man pages...
	- Uh so tried to comment out the whole feof while loop and still and running into seg fault??
	- I'm gonna guess it's an issue with the command line args which we should def fix asap
	- Ok no its an issue with proccessing the job file it works fine without anything to do w that

Trying to debug jobfile thing
	- Let's uncomment line by line until something breaks
	- OKAY so fclose(fd); singlehandedly caused the segmentation fault! now ??? find out why?
	- Let's try the while loop without fclose??
	- No ok that also causes a segmentation fault uh oh
		- Line by line again??
		- Is this a waste of time maybe I should just go to office hours lol
		- It's fine I'll work for a little longer
		- So the problem is with the file -- maybe it's not being opened correctly?
		- NO MY JOBFILE NAME WAS MISPELLED YOU'RE JOKING
		- wow
		- that's embarrassing
		- I mean we can add a check for that by making sure the file pointer isn't null before proceeding
		- Let's do that
		- Sweet ok that's not ever happening again (for this project...) (hopefully.....) (at least uncaught......)

Now back to trying to get partial functionality running
	- Line by line uncommenting
	- Okay yeah so our only problem now is 'int rc = getLine(buffer, 99, fd);
	- No way is this also mispelled???
	- No phew
	- But wait now idk what the issue is still :/
	- maybe an office hours question tbh... not sure w the docs what's wrong

Maybe try to create nodes now?
	- Cool I think I created the initial node that listHead points to
	- Now need to figure out how to add to end of list 


10/06/23

Initialized buffer properly, fixing all previous issues mentioned in the prior log.
	- Did it as a pointer, not a plain char array. Also removed some uneeded if-statements.