#!/bin/bash

if [[ -z "cub3D" ]]; then
  echo -e "cub3D binary not found\n"
  exit 1
fi

CHECK=0

for file in "/assets/maps/valid_maps/"; do
  make && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-mismatched-frees=yes --track-fds=yes --trace-children=yes ./cub3D $file
  if [[ $? != 0 ]]; then
    echo "$file : KO"
    $CHECK = 1
  else
    echo "$file : OK"
  fi
done

for file in "/assets/maps/invalid_maps/"; do
  make && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-mismatched-frees=yes --track-fds=yes --trace-children=yes ./cub3D $file
  if [[ $? == 0 ]]; then
    echo "$file : KO"
    $CHECK = 1
  else
    echo "$file : OK"
  fi
done

#checker si on affiche uniquement error 

exit $CHECK

