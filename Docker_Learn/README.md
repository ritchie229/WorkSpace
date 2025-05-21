# Older versions of Docker Desktop
https://gist.github.com/kupietools/2f9f085228d765da579f0f0702bec33c
https://docs.docker.com/desktop/release-notes/#4242


# Install on Debian like
sudo apt update
sudo apt install apt-transport-https
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"
sudo apt update
sudo apt install docker-ce
sudo systemctl status docker
sudo usermod -aG docker $USER
