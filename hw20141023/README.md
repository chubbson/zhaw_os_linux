#check ur internet connection 
. dhclient -r
. dhclient

# getting fedora 17 source
$ yum install kernel-deve kernel-tools kernel-headers
$ ls -l /usr/src/kernel/
$ cd 3.9.10-100.fc17.i686
