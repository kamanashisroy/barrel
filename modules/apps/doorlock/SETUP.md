Please download the archlinux rpi image and install first.

Install additional packages
===============================
Apply following commands:

```
pacman -Syu
pacman -S php apache php-apache php-fpm
```

### Configure php
Now edit the /etc/php/php-fpm.conf file, and see the unix socket location. There will be something like the following.

```
listen = /run/php-fpm/php-fpm.sock
```

Now edit the /etc/php/php.ini file. There will be a line defining open_basedir. It should be like the following,

```
open_basedir = /srv/http/:/home/:/tmp/:/usr/share/pear/:/usr/share/webapps/:/sys/class/gpio/gpio4
```

### Configure http

Then you need to edit /etc/http/http.conf file and add the following line before 'DocumentRoot'.

```
ProxyPassMatch ^/(.*\.php(/.*)?)$ unix:/run/php-fpm/php-fpm.sock|fcgi://127.0.0.1:9000/srv/http/
```

Near this line, please change it to add index.php .

```
<IfModule dir_module>
    DirectoryIndex index.html index.php
</IfModule>
```

### Start the services.

Start php-fpm and apache.

```
php-fpm
apachectl restart
```

You can start the services using systemctl.

```
systemctl enable php-fpm.service httpd.service
```

Install the website
======================

Remove the /src/http directory and move website.tgz there. uncompress,

```
tar -xzf website.tgz 
mv website /src/http
echo "4" > /sys/class/gpio/export
echo "out" > /sys/class/gpio/gpio4/direction
```

Now see if it works from the browser.

Autostart services
====================

You may need a auto start script to do certain things on startup.
Put the following code in /usr/lib/systemd/system/doorlock.service file.

```
[Unit]
Description=Doorlock Opener

[Service]
ExecStartPre=/usr/bin/echo 4 >/sys/class/gpio/export
ExecStart=/usr/bin/echo out >/sys/class/gpio/gpio4/direction
ExecStart=/usr/bin/chmod a+rw /sys/class/gpio/gpio4/value

[Install]
WantedBy=sysinit.target
```

Now enable the services to startup everything while booting.

```
systemctl enable php-fpm.service doorlock.service httpd.service
reboot
```
