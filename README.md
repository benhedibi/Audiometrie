# Patient2k19 


Is a database application that I have developped for a Hearing Loss Measurement Lab in North Africa. They were having some critical issues with the very aged software they were using (16 years old), a Software which was built around the old mighty Paradox Database. Some of the issues they were having are :

- Constant losses and corruptions of the database records.
- Random crashes which occur frequently while editing or adding new patient's records to the measurements database.
- The blob data storage was completely corrupted thus various functionalities were impossible to use without crashing the application.
- Sometimes whenever they add a new record : instead of getting appended, it just overwrites a random record in the database.
- Plus a lot of other weired bugs.

I was asked to build a new application from scratch in order to correct all the mentionned bugs as well as adding some brand new useful functionalities.

## What I did :

- Coded a custom recovery utility which allowed me to recover about 80% of the corrupted Paradox records. (Source code not included in this repository).
- Created a pretty simple but highly effective Relational Database Engine from scratch / LillyDB / tailored for the exclusive needs of the software. Custom database with multi-users support & privileges,Data Encryption & Compression,Incremental indexes and blob support etc..
- Coded a database import utility in order to import records from .csv files ( exported from paradox databases ) into LillyDB format.
- Blob support was implemented externally from the databases containers as simple files which have this naming scheme : BLOB_TYPE_NAME concatenated with the Hexadecimal of the associated record index. Blob records may contain pictures,confidential medical observations or Facial recognition data.  
- No SQL support as I could have used SQLite for the whole project but I have implemented a primitive indexing & caching mechanisms, an implementation which allowed me to add records searching, filtering & complex statistiques functionalities with a fast lightning speed performance.
- Facial recognition support using Luxand's <b>FaceSDK</b>



