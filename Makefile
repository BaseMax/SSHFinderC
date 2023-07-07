CC = cc
CFLAGS = -O2 -g -Wall -Werror

all: ssh_system_finder

ssh_system_finder:
	@echo "[+] Building project..."
	$(CC) $(CFLAGS) -o ssh_system_finder ./src/sshfinder.c

run: ssh_system_finder
	./ssh_system_finder

clean:
	@echo "[+] Cleaning..."
	rm -f ssh_system_finder