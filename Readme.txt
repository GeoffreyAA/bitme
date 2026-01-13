BitMe
=====

BitMe is a bitrate calculator with a different, perhaps whimsical appearance.

The program goes back a long time. The first version, "The Bitrate Calculator," later BitMe, was written in secondary school (2003 or 2004). It was put together in Visual Basic and looked pretty, but I wanted something better. Later, learning C++, I rewrote it, helped by MFC, releasing version 2.1.1 on SourceForge in November 2007. In 2013, I wrote BitMe from scratch again; this had a sounder architecture but kept the old appearance. Then, in 2016, I tackled the challenge of adding support for any container or codec. Unfortunately, this work was incomplete and I did not touch it until 2021. So, cutting out the idea of working with any codec, and using an approximate method, I simplified the system, keeping the idea of various containers and adding more. It is working but will benefit from more tuning and containers.

I hope BitMe is of use to you.

Thanks,
Geoffrey


Notes
-----

The program comes with a default language of English and can be translated into others. Open the "English.lng" file in a plain-text editor, like Notepad, and translate all the words on the right-hand side of the equal-to (=) sign. Then, save it as another file, using UTF-8 encoding without the BOM, or byte-order mark. Lastly, rename the file to that of the language: "French.lng" for example. The extension must be ".lng" or the file will not be picked up. Language can be changed in Settings. Note that UTF-16 encoding will not work, and using the BOM is not advised; if the latter is used, the first string will simply be lost to the program. Plain ANSI encoding also works, but UTF-8, without the BOM, is recommended.

Only download BitMe from its official page (https://github.com/GeoffreyAA/bitme). If you got it from somewhere else, please be aware that I had no hand in that, and it could be modified or infected. Also, this is free software, so do not pay for it anywhere.