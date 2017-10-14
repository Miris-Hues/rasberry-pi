#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>
#include <errno.h>


#define BUFFER_SIZE 1024
#define NO_SHELL 0
#define SUCCESS 1
#define TCP_PORT 22
#define ERROR -1
#define SHELL_INVOKE_ERROR 127
int touchSensor = 5;

void setup(void){
	pinMode(touchSensor,INPUT);

	if(wiringPiSetup() == -1){
		fprintf(stdout, "Unable to start wiringPi: %s\n",strerror(errno));
		exit(1);
	}
}

int loop(void){
		
	int touchValue = digitalRead(touchSensor);
	char * buf = malloc((size_t)(BUFFER_SIZE));
	
	if(touchValue == HIGH){
		system("raspistill -t 1000 -o cam.jpg");
		system("raspistill -o /home/pi/image.jpg");
		system("sudo pip install freeze");
		system("sudo pip install azure-storage");
		sprintf(buf, "python ./main.py %s","image.jpg");
		system(buf);
		//printf("a");
		return 1;
	}
}

int main (int argc, char * argv[]) {
	 
	int sysValue = system("sudo apt-get install -y python-dev");
	if(sysValue == SHELL_INVOKE_ERROR){
		printf("Shell Invoke Error");
		return SHELL_INVOKE_ERROR;
	}
	else if(sysValue == ERROR){
		printf("Error");
		return ERROR;
	}
	else if(sysValue == NO_SHELL){
		printf("Not Shell");
	}
	setup();
	while(1){
		loop();
	}

	return 0;
}
