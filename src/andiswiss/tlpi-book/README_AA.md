# tlpi-book -- Installation process

I (AndiSwiss) did follow the following steps in order to 
get tlpi-book to work:

(as described on slide 6 on https://github.com/tamberg/fhnw-syspr/blob/master/03/Syspr03FileIO.pdf)

```bash
cd src/andiswiss/
apt-get install wget
wget http://man7.org/tlpi/code/download/tlpi-180725-book.tar.gz --no-check-certificate
tar xfzmv tlpi-180725-book.tar.gz

# build the project:
cd tlpi-book
make
```

NOTES:
- `sudo ...` was not necessary, since I'm root
- `apt-get install libcap-dev` was not necessary; it was already up to date
- `apt-get install libacl1-dev` was not necessary; it was already up to date



After that, you can run individual apps, e.g. 
```bash
cd time
./calendar_time
```

