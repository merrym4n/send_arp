#include <stdio.h>

char GetMac(char *interface) {
	struct ifreq tmp;
	char MacMine[6];
	int s = socket(PF_INET, SOCK_STREAM, 0);

	strcpy(tmp.ifr_name, interface);
	if(ioctl(s, SIOCGIFHWADDR, &tmp)) {
		printf("Couldn't get Mac Address!!\n");
		exit(-1);
	}
	memcpy(MacMine, tmp.ifr_addr.sa_data, 6);

	return MacMine;
}

int main(int argc, char *argv[]) {
	char *interface;
	char MacMine[6];

	MacMine = GetMac(interface);
	return 0;
}