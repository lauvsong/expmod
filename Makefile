expmod: expmod.c
	gcc expmod.c -L.. -lcrypto  -I../include/crypto -o expmod

clean:
	rm expmod