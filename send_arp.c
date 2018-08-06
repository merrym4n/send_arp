#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/ioctl.h>	// ioctl()

#include <net/if.h>	// struct ifreq, socket()

#include <netinet/ip.h>	// struct in_addr

#include <arpa/inet.h>	// inet_aton()


void Get_Mac(char *interface, unsigned char *Mac_Mine) {
	struct ifreq tmp;
	int s = socket(PF_INET, SOCK_STREAM, 0);
	int i=0;
	strcpy(tmp.ifr_name, interface);
	if(ioctl(s, SIOCGIFHWADDR, &tmp)) {
		printf("Couldn't get Mac Address!!\n");
		exit(-1);
	}
	memcpy(Mac_Mine, tmp.ifr_addr.sa_data, 6);
}

int main(int argc, char *argv[]) {
	char *interface;
	struct in_addr IP_Sender = {0,};
	struct in_addr IP_Mine = {0,};
	struct in_addr IP_Target = {0,};

	// If we're just using char, there is ffffff in the string.
	unsigned char Mac_Mine[6];
	unsigned char Mac_Target[6];

	int i;
	if(argc != 4) {
		printf("send_arp <interface> <sender ip> <target ip>\n");
		printf("send_arp eth0 192.168.10.2 192.168.10.1\n");
		return -1;
	}
	else
		for(i=0;i<argc;i++)
			printf("%d %s\n", i, argv[i]);

	interface = argv[1];
	inet_aton(argv[2], &IP_Sender);
	inet_aton(argv[3], &IP_Target);
	Get_Mac(interface, Mac_Mine);

	printf("My Mac is %02x", Mac_Mine[0]);
	for(i=1;i<6;i++)
		printf(":%02x", Mac_Mine[i]);
	printf("\n");
	
	return 0;
}
