https://selectel.ru/blog/tutorials/what-is-git-push-and-how-to-use-it/
```bash
git clone git@github.com:ritchie229/WorkSpace.git

git init

git remote add LearnLinux git@github.com:ritchie229/WorkSpace.git
git add .
git add LearnLinux/CentOS=to-domain.txt

git config --global user.email "rishat.mukhtarov@gmail.com"
git config --global user.name "ritchie229"

git commit -m "One more file to add - how to enable grapthics on Rocky Linux"
git commit -m "Some points on Linux Learning"

git push
```
