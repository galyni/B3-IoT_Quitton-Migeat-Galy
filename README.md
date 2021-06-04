# B3-IoT

## Architecture

Carte centrale : ESP8266.

Capteur : capteur de mouvements SR501.

Actionneur : buzzer pyéloélectrique.

Branchements : à l'aide d'une breadboard. Les éléments sont compatibles avec le 3.3V fourni par notre carte.
Leurs ports de données sont connectés à des ports de la carte, ce qui permet de lire ou d'écrire des données.


Au centre de l'architecture, nous avons mis en place un broker MQTT et un serveur Node-RED.

Enfin, nous avons créé un site Web élémentaire comprenant quelques boutons et capable de faire des requêtes GET sur le serveur Node-RED.

Les circuits de communication possible entre ces éléments étaient les suivants :

- Quand un mouvement est détecté par le capteur, l'ESP publie "true" sur le topic "motion" du broker MQTT et déclenche une sonnerie.
- Le site Web propose trois boutons : "turn off alamr", "activate sensor", "deactivate sensor".
- Ces boutons appellent des méthodes qui font des requêtes GET sur l'url du serveur Node-RED. En fonction de l'url et des paramètres fournis
dans l'url, un node crée un objet message MQTT avec les détails nécessaires pour son interprétation par la carte.
- La carte est abonnée à deux topics sur le broker : alarm et sensor. Sensor sert à désactiver complètement la détection de mouvements,
Alarm sert à couper l'alarme sans désactiver la détection (un nouveau mouvement la déclenchera à nouveau.


## Perspectives

Envoi des notifications ou de SMS sur le téléphone de l'utilisateur.

Tourelle de neutralisation composée de servo-moteurs et d'un lanceur de fléchettes anesthésiantes.
Nécessite pour fonctionner d'utiliser plusieurs capteurs de mouvements capables de fournir une direction précise, afin de trianguler la position de l'intrus.





