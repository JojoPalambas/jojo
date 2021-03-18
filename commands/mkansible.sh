#!/bin/sh

GREEN='\033[0;32m'
RED='\033[0;31m'
RESET='\033[0m'

OK="[${GREEN}OK${RESET}]"
KO="[${RED}KO${RESET}]"

BASE=$PWD

if [ $# -gt 0 ]; then
    BASE="$PWD/$1"
fi

if [ ! -e $BASE ]; then
  echo
  echo The given path does not exist!
  echo
  exit 1
fi

read -p "New project folder name: " FOLDER
echo

while [ -z $FOLDER ]; do
  echo "${KO} You must give folder name!"
  read -p 'New project folder name: ' FOLDER
  echo
done

echo "${OK} The new Ansible project will be in $BASE/$FOLDER"
echo

read -p 'Inventory file name (00_inventory.yml): ' INVENTORY
echo

if [ -z $INVENTORY ]; then
  INVENTORY='00_inventory.yml'
fi

read -p 'Playbook file name (01_playbook.yml): ' PLAYBOOK
echo

if [ -z $PLAYBOOK ]; then
  PLAYBOOK='01_playbook.yml'
fi

read -p 'Playbook name: ' PLAYBOOK_NAME
echo

mkdir "$BASE/$FOLDER"
echo "${OK} + DIR $BASE/$FOLDER created"

mkdir "$BASE/$FOLDER/host_vars"
echo "${OK} + DIR $BASE/host_vars created"
mkdir "$BASE/$FOLDER/group_vars"
echo "${OK} + DIR $BASE/group_vars created"

touch "$BASE/$FOLDER/$INVENTORY"
echo "all:" >> "$BASE/$FOLDER/$INVENTORY"
echo "  children:" >> "$BASE/$FOLDER/$INVENTORY"
echo "${OK} + FIL $BASE/$FOLDER/$INVENTORY created"

touch "$BASE/$FOLDER/$PLAYBOOK"
echo "- name: $PLAYBOOK_NAME" >> "$BASE/$FOLDER/$PLAYBOOK"
echo "  hosts:" >> "$BASE/$FOLDER/$PLAYBOOK"
echo "  vars:" >> "$BASE/$FOLDER/$PLAYBOOK"
echo "${OK} + FIL $BASE/$FOLDER/$PLAYBOOK created"
