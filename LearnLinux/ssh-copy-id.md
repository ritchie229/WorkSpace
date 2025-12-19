```bash
sudo su
cd .ssh/
ssh-keygen -t ed25519 -C "rishat.mukhtarov@gmail.com"
eval "$(ssh-agent -s)"
ssh-copy-id -i ~/.ssh/id_ed25519.pub root@192.168.0.107
ssh root@192.168.0.107
```
```bash
clip < ~/.ssh/id_ed25519.pub
cat ~/.ssh/id_ed25519.pub | clip
```
```bash
git config --global user.email "rishat.mukhtarov@gmail.com"
git config --global user.name "ritchie229"
```
Простое копирование ssh ключей между серверами c использованием утилиты ssh-copy-id 
<br>
Традиционно администраторы решают задачу копирования ssh ключей между серверами путем копирования содержимого файла /root/.ssh/id_rsa.pub с сервера server1 на server2 в файл /root/.ssh/authorized_keys. Копируют обычно из одного терминала в другой, но есть более изящное решение — это использование утилиты ssh-copy-id, которая позволяет скопировать содержимое id_rsa.pub сервера источник (в нашем случае server1) на сервер приемник (server2) в нужный нам authorized_keys не открывая консоль сервера приемника (server2).
<br>

Исходные данные: 2 сервера с Debian 8 (server1 и server2). <br>
Задача: Организовать вход по ssh ключу с сервера server1 (источник) на server2 (приемник) с правами root.<br>

Итак сделаем все по порядку:<br>

1. На server1 генерируем публичный открытый и закрытый RSA-ключи. Делаем это под пользователем root:
```bash
ssh-keygen -t rsa
```
Если на сервере уже есть эти ключи, то он выдаст предупреждение, где нужно будет либо подтвердить замену старых ключей либо отказаться.<br>

Мы создаем ключи впервые, поэтому предупреждения не будет, будет выведена примерно такая информация:<br>
> [!INFORMATION]
> Generating public/private rsa key pair.<br>
> Enter file in which to save the key (/root/.ssh/id_rsa): <-- ENTER <br>
> Created directory '/root/.ssh'.<br>
> Enter passphrase (empty for no passphrase): <-- ENTER<br>
> Enter same passphrase again: <-- ENTER <br>
> Your identification has been saved in /root/.ssh/id_rsa.<br>
> Your public key has been saved in /root/.ssh/id_rsa.pub.<br>

Вы можете защитить приватный ключ паролем и тогда чтобы попасть на сервер server2 по ssh ключу нужно будет ввести этот пароль, я настоятельно рекомендую для доступа с уровнем root ввести пароль на приватный ключ.<br>

Ключи сгенерированы, мы можем проверить под пользователем root выполнив команду<br>
```bash
cat ~/.ssh/id_rsa.pub
```
В ответ увидим примерно:
```
ssh-rsa AAAAB3Nz.....ywWmpl root@server1
```
2. Теперь нужно передать публичный ключ id_rsa.pub пользователя root на server2, для этого на server1 выполняем:<bash>
```bash
ssh-copy-id -i ~/.ssh/id_rsa.pub root@server2
```
Вводим пароль root от сервера server2 и ключ будет передан и записан в нужный файл `authorized_keys` <br>

Важное уточнение: Чтобы передать публичный ключ на `server2` под `root` нужно чтобы пользователю `root` было разрешен вход по `ssh` на `server2`, обычно при базовой установке Debian/Ubuntu вход под `root` по `ssh` разрешен, это настраивается директивой `PermitRootLogin` в файле `/etc/ssh/sshd_config`
<br>
```yaml
PermitRootLogin yes — Вход под root по ssh разрешен.

PermitRootLogin no — Вход под root по ssh запрещен.

PermitRootLogin without-password — Вход под root по ssh разрешен только по ssh ключам.

PermitRootLogin forced-commands-only — Вход под root по ssh разрешен только по ssh ключам и только для выполнения заранее определенной команды, сама команда прописывается в /root/.ssh/authorized_keys в формате:

command="rsync" ssh-rsa AAAAB3N……. root@server2
```
После изменения PermitRootLogin не забудьте перезапустить службу sshd командой:<br>
```bash
service sshd restart
```
3. Теперь Вы можете зайти c `server1` на `serve2` под `root` без пароля, проверяем находясь под `root` на `server1`:
```bash
ssh root@server2
```
