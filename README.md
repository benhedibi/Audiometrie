# Patient2k19 


Is a database application that I have developped for a Hearing Loss Measurement Lab in North Africa. They were having some critical issues with the very aged software they were using (16 years old), a Software which was built around the old mighty Paradox Database. Some of the issues they were having are :

- Constant losses and corruptions of the database records.
- Random crashes which occur frequently while editing or adding new patient's records to the measurements database.
- The blob data storage was completely corrupted thus various functionalities were impossible to use without crashing the application.
- Sometimes whenever they add a new record : instead of getting appended, it just overwrites a random record in the database.
- Plus a lot of other weired bugs.

I was asked to build a new application from scratch in order to correct all the mentionned bugs as well as adding some brand new useful functionalities.

## What I did :

- Coded a custom <b>recovery</b> utility which allowed me to recover about <b>80%</b> of the corrupted <b>Paradox/</b> records. (Source code not included in this repository).
- Created a pretty simple but highly effective <b>Relational Database Engine</b> from scratch - <b>LillyDB</b> - tailored for the exclusive needs of the software. Custom database with multi-users support & privileges,Data Encryption & Compression,Incremental indexes and blob support etc..
- Coded a database import utility in order to import records from .csv files ( exported from paradox databases ) into <b>LillyDB</b> format.
- <b>Blob</b> support was implemented externally from the databases containers as simple files which have this naming scheme : <b>BLOB_TYPE_NAME</b> concatenated with the <b>Hexadecimal value</b> of the associated record index. Blob records can contain pictures,confidential medical observations or Facial recognition data.  
- No <b>SQL support</b> as I could have used <b>SQLite</b> for the whole project but I have implemented a primitive <b>indexing</b> & <b>caching</b> mechanisms, an implementation which allowed me to add records searching, filtering & complex statistiques functionalities with a fast lightning speed performance.
- <b>Facial recognition</b> support using <b>Luxand's FaceSDK</b> ( Source code not included in this repository as the <b>sdk</b> is a proprietary commercial product)



