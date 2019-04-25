# AISR_Simulator
Astronomical Image Subset Simulator

# Dependency
* mysql-client (which depends on openssl)
* CFITSIO (which depends on curl)

# Setup
1. Please intall the above lib
2. create a new file, named as "Makefile.rule" in this project's root dir
3. establish the following path var in Makefile.rule, according to your local settings

* MYSQLCLIENT_DIR = /usr/local/opt/mysql-client
* OPENSSL_DIR     = /usr/local/opt/openssl
* CURL_DIR        = /usr/local/opt/curl
* CFITSIO         = common/cfitsio/