all:arp_send

arp_send:arp_send.o
	gcc -o send_arp send_arp.o -lpcap

arp_send.o:
	gcc -c -o send_arp.o send_arp.c

clean:
	rm -rf send_arp
	rm -f *.o
