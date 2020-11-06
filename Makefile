# all : xftp
# .PHONY : all

# xftp: xftp.o common.o xftp-client.o
# 	gcc xftp.o common.o xftp-client.o -o xftp

# xftp.o: xftp.c common.c xftp-client.c
# 	gcc  xftp.c xftp-client.c common.c -o xftp.o

# xftp-client.o: xftp-client.c common.c
# 	gcc  xftp-client.c common.c -o xftp-client.o

# # xftpd: xftpd.o common.o
# # 	gcc xftpd.o common.o  -o xftpd

# # xftpd.o: xftp.c common.c
# # 	gcc xftpd.c common.c -o xftpd.o

# common.o: common.c
# 	gcc -c common.c -o common.o

# .PHONY: clean  
# clean:  
# 	rm -rf *.o xftp xftpd

all : xftp xftpd
.PHONY : all

xftp: xftp.o common.o xftp-client.o
	gcc xftp.o common.o xftp-client.o -o xftp

xftp.o: xftp.c
	gcc -c xftp.c -o xftp.o

xftp-client.o: xftp-client.c common.c
	gcc -c xftp-client.c -o xftp-client.o

xftpd: xftpd.o common.o
	gcc xftpd.o common.o -o xftpd

xftpd.o: xftp.c
	gcc -c xftpd.c -o xftpd.o

common.o: common.c
	gcc -c common.c -o common.o

.PHONY: clean  
clean:  
	rm -rf *.o xftp xftpd