# rot13

`rot13` reads from standard input or the named files,
moving each occurrence of a letter 13 places forward in the alphabet,
wrapping around past the end of the alphabet See also [ROT13](https://en.wikipedia.org/wiki/ROT13).

I wrote it partly for fun
and partly because I didn't want all the setgid stuff in [bsdgames](https://packages.debian.org/bsdgames) appearing in my security reports.

## Install

```
./autogen.sh
./configure
make check
sudo make install
```

## Use

```
$ rot13 README.md 
# ebg13

`ebg13` ernqf sebz fgnaqneq vachg be gur anzrq svyrf,
zbivat rnpu bppheerapr bs n yrggre 13 cynprf sbejneq va gur nycunorg,
jenccvat nebhaq cnfg gur raq bs gur nycunorg.
[...etc...]
```

## Documentation

```
man rot13
```

## License

Copyright © Richard Kettewell. 

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see [www.gnu.org/licenses](https://www.gnu.org/licenses/).
