# Music config USB storage

Project om de muziek configuratie op een USB stick de laden/saven.
Bedoeld voor- en getest met een Teensy 4.1.

## Files

Dit is het nut van de bestanden in dit repository:
1. `usb_config_storage.ino`: Dit is de voorbeeld code die je in je Arduino project kunt
   gebruiken. Zou voor zichzelf moeten spreken. Wat je moet doen is een MusicConfig object
   vullen met de waardes van de knoppen/sequencer.
   ```c
   MusicConfig config;
   config.synth_notes[0] = 1;
   config.synth_notes[1] = 0;  // 0 kun je bijvoorbeeld gebruiken voor geen noot
   ...
   config.drum_notes[0][0] = 1;
   config.drum_notes[0][1] = 0;
   ```
   Die config pass je dan in de de save() functie. Voor load kun je gewoon een lege config
   erin gooien zoals in de voorbeeld code.
2. `main_on_host.cpp` en `hal.h`: Die Arduino IDE is tering traag met compilen, dus ik
   wilde ook een versie die ik gewoon met gcc kon compilen. Zo kan ik sneller testen en
   debuggen. Deze files kun je in principe negeren. Mocht je het willen runnen:
    ```bash
    g++ *.cpp -o main -std=c++11
    ./main.exe
    ```
    Als je van die `hal.h` af wilt moet je even een replace-all doen voor `log_print` naar
    `Serial.printf`.
3. `example_config.txt`: Hulp bestandje om op de USB stick te zetten om te testen.
4. `music_config.*`: Bevat de struct om de data van een project in op te slaan.
5. `music_config_manager.*`: Bevat de code om die music_config te laden en schrijven naar
   de USB stick.
6. `usb_drive.*`: Bevat de code om de USB stick te detecteren en te lezen/schrijven.

## Note over formatting van de USB stick

Ik heb wat gedoe gehad met m'n USB stick. Zie [deze thread](https://forum.pjrc.com/threads/73275-USBHost_t36-h-Unable-to-initialize-filesystem-with-SanDisk-drive?p=329513) voor meer info.

Als je problemen hebt om het filesystem correct te laden doe dan het volgende:
1. Open de Windows Disk Management tool
2. Verwijder de bestaande partities/volumes van de USB stick
3. Maak een nieuwe FAT partitie aan. FAT32, FAT16 of exFAT zou moeten werken, ik heb FAT32 gebruikt.

Het is blijkbaar belangrijk dat er een Master Boot Record (MBR) op de USB stick staat.
Simpelweg een bestaand volume formatteren werkt niet. Je moet echt de partitie verwijderen.
Mocht dit het nog niet fixen probeer dan de diskpart tool met mijn instructies uit
bovenstaande thread.
