#!/bin/bash

CUB3D_EXEC="../cub3D"
CHECK=0
VALIDS_MAPS="../assets/maps/valid_maps/"
INVALIDS_MAPS="../assets/maps/invalid_maps/"


if [[ ! -x "$CUB3D_EXEC" ]]; then
  echo -e "Error : cub3D binary not found.\n"
  exit 1
fi


run_parsing_test()
{
  local file="$1"
  local expected_result="$2"
  local leaks
  local success=1

  ./"$CUB3D_EXEC" "$file"
  cub3d_exit_code=$?
  valgrind_output=$(valgrind --leak-check=full \
    --show-leak-kinds=all \
    --track-origins=yes \
    --show-mismatched-frees=yes \
    --track-fds=yes \
    --error-exitcode=42 \
    "$CUB3D_EXEC" "$file" 2>&1)


  if [[ $expected_result == 0 && $cub3d_exit_code != 0 || ($expected_result != 0 && $cub3d_exit_code == 0) ]]; then
   success=0
  fi
  if [[ $(echo $valgrind_output | grep "All heap blocks were freed -- no leaks are possible" | wc -l) != 1 && $(echo valgrind_output | grep "ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)" | wc -l) != 1 ]]; then
   success=0
  fi
  if [[ $success == 1 ]]; then
    echo -e "$file : \033[0;32mOK\033[0m"
  else
    echo -e "$file : \033[0;31mKO\033[0m"
  fi
  echo ""
}

make -C ../

for file in "$VALIDS_MAPS"/*; do
  run_parsing_test $file 0
done

for file in "$INVALIDS_MAPS"/*; do
  run_parsing_test $file 
done


