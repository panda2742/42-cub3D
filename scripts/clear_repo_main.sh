echo -e "\e[48;2;10;240;10;m//////////////////////////////////\e[0m\n"
echo -e "\e[38;2;10;240;10;mCleaning repository for main...\e[0m\n"
echo -e "\e[48;2;10;240;10;m//////////////////////////////////\e[0m\n"

ls -la
rm -rf .dist
rm -rf .dist_bonus
rm -rf cub3D
rm -rf cub3D_bonus
make fclean
ls -la

echo -e "\e[48;2;10;240;10;m//////////////////////////////////\e[0m\n"
echo -e "\e[38;2;10;240;10;mRepo cleaned!\e[0m\n"
echo -e "\e[48;2;10;240;10;m//////////////////////////////////\e[0m\n"

echo -e "\e[48;2;10;240;240;m//////////////////////////////////\e[0m\n"
echo -e "\e[38;2;10;240;240;mPushing now...\e[0m\n"
echo -e "\e[48;2;10;240;240;m//////////////////////////////////\e[0m\n"

git status --porcelain
if [[ -n "$(git status --porcelain)" ]]; then
  git config user.name "github-actions[bot]"
  git config user.email "github-actions[bot]@users.noreply.github.com"
  git add -u
  git commit -m "ci: remove useless files"
  git push
else
  echo -e "\e[38;2;240;10;10;mNothing has to be committed.\e[0m\n"
fi
ls -la

echo -e "\e[48;2;10;240;240;m//////////////////////////////////\e[0m\n"
echo -e "\e[38;2;10;240;240;mEverything has been pushed!\e[0m\n"
echo -e "\e[48;2;10;240;240;m//////////////////////////////////\e[0m\n"