#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

void head_n(char *file, int n){
	int fd, line_count = 0;
	fd = open(file, O_RDONLY);
	if(fd == -1){
		printf(1, "cannot open %s\n", file);
		return;
	}
	char ch;
	while(read(fd, &ch, 1) == 1){
		if(line_count == n) break;
		if(ch == '\n')	line_count++;
		write(1, &ch, 1);
	}
	close(fd);
}

int main(int argc, char *argv[]){
	int n = 10;

	if(argc < 2){
		printf(1, "Insufficient Arguments.\n");
		exit();
	}

	if(argc == 2){
		head_n(argv[1], n);
	}
	else if(argc == 3){
		if(argv[1][0] == '-'){
			if(argv[1][1] == 'n'){
				printf(1, "Unspecified number of lines\n");
				exit();
			}
			n = atoi(argv[1] + 1);
		}
		head_n(argv[2], n);
	}
	else if(argc == 4){
		if(argv[1][0] == '-'){
			n = atoi(argv[2]);
			head_n(argv[3], n);
		}
		else {
			printf(1, "Invalid arguments\n");
			exit();
		}
	}

	exit();
}
