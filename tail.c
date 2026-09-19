#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


#define MAX 10000

int main(int argc, char *argv[]){
	int fd, n;
	static char buf[MAX];
	
	int lines = 0;
	int start = 0;

	if(argc < 2){
		printf(1, "tail filename\n");
		exit();
	}

	fd = open(argv[1], O_RDONLY);

	if(fd < 0){
		printf(1, "tail: cannot open %s\n", argv[1]);
		exit();
	}

	n = read(fd, buf, MAX);

	close(fd);

	if(n < 0){
		printf(1, "read error\n");
		exit();
	}

	// count number of lines
	for(int i = 0; i < n; i++){
		if(buf[i] == '\n') lines++;
	}

	if(lines > 10){
		int count = 0;
		for(int i = n-1; i >= 0; i--){	
			if(buf[i] == '\n') count++;

			if(count == 10){
				start = i+1;
				break;
			}
		}
	}

	write(1, buf + start, n-start);
	exit();
}	
