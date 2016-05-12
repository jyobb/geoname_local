# geoname_local
Add a geonames database to islandora

# Requirements
Drush

# Installation
Install as usual.

Once you have installed the module you will need to download geonames data into the data folder and populate the database with the included drush script.

drush -v --user=admin --uri=http://islandorasev_dev.ca islandora --data="geonames" --filepath="data/CA.txt"

drush -v --user=admin --uri=http://islandorasev_dev.ca islandora --data="admin1codes" --filepath="data/admin1CodesASCII.txt"

Inforamtion about the Geonames data can be downloaded found at http://www.geonames.org/                                                                                                                                  

Dataset downloads can be found here: http://download.geonames.org/export/dump/                                                                                                                                           

You need to download both the a country file i.e.(CA.txt) and admin1CodesASCII.txt 

