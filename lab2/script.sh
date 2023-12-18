#!/bin/bash -e

SHARED="/shared"
LOCK_FILE="/shared/lock"
CONTAINER_ID=$(od -An -N4 -tu4 /dev/urandom)
FILE_INDEX=1

getFilename() {
  local index=1
  while true; do
    filename=$(printf "%03d" $index)
    if [ ! -f "$SHARED/$filename" ]; then
      break
    fi
    ((index++))
  done
}

createFile() {
  exec {fd}>$LOCK_FILE
  flock "$fd"

  getFilename
  echo "$CONTAINER_ID $FILE_INDEX" > "$SHARED/$filename"

  flock -u "$fd"

  echo "$CONTAINER_ID created $filename"
  ((FILE_INDEX++))
}

deleteFile() {
  text=$(<"$SHARED/$filename")
  rm -f "$SHARED/$filename"
  echo "$CONTAINER_ID deleted $filename : $text"
}

while true; do
  createFile
  sleep 1
  deleteFile
done
