#!/bin/bash

if [[ $# -ne 2 ]]; then
  echo "Usage: $0 [IP_ADDRESS] [PORT]"
  exit 1
fi

IP_ADDRESS=$1
PORT=$2

# Liste des commandes FTP à tester
COMMANDS=("USER Anonymous" "PASS" "PWD" "CDUP" "CWD /" "TYPE I" "PASV" "LIST" "RETR" "PORT" "DELE" "STOR" "QUIT")

# Connexion Telnet au serveur
exec 3<>/dev/tcp/$IP_ADDRESS/$PORT

if [ $? -ne 0 ]; then
  echo "La connexion a échoué."
  exit 1
fi

read response <&3

# check if the response is 220
if [[ $response != 220* ]]; then
  echo "La connexion a échoué."
  exit 1
fi
echo "Connexion réussie. Envoi des commandes..."

# Envoi de chaque commande à travers la connexion Telnet
count=0
for command in "${COMMANDS[@]}"; do
  echo "Envoi de la commande: $command"
  echo "$command" >&3
  sleep 0.1
  read response <&3
  if [[ $response == 500* ]]; then
      echo "La commande $command a échoué."
  else
      ((count++))
  fi
done

# Affichage du nombre de commandes FTP implémentées
echo "Il y a $count/"${#COMMANDS[@]}" commandes implémentées."

# Fermeture de la connexion Telnet
echo "Fermeture de la connexion."
echo "QUIT" >&3
exec 3<&-
exec 3>&-
